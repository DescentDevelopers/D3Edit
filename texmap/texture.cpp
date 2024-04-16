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
#include "grdefs.h"
#include "texture.h"
#include "pstypes.h"
#include "fix.h"
#include "mono.h"
#include "3d.h"
#include "pserror.h"
#include "bitmap.h"
#include "ddio.h"
#include "renderer.h"
#include "macros.h"
#include "mem.h"

#define RECIP_TABLE_SIZE 640
#define ZBUFFER_MAX_DIMENSION	1000

#define PIX_PER_SPAN 16

void (*Texture_render_function)(g3Point *,int)=NULL;

int Current_mip=0;

float MipChoices[]={64,128,180};

void (*Texture_functions[])(g3Point *,int)={tex_UnlitTexturedQuad,tex_LitTexturedQuad,tex_ColoredTexturedQuad,
									  tex_PerUnlitTexturedQuad,tex_PerLitTexturedQuad,
									  tex_UnlitTransQuad,tex_LitTransQuad,
									  tex_PerUnlitTransQuad,tex_PerLitTransQuad,
									  tex_PerColoredTexturedQuad,tex_LinFlatShade,tex_PerFlatShade,
									  tex_LitTexturedTriangle,tex_FlatPolyTriangle,tex_AlphaTexturedQuad};

static int Tex_width,Tex_height,Tex_pitch,Tex_x1,Tex_x2,Tex_y1,Tex_y2;
static float Tex_aspect_ratio;
static ubyte *Tex_framebuffer;

static float *ZBuffer;
static int ZBuffer_width,ZBuffer_height,ZBuffer_init=0;
static light_state tex_LightingState=LS_NONE;
static color_model tex_ColorModel=CM_MONO;
static texture_type tex_TextureType=TT_LINEAR;
static sbyte		  tex_alpha_type=AT_ALWAYS;

static ubyte Fog_state=0;
static float Fog_near_z=0,Fog_far_z=0;

static fix LeftU,LeftV,Left_DU,Left_DV;
static fix RightU,RightV,Right_DU,Right_DV;
static float FLeftU,FLeftV,FLeft_DU,FLeft_DV,FLeftZ,FLeft_DZ;
static float FRightU,FRightV,FRight_DU,FRight_DV,FRightZ,FRight_DZ;
static fix Delta_right_x,Right_x,Delta_left_x,Left_x;

static int BigSteps,MidSteps,Leftovers;

static ubyte *TexSrc;
static ushort *TexSrc16;
static int Ander;		// for AND in our inner loops
static int Tex_bitmap;
static ushort Flat_polygon_color=0;
static int DeltaLight;

static ushort *Current_tex_palette;
static int Lighting8;
static int Mips_on=1;

ubyte TexShadeTable8[MAX_TEXTURE_SHADES][256];
ulong TexShadeTable16[MAX_TEXTURE_SHADES][256];
ubyte TexRevShadeTable8[MAX_TEXTURE_SHADES][256];
ulong TexRevShadeTable16[MAX_TEXTURE_SHADES][256];
ushort Translate4444To1555[65536];

fix Fix_recip_table[RECIP_TABLE_SIZE];
float Float_recip_table[RECIP_TABLE_SIZE];

void tex_PerLitGeneral16 (g3Point *p,int nv);
void tex_LinLitGeneral16 (g3Point *p,int nv);
void tex_PerUnlitGeneral16 (g3Point *p,int nv);
void tex_LinUnlitGeneral16 (g3Point *p,int nv);

void tex_PerLitTransGeneral16(g3Point *p,int nv);
void tex_LinLitTransGeneral16(g3Point *p,int nv);

void tex_PerUnlitTransGeneral16(g3Point *p,int nv);
void tex_LinUnlitTransGeneral16(g3Point *p,int nv);
void tex_SetZBufferState (int state);
void tex_ZBuf16(g3Point *p,int nv);
void tex_Draw4444(g3Point *p,int nv);

int tex_ClipLine(int &l, int &t, int &r, int &b);
int tex_ClipRect(int &l, int &t, int &r, int &b);
void tex_DrawLine16(int x1, int y1, int x2, int y2);
void tex_DrawHLine16(int x1, int x2, int y);
void tex_DrawVLine16(int y1, int y2, int x);
void tex_FillCircle16(ushort col, int xc, int yc, int r);
void tex_DrawCircle16(int xc, int yc, int r);


// Tells the software renderer whether or not to use mipping
void tex_SetMipState (int mipstate)
{
	Mips_on=mipstate;
}

void tex_BuildRecipTable ()
{
	Fix_recip_table[0]=F1_0;
	Float_recip_table[0]=1.0;

	for (int i=1;i<RECIP_TABLE_SIZE;i++)
	{
		Fix_recip_table[i]=F1_0/i;
		Float_recip_table[i]=1.0/(float)i;
	}

}



