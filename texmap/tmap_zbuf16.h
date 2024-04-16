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
			int i;
			fix fx_u,fx_v;
			int texture_width=bm_w(Tex_bitmap,Current_mip);
			ushort *src16=bm_data (Tex_bitmap,Current_mip);
			fix cu,cv;
			int srcptr;
						
			dudx=dvdx;

			float left_u_over_z=FLeftU;
			float left_v_over_z=FLeftV;
			float left_z_over_1=FLeftZ;

			ASSERT (Tex_width<=ZBUFFER_MAX_DIMENSION && Tex_height<=ZBUFFER_MAX_DIMENSION);
					
			
			for (i=0;i<width;i++)
			{
				float left_z=1/left_z_over_1;
				float left_u=left_u_over_z * left_z;
				float left_v=left_v_over_z * left_z;
			
				fx_u=FloatToFix(left_u);
				fx_v=FloatToFix(left_v);

				cu=FixToInt (fx_u);
				cv=FixToInt (fx_v);
				
				cu&=(texture_width-1);
				cv&=(texture_width-1);
				srcptr=(cv*texture_width)+cu;
					
				pix=src16[srcptr];

				if (!(pix & OPAQUE_FLAG))				
				{
					dest++;
					
				}
				else
				{
					if (left_z<=ZBuffer[desty*ZBuffer_width+(x1+i)])
					{
						*dest++ = (TexShadeTable16[31][pix>>8])+TexShadeTable8[31][pix & 0xFF];
						ZBuffer[desty*ZBuffer_width+(x1+i)]=left_z;
					}
					else
					{
						dest++;
						int a=1;
					}
				}
										
				left_z_over_1+=fldzdx;
				left_u_over_z+=fldudx;
				left_v_over_z+=fldvdx;
			}
#endif

