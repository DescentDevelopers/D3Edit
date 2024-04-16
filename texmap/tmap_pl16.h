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
 #ifdef ACTIVATE_INNER_LOOP
		
			fix fx_l  = LeftMonoLight;

			ushort pix;
			dest=(destptr+x1);
			int i,t;
			fix fx_u,fx_v;
			float right_u,right_v,right_z;
			int texture_width=bm_w(Tex_bitmap,Current_mip);
			ushort *src16=bm_data (Tex_bitmap,Current_mip);
			
			fix cu,cv,cl;
			int srcptr;

			BigSteps=width/16;
			Leftovers=width%16;

			float u_affine=fldudx*16;
			float v_affine=fldvdx*16;
			float z_affine=fldzdx*16;

			float left_u_over_z=FLeftU;
			float left_v_over_z=FLeftV;
			float left_z_over_1=FLeftZ;

			float right_u_over_z=FLeftU+u_affine;
			float right_v_over_z=FLeftV+v_affine;
			float right_z_over_1=FLeftZ+z_affine;

			float left_z=1/left_z_over_1;
			float left_u=left_u_over_z * left_z;
			float left_v=left_v_over_z * left_z;
			
			for (i=0;i<BigSteps;i++)
			{
				right_z=1/right_z_over_1;
				right_u=right_u_over_z * right_z;
				right_v=right_v_over_z * right_z;

				fx_u=FloatToFix(left_u);
				fx_v=FloatToFix(left_v);

				dudx=FloatToFix((right_u-left_u)/16);
				dvdx=FloatToFix((right_v-left_v)/16);

				for (t=0;t<16;t++)
				{
					cu=FixToInt (fx_u);
					cv=FixToInt (fx_v);
					cl=FixToInt(fx_l);

					cu&=(texture_width-1);
					cv&=(texture_width-1);
					srcptr=(cv*texture_width)+cu;
					
					pix=src16[srcptr];

					if (! (pix & OPAQUE_FLAG))				
						dest++;
					else
						*dest++ = (TexShadeTable16[cl][pix>>8])+TexShadeTable8[cl][pix & 0xFF];
										
										
					
					fx_u+=dudx;
					fx_v+=dvdx;
					fx_l+=dldx;
				}

				left_z=right_z;
				left_u=right_u;
				left_v=right_v;

				right_z_over_1+=z_affine;
				right_u_over_z+=u_affine;
				right_v_over_z+=v_affine;
			}
			if (Leftovers)
			{
				
				right_z_over_1=FRightZ;
				right_u_over_z=FRightU;
				right_v_over_z=FRightV;

				right_z=1/right_z_over_1;
				right_u=right_u_over_z * right_z;
				right_v=right_v_over_z * right_z;

				fx_u=FloatToFix(left_u);
				fx_v=FloatToFix(left_v);

				dudx=FloatToFix((right_u-left_u)/Leftovers);
				dvdx=FloatToFix((right_v-left_v)/Leftovers);
				
				for (t=0;t<Leftovers;t++)
				{
					cu=FixToInt (fx_u);
					cv=FixToInt (fx_v);
					cl=FixToInt(fx_l);

					cu&=(texture_width-1);
					cv&=(texture_width-1);
					srcptr=(cv*texture_width)+cu;

					pix=src16[srcptr];

					if (!(pix & OPAQUE_FLAG))				
						dest++;
					else				
						*dest++ = (TexShadeTable16[cl][pix>>8])+TexShadeTable8[cl][pix & 0xFF];
									
					fx_u+=dudx;
					fx_v+=dvdx;
					fx_l+=dldx;
				}

				
			}


#endif

