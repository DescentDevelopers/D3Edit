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

#ifndef _MONO_H
#define _MONO_H
#include "debug.h"
void nw_InitTCPLogging(char *ip, unsigned short port);
void nw_TCPPrintf(int n, char *format, ...);
#if (!defined(RELEASE)) && defined(MONO)
extern bool Debug_print_block;
// Prints a formatted string to the debug window
#define mprintf(args) Debug_ConsolePrintf args
// Prints a formatted string on window n at row, col.
#define mprintf_at(args) Debug_ConsolePrintf args
#define DebugBlockPrint(args)                                                                                          \
  do {                                                                                                                 \
    if (Debug_print_block)                                                                                             \
      mprintf_at((1, 5, 51, args));                                                                                    \
  } while (0)
#else // ifdef _DEBUG
#ifndef MACINTOSH
#define mprintf(args) // DAJ defined in target headers
#endif
#define mprintf_at(args)
#define DebugBlockPrint(args)
#endif // ifdef _DEBUG
#endif
