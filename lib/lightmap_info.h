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
 

#ifndef LIGHTMAP_INFO_H
#define LIGHTMAP_INFO_H
// Lightmap info header

#include "pstypes.h"
#include "pserror.h"
#include "vecmat.h"

#define BAD_LMI_INDEX	65535

// What this lightmap is used for:
#define LMI_ROOM						0
#define LMI_ROOM_OBJECT				1
#define LMI_TERRAIN					2
#define LMI_TERRAIN_OBJECT			3
#define LMI_DYNAMIC					4
#define LMI_EXTERNAL_ROOM			5
#define LMI_EXTERNAL_ROOM_OBJECT	6

typedef struct
{
	ubyte xspacing,yspacing;
	ushort lm_handle;
	vector upper_left,normal;
	ubyte width,height,x1,y1;
	ubyte used;


	ushort dynamic;
	short spec_map;

	ubyte type;		// see LMI_types above
} lightmap_info;

extern lightmap_info *LightmapInfo;
extern int Num_of_lightmap_info;
extern int Num_lightmap_infos_read;

#define MAX_LIGHTMAP_INFOS		(65534)

// Sets all the lightmaps to unused
void InitLightmapInfo(int nummaps = 0);

// Allocs a lightmap of w x h size
// Returns lightmap handle if successful, -1 if otherwise
int AllocLightmapInfo (int w,int h,int type,bool alloc_lightmap=true);

// Given a handle, frees the lightmap memory and flags this lightmap as unused
void FreeLightmapInfo (int handle);

// Gets the width of this lightmap_info handle
int lmi_w(int handle);

// Gets the height of this lightmap_info handle
int lmi_h(int handle);

// Softens the edges of lightmaps so there are fewer artifaces
void ShadeLightmapInfoEdges (int type);
void BlurLightmapInfos (int type);

#endif

