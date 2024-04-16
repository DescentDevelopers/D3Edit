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
#ifndef POSTRENDER_H
#define POSTRENDER_H

#define MAX_POSTRENDERS 3000

#define PRT_OBJECT 0
#define PRT_VISEFFECT 1
#define PRT_WALL 2

typedef struct {
  ubyte type; // See types above
  union {
    short objnum;
    short visnum;
    short facenum;
  };

  short roomnum;
  float z;
} postrender_struct;

extern int Num_postrenders;
extern postrender_struct Postrender_list[];

void ResetPostrenderList();

// Renders all the objects/viseffects/walls we have in our postrender list
void PostRender(int);

void DrawPostrenderFace(int roomnum, int facenum, bool change_z = true);

#endif