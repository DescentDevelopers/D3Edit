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
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef MACINTOSH
#include <stat.h>	
#else
#include <sys/stat.h>	
#endif
#ifndef __LINUX__
//Non-Linux Builds
#include <io.h>
#else
//Linux Builds
#include "linux/linux_fix.h"
#endif
#include "byteswap.h"
#include "hogfile.h"
#include "pstypes.h"
#include "macros.h"
#include "mem.h"
#include "ddio.h"
/*	HOG FILE FORMAT v2.0 
		
		HOG_TAG_STR			[strlen()]
		NFILES				[int32]
		HDRINFO				[HOG_HDR_SIZE]
		FILE_TABLE			[sizeof(FILE_ENTRY) * NFILES]
		FILE 0				[filelen(FILE 0)]
		FILE 1				[filelen(FILE 1)]
		.
		.
		.
		FILE NFILES-1		[filelen(NFILES -1)]
*/
char hogerr_filename[PSPATHNAME_LEN];  // Used by NewHogFile() to return errors
////////////////////////////////////////////////////////////////////////
/*	FileCopy
		used to copy one file to another.
*/
bool FileCopy(FILE *ofp,FILE *ifp,int length)
{
	#define BUFFER_SIZE			(1024*1024)			//	1 meg
	char *buffer;
	buffer = (char *)mem_malloc(BUFFER_SIZE);
	if (!buffer) 
		return false;
	while (length) 
	{
		size_t n,read_len;
		read_len = min(length,(int)BUFFER_SIZE);
		n = fread( buffer, 1, read_len, ifp );
		if ( n != read_len )	{
			mem_free(buffer);
			return false;
		}
		if (fwrite( buffer, 1, read_len, ofp) != read_len )	{
			mem_free(buffer);
			return false;
		}
		length -= read_len;
	}
	mem_free(buffer);
	return true;
}
bool ReadHogHeader(FILE *fp, tHogHeader *header)
{
	int res=0;
	res = fread(&header->nfiles, sizeof(header->nfiles), 1, fp);
	header->nfiles = INTEL_INT(header->nfiles);
	res = fread(&header->file_data_offset, sizeof(header->file_data_offset), 1, fp);
	header->file_data_offset = INTEL_INT(header->file_data_offset);
	
	
	if (res) 
		return true;
	else
		return false;
}
bool ReadHogEntry(FILE *fp, tHogFileEntry *entry)
{
	int res=0;
	res = fread(entry->name, sizeof(char), PSFILENAME_LEN+1, fp);
	res = fread(&entry->flags, sizeof(entry->flags), 1, fp);
	entry->flags = INTEL_INT(entry->flags);
	res = fread(&entry->len, sizeof(entry->len), 1, fp);
	entry->len = INTEL_INT(entry->len);
	res = fread(&entry->timestamp, sizeof(entry->timestamp), 1, fp);
	entry->timestamp = INTEL_INT(entry->timestamp);
	
	if (res) 
		return true;
	else
		return false;
}


