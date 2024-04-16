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

#ifndef DEBUG_H
#define DEBUG_H
#include "pstypes.h"
//	---------------------------------------------------------------------------
//	Debug system is a member of the 'platform' library.
//	---------------------------------------------------------------------------
//	---------------------------------------------------------------------------
//	Constants
//	---------------------------------------------------------------------------
#ifndef IDOK
#define IDOK 1
#endif
#ifndef IDCANCEL
#define IDCANCEL 2
#endif
#ifndef IDABORT
#define IDABORT 3
#endif
#ifndef IDRETRY
#define IDRETRY 4
#endif
#ifndef IDIGNORE
#define IDIGNORE 5
#endif
#ifndef IDYES
#define IDYES 6
#endif
#ifndef IDNO
#define IDNO 7
#endif
//#define DEBUG_LEVEL 0		//DAJ
#if defined(WIN32) || defined(__LINUX__)
const int OSMBOX_OK = 1, OSMBOX_YESNO = 2, OSMBOX_YESNOCANCEL = 3, OSMBOX_ABORTRETRYIGNORE = 4, OSMBOX_OKCANCEL = 5;
#else
#define OSMBOX_OK 1
#define OSMBOX_YESNO 2
#define OSMBOX_YESNOCANCEL 3
#define OSMBOX_ABORTRETRYIGNORE 4
#define OSMBOX_OKCANCEL 5
#endif
//	---------------------------------------------------------------------------
//	Functions
//	---------------------------------------------------------------------------
extern bool Debug_break;
//	if we are running under a debugger, then pass true
bool Debug_Init(bool debugger, bool mono_debug);
// Does a messagebox with a stack dump
// Messagebox shows topstring, then stack dump, then bottomstring
// Return types are the same as the Windows return values
int Debug_ErrorBox(int type, const char *topstring, const char *title, const char *bottomstring);
// displays an message box
// Returns the same values as the Win32 MessageBox() function
int Debug_MessageBox(int type, const char *title, const char *str);
//	these functions deal with debug spew support
bool Debug_Logfile(const char *filename);
void Debug_LogWrite(const char *str);
bool Debug_ConsoleInit();
void Debug_ConsoleOpen(int n, int row, int col, int width, int height, char *title);
void Debug_ConsoleClose(int n);
void Debug_ConsolePrintf(int n, char *format, ...);
void Debug_ConsolePrintf(int n, int row, int col, char *format, ...);
void Debug_ConsoleRedirectMessages(int virtual_window, int physical_window);
//	DEBUGGING MACROS
// Break into the debugger, if this feature was enabled in Debug_init()
#if !defined(RELEASE)
#if defined(WIN32)
#define debug_break()                                                                                                  \
  do {                                                                                                                 \
    if (Debug_break)                                                                                                   \
      __asm int 3                                                                                                      \
  } while (0)
#elif defined(__LINUX__)
void ddio_InternalKeyClose();
//#define debug_break() do{__asm__ __volatile__ ( "int $3" );}while(0)
#define debug_break()                                                                                                  \
  do {                                                                                                                 \
    ddio_InternalKeyClose();                                                                                           \
    __asm__ __volatile__("int $3");                                                                                    \
  } while (0)
#elif defined(MACINTOSH)
#define debug_break()                                                                                                  \
  do {                                                                                                                 \
    if (Debug_break)                                                                                                   \
      Debugger();                                                                                                      \
  } while (0)
#else
#define debug_break()
#endif
#else
#define debug_break()
#endif
#if defined(WIN32)
// We forward declare PEXCEPTION_POINTERS so that the function
// prototype doesn't needlessly require windows.h.
typedef struct _EXCEPTION_POINTERS EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;
int __cdecl RecordExceptionInfo(PEXCEPTION_POINTERS data, const char *Message);
#endif
#endif