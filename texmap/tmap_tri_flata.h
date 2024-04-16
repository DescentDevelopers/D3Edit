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
dest = destptr;

int xs = x1;
int xe = x1 + width - 1;

if (xs & 1) {
  dest[xs++] = Flat_polygon_color;
}
if (!(xe & 1))
  dest[xe--] = Flat_polygon_color;

int count = (xe - xs + 1) / 2;

dest += xs;

if (count) {
  __asm {
					mov ax,Flat_polygon_color
					shl eax,16
					mov ax,Flat_polygon_color
					mov edi,dest
					mov ecx,count

					loopit:

					mov [edi], eax

					add edi, 4
					dec ecx
					jnz loopit

  }
}

#endif
