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

#ifndef _COLLIDE_H
#define _COLLIDE_H

#include "object.h"
#include "vecmat.h"
#include "FindIntersection.h"

extern ubyte CollisionResult[MAX_OBJECT_TYPES][MAX_OBJECT_TYPES];
extern ubyte CollisionRayResult[MAX_OBJECT_TYPES];

void CollideInit();
void collide_two_objects(object *A, object *B, vector *collision_point, vector *collision_normal,
                         fvi_info *hit_info = NULL);
extern void apply_damage_to_player(object *player, object *killer, float damage);

// Process a collision between an object and a wall
// Returns true if the object hits the wall, and false if should keep going though the wall (for breakable glass)
bool collide_object_with_wall(object *A, float hitspeed, int hitseg, int hitwall, vector *hitpt, vector *wall_normal,
                              float hit_dot);

extern int apply_damage_to_robot(object *robot, float damage, int killer_objnum);

extern int Immaterial;

extern void collide_player_and_weapon(object *player, object *weapon, vector *collision_point);
extern void collide_player_and_materialization_center(object *objp);
extern void collide_robot_and_materialization_center(object *objp);

extern void scrape_object_on_wall(object *obj, int hitseg, int hitwall, vector *hitpt, vector *wall_normal);
extern int maybe_detonate_weapon(object *obj0p, object *obj, vector *pos);

extern void collide_player_and_nasty_robot(object *player, object *robot, vector *collision_point);

extern void net_destroy_controlcen(object *controlcen);
extern void collide_player_and_powerup(object *player, object *powerup, vector *collision_point);
// extern int check_effect_blowup(segment *seg,int side,vector *pnt, object *blower, int force_blowup_flag);
extern void apply_damage_to_controlcen(object *controlcen, float damage, short who);
extern void bump_one_object(object *obj0, vector *hit_dir, float damage);

void ConvertEulerToAxisAmount(vector *e, vector *n, float *w);
void ConvertAxisAmountToEuler(vector *n, float *w, vector *e);

void bump_obj_against_fixed(object *obj, vector *collision_point, vector *collision_normal);

#ifndef NED_PHYSICS
#define RESULT_NOTHING 0
#define RESULT_CHECK_SPHERE_SPHERE 1
#define RESULT_CHECK_SPHERE_POLY 2
#define RESULT_CHECK_POLY_SPHERE 3
#define RESULT_CHECK_BBOX_POLY 4
#define RESULT_CHECK_POLY_BBOX 5
#define RESULT_CHECK_BBOX_BBOX 6
#define RESULT_CHECK_BBOX_SPHERE 7
#define RESULT_CHECK_SPHERE_BBOX 8
#define RESULT_CHECK_SPHERE_ROOM 9
#define RESULT_CHECK_BBOX_ROOM 10
#endif

#endif
