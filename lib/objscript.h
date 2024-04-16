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
 


#ifndef OBJSCRIPT_H
#define OBJSCRIPT_H

#include "pstypes.h"
#include "d3x_op.h"
#include "vecmat.h"

struct object;
struct trigger;


//	assigns scripts for a level.
void AssignScriptsForLevel();

//	free scripts for a level
void FreeScriptsForLevel();

//allocates and initializes the scripts for an object.
void InitObjectScripts(object *objp,bool do_evt_created=true);

//frees all scripts for an object.
void FreeObjectScripts(object *objp,bool level_end=false);

//allocates and initializes the scripts for a trigger.
void InitTriggerScript(trigger *tp);

//frees all scripts for an trigger.
void FreeTriggerScript(trigger *tp,bool level_end=false);

//@@// called to reinitialize an object's 'state' given the current script element of object.
//@@//	refuses to call EVT_CREATED too.  this just restores the state of a script given the current script_info
//@@// op is the object where the script will be assigned.  the script should already be freed and ready
//@@void ReinitObjectScripts(object *op, script_info *script, int mem_size, vector *mem);
//@@
//@@// called to reinitialize a trigger's 'state' given the current script element of trigger.
//@@//	refuses to call EVT_CREATED too.  this just restores the state of a script given the current script_info
//@@// tp is the trogger where the script will be assigned.  the script should already be freed and ready
//@@void ReinitTriggerScripts(trigger *tp, script_info *script, int mem_size, vector *mem);


#endif