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
 
#include "macros.h"
#include "psclass.h"
#include <string.h>

// CleanupStr
//		this function strips all leading and trailing spaces, keeping internal spaces.  this goes
//		for tabs too.
int CleanupStr(char *dest, const char *src, int destlen)
{
	int i,j, err, begin=0, end=0, len;

	err = 0;

	len = strlen(src);
	for (i = 0; i < len; i++)
	{
		char ch;
		ch = src[i];

	//	 mark beginning.
		if ((ch>' ' && ch>'\t') && err < 1) { err = 1; begin = i; end = i; }
		else if (ch == ' ' && err == 1) { err = 2; end = i; }
		else if (ch > ' ' && err >= 1) { end = i; }
	}

	j = 0;
	for (i = begin; i < (end+1); i++)
	{
		char ch;
		ch = src[i];
		if (j == destlen-1) break;
		if (ch != '\"') dest[j++] = ch;
	}

	dest[j] = 0;

	return 0;
}


// tStringTok
//		you may start a string tokenization object by calling the start function
//		then call next, to get the following tokens.
//		note that this class uses it's own copy of the string to ensure that strtok doesn't
//		get corrupted.

tStringTok::~tStringTok()
{
	if (m_strbuf) 
		delete[] m_strbuf;
}


char *tStringTok::start(const char *str, const char *tokens)
{
// if we pass a null string, then reset this object
	if (str == NULL) {
		if (m_strbuf) 
			delete[] m_strbuf;
		m_strbuf = NULL;
		m_curptr = NULL;
		return NULL;
	}

	char *new_str = new char[strlen(str)+1];

//	copy string into new string buffer.  AFTER THIS, delete the current string buffer, since the pointer
//	passed in could point to the current m_strbuf ptr.
	strcpy(new_str, str);
	
	if (m_strbuf) 
		delete[] m_strbuf;
	m_strbuf = new_str;
	m_curptr = m_strbuf;

	return this->next(tokens);
}


char *tStringTok::next(const char *tokens)
{
// create string by terminating m_strbuf when a token is it.
	char *cur_str, *end_str;
	int slen2, j;

	if (!m_curptr)
		return m_curptr;

	slen2 = strlen(tokens);
	cur_str = NULL;

	for (j = 0; j < slen2; j++)
	{
		end_str = strchr(m_curptr, tokens[j]);
		if (end_str) {
			*end_str = 0;
			cur_str = m_curptr;
			m_curptr = end_str+1;
			return cur_str;
		}
	}
	//	at this point, we found no tokens, so m_curptr will point to the string we want to return.
	// then we set m_curptr to NULL, telling any subsequent calls to next to return NULL.

	cur_str = m_curptr;
	m_curptr = NULL;

	return cur_str;
}
