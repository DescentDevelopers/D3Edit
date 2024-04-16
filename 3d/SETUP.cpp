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

#include <stdlib.h>

#include "3d.h"
#include "Globvars.h"
#include "Clipper.h"
#include "pserror.h"
#include "renderer.h"

// initialize the 3d system
void g3_Init(void) {
  // div0_init(DM_ERROR);
  atexit(g3_Close);
}

// close down the 3d system
void g3_Close(void) {}

// User-specified aspect ratio, stored as w/h
float Aspect = 0.0;

// allows the program to specify an aspect ratio that overrides the renderer's
// The parameter is the w/h of the screen pixels
void g3_SetAspectRatio(float aspect) { Aspect = aspect; }

// start the frame
void g3_StartFrame(vector *view_pos, matrix *view_matrix, float zoom) {
  float s;

  // Get window size
  rend_GetProjectionParameters(&Window_width, &Window_height);

  // Set vars for projection
  Window_w2 = (float)Window_width / 2.0;
  Window_h2 = (float)Window_height / 2.0;

  // Compute aspect ratio for this window
  float screen_aspect = rend_GetAspectRatio();
  if (Aspect != 0.0) // check for user override
    screen_aspect = screen_aspect * 4.0 / 3.0 / Aspect;
  s = screen_aspect * (float)Window_height / (float)Window_width;

  if (s <= 0) { // scale x
    Matrix_scale.x = s;
    Matrix_scale.y = 1.0;
  } else {
    Matrix_scale.y = 1.0 / s;
    Matrix_scale.x = 1.0;
  }

  Matrix_scale.z = 1.0; // always 1

  // Set the view variables
  View_position = *view_pos;
  View_zoom = zoom;
  Unscaled_matrix = *view_matrix;

  // Compute matrix scale for zoom and aspect ratio

  if (View_zoom <= 1.0) // zoom in by scaling z

    Matrix_scale.z = Matrix_scale.z * View_zoom;

  else { // zoom out by scaling x&y

    float s = 1.0 / View_zoom;

    Matrix_scale.x = Matrix_scale.x * s;
    Matrix_scale.y = Matrix_scale.y * s;
  }

  // Scale the matrix elements
  View_matrix.rvec = Unscaled_matrix.rvec * Matrix_scale.x;
  View_matrix.uvec = Unscaled_matrix.uvec * Matrix_scale.y;
  View_matrix.fvec = Unscaled_matrix.fvec * Matrix_scale.z;

  // Reset the list of free points
  InitFreePoints();

  // Reset the far clip plane
  g3_ResetFarClipZ();
}

// this doesn't do anything, but is here for completeness
void g3_EndFrame(void) {
  // make sure temp points are free
  CheckTempPoints();
}

// get the current view position
void g3_GetViewPosition(vector *vp) { *vp = View_position; }

void g3_GetViewMatrix(matrix *mat) { *mat = View_matrix; }

void g3_GetUnscaledMatrix(matrix *mat) { *mat = Unscaled_matrix; }

// Gets the matrix scale vector
void g3_GetMatrixScale(vector *matrix_scale) { *matrix_scale = Matrix_scale; }
