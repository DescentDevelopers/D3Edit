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
 


#ifndef TASKSYSTEM_H
#define TASKSYSTEM_H


#include "pstypes.h"

typedef enum tTaskPriority {
	TASKPRIORITY_HIGHEST,
	TASKPRIORITY_NORMAL,
	TASKPRIORITY_LOWEST
} tTaskPriority;


//	Since this system handles concepts such as multitasking, and the such, 
//	we will define the event structures differently, since different systems
//	handle multitasking differently.

class osEvent
{
#if defined(DD_ACCESS_RING)
public:
#else
private:
#endif		// DD_ACCESS_RING_0
#if defined(WIN32)
	unsigned event_os_handle;					// this is the Win32 Event Handle
#endif		// WIN32
	
public:
	osEvent(char *name);
	~osEvent();

	bool error() const;							// reports error

	void signal();								// signal the event so blocking can stop
	void clear();								// clear the event so blocking can continue
	bool block(int timeout=-1);			// block until signaled (-1 = full blocking, else time in ms to block)
};


class osTask
{
#if defined(DD_ACCESS_RING)
public:
#else
private:
#endif		// DD_ACCESS_RING_0
#if defined(WIN32)
	unsigned task_os_handle;					// This is the Win32 EventHandle
	unsigned task_os_id;						// Win32 Thread ID
#endif		// WIN32

public:
	osTask(unsigned (*func)(void *), tTaskPriority priority, void *parm=NULL);
	~osTask();

	bool error() const;							// reports error

	void suspend();								// suspends task
	void resume();								// resumes task
};


//	This establishes a mutual exclusion object.  once one thread locks the object, 
//	any code in another thread that contains a mutex check will block or skip that code until
//	the locking thread unlocks it.
class osMutex
{
#if defined(DD_ACCESS_RING)
public:
#else
private:
#endif

#if defined(WIN32)
	unsigned mutex_os_handle;
#endif

public:
	osMutex();
	~osMutex();

	bool Create();								// creates a mutex object.
	void Destroy();							// destroys a mutex object
	
// calling thread will attempt to acquire mutex (wait until timeout in ms.) if timeout == -1, wait forever...
	bool Acquire(int timeout=-1);				

// calling thread releases control of mutex.
	void Release();
};



#endif



	
			