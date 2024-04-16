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
 

/*
VirtualGCC

Descent 3 Virtual Compiler layer for GCC compiler.

Currently assumes that the following environment variables are setup before calling:

PATH :		Should point to the directory containing the GCC bin directory

The gcc compiler tested is:
egcs-1.1.2
mingw distribution

http://www.xraylith.wisc.edu/~khan/software/gnu-win32/
ftp://ftp.xraylith.wisc.edu/pub/khan/gnu-win32/mingw32/egcs-1.1.2/

mingw should be the packaged used, and not Cygwin (as it has license and dll dependency issues)

NOTE: I think there is problems with debugging information, I think I might have to 
always turn it off.

*/
#include <windows.h>    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

typedef enum{DEBUG_NONE=0,DEBUG_COFF,DEBUG_CSEVEN}Debug_type;
char Source_filename[_MAX_PATH];
char Output_filename[_MAX_PATH];
char Working_directory[_MAX_PATH];
char DLLInit_filename[_MAX_PATH];
Debug_type Debug_info_type;
char Warning_level;
bool Level_DLL_build;
unsigned int game_checksum;

#define CL_SOURCEFILE	0
#define CL_DEBUGINFO	1
#define CL_OUTPUTFILE	2
#define CL_WARNINGLVL	3
#define CL_DIRECTORY	4
#define CL_DLLTYPE		5
#define CL_CHECKSUM		6
typedef struct{
	char *string;
	unsigned short command;
}tCommandLineOption;
tCommandLineOption CommandLineOptions[] = {
	{"-F",CL_SOURCEFILE},
	{"-D",CL_DEBUGINFO},
	{"-O",CL_OUTPUTFILE},
	{"-W",CL_WARNINGLVL},
	{"-DIR",CL_DIRECTORY},
	{"-LEVEL",CL_DLLTYPE},
	{"-CHECKSUM",CL_CHECKSUM}};

bool FindGCCPath(char *gcc_bin_path);

void output(char *format, ... )
{
	char buffer[512];
	va_list list;
	va_start(list,format);
	vsprintf(buffer,format,list);
	va_end(list);

	fprintf(stdout,buffer);
	fflush(stdout);
}

// Constructs a path in the local file system's syntax
// 	newPath: stores the constructed path
//  absolutePathHeader: absolute path on which the sub directories will be appended
//						(specified in local file system syntax)
//  takes a variable number of subdirectories which will be concatenated on to the path
//		the last argument in the list of sub dirs *MUST* be NULL to terminate the list
void MakePath(char* newPath, const char* absolutePathHeader, const char* subDir, ...)
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

