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
 

/*	Functions
*/

#ifndef DDGRWIN32DX_H
#define DDGRWIN32DX_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "ddgr.h"
#include "ddraw.h"

class oeApplication;


/* Data structures
*/
typedef struct tDXSurface
{
	LPDIRECTDRAWSURFACE	lpdds;
	LPDIRECTDRAWSURFACE	lpddsback;
	bool backbuffer;
} 
tDXSurface;

#define DX_MAX_DEVMODES		32
typedef struct tDDGRDXInternalData				// Internal data for DX subsystem
{
	bool						init;								// is library initialized
	LPDIRECTDRAW			lpDD;								// DirectDraw Object for video manipulation
	HWND						hPrimaryWnd;					// window owning display
	int						vidrefs;							// Number of surface references to hPrimaryWnd.
	tDXSurface				vidsurf;
	DDSURFACEDESC			vidmodes[DX_MAX_DEVMODES];	// Device modes for GDI subsystem (not GDIX)
} 
tDDGRDXInternalData;


/*	Externs */
extern tDDGRDXInternalData DDGR_DX_lib_data;


/*	Macros */
#define DX_DATA(_c) DDGR_DX_lib_data._c


//	Initializes DX subsystem
bool ddgr_dx_Init(oeApplication *app);

//	Closes DX subsystem
void ddgr_dx_Close();

//	Initializes the display for use with the DX subsystem.
bool ddgr_dx_surf_InitVideo(ddgr_surface *sf);

//	Deinitializes the video surface
void ddgr_dx_surf_CloseVideo(ddgr_surface *sf);

//	flips the buffers in a surface.  really only useful for video screens
bool ddgr_dx_surf_FlipVideo(ddgr_surface *sf);

/*	input:
		sf->name is optional.
		sf->w, sf->h, sf->bpp are mandatory
		sf->type and sf->flags are mandatory.
	output:
		sf->obj = surface object.
		sf->locks = 0
*/
bool ddgr_dx_surf_Create(ddgr_surface *sf);
void ddgr_dx_surf_Destroy(ddgr_surface *sf);

/*	retrieves a pointer to surface memory.  allowed to lock one surface multiple times.
		ptr is the returned pointer to surface memory.  used to unlock surface also
		rowsize is the size in bytes of one row of memory.	
*/
bool ddgr_dx_surf_Lock(ddgr_surface *sf, void **ptr, int *rowsize);
bool ddgr_dx_surf_Unlock(ddgr_surface *sf, void *ptr);

//	attaches an OS handle to a surface
void ddgr_dx_surf_AttachHandle(ddgr_surface *sf, unsigned handle);

//	The only graphic primatives
//	clear
//	blt.
void ddgr_dx_surf_Clear(ddgr_surface *dsf, ddgr_color col, int l, int t, int w, int h);
bool ddgr_dx_surf_Blt(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh);


#endif
