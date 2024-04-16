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
 
#ifndef APP_H
#define APP_H
#include "pstypes.h"
/*	Basic Application data types */
/*	Application Object
		This object entails initialization and cleanup of all operating system 
		elements, as well as data that libraries may need to initialize their 
		systems.  Look under the specific header file for a platform for information
		about what's needed for the target machine.
*/
/*	Application flags */
const int	OEAPP_WINDOWED = 1,			// App will run in a window. May not be supported.
				OEAPP_FULLSCREEN = 2,		// App will run in fullscreen.  May not be supported.
				OEAPP_TOPMOST = 4,			// App will be on the topmost display.  May not be supported.
				OEAPP_CONSOLE = 8;			// App will run in a console style window.  
class oeApplication
{
protected:
	bool m_AppActive;
public:
	oeApplication() { m_AppActive = true; };
	virtual ~oeApplication() {};
//	initializes the object
	virtual void init() = 0;
//	Function to retrieve information from object through a platform defined structure.
	virtual void get_info(void *buffer) = 0;
//	defer returns some flags.   essentially this function defers program control to OS.
	virtual unsigned defer() = 0;
//	suspends application for a certain amout of time...
	virtual void delay(float secs) = 0 ;
//	set a function to run when deferring to OS.
	virtual void set_defer_handler(void (*func)(bool)) = 0;
public:
//	checks if the application is active
	bool active() const { return m_AppActive;	};
	void activate() { m_AppActive = true; };
	void deactivate() { m_AppActive = false; };
};
/*	This section includes the platform-specific header files 
	Add a platform to this list once implemented:
		Win32				Samir		Win32App.h			06/97
*/
#if defined(WIN32)
#include "win\Win32App.h"
#elif defined(__LINUX__)
#include "linux/lnxapp.h"
#elif defined(MACINTOSH)
#include "macapp.h"
#endif
#endif
