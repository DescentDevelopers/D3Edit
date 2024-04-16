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

dest = destptr + x1;

BigSteps = width >> 3;
Leftovers = width & 7;

TexSrc = bm_data8(Tex_bitmap, Current_mip);
Current_tex_palette = bm_palette(Tex_bitmap);
static int old_ander = -1;

if (1) {

  __asm {
					; edx = U and V in 8:8 format
					; ecx = DU and DV in 8:8 format

					mov edi, dest
					mov esi, TexSrc
				
					mov ecx, LeftMonoLight
					shr ecx, 8
					
					mov edx, Ander
					cmp edx, old_ander		; is this a new polygon?
					je StartCoords			; no? then skip fixup
					
					mov AFixer1-4, edx
					mov AFixer2-4, edx
					mov AFixer3-4, edx
					mov AFixer4-4, edx
					mov AFixer5-4, edx
					mov AFixer6-4, edx
					mov AFixer7-4, edx
					mov AFixer8-4, edx
					mov AFixer9-4, edx

					mov old_ander, edx

					StartCoords:
				
					mov edx, LeftV
					shl edx, 8
					mov eax, LeftU
					shr eax, 8
					mov dx, ax			; edx= V:U in 8.8 format
	
					mov ebx, dvdx
					shl ebx, 8
					mov eax, dudx
					shr eax, 8
					mov bx, ax

					push ebp
					mov ebp, ebx		; ebp= DV:DU in 8.8 format
					mov ebx,0

					cmp BigSteps,0
					je DoLeftovers

					BigLoop:

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     bh, ch						; save upper 8 bits of texel in ah
					mov     al, dh						; al=U integer
					and     eax, FIXUP32				; make sure our texture wraps
					AFixer1:mov bl, [esi+eax]			; get source texel
					mov     eax, Current_tex_palette
					add		edx, ebp					; add deltas to U and V			
					add     ecx, [Lighting8]
					mov     eax,[eax+ebx*2]
					mov     [edi], ax					; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     bh, ch						; save upper 8 bits of texel in ah
					mov     al, dh						; al=U integer
					and     eax, FIXUP32				; make sure our texture wraps
					AFixer2:mov bl, [esi+eax]			; get source texel
					mov     eax, Current_tex_palette
					add		edx, ebp					; add deltas to U and V			
					add     ecx, [Lighting8]
					mov     eax,[eax+ebx*2]
					mov     [edi+2], ax					; write out texel


					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     bh, ch						; save upper 8 bits of texel in ah
					mov     al, dh						; al=U integer
					and     eax, FIXUP32				; make sure our texture wraps
					AFixer3:mov bl, [esi+eax]			; get source texel
					mov     eax, Current_tex_palette
					add		edx, ebp					; add deltas to U and V			
					add     ecx, [Lighting8]
					mov     eax,[eax+ebx*2]
					mov     [edi+4], ax					; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     bh, ch						; save upper 8 bits of texel in ah
					mov     al, dh						; al=U integer
					and     eax, FIXUP32				; make sure our texture wraps
					AFixer4:mov bl, [esi+eax]			; get source texel
					mov     eax, Current_tex_palette
					add		edx, ebp					; add deltas to U and V			
					add     ecx, [Lighting8]
					mov     eax,[eax+ebx*2]
					mov     [edi+6], ax					; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     bh, ch						; save upper 8 bits of texel in ah
					mov     al, dh						; al=U integer
					and     eax, FIXUP32				; make sure our texture wraps
					AFixer5:mov bl, [esi+eax]			; get source texel
					mov     eax, Current_tex_palette
					add		edx, ebp					; add deltas to U and V			
					add     ecx, [Lighting8]
					mov     eax,[eax+ebx*2]
					mov     [edi+8], ax					; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     bh, ch						; save upper 8 bits of texel in ah
					mov     al, dh						; al=U integer
					and     eax, FIXUP32				; make sure our texture wraps
					AFixer6:mov bl, [esi+eax]			; get source texel
					mov     eax, Current_tex_palette
					add		edx, ebp					; add deltas to U and V			
					add     ecx, [Lighting8]
					mov     eax,[eax+ebx*2]
					mov     [edi+10], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     bh, ch						; save upper 8 bits of texel in ah
					mov     al, dh						; al=U integer
					and     eax, FIXUP32				; make sure our texture wraps
					AFixer7:mov bl, [esi+eax]			; get source texel
					mov     eax, Current_tex_palette
					add		edx, ebp					; add deltas to U and V			
					add     ecx, [Lighting8]
					mov     eax,[eax+ebx*2]
					mov     [edi+12], ax				; write out texel

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     bh, ch						; save upper 8 bits of texel in ah
					mov     al, dh						; al=U integer
					and     eax, FIXUP32				; make sure our texture wraps
					AFixer8:mov bl, [esi+eax]			; get source texel
					mov     eax, Current_tex_palette
					add		edx, ebp					; add deltas to U and V			
					add     ecx, [Lighting8]
					mov     eax,[eax+ebx*2]
					mov     [edi+14], ax				; write out texel

					add edi,16
					dec BigSteps
					jnz BigLoop

					DoLeftovers:

					cmp Leftovers,0
					je done

					LeftoverLoop:

					mov		eax, edx					; eax=CV:CU in 8.8 format, edx=CV:CU
					shr		eax, 16						; ah=V integer
					mov     bh, ch						; save upper 8 bits of texel in ah
					mov     al, dh						; al=U integer
					and     eax, FIXUP32				; make sure our texture wraps
					AFixer9:mov bl, [esi+eax]			; get source texel
					mov     eax, Current_tex_palette
					add		edx, ebp					; add deltas to U and V			
					add     ecx, [Lighting8]
					mov     eax,[eax+ebx*2]
					mov     [edi], ax					; write out texel
		
					add edi,2
					dec Leftovers
					jnz LeftoverLoop

					done:
					pop ebp
  }
}

#endif