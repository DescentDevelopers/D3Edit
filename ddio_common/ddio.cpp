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
 
#include "ddio.h"
#include "joystick.h"
#include "pserror.h"
#include <stdlib.h>
static bool DDIO_initialized = false;
// ----------------------------------------------------------------------------
//	Common initialization
// ----------------------------------------------------------------------------
//	Initializes DDIO system
bool ddio_Init(ddio_init_info *init_info)
{
	static bool first_time=true;
	bool res;
	ASSERT(!DDIO_initialized);
	if (first_time) {
		atexit(ddio_Close);
	}
	mprintf((0, "DDIO system initializing...\n"));
	res = ddio_InternalInit(init_info);
	if (res) {
		if (first_time) {				// initialize once and only once.
			timer_Init(0,init_info->use_lo_res_time);
		}
		if (!ddio_KeyInit(init_info)) 
			Error("Failed to initialize keyboard system.");
		ddio_MouseInit();
	}
	first_time = false;
	DDIO_initialized = true;
	joy_Init(init_info->joy_emulation);
	return res;
}
void ddio_Close()
{
	if (DDIO_initialized) {
		joy_Close();
		ddio_MouseClose();
		ddio_KeyClose();
		ddio_InternalClose();
		mprintf((0, "DDIO system closed.\n"));
		DDIO_initialized = false;
	}
}
void ddio_Suspend()
{
	ddio_InternalKeySuspend();
	ddio_InternalMouseSuspend();
#ifdef MACINTOSH
	ddio_InternalJoySuspend();		//DAJ make sprockets happy
#endif
}
void ddio_Resume()
{
	ddio_InternalKeyResume();
	ddio_InternalMouseResume();
#ifdef MACINTOSH
	ddio_InternalJoyResume();
#endif
}
// handles buffered input from devices once per frame.
void ddio_Frame()
{
	ddio_InternalKeyFrame();
	ddio_InternalMouseFrame();
	ddio_InternalJoyFrame();
}
