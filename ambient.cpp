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
 

#include <stdlib.h>
#include <string.h>

#include "ambient.h"

#include "hlsoundlib.h"

#include "room.h"
#include "game.h"
#include "psrand.h"

#define MAX_AMBIENT_SOUND_PATTERNS	100
asp Ambient_sound_patterns[MAX_AMBIENT_SOUND_PATTERNS];
int Num_ambient_sound_patterns=0;



#include "ddio.h"
#include "CFILE.H"
#include "soundload.h"
#include "descent.h"
#include "mem.h"

//Close down ambient sound system and free data
void FreeAmbientSoundData()
{
	for (int p=0;p<Num_ambient_sound_patterns;p++)
		if (Ambient_sound_patterns[p].num_sounds)
			mem_free(Ambient_sound_patterns[p].sounds);

	Num_ambient_sound_patterns = 0;
}

//Initialize the ambient sound system
void InitAmbientSoundSystem()
{
	atexit(FreeAmbientSoundData);

	ReadAmbientData();

	//Get rid of deleted patterns
	for (int p=0;p<Num_ambient_sound_patterns;p++) {

		asp *asp = &Ambient_sound_patterns[p];

		if (! asp->name[0]) {
			Ambient_sound_patterns[p] = Ambient_sound_patterns[Num_ambient_sound_patterns-1];
			Num_ambient_sound_patterns--;
		}
	}
}

//Return the index of a named ambient sound pattern
//Returns number, or -1 if can't find
int FindAmbientSoundPattern(char *aspname)
{
	if (! aspname[0])
		return -1;

	for (int i=0;i<Num_ambient_sound_patterns;i++)
		if (stricmp(Ambient_sound_patterns[i].name,aspname) == 0)
			return i;

	return -1;
}

//Returns a pointer to the name of the specified ambient sound pattern
char *AmbientSoundPatternName(int n)
{
	return Ambient_sound_patterns[n].name;
}

#define AMBIENT_FILE_ID			"ASPF"
#define AMBIENT_FILE_VERSION	0

//Reads data from the ambient sound data file
void ReadAmbientData()
{
	CFILE *ifile;
	char file_id[sizeof(AMBIENT_FILE_ID)];
	int version;

	//Get rid of any old data
	FreeAmbientSoundData();

	//Build filename
	ifile = cfopen(AMBIENT_FILE_NAME,"rb");

	if (!ifile) {
		Int3();
		return;
	}

	//Read file ID
	cf_ReadBytes((unsigned char *) file_id,strlen(AMBIENT_FILE_ID),ifile);
	if (strncmp(file_id,AMBIENT_FILE_ID,strlen(AMBIENT_FILE_ID)) != 0) {
		Int3();
		cfclose(ifile);
		return;
	}

	//Read version
	version = cf_ReadInt(ifile);

	if (version > AMBIENT_FILE_VERSION) {
		Int3();
		cfclose(ifile);
		return;
	}

	//Get the number of patterns
	Num_ambient_sound_patterns = cf_ReadInt(ifile);

	//Read the patterns
	for (int p=0;p<Num_ambient_sound_patterns;p++) {

		asp *asp = &Ambient_sound_patterns[p];

		cf_ReadString(asp->name,sizeof(asp->name),ifile);

		asp->min_delay = cf_ReadFloat(ifile);
		asp->max_delay = cf_ReadFloat(ifile);

		asp->num_sounds = cf_ReadInt(ifile);

		if (asp->num_sounds>0)
			asp->sounds = (ase *) mem_malloc(sizeof(*asp->sounds) * asp->num_sounds);
		else
			asp->sounds=NULL;

		int prob=0;
		for (int s=0;s<asp->num_sounds;s++) {
			char tbuf[PAGENAME_LEN];

			cf_ReadString(tbuf,sizeof(tbuf),ifile);
			asp->sounds[s].handle = FindSoundName(IGNORE_TABLE(tbuf));

			asp->sounds[s].min_volume = cf_ReadFloat(ifile);
			asp->sounds[s].max_volume = cf_ReadFloat(ifile);
			asp->sounds[s].probability = cf_ReadInt(ifile);

			prob += asp->sounds[s].probability;
		}

		if (asp->num_sounds && (prob != 100)) {
			Int3();
			asp->sounds[0].probability += 100 - prob;		//make it total 100
		}
	}

	cfclose(ifile);
}

#ifdef NEWEDITOR
extern char D3HogDir[_MAX_PATH*2];
#endif

//Writes data from the ambient sound data file
void WriteAmbientData()
{
	char filename[_MAX_PATH];
	CFILE *ofile;

#ifndef NEWEDITOR
	ddio_MakePath(filename,Base_directory,"data","misc",AMBIENT_FILE_NAME,NULL);
#else
	ddio_MakePath(filename,D3HogDir,"data","misc",AMBIENT_FILE_NAME,NULL);
#endif
	ofile = cfopen(filename,"wb");

	if (!ofile) {
		Int3();
		return;
	}

	//Write file ID & version
	cf_WriteBytes((ubyte *) AMBIENT_FILE_ID,strlen(AMBIENT_FILE_ID),ofile);
	cf_WriteInt(ofile,AMBIENT_FILE_VERSION);

	//Write the number of patterns
	cf_WriteInt(ofile,Num_ambient_sound_patterns);

	//Read the patterns
	for (int p=0;p<Num_ambient_sound_patterns;p++) {

		asp *asp = &Ambient_sound_patterns[p];

		cf_WriteString(ofile,asp->name);

		cf_WriteFloat(ofile,asp->min_delay);
		cf_WriteFloat(ofile,asp->max_delay);

		cf_WriteInt(ofile,asp->num_sounds);

		for (int s=0;s<asp->num_sounds;s++) {
			cf_WriteString(ofile,Sounds[asp->sounds[s].handle].name);

			cf_WriteFloat(ofile,asp->sounds[s].min_volume);
			cf_WriteFloat(ofile,asp->sounds[s].max_volume);
			cf_WriteInt(ofile,asp->sounds[s].probability);
		}
	}

	cfclose(ofile);
}

