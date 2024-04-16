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
#ifndef LIST_H
#define LIST_H

#include "pstypes.h"
#include "pserror.h"

typedef struct listnode {
  void *data;
  struct listnode *next;
  struct listnode *prev;
} listnode, list;

// Allocates space for a new list node
listnode *NewListNode(void);

// Adds an item to a list
int AddListItem(list **listp, void *item);

// Removes an item from a list
int RemoveListItem(list **listp, void *item);

// Destroys all the nodes in a list
// The items must be freed in another routine
void DestroyList(list **listp);

// Returns the number of items in a list
int CountListItems(list **listp);

// returns a pointer the given item index in a list
// Returns NULL if point not found
void *GetListItem(list **listp, int index);

// Returns how far from the head of the list a given item is
// Returns -1 if not found
int GetListItemIndex(list **listp, void *item);

#endif