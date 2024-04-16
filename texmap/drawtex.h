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
 // #define PERSPECTIVE		1=PERSPECTIVE 0=LINEAR
// #define MONO_LIGHTING	1=MONO LIGHTING 0=FULLY BRIGHT
// #define COLORED_LIGHTING 1=COLORED LIGHTS 0=FULLY BRIGHT

#ifdef COLORED_LIGHTING
	fix LeftRedLight,LeftDeltaRedLight,LeftGreenLight,LeftDeltaGreenLight,LeftBlueLight,LeftDeltaBlueLight;
#endif
#ifdef MONO_LIGHTING
	fix LeftMonoLight,LeftDeltaMonoLight;
#endif

	int i;
	int rowsize=Tex_pitch/2;
	int surfwidth=Tex_width;
	int surfheight=Tex_height;

	texs_texpoint cp[3];
	
	texs_texpoint *v1 = &cp[0];
    texs_texpoint *v2 = &cp[1];
    texs_texpoint *v3 = &cp[2];
	
	texs_texpoint *l1,*l2;

	int height,left_height,right_height,points_on_right,points_on_left,desty;
	float closest_z=90000000;
	fix fx_recip_dyl;
	fix fxlongest,fxtemp;
	float fltemp,fllongest,flheight;
	ushort *destptr,*dest;
	#ifdef TEXTURING
		fix dudx,dvdx;
	#endif
	
	#ifdef COLORED_LIGHTING
		fix dlred_dx,dlgreen_dx,dlblue_dx;
	#endif
	#ifdef MONO_LIGHTING
		fix dldx;
		int new_triangle=1;	
	#endif
	#ifdef PERSPECTIVE
		float fldzdx,fldudx,fldvdx;
		int extra_precision=0;
	#endif

	// change points into texpoints

	for (i=0;i<3;i++)
	{
		//g3Point tp=p[i];
		
		ASSERT (p[i].p3_flags & PF_PROJECTED);

		if (p[i].p3_vec.z<closest_z)
			closest_z=p[i].p3_vec.z;

		cp[i].screenx=p[i].p3_sx;
		cp[i].screeny=p[i].p3_sy;

		cp[i].flscreenx=p[i].p3_sx;
		cp[i].flscreeny=p[i].p3_sy;


		#ifdef TEXTURING
			#ifndef PERSPECTIVE
				cp[i].ucoord=FloatToFix(p[i].p3_u);
				cp[i].vcoord=FloatToFix(p[i].p3_v);
			#else
				cp[i].flucoord=(p[i].p3_u);
				cp[i].flvcoord=(p[i].p3_v);
			#endif
		#endif
		
			
		#ifdef PERSPECTIVE
			cp[i].flzcoord=p[i].p3_vec.z;
			if (cp[i].flzcoord<0.000015)
				cp[i].flzcoord=0.000015;
			//if (cp[i].flzcoord<1)
				//extra_precision=1;
		#endif

		#ifdef MONO_LIGHTING
			ASSERT (p[i].p3_l>=0 && p[i].p3_l<=1);
			cp[i].monolight=FloatToFix(p[i].p3_l*(MAX_TEXTURE_SHADES-1));
			ASSERT (cp[i].monolight<=IntToFix(31));
		#endif
			
		#ifdef COLORED_LIGHTING
			cp[i].redlight=FloatToFix((1-p[i].p3_r)*(MAX_TEXTURE_SHADES-1));
			cp[i].greenlight=FloatToFix((1-p[i].p3_g)*(MAX_TEXTURE_SHADES-1));
			cp[i].bluelight=FloatToFix((1-p[i].p3_b)*(MAX_TEXTURE_SHADES-1));
		#endif		
		
	}


	#ifdef TEXTURING
		Current_mip=0;		// force no mipping for terrain triangles
		ASSERT (Current_mip<NUM_MIP_LEVELS);

		// Get our AND value for this triangle
		Ander=tex_GetAnder (Tex_bitmap,Current_mip);
		
		for (i=0;i<3;i++)
		{
			#ifndef PERSPECTIVE
				cp[i].ucoord=cp[i].ucoord*(bm_w(Tex_bitmap,Current_mip)-1);
				cp[i].vcoord=cp[i].vcoord*(bm_h(Tex_bitmap,Current_mip)-1);
			#else
				cp[i].flucoord=cp[i].flucoord*(bm_w(Tex_bitmap,Current_mip)-1);
				cp[i].flvcoord=cp[i].flvcoord*(bm_h(Tex_bitmap,Current_mip)-1);
			#endif
		}
	#endif

	// Sort the triangle so that v1 points to the topmost, v2 to the
    // middle and v3 to the bottom vertex.
     
    if(v1->screeny > v2->screeny) { texs_texpoint *v = v1; v1 = v2; v2 = v; }
    if(v1->screeny > v3->screeny) { texs_texpoint *v = v1; v1 = v3; v3 = v; }
    if(v2->screeny > v3->screeny) { texs_texpoint *v = v2; v2 = v3; v3 = v; }
	

	height = v3->screeny - v1->screeny;
	flheight= v3->flscreeny - v1->flscreeny;
    if(height == 0)
        return;

	#ifdef PERSPECTIVE
		
		// If this is a perspective map, change our coords to be u/z v/z and 1/z

		v1->flzcoord=1.0/v1->flzcoord;  v1->flucoord*=v1->flzcoord;	v1->flvcoord*=v1->flzcoord;
		v2->flzcoord=1.0/v2->flzcoord;  v2->flucoord*=v2->flzcoord;	v2->flvcoord*=v2->flzcoord;
		v3->flzcoord=1.0/v3->flzcoord;  v3->flucoord*=v3->flzcoord;	v3->flvcoord*=v3->flzcoord;
		

	#endif

	// We start out by calculating the length of the longest scanline.
	// This value is then used for our linear interpolants
	
	// fltemp equals the percentage of the top to middle vertices height versus
	// the total height
	fltemp = (v2->flscreeny - v1->flscreeny) / flheight;	
	fllongest = (fltemp * (v3->flscreenx - v1->flscreenx)) + (v1->flscreenx - v2->flscreenx);
	

	fxtemp = IntToFix(v2->screeny - v1->screeny) / height;		
	fxlongest = (fxtemp * (v3->screenx - v1->screenx)) + IntToFix(v1->screenx - v2->screenx);
	

		
    if(fxlongest == 0)
        return;
	
    // Now that we have the length of the longest scanline we can use that 
    // to tell us which is left and which is the right side of the triangle.

    if(fxlongest < 0)
    {
		// If longest is neg. we have the middle vertex on the right side.
        // Store the pointers for the right and left edge of the triangle.

		fxlongest-=0x30000;	// stupid fix to make sure delta's don't go <0 or >texture width
		
		points_on_left=1;
		points_on_right=2;

        // Calculate initial left and right parameters
        l1=v1;
		l2=v3;
		#include "leftedge.h"
		if (left_height<=0)
			return;
		
		l1=v1;
		l2=v2;
		#include "rightedg.h"
		if (right_height<=0)
		{			
             points_on_right--;
					        
			l1=v2;
			l2=v3;
			#include "rightedg.h"
			if (right_height<=0)
                return;
		
        }

		if(fxlongest > -0x1000)
			fxlongest = -0x1000;     
    }
    else
    {

		fxlongest+=0x30000;	// stupid fix to make sure delta's don't go <0 or >texture width

	    // If longest is pos. we have the middle vertex on the left side.
        // Store the pointers for the left and right edge of the triangle.

		points_on_left=2;
		points_on_right=1;

        // Calculate initial right and left parameters

		l1=v1;
		l2=v3;
		#include "rightedg.h"
        if (right_height<= 0)
            return;
		

		l1=v1;
		l2=v2;
		#include "leftedge.h"
		if (left_height<=0)
        {
            // The first left section had zero height. Use the next section.
            points_on_left--;
			l1=v2;
			l2=v3;
			#include "leftedge.h"
			if (left_height<=0)
				return;
        }

		if(fxlongest < 0x1000)
			fxlongest = 0x1000;     
    }

	#ifdef TEXTURING

		// Now, calculate our uv's and lighting delta values
		#ifndef PERSPECTIVE
			dudx = FixDiv (FixMul(fxtemp,(v3->ucoord - v1->ucoord)) + (v1->ucoord - v2->ucoord)  ,fxlongest);
			dvdx = FixDiv (FixMul(fxtemp,(v3->vcoord - v1->vcoord)) + (v1->vcoord - v2->vcoord) , fxlongest);
		#else
			if (extra_precision==0)
			{
				fldudx = ((fltemp * (v3->flucoord - v1->flucoord)) + (v1->flucoord - v2->flucoord))/fllongest;
				fldvdx = ((fltemp * (v3->flvcoord - v1->flvcoord)) + (v1->flvcoord - v2->flvcoord))/fllongest;
				fldzdx = ((fltemp * (v3->flzcoord - v1->flzcoord)) + (v1->flzcoord - v2->flzcoord))/fllongest;
			}
		#endif

	
	#endif
	

	#ifdef MONO_LIGHTING
		dldx = FixDiv (FixMul(fxtemp,(v3->monolight - v1->monolight)) + (v1->monolight - v2->monolight) , fxlongest);
		Lighting8=dldx>>8;
				
		if (Lighting8<0)
			Lighting8++;	// round towards 0 for negative deltas
	#endif

	#ifdef COLORED_LIGHTING
		dlred_dx =  FixDiv (FixMul(fxtemp,(v3->redlight - v1->redlight)) + (v1->redlight - v2->redlight) , fxlongest);
		dlgreen_dx =  FixDiv (FixMul(fxtemp,(v3->greenlight - v1->greenlight)) + (v1->greenlight - v2->greenlight) , fxlongest);
		dlblue_dx =  FixDiv (FixMul(fxtemp,(v3->bluelight - v1->bluelight)) + (v1->bluelight - v2->bluelight) , fxlongest);
	#endif
	

	// Set the destptr to equal the first row to draw to
	destptr=(ushort*)Tex_framebuffer+(v1->screeny*rowsize);
	desty=v1->screeny;

	while (1)
    {
        int x1 = FixToInt(Left_x);
        int width = FixToInt(Right_x) - x1;

		if (desty<0 || desty>=surfheight)
			goto UpdateExtents;

		if (x1<0 || x1>=surfwidth)
			goto UpdateExtents;
		if ((x1+width)>=surfwidth)
		{
			width=(surfwidth-x1);
			//width--;
		}
			
        if(width > 0)
        {
			#ifdef PERSPECTIVE
				if (extra_precision)
				{
					fldudx=(FRightU-FLeftU)/width;
					fldvdx=(FRightV-FLeftV)/width;
					fldzdx=(FRightZ-FLeftZ)/width;
				}	
			#endif

			#define ACTIVATE_INNER_LOOP

			#include TEX_INNER_LOOP
			
			#undef ACTIVATE_INNER_LOOP

        }

		UpdateExtents:		

        // Interpolate along the left edge of the triangle
        if(--left_height <= 0)  // At the bottom of this section?
        {
            if(--points_on_left <= 0)     // All sections done?
                return;
           			
			l1=v2;
			l2=v3;
			#include "leftedge.h"
			if (left_height<=0)
				return;
			
        }
        else
        {
            Left_x += Delta_left_x;

			#ifdef TEXTURING
				#ifdef PERSPECTIVE
					FLeftZ += FLeft_DZ;
					FLeftU += FLeft_DU;
					FLeftV += FLeft_DV;
				#else
					LeftU += Left_DU;
					LeftV += Left_DV;
				#endif
			#endif
		
			#ifdef MONO_LIGHTING
				LeftMonoLight+=LeftDeltaMonoLight;
			#endif

			#ifdef COLORED_LIGHTING
				LeftRedLight+=LeftDeltaRedLight;
				LeftGreenLight+=LeftDeltaGreenLight;
				LeftBlueLight+=LeftDeltaBlueLight;
			#endif
				
        }

        // Interpolate along the right edge of the triangle
        if(--right_height <= 0) // At the bottom of this section?
        {
            if(--points_on_right <= 0)    // All sections done?
                return;
			l1=v2;
			l2=v3;
			#include "rightedg.h"
            if(right_height <= 0)     // Nope, do the last section
                return;
			
        }
        else
		{
			Right_x += Delta_right_x;
			#ifdef PERSPECTIVE
				FRightZ += FRight_DZ;
				FRightU += FRight_DU;
				FRightV += FRight_DV;
			#endif
				
		}

		destptr += (rowsize);
		desty++;
        
    }
	
#undef PERSPECTIVE
#undef COLORED_LIGHTING
#undef MONO_LIGHTING
#undef TEX_INNER_LOOP
#undef TEXTURING
#undef LIGHT_INNER_LOOP
