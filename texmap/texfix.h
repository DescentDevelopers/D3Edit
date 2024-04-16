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
 


#ifndef _TEXFIX_H
#define _TEXFIX_H

#include "math.h"
#include "fix.h"

#define TexFloatScaler (16777216.0)
#define TexFixShift    24
#define TF1_0 		   (16777216)

//#define FloatToFix(num) vm_FloatToFix(num)
#define TexFloatToFix(num) (num * TexFloatScaler)

#define TexIntToFix(num) ((num)<<TexFixShift)
#define TexShortToFix(num) (((long)a)<< TexFixShift)
#define TexFixToFloat(num) ((num)/TexFloatScaler)
#define TexFixToInt(num) ((num)>>TexFixShift)
#define TexFixToShort(num) ((short)((num)>>TexFixShift))
#define TexFixMul(a,b) tex_FixMul824(a,b)
#define TexFixDiv(a,b) tex_FixDiv824(a,b)

__inline extern fix tex_FixMul824 (fix a, fix b );
__inline extern fix tex_FixDiv824 (fix a, fix b );
#endif
