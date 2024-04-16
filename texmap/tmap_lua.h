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
BigSteps = width >> 4;
Leftovers = width & 0x0F;

TexSrc = bm_data8(Tex_bitmap, Current_mip);

__asm {
				; edx = U and V in 8:8 format
				; ecx = DU and DV in 8:8 format

				mov edi, dest
				mov esi, TexSrc

				mov edx, LeftV
				shl edx, 8
				mov eax, LeftU
				shr eax, 8
				mov dx, ax

				mov ebx, dvdx
				shl ebx, 8
				mov eax, dudx
				shr eax, 8
				mov bx, ax

				push ebp
				mov ebp, ebx
				mov ebx,0
				mov bh, MAX_TEXTURE_SHADES-1
			
				cmp BigSteps,0
				je DoLeftovers
											
				BigLoop:
			
				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi], ax			; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov     eax, FadeTable[ebx*4]
				mov     [edi+2], ax			; write out texel


				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+4], ax			; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+6], ax			; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+8], ax			; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+10], ax		; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+12], ax		; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+14], ax		; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+16], ax		; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+18], ax		; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+20], ax		; write out texel
			
				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+22], ax		; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+24], ax		; write out texel
		
				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+26], ax		; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+28], ax		; write out texel

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov     [edi+30], ax		; write out texel

				add		edi,32
				dec BigSteps
				jnz BigLoop
				

				DoLeftovers:

				cmp Leftovers, 0
				je Done

				LeftoverLoop:

				mov		eax, edx			; eax=CV:CU in 8.8 format, edx=CV:CU
				shr		eax, 16				; ah=V integer
				mov     al, dh				; al=U integer
				and     eax, [Ander]		; make sure our texture wraps
				mov     bl, [esi+eax]		; get source texel
				add		edx, ebp			; add deltas to U and V
				mov		eax, FadeTable[ebx*4]
				mov		[edi],ax		; write out texel
				
				add		edi,2
				dec Leftovers
				jnz LeftoverLoop

				Done:
				pop ebp
}

#endif
