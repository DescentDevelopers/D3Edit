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
 

#ifndef __CONFIG_H__
#define __CONFIG_H__

//Main menu configuration functions
// ------------------------------------------------------
// ConfigForceFeedback
//	Purpose:
//	Configures your Force Feedback device on your computer
// ------------------------------------------------------
void ConfigForceFeedback(void);


// General option toggles
typedef struct tGameToggles
{
	bool show_reticle;
	bool guided_mainview;
	bool ship_noises;
}
tGameToggles;

extern tGameToggles Game_toggles;

// this list should match the list in config.cpp to work.
#ifdef MACINTOSH
	#define N_SUPPORTED_VIDRES 3
	
	#define RES_640X480		0
	#define RES_800X600		1
	#define RES_960X720		2
	#define RES_1024X768	3
#else
	#define N_SUPPORTED_VIDRES 8

	#define RES_512X384		0
	#define RES_640X480		1
	#define RES_800X600		2
	#define RES_960X720		3
	#define RES_1024X768		4
	#define RES_1280X960		5
	#define RES_1600X1200	6
#endif
// stored resolution list and desired game resolution
typedef struct tVideoResolution
{
	ushort width;
	ushort height;
}
tVideoResolution;

extern tVideoResolution Video_res_list[];
extern int Game_video_resolution;


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//KEEP THESE MEMBERS IN THE SAME ORDER, IF YOU ADD,REMOVE, OR CHANGE ANYTHING IN THIS STRUCT, MAKE SURE YOU
//UPDATE DetailPresetLow,DetailPresetMed,DetailPresetHigh AND DetailPresetVHi IN CONFIG.CPP
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
typedef struct tDetailSettings {
	float Terrain_render_distance;	//VisibleTerrainDistance
	float Pixel_error;				//PixelErrorTolerance
	bool Specular_lighting;			//DoSpecularPass
	bool Dynamic_lighting;			//Enable_dynamic_lighting
	bool Fast_headlight_on;
	bool Mirrored_surfaces;
	bool Fog_enabled;
	bool Coronas_enabled;
	bool Procedurals_enabled;
	bool Powerup_halos;
	bool Scorches_enabled;
	bool Weapon_coronas_enabled;
	bool Bumpmapping_enabled;
	ubyte Specular_mapping_type;
	ubyte Object_complexity;		//0 = low, 1 = medium, 2=high
} tDetailSettings;


// Call this with one of the above defines to set the detail level to a predefined set (custom level is ignored)
void ConfigSetDetailLevel(int level);
// returns the current detail level that the given tDetailSettings is at
int ConfigGetDetailLevel(tDetailSettings *ds);

#define DETAIL_LEVEL_LOW			0
#define DETAIL_LEVEL_MED			1
#define DETAIL_LEVEL_HIGH			2
#define DETAIL_LEVEL_VERY_HIGH	3
#define DETAIL_LEVEL_CUSTOM		4

extern tDetailSettings Detail_settings;
extern int Default_detail_level;

// displays new options menu
extern void OptionsMenu();
#endif