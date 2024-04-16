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

#ifndef _LIGHTING_H
#define _LIGHTING_H

#include "object.h"
#include "room.h"
#include "terrain.h"

#define MAX_LIGHT 1.0
#define LIGHTMAP_SPACING 5.0

#define VOLUME_SPACING 10.0

#define INVISIBLE_VOLUME_ELEMENT 0x01

#define MAX_SPECULAR_INCREMENTS 4096

extern float Specular_tables[3][MAX_SPECULAR_INCREMENTS];

typedef struct {
  ushort *mem_ptr;
  ubyte used;
} dynamic_lightmap;

typedef struct {
  ushort lmi_handle;
} dynamic_face;

typedef struct {
  ushort cellnum;
  ubyte r, g, b;
} dynamic_cell;

// Sets up our dynamic lighting maps
void InitDynamicLighting();

// Returns the class index of a specified lightmap resolution
int GetLightmapClass(int res);

// Returns an index into the Dynamic_lightmaps array.  Index returned is marked as unused
int FindFreeDynamicLightmap(int cl);

// Applies dynamic lighting to the room faces based on the light coming from
// an object
void ApplyLightingToRooms(vector *, int, float, float, float, float, vector *light_direction = NULL,
                          float dot_range = 0);

// Clears the used flag for the dynamic lightmaps
void ClearDynamicLightmaps();

// Changes the terrain shading to approximate lighting
void ApplyLightingToTerrain(vector *pos, int cellnum, float light_dist, float red_scale, float green_scale,
                            float blue_scale, vector *light_direction = NULL, float dot_range = 0);

// Gets the viewable lightmap elements
void FindValidLightmapElements(face *fp, dynamic_face *dynamic_fp, vector *light_pos, float light_dist);
// Does a quad tree algo to find what lightmap elements are viewable from our lightsource
int SearchLightQuadTree(face *fp, vector *rvec, vector *uvec, dynamic_face *dynamic_fp, vector *light_pos,
                        float light_dist);

// Given a float, returns the index into the Ubyte_float_table that this number
// corresponds to
ubyte Float_to_ubyte(float fnum);

extern float Ubyte_to_float[];

// Draws the shadows that happen to be falling on a particular face
void DoShadowsForFace(room *rp, int facenum);

// Sets the num_timer_faces field in Room structure to correspond to the number of faces
// that have flickering lights
void CountFaceLights();

// Goes through all rooms and all faces and lights any faces that have their timer values
// set
void DoFaceLighting();

// Sets pulse parameters for an entire room
void SetRoomPulse(room *rp, ubyte pulse_time, ubyte pulse_offset);

// Returns the total number of bytes needed for volume lighting in this room
int GetVolumeSizeOfRoom(room *rp, int *w = NULL, int *h = NULL, int *d = NULL);

// Returns a lightmap that can be applied for specular lighting
int GetSpecularLightmapForFace(vector *pos, room *rp, face *fp);

// Kills the lighting that a face casts and dampens all the faces that light influences
void DestroyLight(int roomnum, int facenum);

// Adds to our list of destroyable lights that got destroyed this frame
void AddToDestroyableLightList(int roomnum, int facenum);

// Goes through our destroyable light list and actually kills all the lights
void DoDestroyedLightsForFrame();

// Blends all the edges that need blending for this frame
void BlendAllLightingEdges();

#endif
