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
 

#ifdef MACINTOSH
#include <string.h>
#endif

#include "memory.h"
#include "bnode.h"
#include "room.h"
#include "mem.h"
#include "vecmat.h"
#include "terrain.h"
#include "room.h"
#include "findintersection.h"
#include "BOA.h"
#include "psrand.h"

bn_list BNode_terrain_list[8];
bool BNode_allocated = false;
bool BNode_verified = false;

//--  Priority Queue
class pq_item 
{
	public:
	pq_item(int node_index, int parent_node, float n_cost) 
	{
		node = node_index;
		p_node = parent_node;
		cost = n_cost; 
		next = NULL;
	}
	
	int node;
	int p_node;
	float cost;

	pq_item *next;
};

class bpq 
{
	pq_item *q_head;

	public:
	bpq() {q_head = NULL;}

	void push(pq_item *new_node) 
	{
		new_node->next = q_head;
		q_head = new_node;
	}
	
	pq_item *pop() 
	{
		pq_item *cur_item = q_head;
		pq_item *prev_item = NULL;
		pq_item *best_item = q_head;
		pq_item *best_prev_item = NULL;
	
		if(q_head == NULL) return NULL;

		while(cur_item != NULL) 
		{
			if(cur_item->cost < best_item->cost) 
			{

				best_prev_item = prev_item;
				best_item = cur_item;
			}

			prev_item = cur_item;
			cur_item = cur_item->next;
		}


		// Actually remove this item from the list
		if(best_item == q_head) 
		{
			q_head = best_item->next;
		} 
		else 
		{
			best_prev_item->next = best_item->next;
		}

		return best_item;
	}
};


int BNode_Path[MAX_BNODES_PER_ROOM];
int BNode_PathNumNodes;

void BNode_UpdatePathInfo(pq_item **node_list, int start, int end) 
{
	int cur_node = end;
	int i;

	BNode_PathNumNodes = 0;

//	mprintf((0, "start crash loop\n"));
	while(cur_node != -1) 
	{
		BNode_Path[BNode_PathNumNodes++] = cur_node;
		cur_node = node_list[cur_node]->p_node;
	}
//	mprintf((0, "end crash loop\n"));

	// Reverse the list (so it is what we want)
	for(i = 0; i < BNode_PathNumNodes>>1; i++)
	{
		int temp;

		temp = BNode_Path[i];
		BNode_Path[i] = BNode_Path[BNode_PathNumNodes - i - 1];
		BNode_Path[BNode_PathNumNodes - i - 1] = temp;
	}

/*	for(i = 0; i < BNode_PathNumNodes; i++)
	{
		mprintf((0, "Node %d\n", BNode_Path[i]));
	}
*/
}

// Ok to use Highest_room_index offset stuff
bool BNode_FindPath(int start_room, int i, int j, float rad)
{
	bpq PQPath;
	int counter;
	pq_item *start_node = new pq_item(i, -1, 0.0f);
	pq_item *cur_node;
	bool f_found = false;

//	mprintf((0, "++++++++++\nFind path from %d to %d in room %d\n", i, j, start_room));

	start_room = BOA_INDEX(start_room);

	pq_item **node_list;
	bn_list *bnlist = BNode_GetBNListPtr(start_room);

	ASSERT(bnlist);
	ASSERT(i >= 0 && i < bnlist->num_nodes && j >= 0 && j < bnlist->num_nodes);

	node_list = (pq_item **) mem_malloc(bnlist->num_nodes * sizeof(pq_item *));
	memset(node_list, 0, bnlist->num_nodes * sizeof(pq_item *));

	PQPath.push(start_node);

	while(cur_node = PQPath.pop()) 
	{
		node_list[cur_node->node] = cur_node;	

		if(cur_node->node == j) 
		{
			BNode_UpdatePathInfo(node_list, i, j);
			f_found = true;
			goto done;
		}

		int num_edges;

		num_edges = bnlist->nodes[cur_node->node].num_edges;

		for(counter = 0; counter < num_edges; counter++) 
		{
			int next_node;
			pq_item *list_item;
			float new_cost;	

//			if(!BOA_PassablePortal(cur_node->roomnum, counter, false, false))
//				continue;

			if(next_node = bnlist->nodes[cur_node->node].edges[counter].end_room != start_room)
				continue;

			next_node = bnlist->nodes[cur_node->node].edges[counter].end_index;

			ASSERT(bnlist->nodes[cur_node->node].edges[counter].cost > 0);
			new_cost = cur_node->cost + bnlist->nodes[cur_node->node].edges[counter].cost;

			list_item = node_list[next_node];

			if(list_item != NULL && list_item->cost < new_cost) 
				continue;

			if(list_item == NULL)
			{
				list_item = new pq_item(next_node, cur_node->node, new_cost);

				node_list[next_node] = list_item;
				PQPath.push(list_item);
			}
			else 
			{
				list_item->cost = new_cost;
				list_item->p_node = cur_node->node;
			}
		}
	}

done:
	for(counter = 0; counter < bnlist->num_nodes; counter++) 
	{
		if (node_list[counter]) delete node_list[counter];
	}

	mem_free(node_list);	//DAJ LEAKFIX
	return f_found;
}


