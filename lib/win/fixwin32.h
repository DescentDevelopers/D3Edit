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
 

#ifndef _FIXWIN32_H
#define _FIXWIN32_H

//what does this do?  Why didn't Jason put a comment here?
// Jason replies: This pragma disables the "no return value" warning that
// is generated when converting doubles to floats
// A thousand pardons for the confusion

#pragma warning (disable:4035)

inline fix FixDiv (fix a,fix b)
{
	__asm 
	{
		mov eax,a
		mov ebx,b
		cdq
		shld edx, eax, 16
		sal eax,16
		idiv ebx
	}
}


inline fix FixMul (fix a,fix b)
{
	__asm
	{
		mov eax,a
		mov ebx,b	
	    imul ebx
        shrd eax,edx,16
	}
}

inline fix FixMulDiv (fix a,fix b,fix c)
{
	__asm 	
	{
		mov eax, a
		mov edx, b
		mov ebx, c
		imul edx
		idiv ebx
	}
}

#pragma warning (default:4035)

#endif