bool WRITE_FILE_ENTRY(FILE *fp, tHogFileEntry *entry)
{
	int res=0;
	res = fwrite(entry->name, sizeof(char), PSFILENAME_LEN+1, fp);
	res = fwrite(&entry->flags, sizeof(entry->flags), 1, fp);
	res = fwrite(&entry->len, sizeof(entry->len), 1, fp);
	res = fwrite(&entry->timestamp, sizeof(entry->timestamp), 1, fp);
	
	if (res) 
		return true;
	else
		return false;
}
////////////////////////////////////////////////////////////////////////
//	create new hog file
int NewHogFile(const char *hogname, int nfiles, const char **filenames)
{
	unsigned i;
	int table_pos;
	FILE *hog_fp;
	tHogHeader header;
	tHogFileEntry *table;
	char ext[_MAX_EXT];
	hogerr_filename[0]='\0';
//	allocate file table
	if (nfiles <= 0) 
		return HOGMAKER_ERROR;
	table = new tHogFileEntry[nfiles];
	if (!table) 
		return HOGMAKER_MEMORY;
//	create new file
	hog_fp = fopen( hogname, "wb" );
	if ( hog_fp == NULL )		{
		delete[] table;
		strcpy(hogerr_filename,hogname);
		return HOGMAKER_OPENOUTFILE;
	}
//write the tag
	if (!fwrite(HOG_TAG_STR, strlen(HOG_TAG_STR), 1, hog_fp ))	{
		delete[] table;
		fclose(hog_fp);
		strcpy(hogerr_filename,hogname);
		return HOGMAKER_OUTFILE;
	}
//write number of files
	ubyte filler = 0xff;
	header.nfiles = (unsigned)nfiles;
	header.file_data_offset = strlen(HOG_TAG_STR) + HOG_HDR_SIZE + (sizeof(tHogFileEntry) * header.nfiles);
	if (!fwrite(&header.nfiles,sizeof(header.nfiles),1,hog_fp))	{
		delete[] table;
		fclose(hog_fp);
		strcpy(hogerr_filename,hogname);
		return HOGMAKER_OUTFILE;
	}
	if (!fwrite(&header.file_data_offset,sizeof(header.file_data_offset),1,hog_fp))	{
		delete[] table;
		fclose(hog_fp);
		strcpy(hogerr_filename,hogname);
		return HOGMAKER_OUTFILE;
	}
	// write out filler
	for(i=0; i < HOG_HDR_SIZE-sizeof(tHogHeader); i++)
		if (!fwrite(&filler,sizeof(ubyte),1,hog_fp))	{
			delete[] table;
			fclose(hog_fp);
			strcpy(hogerr_filename,hogname);
			return HOGMAKER_OUTFILE;
		}
//save file position of index table and write out dummy table
	table_pos = strlen(HOG_TAG_STR) + HOG_HDR_SIZE;
	memset(&table[0], 0, sizeof(table[0]));
	for (i = 0; i < header.nfiles; i++)
	{
		if (!WRITE_FILE_ENTRY(hog_fp, &table[0])) {
			delete[] table;
			fclose(hog_fp);
			strcpy(hogerr_filename,hogname);
			return HOGMAKER_OUTFILE;
		}
	}
//write files (& build index)
	for (i=0;i<header.nfiles;i++) 
	{
		FILE *ifp;
		#if defined(__LINUX__) || defined(MACINTOSH)
		struct stat mystat;
		#else
		struct _stat mystat;
		#endif
		
		ifp = fopen(filenames[i],"rb");
		if ( ifp == NULL )	{
			delete[] table;
			fclose(hog_fp);
			strcpy(hogerr_filename,filenames[i]);
			return HOGMAKER_INFILE;
		}
		//JEFF: make call to ddio lib, linux doesn't have _splitpath
		//_splitpath(filenames[i],NULL,NULL,table[i].name,ext);
		ddio_SplitPath(filenames[i],NULL,table[i].name,ext);
		_fstat(fileno(ifp), &mystat);
	
		strcat(table[i].name,ext);
		table[i].flags = 0;
	#ifdef MACINTOSH
		table[i].len = mystat.st_size;
	#else
		table[i].len = _filelength(fileno(ifp));
	#endif
		table[i].timestamp = mystat.st_mtime;
		if (!FileCopy(hog_fp,ifp,table[i].len)) {
			delete[] table;
			fclose(hog_fp);
			strcpy(hogerr_filename,filenames[i]);
			return HOGMAKER_COPY;
		}
		fclose(ifp);
	}
//now write the real index
	fseek(hog_fp,table_pos,SEEK_SET);
	for (i = 0; i < header.nfiles; i++)
	{
		if (!WRITE_FILE_ENTRY(hog_fp, &table[i])) {
			delete[] table;
			fclose(hog_fp);
			strcpy(hogerr_filename,hogname);
			return HOGMAKER_OUTFILE;
		}
	}
//	cleanup
	fclose( hog_fp );	
	delete[] table;
	return HOGMAKER_OK;
}
// A modifed version of NewHogFile()
// This one also takes a pointer to a function that will perform
// progress updates (for the user)
int CreateNewHogFile(const char *hogname, int nfiles, const char **filenames,
					 void(* UpdateFunction)(char *))
{
	unsigned i;
	int table_pos;
	FILE *hog_fp;
	tHogHeader header;
	tHogFileEntry *table;
	char ext[_MAX_EXT];
	hogerr_filename[0]='\0';
//	allocate file table
	if (nfiles <= 0) 
		return HOGMAKER_ERROR;
	table = new tHogFileEntry[nfiles];
	if (!table) 
		return HOGMAKER_MEMORY;
//	create new file
	hog_fp = fopen( hogname, "wb" );
	if ( hog_fp == NULL )		{
		delete[] table;
		strcpy(hogerr_filename,hogname);
		return HOGMAKER_OPENOUTFILE;
	}
//write the tag
	if (!fwrite(HOG_TAG_STR, strlen(HOG_TAG_STR), 1, hog_fp ))	{
		delete[] table;
		fclose(hog_fp);
		strcpy(hogerr_filename,hogname);
		return HOGMAKER_OUTFILE;
	}
//write number of files
	ubyte filler = 0xff;
	header.nfiles = (unsigned)nfiles;
	header.file_data_offset = strlen(HOG_TAG_STR) + HOG_HDR_SIZE + (sizeof(tHogFileEntry) * header.nfiles);
	if (!fwrite(&header.nfiles,sizeof(header.nfiles),1,hog_fp))	{
		delete[] table;
		fclose(hog_fp);
		strcpy(hogerr_filename,hogname);
		return HOGMAKER_OUTFILE;
	}
	if (!fwrite(&header.file_data_offset,sizeof(header.file_data_offset),1,hog_fp))	{
		delete[] table;
		fclose(hog_fp);
		strcpy(hogerr_filename,hogname);
		return HOGMAKER_OUTFILE;
	}
	// write out filler
	for(i=0; i < HOG_HDR_SIZE-sizeof(tHogHeader); i++)
		if (!fwrite(&filler,sizeof(ubyte),1,hog_fp))	{
			delete[] table;
			fclose(hog_fp);
			strcpy(hogerr_filename,hogname);
			return HOGMAKER_OUTFILE;
		}
//save file position of index table and write out dummy table
	table_pos = strlen(HOG_TAG_STR) + HOG_HDR_SIZE;
	memset(&table[0], 0, sizeof(table[0]));
	for (i = 0; i < header.nfiles; i++)
	{
		if (!WRITE_FILE_ENTRY(hog_fp, &table[0])) {
			delete[] table;
			fclose(hog_fp);
			strcpy(hogerr_filename,hogname);
			return HOGMAKER_OUTFILE;
		}
	}
//write files (& build index)
	for (i=0;i<header.nfiles;i++) 
	{
		FILE *ifp;
		#if defined(__LINUX__) || defined(MACINTOSH)
		struct stat mystat;
		#else
		struct _stat mystat;
		#endif
		ifp = fopen(filenames[i],"rb");
		if ( ifp == NULL )	{
			delete[] table;
			fclose(hog_fp);
			strcpy(hogerr_filename,filenames[i]);
			return HOGMAKER_INFILE;
		}
		//using ddio_SplitPath since it is linux friendly
		//_splitpath(filenames[i],NULL,NULL,table[i].name,ext);
		ddio_SplitPath(filenames[i],NULL,table[i].name,ext);
		_fstat(fileno(ifp), &mystat);
		strcat(table[i].name,ext);
		table[i].flags = 0;
	#ifdef MACINTOSH
		table[i].len = mystat.st_size;
	#else
		table[i].len = _filelength(fileno(ifp));
	#endif
		table[i].timestamp = mystat.st_mtime;
		if (!FileCopy(hog_fp,ifp,table[i].len)) {
			delete[] table;
			fclose(hog_fp);
			strcpy(hogerr_filename,filenames[i]);
			return HOGMAKER_COPY;
		}
		fclose(ifp);
		// Setup the update message and send it
		char msg[256];
		int ipct = int(100.0*(double(i)/double(header.nfiles)));
		sprintf(msg,"Creating Hog File... (%d%% done)",ipct);
		if(UpdateFunction!=NULL) UpdateFunction(msg);
	}
//now write the real index
	fseek(hog_fp,table_pos,SEEK_SET);
	for (i = 0; i < header.nfiles; i++)
	{
		if (!WRITE_FILE_ENTRY(hog_fp, &table[i])) {
			delete[] table;
			fclose(hog_fp);
			strcpy(hogerr_filename,hogname);
			return HOGMAKER_OUTFILE;
		}
	}
//	cleanup
	fclose( hog_fp );	
	delete[] table;
	// Setup the update message and send it
	char msg[256];
	sprintf(msg,"Done Creating Hog File.");
	if(UpdateFunction!=NULL) UpdateFunction(msg);
	return HOGMAKER_OK;
}
