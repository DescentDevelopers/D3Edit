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
 


#ifndef __VISEFFECT_EXTERNAL_H_
#define __VISEFFECT_EXTERNAL_H_


#include "pstypes.h"
#include "pserror.h"
#include "vecmat.h"

#define MAX_VIS_EFFECTS	4096 //DAJ utb 5000

// types
#define VIS_NONE			0
#define VIS_FIREBALL		1

// Flags
#define VF_USES_LIFELEFT		1
#define VF_WINDSHIELD_EFFECT	2
#define VF_DEAD					4
#define VF_PLANAR					8
#define VF_REVERSE				16
#define VF_EXPAND					32
#define VF_ATTACHED				64
#define VF_NO_Z_ADJUST			128
#define VF_LINK_TO_VIEWER		256	// Always link into the room that the viewer is in

struct object;

typedef struct
{
	int obj_handle;
	int dest_objhandle;

	ushort modelnum;
	ushort vertnum;
	ushort end_vertnum;

	ubyte subnum,subnum2;	
} vis_attach_info;

typedef struct
{
	ubyte width;
	ubyte height;
	ubyte texture;			
} axis_billboard_info;


typedef struct
{
	vector pos;
	vector end_pos;	
	vector velocity;
	float mass;
	float drag;
	float size;
	float lifeleft;
	float lifetime;
	float creation_time;

	int roomnum;
	
	int phys_flags;
	
	short custom_handle;
	ushort lighting_color;

	ushort flags;

	short next;
	short prev;

	vis_attach_info attach_info;
	axis_billboard_info billboard_info;

	ubyte movement_type;
	ubyte type,id;
} vis_effect;

#endif