void tex_Build16BitShadeTable()
{
	int shade,t,i;
	ubyte r,g,b;
	ubyte rt,gt,bt;
	ushort wg;

	mprintf ((0,"Building 16bit fade table.\n"));

	for (i=0;i<65536;i++)
	{
		int a=(i>>12) & 0xf;
		int r=(i>>8) & 0xf;
		int g=(i>>4) & 0xf;
		int b=(i>>0) & 0xf;

		r<<=1;
		g<<=1;
		b<<=1;
		
		Translate4444To1555[i]=OPAQUE_FLAG|(r<<10)|(g<<5)|b;
	}
		
	for (i=0;i<MAX_TEXTURE_SHADES;i++)
		for (t=0;t<256;t++)
		{
			TexShadeTable8[i][t]=0;
			TexShadeTable16[i][t]=0;
			TexRevShadeTable8[i][t]=0;
			TexRevShadeTable16[i][t]=0;
		}

	for (shade=0;shade<MAX_TEXTURE_SHADES;shade++)
	{

		for (bt=0;bt<32;bt++)
		{
			b=(bt*shade)/(MAX_TEXTURE_SHADES-1);
			for (i=0;i<8;i++)
			{
				TexShadeTable8[shade][i*32+bt]=b;
				TexRevShadeTable8[(MAX_TEXTURE_SHADES-1)-shade][i*32+bt]=b;
			}
		}
		for (rt=0;rt<32;rt++)
		{
			r=(rt*shade)/(MAX_TEXTURE_SHADES-1);
			for (i=0;i<8;i++)
			{
				TexShadeTable16[shade][rt*8+i]=r<<11;
				TexRevShadeTable16[(MAX_TEXTURE_SHADES-1)-shade][rt*8+i]=r<<11;
			}
		}

		for (gt=0;gt<8;gt++)
		{
			g=(gt*shade)/(MAX_TEXTURE_SHADES-1);
			g&=0xFE;		// Take that low bit out!
			for (i=0;i<32;i++)
			{
				TexShadeTable8[shade][gt*32+i]|=(g<<5);
				TexRevShadeTable8[(MAX_TEXTURE_SHADES-1)-shade][gt*32+i]|=(g<<5);

			}

			g=((gt*8)*shade)/(MAX_TEXTURE_SHADES-1);
			wg=g;
			for (i=0;i<32;i++)
			{
				TexShadeTable16[shade][i*8+gt]|=(wg<<5);
				TexRevShadeTable16[(MAX_TEXTURE_SHADES-1)-shade][i*8+gt]|=(wg<<5);
			}
		}
	}
}


int tex_Init()
{
	// Initializes the lookup tables texture mapping
	tex_BuildRecipTable();
	tex_Build16BitShadeTable();

	return 1;
}

// Gets the correct AND value so our textures wrap
int tex_GetAnder (int bm,int mip)
{
	int av;
	int temp_w=bm_w(bm,mip);		// w and h are the same for mips

	if (Renderer_type==RENDERER_SOFTWARE_8BIT)
	{
		av=(temp_w-1)*256;
		av+=(temp_w-1);
	}
	else
	{
		av=(temp_w-1)*256;
		av+=((temp_w-1)<<1);
	}

	return av;
}

// Given nv points, draws that polygon according to the rendertype currently set
// Handle is a bitmap handle
void tex_DrawPointList (int handle,g3Point **p,int nv)
{
	g3Point t[100];
	int i;
	ubyte do_second_pass=0;
	ubyte second_pass=0;
	
	ASSERT (nv<100);

	if (Overlay_type==OT_REPLACE)
		do_second_pass=1;

	Tex_bitmap=handle;
		
	for (i=0;i<nv;i++)
	{
		t[i]=*p[i];

		if (tex_ColorModel==CM_RGB)
			t[i].p3_l=1.0;

		if (Fog_state)
		{
			if (t[i].p3_z>Fog_far_z)
				t[i].p3_l=0;
			else if (t[i].p3_z>Fog_near_z && t[i].p3_z<=Fog_far_z)
			{
				float fogdiff=Fog_far_z-Fog_near_z;
				float light_adjust=1-((t[i].p3_z-Fog_near_z)/fogdiff);

				t[i].p3_l*=light_adjust;
			}

		}
	}

	if (tex_TextureType!=TT_FLAT && bm_format(Tex_bitmap)==BITMAP_FORMAT_4444)\
	{
		tex_Draw4444(t,nv);
		return;
	}

		
	// Now go thru and figure out what function to call:
	
	StartDrawing:

	if (ZBuffer_init)
	{
		tex_ZBuf16(t,nv);
		goto SkipToEnd;
	}
	
	switch (tex_LightingState)
	{
		case LS_GOURAUD:
		{
			switch (tex_TextureType)
			{
				case TT_FLAT:
					tex_DrawFlatPolygon (p,nv);
					break;
				case TT_LINEAR:
					if (tex_alpha_type & ATF_TEXTURE)
					{
						if (second_pass)
							tex_UnlitTransQuad (t,nv);
						else
							tex_UnlitTransQuad (t,nv);
					}
					else
					{
						if (second_pass)
							tex_UnlitTransQuad (t,nv);
						else
							tex_UnlitTexturedQuad (t,nv);
					}
					
					break;
				case TT_PERSPECTIVE:
					if (tex_alpha_type & ATF_TEXTURE)
					{
						if (second_pass)
							tex_PerUnlitTransQuad (t,nv);
						else
							tex_PerUnlitTransQuad (t,nv);
					}
					else
					{
						if (second_pass)
							tex_PerUnlitTransQuad (t,nv);
						else
							tex_PerUnlitTexturedQuad (t,nv);
					}
					break;
				case TT_PERSPECTIVE_SPECIAL:
					tex_PerFlatShade (t,nv);
					break;
				case TT_LINEAR_SPECIAL:
					tex_LinFlatShade (t,nv);
					break;
				default:
					Int3();
					break;
			}
		}
		break;	// case LS_GOURAUD

		case LS_NONE:
		{
			switch (tex_TextureType)
			{
				case TT_FLAT:
					tex_DrawFlatPolygon (p,nv);
					break;
				case TT_LINEAR:
					if (tex_alpha_type & ATF_TEXTURE)
					{
						if (second_pass)
							tex_UnlitTransQuad (t,nv);
						else
							tex_UnlitTransQuad (t,nv);
					}
					else
					{
						if (second_pass)
							tex_UnlitTransQuad (t,nv);
						else
							tex_UnlitTexturedQuad (t,nv);
					}
					break;
				case TT_PERSPECTIVE:
					if (tex_alpha_type & ATF_TEXTURE)
					{
						if (second_pass)
							tex_PerUnlitTransQuad (t,nv);
						else
							tex_PerUnlitTransQuad (t,nv);
					}
					else
					{
						if (second_pass)
							tex_PerUnlitTransQuad (t,nv);
						else
							tex_PerUnlitTexturedQuad (t,nv);
					}
					break;
				case TT_PERSPECTIVE_SPECIAL:
					tex_PerFlatShade (t,nv);
					break;
				case TT_LINEAR_SPECIAL:
					tex_LinFlatShade (t,nv);
					break;
				default:
					Int3();
					break;
			}
		}
		break;	// case LS_NONE

		default:
			break;
	}

	SkipToEnd:

	// Do overlay map if present
	if (do_second_pass)
	{
		for (i=0;i<nv;i++)
		{
			t[i].p3_u=t[i].p3_u2;
			t[i].p3_v=t[i].p3_v2;
		
		}
		Tex_bitmap=Overlay_map;

		second_pass=1;
		do_second_pass=0;
		goto StartDrawing;
	}
}

