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

#ifndef MEM_H
#define MEM_H

//#define MEM_USE_RTL	1

#ifdef MACINTOSH
#undef MEM_USE_RTL
#endif

#ifdef MEM_USE_RTL
#define mem_malloc(d) malloc(d) // Use this if your going to run BoundsChecker
#define mem_free(d) free(d)
#define mem_strdup(d) strdup(d)
#define mem_size(d) _msize(d)
#define mem_realloc(d, e) realloc(d, e)
#else
// Use this if your going to NOT run BoundsChecker
#define mem_malloc(d) mem_malloc_sub(d, __FILE__, __LINE__)
#define mem_free(d) mem_free_sub(d)
#define mem_strdup(d) mem_strdup_sub(d, __FILE__, __LINE__)
#define mem_size(d) mem_size_sub(d)
#define mem_realloc(d, e) mem_realloc_sub(d, e)
#endif

extern bool Mem_low_memory_mode;
extern bool Mem_superlow_memory_mode; // DAJ

//	use if you want to manually print out a memory error
#define mem_error() mem_error_msg(__FILE__, __LINE__)

//	initializes memory library.
void mem_Init();

// shutsdown memory
void mem_shutdown(void);

// Returns the number of dynamically allocated bytes
int mem_GetTotalMemoryUsed();

// Allocates a block of memory and returns a pointer to it
void *mem_malloc_sub(int size, const char *file, int line);

// Frees a previously allocated block of memory
void mem_free_sub(void *memblock);

//	prints out a memory error message
void mem_error_msg(const char *file, int line, int size = -1);

char *mem_strdup_sub(const char *src, char *file, int line);

void *mem_realloc_sub(void *memblock, int size);

int mem_size_sub(void *memblock);

bool mem_dumpmallocstofile(char *filename);

#endif