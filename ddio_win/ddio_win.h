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
 


#ifndef DDIO_WIN_H
#define DDIO_WIN_H

#include "pstypes.h"
#include "dinput.h"

class oeWin32Application;

typedef struct dinput_data {
	oeWin32Application *app;
	HWND hwnd;
	LPDIRECTINPUT lpdi;
	bool preemptive;
} dinput_data;

extern dinput_data DInputData;
extern bool DDIO_init;
extern bool DDIO_preemptive;


bool ddio_JoyHandler();
float ddio_TickToSeconds(unsigned long ticks);

#ifdef _DEBUG
void ddio_DebugMessage(unsigned err, char *fmt, ...);
#define DDIO_MESSAGE(_m) ddio_DebugMessage _m
#else
#define DDIO_MESSAGE(_m)
#endif

#define MAKE_DDIO_TIME(_ms) ddio_TickToSeconds(_ms)


//	hook in timer function at certain period.  returns a handle to this function
DWORD timer_HookFunction(void (CALLBACK *fncptr)(UINT, UINT, DWORD, DWORD, DWORD), UINT period);

//	clears function from hook list specified by a handle returned from HookFunction
void timer_ReleaseFunction(DWORD func);


#endif