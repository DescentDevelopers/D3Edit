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

// ----------------------------------------------------------------------------
// Device Dependent IO System Main Library Interface - functions here are located
//	in the ddio_??? system where ??? is the os.
// ----------------------------------------------------------------------------

#ifndef DDIO_H
#define DDIO_H

class oeApplication;

#include <stdio.h>

#include "pstypes.h"
#include "ddio_common.h"

// ----------------------------------------------------------------------------
//	Initialization and destruction functions
// ----------------------------------------------------------------------------

//	preemptive = 1 for thread based IO.  Initializes the IO system
bool ddio_InternalInit(ddio_init_info *init_info);
void ddio_InternalClose();

// ----------------------------------------------------------------------------
//	Keyboard Interface
// ----------------------------------------------------------------------------

// used by ddio system to initialize machine specific key code.
bool ddio_InternalKeyInit(ddio_init_info *init_info);
void ddio_InternalKeyClose();

// handled internally if keyboard system needs additional processing per frame
void ddio_InternalKeyFrame();
void ddio_InternalKeySuspend();
void ddio_InternalKeyResume();

// returns if key is up or down
bool ddio_InternalKeyState(ubyte key);

// returns internal key down time
float ddio_InternalKeyDownTime(ubyte key);

// flush a key internally
void ddio_InternalResetKey(ubyte key);

// ----------------------------------------------------------------------------
//	Device Dependent Timer Interface
// ----------------------------------------------------------------------------

bool timer_Init(int preemptive, bool force_lores);
void timer_Close();

//	returns time in seconds
float timer_GetTime();

// returns time in milliseconds
longlong timer_GetMSTime();

//	hook in timer function at certain period.  returns a handle to this function
//@@int timer_HookFunction(void (*fncptr)(), int period);

//	clears function from hook list specified by a handle returned from HookFunction
//@@void timer_ReleaseFunction(int func);

// ----------------------------------------------------------------------------
//	Device Dependent Mouse Interface
// ----------------------------------------------------------------------------

#define MOUSE_LB 1 // mouse button masks
#define MOUSE_RB 2
#define MOUSE_CB 4
#define MOUSE_B4 8
#define MOUSE_B5 16
#define MOUSE_B6 32
#define MOUSE_B7 64
#define MOUSE_B8 128

#define N_MSEBTNS 8

//	initializes mouse.
bool ddio_MouseInit();
void ddio_MouseClose();

// get device caps
int ddio_MouseGetCaps(int *btn, int *axis);

// use these extensions to set exclusive or standard mouse modes
#define MOUSE_STANDARD_MODE 1  // uses absolute coordinates and simple buttons
#define MOUSE_EXCLUSIVE_MODE 2 // uses relative coordinates and advanced button information
void ddio_MouseMode(int mode);

//	resets position of mouse to center, resets virtual coord system to equal screen coordinate system
void ddio_MouseReset();

// resets mouse queue and button info only.
void ddio_MouseQueueFlush();

// handled internally if mouse system needs additional processing per frame
void ddio_InternalMouseFrame();

// used to prevent mouse input from being registered
void ddio_InternalMouseSuspend();
void ddio_InternalMouseResume();

//	returns absolute position of mouse, button state and mouse deltas.
/*	x, y = absolute mouse position
        dx, dy = mouse deltas since last call
        return value is mouse button mask.   values not needed should pass NULL pointers.
*/
int ddio_MouseGetState(int *x, int *y, int *dx, int *dy, int *z = NULL, int *dz = NULL);

// gets a mouse button event, returns false if none.
bool ddio_MouseGetEvent(int *btn, bool *state);

// returns string to binding.
const char *ddio_MouseGetBtnText(int btn);
const char *ddio_MouseGetAxisText(int axis);

// tells app is the mouse system will poll the mouse device the next time ddio_MouseGetState
//	is called.
bool ddio_IsMouseReady();

// return mouse button down time.
float ddio_MouseBtnDownTime(int btn);

// return mouse button down time
int ddio_MouseBtnDownCount(int btn);

// return mouse button up count
int ddio_MouseBtnUpCount(int btn);

//	displays the mouse pointer.  Each Hide call = Show call.
// void ddio_MouseShow();
// void ddio_MouseHide();

//	set bounds for system polling of coordinates
void ddio_MouseSetLimits(int left, int top, int right, int bottom, int zmin = 0, int zmax = 0);
void ddio_MouseGetLimits(int *left, int *top, int *right, int *bottom, int *zmin = 0, int *zmax = 0);

// virtual coordinate system for mouse (match to video resolution set for optimal mouse usage.
void ddio_MouseSetVCoords(int width, int height);

//	---------------------------------------------------------------------------
//	File Operations
//	---------------------------------------------------------------------------

//	creates or destroys a directory or folder on disk
//	This pathname is *RELATIVE* not fully qualified
bool ddio_CreateDir(const char *path);
bool ddio_RemoveDir(const char *path);

// deletes a file.  Returns 1 if successful, 0 on failure
//	This pathname is *RELATIVE* not fully qualified
int ddio_DeleteFile(char *name);

// Save/Restore the current working directory
void ddio_SaveWorkingDir(void);
void ddio_RestoreWorkingDir(void);

