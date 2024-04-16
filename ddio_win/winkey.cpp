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
 



// ----------------------------------------------------------------------------
//	Keyboard Interface
// ----------------------------------------------------------------------------
#include "DDAccess.h"

#include "pserror.h"
#include "mono.h"
#include "ddio.h"
#include "ddio_win.h"
#include "Application.h"
#include "TaskSystem.h"

#include <stdlib.h>
#include <process.h>


// ----------------------------------------------------------------------------
//	Local global data
// ----------------------------------------------------------------------------
#define	DIKEY_BUFFER_SIZE			32

static struct tWinKeyData
{
	LPDIRECTINPUTDEVICE lpdikey;					// key device
	HANDLE evtnotify;									// notify event
	HHOOK winhook;										// windows hook
	unsigned long thread;							// thread id
//	osMutex keyframe_mutex;							// mutex between internal key frame and key thread.
	bool nextframe;									// used for mutexing between keyframe and thread.
	bool acquired;										// device acquired?
	bool thread_active;								// used in thread.
	bool suspended;
}
WKD = { 
	NULL,
	NULL,
	NULL,
	0xffffffff,
	false,
	false,
	false,
	true
};

volatile struct tWinKeys
{
	union {
		DWORD up_ticks;								// windows ticks when key went up last
		float up_time;
	};
	union {
		DWORD down_ticks;								// windows ticks when key went down last
		float down_time;
	};
	bool status;										// is it down?
	bool mutex_flag;									// done for mutexing between ddio_Internal and KeyThread
	ushort mutex_data;
}
WKeys[DDIO_MAX_KEYS];


static		int				DDIO_key_language = KBLANG_AMERICAN;


///////////////////////////////////////////////////////////////////////////////
//	Initializes DirectInputDevice keyboard if we are under Win9x or at least NT5
//	we set the cooperative level, etc.
LPDIRECTINPUTDEVICE dikey_Init(LPDIRECTINPUT lpdi, HWND hwnd);

//	Shutsdown DirectInputDevice keyboard if passed device is valid.
void dikey_Shutdown(LPDIRECTINPUTDEVICE lpdikey);

// sets up preemptive keyboard handling.
HANDLE dikey_EnableNotify(LPDIRECTINPUTDEVICE lpdikey);

//	disables event based notification.
bool dikey_DisableNotify(LPDIRECTINPUTDEVICE lpdikey, HANDLE evthandle);

//	acquires or unacquires device
// returns device acquisition state.
bool dikey_Acquire(LPDIRECTINPUTDEVICE lpdikey, bool acquire);

// emulated keyboard functionality
bool ddio_Win_KeyInit();
void ddio_Win_KeyClose();

int ddio_KeyHandler(HWnd wnd, unsigned msg, unsigned wParam, long lParam);

void CALLBACK key_TimerProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
LRESULT CALLBACK KeyboardProc( int code, WPARAM wParam, LPARAM lParam);

// DirectInput Keyboard Thread
void __cdecl dikey_Thread(void *dp);

// translates scan code to foreign equivs.
ubyte xlate_scancode(ubyte scan_code);


///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
//	Initialization of keyboard device.
// ----------------------------------------------------------------------------

