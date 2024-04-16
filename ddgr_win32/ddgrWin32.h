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

#ifndef DDGRWIN32_H
#define DDGRWIN32_H

#include "ddgr.h"
#include "pstypes.h"

/*	Subsystem constants

        as of v2.0
*/
const int DDGR_GDI_SUBSYSTEM = 1, // GDI subsystem
    DDGR_GDIX_SUBSYSTEM = 2,      // GDIX subsystem (GDI+DirectX)
    DDGR_DX_SUBSYSTEM = 3;        // DIRECTX subsystem

/*	Internal Library Data

*/
typedef struct tDDGRInternalData {
  bool init;     // Is library currently initialized
  int subsystem; // Current active subsystem
} tDDGRInternalData;

/*	Global externs
 */
extern tDDGRInternalData DDGR_lib_data;
extern char *DDGR_subsystem_names[];
extern int DDGR_subsystems[];

/*	Macros
 */
#define LIB_DATA(_c) DDGR_lib_data._c

inline unsigned DDGR_MAKERGB16(ddgr_color c) {
  unsigned char r, g, b;
  r = (unsigned char)((c & 0x00ff0000) >> 16);
  g = (unsigned char)((c & 0x0000ff00) >> 8);
  b = (unsigned char)(c & 0x000000ff);

  return (((r >> 3) << 10) + ((g >> 3) << 5) + (b >> 3));
}

inline int DDGR_COLOR_RED(ddgr_color c) {
  unsigned r = (unsigned char)((c & 0x00ff0000) >> 16);
  return (int)r;
}

inline int DDGR_COLOR_GREEN(ddgr_color c) {
  unsigned g = (unsigned char)((c & 0x0000ff00) >> 8);
  return (int)g;
}

inline int DDGR_COLOR_BLUE(ddgr_color c) {
  unsigned b = (unsigned char)(c & 0x000000ff);
  return (int)b;
}

/*	Functions Internal
 */

void ddgr_FatalError(char *fmt, ...);
void ddgr_PushError(char *fmt, ...);

#endif