bool CollectArguments(int argc, char *argv[])
{
	// initialize data that will use during compilation
	Source_filename[0]	= '\0';
	Output_filename[0]	= '\0';
	Working_directory[0]= '\0';
	DLLInit_filename[0] = '\0';
	Debug_info_type		= DEBUG_NONE;
	Warning_level		= 3;
	Level_DLL_build		= false;
	game_checksum		= 0;

	int arg = 1,index;
	int command_option_count = sizeof(CommandLineOptions)/sizeof(tCommandLineOption);

	while( arg < argc ){
		index = 0;

		while(index<command_option_count){
			if(!stricmp(argv[arg],CommandLineOptions[index].string)){
				break;
			}
			index++;
		}

		if(index>=command_option_count){
			//malformed command option
			output("Warning: Ignoring malformed command line option: %s\n",argv[arg]);
		}else{
			switch(CommandLineOptions[index].command){
			case CL_SOURCEFILE:
				arg++;
				if(arg<argc){
					strcpy(Source_filename,argv[arg]);					
				}else{
					output("Error: Expecting command line data for %s\n",argv[arg-1]);
				}
				break;
			case CL_DEBUGINFO:
				arg++;
				if(arg<argc){
					if(!stricmp(argv[arg],"COFF")){
						Debug_info_type = DEBUG_COFF;
					}else if(!stricmp(argv[arg],"C7")){
						Debug_info_type = DEBUG_CSEVEN;
					}				
				}else{
					output("Error: Expecting command line data for %s\n",argv[arg-1]);
				}
				break;
			case CL_OUTPUTFILE:
				arg++;
				if(arg<argc){
					strcpy(Output_filename,argv[arg]);					
				}else{
					output("Error: Expecting command line data for %s\n",argv[arg-1]);
				}
				break;
			case CL_WARNINGLVL:
				arg++;
				if(arg<argc){
					Warning_level = atoi(argv[arg]);
					if(Warning_level<0)	Warning_level = 0;
					if(Warning_level>4) Warning_level = 4;
				}else{
					output("Error: Expecting command line data for %s\n",argv[arg-1]);
				}
				break;
			case CL_DIRECTORY:
				arg++;
				if(arg<argc){
					strcpy(Working_directory,argv[arg]);					
				}else{
					output("Error: Expecting command line data for %s\n",argv[arg-1]);
				}
				break;
			case CL_DLLTYPE:
				Level_DLL_build = true;
				break;
			case CL_CHECKSUM:
				arg++;
				if(arg<argc){
					char buffer[64],*end;
					strcpy(buffer,argv[arg]);
					game_checksum = strtoul(buffer,&end,10);
				}else{
					output("Error: Expecting command line data for %s\n",argv[arg-1]);
				}
				break;
			default:
				output("Warning: Internal command line parsing error, unhandled option %s\n",argv[arg]);
				break;
			}
		}

		arg++;
	}

	if(Source_filename[0]=='\0'){
		//we're missing the required -f option
		output("Critical Error: Missing source filename (-f) option\n");
		return false;
	}

	if(Working_directory[0]=='\0'){
		//we're missing the required -dir option
		output("Critical Error: Missing working directory (-dir) option\n");
		return false;
	}

#ifndef NEWEDITOR
	if(game_checksum==0)
	{
		//we're missing the required -checksum option
		output("Critical Error: Mission -checksum option\n");
		return false;
	}
#endif

	char temp_outputfilename[_MAX_PATH],temp_sourcefilename[_MAX_PATH],temp_dllinitfilename[_MAX_PATH];

	//setup output filename if it wasn't given
	if(Output_filename[0]=='\0'){
		char filename[_MAX_PATH],ext[_MAX_EXT];
		_splitpath(Source_filename,NULL,NULL,filename,ext);
		strcat(filename,".dll");
		MakePath(temp_outputfilename,Working_directory,filename,NULL);
	}else{
		//setup with correct path
		char filename[_MAX_PATH],ext[_MAX_EXT];
		_splitpath(Output_filename,NULL,NULL,filename,ext);
		strcat(filename,ext);
		MakePath(temp_outputfilename,Working_directory,filename,NULL);
	}

	//setup the source filename
	char filename[_MAX_PATH],ext[_MAX_EXT];
	_splitpath(Source_filename,NULL,NULL,filename,ext);
	strcat(filename,ext);
	MakePath(temp_sourcefilename,Working_directory,filename,NULL);

	MakePath(temp_dllinitfilename,Working_directory,"dllinit.c",NULL);

	//bash input/output filename's to all lowercase (so it doesn't confuse gcc)
	char *ptr;
	ptr = temp_sourcefilename;
	while(*ptr) { *ptr = tolower(*ptr); ptr++;}
	ptr = temp_outputfilename;
	while(*ptr) { *ptr = tolower(*ptr); ptr++;}

	//add quotes around the strings
	sprintf(Source_filename,"\"%s\"",temp_sourcefilename);
	sprintf(Output_filename,"\"%s\"",temp_outputfilename);
	sprintf(DLLInit_filename,"\"%s\"",temp_dllinitfilename);

	//Display the given options
	//-------------------------
	output("Source: %s\n",Source_filename);
	output("Output: %s\n",Output_filename);
	output("DLLinit: %s\n",DLLInit_filename);
	output("Debug Info: %s\n",(Debug_info_type==DEBUG_NONE)?"None":((Debug_info_type==DEBUG_COFF)?"COFF":"C7"));
	output("Warning Level: %d\n",Warning_level);	
	output("DLL Type: %s\n",(Level_DLL_build)?"Level Script":"Game Script");
	return true;
}

