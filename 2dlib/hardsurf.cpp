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
 

#include "gr.h"


//	----------------------------------------------------------------------------
//	constructor and destructor
//	----------------------------------------------------------------------------

grHardwareSurface::grHardwareSurface()
	:grSurface()
{

}


grHardwareSurface::grHardwareSurface(int w, int h, int bpp, unsigned flags, const char *name)
	:grSurface(w, h, bpp, SURFTYPE_GENERIC, flags, name)
{

}


grHardwareSurface::~grHardwareSurface()
{

}


//	----------------------------------------------------------------------------
//	initialize a hardware surface with these values
//	----------------------------------------------------------------------------

bool grHardwareSurface::create(int w, int h, int bpp, unsigned flags, const char *name)
{
	grSurface::create(w,h,bpp, SURFTYPE_GENERIC, flags, name);
	return 1;
}

