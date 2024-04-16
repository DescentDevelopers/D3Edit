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
 

#include "ddio.h"
#include "ddio_win.h"
#include "pserror.h"
#include "mem.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdarg.h>
#include <sys\stat.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>


//	---------------------------------------------------------------------------
//	File operations

//	creates a directory or folder on disk
bool ddio_CreateDir(const char *path)
{
	return (CreateDirectory(path, NULL)) ? true : false;
}


//	destroys a directory
bool ddio_RemoveDir(const char *path)
{
	return (RemoveDirectory(path)) ? true : false;
}
	

//	retrieve the current working folder where file operation will occur.
void ddio_GetWorkingDir(char *path, int len)
{
	GetCurrentDirectory(len,path);
}	

bool ddio_SetWorkingDir(const char *path)
{
	return (SetCurrentDirectory(path)) ? true : false;
}

bool ddio_FileDiff(const char *path1, const char *path2)
{
	struct _stat abuf,bbuf;

	if (_stat(path1,&abuf))
		Int3();		//error getting stat info

	if (_stat(path2,&bbuf))
		Int3();		//error getting stat info

	if ((abuf.st_size != bbuf.st_size) || (abuf.st_mtime != bbuf.st_mtime))
		return true;

	return false;
}

// get a file's length
int	ddio_GetFileLength(FILE* filePtr)
{
	return (filelength(fileno(filePtr)));
}

// Split a pathname into its component parts
void ddio_SplitPath(const char* srcPath, char* path, char* filename, char* ext)
{
	char drivename[_MAX_DRIVE], dirname[_MAX_DIR];

	_splitpath(srcPath, drivename, dirname, filename, ext);

	if (path) 
		sprintf(path, "%s%s", drivename, dirname);
}

