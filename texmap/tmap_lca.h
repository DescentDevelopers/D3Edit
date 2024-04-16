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

			fix u  = LeftU;
            fix v  = LeftV;
			fix rl  = LeftRedLight;
			fix gl  = LeftGreenLight;
			fix bl  = LeftBlueLight;
			ubyte *src;
			
			dest=(destptr+x1);
			src=bm_data8 (Tex_bitmap,Current_mip);
			Current_tex_palette=bm_palette (Tex_bitmap);

			int i;
									
			for (i=0;i<width;i++)
			{
				int rc=FixToInt(rl);
				int gc=FixToInt(gl);
				int bc=FixToInt(bl);
				ushort pix;
				ubyte pix8;
				int r,g,b;
				uint offset=(FixToInt(v)<<8)+FixToInt(u);
				offset&=Ander;
				
				pix8=src[offset];
				pix=Current_tex_palette[((MAX_TEXTURE_SHADES-1)*256)+pix8];
				
				// Get each of our components separated and normalized between 0 and 31
				r=(pix & 0xF800)>>11;
				g=(pix & 0x7E0)>>6;		// Scale green down an extra bit, we'll scale up below
				b=pix & 0x001F;

				if (r-rc<0)
					r=0;
				else r-=rc;

				if (b-bc<0)
					b=0;
				else b-=bc;

				if (g-gc<0)
					g=0;
				else g-=gc;


				r<<=11;
				g<<=6;
				
				pix=r|g|b;
				
				*dest++ = pix;
                u += dudx;
                v += dvdx;
				rl += dlred_dx;
				gl += dlgreen_dx;
				bl += dlblue_dx;	
			}
#endif