// Draws a solid color polygon.  "color" is a color in 5-6-5 format.
void tex_DrawFlatPolygon (g3Point **pv,int nv)
{
	g3Point p[100];
	int k;

	ASSERT (nv<100);

	Tex_bitmap=0;
		
	for (k=0;k<nv;k++)
		p[k]=*pv[k];

	#include "flat_poly.h"
	#define TEX_INNER_LOOP "flat_poly.h"
	#include "drawquad.h"
}

void tex_SetFlatColor (ddgr_color color)
{
	Flat_polygon_color=GR_COLOR_TO_16(color);
}


int tex_RightSection(texs_texpoint *v1,texs_texpoint *v2)
{
    int height = v2->screeny - v1->screeny;
	if(height == 0)
        return 0;

    Delta_right_x = IntToFix(v2->screenx - v1->screenx) / height;
    Right_x = IntToFix(v1->screenx);

    return height;                  // return the height of this section
}

int tex_LeftSection(texs_texpoint *v1,texs_texpoint *v2)
{
    int height = v2->screeny - v1->screeny;
    if(height == 0)
        return 0;
	
    // Calculate the deltas along this section

    Delta_left_x = IntToFix(v2->screenx - v1->screenx) / height;
    Left_x = IntToFix(v1->screenx);
	
	return height;
}

void tex_LinFlatShade (g3Point *p,int nv)
{

	if (Renderer_type==RENDERER_SOFTWARE_16BIT)
	{
		tex_LinFlatShade16 (p,nv);
		return;

	}
	else
		Int3();	// No 8bit support anymore
}
void tex_PerFlatShade (g3Point *p,int nv)
{
	if (Renderer_type==RENDERER_SOFTWARE_16BIT)
	{
		tex_PerFlatShade16 (p,nv);
		return;
	}
	else
		Int3();	// No 8bit support anymore

}

void tex_AlphaTexturedQuad (g3Point *p,int nv)
{
	#include "tmap_alpha16.h"
	#define TEX_INNER_LOOP "tmap_alpha16.h"
	
	#include "drawquad.h"
}

void tex_UnlitTexturedQuad (g3Point *p,int nv)
{
	if (Renderer_type==RENDERER_SOFTWARE_16BIT)
	{
		tex_UnlitTexturedQuad16 (p,nv);
		return;
	}
	else
		Int3();	// No 8bit support anymore
	
}

void tex_LitTexturedQuad (g3Point *p,int nv)
{
	if (Renderer_type==RENDERER_SOFTWARE_16BIT)
	{
		tex_LitTexturedQuad16 (p,nv);
		return;
	}
	else
		Int3();	// No 8bit support anymore
	
}
void tex_ColoredTexturedQuad (g3Point *p,int nv)
{
	Int3();

}

void tex_PerUnlitTexturedQuad (g3Point *p,int nv)
{
	if (Renderer_type==RENDERER_SOFTWARE_16BIT)
	{
		tex_PerUnlitTexturedQuad16 (p,nv);
		return;
	}
	else
		Int3();	// No 8bit support anymore

	
}

void tex_PerLitTexturedQuad (g3Point *p,int nv)
{
	if (Renderer_type==RENDERER_SOFTWARE_16BIT)
	{
		tex_PerLitTexturedQuad16 (p,nv);
		return;
	}
	else
		Int3();	// No 8bit support anymore

	
}


void tex_UnlitTransQuad (g3Point *p,int nv)
{
	if (Renderer_type==RENDERER_SOFTWARE_16BIT)
	{
		tex_LinUnlitTransGeneral16(p,nv);
		return;
	}
	else
		Int3();	// No 8bit support anymore


}

