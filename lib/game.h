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
 


#ifndef _GAME_H
#define _GAME_H

#include "pserror.h"
#include "renderer.h"
#include "object.h"

//	return 0 if we wan't to return to the menu, or return 1 if everything
//	is okay. starts a new game based off the current mission.
void PlayGame(void);

//	meant for 'instant' action	(usually run from editor, but...)
void QuickPlayGame();

float GetFPS ();

//Stop the Frame_time clock
void StopTime(void);

//Restart the Frame_time clock
void StartTime(void);

//Compute how long last frame took
void CalcFrameTime(void);

//	Initialize frame timer
void InitFrameTime(void);


//Sets screen mode
const int	SM_NULL			= 0,
				SM_GAME			= 1,
				SM_MENU			= 2,
				SM_CINEMATIC	= 3;

void SetScreenMode(int sm, bool force_res_change=false);
int GetScreenMode();

//	ALWAYS CALL THESE TO START AND END RENDERING
void StartFrame(bool clear=true);
void StartFrame(int x, int y, int x2, int y2, bool clear=true,bool push_on_stack=true);
void EndFrame();

// retrives the settings of the last call to StartFrame
// returns false if it's not currently in between a StartFrame/EndFrame block
bool GetFrameParameters(int *x1,int *y1,int *x2,int *y2);

//	call this to set the game mode
void SetGameMode(int mode);

//How long (in seconds) the last frame took
extern float Frametime;

//How long (in seconds) since the game started
extern float Gametime;

//	set this to clear the screen X number of times.
extern int Clear_screen;

//How many frames have been renered.
//NOTE: this is a count of 3d frames, not game frames
extern int FrameCount;

//Vars for game 3D window
extern int Game_window_x,Game_window_y,Game_window_w,Game_window_h;
extern int Max_window_w,Max_window_h;

extern int Game_mode;
extern int Difficulty_level;

extern int sound_override_force_field;
extern int sound_override_glass_breaking;

#define MAX_FORCE_FIELD_BOUNCE_TEXTURES 3
extern int   force_field_bounce_texture[MAX_FORCE_FIELD_BOUNCE_TEXTURES];
extern float force_field_bounce_multiplier[MAX_FORCE_FIELD_BOUNCE_TEXTURES];

extern bool Level_powerups_ignore_wind;

#ifdef _DEBUG
extern int Game_show_sphere;
extern int Game_show_portal_vis_pnts;
extern int Game_update_attach;
extern int Game_do_walking_sim;
extern int Game_do_vis_sim;
extern int Game_do_flying_sim;
extern int Game_do_ai_movement;
extern int Game_do_ai_vis;
#endif

extern bool UseHardware;
extern renderer_type PreferredRenderer;
// State variables for our renderer
extern rendering_state Render_state;
extern renderer_preferred_state Render_preferred_state;

#define GM_SINGLE		1								// Single player game.
//#define GM_SERIAL	2								// You are in serial mode (Jason doesn't like this.)
#define GM_NETWORK	4								// You are in network mode
#define GM_MODEM		32								// You are in a modem (serial) game

#define GM_GAME_OVER	128							// Game has been finished

#define GM_NONE		0								// You are not in any mode, kind of dangerous...
#define GM_NORMAL		1								// You are in normal play mode, no multiplayer stuff
#define GM_MULTI		(GM_NETWORK + GM_MODEM)	// You are in some type of multiplayer game

/*
struct trigger;
struct tD3XThread;
struct tD3XProgram;
*/

typedef struct gamemode {
	char scriptname[64];
	int requested_num_teams;
/*
	tD3XProgram *d3xmod;
	tD3XThread *d3xthread;
	int objmehandle;
	int objithandle;
	trigger *trigme;
	trigger *trigit;
*/
}
gamemode;

//Structure for a terrain sound "band"
typedef struct {
	int	sound_index;					//the sound to play
	ubyte	low_alt,high_alt;				//top & bottom of range of sound
	float	low_volume,high_volume;		//volume at top & bottom of range
} terrain_sound_band;

//How many terrain sound bands we have
#define NUM_TERRAIN_SOUND_BANDS	5

//The terrain sound bands for the current level
extern terrain_sound_band Terrain_sound_bands[];

//Clear out all the terrain sound bands
void ClearTerrainSound();

//Starts the sound on the terrain
void StartTerrainSound();

//Missile camera.  If disabled, this is -1.  Otherwise, it's a window number (see SmallViews.h).
extern int Missile_camera_window;

//	contains all relevent information for gamemode pertaining to d3x system.
extern gamemode Gamemode_info;

//Starts the game-engine "cutscene"
//Puts the player in AI mode, sets the view to an external camera, switches to letterbox, & puts the player on a path
//Parameters:	camera - the camera for the view
//					pathnum - the path the player should follow
//					time - if > 0.0, how long the sequence plays before the level ends
void StartEndlevelSequence(object *camera,int pathnum,float time);


inline void ResetGamemode() 
{
	Gamemode_info.scriptname[0] = 0;
	Gamemode_info.requested_num_teams = 1;
	/*
	Gamemode_info.objmehandle = 0;
	Gamemode_info.objithandle = 0;
	Gamemode_info.trigme = 0;
	Gamemode_info.trigit = 0;
	*/
}

void SetGamemodeScript(const char *scrfilename,int num_requested_teams=-1);

// Does a screenshot and tells the bitmap lib to save out the picture as a tga
void DoScreenshot ();

#endif
