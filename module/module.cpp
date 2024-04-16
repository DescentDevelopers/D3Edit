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

#include "module.h"
#include "pstypes.h"
#include "pserror.h"
#include "ddio.h"

#ifdef __LINUX__
bool mod_FindRealFileNameCaseInsenstive(const char *directory, const char *filename, char *new_filename);
#endif

#ifdef MACINTOSH
#include <Files.h>
#include <CodeFragments.h>
#endif
#include "module.h"
#include "pstypes.h"
#include "pserror.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#if defined(__LINUX__)
#include "linux/linux_fix.h"
#endif
#if defined(WIN32) // INSTEAD OF MAKING MODULE HAVE DEPENDENCIES, PUT THE 2 DDIO FUNCTIONS I NEED HERE
// Split a pathname into its component parts
void dd_SplitPath(const char *srcPath, char *path, char *filename, char *ext) {
  char drivename[_MAX_DRIVE], dirname[_MAX_DIR];
  _splitpath(srcPath, drivename, dirname, filename, ext);
  if (path)
    sprintf(path, "%s%s", drivename, dirname);
}
// Constructs a path in the local file system's syntax
// 	newPath: stores the constructed path
//  absolutePathHeader: absolute path on which the sub directories will be appended
//						(specified in local file system syntax)
//  takes a variable number of subdirectories which will be concatenated on to the path
//		the last argument in the list of sub dirs *MUST* be NULL to terminate the list
void dd_MakePath(char *newPath, const char *absolutePathHeader, const char *subDir, ...) {
  const char delimiter = '\\';
  va_list args;
  char *currentDir = NULL;
  int pathLength = 0;

  assert(newPath);
  assert(absolutePathHeader);
  assert(subDir);

  if (newPath != absolutePathHeader) {
    strcpy(newPath, absolutePathHeader);
  }
  // Add the first sub directory
  pathLength = strlen(newPath);
  if (newPath[pathLength - 1] != delimiter) {
    newPath[pathLength] = delimiter; // add the delimiter
    newPath[pathLength + 1] = 0;     // terminate the string
  }
  strcat(newPath, subDir);

  // Add the additional subdirectories
  va_start(args, subDir);
  while ((currentDir = va_arg(args, char *)) != NULL) {
    pathLength = strlen(newPath);
    if (newPath[pathLength - 1] != delimiter) {
      newPath[pathLength] = delimiter; // add the delimiter
      newPath[pathLength + 1] = 0;     // terminate the string
    }
    strcat(newPath, currentDir);
  }
  va_end(args);
}
#elif defined(MACINTOSH)
// DAJ why duplicate the functions that ddio provides???
// Split a pathname into its component parts
void dd_SplitPath(const char *srcPath, char *path, char *filename, char *ext) {
#ifdef FIXED
  char drivename[_MAX_DRIVE], dirname[_MAX_DIR];
  _splitpath(srcPath, drivename, dirname, filename, ext);
  if (path)
    sprintf(path, "%s%s", drivename, dirname);
#endif
}
// Constructs a path in the local file system's syntax
// 	newPath: stores the constructed path
//  absolutePathHeader: absolute path on which the sub directories will be appended
//						(specified in local file system syntax)
//  takes a variable number of subdirectories which will be concatenated on to the path
//		the last argument in the list of sub dirs *MUST* be NULL to terminate the list
void dd_MakePath(char *newPath, const char *absolutePathHeader, const char *subDir, ...) {
#ifdef FIXED
  const char delimiter = '\\';
  va_list args;
  char *currentDir = NULL;
  int pathLength = 0;

  assert(newPath);
  assert(absolutePathHeader);
  assert(subDir);

  if (newPath != absolutePathHeader) {
    strcpy(newPath, absolutePathHeader);
  }
  // Add the first sub directory
  pathLength = strlen(newPath);
  if (newPath[pathLength - 1] != delimiter) {
    newPath[pathLength] = delimiter; // add the delimiter
    newPath[pathLength + 1] = 0;     // terminate the string
  }
  strcat(newPath, subDir);

  // Add the additional subdirectories
  va_start(args, subDir);
  while ((currentDir = va_arg(args, char *)) != NULL) {
    pathLength = strlen(newPath);
    if (newPath[pathLength - 1] != delimiter) {
      newPath[pathLength] = delimiter; // add the delimiter
      newPath[pathLength + 1] = 0;     // terminate the string
    }
    strcat(newPath, currentDir);
  }
  va_end(args);
#endif
}
#elif defined(__LINUX__)
// Split a pathname into its component parts
void dd_SplitPath(const char *srcPath, char *path, char *filename, char *ext) {
  int pathStart = -1;
  int pathEnd = -1;
  int fileStart = -1;
  int fileEnd = -1;
  int extStart = -1;
  int extEnd = -1;
  int totalLen = strlen(srcPath);
  // Check for an extension
  ///////////////////////////////////////
  int t = totalLen - 1;
  while ((srcPath[t] != '.') && (srcPath[t] != '/') && (t >= 0))
    t--;
  // see if we are at an extension
  if ((t >= 0) && (srcPath[t] == '.')) {
    // we have an extension
    extStart = t;
    extEnd = totalLen - 1;
    if (ext) {
      strncpy(ext, &(srcPath[extStart]), extEnd - extStart + 1);
      ext[extEnd - extStart + 1] = '\0';
    }
  } else {
    // no extension
    if (ext)
      ext[0] = '\0';
  }

  // Check for file name
  ////////////////////////////////////
  int temp = (extStart != -1) ? (extStart) : (totalLen - 1);
  while ((srcPath[temp] != '/') && (temp >= 0))
    temp--;
  if (temp < 0)
    temp = 0;
  if (srcPath[temp] == '/') {
    // we have a file
    fileStart = temp + 1;
    if (extStart != -1)
      fileEnd = extStart - 1;
    else
      fileEnd = totalLen - 1;
    if (filename) {
      strncpy(filename, &(srcPath[fileStart]), fileEnd - fileStart + 1);
      filename[fileEnd - fileStart + 1] = '\0';
    }
    pathStart = 0;
    pathEnd = fileStart - 2;
    // Copy the rest into the path name
    if (path) {
      strncpy(path, &(srcPath[pathStart]), pathEnd - pathStart + 1);
      path[pathEnd - pathStart + 1] = 0;
    }
  } else {
    // only file, no path
    fileStart = 0;
    if (extStart != -1)
      fileEnd = extStart - 1;
    else
      fileEnd = totalLen - 1;
    if (filename) {
      strncpy(filename, &(srcPath[fileStart]), fileEnd - fileStart + 1);
      filename[fileEnd - fileStart + 1] = 0;
    }

    // Only file no path
    if (path) {
      path[0] = 0;
    }
  }
}
// Constructs a path in the local file system's syntax
// 	newPath: stores the constructed path
//  absolutePathHeader: absolute path on which the sub directories will be appended
//						(specified in local file system syntax)
//  takes a variable number of subdirectories which will be concatenated on to the path
//		the last argument in the list of sub dirs *MUST* be NULL to terminate the list
void dd_MakePath(char *newPath, const char *absolutePathHeader, const char *subDir, ...) {
  const char delimiter = '/';
  va_list args;
  char *currentDir = NULL;
  int pathLength = 0;

  ASSERT(newPath);
  ASSERT(absolutePathHeader);
  ASSERT(subDir);

  if (newPath != absolutePathHeader) {
    strcpy(newPath, absolutePathHeader);
  }
  // Add the first sub directory
  pathLength = strlen(newPath);
  if (newPath[pathLength - 1] != delimiter) {
    newPath[pathLength] = delimiter; // add the delimiter
    newPath[pathLength + 1] = 0;     // terminate the string
  }
  strcat(newPath, subDir);

  // Add the additional subdirectories
  va_start(args, subDir);
  while ((currentDir = va_arg(args, char *)) != NULL) {
    pathLength = strlen(newPath);
    if (newPath[pathLength - 1] != delimiter) {
      newPath[pathLength] = delimiter; // add the delimiter
      newPath[pathLength + 1] = 0;     // terminate the string
    }
    strcat(newPath, currentDir);
  }
  va_end(args);
}
#endif
int ModLastError = MODERR_NOERROR;
//	Returns the real name of the module.  If a given file has an extension, it will
//	just return that filename.  If the given file has no given extension, the
//	system specific extension is concatted and returned.
void mod_GetRealModuleName(const char *modfilename, char *realmodfilename) {
  char pathname[_MAX_PATH], filename[_MAX_FNAME], extension[_MAX_EXT];
#ifdef MACINTOSH
  ddio_SplitPath(modfilename, pathname, filename, extension);
#else
  dd_SplitPath(modfilename, pathname, filename, extension);
#endif
  if (*extension == '\0')
#if defined(WIN32)
    strcat(filename, ".dll");
#elif defined(MACINTOSH)
    strcat(filename, ".msl");
#elif defined(__LINUX__)
    strcat(filename, ".so");
#endif
  else {
#if defined(WIN32)
    if (!stricmp(extension, ".so") || !stricmp(extension, "msl"))
      strcat(filename, ".dll");
    else
      strcat(filename, extension);
#elif defined(MACINTOSH)
    if (!stricmp(extension, ".dll") || !stricmp(extension, "so"))
      strcat(filename, ".msl");
    else
      strcat(filename, extension);
#elif defined(__LINUX__)
    if (!stricmp(extension, ".dll") || !stricmp(extension, "msl"))
      strcat(filename, ".so");
    else
      strcat(filename, extension);
#endif
  }
  if (*pathname != '\0')
#ifdef MACINTOSH
    ddio_MakePath(realmodfilename, pathname, filename, NULL);
#else
    dd_MakePath(realmodfilename, pathname, filename, NULL);
#endif
  else
    strcpy(realmodfilename, filename);
}
// Loads a dynamic module into memory for use.
// Returns true on success, false otherwise
// modfilename is the name of the module (without an extension such as DLL, or so)
bool mod_LoadModule(module *handle, char *imodfilename, int flags) {
  if (!imodfilename) {
    ModLastError = MODERR_OTHER;
    return false;
  }
  if (!handle) {
    ModLastError = MODERR_INVALIDHANDLE;
    return false;
  }
  handle->handle = NULL;
  char modfilename[_MAX_PATH];
  mod_GetRealModuleName(imodfilename, modfilename);
#if defined(WIN32)
  handle->handle = LoadLibrary(modfilename);
  if (!handle->handle) {
    // There was an error loading the module
    DWORD err = GetLastError();
    switch (err) {
    case ERROR_DLL_INIT_FAILED:
      ModLastError = MODERR_MODINITFAIL;
      break;
    case ERROR_DLL_NOT_FOUND:
      ModLastError = MODERR_MODNOTFOUND;
      break;
    case ERROR_INVALID_DLL:
      ModLastError = MODERR_INVALIDMOD;
      break;
    default:
      ModLastError = MODERR_OTHER;
      break;
    }
    return false;
  }
#elif defined(__LINUX__)
  int f = 0;
  if (flags & MODF_LAZY)
    f |= RTLD_LAZY;
  if (flags & MODF_NOW)
    f |= RTLD_NOW;
  if (flags & MODF_GLOBAL)
    f |= RTLD_GLOBAL;
  handle->handle = dlopen(modfilename, f);
  if (!handle->handle) {
    // ok we couldn't find the given name...try other ways
    char dir[_MAX_PATH], fname[_MAX_PATH], nname[_MAX_PATH], ext[64];
    dd_SplitPath(modfilename, dir, fname, ext);
    strcat(fname, ext);

    if (!mod_FindRealFileNameCaseInsenstive(dir, fname, nname)) {
      mprintf((0, "Module Load Err: %s\n", dlerror()));
      ModLastError = MODERR_MODNOTFOUND;
      return false;
    } else {
      // ok we have a different filename
      dd_MakePath(modfilename, dir, nname, NULL);
      mprintf((0, "MOD: Attempting to open %s instead of %s\n", modfilename, fname));
      handle->handle = dlopen(modfilename, f);
      if (!handle->handle) {
        mprintf((0, "Module Load Err: %s\n", dlerror()));
        ModLastError = MODERR_MODNOTFOUND;
        return false;
      }
    }
  }
#elif defined(MACINTOSH)
  OSErr err = noErr;
  FSSpec SLSpec;
  Str255 errName;
  Str63 toolName;
  Ptr myMainAddr;
  CFragConnectionID connID;
  Str255 symName;
  strcpy((char *)symName, modfilename);
  c2pstr((char *)symName);
  err = FSMakeFSSpec(0, 0L, symName, &SLSpec);
  if (err) {
    mprintf((2, "could not make FSSpec in loadModule\n"));
    //		Int3();
  }
  err = GetDiskFragment(&SLSpec, 0, 0, NULL, 5, &connID, (Ptr *)NULL, NULL);
  //	err = GetDiskFragment(&SLSpec, 0, kCFragGoesToEOF, toolName, kPrivateCFragCopy, &connID, (Ptr*)&myMainAddr,
  //errName);
  if (err) {
    mprintf((2, "could not get disk fragmet %s\n", modfilename));
    //		Int3();;
  }

  handle->handle = connID;
  mprintf((0, "opening fragment ID 0x%X\n", handle->handle));
#endif
  // Success
  return true;
}
// Frees a previously loaded module from memory, it can no longer be used
// Returns true on success, false otherwise
bool mod_FreeModule(module *handle) {
  bool ret = true;

  if (!handle) {
    ModLastError = MODERR_INVALIDHANDLE;
    return false;
  }
  if (!handle->handle) {
    ModLastError = MODERR_OTHER;
    return false;
  }
#if defined(WIN32)
  ret = (FreeLibrary(handle->handle) != 0);
#elif defined(__LINUX__)
  dlclose(handle->handle); // dlclose() returns an int, but no docs say what values!!!
#elif defined(MACINTOSH)
/*	//BROKE! but not needed, OS closes connection on quit
        OSErr err = noErr;
        if(handle->handle)
                mprintf((0, "closeing fragment 0x%X\n", handle->handle));
                err = CloseConnection((CFragConnectionID*)handle->handle);
                if(err != noErr) {
                        mprintf((2, "could not close fragment 0x%X\n", handle->handle));
//			return false;
        }
*/
#endif
  handle->handle = NULL;
  return ret;
}
// Returns a pointer to a function within a loaded module.  If it returns NULL there was an error.  Check
// mod_GetLastError to see if there was an error symstr is the name of the function you want to get the symbol for (Do
// NOT give any pre/suffix to this name) parmbytes is the size (in bytes) of the parameter list the function should have
MODPROCADDRESS mod_GetSymbol(module *handle, char *symstr, unsigned char parmbytes) {
  char buffer[256];
  MODPROCADDRESS sym;
  if (!handle) {
    ModLastError = MODERR_INVALIDHANDLE;
    return NULL;
  }
  if (!symstr) {
    ModLastError = MODERR_OTHER;
    return NULL;
  }
  if (!handle->handle) {
    ModLastError = MODERR_NOMOD;
    return NULL;
  }
#if defined(WIN32)
  // We need to first form the correct symbol name (for Windows)
  if (parmbytes == 255)
    sprintf(buffer, "%s", symstr);
  else
    sprintf(buffer, "_%s@%d", symstr, parmbytes);
  DWORD err;
  sym = GetProcAddress(handle->handle, buffer);
  if (!sym) {
    err = GetLastError();

    // Try again using no byte ordinals
    if (parmbytes != 255) {
      sprintf(buffer, "%s", symstr);
      sym = GetProcAddress(handle->handle, buffer);
      if (!sym)
        err = GetLastError();
    }
  }
  if (!sym) {
    // there was an error

    switch (err) {
    case ERROR_DLL_INIT_FAILED:
      ModLastError = MODERR_MODINITFAIL;
      break;
    case ERROR_DLL_NOT_FOUND:
      ModLastError = MODERR_MODNOTFOUND;
      break;
    case ERROR_INVALID_DLL:
      ModLastError = MODERR_INVALIDMOD;
      break;
    default:
      ModLastError = MODERR_OTHER;
      break;
    }
    return NULL;
  }
#elif defined(__LINUX__)
  sym = dlsym(handle->handle, symstr);
  if (!sym) {
    ModLastError = MODERR_OTHER;
    return NULL;
  }
#elif defined(MACINTOSH)
  OSErr err = noErr;
  CFragSymbolClass symClass;
  CFragConnectionID connID;
  Str255 symName;
  mprintf((0, "finding %s in fragment 0x%X\n", symstr, handle->handle));
  connID = (CFragConnectionID)handle->handle;

  // DAJ for testing only
  long numSym;
  Ptr symAddr;
  err = CountSymbols(connID, &numSym);
  for (int i = 0; i < numSym; i++) {
    err = GetIndSymbol(connID, i, symName, &symAddr, &symClass);
  }

  strcpy((char *)symName, symstr);
  c2pstr((char *)symName);

  err = FindSymbol(connID, symName, (Ptr *)&sym, &symClass);
  if (err) {
    mprintf((2, "could not find %s in fragment %d\n", symstr, handle->handle));
    return NULL;
  }
  if (!sym) {
    ModLastError = MODERR_OTHER;
    return NULL;
  }
#endif
  return sym;
}
// Returns an error code to what the last error was.  When this function is called the last error is cleared, so by
// calling this function it not only returns the last error, but it removes it, so if you were to call this function
// again, it would return no error
int mod_GetLastError(void) {
  // Clear out the errors
#if defined(WIN32)
  SetLastError(0);
#elif defined(__LINUX__)
  dlerror();
#endif
  int ret = ModLastError;
  ModLastError = MODERR_NOERROR;
  return ret;
}