bool Step1(STARTUPINFO *si);
void Step2(STARTUPINFO *si);
void Step3(STARTUPINFO *si);
void Step4(STARTUPINFO *si);
char output_object[_MAX_PATH];
char output_dllinit[_MAX_PATH];
char Def_filename[_MAX_PATH];
char WarningLevelString[256];
char DebugLevelString[32];
char ChecksumString[64];

void main (int argc, char *argv[])
{
	output("Virtual GCC Compiler layer for Descent 3\n");
	output("Copyright 1999 Outrage Entertainment\n");
	if(!CollectArguments(argc,argv))
		return;
	
	STARTUPINFO         si   = {0};
	// Make child process use this app's standard files.
	si.cb = sizeof(si);        
	si.dwFlags    = STARTF_USESTDHANDLES;
	si.hStdInput  = GetStdHandle (STD_INPUT_HANDLE);
	si.hStdOutput = GetStdHandle (STD_OUTPUT_HANDLE);
	si.hStdError  = GetStdHandle (STD_ERROR_HANDLE);

	char old_path[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH,old_path);

	bool missing_variables = false;

 	//Check for needed environment variables
	char gcc_bin_path[_MAX_PATH];
	if(FindGCCPath(gcc_bin_path))
	{
		//found gcc.exe
		output("Using gcc.exe found in %s\n",gcc_bin_path);
		SetCurrentDirectory(gcc_bin_path);
	}else
	{
		output("gcc.exe not found in your path, please verify that your PATH environment variable is setup correctly, and it includes your bin directory of your gcc installation\n");
		output("example:\n");
		output("set PATH=C:\\Windows;C:\\Windows\\Command;C:\\EGCS-1.1.2\\bin\n");
		missing_variables = true;
	}

	if(missing_variables){
		return;
	}

	if(Level_DLL_build){
		MakePath(Def_filename,Working_directory,"gcc-lvl.def",NULL);
	}else{
		MakePath(Def_filename,Working_directory,"gcc-game.def",NULL);
	}

	WarningLevelString[0] = '\0';
	DebugLevelString[0] = '\0';
	ChecksumString[0] = '\0';

	switch(Warning_level){
	case 0:
		strcpy(WarningLevelString,"-w");
		break;
	case 1:
		strcpy(WarningLevelString,"-W -Wparentheses ");
		break;
	case 2:
		strcpy(WarningLevelString,"-W -Wreturn-type -Wparentheses -Wimplicit");
		break;
	case 3:
		strcpy(WarningLevelString,"-W -Wreturn-type -Wunused -Wformat -Wparentheses -Wimplicit");
		break;
	case 4:
		strcpy(WarningLevelString,"-Wall -W -Wreturn-type -Wunused -Wformat -Wparentheses -Wimplicit");
		break;
	}

	if(Debug_info_type==DEBUG_CSEVEN || Debug_info_type==DEBUG_COFF)
	{
		output("Warning: C7/COFF Debug information not supported, using gcc default debug info\n");
	}

#ifndef NEWEDITOR
	sprintf(ChecksumString,"-DCHECKSUM=%d",game_checksum);
#else
	strcpy(ChecksumString,"");
#endif

	switch(Debug_info_type){
	case DEBUG_NONE:
		strcpy(DebugLevelString,"-O2");
		break;
	case DEBUG_COFF:
	case DEBUG_CSEVEN:
		//strcpy(DebugLevelString,"-gcoff");
		strcpy(DebugLevelString,"-g");
		break;
	};

	//2 step process to build a dll from exe in gcc

	//Step 1: Compile source file to object file
	if(!Step1(&si))
	{
		SetCurrentDirectory(old_path);
		exit(1);
	}

	//Step 2: DLL
	Step2(&si);

	output("Done.");

	SetCurrentDirectory(old_path);
}