void ddio_CopyFileTime (char *destname,const char *srcname)
{
	HANDLE desthandle,srchandle;
	FILETIME a,b,c;
	bool first_time = 1;

try_again:;

	desthandle=CreateFile(destname,GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	srchandle=CreateFile(srcname,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if (desthandle==INVALID_HANDLE_VALUE || srchandle==INVALID_HANDLE_VALUE)
	{
		mprintf ((0,"Couldn't copy file time for %s! Error=%d\n",destname,GetLastError()));

		if (desthandle!=INVALID_HANDLE_VALUE)
			CloseHandle(desthandle);

		if (srchandle!=INVALID_HANDLE_VALUE)
			CloseHandle(srchandle);

		if (first_time) {
			first_time = 0;
			Sleep(500);
			goto try_again;
		}

		//JEFF: This Int3 has become really annoying...all we do is blow by it anyway
		//removed for sanity.
		//@@Int3();	//Let Matt know if you hit this!
		return;
	}

	GetFileTime (srchandle,&a,&b,&c);
	SetFileTime (desthandle,&a,&b,&c);

	CloseHandle (desthandle);
	CloseHandle (srchandle);
}

// deletes a file.  Returns 1 if successful, 0 on failure
int ddio_DeleteFile (char *name)
{
	return (DeleteFile (name));
}


// Save/Restore the current working directory

static char SavedWorkingDir[_MAX_DIR];

void ddio_SaveWorkingDir(void)
{
	GetCurrentDirectory(_MAX_DIR, SavedWorkingDir);
}


void ddio_RestoreWorkingDir(void)
{
	SetCurrentDirectory(SavedWorkingDir);
}


// 	Checks if a directory exists (returns 1 if it does, 0 if not)
//	This pathname is *RELATIVE* not fully qualified
bool ddio_DirExists(const char* path)
{
	BOOL res;

	ddio_SaveWorkingDir();
	res = SetCurrentDirectory(path);
	ddio_RestoreWorkingDir();	

	return (res) ? true: false;
}


// Constructs a path in the local file system's syntax
// 	newPath: stores the constructed path
//  absolutePathHeader: absolute path on which the sub directories will be appended
//						(specified in local file system syntax)
//  takes a variable number of subdirectories which will be concatenated on to the path
//		the last argument in the list of sub dirs *MUST* be NULL to terminate the list
void ddio_MakePath(char* newPath, const char* absolutePathHeader, const char* subDir, ...)
{
	const char	delimiter = '\\';
	va_list		args;
	char*		currentDir = NULL;
	int			pathLength = 0;
	
	assert(newPath);
	assert(absolutePathHeader);
	assert(subDir);
		
	if (newPath != absolutePathHeader)
	{
		strcpy(newPath, absolutePathHeader);
	}

	// Add the first sub directory
	pathLength = strlen(newPath);
	if (newPath[pathLength - 1] != delimiter)
	{
		newPath[pathLength] = delimiter;		// add the delimiter
		newPath[pathLength+1] = 0;				// terminate the string
	}
	strcat(newPath, subDir);		
	
	// Add the additional subdirectories
	va_start(args, subDir);
		while ((currentDir = va_arg(args, char*)) != NULL)
		{
			pathLength = strlen(newPath);
			if (newPath[pathLength - 1] != delimiter)
			{
				newPath[pathLength] = delimiter;		// add the delimiter
				newPath[pathLength+1] = 0;				// terminate the string
			}
			strcat(newPath, currentDir);		
		}
	va_end(args);	
}

bool ddio_GetTempFileName(char *basedir,char *prefix,char *filename)
{

	if(!GetTempFileName(basedir,prefix,0,filename))
		return false;
	else
		return true;
}


//	These functions allow one to find a file
//		You use FindFileStart by giving it a wildcard (like *.*, *.txt, u??.*, whatever).  It returns
//		a filename in namebuf.
//		Use FindNextFile to get the next file found with the wildcard given in FindFileStart.
//		Use FindFileClose to end your search.
static HANDLE hFindFile = INVALID_HANDLE_VALUE;
static WIN32_FIND_DATA FindFileData;

bool ddio_FindFileStart(const char *wildcard, char *namebuf)
{
	if (hFindFile != INVALID_HANDLE_VALUE) 
		ddio_FindFileClose();

	hFindFile = FindFirstFile(wildcard, &FindFileData);
	if (hFindFile != INVALID_HANDLE_VALUE) {
		strcpy(namebuf, FindFileData.cFileName);
		return true;
	}
	else {
		namebuf[0] = 0;
		return false;
	}
}


bool ddio_FindNextFile(char *namebuf)
{
	
	if (!hFindFile) return false;

	if (FindNextFile(hFindFile, &FindFileData)) {
		strcpy(namebuf, FindFileData.cFileName);
		return true;
	}
	else {
		namebuf[0] = 0;
		return false;
	}
}


void ddio_FindFileClose()
{
	if (hFindFile != INVALID_HANDLE_VALUE) FindClose(hFindFile);
	hFindFile = INVALID_HANDLE_VALUE;
}


static HANDLE hFindDir = INVALID_HANDLE_VALUE;
static WIN32_FIND_DATA FindDirData;
bool ddio_FindDirStart(const char *wildcard, char *namebuf)
{
	if (hFindDir != INVALID_HANDLE_VALUE) 
		ddio_FindDirClose();

	hFindDir = FindFirstFile(wildcard, &FindDirData);
	if (hFindDir != INVALID_HANDLE_VALUE) {

		if(FindDirData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY){
			strcpy(namebuf, FindDirData.cFileName);
			return true;
		}else{
			return ddio_FindNextDir(namebuf);
		}			
	}
	else {
		namebuf[0] = 0;
		return false;
	}
}

bool ddio_FindNextDir(char *namebuf)
{
	
	if (!hFindDir) return false;

	bool done = false;
	bool found = false;

	while( !done ){

		if (FindNextFile(hFindDir, &FindDirData)){
			if(FindDirData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY){
				strcpy(namebuf, FindDirData.cFileName);
				done = true;
				found = true;
			}
		}else{
			namebuf[0] = '\0';
			done = true;
		}
	}

	return found;
}

void ddio_FindDirClose()
{
	if (hFindDir != INVALID_HANDLE_VALUE) FindClose(hFindDir);
	hFindDir = INVALID_HANDLE_VALUE;
}


//	 pass in a pathname (could be from ddio_SplitPath), root_path will have the drive name.
void ddio_GetRootFromPath(const char *srcPath, char *root_path)
{
	assert(root_path);
	assert(srcPath);

	//the first char should be drive letter, second char should be a :
	if((isalpha(srcPath[0]))&&(srcPath[1]==':')){
		//everything is ok
		strncpy(root_path,srcPath,2);
		root_path[2] = '\0';
	}else{
		//invalid path (no root)
		root_path[0]='\0';
	}
}

//	retrieve root names, free up roots array (allocated with malloc) after use
int ddio_GetFileSysRoots(char **roots, int max_roots)
{
	char buffer[100];

	int ret = GetLogicalDriveStrings(100,buffer);
	if(ret==0){
		//there was an error
		return 0;
	}

	if( ret > 100 ){
		//we didn't have enough space
		return 0;
	}

	int count = 0;
	bool done = false;
	char *strptr = buffer;
	char *string;
	int strsize;
	while( (count<max_roots) && (!done) ){
		if(*strptr!=0){
			strsize = strlen(strptr);
			string = roots[count] = (char *)mem_malloc(strsize);
			if(!string)
				break;
			//remove the trailing \ from windows
			strncpy(string,strptr,strsize-1);
			string[strsize-1]='\0';			
			
			strptr+= (strsize + 1);

			count++;
		}else
			done = true;
	}
	return count;
}

//	given a path, it cleans it up (if the path is c:\windows\..\dos it would make it c:\dos)
//	srcPath is the original path
//	dest is the finished cleaned path.
//		dest should be at least _MAX_PATH in size
void ddio_CleanPath(char *dest,const char* srcPath)
{
	strcpy(dest,srcPath);

	//break the path into directories
	char **directories;
	int dirs;
	int path_length;

	//make sure the path ends with a \ for sanity
	path_length = strlen(dest);

	if(dest[path_length-1]!='\\'){
		dest[path_length]='\\';
		dest[path_length+1]='\0';
		path_length++;
	}

	//now divide the full path into seperate NULL terminated strings,counting the number
	//of directories in the process
	dirs = 0;
	char *strptr = dest;
	while(*strptr!='\0'){
		if(*strptr=='\\'){
			*strptr = '\0';
			dirs++;
		}
		strptr++;
	}

	//check to make sure we have a directory, if we don't then return the original path given
	if(dirs==0){
		strcpy(dest,srcPath);
		return;
	}

	//allocate the memory needed for the seperate strings of each directory
	directories = (char **)mem_malloc(sizeof(char *)*dirs);
	if(!directories){
		strcpy(dest,srcPath);
		return;
	}

	//now get all the directories, and place into the individual strings
	strptr = dest;
	int count = 0;
	while(count<dirs){
		directories[count] = mem_strdup(strptr);
		strptr += strlen(strptr) + 1;
		count++;
	}

	//now the fun part, figure out the correct order of the directories
	int *dir_order;

	dir_order = (int *)mem_malloc(sizeof(int)*dirs);
	if(!dir_order){
		strcpy(dest,srcPath);
		return;
	}

	for(count=0;count<dirs;count++)
		dir_order[count] = -1;	//a -1 means the end of the sequence

	//now build the order based on the indicies
	int curr_index = 0;
	for(count=0;count<dirs;count++){
		
		if(!stricmp(directories[count],"..")){
			//we have to back up a directory
			curr_index--;				//back up
			if(curr_index<0)
				curr_index=0;			//can't go further than root
			dir_order[curr_index] = -1;	//invalidate current slot
		}else
		if(stricmp(directories[count],".")){
			//we have a normal directory, add it's index
			dir_order[curr_index] = count;
			curr_index++;
		}
	}

	//now rebuild the correct path for use, when we hit -1, we're done
	dest[0]='\0';
	for(count=0;count<dirs;count++){
		if(dir_order[count]==-1)
			break;
		else{
			strcat(dest,directories[dir_order[count]]);
			strcat(dest,"\\");
		}
	}

	//now remove trailing \ char
	path_length = strlen(dest);
	if((path_length>0)&&(dest[path_length-1]=='\\'))
		dest[path_length-1]='\0';

	//free up all the allocated memory and we're done
	for(count=0;count<dirs;count++){
		if(directories[count])
			mem_free(directories[count]);
	}
	if(directories)
		mem_free(directories);	
	if(dir_order)
		mem_free(dir_order);
}

//	given a path (with no filename), it will return the parent path
//	srcPath is the source given path
//	dest is where the parent path will be placed
//	returns true on success
//		dest should be at least _MAX_PATH in length
bool ddio_GetParentPath(char *dest,const char* srcPath)
{
	assert(srcPath);
	assert(dest);

#define PARENT_DELIM ".."
	int spath_len = strlen(srcPath);
	char *temp;

	temp = (char *)mem_malloc(spath_len+strlen(PARENT_DELIM)+3);
	if(!temp){
		return false;
	}

	ddio_MakePath(temp,srcPath,PARENT_DELIM,NULL);
	ddio_CleanPath(dest,temp);
	mem_free(temp);
	return true;
}

//Finds a full path from a relative path
//Parameters:	full_path - filled in with the fully-specified path.  Buffer must be at least _MAX_PATH bytes long
//					rel_path - a path specification, either relative or absolute
//Returns TRUE if successful, FALSE if an error
bool ddio_GetFullPath(char *full_path,const char *rel_path)
{
	char old_path[_MAX_PATH];

	ddio_GetWorkingDir(old_path,sizeof(old_path));	//save old directory

	if (! ddio_SetWorkingDir(rel_path))					//try switching to new directory
		return 0;												//couldn't switch, so return error

	ddio_GetWorkingDir(full_path,_MAX_PATH);		 	//get path from the OS

	ddio_SetWorkingDir(old_path);							//now restore old path

	return 1;
}

//Renames file
//Returns true on success or false on an error
bool ddio_RenameFile(char *oldfile,char *newfile)
{
	int rcode = rename(oldfile,newfile);
	if(!rcode)
		return true;
	else
		return false;	
}

//Give a volume label to look for, and if it's found returns a path 
//If it isn't found, return NULL (used to return "")
char * ddio_GetCDDrive(char *vol)
{

	#define MAX_FSTYPE_LEN	30	
	static char drivepath[10];
	unsigned long volflags;
	int i;
	char volume[_MAX_PATH];
	char fsname[MAX_FSTYPE_LEN] = "";
	unsigned long serial;
	unsigned long component;

	strcpy(drivepath,"c:\\");

	for( i = 1; i <= 26; i++ )      
	{
		if(DRIVE_CDROM==GetDriveType(drivepath))
		{
			//Get the drive volume name
			volume[0] = 0;
			if(!GetVolumeInformation(drivepath,volume,_MAX_PATH,&serial,&component,&volflags,fsname,MAX_FSTYPE_LEN))
			{
				mprintf((0,"Call to GetVolumeInformation() failed. Last error = %d\n",GetLastError()));
			}
			
			if(strcmpi(volume,vol)==0)
			{
				return drivepath;
			}
		}
		drivepath[0]++;
	}
	drivepath[0] = 0;
	return NULL;//drivepath;

}

// Checks to see if a lock file is located in the specified directory.
//	Parameters:
//		dir		Directory for which the lock file should be checked
//	Returns:
//		1		Lock file doesn't exist
//		2		Lock file was in a directory, but it belonged to a process that no longer
//				exists, so a lock file _can_ be made in the directory.
//		3		Lock file for this process already exists
//		0		Lock file currently exists in directory
//		-1		Illegal directory
//		-2		There is a lock file in the directory, but it is in an illegal format
int ddio_CheckLockFile(const char *dir)
{
	DWORD curr_pid = GetCurrentProcessId();
	char old_directory[_MAX_PATH];
	ddio_GetWorkingDir(old_directory,_MAX_PATH);
	if(!ddio_SetWorkingDir(dir))
		return -1;

	bool found_lock_file_in_dir = false;
	FILE *file;

	chmod(".lock",_S_IREAD|_S_IWRITE);
	file = fopen(".lock","rb");

	if(!file)
	{
		//File exists, but couldn't open it
		if (errno == EACCES)
		{
			ddio_SetWorkingDir(old_directory);
			return -2;
		}

		found_lock_file_in_dir = false;
	}else
	{
		found_lock_file_in_dir = true;

		//check the file, see if it is a lock file
		char c;
		c = fgetc(file); if(c!='L')	{fclose(file); ddio_SetWorkingDir(old_directory); return -2;}
		c = fgetc(file); if(c!='O')	{fclose(file); ddio_SetWorkingDir(old_directory); return -2;}
		c = fgetc(file); if(c!='C')	{fclose(file); ddio_SetWorkingDir(old_directory); return -2;}
		c = fgetc(file); if(c!='K')	{fclose(file); ddio_SetWorkingDir(old_directory); return -2;}

		//it appears to be a lock file, check the pid
		DWORD f_pid;
		fread(&f_pid,sizeof(DWORD),1,file);
		fclose(file);

		//check the file id in the file, compared to our pid
		if(f_pid==curr_pid)
		{
			//lock file already exists for the current process
			ddio_SetWorkingDir(old_directory);
			return 3;
		}

		HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS,FALSE,f_pid);
		if(proc)
		{			
			DWORD obj_ret = WaitForSingleObject(proc,0);
			CloseHandle(proc);
			if(obj_ret==WAIT_TIMEOUT)
			{
				//this process exists still
				ddio_SetWorkingDir(old_directory);
				return 0;
			}
		}

		//the process no longer exists, we can create a lock file if needed
		//we'll delete the useless one now		
		ddio_DeleteFile(".lock");
	}

	ddio_SetWorkingDir(old_directory);
	return (found_lock_file_in_dir)?2:1;
}

// Creates a lock file in the specified directory
//	Parameters:
//		dir		Directory for which the lock file should be created in
//	Returns:
//		1		Lock file created
//		2		Lock file created (there was a lock file in that directory, but it belonged
//				to a process that no longer exists)
//		3		Lock file for this process already exists
//		0		Lock file not created, a lock file currently exists in the directory
//		-1		Illegal directory
//		-2		There is a lock file in the directory, but it is in an illegal format
//		-3		Unable to create lock file
int ddio_CreateLockFile(const char *dir)
{
	int result = ddio_CheckLockFile(dir);
	switch(result)
	{
	case 0:
	case -1:
	case -2:
	case 3:
		return result;
	};

	DWORD curr_pid = GetCurrentProcessId();
	char old_directory[_MAX_PATH];
	ddio_GetWorkingDir(old_directory,_MAX_PATH);
	if(!ddio_SetWorkingDir(dir))
		return -1;

	FILE *file;
	file = fopen(".lock","wb");
	if(!file)
	{
		ddio_SetWorkingDir(old_directory);
		return -3;
	}

	fputc('L',file);
	fputc('O',file);
	fputc('C',file);
	fputc('K',file);
	fwrite(&curr_pid,sizeof(DWORD),1,file);

	fclose(file);
	ddio_SetWorkingDir(old_directory);

	// at this point result will either be 1 or 2 from checking the lock file
	// either way, a lock file has been created
	return result;
}

// Deletes a lock file (for the current process) in the specified directory
//	Parameters:
//		dir		Directory for which the lock file should be deleted from
//	Returns:
//		1		Lock file deleted
//		0		Lock file not deleted, the lock file in the directory does not belong to our
//				process
//		-1		Illegal directory
//		-2		A lock file exists in the directory, but wasn't deleted...illegal format
//		-3		Unable to delete file
int ddio_DeleteLockFile(const char *dir)
{
	DWORD curr_pid = GetCurrentProcessId();
	char old_directory[_MAX_PATH];
	ddio_GetWorkingDir(old_directory,_MAX_PATH);
	if(!ddio_SetWorkingDir(dir))
		return -1;

	FILE *file;

	chmod(".lock",_S_IREAD|_S_IWRITE);
	file = fopen(".lock","rb");

	if(!file)
		return 1;

	//check the file, see if it is a lock file
	char c;
	c = fgetc(file); if(c!='L')	{fclose(file); ddio_SetWorkingDir(old_directory); return -2;}
	c = fgetc(file); if(c!='O')	{fclose(file); ddio_SetWorkingDir(old_directory); return -2;}
	c = fgetc(file); if(c!='C')	{fclose(file); ddio_SetWorkingDir(old_directory); return -2;}
	c = fgetc(file); if(c!='K')	{fclose(file); ddio_SetWorkingDir(old_directory); return -2;}

	//it appears to be a lock file, check the pid
	DWORD f_pid;
	fread(&f_pid,sizeof(DWORD),1,file);
	fclose(file);

	//check the file id in the file, compared to our pid
	if(f_pid!=curr_pid)
	{
		//it doesn't belong to 		
		ddio_SetWorkingDir(old_directory);
		return 0;
	}

	//the lock file in the directory belongs to us!
	if(!ddio_DeleteFile(".lock"))
	{
		ddio_SetWorkingDir(old_directory);
		return -3;
	}

	ddio_SetWorkingDir(old_directory);

	return 1;
}