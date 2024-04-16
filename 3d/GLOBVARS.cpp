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

#include "3d.h"
#include "Globvars.h"
#include "float.h"

vector View_position;
float View_zoom;

float Far_clip_z = FLT_MAX; // set to a really really far distance initially

ubyte Clip_custom = 0;
float Clip_plane_distance = 0;
vector Clip_plane;

matrix Unscaled_matrix; // before scaling
matrix View_matrix;

vector Matrix_scale; // how the matrix is scaled, window_scale * zoom

int Window_width;  // the actual width
int Window_height; // the actual height

float Window_w2; // width/2
float Window_h2; // height/2
