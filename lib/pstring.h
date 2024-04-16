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
 


#ifndef _PSTRING_H_
#define _PSTRING_H_

#include <stdarg.h>

//	Pvsprintf
//		Similar to vsprintf/_vsnprintf, however handles the case of a buffer overflow.  Arguments are the
//	same as _vsnprintf.  In the case of count, pass in the size of the buffer, in the case where there is
//	a buffer overflow, a \0 will be tacked on as the last byte in the buffer, ensuring a valid string.
int Pvsprintf(char *buffer, int count, const char *format, va_list argptr);

//	Psprintf
//		Similar to sprintf/_snprintf, however handles the case of a buffer overflow.  Arguments are the
//	same as _snprintf.  In the case of count, pass in the size of the buffer, in the case where there is
//	a buffer overflow, a \0 will be tacked on as the last byte in the buffer, ensuring a valid string.
int Psprintf(char *buffer, int count, const char *format, ... );

// CleanupStr
//		this function strips all leading and trailing spaces, keeping internal spaces.  this goes
//		for tabs too.
int CleanupStr(char *dest, const char *src, int destlen);

// tStringTok
//		you may start a string tokenization object by calling the start function
//		then call next, to get the following tokens.
//		note that this class uses it's own copy of the string to ensure that strtok doesn't
//		get corrupted.

class tStringTok
{
	char *m_strbuf;
	char *m_curptr;

public:
	tStringTok() : m_strbuf(0), m_curptr(0) {};
	~tStringTok();

	char *start(const char *str, const char *tokens);
	char *next(const char *tokens);
};

#endif