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
 

#ifndef __DLMODULE_H_
#define __DLMODULE_H_


#ifdef __cplusplus
#define CPPEXTERN	extern "C"
#else
#define CPPEXTERN	extern
#endif


#ifdef WIN32
//=========================Windows Definition============================
#include "windows.h"


#ifdef _MSC_VER		//Visual C++ Build
#define DLLFUNCCALL		__stdcall
#define DLLFUNCCALLPTR	*DLLFUNCCALL
#else				//Non-Visual C++ Build
#define DLLFUNCCALL __attribute__((stdcall))
#define DLLFUNCCALLPTR	DLLFUNCCALL*
#endif

#define MODPROCADDRESS	FARPROC
#define DLLFUNCEXPORT	__declspec (dllexport)
#define DLLFUNCIMPORT	__declspec (dllimport)
#define DLLEXPORT		CPPEXTERN DLLFUNCEXPORT
typedef struct{
	HINSTANCE	handle;	//handle to the DLL
}module;
//=======================================================================
#elif defined (__LINUX__)
//==========================Linux Definitions============================
#include <dlfcn.h>

#define MODPROCADDRESS	void*
#define DLLFUNCCALL		__attribute__((stdcall))
#define DLLFUNCCALLPTR	DLLFUNCCALL*
#define DLLFUNCEXPORT
#define DLLFUNCIMPORT
#define DLLEXPORT		CPPEXTERN

typedef struct{
	void *handle;	//handle to the DLL
}module;
//=======================================================================
#elif defined (MACINTOSH)
//==========================Mac Definitions============================
#define MODPROCADDRESS	void*
#define DLLFUNCCALL
#define DLLFUNCCALLPTR	DLLFUNCCALL*
#define DLLFUNCEXPORT
#define DLLFUNCIMPORT
#define DLLEXPORT

typedef struct{
	void *handle;	//handle to the DLL
}module;
//=======================================================================

#endif


//Mod error codes
#define MODERR_NOERROR		0	//There was no error
#define MODERR_INVALIDMOD	1	//This is not a valid module
#define MODERR_MODNOTFOUND	2	//The module couldn't be found
#define MODERR_MODINITFAIL	3	//The module initialization routine failed
#define MODERR_NOMOD		4	//The value you past in for the module isn't a module, or nothing has been loaded
#define MODERR_INVALIDHANDLE 5	//The module handle passed in is NULL
#define MODERR_OTHER		255	//Some other error occured

//Flags
#define MODF_LAZY			0x001	//Symbol resolution on demand
#define MODF_NOW			0x002	//Resolve all symbols before returning
#define MODF_GLOBAL			0x200	//

//	Returns the real name of the module.  If a given file has an extension, it will
//	just return that filename.  If the given file has no given extension, the 
//	system specific extension is concatted and returned.
void mod_GetRealModuleName(const char *modfilename,char *realmodfilename);

//Loads a dynamic module into memory for use.  If no extension is given, the default
//	system specific extension is used.
//Returns true on success, false otherwise
bool mod_LoadModule(module *handle,char *modfilename,int flags=MODF_LAZY);

//Frees a previously loaded module from memory, it can no longer be used
//Returns true on success, false otherwise
bool mod_FreeModule(module *handle);

//Returns a pointer to a function within a loaded module.  If it returns NULL there was an error.  Check mod_GetLastError
//to see if there was an error
//symstr is the name of the function you want to get the symbol for (Do NOT give any pre/suffix to this name)
//parmbytes is the size (in bytes) of the parameter list the function should have
MODPROCADDRESS mod_GetSymbol(module *handle,char *symstr,unsigned char parmbytes);

//Returns an error code to what the last error was.  When this function is called the last error is cleared, so by calling
//this function it not only returns the last error, but it removes it, so if you were to call this function again, it would
//return no error
int mod_GetLastError(void);


#endif