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
 

#ifndef _GLOBVARS_H
#define _GLOBVARS_H

#include "pserror.h"

#define MAX_POINTS_IN_POLY 100

extern int Window_width,Window_height;		//the actual integer width & height
extern float Window_w2,Window_h2;	  		//width,height/2

extern int free_point_num;

extern float View_zoom;
extern vector View_position,Matrix_scale;
extern matrix View_matrix,Unscaled_matrix;

extern float Far_clip_z;

// For custom clipping plane
extern ubyte Clip_custom;
extern float Clip_plane_distance;
extern vector Clip_plane;

#endif
