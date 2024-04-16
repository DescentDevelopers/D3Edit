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

#ifndef VIS_EFFECT_H
#define VIS_EFFECT_H

#include "viseffect_external.h"

extern vis_effect *VisEffects;
extern int Highest_vis_effect_index;
extern ushort max_vis_effects;

// Returns the next free viseffect
int VisEffectAllocate();

// Frees up a viseffect for use
int VisEffectFree(int visnum);

int VisEffectInitType(vis_effect *vis);

// initialize a new viseffect.  adds to the list for the given room
// returns the object number
int VisEffectCreate(ubyte type, ubyte id, int roomnum, vector *pos);

// link the viseffect  into the list for its room
// Does nothing for effects over terrain
void VisEffectLink(int visnum, int roomnum);

// Unlinks a viseffect from a room
// Does nothing for terrain
void VisEffectUnlink(int visnum);

// when an effect has moved into a new room, this function unlinks it
// from its old room and links it into the new room
void VisEffectRelink(int visnum, int newroomnum);

// Frees all the vis effects that are currently in use
void FreeAllVisEffects();

// Goes through our array and clears the slots out
void InitVisEffects();

// remove viseffect from the world
void VisEffectDelete(int visnum);

// Kills all the effects that are dead
void VisEffectDeleteDead();

// Moves our visuals
void VisEffectMoveAll();

// Renders a vis effect
void DrawVisEffect(vis_effect *vis);

// Creates a some sparks that go in random directions
void CreateRandomSparks(int num_sparks, vector *pos, int roomnum, int which_index = -1, float force_scalar = 1);

// Creates a some line sparks that go in random directions
void CreateRandomLineSparks(int num_sparks, vector *pos, int roomnum, ushort color = 0, float force_scalar = 1);

// Creates vis effects but has the caller set their parameters
// initialize a new viseffect.  adds to the list for the given room
// returns the vis number
int VisEffectCreateControlled(ubyte type, object *parent, ubyte id, int roomnum, vector *pos, float lifetime,
                              vector *velocity, int phys_flags = 0, float size = 0, float mass = 0.0f,
                              float drag = 0.0f, bool isreal = 0);

// Creates a some particles that go in random directions
void CreateRandomParticles(int num_sparks, vector *pos, int roomnum, int bm_handle, float size, float life);

// Attaches viseffects that move with an object
void AttachRandomNapalmEffectsToObject(object *obj);

#endif