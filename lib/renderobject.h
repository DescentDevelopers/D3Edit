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
#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "object.h"
#include "polymodel.h"

#ifdef _DEBUG
void DrawDebugInfo(object *obj);
void DrawRoomVisPnts(object *obj);
#endif

//	Render an object.  Calls one of several routines based on type
void RenderObject(object *obj);

// Sets the polygon render object type to static (one lightval for whole object)
void RenderObject_SetStatic(float r, float g, float b);

// Sets the polygon render object type to gouraud
void RenderObject_SetGouraud(vector *dir, float r, float g, float b, float scalar = 1.0);

// Sets the object render to draw a polymodel with lightmaps applied
void RenderObject_SetLightmaps(lightmap_object *lmobject);

// Actually draws a polygon model based on the light parameters set by the above
// functions
void RenderObject_DrawPolymodel(object *obj, float *normalized_times);

// Sets the direction of the lightsource to be used when calculating vertex lighting
// The light source vector should be in the models coordinate space
void RenderObject_SetLightDirection(vector *dir);

// Given a position in 3space and a size, returns whether or not that sized point is
// visible from the current view matrix
int IsPointVisible(vector *, float, float *pointz = NULL);

// Draws the 'typing message' icon indicator above an object
void DrawPlayerTypingIndicator(object *obj);

#define POWERUP_SPARKLE_INTERVAL 1.0f / 30.0f
extern float Last_powerup_sparkle_time;

#endif