bool Step1(STARTUPINFO *si)
{
	PROCESS_INFORMATION pi   = {0};
	BOOL bRet = FALSE;
	FILE *file;

	// build up the command line
	char command_line[256];
	char filename[_MAX_PATH];
	_splitpath(Source_filename,NULL,NULL,filename,NULL);
	strcat(filename,".o");
	MakePath(output_object,Working_directory,filename,NULL);

	_splitpath(DLLInit_filename,NULL,NULL,filename,NULL);
	strcat(filename,".o");
	MakePath(output_dllinit,Working_directory,filename,NULL);
	
	//build script
	sprintf(command_line,"gcc.exe -I. -I%s -mwindows -o %s -c %s %s %s %s",Working_directory,output_object,Source_filename,WarningLevelString,ChecksumString,DebugLevelString);
	bRet = CreateProcess (NULL, command_line, NULL, NULL, TRUE, 0, NULL, NULL, si, &pi);
	if (bRet){
		WaitForSingleObject (pi.hProcess, INFINITE);
		CloseHandle (pi.hProcess);            
		CloseHandle (pi.hThread);
	}
	//check for success
	file = fopen(output_object,"rb");
	if(!file)
	{
		//error compiling!!
		output("Error compiling %s\n",Source_filename);
		return false;
	}

	//add dllinit function
	sprintf(command_line,"gcc.exe -I. -I%s -mwindows -o %s -c %s %s %s",Working_directory,output_dllinit,DLLInit_filename,WarningLevelString,DebugLevelString);
	bRet = CreateProcess (NULL, command_line, NULL, NULL, TRUE, 0, NULL, NULL, si, &pi);
	if (bRet){
		WaitForSingleObject (pi.hProcess, INFINITE);
		CloseHandle (pi.hProcess);            
		CloseHandle (pi.hThread);
	}

	//check for success
	file = fopen(output_dllinit,"rb");
	if(!file)
	{
		//error compiling!!
		output("Error compiling %s\n",DLLInit_filename);
		return false;
	}

	return true;
}

void Step2(STARTUPINFO *si)
{
	PROCESS_INFORMATION pi   = {0};
	BOOL bRet = FALSE;

	// build up the command line
	char command_line[256];
	sprintf(command_line,"dllwrap.exe --export-all --def %s -o %s %s %s -mwindows",Def_filename,Output_filename,output_object,output_dllinit);

	bRet = CreateProcess (NULL, command_line, NULL, NULL, TRUE, 0, NULL, NULL, si, &pi);
	
	if (bRet){
		WaitForSingleObject (pi.hProcess, INFINITE);
		CloseHandle (pi.hProcess);            
		CloseHandle (pi.hThread);
	}

}

bool FindGCC(char *path)
{	
	if(!SetCurrentDirectory(path))
		return false;

	bool found_it = false;

	//look for gcc.exe in this directory
	HANDLE hFindFile = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA FindFileData;

	hFindFile = FindFirstFile("gcc.exe", &FindFileData);
	if (hFindFile != INVALID_HANDLE_VALUE) {
		//found it!!!!
		found_it = true;
	}
	else {
		//not found
		found_it = false;
	}

	if (hFindFile != INVALID_HANDLE_VALUE) FindClose(hFindFile);

	return found_it;
}

bool FindGCCPath(char *gcc_bin_path)
{
	char path_value[1024];
	if(!GetEnvironmentVariable("PATH",path_value,1024)){
		return false;
	}

	char old_path[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH,old_path); //save working directory

	//it's ; seperated, check each directory for gcc.exe
	char *start_ptr = path_value;
	char *end_ptr = path_value;
	bool done = false;
	while(!done)
	{
		while( *end_ptr && *end_ptr!=';') end_ptr++;
		if(*end_ptr=='\0')
		{
			//end of string
			done = true;
		}else
		{
			*end_ptr = '\0';
		}

		if(end_ptr>start_ptr)
		{
			//we have a path to check
			if(FindGCC(start_ptr))
			{
				strcpy(gcc_bin_path,start_ptr);
				SetCurrentDirectory(old_path);	//restore working directory
				return true;
			}

			if(!done)
			{
				end_ptr++;	//move to next character
				start_ptr = end_ptr;
			}
		}
	}

	SetCurrentDirectory(old_path);	//restore working directory
	return false;
}
