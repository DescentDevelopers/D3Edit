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

#ifndef _FIX_H
#define _FIX_H

#include "math.h"

// Disable the "possible loss of data" warning
#pragma warning(disable : 4244)

// Angles are unsigned shorts
typedef unsigned short angle;

// The basic fixed-point type
typedef long fix;

#define PI 3.141592654
#define PIOVER2 1.570796327 // DAJ

// Constants for converted between fix and float
#define FLOAT_SCALER 65536.0
#define FIX_SHIFT 16

// 1.0 in fixed-point
#define F1_0 (1 << FIX_SHIFT)

// Generate the data for the trig tables.  Must be called before trig functions
void InitMathTables();

// Returns the sine of the given angle.  Linearly interpolates between two entries in a 256-entry table
float FixSin(angle a);

// Returns the cosine of the given angle.  Linearly interpolates between two entries in a 256-entry table
float FixCos(angle a);

// Returns the sine of the given angle, but does no interpolation
float FixSinFast(angle a);

// Returns the cosine of the given angle, but does no interpolation
float FixCosFast(angle a);

#define Round(x) ((int)(x + 0.5))

fix FloatToFixFast(float num);

// Conversion macros
//??#define FloatToFix(num) Round((num) * FLOAT_SCALER)
#define FloatToFix(num) ((fix)((num)*FLOAT_SCALER))
#define IntToFix(num) ((num) << FIX_SHIFT)
#define ShortToFix(num) (((long)(num)) << FIX_SHIFT)
#define FixToFloat(num) (((float)(num)) / FLOAT_SCALER)
#define FixToInt(num) ((num) >> FIX_SHIFT)
#define FixToShort(num) ((short)((num) >> FIX_SHIFT))

// Fixed-point math functions in inline ASM form
#if defined(MACINTOSH)
#include "fixmac.h"
#elif defined(WIN32)
#include "win\fixwin32.h"
#endif

// use this instead of:
// for:  (int)floor(x+0.5f) use FloatRound(x)
//       (int)ceil(x-0.5f)  use FloatRound(x)
//       (int)floor(x-0.5f) use FloatRound(x-1.0f)
//       (int)floor(x)      use FloatRound(x-0.5f)
// for values in the range -2048 to 2048
int FloatRound(float x);

angle FixAtan2(float cos, float sin);
angle FixAsin(float v);
angle FixAcos(float v);

// Does a ceiling operation on a fixed number
fix FixCeil(fix num);

// Floors a fixed number
fix FixFloor(fix num);

#endif
