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
 

#ifndef __PSGLOB_H_
#define __PSGLOB_H_

// Returns 1 if string contains globbing characters in it
int PSGlobHasPattern(char *string);

//	PSGlobMatch
//	Matches the pattern passed in to the string in text.  If the pattern matches
//	it returns 1, if not, it returns 0. In order to have a match, the following
//	conditions must be met:
//	1) The entire string (text) is used for matching.
//	2) '*' matches any sequence of characters.
//	3) '?' matches any character
//	4) [SET] matches any character in the specified set.
//	5) [!SET] matches any character _not_ in the specified set.
//		A set is composed of characters or ranges.  A range looks like
//		character hyphen character (as in 0-9 or A-Z). [0-9a-zA-Z_] is the set
//		of all characters allowed in C identifiers.
//	6) Any other character in the pattern must be matched exactly.(see 9)
//	7) Because of the syntactic significance of []*?!- and \ to match
//		these characters exactly, preced it with a '\'.
//	8) If dot_special is not zero, '*' and '?' do not match '.' at the beginning of text
//	9) If case_sensitive is 0, than case does not matter for the non-pattern characters
int PSGlobMatch(char *pattern, char *text, int case_sensitive, int dot_special);

//Like PSGlobMatch, but match pattern against any final segment of text
int PSGlobMatchAfterStar(char *pattern, int case_sensitive, char *text);

#endif