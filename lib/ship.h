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
 

#ifndef SHIP_H
#define SHIP_H

#include "pstypes.h"
#include "manage.h"
#include "object.h"
#include "robotfirestruct.h"
#include "player.h"

#define MAX_SHIPS				5

//#ifdef DEMO //Demo2 will use GL
//#define DEFAULT_SHIP "Pyro-SE"
//#else
#define DEFAULT_SHIP "Pyro-GL"
//#endif

// Ship fire flags
#define SFF_FUSION	1		// fires like fusion
#define SFF_ZOOM		4		// Zooms in
#define SFF_TENTHS	8		// Ammo displays in tenths

// Default ship IDs
#define SHIP_PYRO_ID	0
#define SHIP_PHOENIX_ID	1
#define SHIP_MAGNUM_ID	2

#define MAX_DEFAULT_SHIPS	3

// Ship flags
#define SF_DEFAULT_ALLOW	1	//Allowed by default

typedef struct
{
	char name[PAGENAME_LEN];
	float size;
	physics_info	phys_info;		//the physics data for this obj type.
	int model_handle;					//  a polygon model
	int dying_model_handle;			// Dying polygon model

	int	med_render_handle;	//handle for med res version of this object
	int	lo_render_handle;		//handle for lo res version of this object   

	float med_lod_distance;
	float lo_lod_distance;

	otype_wb_info static_wb[MAX_PLAYER_WEAPONS];
	ubyte fire_flags[MAX_PLAYER_WEAPONS];		// how a particular weapon fires
	int	max_ammo[MAX_PLAYER_WEAPONS];

	int	firing_sound[MAX_PLAYER_WEAPONS];			//sound the weapon makes while button held down
	int	firing_release_sound[MAX_PLAYER_WEAPONS];	//sound the weapon makes when the button is released

	int	spew_powerup[MAX_PLAYER_WEAPONS];	//which powerup to spew for each weapon

	char cockpit_name[PAGENAME_LEN];		// name of cockpit.inf file 
	char hud_config_name[PAGENAME_LEN];	// name of hud configuration file

	float armor_scalar;

	int flags;
	ubyte used;
} ship;


extern int Num_ships;
extern ship Ships[MAX_SHIPS];

extern char *AllowedShips[];

// Sets all ships to unused
void InitShips ();

// Allocs a ship for use, returns -1 if error, else index on success
int AllocShip ();

// Frees ship index n
void FreeShip (int n);

// Gets next ship from n that has actually been alloced
int GetNextShip (int n);

// Gets previous ship from n that has actually been alloced
int GetPrevShip (int n);

// Searches thru all ships for a specific name, returns -1 if not found
// or index of ship with name
int FindShipName (char *name);

// Given a filename, loads either the model or vclip found in that file.  If type
// is not NULL, sets it to 1 if file is model, otherwise sets it to zero
int LoadShipImage (char *filename);

// Given a ship handle, returns that ships image for framenum
int GetShipImage (int handle);

// This is a very confusing function.  It takes all the ships that we have loaded 
// and remaps then into their proper places (if they are static). 
void RemapShips ();

// goes thru every entity that could possible have a ship index (ie objects, ships, etc)
// and changes the old index to the new index
void RemapAllShipObjects (int old_index,int new_index);



#endif