void tex_LitTransQuad (g3Point *p,int nv)
{
	if (Renderer_type==RENDERER_SOFTWARE_16BIT)
	{
		tex_LinLitTransGeneral16(p,nv);
		return;
	}
	else
		Int3();	// No 8bit support anymore
}

void tex_PerColoredTexturedQuad (g3Point *p,int nv)
{
	Int3();	
}

void tex_PerUnlitTransQuad (g3Point *p,int nv)
{
	if (Renderer_type==RENDERER_SOFTWARE_16BIT)
	{
		tex_PerUnlitTransGeneral16(p,nv);
		return;
	}
	else
		Int3();	// No 8bit support anymore

	
}

void tex_PerLitTransQuad (g3Point *p,int nv)
{
	if (Renderer_type==RENDERER_SOFTWARE_16BIT)
	{
		tex_PerLitTransGeneral16(p,nv);
		return;
	}
	else
		Int3();	// No 8bit support anymore
}

void tex_UnlitTexturedQuad16 (g3Point *p,int nv)
{
	if (bm_w(Tex_bitmap,0)!=128)
	{
		tex_LinUnlitGeneral16(p,nv);
		return;
	}

	#ifdef MACINTOSH
		#include "tmap_ll16.h"
		#define TEX_INNER_LOOP "tmap_ll16.h"
	#else
		#include "tmap_ll16a.h"
		#define TEX_INNER_LOOP "tmap_ll16a.h"
	#endif
		

	#include "drawquad.h"
}

void tex_LitTexturedQuad16 (g3Point *p,int nv)
{
	if (bm_w(Tex_bitmap,0)!=128)
	{
		tex_LinLitGeneral16(p,nv);
		return;
	}

	#ifdef MACINTOSH
		#include "tmap_ll16.h"
		#define TEX_INNER_LOOP "tmap_ll16.h"
	#else
		#include "tmap_ll16a.h"
		#define TEX_INNER_LOOP "tmap_ll16a.h"
	#endif
	
	
	#define MONO_LIGHTING

	#include "drawquad.h"
}

void tex_PerUnlitTexturedQuad16 (g3Point *p,int nv)
{
	if (bm_w(Tex_bitmap,0)!=128)
	{
		tex_PerUnlitGeneral16(p,nv);
		return;
	}

	#ifdef MACINTOSH
		#include "tmap_pl16.h"
		#define TEX_INNER_LOOP "tmap_pl16.h"
	#else
		#include "tmap_pl16a.h"
		#define TEX_INNER_LOOP "tmap_pl16a.h"
	#endif
	
	
	#define PERSPECTIVE
	
	#include "drawquad.h"
}

void tex_PerLitTexturedQuad16 (g3Point *p,int nv)
{
	if (bm_w(Tex_bitmap,0)!=128)
	{
		tex_PerLitGeneral16(p,nv);
		return;
	}

	#ifdef MACINTOSH
		#include "tmap_pl16.h"
		#define TEX_INNER_LOOP "tmap_pl16.h"
	#else
		#include "tmap_pl16a.h"
		#define TEX_INNER_LOOP "tmap_pl16a.h"
	#endif
		 	
 	#define PERSPECTIVE
	#define MONO_LIGHTING

	

	#include "drawquad.h"
}

void tex_LitTexturedTriangle16 (g3Point *p,int nv)
{	

	#include "tmap_ll16.h"
	#define TEX_INNER_LOOP "tmap_ll16.h"
	//#define TEXTURING
	#define MONO_LIGHTING

	#include "drawquad.h"
}

void tex_LitTexturedTriangle (g3Point *p,int nv)
{
	if (Renderer_type==RENDERER_SOFTWARE_16BIT)
	{
		tex_LitTexturedTriangle16 (p,nv);
		return;
	}
	else
		Int3();	// No 8bit support anymore


}

void tex_FlatPolyTriangle (g3Point *p,int nv)
{
	#ifdef MACINTOSH
		#include "tmap_mac_tri_flata.h"
	#else
		#include "tmap_tri_flata.h"
	#endif
	
	#ifdef MACINTOSH
		#define TEX_INNER_LOOP "tmap_mac_tri_flata.h"
	#else
		#define TEX_INNER_LOOP "tmap_tri_flata.h"
	#endif
	
	#include "drawtex.h"
}




// Gets the left top, left bottom, right top, and right bottom indices.  Also finds
// lowest y index.  
void tex_GetVertexOrdering (texs_texpoint *t, int nv, int *vlt, int *vlb, int *vrt, int *vrb,int *bottom_y_ind)
{
	int	i;
	int	min_y,max_y;
	int	min_y_ind;
	int	original_vrt;
	fix	min_x;

	// Scan all vertices, set min_y_ind to vertex with smallest y coordinate.
	min_y = t[0].screeny;
	max_y = min_y;
	min_y_ind = 0;
	min_x = t[0].screenx;
	*bottom_y_ind = 0;

	for (i=1; i<nv; i++) 
	{
		if (t[i].screeny < min_y) 
		{
			min_y = t[i].screeny;
			min_y_ind = i;
			min_x = t[i].screenx;
		} 
		else if (t[i].screeny == min_y)
		{
			if (t[i].screenx < min_x) 
			{
				min_y_ind = i;
				min_x = t[i].screenx;
			}
		}
		if (t[i].screeny > max_y) 
		{
			max_y = t[i].screeny;
			*bottom_y_ind = i;
		}
	}


	// Set "vertex left top", etc. based on vertex with topmost y coordinate
	*vlt = min_y_ind;
	*vrt = *vlt;
	*vlb = tex_PrevIndex(*vlt,nv);
	*vrb = tex_NextIndex(*vrt,nv);

	// If right edge is horizontal, then advance along polygon bound until it no longer is or until all
	// vertices have been examined.
	// (Left edge cannot be horizontal, because *vlt is set to leftmost point with highest y coordinate.)

	original_vrt = *vrt;

	while (t[*vrt].screeny == t[*vrb].screeny) 
	{
		if (tex_NextIndex(*vrt,nv) == original_vrt) 
			break;
		
		*vrt = tex_NextIndex(*vrt,nv);
		*vrb = tex_NextIndex(*vrt,nv);
	}
}