// this version will try to initialize a direct input keyboard device.  if it fails
// it falls back to the old keyboard hook (less reliable but works.)
bool ddio_InternalKeyInit(ddio_init_info *init_info)
{
	bool emulated = init_info->key_emulation;
	
	LPDIRECTINPUTDEVICE lpdikey = NULL;
	int i;

// reset key list
	for (i = 0; i < DDIO_MAX_KEYS; i++)
	{
		WKeys[i].down_ticks = 0;
		WKeys[i].up_ticks = 0;
		WKeys[i].status = false;
	}

// start init.
	if (!emulated) {
		lpdikey = dikey_Init(DInputData.lpdi, (HWND)DInputData.app->m_hWnd);
	}

retry_key_init:
	if (lpdikey) {
	//	direct input keyboard can work, so we initialize preemptive handling of the keyboard 
		HANDLE hevt = dikey_EnableNotify(lpdikey);

		if (hevt) {
		// event handling will work, so let's create the keyboard thread.
			bool acquired = dikey_Acquire(lpdikey, true);
			if (acquired) {
			//	create keyboard thread
				unsigned long thrid;
				WKD.thread_active = true;
				WKD.lpdikey = lpdikey;
				WKD.thread = 0;
				WKD.evtnotify = hevt;
				WKD.acquired = acquired;
				WKD.winhook = NULL;
				WKD.suspended = false;
				WKD.nextframe = false;
				thrid = _beginthread(dikey_Thread, 0, NULL);
				if (thrid == (unsigned long)(-1)) {
					mprintf((0, "DDIO: DI_Keyboard thread failed to initialize.\n"));
					WKD.thread_active = false;
					WKD.lpdikey = NULL;
					WKD.thread = 0xffffffff;
					WKD.evtnotify = NULL;
					WKD.acquired = false;
					WKD.winhook = NULL;
					WKD.suspended = false;
					acquired = dikey_Acquire(lpdikey, false);
					dikey_DisableNotify(lpdikey, hevt);
					dikey_Shutdown(lpdikey);
					lpdikey = NULL;
				}
				else {
				// success!  init data.
				// set priority of thread too.
					WKD.thread = thrid;
					if (SetThreadPriority((HANDLE)thrid, THREAD_PRIORITY_TIME_CRITICAL) == FALSE) {
						SetThreadPriority((HANDLE)thrid, THREAD_PRIORITY_HIGHEST);
					}
					mprintf((0, "DDIO: DI_Keyboard initialized.\n"));
				}
			}
			else {
			// failed to acquire device? can't do.
				dikey_DisableNotify(lpdikey, hevt);
				dikey_Shutdown(lpdikey);
				lpdikey = NULL;
			}
		}
		else {
		// somehow event notification failed, can't do.
			dikey_Shutdown(lpdikey);
			lpdikey = NULL;
		}

		if (lpdikey == NULL) {
			goto retry_key_init;
		}
	}
	else {
	// here, initialize hook procedure.
		return ddio_Win_KeyInit();
	}

	return true;
}


//	this will shutdown direct input or the windows hook, whichever was chosen.
void ddio_InternalKeyClose()
{
	if (WKD.lpdikey) {
	// deactivate thread and free it, then unacquire device, disable event notification, and shutdown!
		WKD.thread_active = false;
		SetEvent(WKD.evtnotify);
		Sleep(500);
		WKD.acquired = dikey_Acquire(WKD.lpdikey, false);
		dikey_DisableNotify(WKD.lpdikey, WKD.evtnotify);
		dikey_Shutdown(WKD.lpdikey);
		WKD.thread = 0xffffffff;
		WKD.evtnotify = NULL;
		WKD.lpdikey = NULL;
		mprintf((0, "DDIO: DI_Keyboard shutdown.\n"));
	}
	if (WKD.winhook) {
		ddio_Win_KeyClose();
	}
}


// handled internally if keyboard system needs additional processing per frame
void ddio_InternalKeyFrame()
{
}


//////////////////////////////////////////////////////////////////////////////
// Miscellaneous API
//////////////////////////////////////////////////////////////////////////////

                                                                              
// returns if key is up or down
bool ddio_InternalKeyState(ubyte key)
{
	return WKeys[key].status;
}


float ddio_InternalKeyDownTime(ubyte key)
{
	float down_time = 0.0f;
	if (WKeys[key].status) {
		if (WKD.winhook) {
			float timer = timer_GetTime();
			down_time = timer - WKeys[key].down_time;
			WKeys[key].down_time = timer;
		}
		else {
			DWORD curtickcount = GetTickCount();
			DWORD ticks =  curtickcount - WKeys[key].down_ticks;
			if (ticks == 0) {
				//mprintf((0, "ticks=%d\n", ticks));
			}
			WKeys[key].down_ticks = curtickcount;
			down_time = (ticks/1000.0f);
		}
	}
	else {
		if (WKD.winhook) {
			down_time = WKeys[key].up_time - WKeys[key].down_time;
			WKeys[key].down_time = WKeys[key].up_time = 0.0f;
		}
		else {
			DWORD ticks = WKeys[key].up_ticks - WKeys[key].down_ticks;
			WKeys[key].down_ticks = 0;
			WKeys[key].up_ticks = 0;
			down_time = (ticks/1000.0f);
		}
	}

	return down_time;
}


