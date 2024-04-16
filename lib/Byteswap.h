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
 

#ifndef _BYTESWAP_H
#define _BYTESWAP_H

#include "pstypes.h"

/*
#include "psendian.h"

#define SWAPSHORT(x)	(	((x) << 8) | (((ushort)(x)) >> 8) )
#define SWAPINT(x)	(	((x) << 24) | (((ulong)(x)) >> 24) | (((x) & 0x0000ff00) << 8) | (((x) & 0x00ff0000) >> 8)	)

//Stupid function to trick the compiler into letting me byteswap a float
inline float SWAPFLOAT(float x)
{
	int i = SWAPINT(*((int *) &(x)));
	return *((float *) &(i));
}

// INTEL_ assumes the returned value will be in "Little Endian Format"
#define INTEL_INT(x)		Endian_SwapInt(x)
#define INTEL_SHORT(x)		Endian_SwapShort(x)
#define INTEL_FLOAT(x)		Endian_SwapFloat(x)

// MOTOROLA_ assumes the returned value will be in "Big Endian Format"
#define MOTOROLA_INT(x)		SWAPINT(Endian_SwapInt(x))
#define MOTOROLA_SHORT(x)	SWAPSHORT(Endian_SwapShort(x))
#define MOTOROLA_FLOAT(x)	SWAPFLOAT(Endian_SwapFloat(x))
*/
#define SWAPSHORT(x)	(0xFFFF & ( ((x) << 8) | (((ushort)(x)) >> 8) ))
#define SWAPINT(x)	(	((x) << 24) | (((ulong)(x)) >> 24) | (((x) & 0x0000ff00) << 8) | (((x) & 0x00ff0000) >> 8)	)

//Stupid function to trick the compiler into letting me byteswap a float
inline float SWAPFLOAT(float x)
{
	int i = SWAPINT(*((int *) &(x)));
	return *((float *) &(i));
}


//Default is little endian, so change for Macintosh
#ifdef MACINTOSH
   #define OUTRAGE_BIG_ENDIAN
#endif

#ifdef __LINUX__
#include <endian.h>
#if BYTE_ORDER == BIG_ENDIAN
	#define OUTRAGE_BIG_ENDIAN
#endif
#endif

#ifndef OUTRAGE_BIG_ENDIAN
	#define INTEL_INT(x)			x
	#define INTEL_SHORT(x)		x
	#define INTEL_FLOAT(x)		x
	#define MOTOROLA_INT(x)		SWAPINT(x)
	#define MOTOROLA_SHORT(x)	SWAPSHORT(x)
	#define MOTOROLA_FLOAT(x)	SWAPFLOAT(x)
#else
	#define INTEL_INT(x)			SWAPINT(x)
	#define INTEL_SHORT(x)		SWAPSHORT(x)
	#define INTEL_FLOAT(x)		SWAPFLOAT(x)
	#define MOTOROLA_INT(x)		x
	#define MOTOROLA_SHORT(x)	x	
	#define MOTOROLA_FLOAT(x)	x
#endif

#endif
