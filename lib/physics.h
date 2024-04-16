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

#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "vecmat.h"
#include "FindIntersection.h"
#include "object.h"
#include "viseffect.h"

extern int Physics_normal_counter;
extern int Physics_normal_looping_counter;
extern int Physics_walking_counter;
extern int Physics_walking_looping_counter;
extern int Physics_vis_counter;

// The current strength of the world's gravity
extern float Gravity_strength;

#define PHYSICS_UNLIMITED_BOUNCE -1

#ifdef _DEBUG
extern int Physics_player_verbose;
#endif

extern ubyte Default_player_terrain_leveling;
extern ubyte Default_player_room_leveling;

extern bool PhysicsDoSimRot(object *obj, float frame_time, matrix *orient, vector *rotforce, vector *rotvel,
                            angle *turn_roll);
extern void PhysicsDoSimLinear(object *obj, vector *pos, vector *force, vector *velocity, vector *movement_vec,
                               vector *movement_pos, float sim_time, int count);

extern int Physics_NumLinked;
extern int PhysicsLinkList[MAX_OBJECTS];

// Simulate a physics object for this frame
void do_physics_sim(object *obj);

// Quick sim for vis stuff
void do_vis_physics_sim(vis_effect *vis);

// Simulate a physics object for this frame
void do_walking_sim(object *obj);

// Applies an instantaneous force on an object, resulting in an instantaneous
// change in velocity.
void phys_apply_force(object *obj, vector *force_vec, short weapon_index = -1);
void phys_apply_rot(object *obj, vector *force_vec);

// this routine will set the thrust for an object to a value that will
//(hopefully) maintain the object's current velocity
void set_thrust_from_velocity(object *obj);

// Determines the point and normal of the ground point
bool PhysCalcGround(vector *ground_point, vector *ground_normal, object *obj, int ground_num);

// Linked objects arbitrary linking for things like weapons (unlike attached objects)
void DoPhysLinkedFrame(object *obj);

#endif
