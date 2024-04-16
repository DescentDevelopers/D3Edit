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
 //
// AIGame3_External.h
// 
// ------------------
//
// This file provides a link between Dallas scripts and AIGame3.cpp


// Bot Communication packet
typedef struct
{
	char action;
	void *ptr;
} bot_com;


// Alien Organism Communication Constants
#define ALIEN_COM_HUNT_TO_OBJ				20
#define ALIEN_COM_SCAV_TO_OBJ				21

// Alien Boss Communication Constants
#define AB_COM_THRUSTER_IS_FIRING		0
#define AB_COM_THRUSTER_MISFIRED			1
#define AB_COM_SET_SCENARIO_IDS			2
#define AB_COM_IS_NESTING					3
#define AB_COM_THRUSTER_IGNITED			4
#define AB_COM_ITS_SHOWTIME				5
#define AB_COM_START_WAITING_EFFECT		6

// Security Camera Communication Constants
#define SC_COM_GET_ALERT_STATUS			0

// Crowd Control Communication Constants
#define CC_COM_SET_DATA						0
#define CC_COM_DISABLE_CHECK				1

// Alien Boss Scenario ID Packet
typedef struct
{
	int nest_handle;
	int left_hide_room;
	int right_hide_room;
} ab_scenario_ids;

// Crowd Control Packet
typedef struct
{
	int follow_handle;
	float stop_dist;
	float slowdown_offset;
} cc_packet;

// Sends a command out to a robot
bool SendCommand(int me, int it, char command, void *ptr)
{
	bot_com com;

	com.action = command;
	com.ptr = ptr;

	tOSIRISEventInfo ei;

	ei.me_handle = it;
	ei.extra_info = (void *)&com;
	ei.evt_ai_notify.notify_type = AIN_USER_DEFINED;
	ei.evt_ai_notify.it_handle = me;

	return Obj_CallEvent(it, EVT_AI_NOTIFY, &ei);
}


// =======================================================================
// Copy and Paste the following into the custom section of a Dallas script
// =======================================================================


/*
bool qSecurityCameraAlerted(int obj_handle)
{
	bool camera_alerted;

	SendCommand(obj_handle,obj_handle,SC_COM_GET_ALERT_STATUS,&camera_alerted);

	return camera_alerted;
}
*/


/*
$$ACTION
Custom
Tell [o:Alien Organism] to hunt to [o:Destination Object]
aAlienOrganismHunt
Tell Alien Organism to hunt to Destination Object
Causes an alien organism (and possibly its squad) to go hunting toward a particular object.

Parameters:
  Alien Organism: the alien that should go hunting
  Destination Object: the object to hunt towards
$$END
*/
/*
void aAlienOrganismHunt(int alien_handle, int dest_handle)
{
	SendCommand(alien_handle,alien_handle,ALIEN_COM_HUNT_TO_OBJ,&dest_handle);
}
*/


/*
$$ACTION
Custom
Tell [o:Alien Organism] to scavenge to [o:Destination Object]
aAlienOrganismScav
Tell Alien Organism to scavenge to Destination Object
Causes an alien organism (and possibly its squad) to go scavenging toward a particular object.

Parameters:
  Alien Organism: the alien that should go scavenging
  Destination Object: the object to scavenge towards
$$END
*/
/*
void aAlienOrganismScav(int alien_handle, int dest_handle)
{
	SendCommand(alien_handle,alien_handle,ALIEN_COM_SCAV_TO_OBJ,&dest_handle);
}
*/