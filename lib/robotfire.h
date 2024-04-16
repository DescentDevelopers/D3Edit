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
#ifndef ROBOTFIRE_H_
#define ROBOTFIRE_H_

#include "robotfirestruct.h"
#include "objinfo.h"
#include "object.h"
#include "ship.h"

void FireOnOffWeapon(object *obj);

void WBSetupFireAnim(object *obj, otype_wb_info *static_wb, int wb_index);
void WBFireAnimFrame(object *obj, otype_wb_info *static_wb, int wb_index);

bool WBIsBatteryReady(object *obj, otype_wb_info *static_wb, int wb_index);
void WBFireBattery(object *obj, otype_wb_info *static_wb, int wb_index);
void WBFireBattery(object *obj, otype_wb_info *static_wb, int poly_wb_index, int dynamic_wb_index,
                   float damage_scalar = 1.0);

void WBClearInfo(object *obj);
void WBClearInfo(otype_wb_info static_wb[]);

void WBEnable(object *obj, int wb_index, bool f_enable);

#endif
