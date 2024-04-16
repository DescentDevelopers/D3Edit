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

	char temp_outputfilename[_MAX_PATH],temp_sourcefilename[_MAX_PATH];

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

	//add quotes around the strings
	sprintf(Source_filename,"\"%s\"",temp_sourcefilename);
	sprintf(Output_filename,"\"%s\"",temp_outputfilename);

	//Display the given options
	//-------------------------
	output("Source: %s\n",Source_filename);
	output("Output: %s\n",Output_filename);
	output("Debug Info: %s\n",(Debug_info_type==DEBUG_NONE)?"None":((Debug_info_type==DEBUG_COFF)?"COFF":"C7"));
	output("Warning Level: %d\n",Warning_level);	
	output("DLL Type: %s\n",(Level_DLL_build)?"Level Script":"Game Script");
	return true;
}

int Step1(STARTUPINFO *si);
void Step2(STARTUPINFO *si);
char output_object[_MAX_PATH];
char Def_filename[_MAX_PATH];
char WarningLevelString[256];
char DebugLevelString[32];
char ChecksumString[64];

void main (int argc, char *argv[])
{
	output("Virtual MS Compiler layer for Descent 3\n");
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

	char old_path[_MAX_PATH],temp_path[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH,old_path);

	bool missing_variables = false;


 	//Check for needed environment variables
	if(!GetEnvironmentVariable("INCLUDE",temp_path,_MAX_PATH)){
		//they are missing the environment variable
		output("INCLUDE environment variable not set\n");
		output("Make sure vcvars32.bat is properly called from your autoexec.bat\n");
		missing_variables = true;
	}

	if(!GetEnvironmentVariable("LIB",temp_path,_MAX_PATH)){
		//they are missing the environment variable
		output("LIB environment variable not set\n");
		output("Make sure vcvars32.bat is properly called from your autoexec.bat\n");
		missing_variables = true;
	}

	if(!GetEnvironmentVariable("MSVCDIR",temp_path,_MAX_PATH)){
		//they are missing the environment variable
		output("MSVCDIR environment variable not set\n");
		output("MSVCDIR Should point to the directory of your Visual C installation\n");
		output("typically \"C:\\Program Files\\Microsoft Visual Studio\\VC98\"\n");
		missing_variables = true;
	}else{
		char big_buffer[_MAX_PATH];
		MakePath(big_buffer,temp_path,"bin",NULL);
		SetCurrentDirectory(big_buffer);
	}

	if(missing_variables){
		return;
	}

	if(Level_DLL_build){
		MakePath(Def_filename,Working_directory,"ms-lvl.def",NULL);
	}else{
		MakePath(Def_filename,Working_directory,"ms-game.def",NULL);
	}

	WarningLevelString[0] = '\0';
	DebugLevelString[0] = '\0';
	ChecksumString[0] = '\0';

	switch(Warning_level){
	case 1:
		strcpy(WarningLevelString,"/W1 ");
		break;
	case 2:
		strcpy(WarningLevelString,"/W2 ");
		break;
	case 3:
		strcpy(WarningLevelString,"/W3 ");
		break;
	case 4:
		strcpy(WarningLevelString,"/W4 ");
		break;
	}

	switch(Debug_info_type){
	case DEBUG_NONE:
		strcpy(DebugLevelString," ");
		break;
	case DEBUG_COFF:
		strcpy(DebugLevelString,"/Od /debug /debugtype:coff ");
		break;
	case DEBUG_CSEVEN:
		strcpy(DebugLevelString,"/Od /debug ");
		break;
	};

#ifndef NEWEDITOR
	sprintf(ChecksumString,"/DCHECKSUM=%d",game_checksum);
#else
	strcpy(ChecksumString,"");
#endif


	//2 step process to build a dll from exe in cl

	//Step 1: Compile source file to object file
	if(!Step1(&si)){
		SetCurrentDirectory(old_path);
		exit(0);
	}		

	//Step 2: Build DLL
	Step2(&si);

	output("Done.");

	SetCurrentDirectory(old_path);
}