//	retrieve the current working folder where file operation will occur.
//	Note ---> The path in Get/Set working directory is in the *LOCAL* file system's syntax
//	This pathname is relative *OR* fully qualified
void ddio_GetWorkingDir(char *path, int len);
bool ddio_SetWorkingDir(const char *path);

// 	Checks if a directory exists (returns 1 if it does, 0 if not)
//	This pathname is *RELATIVE* not fully qualified
bool ddio_DirExists(const char *path);

//  get a file length of a FILE
int ddio_GetFileLength(FILE *filePtr);

//	check if two files are different
//	This pathname is *RELATIVE* not fully qualified
bool ddio_FileDiff(const char *fileNameA, const char *fileNameB);

//	copies one files timestamp to another
void ddio_CopyFileTime(char *dest, const char *src);

// Split a pathname into its component parts
//	The path in splitpath is in the *LOCAL* file system's syntax
void ddio_SplitPath(const char *srcPath, char *path, char *filename, char *ext);

//	 pass in a pathname (could be from ddio_SplitPath), root_path will have the drive name.
void ddio_GetRootFromPath(const char *srcPath, char *root_path);

//	retrieve root names, free up roots array (allocated with malloc) after use
int ddio_GetFileSysRoots(char **roots, int max_roots);

// Constructs a path in the local file system's syntax
// 	builtPath: stores the constructed path
//  absolutePathHeader: absolute path on which the sub directories will be appended
//						(specified in local file system syntax)
//	subdir:	the first subdirectory
//  takes a variable number of additional subdirectories which will be concatenated on to the path
//		the last argument in the list of sub dirs *MUST* be NULL to terminate the list
void ddio_MakePath(char *newPath, const char *absolutePathHeader, const char *subDir, ...);

//	These functions allow one to find a file
//		You use FindFileStart by giving it a wildcard (like *.*, *.txt, u??.*, whatever).  It returns
//		a filename in namebuf.
//		Use FindNextFile to get the next file found with the wildcard given in FindFileStart.
//		Use FindFileClose to end your search.
bool ddio_FindFileStart(const char *wildcard, char *namebuf);
bool ddio_FindNextFile(char *namebuf);
void ddio_FindFileClose();

void ddio_FindDirClose();
bool ddio_FindDirStart(const char *wildcard, char *namebuf);
bool ddio_FindNextDir(char *namebuf);

//	given a path (with no filename), it will return the parent path
//	srcPath is the source given path
//	dest is where the parent path will be placed
//	returns true on success
//		dest should be at least _MAX_PATH in length
bool ddio_GetParentPath(char *dest, const char *srcPath);

//	given a path, it cleans it up (if the path is c:\windows\..\dos it would make it c:\dos)
//	srcPath is the original path
//	dest is the finished cleaned path.
//		dest should be at least _MAX_PATH in size
void ddio_CleanPath(char *dest, const char *srcPath);

// Finds a full path from a relative path
// Parameters:	full_path - filled in with the fully-specified path.  Buffer must be at least _MAX_PATH bytes long
//					rel_path - a path specification, either relative or absolute
// Returns TRUE if successful, FALSE if an error
bool ddio_GetFullPath(char *full_path, const char *rel_path);

// Generates a temporary filename based on the prefix, and basedir
// Parameters:
//		basedir - directory to put the files
//		prefix - prefix for the temp filename
//		filename - buffer to hold generated filename (must be at least _MAX_PATH in length)
//
// Returns TRUE if successful, FALSE if an error
bool ddio_GetTempFileName(char *basedir, char *prefix, char *filename);

// Renames file
// Returns true on success or false on an error
bool ddio_RenameFile(char *oldfile, char *newfile);

// Give a volume label to look for, and if it's found returns a path
// If it isn't found, return ""
char *ddio_GetCDDrive(char *vol);

// Checks to see if a lock file is located in the specified directory.
//	Parameters:
//		dir		Directory for which the lock file should be checked
//	Returns:
//		1		Lock file doesn't exist
//		2		Lock file was in a directory, but it belonged to a process that no longer
//				exists, so a lock file _can_ be made in the directory.
//		3		Lock file for this process already exists
//		0		Lock file currently exists in directory
//		-1		Illegal directory
//		-2		There is a lock file in the directory, but it is in an illegal format
int ddio_CheckLockFile(const char *dir);

// Creates a lock file in the specified directory
//	Parameters:
//		dir		Directory for which the lock file should be created in
//	Returns:
//		1		Lock file created
//		2		Lock file created (there was a lock file in that directory, but it belonged
//				to a process that no longer exists)
//		3		Lock file for this process already exists
//		0		Lock file not created, a lock file currently exists in the directory
//		-1		Illegal directory
//		-2		There is a lock file in the directory, but it is in an illegal format
//		-3		Unable to create lock file
int ddio_CreateLockFile(const char *dir);

// Deletes a lock file (for the current process) in the specified directory
//	Parameters:
//		dir		Directory for which the lock file should be deleted from
//	Returns:
//		1		Lock file deleted
//		0		Lock file not deleted, the lock file in the directory does not belong to our
//				process
//		-1		Illegal directory
//		-2		A lock file exists in the directory, but wasn't deleted...illegal format
//		-3		Unable to delete file
int ddio_DeleteLockFile(const char *dir);

#endif