//	Returns number preceding val modulo modulus.
//	prevmod(3,4) = 2
//	prevmod(0,4) = 3
int tex_PrevIndex(int val,int modulus)
{
	if (val > 0)
		return val-1;
	else
		return modulus-1;
}

//	Returns number succeeding val modulo modulus.
//	succmod(3,4) = 0
//	succmod(0,4) = 1
int tex_NextIndex(int val,int modulus)
{
	if (val < modulus-1)
		return val+1;
	else
		return 0;
}


// Sets the fog state to TRUE or FALSE
void tex_SetFogState (int on)
{
	Fog_state=on;

}

// Sets the near and far plane of fog
void tex_SetFogBorders (float fog_near,float fog_far)
{
	Fog_near_z=fog_near;
	Fog_far_z=fog_far;
}

void tex_LinFlatShade16 (g3Point *p,int nv)
{
	
	#include "tmap_flat16.h"
	#define TEX_INNER_LOOP "tmap_flat16.h"
	#include "drawquad.h"
}
void tex_PerFlatShade16 (g3Point *p,int nv)
{
	#include "tmap_perflat16.h"
	#define TEX_INNER_LOOP "tmap_perflat16.h"
	#define PERSPECTIVE
	#include "drawquad.h"
}

void tex_SetLighting (light_state state)
{
	tex_LightingState=state;
}
void tex_SetColorModel (color_model state)
{
	tex_ColorModel=state;
}
void tex_SetTextureType (texture_type state)
{
	tex_TextureType=state;
}

void tex_PerLitGeneral16 (g3Point *p,int nv)
{
	#include "tmap_pl16.h"
	#define TEX_INNER_LOOP "tmap_pl16.h"
	//#define TEXTURING
	#define MONO_LIGHTING
	#define PERSPECTIVE

	#include "drawquad.h"
}

void tex_LinLitGeneral16 (g3Point *p,int nv)
{
	#include "tmap_ll16.h"
	#define TEX_INNER_LOOP "tmap_ll16.h"
	//#define TEXTURING
	#define MONO_LIGHTING
	
	#include "drawquad.h"
}

void tex_PerUnlitGeneral16 (g3Point *p,int nv)
{
	#include "tmap_pl16.h"
	#define TEX_INNER_LOOP "tmap_pl16.h"
	//#define TEXTURING
	#define PERSPECTIVE

	#include "drawquad.h"
}

void tex_LinUnlitGeneral16 (g3Point *p,int nv)
{
	#include "tmap_ll16.h"
	#define TEX_INNER_LOOP "tmap_ll16.h"
	//#define TEXTURING

	#include "drawquad.h"
}

void tex_PerLitTransGeneral16(g3Point *p,int nv)
{
	#include "tmap_pl16.h"
	#define TEX_INNER_LOOP "tmap_pl16.h"
	//#define TEXTURING
	#define MONO_LIGHTING
	#define PERSPECTIVE
	
	#include "drawquad.h"
}
void tex_LinLitTransGeneral16(g3Point *p,int nv)
{
	#include "tmap_ll16.h"
	#define TEX_INNER_LOOP "tmap_ll16.h"
	//#define TEXTURING
	#define MONO_LIGHTING
	
	#include "drawquad.h"
}

void tex_PerUnlitTransGeneral16(g3Point *p,int nv)
{
	#include "tmap_pl16.h"
	#define TEX_INNER_LOOP "tmap_pl16.h"
	//#define TEXTURING
	#define PERSPECTIVE
	
	#include "drawquad.h"
}


void tex_LinUnlitTransGeneral16(g3Point *p,int nv)
{
	#include "tmap_ll16.h"
	#define TEX_INNER_LOOP "tmap_ll16.h"
	//#define TEXTURING
	
	#include "drawquad.h"
}

void tex_Draw4444(g3Point *p,int nv)
{
	#include "tmap_4444.h"
	#define TEX_INNER_LOOP "tmap_4444.h"
	//#define TEXTURING
	
	#include "drawquad.h"
}

void tex_ZBuf16(g3Point *p,int nv)
{
	#include "tmap_zbuf16.h"
	#define TEX_INNER_LOOP "tmap_zbuf16.h"
	//#define TEXTURING
	#define PERSPECTIVE
	
	#include "drawquad.h"
}

void tex_SetAlphaType (sbyte atype)
{
	tex_alpha_type=atype;
}


