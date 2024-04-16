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
#ifndef SPECIAL_FACE_H
#define SPECIAL_FACE_H

#include "pstypes.h"
#include "pserror.h"
#include "vecmat.h"

#define BAD_SPECIAL_FACE_INDEX -1
#define MAX_SPECIAL_FACES 13000 // made large enough for Josh's Mercenary level 3

// What this special face is used for:
#define SFT_SPECULAR 1

typedef struct {
  vector bright_center;
  ushort bright_color;
} specular_instance;

#define SFF_SPEC_OBJECT 1
#define SFF_SPEC_SMOOTH 2

typedef struct {
  ubyte type; // See types (above)
  ubyte num;  // Number of instances
  ubyte used;
  ubyte flags;

  specular_instance *spec_instance;

  vector *vertnorms;

} special_face;

extern special_face SpecialFaces[];
extern int Num_of_special_faces;

// Sets all the special faces to unused
void InitSpecialFaces();

// Returns an index into the special faces array
int AllocSpecialFace(int type, int num, bool vertnorms = false, int num_vertnorms = 0);

// Given a handle, frees the special face
void FreeSpecialFace(int handle);

#endif
