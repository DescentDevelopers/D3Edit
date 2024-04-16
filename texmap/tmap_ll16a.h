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

#define FIXUP32 012345678h

// 32677 REPRESENTS OUR 128x128x16 ANDING VALUE

dest = destptr + x1;

BigSteps = width >> 3;
Leftovers = width & 7;

TexSrc16 = bm_data(Tex_bitmap, Current_mip);

if (dldx >= 0) {

  ushort light8 = (LeftMonoLight >> 8);
  ushort dldx8 = dldx / 256;

  __asm {
					; edx = U and V in 8:8 format
					; ebp = DU and DV in 8:8 format

					mov edi, dest
					mov esi, TexSrc16
				
					mov ecx,0
					mov cx, light8
					
					mov ebx, 0
					mov bx, dldx8
					mov DeltaLight, ebx

                                         // StartCoords:
				
					mov edx, LeftV
					shl edx, 8
					mov eax, LeftU
					shr eax, 8
					shl eax, 1
					mov dx, ax			; edx= V:U in 8.8 format
	
					mov ebx, dvdx
					shl ebx, 8
					mov eax, dudx
					shr eax, 8
					shl eax, 1
					mov bx, ax

					push ebp
					mov ebp, ebx		; ebp= DV:DU in 8.8 format

					cmp BigSteps,0
					je DoLeftovers
				
					BigLoop:
			
					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+2], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+4], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+6], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+8], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+10], ax			; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+12], ax			; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+14], ax			; write out texel

					add		edi,16
					dec BigSteps
					jnz BigLoop
				
					DoLeftovers:

					cmp Leftovers,0
					je done

					LeftoverLoop:
				
					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi], ax				; write out texel

					add edi,2
					dec Leftovers
					jnz LeftoverLoop

					done:
					pop ebp
  }
} else {

  ushort light8 = (IntToFix(MAX_TEXTURE_SHADES - 1) - LeftMonoLight) >> 8;
  ushort dldx8 = (-dldx) / 256;

  __asm {
					; edx = U and V in 8:8 format
					; ecx = DU and DV in 8:8 format

					mov edi, dest
					mov esi, TexSrc16
				
					mov ecx,0
					mov cx, light8
										
					mov ebx,0
					mov bx, dldx8

					mov DeltaLight, ebx

                                         // StartCoords:
				
					mov edx, LeftV
					shl edx, 8
					mov eax, LeftU
					shr eax, 8
					shl eax, 1
					mov dx, ax			; edx= V:U in 8.8 format
	
					mov ebx, dvdx
					shl ebx, 8
					mov eax, dudx
					shr eax, 8
					shl eax, 1
					mov bx, ax

					push ebp
					mov ebp, ebx		; ebp= DV:DU in 8.8 format

					cmp BigSteps,0
					je DoLeftovers2
				
					BigLoop2:
			
					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexRevShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexRevShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexRevShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexRevShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+2], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexRevShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexRevShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+4], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexRevShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexRevShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+6], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexRevShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexRevShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+8], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexRevShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexRevShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+10], ax			; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexRevShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexRevShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+12], ax			; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexRevShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexRevShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi+14], ax			; write out texel

					add		edi,16
					dec BigSteps
					jnz BigLoop2
				
					DoLeftovers2:

					cmp Leftovers,0
					je done2

					LeftoverLoop2:
				
					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     al, dh						; al=U integer
					and     eax, 32766				; make sure our texture wraps
					mov ebx, [esi+eax]			; get source texel
					mov     ah, bh						; save upper 8 bits of texel in ah
					mov     bh, ch						; bx now equals light:lower 8 bits
					and     ebx, 0FFFFh					; clear out upper 16bits of ebx
					mov     al, TexRevShadeTable8[ebx]		; get lower 8bit shaded pixel
					add		edx, ebp					; add deltas to U and V			
					mov     bl, ah						
					mov     ah,0						
					add		eax, TexRevShadeTable16[ebx*4]
					add     ecx, DeltaLight
					mov [edi], ax				; write out texel

					add edi,2
					dec Leftovers
					jnz LeftoverLoop2

					done2:
					pop ebp
  }
}

#endif
