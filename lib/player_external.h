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

#ifndef __PLAYER_EXTERNAL_H_
#define __PLAYER_EXTERNAL_H_

#define N_PLAYER_GUNS 8

// Initial player stat values
#define INITIAL_ENERGY 100  // 100% energy to start
#define INITIAL_SHIELDS 100 // 100% shields to start

#define MAX_ENERGY 200 // go up to 200
#define MAX_SHIELDS 200

// Observer modes
#define OBSERVER_MODE_ROAM 0
#define OBSERVER_MODE_PIGGYBACK 1

// Values for special flags
#define PLAYER_FLAGS_INVULNERABLE 1          // Player is invincible
#define PLAYER_FLAGS_DYING 4                 // Is this player in the middle of dying?
#define PLAYER_FLAGS_DEAD 8                  //	The player is just sitting there dead.
#define PLAYER_FLAGS_UNUSED 16               // ????
#define PLAYER_FLAGS_UNUSED1 32              // ????
#define PLAYER_FLAGS_UNUSED2 64              // ????
#define PLAYER_FLAGS_UNUSED3 128             // ????
#define PLAYER_FLAGS_UNUSED4 256             // ????
#define PLAYER_FLAGS_UNUSED5 512             // ????
#define PLAYER_FLAGS_UNUSED6 1024            // ????
#define PLAYER_FLAGS_AFTERBURNER 4096        // Player has an afterburner
#define PLAYER_FLAGS_HEADLIGHT 8192          // Player has headlight boost
#define PLAYER_FLAGS_HEADLIGHT_STOLEN 16384  // is the headlight stolen?
#define PLAYER_FLAGS_AFTERBURN_ON 32768      // Player afterburner is engaged
#define PLAYER_FLAGS_CUSTOM_TEXTURE 65536    // Player has a custom texture
#define PLAYER_FLAGS_THRUSTED (1 << 17)      // Player has thrusted this frame
#define PLAYER_FLAGS_BULLSEYE (1 << 18)      // Bullseye reticle should light up
#define PLAYER_FLAGS_ZOOMED (1 << 19)        // Bullseye reticle should light up
#define PLAYER_FLAGS_REARVIEW (1 << 20)      // Play is using rearview
#define PLAYER_FLAGS_SEND_MOVEMENT (1 << 21) // We need to tell the server about our movement
#define PLAYER_FLAGS_PLAYSOUNDMSGFORINVULN                                                                             \
  (1 << 22) // A sound and hud message should be displayed when invulnerability wears off

// Variables for weapon_fire_flags
#define WFF_SPRAY 1   // a spray weapon is firing
#define WFF_ON_OFF 2  // an on/off weapon is firing
#define WFF_FIRED 128 // fired this frame

// Define the two player weapons
#define PW_PRIMARY 0
#define PW_SECONDARY 1

// These are used to mask out various controls, put in initially for the training system
#define PCBF_FORWARD 1
#define PCBF_REVERSE 2
#define PCBF_LEFT 4
#define PCBF_RIGHT 8
#define PCBF_UP 16
#define PCBF_DOWN 32
#define PCBF_PITCHUP 64
#define PCBF_PITCHDOWN 128
#define PCBF_HEADINGLEFT 256
#define PCBF_HEADINGRIGHT 512
#define PCBF_BANKLEFT 1024
#define PCBF_BANKRIGHT 2048
#define PCBF_PRIMARY 4096
#define PCBF_SECONDARY 8192
#define PCBF_AFTERBURNER 16384

#endif