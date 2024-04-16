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

#ifndef DDVID_H
#define DDVID_H

#include "pstypes.h"
#include "grdefs.h"

class oeApplication;

//	called first to allow fullscreen video access
bool ddvid_Init(oeApplication *app, char *driver);
void ddvid_Close();

//	sets the appropriate video mode.
bool ddvid_SetVideoMode(int w, int h, int color_depth, bool paged);

//	sets screen handle
void ddvid_SetVideoHandle(unsigned handle);

//	retrieves screen information
void ddvid_GetVideoProperties(int *w, int *h, int *color_depth);

//	retrieves screen aspect ratio.
float ddvid_GetAspectRatio();

//	retreives frame buffer info for a video mode.
void ddvid_LockFrameBuffer(ubyte **data, int *pitch);
void ddvid_UnlockFrameBuffer();

//	flips screen if there's a back buffer
void ddvid_VideoFlip();

// only available to DD_ACCESS libraries.
#if defined(DD_ACCESS_RING)
#if defined(WIN32)

//	dd_obj is the DIRECTDRAW OBJECT for the system.
//	dds_obj is the DIRECTDRAWSURFACE OBJECT for the screen
void ddvid_GetVideoDDrawProps(uint *dd_obj, uint *dds_obj);

#endif // WIN32

#endif // DD_ACCESS

#endif
