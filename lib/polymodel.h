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

#ifndef POLYMODEL_H
#define POLYMODEL_H

#include "manage.h"
#include "pstypes.h"
#include "vecmat.h"
#include "3d.h"
#include "robotfirestruct.h"
#include "polymodel_external.h"
#include "object_external_struct.h"

#define PM_COMPATIBLE_VERSION 1807
#define PM_OBJFILE_VERSION 2300

#define WB_INDEX_SHIFT 16      // bits to shift over to get the weapon battery index (after masking out flags)
#define SOF_WB_MASKS 0x01F0000 // Room for 32 weapon batteries (currently we only use 21 slots)

#define SOF_MONITOR_MASK 0x0ff0 // mask for monitors

extern int Num_poly_models;
extern poly_model Poly_models[];

extern int Polymodel_use_effect;
extern polymodel_effect Polymodel_effect;
extern polymodel_light_type Polymodel_light_type;
extern float Polylighting_static_red;
extern float Polylighting_static_green;
extern float Polylighting_static_blue;
extern ubyte *Polylighting_gouraud;
extern vector *Polymodel_light_direction, Polymodel_fog_portal_vert, Polymodel_fog_plane, Polymodel_specular_pos,
    Polymodel_bump_pos;
extern lightmap_object *Polylighting_lightmap_object;

extern vector Model_eye_position;
extern vector Interp_pos_instance_vec;
extern g3Point Robot_points[];

// Flag to draw an outline around the faces
extern bool Polymodel_outline_mode;

inline float POLY_WIDTH(int model_num) { return Poly_models[model_num].maxs.x - Poly_models[model_num].mins.x; }

inline float POLY_HEIGHT(int model_num) { return Poly_models[model_num].maxs.y - Poly_models[model_num].mins.y; }

inline float POLY_DEPTH(int model_num) { return Poly_models[model_num].maxs.z - Poly_models[model_num].mins.z; }

// given a filename, reads in a POF and returns an index into the Poly_models array
// returns -1 if something is wrong
int LoadPolyModel(char *filename, int pageable);

// gets the filename from a path, plus appends our .pof extension
void ChangePolyModelName(char *src, char *dest);

// Searches thru all polymodels for a specific name, returns -1 if not found
// or index of polymodel with name
int FindPolyModelName(char *name);

// Draws a polygon model to the viewport
// Normalized_time is an array of floats from 0 to 1 that represent how far into
// an animation state we are

// This one is for static lighting - ie 1 light value for the entire model
void DrawPolygonModel(vector *pos, matrix *orient, int model_num, float *normalized_time, int flags, float r, float g,
                      float b, uint f_render_sub = 0xFFFFFFFF, ubyte use_effect = 0, ubyte overlay = 0);

// This one is for gouraud shading - the lightdir is the normalized light direction, and lightscalar is a 0-1 scalar to
// apply
void DrawPolygonModel(vector *pos, matrix *orient, int model_num, float *normalized_time, int flags, vector *lightdir,
                      float r, float g, float b, uint f_render_sub = 0xFFFFFFFF, ubyte use_effect = 0,
                      ubyte overlay = 0);

// This one is for lightmap rendering
void DrawPolygonModel(vector *pos, matrix *orient, int model_num, float *normalized_time, int flags,
                      lightmap_object *lm_object, uint f_render_sub, ubyte use_effect = 0, ubyte overlay = 0);

// gives the interpreter an array of points to use
void g3_SetInterpPoints(g3Point *pointlist);

// calls the object interpreter to render an object.  The object renderer
// is really a seperate pipeline. returns true if drew
int InterpPolygonModel(poly_model *pm);

// Inits our models array
int InitModels();

// Frees polymodel located in index of Poly_models array
void FreePolyModel(int index);

// Given an actual keyframe number, returns the normalized (0 to 1) position of that
// keyframe.  Handle is an index into the Poly_models array
float GetNormalizedKeyframe(int handle, float num);

// Goes through all poly models and gets all missing textures
void RemapPolyModels();

// For macintosh, we must swap the interpreted model code
void SwapPolymodelData(ubyte *data);

// Sets a positional instance
void StartPolyModelPosInstance(vector *posvec);

// Pops a positional instance
void DonePolyModelPosInstance();

void SetModelAngles(poly_model *po, float *normalized_angles);
void SetModelInterpPos(poly_model *po, float *normalized_pos);

void SetNormalizedTimeObj(object *obj, float *normalized_time);
void SetNormalizedTimeAnim(float norm_anim_frame, float *normalized_time, poly_model *pm);

void WBClearInfo(poly_model *pm);

// Computes the size of a polymodel.
float ComputeDefaultSize(int type, int handle, float *size_ptr);

// Returns the total number of faces in a model
int CountFacesInPolymodel(poly_model *pm);

// Rendering functions
int RenderPolygonModel(poly_model *, uint f_render_sub = 0xFFFFFFFF);
void RenderSubmodel(poly_model *pm, bsp_info *sm, uint f_render_sub);

//	returns point within polymodel/submodel in world coordinates.
void GetPolyModelPointInWorld(vector *dest, poly_model *pm, vector *wpos, matrix *orient, int subnum, vector *pos,
                              vector *norm = NULL);
void GetPolyModelPointInWorld(vector *dest, poly_model *pm, vector *wpos, matrix *orient, int subnum,
                              float *normalized_time, vector *pos, vector *norm = NULL);

// Returns 1 if this submodel shouldn't be rendered
int IsNonRenderableSubmodel(poly_model *pm, int submodelnum);

// Sets the effect used by a polymodel
void SetPolymodelEffect(polymodel_effect *);

// Pages in a polymodel if its not already in memory
void PageInPolymodel(int polynum, int type = -1, float *size_ptr = NULL);

// Gets a pointer to a polymodel.  Pages it in if neccessary
poly_model *GetPolymodelPointer(int polynum);

// Frees all the polymodel data, but doesn't free the actual polymodel itself
void FreePolymodelData(int i);

// Sets the position and rotation of a polymodel.  Used for rendering and collision detection
void SetModelAnglesAndPos(poly_model *po, float *normalized_time, uint subobj_flags = 0xFFFFFFFF);

#endif
