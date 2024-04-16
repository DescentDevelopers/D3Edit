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

#ifndef __LOCALIZATION_H__
#define __LOCALIZATION_H__

#define LANGUAGE_ENGLISH 0
#define LANGUAGE_GERMAN 1
#define LANGUAGE_SPANISH 2
#define LANGUAGE_ITALIAN 3
#define LANGUAGE_FRENCH 4
void Localization_SetLanguage(int type);
int Localization_GetLanguage(void);

// Call this to load up the string tables into memory
// Returns the number of strings loaded, if this is 0, then the program MUST not continue
int LoadStringTables(void);

// Deallocates all the memory used for the string tables
void FreeStringTables(void);

// Returns a pointer to the string at the index location from the string table
// if it is a bad index given, then the pointer to the error string "ERROR MISSING STRING" is given
char *GetStringFromTable(int index);

// Given a filename, pointer to a char * array and a pointer to an int,
// it will load the string table and fill in the information
// returns true on success
bool CreateStringTable(char *filename, char ***table, int *size);
// Given a string table and it's count of strings, it will free up it's memory
void DestroyStringTable(char **table, int size);

// GrowString class
// handles a string of increasing size (using +,=,+=)
typedef struct tbufferinfo {
  char *string_data;
  tbufferinfo *next;
} tbufferinfo;

class GrowString {
public:
  GrowString();
  ~GrowString();
  void Destroy(void);
  void operator+=(char *str);
  GrowString operator+(char *str);
  GrowString operator+(GrowString &gs);
  void operator+=(GrowString &gs);
  void operator=(char *str);
  void operator=(GrowString &gs);
  void GetString(char **str);
  int Length(void);

private:
  tbufferinfo root;
  tbufferinfo *curr;
};

#endif