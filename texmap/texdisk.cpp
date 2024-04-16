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
 #include <stdio.h>
#include <stdlib.h>
#include "texture.h"
#include "mono.h"

int tex_LoadTexture (texture *texptr,char *filename)
{
	// Loads a PCX file into a 128 x 128 texture.
	// The pcx file must be 256 colors
	// Returns 1 if successful, 0 if failed

	FILE *infile;
	int run=0,i,total,t;
	short xmin,ymin,xmax,ymax;
	int width,height;
	ubyte buf,temp[128],red,green,blue;
	ubyte texbuf[320*256],c;
	ushort clut[256];


	infile=(FILE *)fopen (filename,"rb");
	if (!infile)
	{
		//mprintf ((0,"Unable to open %s.\n",filename));
		return 0;
	}
	

	fread (temp,4,1,infile);
	fread (&xmin,2,1,infile);
	fread (&ymin,2,1,infile);
	fread (&xmax,2,1,infile);
	fread (&ymax,2,1,infile);
	fread (temp,116,1,infile);

	width=1+xmax-xmin;
	height=1+ymax-ymin;
	total=width*height; 
	
	while (run < total)
	{
		fread (&buf,1,1,infile);
		if (buf>=192)
		{
	        unsigned char tb=0;
			fread (&tb,1,1,infile);
			for (i=0;i<(buf-192);i++,run++)
   				texbuf[run]=tb;
		}
		else
		{
			texbuf[run]=buf;
			run++;
		}
    }
  
	fgetc(infile);

	// build a 5-6-5 lookup table
	for (i=0;i<256;i++)
	{
		fread (&red,1,1,infile);
		fread (&green,1,1,infile);
		fread (&blue,1,1,infile);
		red>>=2; green>>=2; blue>>=2;

		clut[i] = (((red & 0x3f)>>1) << 11) |
				    ((green & 0x3f) << 5) |
					((blue & 0x3f)>>1);
		
	}


	// Convert this texture into 5-6-5 format
	for (i=0;i<TEXTURE_HEIGHT;i++)
		for (t=0;t<TEXTURE_WIDTH;t++)
		{
			c=texbuf[((i%height)*width)+(t%width)];
			texptr->data[0][i*TEXTURE_WIDTH+t]=clut[c];
		}

	fclose (infile);
	return (1);
}


int tex_LoadTGATexture (texture *texptr,char *filename)
{
	// Loads a TGA file into a 128 x 128 texture.
	// The TGA must be type 2 (RGB, uncompressed) and be in 32 bit format
	// Returns 1 if successful, 0 if failed

	FILE *infile;
	ubyte image_id_len,color_map_type,image_type,pixsize,descriptor;
	ubyte dumbbuf[20];
	ushort width,height;
	unsigned int pixel;
	int i,t;
		
	infile=(FILE *)fopen (filename,"rb");
	if (!infile)
	{
		mprintf ((0,"LoadTGA: Unable to open %s.\n",filename));
		return 0;
	}
	

	fread (&image_id_len,1,1,infile);
	fread (&color_map_type,1,1,infile);
	fread (&image_type,1,1,infile);

	if (image_id_len!=0 || color_map_type!=0 || image_type!=2)
	{
		mprintf ((0,"LoadTGA: Can't read this type of TGA. File: %s\n",filename));
		return 0;
	}
	fread (&dumbbuf,1,5,infile);		// ignore color map specification
	fread (&dumbbuf,1,2,infile);		// ignore x origin
	fread (&dumbbuf,1,2,infile);		// ignore y origin

	fread (&width,2,1,infile);
	fread (&height,2,1,infile);

	if (width!=128 || height!=128)
	{
		mprintf ((0,"LoadTGA: Width or height for this image is invalid.  File: %s",filename));
		return 0;
	}

	fread (&pixsize,1,1,infile);
	if (pixsize!=32)
	{
		mprintf ((0,"LoadTGA: This file has a pixsize of field of %d, it should be 32. File: %s",pixsize,filename));
		return 0;
	}
	fread (&descriptor,1,1,infile);
	if (descriptor!=8)
	{
		mprintf ((0,"LoadTGA: Descriptor field must be 8, but this is %d. File:%s\n",descriptor,filename));
		return 0;
	}
	for (i=0;i<128;i++)
	{
		for (t=0;t<128;t++)
		{
			fread (&pixel,4,1,infile);
			int red=((pixel>>16) & 0xFF);
			int green=((pixel>>8) & 0xFF);
			int blue=((pixel) & 0xFF);
			int alpha=((pixel>>24) & 0xFF);
			
			int newred=red>>3;
			int newgreen=green>>2;
			int newblue=blue>>3;
			ushort newpix=(newred<<11) | (newgreen << 5) | (newblue);
			if (alpha==0)
				newpix=TRANSPARENT_COLOR;
			else
			{
				if (newpix==TRANSPARENT_COLOR)
					newpix=REPLACEMENT_COLOR;
			}
			
			texptr->data[0][(127-i)*TEXTURE_WIDTH+t]=newpix;
		}
	}
	
	fclose (infile);
	tex_GenerateMipMaps (texptr);
	return (1);
}

void tex_GenerateMipMaps (texture *texptr)
{
	// Given a source texture, generates two mip maps for it

	int width=texptr->width[0];
	int height=texptr->height[0];
	int jump=2;
	ushort *srcptr;
	ushort rsum,gsum,bsum,asum;
	int miplevel,i,t;
	
	for (miplevel=1;miplevel<NUM_MIP_LEVELS;miplevel++)
	{
		width/=2; height/=2;
		

		texptr->width[miplevel]=width;
		texptr->height[miplevel]=height;


		for (i=0;i<height;i++)
		{
			int adjheight=(i*jump)*texptr->width[miplevel-1];
		
			for (t=0;t<width;t++)
			{
				
				int adjwidth=(t*jump);

				srcptr=texptr->data[miplevel-1]+adjheight+adjwidth;

				rsum=gsum=bsum=asum=0;
	
	
				for (int y=0;y<2;y++)
					for (int x=0;x<2;x++)
					{
						ushort pix=srcptr[y*texptr->width[miplevel-1]+x];
						ushort r=pix>>11;
						ushort g=(pix>>5) & 63;
						ushort b=(pix & 31);

						
							
						rsum+=r;
						if (g!=63)
							gsum+=g;
						bsum+=b;
						if (g==63)
							asum++;
					}

				// Average our source pixels
				rsum/=4;
				gsum/=4;
				bsum/=4;

				ushort destpix=(rsum<<11) | (gsum<<5) | bsum;
				if (destpix==TRANSPARENT_COLOR)
					destpix=REPLACEMENT_COLOR;
				if (asum>2)
					destpix=TRANSPARENT_COLOR;

				texptr->data[miplevel][i*width+t]=destpix;
			}
		}
	}

	texptr->mipmapped=1;
}






		





