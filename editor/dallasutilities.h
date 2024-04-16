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
 

#ifndef _DALLAS_UTILITIES_H_
#define _DALLAS_UTILITIES_H_

#define WHITESPACE_CHARS	" \t\r\n"

// Removes any whitespace padding from the end of a string
void RemoveTrailingWhitespace(char *s);

// Returns a pointer to the first non-whitespace char in given string
char *SkipInitialWhitespace(char *s);


bool FindManageFirst(char *buffer,char *wildcard);
bool FindManageNext(char *buffer);
void FindManageClose(void);
bool GamefileExists(char *name);

#endif /*_DALLAS_UTILITIES_H_*/