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

#ifndef DOOR_H
#define DOOR_H

#ifdef NEWEDITOR /* only include tablefile header (manage stuff for NEWEDITOR) */
#include "..\neweditor\ned_TableFile.h"
#include "..\neweditor\ned_Door.h"
#include "pstypes.h"
#include "object.h"
#else

#include "pstypes.h"
#include "manage.h"
#include "object.h"

// IMPORTANT!!!!!!!!!!!
// "Doors" refers to a predefined door that is in memory
// "Doorways" are specific doors that are in the mine
// So, there can be several Doorways that all point to the same Door
// Get it?  If not, talk to Samir or Jason

// Door flags

#define DF_BLASTABLE 1  // this door can be destroyed
#define DF_SEETHROUGH 2 // this door can be seen through even when closed

//	DOOR STRUCTURES

typedef struct {
  char name[PAGENAME_LEN]; // name of the door
  ubyte used;              // if this door is in use
  ubyte flags;             // flags for this door
  ubyte pad;               // keep alignment (pagename is 35 chars long)
  short hit_points;        // for blastable doors
  float total_open_time;   // time of animation to open door
  float total_close_time;  // time of animation to close door
  float total_time_open;   // how much time to stay open
  int model_handle;        // an index into the polymodels array
  int open_sound;          // sound to play when closing
  int close_sound;         // sound to play when closing

  // OSIRIS information
  char module_name[MAX_MODULENAME_LEN];

} door;

// The max number of predefined doors
#define MAX_DOORS 60
extern int Num_doors; // number of actual doors in game.
extern door Doors[];

// Sets all doors to unused
void InitDoors();

// Allocs a door for use, returns -1 if error, else index on success
int AllocDoor();

// Frees door index n
void FreeDoor(int n);

// Gets next door from n that has actually been alloced
int GetNextDoor(int n);
// Gets previous door from n that has actually been alloced
int GetPrevDoor(int n);
// Searches thru all doors for a specific name, returns -1 if not found
// or index of door with name
int FindDoorName(char *name);

// Given a filename, loads the model found in that file
int LoadDoorImage(char *filename, int pageable = 1);
// Given a door handle, returns an index to that doors model
int GetDoorImage(int handle);

//	Remaps the doors
void RemapDoors();

#endif

#endif