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
#ifndef SOUNDLOAD_H_
#define SOUNDLOAD_H_

#include "ssl_lib.h"

extern int Num_sounds;
extern int Num_sound_files;

// Allocs a sound file for use, returns -1 if error, else index on success
int AllocSoundFile();

// Frees sound index n
void FreeSoundFile(int n);

// Gets next sound file from n that has actually been alloced
int GetNextSoundFile(int n);

// Gets previous sound file from n that has actually been alloced
int GetPrevSoundFile(int n);

// Searches thru all sounds for a specific name, returns -1 if not found
// or index of sound with name
int FindSoundFileName(char *name);

// Given a filename, loads the sound file.
int LoadSoundFile(char *filename, float import_volume, bool f_get_data = false);

// Sets all sounds to unused
void InitSounds();

// Allocs a sound for use, returns -1 if error, else index on success
int AllocSound();

// Frees sound index n
void FreeSound(int n);

// Gets next sound from n that has actually been alloced
int GetNextSound(int n);

// Gets previous sound from n that has actually been alloced
int GetPrevSound(int n);

// Searches thru all sounds for a specific name, returns -1 if not found
// or index of sound with name
int FindSoundName(char *name);

// Given a filename, loads the sound.
int LoadSound(char *filename);

// This is a very confusing function.  It takes all the sounds that we have loaded
// and remaps then into their proper places (if they are static).
void RemapSounds();

// goes thru every entity that could possible have a sound index (ie objects, robots, etc)
// and changes the old index to the new index
void RemapAllSoundObjects(int old_index, int new_index);

#endif