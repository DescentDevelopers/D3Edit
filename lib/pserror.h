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

#ifndef PSERROR_H
#define PSERROR_H
#include <assert.h>
#include "debug.h"
#include "mono.h"
//	initializes error handler.
bool error_Init(bool debugger, bool mono_debug, const char *app_title);
//	exits the application and prints out a standard error message
void Error(char *fmt, ...);
//	prints out an assertion error
void AssertionFailed(char *expstr, char *file, int line);
// Brings up an error message for an int3
void Int3MessageBox(char *file, int line);
//	Message box functions
#define MBOX_OK 1
#define MBOX_YESNO 2
#define MBOX_YESNOCANCEL 3
#define MBOX_ABORTRETRYIGNORE 4
#ifndef RELEASE
//	prints out a standard OS messagebox
void OutrageMessageBox(char *str, ...);
int OutrageMessageBox(int type, char *str, ...);
#endif
// Sets the title for future OutrageMessageBox() dialogs
void SetMessageBoxTitle(char *title);
// Write a block of text to the system clipboard
void DumpTextToClipboard(char *text);
//////////////////////////////////////////////////////////////////////////////
//	development debugging functions
//	adds a function to be called when a debug break occurs.
//	undefine any ASSERT macro previously defined.
#ifdef ASSERT
#undef ASSERT
#endif
//	this callback is invoked when a DEBUG_BREAK macro is used.
//		arguments
//			style = 1 if ASSERT
//					= 0 if Int3 debugger break.
extern void (*DebugBreak_callback_stop)();
extern void (*DebugBreak_callback_resume)();
//	set DEBUG_BREAK callback
inline void SetDebugBreakHandlers(void (*stop)(), void (*resume)()) {
  DebugBreak_callback_stop = stop;
  DebugBreak_callback_resume = resume;
}
// DEBUG_BREAK()
// Calls the debug_break() macro surrounded by calls to the debug callbacks (to turn off & on graphics)
// ASSERT()
// Like the standard C assert(), but if the condition failed and debugging on,
// does a DEBUG_BREAK().  If debugging on, brings up a dialog.
// Int3()
// Does a DEBUG_BREAK() if debugging is turned on.  Also does an mprintf().
//	Define the macros
#ifndef RELEASE
#ifdef MACINTOSH
#include "malloc.h"
#else
#include <malloc.h>
#endif
#if defined(WIN32)
#define DEBUG_BREAK()                                                                                                  \
  do {                                                                                                                 \
    if (DebugBreak_callback_stop)                                                                                      \
      (*DebugBreak_callback_stop)();                                                                                   \
    debug_break();                                                                                                     \
    if (DebugBreak_callback_resume)                                                                                    \
      (*DebugBreak_callback_resume)();                                                                                 \
  } while (0)
#define ASSERT(x)                                                                                                      \
  do {                                                                                                                 \
    if (!(unsigned)(x)) {                                                                                              \
      mprintf((0, "Assertion failed (%s) in %s line %d.\n", #x, __FILE__, __LINE__));                                  \
      if (Debug_break)                                                                                                 \
        DEBUG_BREAK();                                                                                                 \
      else                                                                                                             \
        AssertionFailed(#x, __FILE__, __LINE__);                                                                       \
    }                                                                                                                  \
  } while (0)
#define Int3()                                                                                                         \
  do {                                                                                                                 \
    mprintf((0, "Int3 at %s line %d.\n", __FILE__, __LINE__));                                                         \
    if (Debug_break)                                                                                                   \
      DEBUG_BREAK();                                                                                                   \
    else                                                                                                               \
      Int3MessageBox(__FILE__, __LINE__);                                                                              \
  } while (0)
#define HEAPCHECK()                                                                                                    \
  do {                                                                                                                 \
    if (_heapchk() != _HEAPOK)                                                                                         \
      Int3();                                                                                                          \
  } while (0)
#elif defined(LINUX)
// For some reason Linux doesn't like the \ continuation character, so I have to uglify this
#define DEBUG_BREAK()                                                                                                  \
  do {                                                                                                                 \
    if (DebugBreak_callback_stop)                                                                                      \
      (*DebugBreak_callback_stop)();                                                                                   \
    debug_break();                                                                                                     \
    if (DebugBreak_callback_resume)                                                                                    \
      (*DebugBreak_callback_resume)();                                                                                 \
  } while (0)
#define ASSERT(x)                                                                                                      \
  do {                                                                                                                 \
    if (!(unsigned)(x)) {                                                                                              \
      mprintf((0, "Assertion failed (%s) in %s line %d.\n", #x, __FILE__, __LINE__));                                  \
      if (Debug_break)                                                                                                 \
        DEBUG_BREAK();                                                                                                 \
      else                                                                                                             \
        AssertionFailed(#x, __FILE__, __LINE__);                                                                       \
    }                                                                                                                  \
  } while (0)
#define Int3()                                                                                                         \
  do {                                                                                                                 \
    mprintf((0, "Int3 at %s line %d.\n", __FILE__, __LINE__));                                                         \
    if (Debug_break)                                                                                                   \
      DEBUG_BREAK();                                                                                                   \
    else                                                                                                               \
      Int3MessageBox(__FILE__, __LINE__);                                                                              \
  } while (0)
#define HEAPCHECK()
#elif defined(MACINTOSH)
#define DEBUG_BREAK()                                                                                                  \
  do {                                                                                                                 \
    if (DebugBreak_callback_stop)                                                                                      \
      (*DebugBreak_callback_stop)();                                                                                   \
    debug_break();                                                                                                     \
    if (DebugBreak_callback_resume)                                                                                    \
      (*DebugBreak_callback_resume)();                                                                                 \
  } while (0)
#define ASSERT(x) assert(x)
/*	#define ASSERT(x) \
                do { \
                        if (!(unsigned)(x)) { \
                                mprintf((0, "Assertion failed (%s) in %s line %d.\n", #x, __FILE__, __LINE__)); \
                                if (Debug_break)	\
                                        DEBUG_BREAK(); \
                                else	\
                                        AssertionFailed(#x, __FILE__, __LINE__); \
                        } \
                } while(0)
*/
#define Int3()                                                                                                         \
  do {                                                                                                                 \
    mprintf((0, "Int3 at %s line %d.\n", __FILE__, __LINE__));                                                         \
    if (Debug_break)                                                                                                   \
      DEBUG_BREAK();                                                                                                   \
    else                                                                                                               \
      Int3MessageBox(__FILE__, __LINE__);                                                                              \
  } while (0)
#define HEAPCHECK()
#endif
#else
#define DEBUG_BREAK()
#define ASSERT(x)
#define Int3()
#define HEAPCHECK()
#endif
#endif