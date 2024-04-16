/*
 THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF OUTRAGE
 ENTERTAINMENT, INC. ("OUTRAGE").  OUTRAGE, IN DISTRIBUTING THE CODE TO
 END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
 ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
 IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
 SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
 FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
 CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
 AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.
 COPYRIGHT 1996-2000 OUTRAGE ENTERTAINMENT, INC.  ALL RIGHTS RESERVED.
 */
 

#include "ddvidlib.h"
#include "pserror.h"

//	DirectDraw Display mode enumeration callback
HRESULT WINAPI DDEnumModesCallback(LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext);


// inits fullscreen system
bool ddvidfs_Init()
{
	HRESULT hres;

	hres = DirectDrawCreate(NULL, &DDVideo_info.lpDD, NULL);

	if (hres != DD_OK) {
		Error("Failure to initialize DirectDraw driver. (%d)", LOWORD(hres));
	}


	hres = DDVideo_info.lpDD->SetCooperativeLevel(DDVideo_info.hWnd, 
											DDSCL_ALLOWREBOOT | 
											DDSCL_EXCLUSIVE | 
											DDSCL_FULLSCREEN);
	if (hres != DD_OK) {
		Error("Failed to set access mode for DirectDraw driver. (%d)", LOWORD(hres));
	}

//	dummy mode
	DDVideo_info.DDModes[DDVideo_info.nDDModes].ddpfPixelFormat.dwRGBBitCount = 0;
	DDVideo_info.DDModes[DDVideo_info.nDDModes].dwWidth = 0;
	DDVideo_info.DDModes[DDVideo_info.nDDModes].dwHeight = 0;
	DDVideo_info.nDDModes++;
	
//	enumerate all display modes.
	if (DDVideo_info.lpDD->EnumDisplayModes(0,NULL,NULL,DDEnumModesCallback) != DD_OK) {
		mprintf((0, "DDVID error: Error enumerating display modes.\n"));
		return false;
	}

	mprintf((0, "Video fullscreen system initialized.\n"));

	return true;
}


//	closes fullscreen system
void ddvidfs_Close()
{
	if (DDVideo_info.lpDDSFront) 
		DDVideo_info.lpDDSFront->Release();

	if (DDVideo_info.lpDD) {
		DDVideo_info.lpDD->RestoreDisplayMode();
		DDVideo_info.lpDD->SetCooperativeLevel(NULL, DDSCL_NORMAL);
		DDVideo_info.lpDD->Release();
		DDVideo_info.lpDD = NULL;
	}

	DDVideo_info.lpDDSFront = NULL;
	DDVideo_info.lpDDSBack = NULL;
	DDVideo_info.hWnd = NULL;
	DDVideo_info.nDDModes = 0;
}


//	uses direct draw.  if paged, allows frame buffer access.
bool ddvidfs_SetVideoMode(int w, int h, int color_depth, bool paged)
{
	HRESULT hres;
	DDSCAPS ddscaps;
	DDSURFACEDESC ddsd;
	int i, mode;
	bool found_mode;

	mode = 0;
	found_mode = false;

//	find closest match for video mode.
	for (i = 0; i < DDVideo_info.nDDModes; i++)
	{
		if (color_depth == (int)DDVideo_info.DDModes[i].ddpfPixelFormat.dwRGBBitCount) {
			if (DDVideo_info.DDModes[i].dwWidth >= (DWORD)w && DDVideo_info.DDModes[mode].dwWidth < (DWORD)w)
				if (DDVideo_info.DDModes[i].dwHeight >=(DWORD)h && DDVideo_info.DDModes[mode].dwHeight < (DWORD)h) {
					mode = i;
					found_mode = true;
				}
		}
	}

	if (!found_mode) {
	//	we couldn't find a mode, error!
		return false;
	}

	if (DDVideo_info.curmode != mode) {

	//	mode should contain the video mode.
		hres = DDVideo_info.lpDD->SetDisplayMode(DDVideo_info.DDModes[mode].dwWidth, 
									DDVideo_info.DDModes[mode].dwHeight,
									DDVideo_info.DDModes[mode].ddpfPixelFormat.dwRGBBitCount);
		ASSERT(DDVideo_info.DDModes[mode].ddpfPixelFormat.dwRGBBitCount >= BPP_16);
		if (hres != DD_OK) 
			Error("Unable to set DirectDraw display mode. (%d)", LOWORD(hres)); 
	}

	DDVideo_info.curmode = mode;

//	if not paged, then this is a single paged system (no lfb access, good for opengl)
	if (!paged) 
		return true;

//	now create surface, dependant on whether an extra page was requested
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	if (paged) {
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.dwBackBufferCount = 1;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	}
	else {
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	}

	hres = DDVideo_info.lpDD->CreateSurface(&ddsd, &DDVideo_info.lpDDSFront, NULL);
	if (hres != DD_OK) 
		Error("Unable to capture DirectDraw display surface. (%d)", LOWORD(hres)); 
		
	
	if (paged) { 
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		
		hres = DDVideo_info.lpDDSFront->GetAttachedSurface(&ddscaps, &DDVideo_info.lpDDSBack);
		if (hres != DD_OK) {
			mprintf((0,"Unable to capture DirectDraw display back surface (%d)", LOWORD(hres))); 
			return false;
		}
	}
	else {
		DDVideo_info.lpDDSBack = NULL;
	}

	return true;
}


//	closes video mode for fs
void ddvidfs_CloseVideo()
{
//	uninitialize old screen
	if (DDVideo_info.lpDDSFront) {
		DDVideo_info.lpDDSFront->Release();
		DDVideo_info.lpDDSFront = NULL;
		DDVideo_info.lpDDSBack = NULL;
	}
}


//	retrieves screen information for fullscreen version
void ddvidfs_GetVideoProperties(int *w, int *h, int *color_depth)
{
	ASSERT(DDVideo_info.curmode > -1);

	*w = DDVideo_info.DDModes[DDVideo_info.curmode].dwWidth;
	*h = DDVideo_info.DDModes[DDVideo_info.curmode].dwHeight;
	*color_depth = (int)DDVideo_info.DDModes[DDVideo_info.curmode].ddpfPixelFormat.dwRGBBitCount;
}


//	flips screen if there's a back buffer
void ddvidfs_VideoFlip()
{
	if (DDVideo_info.lpDDSBack)
		DDVideo_info.lpDDSFront->Flip(NULL, DDFLIP_WAIT);
}


//	returns the directdraw object 
uint ddvidfs_GetDirectDrawObject()
{
	return (uint)DDVideo_info.lpDD;
}


//	DirectDraw Display mode enumeration callback
HRESULT WINAPI DDEnumModesCallback(LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext)
{
	if (DDVideo_info.nDDModes < VM_MAX_MODES) {
		memcpy(&DDVideo_info.DDModes[DDVideo_info.nDDModes], lpDDSurfaceDesc, sizeof(DDSURFACEDESC));
		DDVideo_info.nDDModes++;
	}

	return DDENUMRET_OK;
}