#ifdef __LINUX__
#include <assert.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <glob.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>

void dd_GetWorkingDir(char *path, int len);
bool dd_SetWorkingDir(const char *path);
bool dd_FindFileStart(const char *wildcard, char *namebuf);
bool dd_FindNextFile(char *namebuf);
void dd_FindFileClose();

//	retrieve the current working folder where file operation will occur.
void dd_GetWorkingDir(char *path, int len) { getcwd(path, len); }

bool dd_SetWorkingDir(const char *path) { return (chdir(path)) ? false : true; }

// These functions allow one to find a file
static int globerrfn(const char *path, int err) {
  mprintf((0, "Error accessing %s: %s .... \n", path, strerror(err)));
  return 0;
}

class CModFindFiles {
public:
  CModFindFiles() { globindex = -1; }

  bool Start(const char *wildcard, char *namebuf);
  bool Next(char *namebuf);
  void Close(void);

private:
  int globindex;
  glob_t ffres;
};

bool CModFindFiles::Start(const char *wildcard, char *namebuf) {
  ASSERT(wildcard);
  ASSERT(namebuf);

  if (globindex != -1)
    Close();

  int rc, flags;
  flags = GLOB_MARK;
  rc = glob(wildcard, flags, globerrfn, &ffres);
  if (rc == GLOB_NOSPACE) {
    mprintf((0, "Out of space during glob\n"));
    globindex = -1;
    return false;
  }
  if (!ffres.gl_pathc) {
    globindex = -1;
    return false;
  }

  globindex = 0;
  char ext[256];
  dd_SplitPath(ffres.gl_pathv[0], NULL, namebuf, ext);
  strcat(namebuf, ext);
  return true;
}

