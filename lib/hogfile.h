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

#ifndef HOGFILE_H
#define HOGFILE_H

#include "pstypes.h"

#define HOG_HDR_SIZE 64
#define HOG_TAG_STR "HOG2"

typedef struct tHogHeader {
  unsigned nfiles;           // number of files in header
  unsigned file_data_offset; // offset in file to filedata.
} tHogHeader;

typedef struct tHogFileEntry {
  char name[PSFILENAME_LEN + 1]; // file name
  unsigned flags;                // extra info
  unsigned len;                  // length of file
  unsigned long timestamp;       // time of file.
} tHogFileEntry;

#define HOGMAKER_ERROR 0       // Incorrect number of files passed in
#define HOGMAKER_OK 1          //	Hog file was created successfully
#define HOGMAKER_MEMORY 2      // Could not allocated hog entry table
#define HOGMAKER_OUTFILE 3     // Error occurred writing to output hog file
#define HOGMAKER_INFILE 4      // An input file could not be found (filename is stored in hogerr_filename)
#define HOGMAKER_COPY 5        // An error occurred copying an input file into the hog file
#define HOGMAKER_OPENOUTFILE 6 // The specified hog file could not be opened for output

// Used to return filenames involved in a NewHogFile() error
extern char hogerr_filename[PSPATHNAME_LEN];

int NewHogFile(const char *hogname, int nfiles, const char **filenames);
bool ReadHogHeader(FILE *fp, tHogHeader *header);
bool ReadHogEntry(FILE *fp, tHogFileEntry *entry);
bool WRITE_FILE_ENTRY(FILE *fp, tHogFileEntry *entry);
bool FileCopy(FILE *ofp, FILE *ifp, int length);

int CreateNewHogFile(const char *hogname, int nfiles, const char **filenames, void (*UpdateFunction)(char *));

// returns hog cfile info, using a library handle opened via cf_OpenLibrary.
bool cf_ReadHogFileEntry(int library, const char *filename, tHogFileEntry *entry, int *fileoffset);

#endif