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
 #ifndef _TYPES_H
#define _TYPES_H


//define unsigned types;
typedef unsigned char ubyte;
typedef signed char sbyte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

#ifdef _MSC_VER	//only Visual C++ has __int64
typedef __int64	longlong;
#else
typedef long long longlong;
#endif

#ifndef NULL
#define NULL 0
#endif

//The maximum length for a file name, including extension.  It *does not* include the
//terminating NULL, so a buffer to hold a filename needs to be PSFILENAME_LEN+1 bytes long.
#define PSFILENAME_LEN		35

//The maximum length of a path (or path+filename).  The seems (from looking at the code) to
//include the terminating NULL. lengthened to 512 to prevent problems with some long pathnames.
#define PSPATHNAME_LEN		512

#endif