bool CModFindFiles::Next(char *namebuf) {
  ASSERT(namebuf);
  if (globindex == -1)
    return false;
  globindex++;
  if (globindex >= ffres.gl_pathc)
    return false;

  char ext[256];
  dd_SplitPath(ffres.gl_pathv[globindex], NULL, namebuf, ext);
  strcat(namebuf, ext);
  return true;
}

void CModFindFiles::Close(void) {
  if (globindex == -1)
    return;
  globindex = -1;
  globfree(&ffres);
}

bool mod_FindRealFileNameCaseInsenstive(const char *directory, const char *fname, char *new_filename) {
  bool use_dir = false;
  char dir_to_use[_MAX_PATH];
  char file_to_use[_MAX_PATH];

  char *real_dir, *real_file;

  if (directory) {
    // there is a directory for this path
    use_dir = true;
    real_dir = (char *)directory;
    real_file = (char *)fname;
  } else {
    // there may be a directory in the path (*sigh*)
    char t_ext[256];
    char t_dir[_MAX_PATH];
    char t_filename[_MAX_PATH];

    dd_SplitPath(fname, t_dir, t_filename, t_ext);
    if (strlen(t_dir) > 0) {
      use_dir = true;
      strcpy(dir_to_use, t_dir);
      real_dir = (char *)dir_to_use;
      strcpy(file_to_use, t_filename);
      strcat(file_to_use, t_ext);
      real_file = (char *)file_to_use;

      mprintf((1, "MOD: Found directory \"%s\" in filename, new filename is \"%s\"\n", real_dir, real_file));
    } else {
      use_dir = false;
      real_dir = NULL;
      real_file = (char *)fname;
    }
  }

  // build up a list of filenames in the current directory that begin with the lowercase and
  // upper case first letter of the filename

  // do the case of the first letter to start
  int case_val;
  char wildcard_pattern[_MAX_PATH];
  int iterations = 1;
  bool found_match = false;

  if ((real_file[0] >= 'a' && real_file[0] <= 'z') || (real_file[0] >= 'A' && real_file[0] <= 'Z')) {
    // alpha first letter...we need to do 2 iterations
    iterations = 2;
  }

  for (case_val = 0; case_val < iterations; case_val++) {
    if (case_val) {
      // do the opposite case of the first letter
      char first_letter;
      first_letter = real_file[0];
      if (first_letter >= 'a' && first_letter <= 'z') {
        // we need to uppercase the letter
        first_letter = toupper(first_letter);
      } else {
        // we need to lowercase the letter
        first_letter = tolower(first_letter);
      }

      // create a wildcard patter full of ? replacing letters (except the first one)
      char *wptr = wildcard_pattern;
      char *fptr = &real_file[1];
      *wptr = first_letter;
      wptr++;
      while (*fptr) {
        if (isalpha(*fptr)) {
          *wptr = '?';
        } else {
          *wptr = *fptr;
        }

        fptr++;
        wptr++;
      }
      *wptr = '\0';
    } else {
      // use the case of the first letter
      // create a wildcard patter full of ? replacing letters (except the first one)
      char *wptr = wildcard_pattern;
      char *fptr = &real_file[1];
      *wptr = real_file[0];
      wptr++;
      while (*fptr) {
        if (isalpha(*fptr)) {
          *wptr = '?';
        } else {
          *wptr = *fptr;
        }

        fptr++;
        wptr++;
      }
      *wptr = '\0';
    }

    // now tack on a directory if we are to use a directory
    char *wpattern;
    char fullpath[_MAX_PATH];
    if (use_dir) {
      dd_MakePath(fullpath, real_dir, wildcard_pattern, NULL);
      wpattern = fullpath;
    } else {
      wpattern = wildcard_pattern;
    }

    // ok, we have our wildcard pattern, get all the files that match it
    // and search them looking for a match (case insensitive)
    char namebuffer[_MAX_PATH];
    bool gotfile;
    CModFindFiles ff;
    for (gotfile = ff.Start(wpattern, namebuffer); gotfile; gotfile = ff.Next(namebuffer)) {
      if (!stricmp(namebuffer, real_file)) {
        // we found a match!
        found_match = true;
        break;
      }
    }
    ff.Close();

    if (found_match) {
      strcpy(new_filename, namebuffer);
      mprintf((1, "MOD: Using \"%s\" instead of \"%s\"\n", new_filename, real_file));
      break;
    }
  }

  return found_match;
}
#endif
