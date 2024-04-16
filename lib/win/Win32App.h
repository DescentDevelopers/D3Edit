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

#ifndef WIN32APP_H
#define WIN32APP_H

#define MAX_MSG_FUNCTIONS 64

/*	Basic Application Win32 data types */
typedef unsigned int HWnd;
typedef unsigned int HInstance;

//	This structure is used to retrieve and set
typedef struct tWin32AppInfo {
  unsigned flags;                 // Application Flags
  HWnd hwnd;                      // Window Handle
  HInstance hinst;                // Window Instance
  int wnd_x, wnd_y, wnd_w, wnd_h; // Window dimensions
} tWin32AppInfo;

typedef enum tWin32OS { NoWin32, Win9x, WinNT, WinCE } tWin32OS;

/*	Win32 Application Object
                This object entails initialization and cleanup of all operating system
                elements, as well as data that libraries may need to initialize their
                systems.

        The Win32 Application object creates the application window and housekeeps
        the window and instance handle for the application.

        We also allow the option of setting these handles from outside the Application object.


tOEWin32MsgCallback:
        Callbacks return a 0 if we don't want to call the default action for the message, otherwise return 1
        Callbacks are executed in the Window's message procedure, so the calling program need not manually run
        the handler (although, I give you a function to do just that, if you can't depend on the WndProc).
        NOTE: the callbacks are executed in the window's root procedure and not in the inherited WndProc function.
        This means, that callbacks have priority over the application defined WndProc.

        General priority of message handling.
                Outrage Window Procedure:
                        takes care of window creation, destruction and system menus.
                        if message's window not registered then
                                calls Win32 Window Procedure
                        else
                                runs OEWin32MsgCallbacks for that message
                                if OEWin32MsgCallback functions return 0 then
                                        leave Outrage Window Procedure

                                calls oeWin32Application->WndProc hierarchy which
                                        optionally calls Win32 Window Procedure.
                        endif
*/

typedef int (*tOEWin32MsgCallback)(HWnd, unsigned, unsigned, long);

class oeWin32Application : public oeApplication {
#if defined(OEAPP_INTERNAL_MODULE)
public:
#else
private:
#endif
  bool m_WasCreated; // Tells us if this app created the window handle or not.

  int m_NumMsgFn; // Number of message functions.

  struct { // assign functions to messages.
    unsigned msg;
    tOEWin32MsgCallback fn;
  } m_MsgFn[MAX_MSG_FUNCTIONS];

  bool m_NTFlag; // Are we in NT?

  void (*m_DeferFunc)(bool); // function to call when deffering to OS (OnIdle for instance)

  char m_WndName[64]; // name of window.

  static bool os_initialized; // is the OS check initialized?
  static bool first_time;     // first time init?

private:
  int defer_block(); // real defer code.

public:
  //	Creates the window handle
  oeWin32Application(const char *name, unsigned flags, HInstance hinst);

  //	Create object with a premade window handle/instance
  //	we just give it the window handle, instance handle and flags
  oeWin32Application(tWin32AppInfo *appinfo);

  virtual ~oeWin32Application();

  //	initializes the object
  virtual void init();

  //	Function to retrieve information from object through a platform defined structure.
  virtual void get_info(void *appinfo);

  //	defer returns some flags.   essentially this function defers program control to OS.
  virtual unsigned defer();

  //	set a function to run when deferring to OS.
  virtual void set_defer_handler(void (*func)(bool));

  //	delays app for a certain amount of time
  virtual void delay(float secs);

  //	Sizes the displayable region of the app (the window)
  void set_sizepos(int x, int y, int w, int h);

  //	returns -1 if we pass to default window handler.
  virtual int WndProc(HWnd hwnd, unsigned msg, unsigned wParam, long lParam);

  //	These functions allow you to add message handlers.
  bool add_handler(unsigned msg, tOEWin32MsgCallback fn);

  // These functions remove a handler
  bool remove_handler(unsigned msg, tOEWin32MsgCallback fn);

  // Run handler for message (added by add_handler)
  bool run_handler(HWnd wnd, unsigned msg, unsigned wParam, long lParam);

  //	clears handler list
  void clear_handlers();

  //	tells us if we're in NT
  bool NT() const { return m_NTFlag; }

  // retreive full version information
  static tWin32OS version(int *major, int *minor, int *build = NULL, char *desc = NULL);

  // detect if application can handle what we want of it.
  static bool GetSystemSpecs(const char *fname);

//	These variables are only accessable to modules that have DD_ACCESS.
#if defined(DD_ACCESS_RING)
public:
#else
private:
#endif
  HWnd m_hWnd; // handles created by the system
  HInstance m_hInstance;
  unsigned m_Flags;
  int m_X, m_Y, m_W, m_H; // window dimensions.

private:
  void os_init(); // initializes OS components.
};

// the following data is communicated by the application library to other DDAccessed libraries.
#if defined(DD_ACCESS_RING)

// system mouse info.
extern short w32_msewhl_delta; // value of mouse wheel delta for frame

#endif
#endif