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

#include <string.h>

#include "gr.h"
#include "pserror.h"
#include "renderer.h"

//	---------------------------------------------------------------------------
//	grSurface constructor and destructor
//	---------------------------------------------------------------------------

grScreen::grScreen(int w, int h, int bpp, const char *name)
    : grSurface(w, h, bpp, SURFTYPE_VIDEOSCREEN, SURFFLAG_BACKBUFFER, name) {}

grScreen::~grScreen() {}

//	---------------------------------------------------------------------------
//	screen refresh routines
//	---------------------------------------------------------------------------

void grScreen::flip() {
  ASSERT(surf_init());
  if (ddsfObj.flags & SURFFLAG_BACKBUFFER)
    ddgr_surf_FlipVideo(&ddsfObj);
  else if (ddsfObj.flags & SURFFLAG_RENDERER)
    rend_Flip();
}
