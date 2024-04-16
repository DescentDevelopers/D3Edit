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

#ifndef APPDATABASE
#define APPDATABASE

#include "pstypes.h"

/* oeAppDatabase
        to get info about the application from a managed database (or a custom info file)
        Again, this class should be the parent of a platform specific class like osWinDatabase, for instance.
*/

class oeAppDatabase {
public:
  oeAppDatabase(){};

  //	you can also create a reference to a current database.  this is good if
  //	you have a hierachical database.
  oeAppDatabase(oeAppDatabase *parent){};
  virtual ~oeAppDatabase(){};

  //	creates an empty classification or structure where you can store information
  virtual bool create_record(const char *pathname) = 0;

  //	set current database focus to a particular record
  virtual bool lookup_record(const char *pathname) = 0;

  //	read either an integer or string from the current record
  virtual bool read(const char *label, char *entry, int *entrylen) = 0;
  virtual bool read(const char *label, void *entry, int wordsize) = 0; // read an variable-sized integer
  virtual bool read(const char *label, bool *entry) = 0;

  //	write either an integer or string to a record.
  virtual bool write(const char *label, const char *entry, int entrylen) = 0;
  virtual bool write(const char *label, int entry) = 0;

  // get the current user's name.
  virtual void get_user_name(char *buffer, ulong *size) = 0;
};

// JCA: moved these from the Win32Database

// Handy macro to read an int without having to specify the wordsize
#define read_int(label, varp) read(label, varp, sizeof(*varp))

// Macro to write a string
#define write_string(label, varp) write(label, varp, strlen(varp))

/*	This section includes the platform-specific header files
        Add a platform to this list once implemented:

                Win32				Samir		Win32Database.h			06/97
*/

#if defined(WIN32)
#include "win\Win32Database.h"
#elif defined(__LINUX__)
#include "linux/lnxdatabase.h"
#elif defined(MACINTOSH)
#include "macdatabase.h"
#endif

#endif