char BNode_vis[MAX_BNODES_PER_ROOM];
#define VIS_NO_CHECK 2
#define VIS_OK 1
#define VIS_NO 2


bn_list *BNode_GetBNListPtr(int roomnum, bool f_in_load_level)
{
	if(roomnum == -1)
	{
		return NULL;
	}
	else if(roomnum >= 0 && roomnum <= Highest_room_index)
	{
//		if(!f_in_load_level)
//		{
//			ASSERT(!(Rooms[roomnum].flags & RF_EXTERNAL));
//		}

		if(!Rooms[roomnum].used)
		{
			return NULL;
		}

		room *rp = &Rooms[roomnum];
		return &rp->bn_info;
	}
	else if(ROOMNUM_OUTSIDE(roomnum))
	{
		return &BNode_terrain_list[TERRAIN_REGION(roomnum)];
	}
	else if(roomnum <= Highest_room_index + 8)
	{
		return &BNode_terrain_list[roomnum - Highest_room_index - 1];
	}

	return NULL;
}

void BNode_ClearBNodeInfo(void)
{
	int i, j;

	for(i = 0; i < 8; i++)
	{
		if(BNode_allocated)
		{
			for(j = 0; j < BNode_terrain_list[i].num_nodes; j++) {
				if(BNode_terrain_list[i].nodes[j].num_edges)
				{
					mem_free(BNode_terrain_list[i].nodes[j].edges);
				}
			}
			mem_free(BNode_terrain_list[i].nodes);
		}

		BNode_terrain_list[i].num_nodes = 0;
		BNode_terrain_list[i].nodes = NULL;
	}

	BNode_allocated = false;
	BNode_verified = false;
}


void BNode_FreeRoom(room *rp)
{
	int i;

	for(i = 0; i < rp->bn_info.num_nodes; i++)
	{
		if(rp->bn_info.nodes[i].num_edges)
		{
			mem_free(rp->bn_info.nodes[i].edges);
		}
	}

	if(rp->bn_info.num_nodes)
	{
		mem_free(rp->bn_info.nodes);
		rp->bn_info.nodes = NULL;
		rp->bn_info.num_nodes = 0;
	}
}

void BNode_RemapTerrainRooms(int old_hri, int new_hri)
{
	int delta = new_hri - old_hri;
	int i;

	if(!BNode_allocated)
		return;
	
	if(delta == 0)
		return;

	if(new_hri < 0)
		return;

	ASSERT(delta <= 1);

	for(i = 0; i <= new_hri + BOA_num_terrain_regions; i++)
	{

		if((i <= new_hri && Rooms[i].used) || (i > new_hri))
		{
			int j;
			int k;

			//Skip external rooms
			if ((i <= new_hri) && (Rooms[i].flags & RF_EXTERNAL))
				continue;
 
			bn_list *bnlist = BNode_GetBNListPtr(i);
			ASSERT(bnlist);

			for(j = 0; j < bnlist->num_nodes; j++)
			{
				for(k = 0; k < bnlist->nodes[j].num_edges; k++)
				{
					if(bnlist->nodes[j].edges[k].end_room >= new_hri)
					{
						bnlist->nodes[j].edges[k].end_room += delta;
					}
				}
			}
		}
	}
}