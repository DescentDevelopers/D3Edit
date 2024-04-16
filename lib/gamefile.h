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
 #ifndef GAMEFILE_H
#define GAMEFILE_H

#include "pstypes.h"
#include "manage.h"

#define MAX_GAMEFILES		1500

typedef struct
{
	char name[PAGENAME_LEN];
	char dir_name[PAGENAME_LEN];
	ubyte used;
} gamefile;


extern int Num_gamefiles;
extern gamefile Gamefiles[MAX_GAMEFILES];

// Sets all gamefiles to unused
void InitGamefiles ();

// Allocs a gamefile for use, returns -1 if error, else index on success
int AllocGamefile ();

// Frees gamefile index n
void FreeGamefile (int n);

// Gets next gamefile from n that has actually been alloced
int GetNextGamefile (int n);

// Gets previous gamefile from n that has actually been alloced
int GetPrevGamefile (int n);

// Searches thru all gamefile for a specific name, returns -1 if not found
// or index of gamefile with name
int FindGamefileName (char *name);


#endif


