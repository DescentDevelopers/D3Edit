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
 

#ifndef _AMBIENT_H
#define _AMBIENT_H

#include "manage.h"

//An Ambient Sound Element, one part of an Ambient Sound Pattern (ASP)
typedef struct {
	int	handle;							//the sample's handle
	float	min_volume,max_volume;		//minimum and maximum volume
	int	probability;					//between 0 and 100
} ase;

//An Ambient Sound Element, one part of an Ambient Sound Pattern (ASP)
typedef struct {
	char		name[PAGENAME_LEN];		//the name of this pattern
	float		min_delay,max_delay;		//delay time between sounds
	int		num_sounds;					//how many sounds in this pattern
	ase		*sounds;						//array of sounds
	float		delay;						//how long until the next sound
} asp;

extern int Num_ambient_sound_patterns;
extern asp Ambient_sound_patterns[];

#define AMBIENT_FILE_NAME "ambient.dat"
/*
$$TABLE_GENERIC "ambient.dat"
*/

//Initialize the ambient sound system
void InitAmbientSoundSystem();

//Does the ambient sound processing for one frame, maybe playing a sound or two
void DoAmbientSounds();

//Initializes the ambient sounds for the current level
void InitAmbientSounds();

//Return the index of a named ambient sound pattern
//Returns number, or -1 if can't find
int FindAmbientSoundPattern(char *aspname);

//Returns a pointer to the name of the specified ambient sound pattern
char *AmbientSoundPatternName(int n);

//Reads data from the ambient sound data file
void ReadAmbientData();

//Writes data from the ambient sound data file
void WriteAmbientData();

#endif