void tex_SetZBufferState (int state)
{
	if (state==1 && ZBuffer_init==0)
	{
		ZBuffer_width=ZBUFFER_MAX_DIMENSION;
		ZBuffer_height=ZBUFFER_MAX_DIMENSION;

		ZBuffer=(float *)mem_malloc (ZBuffer_width*ZBuffer_height*sizeof(float));
		ASSERT (ZBuffer);
		ZBuffer_init=1;
		return;
	}
	if (state==0 && ZBuffer_init==1)
	{
		mem_free (ZBuffer);
		ZBuffer_init=0;
	}
}
// Clears the zbuffer
void tex_ClearZBuffer ()
{
	for (int i=0;i<ZBuffer_width*ZBuffer_height;i++)
		ZBuffer[i]=99999.0f;
}

void tex_EndFrame()
{
	

}
void tex_StartFrame(int x1,int y1,int x2,int y2)
{
	if (ZBuffer_init)
		tex_ClearZBuffer();

	Tex_x1=x1;
	Tex_x2=x2;
	Tex_y1=y1;
	Tex_y2=y2;
}

// Sets where the software renderer should draw to
void tex_SetSoftwareParameters (float aspect_ratio,int width,int height,int pitch,ubyte *framebuffer)
{
	Tex_width=width;
	Tex_height=height;
	Tex_pitch=pitch;
	Tex_framebuffer=framebuffer;
	Tex_aspect_ratio=aspect_ratio;
}

void tex_GetLFBLock(renderer_lfb *lfb)
{
	lfb->type = LFB_LOCK_WRITE;
	lfb->data = (ushort *)Tex_framebuffer;
	lfb->bytes_per_row = Tex_pitch;
}


void tex_ReleaseLFBLock(renderer_lfb *lfb)
{
	lfb->data = NULL;
}

// Fills in projection variables
void tex_GetProjectionParameters (int *width,int *height)
{
	*width=Tex_x2-Tex_x1;
	*height=Tex_y2-Tex_y1;
}

// Returns the aspect ratio of the physical screen
float tex_GetAspectRatio ()
{
	float aspect_ratio = Tex_aspect_ratio;
	return aspect_ratio;
}


//	software primative renderers
//	fill rect supported.
void tex_FillRect(ddgr_color color, int x1, int y1, int x2, int y2)
{
	x1 = Tex_x1+x1;
	y1 = Tex_y1+y1;
	x2 = Tex_x1+x2;
	y2 = Tex_y1+y2;

	if (tex_ClipRect(x1,y1,x2,y2) == 2) return;

	switch (Renderer_type)
	{
	case RENDERER_SOFTWARE_16BIT:
		{
		unsigned short *sptr;
		unsigned short col = GR_COLOR_TO_16(color);
		int rowsize = Tex_pitch, y;
	
		sptr = (unsigned short *)Tex_framebuffer + (y1 * (rowsize>>1));


		for (y = y1; y < y2; y++, sptr+=(rowsize>>1))
			for (int x = x1; x < x2;x++)
				sptr[x] = col;
		break;
		}
	default:
		Int3();
	}
}


//	set pixel
void tex_SetPixel(ddgr_color color, int x, int y)
{
	x = Tex_x1+x;
	y = Tex_y1+y;

	if (x>=Tex_width || y>=Tex_height)
			return;

	switch (Renderer_type)
	{
	case RENDERER_SOFTWARE_16BIT:
		{
		ushort scol = GR_COLOR_TO_16(color);
		ushort *ptr = (ushort *)Tex_framebuffer + (y*(Tex_pitch>>1)) + x;
		*ptr = scol;
		break;
		}
	default:
		Int3();
	}
}


//	get pixel
ddgr_color tex_GetPixel(int x, int y)
{
	ddgr_color col;

	x = Tex_x1+x;
	y = Tex_y1+y;

	switch (Renderer_type)
	{
	case RENDERER_SOFTWARE_16BIT:
		{
		ushort *ptr = (ushort *)Tex_framebuffer + (y*(Tex_pitch>>1)) + x;
		ushort scol = *ptr;

		col=GR_16_TO_COLOR (scol);
				
		break;
		}
	default:
		Int3();						// NOT YET SUPPORTED!
	}

	return col;
}


//	fillcircle
void tex_FillCircle(ddgr_color col, int xc, int yc, int r)
{
	xc = Tex_x1+xc;
	yc = Tex_y1+yc;

	switch (Renderer_type)
	{
	case RENDERER_SOFTWARE_16BIT:
		tex_FillCircle16(GR_COLOR_TO_16(col), xc,yc,r);
		break;
	default:
		Int3();
	}

}


void tex_DrawCircle(int xc, int yc, int r)
{
	xc = Tex_x1+xc;
	yc = Tex_y1+yc;

	switch (Renderer_type)
	{
	case RENDERER_SOFTWARE_16BIT:
		tex_DrawCircle16(xc,yc,r);
		break;
	default:
		Int3();
	}
}


//	16bit versions of circle renderer

inline void tex_SetPixelClip16(ushort col, int x, int y)
{
	if (x >= Tex_x2 || x < Tex_x1 || y >= Tex_y2 || y < Tex_y1) return;
	ushort *ptr = (ushort *)Tex_framebuffer + (y*(Tex_pitch>>1)) + x;
	*ptr = col;
}

inline void tex_DrawHLineClip16(int x1, int x2, int y)
{
	if (x1 >= Tex_x2) return;
	if (x2 < Tex_x1) return;
	if (y >= Tex_y2 || y < Tex_y1) return;
	if (x1 < Tex_x1) x1 = Tex_x1;
	if (x2 >=Tex_x2) x2 = Tex_x2-1;

	tex_DrawHLine16(x1,x2,y);
}

