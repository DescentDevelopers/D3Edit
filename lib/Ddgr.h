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
 


#ifndef _DDGR_H
#define _DDGR_H

#include "pstypes.h"
#include "macros.h"		
#include "grdefs.h"

//	----------------------------------------------------------------------------
//	DDGR 
//		version 1.0						// DirectDraw, GDI support
//		version 2.x						// fullscreen-windowed remanagement.
//	----------------------------------------------------------------------------


//	----------------------------------------------------------------------------
//	Data structures
//	----------------------------------------------------------------------------

/*	Type definitions */

class oeApplication;

/*	
	Diagnostic DDGR system types and functions
*/

typedef struct ddgr_init_info 
{
	oeApplication *obj;						// the app object created by app calling
	char *subsystem;							// subsystem name (i.e. 'DirectDraw', 'GDI')
	ushort windowed:1;						// are we running in a fullscreen or windowed mode
	ushort debug:1;							// are we running in debug mode?
} 
ddgr_init_info;

/*	app = application object.
	subsystem = subsystem name ('DirectDraw', 'GDI')
	fullscreen = whether it's full screen or windowed 
*/
bool ddgr_Init(oeApplication *app, char *subsystem, bool fullscreen);
void ddgr_Close();
void ddgr_GetSubsystem(char *name, bool *fullscreen);

//	returns aspect ratio of current display.
float ddgr_GetAspectRatio();


/*	Surface bit depths
		The bitdepth of the surface determines the color format of the surface.  Renderers
		should use this value to plot
*/

//	Green with all 6 bits set to 1 is our transparent color
//	default transparent color to 16bit, but all code should use the first 2 defines.

/*	Surface types
		Surfaces symbolize a flat 2d surface where pixels are lit.  Essentially, a surface could
		be a bitmap, but if it's the display, it's a bitmap managed by the video card. 
		The goal of this library is to provide a clean, device-independent method to accessing
		surfaces.

	SURFTYPE_VIDEOSCREEN:
		The video screen is a physical or virtual display.
		When you create a videoscreen, you may specify either it is monopage or dualpage (backbuffer)
		When dualpage, the program can RENDER to the 1st page.  To update the video display, you
		must perform a surface flip.

	SURFTYPE_GENERIC:
		This is a generic bitmap managed by the operating system.  RENDERING is allowed.
 */
const int	SURFTYPE_VIDEOSCREEN	= 1,	// This is equivical to the display.
				SURFTYPE_GENERIC		= 2;	//	This is an offscreen bitmap.


/*	Surface flags
		Flags modify a surfaces behavior.  A surface may have a backbuffer, which is only really
		useful for videoscreens. 

	SURFFLAG_BACKBUFFER:
		This surface has a backbuffer.   
			v2.0  Supported in only videoscreen surfaces.

	SURFFLAG_COLORKEY:
		This surface was created with colorkeying in mind.
		Renderers should keep this in mind, and check this flag.
 */
const int	SURFFLAG_BACKBUFFER	= 1,
				SURFFLAG_COLORKEY		= 2;


/*	Surface structures 
		The surface 		
*/
const int	SURF_NAMELEN			= 16;

typedef struct ddgr_surface
{
	void		*obj;									// internal structure info to library
	char		name[SURF_NAMELEN];				// name	
	int		w,h,bpp;								// width, height and bit depth
	ushort	type;									// how driver handles this surface
	ushort	flags;								// colorkeying, etc.
	int		locks;								// lock count.
}
ddgr_surface;

#if defined(DD_ACCESS_RING)					// only available to DD_ACCESS libraries.
#if defined(WIN32)
/*	
	ddraw_surf = true	if this is a true DirectDraw surface, false if a GDI surface
	object_ptr = DirectDraw object if ddraw_surf = true, a HDC if a GDI surface.
*/
void ddgr_surf_GetPrivateData(ddgr_surface *sf, bool *ddraw_surf, uint *object_ptr);

//	you must typecase this return value to LPDIRECTDRAW
unsigned ddgr_GetDDrawObject();
#endif	// WIN32
#endif	// DD_ACCESS_RING


/*	Surface Functions
*/

/*	input:
		sf->name is optional.
		sf->w, sf->h, sf->bpp are mandatory
		sf->type and sf->flags are mandatory.
	output:
		sf->obj = surface object.
		sf->locks = 0
*/
bool 	ddgr_surf_Create(ddgr_surface *sf);
void	ddgr_surf_Destroy(ddgr_surface *sf);

/*	retrieves a pointer to surface memory.  allowed to lock one surface multiple times.
		ptr is the returned pointer to surface memory.  used to unlock surface also
		rowsize is the size in bytes of one row of memory.	
*/
bool	ddgr_surf_Lock(ddgr_surface *sf, void **ptr, int *rowsize);
bool	ddgr_surf_Unlock(ddgr_surface *sf, void *ptr);

//	attaches an OS handle to a surface
void	ddgr_surf_AttachHandle(ddgr_surface *sf, unsigned handle);

/*	initializes a video screen from the given input surface which specifies the dimensions
	of the screen. 
		sf->name is optional
		sf->w, sf->h are mandatory
		sf->bpp is recommended.  if set to BPP_DEFAULT, it uses the current display bit depth
		sf->type = SURFTYPE_VIDEOSCREEN
		sf->flags = 0 or SURFFLAG_BACKBUFFER.  surfaces with backbuffers allow rendering to
						them and display via flip.  monopage surfaces don't have this luxury.
*/
bool 	ddgr_surf_InitVideo(ddgr_surface *sf);

/*	close video reverses the operation of init video for that surface.  the display should stay
	the same, but no more operations may occur to that surface through this library.
*/
void	ddgr_surf_CloseVideo(ddgr_surface *sf);

/*	flips the buffers in a surface.  really only useful for video screens
*/
bool	ddgr_surf_FlipVideo(ddgr_surface *sf);

/*	graphic primatives
*/
void ddgr_surf_Clear(ddgr_surface *dsf, ddgr_color col, int l, int t, int w, int h);
bool ddgr_surf_Blt(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh);


/*	
	8-bit palette surface structures
*/
typedef struct ddgr_rgb 
{
	ubyte r,g,b;									// RGB triplet
	ubyte x;											// reserved...	
} 
ddgr_rgb;

typedef struct ddgr_palette 
{
	void *obj;										// internal object
	ddgr_rgb rgb[256];							// rgb values for palette.
} 
ddgr_palette;

//	attaches a palette to an 8-bit surface only.
bool ddgr_surf_AttachPalette(ddgr_surface *surf, ddgr_palette *pal);

//	grabs a palette.
bool ddgr_surf_GetPalette(ddgr_surface *surf, ddgr_palette *pal);

//	creates and destroys palette objects.
bool ddgr_8bit_CreatePalette(ddgr_palette *pal);
bool ddgr_8bit_DestroyPalette(ddgr_palette *pal);

//	loads a palette with specified entriyes
bool ddgr_8bit_LoadPalette(ddgr_palette *pal, int start, int count);

//	returns an index into the palette
int ddgr_8bit_FindClosestColor(ddgr_palette *pal,ddgr_color col);

#endif
								
