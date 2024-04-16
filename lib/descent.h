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

#ifndef _DESCENT_H
#define _DESCENT_H

#include <stdlib.h>
#include "application.h"

// The name of this product
#ifdef DEMO
#define PRODUCT_NAME "Descent 3 Demo"
#else
#define PRODUCT_NAME "Descent 3"
#endif

// This is the port number assigned to "descent3" by the IANA (Internet Assigned Numbers Authority)
// Don't arbitrarily change this number!
#ifdef OEM
// The port used for the OEM version isn't a legitimate IANA port number
#define D3_DEFAULT_PORT 2092
#else
#define D3_DEFAULT_PORT 2092
#endif

class grScreen;
class oeApplication;
class oeAppDatabase;
class grViewport;

//	---------------------------------------------------------------------------
//	Constants and Types

typedef enum function_mode {
  INIT_MODE,
  GAME_MODE,
  RESTORE_GAME_MODE,
  EDITOR_MODE,
  EDITOR_GAME_MODE,
  MENU_MODE,
  QUIT_MODE,
  LOADDEMO_MODE,
  GAMEGAUGE_MODE,
  CREDITS_MODE
} function_mode;

extern bool Descent_overrided_intro;

// Maximum samples to save for gamegauge graph info
#define GAMEGAUGE_MAX_LOG 1000

// This is the default FOV
#define D3_DEFAULT_FOV 72.0
// This is the default zoom factor to be used for the game 3D view.
#define D3_DEFAULT_ZOOM 0.726f

// How long the a mission name can be
#define MSN_NAMELEN 32

// The "root" directory of the D3 file tree
extern char Base_directory[];

//	---------------------------------------------------------------------------
//	Globals

extern grScreen *Game_screen;                   // The Descent 3 screen.
extern oeApplication *Descent;                  // The Descent object
extern oeAppDatabase *Database;                 // The Database
extern char Descent3_temp_directory[_MAX_PATH]; // temp directory to put temp files
extern bool Katmai;                             // whether or not katmai is detected
//	---------------------------------------------------------------------------
//	Functions

#ifdef EDITOR
void WinMainInitEditor(unsigned hwnd, unsigned hinst);
#endif

//	Runs Descent III
void Descent3();

//	Runs the game, or editor
void MainLoop();

//	the defer handler
void D3DeferHandler(bool is_active);

//	Set and retrieve the current function mode of Descent 3
void SetFunctionMode(function_mode mode);
function_mode GetFunctionMode();

//	these functions create viewports from the game screen in a 'nice' C way
void CreateGameViewport(grViewport **vp);
void DestroyGameViewport(grViewport *vp);

// This function figures out whether or not a file needs to be loaded off of
// CD or off of the local drive. If it needs to come from a CD, it figures out
// which CD and prompts the user to enter that CD. If they hit cancel, it
// returns NULL.
char *GetMultiCDPath(char *file);
char *GetCDVolume(int cd_num);

inline void CREATE_VIEWPORT(grViewport **vp) { CreateGameViewport(vp); }

inline void DESTROY_VIEWPORT(grViewport *vp) { DestroyGameViewport(vp); }

inline void DELAY(float secs) { Descent->delay(secs); }

#ifndef RELEASE
//	this is called when you hit a debug break!
void D3DebugStopHandler();
void D3DebugResumeHandler();
#endif

#endif