int Step1(STARTUPINFO *si)
{
	PROCESS_INFORMATION pi   = {0};
	BOOL bRet = FALSE;

	// build up the command line
	char command_line[256];
	char filename[_MAX_PATH];
	char wd_path[_MAX_PATH];
	
	GetCurrentDirectory(_MAX_PATH,wd_path);
	_splitpath(Source_filename,NULL,NULL,filename,NULL);
	strcat(filename,".obj");
	MakePath(output_object,wd_path,filename,NULL);

	switch(Debug_info_type){
	case DEBUG_NONE:
		strcpy(DebugLevelString,"/O2 ");
		break;
	case DEBUG_COFF:
		strcpy(DebugLevelString,"/Od /Zi");
		break;
	case DEBUG_CSEVEN:
		strcpy(DebugLevelString,"/Od /Zi");
		break;
	};

	//remove the object file if it exists
	FILE *file = fopen(output_object,"rb");

	if(file){
		fclose(file);
		remove(output_object);
	}

	sprintf(command_line,"cl.exe %s /nologo /MTd %s %s %s /Fo\"%s\" /GD /Gd /c",Source_filename,WarningLevelString,DebugLevelString,ChecksumString,output_object);

	bRet = CreateProcess (NULL, command_line, NULL, NULL, TRUE, 0, NULL, NULL, si, &pi);
	
	if (bRet){
		WaitForSingleObject (pi.hProcess, INFINITE);
		CloseHandle (pi.hProcess);            
		CloseHandle (pi.hThread);
	}

	file = fopen(output_object,"rb");
	if(!file){
		//there was an error compiling...bail!
		return 0;
	}else{
		fclose(file);
	}
	return 1;
}

void Step2(STARTUPINFO *si)
{
	PROCESS_INFORMATION pi   = {0};
	BOOL bRet = FALSE;

	// build up the command line
	char command_line[256];

	switch(Debug_info_type){
	case DEBUG_NONE:
		strcpy(DebugLevelString," ");
		break;
	case DEBUG_COFF:
		strcpy(DebugLevelString," /debug /debugtype:coff ");
		break;
	case DEBUG_CSEVEN:
		strcpy(DebugLevelString," /debug ");
		break;
	};

	sprintf(command_line,"link.exe \"%s\" /nologo /dll %s /subsystem:windows /machine:I386 /def:\"%s\" /out:%s /INCREMENTAL:no /PDB:none",output_object,DebugLevelString,Def_filename,Output_filename);

	bRet = CreateProcess (NULL, command_line, NULL, NULL, TRUE, 0, NULL, NULL, si, &pi);
	
	if (bRet){
		WaitForSingleObject (pi.hProcess, INFINITE);
		CloseHandle (pi.hProcess);            
		CloseHandle (pi.hThread);
	}

	char fullpath[_MAX_PATH];
	char filename[_MAX_PATH];
	char drivename[_MAX_DRIVE], dirname[_MAX_PATH];
	char temp[_MAX_PATH];

	_splitpath(Source_filename, drivename, dirname, filename,NULL);
	sprintf(fullpath, "%s%s", drivename, dirname);

	strcpy(temp,filename);
	strcat(temp,".lib");
	MakePath(dirname,(fullpath[0]=='\"')?&fullpath[1]:fullpath,temp,NULL);
	//delete output lib
	if(remove(dirname)){
		output("Warning: Unable to remove temporary file created in step 2 (%s)\n",dirname);
	}

	strcpy(temp,filename);
	strcat(temp,".exp");
	MakePath(dirname,(fullpath[0]=='\"')?&fullpath[1]:fullpath,temp,NULL);
	//delete output files
	if(remove(dirname)){
		output("Warning: Unable to remove temporary file created in step 2 (%s)\n",dirname);
	}

	//delete output files
	if(remove(output_object)){
		output("Warning: Unable to remove temporary file created in step 2 (%s)\n",output_object);
	}

}
