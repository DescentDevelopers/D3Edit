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

#ifndef TRIGGER_H
#define TRIGGER_H

#include "pstypes.h"
#include "ObjScript.h"
#include "vecmat.h"

// Trigger flags
#define TF_UNUSED 1                 //
#define TF_DISABLED 2               // This trigger is currently not active
#define TF_DEAD 4                   // This trigger has been tripped and is now dead
#define TF_ONESHOT 8                // This trigger only works once
#define TF_INFORM_ACTIVATE_TO_LG 16 // This trigger is involved in the level goal system

// Activator flags
#define AF_PLAYER 1        // The player can activate this trigger
#define AF_PLAYER_WEAPON 2 // The player's weapons can activate this trigger
#define AF_ROBOT 4         // A robot can activate this trigger
#define AF_ROBOT_WEAPON 8  // A robot's weapon can activate this trigger
#define AF_CLUTTER 16      // A piece of clutter

// Declare this here so we don't have to include the header file
//@$-struct tD3XThread;

typedef struct {
  int script_id;
  void *script_instance;
} tOSIRISTriggerScript;

#define TRIG_NAME_LEN 19

// The trigger structure
typedef struct trigger {
  char name[TRIG_NAME_LEN + 1]; // the name of this trigger
  int roomnum;                  // the room this trigger is in
  int facenum;                  // the face to which this trigger is attched
  short flags;                  // flags for this trigger
  short activator;              // flags for what can activate this trigger
  // This is allocated when the level is started
  tOSIRISTriggerScript osiris_script;
} trigger;

// The number of triggers currently in the mine
extern int Num_triggers;

// The list of triggers for the mine
extern trigger Triggers[];

// Macro to get trigger number
#define TRIGNUM(tp) (tp) ? ((tp)-Triggers) : -1

// Define this here so we don't have to include object.h
typedef struct object object;

//	initializes trigger system
void InitTriggers();

// Free triggers.
void FreeTriggers();

// types for CheckTrigger()
#define TT_PASS_THROUGH 0
#define TT_COLLIDE 1

// Called to see if a trigger was tripped
void CheckTrigger(int roomnum, int facenum, object *objp, int type);

// Enable or disable a trigger
void TriggerSetState(int trigger_num, bool enabled);

// Determines if a trigger is enabled or disabled
// Returns TRUE if enabled, else false
bool TriggerGetState(int trigger_num);

// Create a new trigger
// Parameters:	roomnum,facenum - where the trigger is
//					activator - activator mask
//					script - handle for the script for this trigger
// Returns:	trigger number of new trigger, or -1 if error
int AddTrigger(char *name, int roomnum, int facenum, int activator, const char *script);

// Remove a trigger
// Paramters:	trig_num - the trigger to delete
void DeleteTrigger(int trig_num);

// Remove a trigger
// Paramters:	roomnum,facenum - where the trigger is
void DeleteTrigger(int roomnum, int facenum);

#endif