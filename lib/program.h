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
 

#ifndef PROGRAM_H
#define PROGRAM_H

#include "pstypes.h"

#include "buildno.h"

#define D3_MAJORVER					0x1		// DESCENT 3 VERSION NUMBER
#define D3_MINORVER					0x3
#define D3_BUILD					0x1

#define DEVELOPMENT_VERSION		0x1		// without editor: with debug, no beta
#define RELEASE_VERSION				0x2		// final release candidate: no debug, beta, editor

#define BETA_VERSION					0x1000	// beta modifier.
#define DEMO_VERSION					0x2000	// same as release, but its the demo.


typedef struct t_program_version {
	int version_type;
	ubyte major, minor, build;
	bool debug: 1;						// are we in debug mode
	bool beta:1;						// are we in beta testing mode
	bool release: 1;					// are we a final release candidate
	bool editor: 1;						// editor code?
	bool windowed: 1;					// runs in a window?
	bool demo:1;							// demo?
} program_version;


//	Program state available to everyone
extern program_version Program_version;


//	Useful macros
#define PROGRAM(_c) Program_version._c

//	functions
void ProgramVersion(int version_type, ubyte major, ubyte minor, ubyte build);


#endif