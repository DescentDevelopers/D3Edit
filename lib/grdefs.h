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
 


#ifndef GRDEFS_H
#define GRDEFS_H

#include "pstypes.h"

//	bit depth info
#define BPP_TO_BYTESPP(x)    (((x)+7)>>3)

#define BPP_DEFAULT	0					// default for current display 
#define BPP_8			8					// 8-bit paletted.
#define BPP_15			15					// 5-5-5 + chroma Hicolor
#define BPP_16			16					// 5-6-5 Hicolor
#define BPP_24			24					// 24 bit true color
#define BPP_32			32					// 32 bit true color

#define FIXED_SCREEN_WIDTH				640
#define FIXED_SCREEN_HEIGHT			480
		  
//	transparent color constant here.
#define OPAQUE_FLAG16	0x8000
#define TRANSPARENT_COLOR32 0x0000FF00
#define NEW_TRANSPARENT_COLOR	0x0000
#define OPAQUE_FLAG		OPAQUE_FLAG16

//	a new color definition
typedef uint ddgr_color;

// Color constants
const ddgr_color GR_NULL		= 0xffffffff,					// don't do a thing with this.
					GR_BLACK			= 0x00000000,
					GR_GREEN			= 0x0000ff00,
					GR_RED			= 0x00ff0000,
					GR_BLUE			= 0x000000ff,
					GR_DARKGRAY		= 0x00404040,
					GR_LIGHTGRAY	= 0x00c0c0c0,
					GR_WHITE			= 0x00ffffff;

#define GR_COLOR_CHAR		1			// ASCII 1 and (r,g,b) changes current text color in string.

//	MACROS
inline ddgr_color GR_RGB(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}

inline ushort GR_RGB16(int r, int g, int b)
{
	return (((r>>3)<<10) + ((g>>3)<<5) + (b>>3));
}

inline ushort GR_COLOR_TO_16(ddgr_color c)
{
	int r,g,b;
	r = ((c & 0x00ff0000) >> 16);
	g = ((c & 0x0000ff00) >> 8);
	b = (c & 0x000000ff);
	
	return (ushort)(((r>>3)<<10) + ((g>>3)<<5) + (b>>3));
}

inline int GR_COLOR_RED(ddgr_color c)
{
	int r = ((c & 0x00ff0000) >> 16);
	return (int)r;
}

inline int GR_COLOR_GREEN(ddgr_color c)
{	
	int g = ((c & 0x0000ff00) >> 8);
	return (int)g;
}

inline int GR_COLOR_BLUE(ddgr_color c)
{
	int b = (c & 0x000000ff);
	return (int)b;
}

inline ddgr_color GR_16_TO_COLOR(ushort col)
{
	int r,g,b;

	r = (col & 0x7c00) >> 7;
	g = (col & 0x03e0) >> 2;
	b = (col & 0x001f) << 3;

	return GR_RGB(r,g,b);
}


#endif