// flush a key internally
void ddio_InternalResetKey(ubyte key)
{
	WKeys[key].down_ticks = 0;
	WKeys[key].up_ticks = 0;
	WKeys[key].status = false;
	WKeys[key].mutex_flag = false;
	WKeys[key].mutex_data = 0;
}


// sets type of keyboard to emulate
// #define KBLANG_AMERICAN		0
// #define KBLANG_BRITISH		1
// #define KBLANG_FRENCH		2
// #define KBLANG_GERMAN		3

void ddio_SetKeyboardLanguage(int language)
{
	DDIO_key_language = language;
}


// translates scan code to foreign equivs.
ubyte xlate_scancode(ubyte scan_code)
{
	ubyte code = scan_code;

	if (DDIO_key_language == KBLANG_FRENCH) {
		switch (scan_code) {
			case KEY_A:	code = KEY_Q; break;
			case KEY_M:	code = KEY_COMMA; break;
			case KEY_Q:	code = KEY_A; break;
			case KEY_W:	code = KEY_Z; break;
			case KEY_Z:	code = KEY_W; break;
			case KEY_SEMICOL:	code = KEY_M; break;
			case KEY_COMMA:	code = KEY_SEMICOL; break;
		}
	}
	else if (DDIO_key_language == KBLANG_GERMAN) {
		switch (scan_code) {
			case KEY_Y:	code = KEY_Z; break;
			case KEY_Z:	code = KEY_Y; break;
		}
	}
	else if (DDIO_key_language == KBLANG_BRITISH) {
		if ( scan_code == KEY_BSLASH_UK ) {	// KEY_SLASH_UK == 0x56
			code = KEY_SLASH;				// KEY_SLASH is really the backslash, 0x2B
		}
	}

	return code;
}



//////////////////////////////////////////////////////////////////////////////
//	DirectInput Functions
//////////////////////////////////////////////////////////////////////////////

inline bool IS_NT4_OR_LOWER()
{
	int maj,min;
	tWin32OS os = oeWin32Application::version(&maj,&min);
	return (os == WinNT && maj < 5) ? true : false;
}


//	Initializes DirectInputDevice keyboard if we are under Win9x or at least NT5
//	we set the cooperative level, etc.
LPDIRECTINPUTDEVICE dikey_Init(LPDIRECTINPUT lpdi, HWND hwnd)
{
	LPDIRECTINPUTDEVICE lpdikey;
	HRESULT hr;

	if (IS_NT4_OR_LOWER()) {
		return NULL;
	}

// see if we can get the keyboard device.
	hr = lpdi->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL);
	if (hr != DI_OK) {
		DDIO_MESSAGE((hr, "DI_Keyboard initialization failed."));
		return NULL;
	}

	hr = lpdikey->SetDataFormat(&c_dfDIKeyboard);
	if (hr != DI_OK) {
		DDIO_MESSAGE((hr, "DI_Keyboard data format specification failed."));
		lpdikey->Release();
		return NULL;
	}

   hr = lpdikey->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);	
	if (hr != DI_OK) {
		DDIO_MESSAGE((hr, "DI_Keyboard set cooperative level failed."));
		lpdikey->Release();
		return NULL;
	}

	return lpdikey;
}


//	Shutsdown DirectInputDevice keyboard if passed device is valid.
void dikey_Shutdown(LPDIRECTINPUTDEVICE lpdikey) 
{
	if (lpdikey) {
		lpdikey->Release();
	}
}


