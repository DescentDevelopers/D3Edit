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
#ifndef _IFF_H
#define _IFF_H

#include "CFILE.H"

// Error codes for read & write routines

#define IFF_NO_ERROR 0      // everything is fine, have a nice day
#define IFF_NO_MEM 1        // not enough mem for loading or processing
#define IFF_UNKNOWN_FORM 2  // IFF file, but not a bitmap
#define IFF_NOT_IFF 3       // this isn't even an IFF file
#define IFF_NO_FILE 4       // cannot find or open file
#define IFF_BAD_BM_TYPE 5   // tried to save invalid type, like BM_RGB15
#define IFF_CORRUPT 6       // bad data in file
#define IFF_FORM_ANIM 7     // this is an anim, with non-anim load rtn
#define IFF_FORM_BITMAP 8   // this is not an anim, with anim load rtn
#define IFF_TOO_MANY_BMS 9  // anim read had more bitmaps than room for
#define IFF_UNKNOWN_MASK 10 // unknown masking type
#define IFF_READ_ERROR 11   // error reading from file
#define IFF_BM_MISMATCH 12  // bm being loaded doesn't match bm loaded into

// Type values for iff bitmaps
#define TYPE_PBM 0
#define TYPE_ILBM 1

// Loads an IFF file, returning bitmap handle or -1 if error
int bm_iff_alloc_file(CFILE *);

// Loads a tga or ogf file into a bitmap...returns handle to bm or -1 on error
int bm_tga_alloc_file(CFILE *infile, char *name, int format = 0);

// Loads a pcx file and converts it to 16 bit.  Returns bitmap handle or -1 on error
int bm_pcx_alloc_file(CFILE *infile);

int bm_tga_load_short_file(CFILE *infile, char *name);

// Pages in bitmap index n.  Returns 1 if successful, 0 if not
int bm_page_in_file(int n);

int bm_iff_read_animbrush(const char *ifilename, int *bm_list);

#endif
