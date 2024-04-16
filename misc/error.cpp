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
 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "mono.h"
#include "pserror.h"
#include "pstring.h"
#include "debug.h"
#include "application.h"

#define MAX_MSG_LEN 2000


void Default_dbgbrk_callback();

//	Debug break chain handlers
void (*DebugBreak_callback_stop)() = NULL;
void (*DebugBreak_callback_resume)() = NULL;

//	library initialized flag
static bool Error_initialized = false;

//	message that is printed out when error occurs
static char Exit_message[MAX_MSG_LEN];
static char App_title[32];
static char Exit_title_str[64];

//	error message output function
void error_Spew();


//////////////////////////////////////////////////////////////////////////////

//	initializes error handler.
bool error_Init(bool debugger, bool mono_debug, const char *app_title)
{
	Debug_Init(debugger, mono_debug);

	Error_initialized = true;
	Exit_message[0] = 0;

	strncpy(App_title, app_title, sizeof(App_title)-1);
	App_title[sizeof(App_title)-1] = 0;

	strncpy(Exit_title_str, app_title, sizeof(Exit_title_str)-1);
	Exit_title_str[sizeof(Exit_title_str)-1] = 0;

	atexit(error_Spew);

	return true;
}

//	exits the application and prints out a standard error message
void Error(char *fmt,...)
{
	va_list arglist;

	strcpy(Exit_message,"Error: ");
	
	va_start(arglist,fmt);
	int exit_msg_len = strlen(Exit_message);
	Pvsprintf(Exit_message+exit_msg_len,MAX_MSG_LEN-exit_msg_len,fmt,arglist);
	va_end(arglist);

	sprintf(Exit_title_str,"%s Error",App_title);

	mprintf ((0,"%s\n",Exit_message));

#ifdef _DEBUG
	int answer;

	if (DebugBreak_callback_stop)
		(*DebugBreak_callback_stop)();

	if (Debug_break)
		answer = Debug_ErrorBox(OSMBOX_ABORTRETRYIGNORE,Exit_title_str,Exit_message,"Press RETRY to debug.");
	else
		answer = Debug_ErrorBox(OSMBOX_OKCANCEL,Exit_title_str,Exit_message,"Press OK to exit, CANCEL to ignore this error and continue.");

	switch (answer) {
		case IDRETRY:
			debug_break();		//Step Out of this function to see where Error() was called
			//fall into ignore/cancel case
		case IDIGNORE:
		case IDCANCEL:
			if (DebugBreak_callback_resume)
				(*DebugBreak_callback_resume)();
			return;
		case IDOK:
		case IDABORT:
			break;		//do nothing, and exit below
	}

	//Clear the message, since we don't need to see it again when we exit
	Exit_message[0] = 0;

#else
	if (!Error_initialized) 
		error_Spew();
#endif

	//Clear the DEBUG_BREAK() callbacks
	SetDebugBreakHandlers(NULL,NULL);

	//Leave the program
	exit(0);
}




//Brings up an error message for an int3
void Int3MessageBox(char *file,int line)
{
#ifndef RELEASE
	char title[128],message[500];
	int answer;

	sprintf(title,"%s Debug Break",App_title);
	sprintf(message,"Int3 in %s at line %d.",file,line);

	if (DebugBreak_callback_stop)
		(*DebugBreak_callback_stop)();

	answer = Debug_ErrorBox(OSMBOX_YESNO,title,message,"It's probably safe to continue.  Continue?");

	if (answer == IDNO) {
		SetDebugBreakHandlers(NULL,NULL);
		exit(1);
	}

	if (DebugBreak_callback_resume)
		(*DebugBreak_callback_resume)();
#endif
}

//	prints out an assertion error
void AssertionFailed(char *expstr, char *file, int line)
{
#ifndef RELEASE
	char title[128],message[500];
	int answer;

	sprintf(title,"%s Assertion Failed",App_title);
	sprintf(message, "Assertion failed: (%s)\n\nFile %s at line %d.", expstr, file, line);

	if (DebugBreak_callback_stop)
		(*DebugBreak_callback_stop)();

	answer = Debug_ErrorBox(OSMBOX_YESNO,title,message,"Continue?");

	if (answer == IDNO) {
		SetDebugBreakHandlers(NULL,NULL);
		exit(1);
	}

	if (DebugBreak_callback_resume)
		(*DebugBreak_callback_resume)();
#endif		//#ifndef RELEASE
}

//	error message output function
void error_Spew()
{
 	if (Exit_message[0]) 
		Debug_MessageBox(OSMBOX_OK,Exit_title_str,Exit_message);
}


//////////////////////////////////////////////////////////////////////////////
//	MESSAGE BOX SYSTEM

char Messagebox_title[80]="Message";

// Sets the title for future OutrageMessageBox() dialogs
void SetMessageBoxTitle(char *title)
{
	strncpy(Messagebox_title,title,sizeof(Messagebox_title));
}

#define BUF_LEN 1024

// Pops up a dialog box to display a message
void OutrageMessageBox(char *str, ...) 
{
	char buf[BUF_LEN];
	va_list arglist;
	int nchars;

	va_start(arglist, str);
		nchars = Pvsprintf(buf, BUF_LEN,str, arglist);
	va_end(arglist);

	if (nchars >= BUF_LEN)
		Debug_MessageBox(OSMBOX_OK, Messagebox_title, "The dialog that follows this one overflowed its text buffer.  The program may crash.");	

	Debug_MessageBox(OSMBOX_OK, Messagebox_title, buf);	

}


int OutrageMessageBox(int type, char *str, ...)
{
	char buf[BUF_LEN];
	va_list arglist;
	int os_flags;
	int nchars;

	va_start(arglist, str);
	nchars = Pvsprintf(buf, BUF_LEN,str, arglist);
	va_end(arglist);
	
	if (type == MBOX_OK) 
		os_flags = OSMBOX_OK;
	else if (type == MBOX_YESNO) 
		os_flags = OSMBOX_YESNO;
	else if (type == MBOX_YESNOCANCEL) 
		os_flags = OSMBOX_YESNOCANCEL;
	else if (type == MBOX_ABORTRETRYIGNORE) 
		os_flags = OSMBOX_ABORTRETRYIGNORE;
	else
		Int3();

	if (nchars >= BUF_LEN)
		Debug_MessageBox(OSMBOX_OK, Messagebox_title, "The dialog that follows this one overflowed its text buffer.  The program may crash.");	

	return Debug_MessageBox(os_flags, Messagebox_title, buf);
}



