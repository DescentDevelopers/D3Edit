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

#ifndef WIN32DATABASE
#define WIN32DATABASE

/* oeWin32AppDatabase
        to get info about the application from a managed database (or a custom info file)
        we get our information from the registry!
*/

class oeWin32AppDatabase : public oeAppDatabase {
  unsigned hBaseKey; // look up from this key.
  unsigned hCurKey;  // current key for lookup

protected:
  char m_Basepath[256];

public:
  oeWin32AppDatabase();
  oeWin32AppDatabase(oeWin32AppDatabase *parent);
  virtual ~oeWin32AppDatabase();

  //	creates an empty classification or structure where you can store information
  virtual bool create_record(const char *pathname);

  //	set current database focus to a particular record
  virtual bool lookup_record(const char *pathname);

  //	read either an integer or string from the current record
  virtual bool read(const char *label, char *entry, int *entrylen);
  virtual bool read(const char *label, void *entry, int wordsize); // read a variable-size int
  virtual bool read(const char *label, bool *entry);

  //	write either an integer or string to a record.
  virtual bool write(const char *label, const char *entry, int entrylen);
  virtual bool write(const char *label, int entry);

  // get the current user's name.
  virtual void get_user_name(char *buffer, ulong *size);
};

// pass name of dll which contains desired language
// NULL library is the default resource DLL
bool win32_SetResourceDLL(const char *libname);

// returns a string from the current resource
bool win32_GetStringResource(int txt_id, char *buffer, int buflen);

#endif