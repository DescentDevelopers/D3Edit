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
 

#ifndef DAMAGE_H
#define DAMAGE_H

#include "damage_external.h"
#include "vecmat.h"
#include "DeathInfo.h"

// Maximum damage magnitude
#define MAX_DAMAGE_MAG	20.0f
#define MAX_EDRAIN_MAG	18.0f

struct object;
struct room;

//	Applies damage to a player object, returns true if damage is applied.
bool ApplyDamageToPlayer(object *playerobj, object *killer, int damage_type,float damage_amount,int server_says=0,int weapon_id=255,bool playsound=1);

//	Applies damage to a robot object, returns true if damage is applied.
bool ApplyDamageToGeneric(object *robotobj, object *killer, int damage_type, float damage, int server_says=0,int weapon_id=255);

//Starts on object on fire
void SetNapalmDamageEffect (object *obj,object *killer,int weapon_id);

// Chrishack -- milestone
void DecreasePlayerEnergy (int slot,float energy);

// Adds a bit of shake to the camera
void AddToShakeMagnitude (float delta);

//This function sortof replaces ExplodeObject()
//Parameters:	objp - the object to destroy
//					killer - the object who is killing it, or NULL 
//					damage - how much damage was applied in the death blow?
//					death_flags - how the object dies
//					delay_time - how long to delay, if a timed delay
void KillObject(object *objp,object *killer,float damage,int death_flags,float delay_time);

//Applies a default death to an object
//Figures out what sort of death to do, then calls the other KillObject()
//Parameters:	objp - the object to destroy
//					killer - the object who is killing it, or NULL 
//					damage - how much damage was applied in the death blow?
void KillObject(object *objp,object *killer,float damage);

//Kills the player
//weapon_id can be -1 for no weapon
void KillPlayer(object *playerobj,object *killer,float damage_amount,int weapon_id);

// Shakes player by some random amount
void ShakePlayer ();

// Restores the player orientation matrix after shaking
void UnshakePlayer ();

//Break the specified (glass) face into shards
//Parameters:	rp, facenum - the face to break
//					hitpnt - the point on the face where the face shatters.  If NULL, uses center point of face
//					hitvec - the direction in which the thing that's breaking the glass is moving.  If NULL,
//						uses the negative of the surface normal
void BreakGlassFace(room *rp,int facenum,vector *hitpnt=NULL,vector *hitvec=NULL);

#endif