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
 

#ifndef GAMESEQUENCE_H
#define GAMESEQUENCE_H


//	gamesequencer states: 
//		game states

typedef enum tGameState 
{
	GAMESTATE_IDLE,					// no state
	GAMESTATE_NEW,						// starts a new game (with current mission.)
	GAMESTATE_LVLNEXT,				// go to the next level
	GAMESTATE_LVLSTART,				// happens when a level starts, game time starts here.
	GAMESTATE_LVLPLAYING,			// calls gameloop, polls for input.
	GAMESTATE_LOADGAME,				// a load game request has been issued.
	GAMESTATE_LVLEND,					// calls endlevel and any other endlevel stuff.
	GAMESTATE_LVLFAILED,				// a level was unsuccessfully ended
	GAMESTATE_LVLWARP,				// warp to a new level
	GAMESTATE_LOADDEMO,				// Load whatever demo was chosen in the UI
	GAMESTATE_GAMEGAUGEDEMO			// Play a gamegauge demo and exit
}
tGameState;


//	top level interfaces for game.
#define GAME_INTERFACE				0
#define GAME_OPTIONS_INTERFACE	1
#define GAME_PAUSE_INTERFACE		2
#define GAME_HELP_INTERFACE		3
#define GAME_BUDDY_INTERFACE		4
#define GAME_TELCOM_BRIEFINGS		5
#define GAME_TELCOM_AUTOMAP		6
#define GAME_TELCOM_CARGO			7
#define GAME_EXIT_CONFIRM			8
#define GAME_DLL_INTERFACE			9
#define GAME_SAVE_INTERFACE		10
#define GAME_LOAD_INTERFACE		11
#define GAME_TOGGLE_DEMO			12
#define GAME_POST_DEMO			13
#define GAME_DEMO_LOOP			14
#define GAME_LEVEL_WARP			15
#define GAME_DEBUGGRAPH_INTERFACE	16

//	variables
extern tGameState Game_state;
extern int Game_interface_mode;	// current interface mode of game (menu, game?)


//	functions
//	main sequencing code for game.  run this to execute a game.
//		before calling this function make sure that a 
//			mission has been loaded/initialized.
bool GameSequencer();

//Sets the current level for subsequent level loads, movies, or briefings
void SetCurrentLevel(int level);

//	loads and starts the specified leve. starts a new level (usually called internally)
bool LoadAndStartCurrentLevel();

//	creates a simple mission to play one level.
bool SimpleStartLevel(char *level_name);

//	sets and retrieves the current gamestate
inline void SetGameState(tGameState state) 
	{	Game_state = state; }

inline tGameState GetGameState() 
	{ return Game_state; }

#endif