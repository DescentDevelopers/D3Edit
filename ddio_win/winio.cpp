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
// Win32 IO System Main Library Interface
// ----------------------------------------------------------------------------
#include "DDAccess.h"

#include <stdlib.h>
#include <stdarg.h>

#include "pserror.h"
#include "pstring.h"
#include "Application.h"
#include "ddio_win.h"
#include "ddio.h"
#include "dinput.h"

//#include "forcefeedback.h"

bool DDIO_init = 0;
dinput_data DInputData;

// ----------------------------------------------------------------------------
//	Initialization and destruction functions
// ----------------------------------------------------------------------------

bool ddio_InternalInit(ddio_init_info *init_info) {
  oeWin32Application *obj = (oeWin32Application *)init_info->obj;
  LPDIRECTINPUT lpdi;
  HRESULT dires;

  ASSERT(!DDIO_init);

  //	Initialize DirectInput subsystem
  mprintf((0, "DI system initializing.\n"));

  if (obj->NT()) {
    // we are in NT, so only require DX3.0
    dires = DirectInputCreate((HINSTANCE)obj->m_hInstance, 0x0300, &lpdi, NULL);

    if (dires != DI_OK) {
      Error("Unable to DirectInput system (Requires at least DirectX 3.0 For NT) [DirectInput:%x]\n", dires);
    }
  } else {
    // we require DX6
    dires = DirectInputCreate((HINSTANCE)obj->m_hInstance, DIRECTINPUT_VERSION, &lpdi, NULL);

    if (dires != DI_OK) {
      Error("Unable to DirectInput system (Requires at least DirectX 6.0) [DirectInput:%x]\n", dires);
    }
  }

  DInputData.app = obj;
  DInputData.lpdi = lpdi;
  DInputData.hwnd = (HWND)obj->m_hWnd;

  DDIO_init = 1;

  return 1;
}

void ddio_InternalClose() {
  ASSERT(DDIO_init);

  //	//Close down forcefeedback
  //	ddio_ff_DetachForce();

  DInputData.lpdi->Release();
  DInputData.lpdi = NULL;
  DDIO_init = 0;

  mprintf((0, "DI system closed.\n"));
}

#ifdef _DEBUG
void ddio_DebugMessage(unsigned err, char *fmt, ...) {
  char buf[128];
  va_list arglist;

  va_start(arglist, fmt);
  Pvsprintf(buf, 128, fmt, arglist);
  va_end(arglist);

  mprintf((0, "DDIO: %s\n", buf));
  if (err) {
    mprintf((1, "DIERR %x.\n", err));
  }
}
#endif
