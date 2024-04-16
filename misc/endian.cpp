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
 

#include "psendian.h"
#include "mono.h"

#define SWAPSHORT(x)	((0xffff & ((x) << 8) | (((unsigned short)(x)) >> 8) ))					
#define SWAPINT(x)	(	((x) << 24) | (((unsigned long)(x)) >> 24) | (((x) & 0x0000ff00) << 8) | (((x) & 0x00ff0000) >> 8)	)
inline float SWAPFLOAT(float x){int i = SWAPINT(*((int *) &(x)));return *((float *) &(i));}

#define ENDIAN_BIG_ENDIAN		0
#define ENDIAN_LITTLE_ENDIAN	1
signed char Endian_type = -1;

// Endian_IsLittleEndian
//
//	Returns true if the machine is Little Endian (i.e. 80x86)
//	Returns false if the machine is Big Endian (i.e. Macintosh)
bool Endian_IsLittleEndian(void)
{
	char c_vals[2] = { 0x00, 0x01 };
	short *s_val;

	s_val = (short *)c_vals;

	if((*s_val)==0x01)
	{
		//we have a Big Endian machine
		mprintf((0,"Machine is BIG ENDIAN format\n"));
		Endian_type = ENDIAN_BIG_ENDIAN;
		return false;
	}

	//else s_val == 256
	//we have a Little Endian machine
	mprintf((0,"Machine is LITTLE ENDIAN format\n"));
	Endian_type = ENDIAN_LITTLE_ENDIAN;
	return true;
}

// Swaps (if needed) a short value (2 bytes) (assumes incoming value is in little endian format)
short Endian_SwapShort(short value)
{
	if(Endian_type==-1)
		Endian_IsLittleEndian();	//detect endianness

	if(Endian_type==ENDIAN_BIG_ENDIAN)
		value = SWAPSHORT(value);

	return value;
}

// Swaps (if needed) an int value (4 bytes) (assumes incoming value is in little endian format)
int Endian_SwapInt(int value)
{
	if(Endian_type==-1)
		Endian_IsLittleEndian();	//detect endianness

	if(Endian_type==ENDIAN_BIG_ENDIAN)
		value = SWAPINT(value);

	return value;
}

// Swaps (if needed) a float value (4 bytes) (assumes incoming value is in little endian format)
float Endian_SwapFloat(float value)
{
	if(Endian_type==-1)
		Endian_IsLittleEndian();	//detect endianness

	if(Endian_type==ENDIAN_BIG_ENDIAN)
		value = SWAPFLOAT(value);

	return value;
}
