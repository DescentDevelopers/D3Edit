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
 

#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "pstypes.h"
#include "CFILE.H"

struct object;

#define MAX_UNIQUE_INVEN_ITEMS	10

#define INVF_SELECTABLE		0x0003	//old 1
#define INVF_USEABLE		0x0003	//old 2
#define INVF_MISSIONITEM	0x0004	//this item lasts across levels
#define INVF_NOREMOVEONUSE	0x0008
#define INVF_VISWHENUSED	0x0010
#define INVF_OBJECT			0x0020	//this item isn't a type/id...but an objhandle
#define INVF_NOTSPEWABLE	0x0040	//this object should not spew...stay in inventory after death
#define INVF_TIMEOUTONSPEW	0x0080	//this object/item times out when it's spewed

// Inventory reset stage settings
#define INVRESET_ALL			0 
#define INVRESET_LEVELCHANGE	1
#define INVRESET_DEATHSPEW		2

typedef struct
{
	bool selectable;
	char *hud_name;
	int amount;
}tInvenList;

typedef struct tInvenInfo
{
	int count;
	char *description;
	char *icon_name;
	char *name;
	int flags;
	ushort iflags;					// Inventory item flags
	int type;
	int id;	
}tInvenInfo;

typedef struct inven_item
{

	int	type;				// what type of object this is... robot, weapon, hostage, powerup, fireball
								// if INVF_OBJECT, this is the object handle
	int	otype;					//countermeasure powerup type
	int	id;						// which form of object...which powerup, robot, etc.
								// if INVF_OBJECT, this is -1
	int	oid;					//countermeasure powerup id
	int	flags;					// misc flags
	ushort	pad2;					// keep alignment

	int count;					//how many of this type/id (not INVF_OBJECT)

	char *description;
	char *icon_name;
	char *name;
	
	ushort iflags;					// Inventory item flags
	
	inven_item *next,*prev;			//pointer to next inventory item
}inven_item;

class Inventory 
{
public:
	Inventory();
	~Inventory();
	//adds a type/id item to the inventory (returns true on success)
	bool Add(int type,int id,object *parent=NULL,int aux_type=-1,int aux_id=-1,int flags=0,char *description=NULL);
	//adds an object to the inventory (marked by it's objhandle)
	bool AddObject(int object_handle,int flags=0,char *description=NULL);
	//adds a special cased CounterMeasure into the inventory
	bool AddCounterMeasure(int id,int aux_type=-1,int aux_id=-1,int flags=0,char *description=NULL);
	//removes an item from the inventory (reduces it's count by one...if there is no more, then it goes bye-bye)
	bool Remove(int type,int id=-1);
	//uses an item in the inventory (also reduces its count by one...if there is no more, then it goes bye-bye)
	bool Use(int type,int id,object *parent=NULL);
	bool Use(int objhandle,object *parent=NULL);
	//returns how many unique type/ids are in the inventory
	int Size(void);
	//returns true if there is an item in the inventory with the given type/id (or objhandle if id is -1)
	bool CheckItem(int type,int id=-1);
	//Resets the inventory, cleaning it out
	//in_game: set to true if this is being called from during gameplay
	// reset_stage:
	//		INVRESET_ALL:			Reset _EVERYTHING_
	//		INVRESET_LEVELCHANGE:	Remove everything except those that last across levels
	//		INVRESET_DEATHSPEW:		Remove everything except those that do not spew (Default)
	void Reset(bool in_game,int reset_stage=INVRESET_DEATHSPEW);
	//resets the position pointer in the list to the beginning
	void ResetPos(void);
	//moves the position pointer to the next inventory item
	void NextPos(bool skip=false);
	//moves the position pointer to the previous inventory item
	void PrevPos(bool skip=false);
	//returns the type/id of the item at the current position
	//return true if it is a real object
	bool GetPosTypeID(int &type,int &id);
	//returns the aux type/id of the item
	//return true if it is a real object
	bool GetAuxPosTypeID(int &type,int &id);
	//returns the description of the item at the current position 
	char *GetPosDescription(void);
	//returns the icon name of the item at the current position
	char *GetPosIconName(void);
	//returns the name of the item at the current position
	char *GetPosName(void);
	//return information about the current position item
	//return true if it is a real object
	bool GetPosInfo(ushort &iflags,int &flags);
	//returns the count of the item at the current position
	int GetPosCount(void);
	//returns true if the position pointer is at the begining of the inventory list
	bool AtBeginning(void);
	//returns false if the position pointer is at the end of the inventory list
	bool AtEnd(void);
	//jump right to an item in the inventory
	void GotoPos(int newpos);
	void GotoPos(int type,int id);
	//uses the currently selected item
	bool UsePos(object *parent=NULL);
	//returns the 'index' position of the current position
	int GetPos(void);
	//checks the pos, if its on a nonselectable item it will move to the next selectable (NULL if none)
	void ValidatePos(bool forward=true);
	//returns whether an item is selectable
	bool IsSelectable(void);
	bool IsUsable(void);
	//returns how many of an type/id is in the inventory
	int GetTypeIDCount(int type,int id);
	//searches the inventory for the specified type/id, sets the pos to it
	bool FindPos(int type,int id=-1);
	//saves the inventory to the file (returns number of bytes written)
	int SaveInventory(CFILE *file);
	//restores the inventory from file (returns number of bytes read)
	int ReadInventory(CFILE *file);
	//gets a detailed list of information about what is in the inventory
	//returns the number of items filled in.
	int GetInventoryItemList(tInvenList *list,int max_amount,int *cur_sel);
private:
	//adds an item to the inventory (returns true on success)
	bool AddObjectItem(int otype,int oid,int oauxt,int oauxi,int flags,char *description=NULL);
	void RemoveNode(inven_item *node);
	//sends a request to the server to use a particular item in the inventory
	void SendRequestToServerToUse(int type,int id=-1);
	inven_item *FindItem(int type,int id=-1);
	inven_item *root;
	int count;
	inven_item *pos;	//used when looking through inventory
};

void InventorySwitch(bool forward);
//moves to the next/prev item in the counter measures list (forward==TRUE means forward, forward==FALSE means go backwards)
void CounterMeasuresSwitch(bool forward);
// Checks for an object in any of the players inventorys and removes it 
void InventoryRemoveObject(int objhandle);


#endif