void tex_FillCircle16(ushort col, int xc, int yc, int r)
{
   int p, x, y;
	ushort oldcol = Flat_polygon_color;

	Flat_polygon_color = col;

//	a short way of doing this.  I sort of remember this.
//	I knoew this is symmetric and quadrant based.
	p = 3 - (r*2);
	x = 0; 
	y = r;

	while(x < y)
	{
	// Draw the first octant
		tex_DrawHLineClip16( xc-y, xc+y, yc-x);
		tex_DrawHLineClip16( xc-y, xc+y, yc+x);

		if (p<0) p = p + (x*4)+6;
	    else  {
		// Draw the second octant
			tex_DrawHLineClip16( xc-x, xc+x, yc-y);
			tex_DrawHLineClip16( xc-x, xc+x, yc+y);
			p = p + ((x-y)*4)+10;
			y--;
		}	
		x++;
	}
	if(x==y) {
		tex_DrawHLineClip16( xc-x, xc+x, yc-y);
		tex_DrawHLineClip16( xc-x, xc+x, yc+y);
	}

	Flat_polygon_color = oldcol;
}


//	draw circle
void tex_DrawCircle16(int xc, int yc, int r)
{
	int x, y, p;

//	a short way of doing this.  I sort of remember this.
//	I know this is symmetric and quadrant based.
	p = 3 - (r*2);
	x = 0; 
	y = r;

	while(x < y)
	{
		// Draw the first octant
		tex_SetPixelClip16(Flat_polygon_color,xc-y,yc-x);
		tex_SetPixelClip16(Flat_polygon_color,xc+x,yc-x);
		tex_SetPixelClip16(Flat_polygon_color,xc-y,yc+x);
		tex_SetPixelClip16(Flat_polygon_color,xc+y,yc+x);

		if (p < 0) 
			p = p + (x*4) + 6;
		else {
		// Draw the second octant
			tex_SetPixelClip16(Flat_polygon_color,xc-x,yc-y);
			tex_SetPixelClip16(Flat_polygon_color,xc+x,yc-y);
			tex_SetPixelClip16(Flat_polygon_color,xc-x,yc+y);
			tex_SetPixelClip16(Flat_polygon_color,xc+x,yc+y);
			p = p+ ((x-y)*4)+10;
			y--;
		}
		x++;
	}
	if(x == y) {
		tex_SetPixelClip16(Flat_polygon_color,xc-x,yc-y);
		tex_SetPixelClip16(Flat_polygon_color,xc+x,yc-y);
		tex_SetPixelClip16(Flat_polygon_color,xc-x,yc+y);
		tex_SetPixelClip16(Flat_polygon_color,xc+x,yc+y);
	}
}


//	software line renderer.
//	the functions 
//		tex_DrawLine		16bit
//		tex_DrawHLine		16bit
//		tex_DrawVLine		16bit
				
void tex_DrawLine(int x1, int y1, int x2, int y2)
{
	x1 = Tex_x1+x1;
	y1 = Tex_y1+y1;
	x2 = Tex_x1+x2;
	y2 = Tex_y1+y2;

	if (tex_ClipLine(x1,y1,x2,y2) == 2) return;
	if (Renderer_type==RENDERER_SOFTWARE_16BIT) {
		tex_DrawLine16 (x1,y1,x2,y2);
	}
	else
		Int3();
}


//	16-bit versions of line renderer.
void tex_DrawLine16(int x1, int y1, int x2, int y2)
{
	int DY, DX;
	int i,x,y,yinc=1,xinc=1,error_term,offset;
	ubyte *surface_ptr = Tex_framebuffer;
	unsigned short color = Flat_polygon_color;

// Check to see if our x coords are reversed
	if (x1>x2)	{	
		SWAP (x1, x2);
		SWAP (y1, y2);
	}

// Check to see if our y coords are reversed
//	if (y1>y2)	{	
//		SWAP(x1, x2);
//		SWAP(y1, y2);
//	}

	DX=x2-x1; DY=y2-y1;
  
	if (DY==0) {
		tex_DrawHLine16(x1, x2, y1);
		return;
	}
	if (DX==0) {
		tex_DrawVLine16(y1, y2, x1);
		return;
	}

    if (DX<0) {	xinc=-1; DX=-DX; }
	if (DY<0) {	yinc=-1; DY=-DY; }

	if (DX>=DY)   // X is greater than y
	{
		error_term=0;
		x=x1; y=y1;

		offset =  yinc * Tex_pitch;
		surface_ptr += y*Tex_pitch;

		for (i=0;i<DX;i++)
		{
			*((unsigned short *)(surface_ptr+(x<<1))) = color;

			x+=xinc;
			error_term+=DY;
			if (error_term>=DX)
			 {
				y+=yinc;
				error_term-=DX;
				surface_ptr += offset;
			 }
	    }
	}
	else
	{	
		error_term=0;
		x=x1; y=y1;

		offset = yinc * Tex_pitch;
		surface_ptr += y*Tex_pitch;
		
		for (i=0;i<DY;i++)
		{
			*((unsigned short *)(surface_ptr+(x<<1))) = color;

			y+=yinc;
			error_term+=DX;
			surface_ptr+= offset;

			if (error_term>=DY)
			{
				x+=xinc;
				error_term-=DY;
			}
	    }
    } 


}


