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
 


#ifndef __GAMECINEMATICS_EXTERNAL_H_
#define __GAMECINEMATICS_EXTERNAL_H_

#ifdef MACINTOSH
#include "vecmat_external.h"
#include "manage_external.h"
#else
#include "lib/vecmat_external.h"
#include "lib/manage_external.h"
#endif


/*
==========================================================
		Canned Cinematics
*/
#define CANNED_LEVEL_INTRO		1
#define CANNED_LEVEL_END_PATH	2	//end level with camera on path
#define CANNED_LEVEL_END_POINT	3	//end level with camera on point
#define CANNED_MOVE_PLAYER_FADE	4	//fade the screen out and move the player to a new position
#define CANNED_LEVEL_END_FADE_WHITE 5	//fade the screen to white and end level

typedef struct
{
	int type;
	/*
	CANNED_LEVEL_INTRO:
		camera_pathid
		target_pathid
		text_to_display
		time
	*/
	/*
	CANNED_LEVEL_END_PATH
		camera_pathid
		target_pathid
		text_to_display
		time
	*/
	/*
	CANNED_LEVEL_END_POINT
		object_to_use_for_point
		target_pathid
		text_to_display
		time
	*/
	/*
	CANNED_MOVE_PLAYER_FADE
		room	//destination room
		pos		//destination pos
		orient	//destination orient
		target_objhandle	//the player
	*/
	/*
	CANNED_LEVEL_END_FADE_WHITE
		time
		text_to_display
	*/

	int camera_pathid;
	int target_pathid;
	char *text_to_display;

	int target_objhandle;

	int room;

	float time;

	int object_to_use_for_point;

	vector pos;
	matrix orient;
	
}tCannedCinematicInfo ;

//========================================================


// flags for game cinematic struct
#define GCF_LETTERBOX		0x00000000
#define GCF_FULLSCREEN		0x00000001
#define GCF_SCREENFORMAT	0x00000001	//mask for screen format to use

#define GCF_USEPATH			0x00000000
#define GCF_USEPOINT		0x00000002
#define GCF_CAMERAPLACEMENT	0x00000002	//mask for camera placement (use path or point)

#define GCF_TEXT_WIPEIN		0x00000004	
#define GCF_TEXT_FADEINOUT	0x00000008
#define GCF_TEXT_NOEFFECT	0x00000000
#define GCF_TEXT_MASK		0x0000000C	//mask for text modes

#define GCF_LAYOUT_BOTTOM	0x00000000	
#define GCF_LAYOUT_TOP		0x00000010
#define GCF_LAYOUT_MIDDLE	0x00000020
#define GCF_LAYOUT_LOW		0x00000040
#define GCF_LAYOUT_MASK		0x00000070	//mask for text layout to use

#define GCF_STOPIFTAGETDEAD	0x00000100	//stop the cinematic if the target dies
#define GCF_FORCETARGETTOEND 0x00000200	//if there is a quick exit (by keypress) force target position to the end of the path
#define GCF_DONTRESTOREVIEWER	0x00000400	//don't restore the view back to the player (this is really an internal flag and shouldn't be used)
#define GCF_IGNOREPLAYERDEAD	0x00000800	//don't stop cinematic if player dies
#define GCF_DOTRANSBEFORETEXT	0x00001000	//process end transitions before drawing text

// callback types
#define GCCT_START			0x00000001	//first frame of the movie
#define GCCT_STOP			0x00000002	//last frame of the movie
#define GCCT_FRAME			0x00000003	//frame of the movie

// Transition types
#define GCTT_NONE		0
#define GCTT_WACKY		1
#define GCTT_FADE		2
#define GCTT_FADEINOUT	3
#define GCTT_FADEWHITE	4

typedef struct
{
	float min,max; //0.0f->1.0f
}PercentageRange;

typedef struct
{
	unsigned int flags;
	
	int target_objhandle;

	int end_transition;
	int start_transition;

	// the name of the path or the position that the camera should be at
	int pathid;
	vector position;
	matrix *orient;
	int room;

	// the total time that the cinematic should play
	float max_time_play;

	//called every frame while the cinematic is processing
	void (*callback)(int type);

	//ranges (based on max_time_play)
	PercentageRange text_display;		// range that the text should be displayed
	PercentageRange track_target;		// range that the camera should track the target
	PercentageRange player_disabled;	// range that the player can't move/fire/etc.
	PercentageRange in_camera_view;		// range that the view is from the camera
	PercentageRange quick_exit;			// range where a key-press will quick exit cinematic

}tGameCinematic;


#endif