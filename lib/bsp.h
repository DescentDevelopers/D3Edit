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
 


#ifndef BSP_H
#define BSP_H

#include "list.h"
#include "vecmat.h"
#include "CFILE.H"

#define BSP_IN_FRONT		1
#define BSP_BEHIND		2
#define BSP_ON_PLANE		3
#define BSP_SPANNING		4
#define BSP_COINCIDENT	5

#define BSP_EPSILON		.00005f

#define BSP_NODE	0
#define BSP_EMPTY_LEAF	1
#define BSP_SOLID_LEAF	2

typedef struct
{
	float a,b,c,d;
	ubyte used;
} bspplane;

typedef struct
{
	vector *verts;
	int nv;
	bspplane plane;

	short roomnum;
	short facenum;
	sbyte subnum;

	int color;

}	bsppolygon;

typedef struct bspnode 
{
	ubyte type;
	bspplane plane;
	ushort node_facenum;
	ushort node_roomnum;
	sbyte node_subnum;
	
	bspnode  *front;
	bspnode  *back;

	list *polylist;
	int num_polys;
} bspnode;

typedef struct bsptree 
{
	list           *vertlist;
	list				*polylist;
	bspnode        *root;
} bsptree;

// Builds a bsp tree for the indoor rooms
void BuildBSPTree ();

// Runs a ray through the bsp tree
// Returns true if a ray is occludes
int BSPRayOccluded(vector *start, vector *end, bspnode *node);
int BSPReportStatus(vector *start, bspnode *node);

// Walks the BSP tree and frees up any nodes/polygons that we might be using
void DestroyBSPTree (bsptree *tree);

// Saves and BSP node to an open file and recurses with the nodes children
void SaveBSPNode (CFILE *outfile,bspnode *node);

// Loads a bsp node from an open file and recurses with its children
void LoadBSPNode (CFILE *infile,bspnode **node);

// Initializes some variables for the indoor bsp tree
void InitDefaultBSP ();



// Builds a bsp tree for a single room
void BuildSingleBSPTree (int roomnum);

// Reports the current mine's checksum
int BSPGetMineChecksum();

extern bsptree MineBSP;
extern int BSPChecksum;
extern ubyte BSP_initted;
extern ubyte UseBSP;

#endif


