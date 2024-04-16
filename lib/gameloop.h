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
 


#include "grdefs.h"
#include "object.h"

//Do all game functions for one frame: render, move objects, etc.
void GameFrame(void);

//Render the world into a game window
//Parameters:	viewer - if not null, this object disabled from rendering.  Not used otherwise.
//					viewer_eye - where we're rendering from
//					viewer_roomnum - the roomnum viewer_eye is in
//					viewer_orient - the oriention for this view
//					zoom - the zoom for this view
//					rear_view - if true, we're looking out the rear of this object
void GameRenderWorld(object *viewer,vector *viewer_eye,int viewer_roomnum,matrix *viewer_orient,float zoom,bool rear_view);

extern float Render_zoom;
extern float Render_FOV;

extern bool Game_paused;							//	determines if game is paused.

extern bool Rendering_main_view;					// determines if we're rendering the main view
extern bool Skip_render_game_frame;				// skips rendering the game frame if set.


//Turn off all camera views
//If total reset is true, set all views to none, otherwise kill object view but keep rear views.
void InitCameraViews(bool total_reset);

//Pauses game
void PauseGame();

//	resumes game operation.
void ResumeGame();

#ifdef _DEBUG
//	initializes test systems.
void InitTestSystems();
#endif


