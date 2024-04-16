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

#ifndef __ENDIAN_H___
#define __ENDIAN_H___

extern "C" {
// Endian_IsLittleEndian
//
//	Returns true if the machine is Little Endian (i.e. 80x86)
//	Returns false if the machine is Big Endian (i.e. Macintosh)
bool Endian_IsLittleEndian(void);

// Swaps (if needed) a short value (2 bytes) (assumes incoming value is in little endian format)
short Endian_SwapShort(short value);

// Swaps (if needed) an int value (4 bytes) (assumes incoming value is in little endian format)
int Endian_SwapInt(int value);

// Swaps (if needed) a float value (4 bytes) (assumes incoming value is in little endian format)
float Endian_SwapFloat(float value);
}
#endif