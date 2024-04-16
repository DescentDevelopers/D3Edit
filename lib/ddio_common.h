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
 

#ifndef DDIO_COMMON_H
#define DDIO_COMMON_H

#include "pstypes.h"


class oeApplication;

#define DDIO_MOUSE_LITE			2					// some ddio systems support the 'lite' extension of mice.

typedef struct ddio_init_info {
	oeApplication *obj;								// App object used to initialize to IO system
	bool use_lo_res_time;
	bool key_emulation;								// keyboard emulation
	bool joy_emulation;								// joystick emulation
} ddio_init_info;


// ----------------------------------------------------------------------------
//	Keyboard Initialization and destruction functions
// ----------------------------------------------------------------------------

//	Initializes DDIO system
bool ddio_Init(ddio_init_info *init_info);
void ddio_Close();

//	suspends ddio input system
void ddio_Suspend();
void ddio_Resume();

// performs io per frame.
void ddio_Frame();

//	initializes keyboard
bool ddio_KeyInit(ddio_init_info *init_info);

//	closes keyboard
void ddio_KeyClose();

//	Handles keyboard queue management(TAKES ADJUSTED KEY VALUES)
void ddio_AddKeyToQueue(int key);

//	Updates timing info for keys
void ddio_UpdateKeyState(int key, bool isdown);

//	given a key code defined below, returns time in seconds since last call.
float ddio_KeyDownTime(int key);

//	return number of times a key's been down since last call.
int ddio_KeyDownCount(int key);

//	returns the state of an ADJUSTED KEY VALUE
bool ddio_GetAdjKeyState(int adj_key);

//	flush keyboard queue
void ddio_KeyFlush();

// flushes an individual key's timing values.
void ddio_KeyFlushKey(int key);

//	gets ADJUSTED KEY from queue
int ddio_KeyInKey();

//	determine if there are ADJUSTED keys in keyqueue
int ddio_KeyPeek();

//	handle input of keyboard per frame.
bool ddio_KeyFrame();

//	converts keycode to ASCII
int ddio_KeyToAscii(int code);

//	converts ascii code to key
int ddio_AsciiToKey(int ascii);


// sets type of keyboard to emulate
#define KBLANG_AMERICAN		0
#define KBLANG_BRITISH		1
#define KBLANG_FRENCH		2
#define KBLANG_GERMAN		3

void ddio_SetKeyboardLanguage(int language);


// ----------------------------------------------------------------------------
//	SERIAL CONSTANTS AND FUNCTIONS
// ----------------------------------------------------------------------------
// serial port data type
typedef void *tSerialPort;

// takes port number 1-4, returns a port object
tSerialPort ddio_SerialOpenPort(int port_number, int baud);

// takes port structure and frees it.
void ddio_SerialClosePort(tSerialPort port);

// writes one byte.  true return value means it worked.
bool ddio_SerialWriteByte(tSerialPort port, ubyte b);

// ----------------------------------------------------------------------------
//	KEYBOARD CONSTANTS
// ----------------------------------------------------------------------------

//	array of key states.
extern volatile short DDIO_key_down_count[];
extern volatile ubyte DDIO_key_state[];

#define KEY_STATE(_c) DDIO_key_state[_c]
#define DDIO_MAX_KEYS		256

//	masks used to specify current keycode state matched with scancode
#define KEY_SHIFTED     0x100
#define KEY_ALTED       0x200
#define KEY_CTRLED      0x400
#define KEY_DEBUGGED	0x800


//	used when defining a system code to use in KeyUpdateState
//	masks
#define KEY_STATE_DOWN		0x80000000
#define KEY_STATE_SYSTEM	0x40000000

//	codes
#define KEY_0           0x0B
#define KEY_1           0x02
#define KEY_2           0x03
#define KEY_3           0x04
#define KEY_4           0x05
#define KEY_5           0x06
#define KEY_6           0x07
#define KEY_7           0x08
#define KEY_8           0x09
#define KEY_9           0x0A
#define KEY_A           0x1E
#define KEY_B           0x30
#define KEY_C           0x2E
#define KEY_D           0x20
#define KEY_E           0x12
#define KEY_F           0x21
#define KEY_G           0x22
#define KEY_H           0x23
#define KEY_I           0x17
#define KEY_J           0x24
#define KEY_K           0x25
#define KEY_L           0x26
#define KEY_M           0x32
#define KEY_N           0x31
#define KEY_O           0x18
#define KEY_P           0x19
#define KEY_Q           0x10
#define KEY_R           0x13
#define KEY_S           0x1F
#define KEY_T           0x14
#define KEY_U           0x16
#define KEY_V           0x2F
#define KEY_W           0x11
#define KEY_X           0x2D
#define KEY_Y           0x15
#define KEY_Z           0x2C
#define KEY_MINUS       0x0C
#define KEY_EQUAL       0x0D
#define KEY_SLASH			0x35		//was KEY_DIVIDE in Descent & D2
#define KEY_BACKSLASH	0x2B		//was KEY_SLASH in Descent and D2
#define KEY_BSLASH_UK	0x56		//UK keyboards have diffent backslash scan code
#define KEY_COMMA       0x33
#define KEY_PERIOD      0x34
#define KEY_SEMICOL     0x27
#define KEY_LBRACKET    0x1A
#define KEY_RBRACKET    0x1B
#define KEY_RAPOSTRO    0x28
#define KEY_LAPOSTRO    0x29
#define KEY_ESC         0x01
#define KEY_ENTER       0x1C
#define KEY_BACKSP      0x0E
#define KEY_TAB         0x0F
#define KEY_SPACEBAR    0x39
#define KEY_NUMLOCK     0xC5
#define KEY_SCROLLOCK   0x46
#define KEY_CAPSLOCK    0x3A
#define KEY_LSHIFT      0x2A
#define KEY_RSHIFT      0x36
#define KEY_LALT        0x38
#define KEY_RALT        0xB8
#define KEY_LCTRL       0x1D
#define KEY_RCTRL       0x9D

#define KEY_F1          0x3B
#define KEY_F2          0x3C
#define KEY_F3          0x3D
#define KEY_F4          0x3E
#define KEY_F5          0x3F
#define KEY_F6          0x40
#define KEY_F7          0x41
#define KEY_F8          0x42
#define KEY_F9          0x43
#define KEY_F10         0x44
#define KEY_F11         0x57
#define KEY_F12         0x58

#define KEY_PAD0        0x52
#define KEY_PAD1        0x4F
#define KEY_PAD2        0x50
#define KEY_PAD3        0x51
#define KEY_PAD4        0x4B
#define KEY_PAD5        0x4C
#define KEY_PAD6        0x4D
#define KEY_PAD7        0x47
#define KEY_PAD8        0x48
#define KEY_PAD9        0x49
#define KEY_PADMINUS    0x4A
#define KEY_PADPLUS     0x4E
#define KEY_PADPERIOD   0x53
#define KEY_PADDIVIDE   0xB5
#define KEY_PADMULTIPLY 0x37
#define KEY_PADENTER    0x9C

#define KEY_INSERT      0xD2
#define KEY_HOME        0xC7
#define KEY_PAGEUP      0xC9
#define KEY_DELETE      0xD3
#define KEY_END         0xCF
#define KEY_PAGEDOWN    0xD1
#define KEY_UP          0xC8
#define KEY_DOWN        0xD0
#define KEY_LEFT        0xCB
#define KEY_RIGHT       0xCD
#define KEY_PRINT_SCREEN	0xB7
#define KEY_PAUSE			0x45


#define KEY_CMD			0xE0 //DAJ mac command key

#endif

