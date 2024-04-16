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
 

#ifndef DOORWAY_H
#define DOORWAY_H

#include "pstypes.h"

// IMPORTANT!!!!!!!!!!!
// "Doors" refers to a predefined door that is in memory
// "Doorways" are specific doors that are in the mine
// So, there can be several Doorways that all point to the same Door
// Get it?  If not, talk to Samir or Jason

//	doorway state
#define DOORWAY_STOPPED			0	// door is not moving
#define DOORWAY_OPENING			1	// door is opening
#define DOORWAY_CLOSING			2	// door is closing
#define DOORWAY_WAITING			3	// door is waiting to be closed
#define DOORWAY_OPENING_AUTO	4	// door is opening and will automatically close

//	doorway flags
#define DF_BLASTED				1	// it's been blasted away
#define DF_AUTO					2	// doorway closes after time.
#define DF_LOCKED					4	// doorway can't open for now
#define DF_KEY_ONLY_ONE			8	// only one key is needed to open (not all keys)
#define DF_GB_IGNORE_LOCKED	16	// the Guide-bot ignores the locked state of this door

//	keymasks
#define KF_KEY1					1	// Each key is a bit in the key_mask set in the door/object
#define KF_KEY2					2
#define KF_KEY3					4	
#define KF_KEY4					8

#define MAX_ACTIVE_DOORWAYS	30		

extern int Num_active_doorways;				// number of active doors in game
extern int Active_doorways[MAX_ACTIVE_DOORWAYS];

//A doorway (room) in the mine
typedef struct doorway {
	int	doornum;					// door type of this doorway
	ubyte state;					// current state of doorway
	ubyte flags;					// flags associated with a doorway
	ubyte keys_needed;			// used by trigger system.  these bits need to be set to activate door
	sbyte	activenum;				// index into active doorways array, or -1 if not active
	float position;	 			// current position of door
	float	dest_pos; 				// destination position
	int	sound_handle;			// handle of last sound played
} doorway;							

//	Macros

//returns the bitflag for the given key number
#define KEY_FLAG(keynum)	(1 << (keynum-1))

//	Variables

//This is a mask of all keys held by all players. Robots use this to determine if a door is openable.
extern int Global_keys;

//
//	Editor Functions
//

//Define a couple types
struct room;
struct object;

// Adds a doorway to the specified room
// Returns a pointer to the doorway struct
doorway *DoorwayAdd(room *rp,int doornum);

//Updates the animation when the door position is changed
void DoorwayUpdateAnimation(room *rp);

//
// General Functions
//

//	executes all active doorways in the game
void DoorwayDoFrame();

//	clears the active state of all doorways that are active back to closed
void DoorwayDeactivateAll();

//Opens a door and, if it has the auto flag set, closes it
//Does not check to see if the door is openable -- the caller must do that.
void DoorwayActivate(int door_obj_handle);

//Stops the doorway if it's moving
void DoorwayStop(int door_obj_handle);

// Locks a given doorway
void DoorwayLockUnlock(int door_obj_handle,bool state);

//Sets the current position of the door.  0.0 = totally closed, 1.0 = totally open
//Does not check to see if the door is openable -- the caller must do that.
void DoorwaySetPosition(int door_obj_handle,float pos);

//Called after loading a saved game to rebuild the active list
void DoorwayRebuildActiveList();

//Called when a door is blown up
void DoorwayDestroy(object *objp);

//
// Query Functions
//

// Returns true if the doorway is locked, else false
bool DoorwayLocked(int door_obj_handle);

// Returns true if the doorway is locked, else false
bool DoorwayLocked(room *rp);

// Returns true if the doorway is openable by the specified player, else false
bool DoorwayOpenable(int door_obj_handle,int opener_handle);

//Returns the current state of the specified door
int DoorwayState(int door_obj_handle);

//Returns the current position of the door.  0.0 = totally closed, 1.0 = totally open
float DoorwayPosition(room *rp);

//Returns the current position of the door.  0.0 = totally closed, 1.0 = totally open
float DoorwayPosition(int door_obj_handle);

//Make old name work
#define DoorwayGetPosition DoorwayPosition

#endif
