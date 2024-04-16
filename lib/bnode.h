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
 

#ifndef BNODE_H_
#define BNODE_H_

#include "vecmat_external.h"

#define MAX_BNODE_SIZE 20.0f
// Not bigger than 127 - char bnode - in portal struct
#define MAX_BNODES_PER_ROOM 127

typedef struct bn_edge
{
	short end_room;
	char end_index;
		
	short flags;
	short cost;
	
	float max_rad;
} bn_edge;

typedef struct bn_node
{
	vector pos;
	int num_edges;
	bn_edge *edges;
} bn_node;

typedef struct bn_list
{
	int num_nodes;
	bn_node *nodes;
} bn_list;

struct room;

extern void BNode_FreeRoom(room *rp);
extern void BNode_ClearBNodeInfo(void);

bn_list *BNode_GetBNListPtr(int roomnum, bool f_in_load_level = false);

extern bn_list BNode_terrain_list[8];
extern bool BNode_allocated;
extern bool BNode_verified;
void BNode_RemapTerrainRooms(int old_hri, int new_hri);

extern int BNode_Path[MAX_BNODES_PER_ROOM];
extern int BNode_PathNumNodes;
extern bool BNode_FindPath(int start_room, int i, int j, float rad);
extern int BNode_FindDirLocalVisibleBNode(int roomnum, vector *pos, vector *fvec, float rad);
extern int BNode_FindClosestLocalVisibleBNode(int roomnum, vector *pos, float rad);

#endif