// sets up preemptive keyboard handling.
HANDLE dikey_EnableNotify(LPDIRECTINPUTDEVICE lpdikey)
{
	if (lpdikey) {
		HANDLE hEvt = CreateEvent(NULL, TRUE, FALSE, "DDIOKeyEvent");	
		HRESULT hr;
		DIPROPDWORD dipropdw = {
			{	
				sizeof(DIPROPDWORD),
				sizeof(DIPROPHEADER),
				0,
				DIPH_DEVICE,
			},
	   	DIKEY_BUFFER_SIZE,
		};
	
		if (!hEvt) {
			DDIO_MESSAGE((0, "DI_Keyboard failed to init system event."));
			return NULL;
		}

	// set event
		hr = lpdikey->SetEventNotification(hEvt);
		if (hr != DI_OK) {
			DDIO_MESSAGE((hr, "DI_Keyboard failed to set preemptive key event notification."));
			CloseHandle(hEvt);
			return NULL;
		}

	// set key buffer size
		hr = lpdikey->SetProperty(DIPROP_BUFFERSIZE, &dipropdw.diph);
		if (FAILED(hr)) {
			DDIO_MESSAGE((hr, "DI_keyboard buffering failed."));
			lpdikey->SetEventNotification(NULL);
			CloseHandle(hEvt);
			return NULL;
		}

		return hEvt;
	}

	return NULL;
}


//	disables event based notification.
bool dikey_DisableNotify(LPDIRECTINPUTDEVICE lpdikey, HANDLE evthandle)
{
	if (lpdikey) {
		lpdikey->SetEventNotification(NULL);
		CloseHandle(evthandle);
		return true;
	}

	return false;
}


//	acquires or unacquires device
// returns device acquisition state.
bool dikey_Acquire(LPDIRECTINPUTDEVICE lpdikey, bool acquire)
{
	HRESULT hr = acquire ? lpdikey->Acquire() : lpdikey->Unacquire();

	if (FAILED(hr)) {
		DDIO_MESSAGE((hr, "DI_keyboard acquire/unacquire fail."));
		return !acquire;
	}

	return acquire;
}


// DirectInput Keyboard Thread
void __cdecl dikey_Thread(void *dp)
{
	unsigned event_count = 0;

	GetAsyncKeyState(VK_PAUSE);					// this will tell if the 'pause' key is toggled
	
	while (WKD.thread_active)
	{
	// this thread will hold until the direct input key event has been signaled by the OS.
	//	after this, we will get all the keys in the io buffer and register them with the
	// key system.

		switch (WaitForSingleObject(WKD.evtnotify, INFINITE))
		{
		case WAIT_TIMEOUT:							// this shouldn't happen, but if it does, no big deal.
			break;
		case WAIT_ABANDONED:							// usually means calling thread quit.
			WKD.thread_active = false;
			break;
		case WAIT_OBJECT_0:							// event was signalled normally
			{
				DIDEVICEOBJECTDATA diobjdata[DIKEY_BUFFER_SIZE];
				DWORD diobjitems = DIKEY_BUFFER_SIZE;
				HRESULT hr;
			//	SHORT async_key_state;
				ubyte key;

				int i;
				
			// don't read if suspended!
				if (WKD.suspended) {
					break;
				}

				event_count++;

			// attempt acquisition if keyboard not already acquired
				if (!WKD.acquired) {
					WKD.acquired = dikey_Acquire(WKD.lpdikey, true);
				}
				if (WKD.acquired) {
					hr = WKD.lpdikey->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), diobjdata, &diobjitems, 0);
					if (SUCCEEDED(hr)) {
					// the pause is key under Windows seems to act kinda strange.  it's a toggle button
					// and USUALLY is preceeded by a KEY_LCTRL press.  If a pause toggle was indicated, flush the
					// keyboard and quit.

					//	note that dwOfs is the acutal key that is either down or up, and dwData tells us if
					//	it is up or down.  So place on key array, and in queue.
						for (i =0; i < (int)diobjitems; i++)
						{
							key = xlate_scancode((ubyte)(diobjdata[i].dwOfs));
							if (diobjdata[i].dwData & 0x80) {
								if (WKeys[key].status) {
									WKeys[key].up_ticks = 0;
								}
								WKeys[key].down_ticks = diobjdata[i].dwTimeStamp;
								WKeys[key].status = true;
								if (key == KEY_LCTRL) {
									WKeys[key].mutex_flag = true;
								}
								mprintf((0, "dkey=%x\n", key));
							}
							else {
								if (WKeys[key].status) {
									WKeys[key].up_ticks = diobjdata[i].dwTimeStamp;
									WKeys[key].status = false;
									mprintf((0, "ukey=%x\n", key));
								}
							}

							ddio_UpdateKeyState(key,WKeys[key].status);
						}
					}
					else {
						if (hr == DIERR_INPUTLOST) {
							WKD.acquired = dikey_Acquire(WKD.lpdikey, true);
						}
						else {
							DDIO_MESSAGE((hr, "DI_keyboard unable to read."));
						}
					}
				}
			}
			break;
		}

		ResetEvent(WKD.evtnotify);
	}

	DDIO_MESSAGE((0, "DI_Keyboard thread ended."));
}