void tex_DrawHLine16(int x1, int x2, int y)
{
	unsigned short *sptr;

	if (x2 < x1) SWAP(x1,x2);

	sptr = (unsigned short *)(Tex_framebuffer + (Tex_pitch*y));

	for (int i = x1; i <=x2; i++)
		sptr[i] = (unsigned short)(Flat_polygon_color);
}


void tex_DrawVLine16(int y1, int y2, int x)
{
	ubyte *ptr;
	unsigned short color = Flat_polygon_color;
	int rowsize = Tex_pitch;

	if (y2 < y1) SWAP(y1,y2);

	ptr = Tex_framebuffer + (rowsize * y1) + (x<<1);

	for (int i = y1; i <=y2; i++)
	{
		*((unsigned short *)(ptr)) = color;
		ptr += rowsize;
	}
}


//	clip rect.
//		returns 2 if totally clipped
//		returns 1 if partially clipped
//		returns 0 if not clipped.

int tex_ClipRect(int &l, int &t, int &r, int &b)
{
	int clipped = 0;

	if (l > r) SWAP(l,r);
	if (t > b) SWAP(t,b);

	if (l >= Tex_x2 || t >=Tex_y2 || r < Tex_x1 || b < Tex_y1) return 2;
	
	if (l < Tex_x1) { l = Tex_x1; clipped = 1; }
	if (t < Tex_y1) { t = Tex_y1; clipped = 1; }
	if (r > Tex_x2) { r = Tex_x2-1; clipped = 1; }
	if (b > Tex_y2) { b = Tex_y2-1; clipped = 1; }

	return clipped;
}


//	grPen::clip_line
//		returns 2 if totally clipped
//		returns 1 if partially clipped
//		returns 0 if not clipped.

# define FSCALE(var,arg,num,den) ((var) = (arg)*(num)/(den))

int tex_ClipLine(int &l, int &t, int &r, int &b)
{
	int clipped=0;
	float clx1, cly1, clx2, cly2;
	float x1, y1, x2, y2;
    float temp;           
	
	x1 = (float)(l);
	y1 = (float)(t);
	x2 = (float)(r);
	y2 = (float)(b);

	clx1 = (float)(Tex_x1);
	cly1 = (float)(Tex_y1);
	clx2 = (float)(Tex_x2-1);
	cly2 = (float)(Tex_y2-1);
	                                       
//	take care of obvious clip case in y bounds;                                                        
    if (y1>y2) { SWAP(y1,y2); SWAP(x1,x2); }                                
    if((y2 < cly1) || (y1 > cly2)) return 2;

//	do x-axis first then check y-axis for clip
//	clip along viewport rect.  if x1 out of bounds, return total clipped,
//	else report partial clipping.
    if(x1 < x2) {                                                       
        if((x2 < clx1) || (x1 > clx2)) return 2;
        if(x1 < clx1) { 
			FSCALE(temp,(y2 - y1),(clx1 - x1),(x2 - x1));    
            if((y1 += temp) > cly2) { return 2; }          
            x1 = clx1; 
			clipped = 1;			
        }                                                            
        if(x2 > clx2) {                                        
			FSCALE(temp,(y2 - y1),(x2 - clx2),(x2 - x1));    
            if((y2 -= temp) < cly1) { return 2; }          
            x2 = clx2;                                         
			clipped = 1;
        } 
		
        if(y1 < cly1) {                                        
			if (y2==y1) return 2;        
			FSCALE(temp,(x2 - x1),(cly1 - y1),(y2 - y1));    
            x1 += temp;                                              
            y1 = cly1;                                         
			clipped = 1;
        }                                                            
        if(y2 > cly2) {                                        
			if (y2==y1) return 2;        
			FSCALE(temp,(x2 - x1),(y2 - cly2),(y2 - y1));    
            x2 -= temp;                                              
            y2 = cly2;                                         
			clipped =1;
        }                                                            
    }                                                                
    else {                                                           
        if((x1 < clx1) || (x2 > clx2)) return 2;

        if(x1 > clx2) {                                        
			if (x1 == x2) return 2;
			FSCALE(temp,(y2 - y1),(x1 - clx2),(x1 - x2));    
            if((y1 += temp) > cly2) { return 2; }          
            x1 = clx2;                                         
			clipped = 1;
        }                                                            
        if(x2 < clx1) {                                        
			if (x1 == x2) return 2;
			FSCALE(temp,(y2 - y1),(clx1 - x2),(x1 - x2));    
            if((y2 -= temp) < cly1) { return 2; }          
            x2 = clx1;                                         
            clipped = 1;                                            
        }                                                            
        if(y1 < cly1) {                                        
			if (y2 == y1) return 2;
			FSCALE(temp,(x1 - x2),(cly1 - y1),(y2 - y1));    
            x1 -= temp;                                              
            y1 = cly1;                                         
            clipped = 1;                                            
        }                                                            
        if(y2 > cly2) {                                        
			if (y2 == y1) return 2;
			FSCALE(temp,(x1 - x2),(y2 - cly2),(y2 - y1));    
            x2 += temp;                                              
            y2 = cly2;                                         
            clipped = 1;                                            
        }                                                            
    }                                                                

	l = (int)(x1);
	t = (int)(y1);
	r = (int)(x2);
	b = (int)(y2);
 
 	return clipped;
}

void tex_GetRenderState (rendering_state *rs)
{
	rs->screen_width=640;
	rs->screen_height=480;
}

			

