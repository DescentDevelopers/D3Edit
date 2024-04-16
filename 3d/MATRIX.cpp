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
#include "globvars.h"

void scale_matrix(void);

// set view from x,y,z & p,b,h, zoom.  Must call one of g3_SetView*()
void g3_SetViewAngles(vector *view_pos, angvec *view_orient, float zoom) {
  View_zoom = zoom;
  View_position = *view_pos;

  vm_angles_2_matrix(&View_matrix, view_orient);

  scale_matrix();
}

// set view from x,y,z, viewer matrix, and zoom.  Must call one of g3_SetView*()
void g3_SetViewMatrix(vector *view_pos, matrix *view_matrix, float zoom) {
  View_zoom = zoom;
  View_position = *view_pos;

  View_matrix = *view_matrix;

  scale_matrix();
}

// performs aspect scaling on global view matrix
void scale_matrix(void) {
  Unscaled_matrix = View_matrix; // so we can use unscaled if we want

  Matrix_scale = Window_scale;

  if (View_zoom <= f1_0) // zoom in by scaling z

    Matrix_scale.z = Matrix_scale.z * View_zoom;

  else { // zoom out by scaling x&y

    float s = 1.0 / View_zoom;

    Matrix_scale.x = Matrix_scale.x * s;
    Matrix_scale.y = Matrix_scale.y * s;
  }

  // now scale matrix elements

  View_matrix.rvec *= Matrix_scale.x;
  View_matrix.uvec *= Matrix_scale.y;
  View_matrix.fvec *= Matrix_scale.z;
}
