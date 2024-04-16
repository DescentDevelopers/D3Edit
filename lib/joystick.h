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

#ifndef JOYSTICK_H
#define JOYSTICK_H

//	joystick ids.  used to initialize a stick and get its position
#ifdef MACINTOSH
#define MAX_JOYSTICKS 1
#define JOYPOV_NUM 1
#else
#define MAX_JOYSTICKS 8
#define JOYPOV_NUM 4
#endif

//	these flags tell what axes these controllers control.
#define JOYFLAG_XVALID 1
#define JOYFLAG_YVALID 2
#define JOYFLAG_ZVALID 4
#define JOYFLAG_RVALID 8
#define JOYFLAG_UVALID 16
#define JOYFLAG_VVALID 32
#define JOYFLAG_POVVALID 64
#define JOYFLAG_POV2VALID 128
#define JOYFLAG_POV3VALID 256
#define JOYFLAG_POV4VALID 512

//	set in joystate.pov
#define JOYPOV_DIR 8
#define JOYPOV_MAXVAL 0x100
#define JOYPOV_UP 0
#define JOYPOV_RIGHT 0x40
#define JOYPOV_DOWN 0x80
#define JOYPOV_LEFT 0xc0
#define JOYPOV_CENTER 0xff

#define JOYAXIS_RANGE 256

typedef int tJoystick;

#define JOYSTICK_1 0
#define JOYSTICK_2 1
#define JOYSTICK_3 2
#define JOYSTICK_4 3
#define JOYSTICK_5 4
#define JOYSTICK_6 5
#define JOYSTICK_7 6
#define JOYSTICK_8 7

typedef struct tJoyInfo {
  char name[128];
  unsigned axes_mask;
  unsigned num_btns;
  int minx, maxx;
  int miny, maxy;
  int minz, maxz;
  int minr, maxr;
  int minu, maxu;
  int minv, maxv;
} tJoyInfo;

//	shared between joystick remote server and local client.
#define JOY_PORT 3192
#define JOY_REQTERM "RTRM"
#define JOY_TERM "TERM"
#define JOY_POS "POSI"
#define JOY_INFO "INFO"
#define JOY_POLL "POLL"

typedef struct tJoyPacket {
  char coda[4]; // used to identify packet
  char buf[128];
} tJoyPacket;

typedef struct tJoyPos {
  int x;
  int y;
  int z;
  int r;
  int u;
  int v;
  unsigned buttons;
  unsigned btn;
  unsigned pov[JOYPOV_NUM];
} tJoyPos;

//	joystick system initialization
bool joy_Init(bool emulation);
void joy_Close();

//	retreive information about joystick.
void joy_GetJoyInfo(tJoystick joy, tJoyInfo *info);

//	retreive position of joystick
void joy_GetPos(tJoystick joy, tJoyPos *pos);

//	retreive uncalibrated position of joystick
void joy_GetRawPos(tJoystick joy, tJoyPos *pos);

//	returns true if joystick valid
bool joy_IsValid(tJoystick joy);

// run by ddio_Frame
void ddio_InternalJoyFrame();

// DAJ Added to support InSprocket
#ifdef MACINTOSH
void ddio_InternalJoySuspend(void);
void ddio_InternalJoyResume(void);
#endif
#endif
