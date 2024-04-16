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
dest = destptr + x1;

BigSteps = width >> 3;
Leftovers = width & 7;

UFrac = LeftU << 16;
VFrac = LeftV << 16;

TexSrc = bm_data8(Tex_bitmap, Current_mip);

__asm {
				push ebp
				mov edi, dest
				mov esi, TexSrc
				mov edx, VFrac
				mov ecx, UFrac
				mov ebx, DeltaUFrac
				shr esi, 1

				cmp BigSteps,0
				je	DoLeftovers
	
				LoopIt:
				
				add edx,DeltaVFrac							; Add in 0.32 DeltaVFrac to VFrac
				sbb ebp,ebp									; ebp will equal -1 if there was a carry
				mov eax, [esi*2]							; get next texel
				add ecx,ebx									; add 0.32 DeltaUFrac to UFrac
				adc esi, [UVStepCarry1+(ebp*4)]				; perform the magical source adjustment
				cmp ax, TRANSPARENT_COLOR
				je jj1
				mov	[edi], ax								; blit destination pixel
				jj1:

				add edx,DeltaVFrac							; Add in 0.32 DeltaVFrac to VFrac
				sbb ebp,ebp									; ebp will equal -1 if there was a carry
				mov eax, [esi*2]							; get next texel
				add ecx,ebx									; add 0.32 DeltaUFrac to UFrac
				adc esi, [UVStepCarry1+(ebp*4)]				; perform the magical source adjustment
				cmp ax, TRANSPARENT_COLOR
				je j2
				mov	[edi+2], ax								; blit destination pixel
				j2:

				add edx,DeltaVFrac							; Add in 0.32 DeltaVFrac to VFrac
				sbb ebp,ebp									; ebp will equal -1 if there was a carry
				mov eax, [esi*2]							; get next texel
				add ecx,ebx									; add 0.32 DeltaUFrac to UFrac
				adc esi, [UVStepCarry1+(ebp*4)]				; perform the magical source adjustment
				cmp ax, TRANSPARENT_COLOR
				je j3
				mov	[edi+4], ax								; blit destination pixel
				j3:

				add edx,DeltaVFrac							; Add in 0.32 DeltaVFrac to VFrac
				sbb ebp,ebp									; ebp will equal -1 if there was a carry
				mov eax, [esi*2]							; get next texel
				add ecx,ebx									; add 0.32 DeltaUFrac to UFrac
				adc esi, [UVStepCarry1+(ebp*4)]				; perform the magical source adjustment
				cmp ax, TRANSPARENT_COLOR
				je j4
				mov	[edi+6], ax								; blit destination pixel
				j4:

				add edx,DeltaVFrac							; Add in 0.32 DeltaVFrac to VFrac
				sbb ebp,ebp									; ebp will equal -1 if there was a carry
				mov eax, [esi*2]							; get next texel
				add ecx,ebx									; add 0.32 DeltaUFrac to UFrac
				adc esi, [UVStepCarry1+(ebp*4)]				; perform the magical source adjustment
				cmp ax, TRANSPARENT_COLOR
				je j5
				mov	[edi+8], ax								; blit destination pixel
				j5:

				add edx,DeltaVFrac							; Add in 0.32 DeltaVFrac to VFrac
				sbb ebp,ebp									; ebp will equal -1 if there was a carry
				mov eax, [esi*2]							; get next texel
				add ecx,ebx									; add 0.32 DeltaUFrac to UFrac
				adc esi, [UVStepCarry1+(ebp*4)]				; perform the magical source adjustment
				cmp ax, TRANSPARENT_COLOR
				je j6
				mov	[edi+10], ax							; blit destination pixel
				j6:

				add edx,DeltaVFrac							; Add in 0.32 DeltaVFrac to VFrac
				sbb ebp,ebp									; ebp will equal -1 if there was a carry
				mov eax, [esi*2]							; get next texel
				add ecx,ebx									; add 0.32 DeltaUFrac to UFrac
				adc esi, [UVStepCarry1+(ebp*4)]				; perform the magical source adjustment
				cmp ax, TRANSPARENT_COLOR
				je j7
				mov	[edi+12], ax							; blit destination pixel
				j7:

				add edx,DeltaVFrac							; Add in 0.32 DeltaVFrac to VFrac
				sbb ebp,ebp									; ebp will equal -1 if there was a carry
				mov eax, [esi*2]							; get next texel
				add ecx,ebx									; add 0.32 DeltaUFrac to UFrac
				adc esi, [UVStepCarry1+(ebp*4)]				; perform the magical source adjustment
				cmp ax, TRANSPARENT_COLOR
				je j8
				mov	[edi+14], ax							; blit destination pixel
				j8:
			

				add edi,16
				dec BigSteps
				jnz LoopIt
		

				DoLeftovers:
				cmp Leftovers, 0
				je Getout

				LoopLeftovers:
			
				add edx,DeltaVFrac							; Add in 0.32 DeltaVFrac to VFrac
				sbb ebp,ebp									; ebp will equal -1 if there was a carry
				mov eax, [esi*2]							; get next texel
				add ecx,ebx									; add 0.32 DeltaUFrac to UFrac
				adc esi, [UVStepCarry1+(ebp*4)]				; perform the magical source adjustment
				cmp ax, TRANSPARENT_COLOR
				je jl1
				mov	[edi], ax								; blit destination pixel
				jl1:
				
				add edi,2
				dec Leftovers
				jnz LoopLeftovers

				Getout:
				pop ebp
}
#endif