void ddio_InternalKeySuspend()
{
	if (WKD.lpdikey && WKD.acquired) {
		WKD.acquired = dikey_Acquire(WKD.lpdikey, false);
	}
	WKD.suspended = true;
}


void ddio_InternalKeyResume()
{
	if (WKD.lpdikey && !WKD.acquired) {
		WKD.acquired = dikey_Acquire(WKD.lpdikey, true);
	}
	WKD.suspended = false;
}




//	Win32 non-threaded version

bool ddio_Win_KeyInit()
{
/*	Initialize hook handlers */
	WKD.winhook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, (HINSTANCE)DInputData.app->m_hInstance, GetCurrentThreadId());
	if (!WKD.winhook) {
		return false;
	}

	mprintf((0, "Keyboard initialized.\n"));

	return true;
}


void ddio_Win_KeyClose()
{
/*	Free up message handlers */
	if (WKD.winhook) {
		UnhookWindowsHookEx(WKD.winhook);
		WKD.winhook = NULL;
	}

	mprintf((0, "Keyboard released.\n"));
}


// ----------------------------------------------------------------------------
//	non DirectInput keyboard handler
// ----------------------------------------------------------------------------


LRESULT CALLBACK KeyboardProc( int code, WPARAM wParam, LPARAM lParam)
{
	int res;

	if (code < 0) {
		return CallNextHookEx(WKD.winhook, code, wParam, lParam);
	}

	if (lParam&0x80000000) 
		res = ddio_KeyHandler(	0, WM_KEYUP, wParam, lParam);
	else
		res = ddio_KeyHandler(	0, WM_KEYDOWN, wParam, lParam);

	return (!res);
}


int ddio_KeyHandler(HWnd wnd, unsigned msg, unsigned wParam, long lParam)
{
	ubyte scan_code;
	float timer = timer_GetTime();
	
	if (!WKD.winhook) 
		return 1;

	switch ((UINT)msg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		scan_code = (unsigned char )((lParam>>16) & 0xff);
		if (lParam & 0x01000000) 
			scan_code |= 0x80;

		scan_code = xlate_scancode(scan_code);

	//	print screen is a weird case.   only accept key ups.
		if (wParam != VK_SNAPSHOT) {
			if (!WKeys[scan_code].status) {
				WKeys[scan_code].up_time = 0;
				WKeys[scan_code].down_time = timer;
			}
			else {
				WKeys[scan_code].up_time = 0;
			}
			WKeys[scan_code].status = true;
			ddio_UpdateKeyState(scan_code, true);
		}
		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		scan_code = (unsigned char )((lParam>>16) & 0xff);
		if (lParam & 0x01000000) 
			scan_code |= 0x80;

		scan_code = xlate_scancode(scan_code);

	//	handle special keys.  print screen, we will simulate the keypress.
		if (wParam == VK_SNAPSHOT) {
			scan_code = KEY_PRINT_SCREEN;
			WKeys[scan_code].down_time = timer;
			WKeys[scan_code].status = true;
			ddio_UpdateKeyState(scan_code, true);
		}
		if (WKeys[scan_code].status) {
			WKeys[scan_code].status = false;
			WKeys[scan_code].up_time = timer;
			ddio_UpdateKeyState(scan_code, false);
		}
	
		break;
	}

	return 1;
}
