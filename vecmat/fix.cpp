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
 #include "fix.h"

fix vm_FloatToFix( float x )
{
	// A fast way to convert floats to fix

	float nf;
    nf = x*65536.0f + 8390656.0f;
    return ((*((int *)&nf)) & 0x7FFFFF)-2048;
}

inline fix vm_FixDiv (fix a,fix b)
{
	__asm 
	{
		mov eax,a
		mov ebx,b
		cdq
		shld edx, eax, 16
		sal eax,16
		idiv ebx
	}
}


inline fix vm_FixMul (fix a,fix b)
{
	__asm
	{
		mov eax,a
		mov ebx,b	
	    imul ebx
        shrd eax,edx,16
	}
}

inline fix vm_FixMulDiv (fix a,fix b,fix c)
{
	__asm 	
	{
		mov eax, a
		mov edx, b
		mov ebx, c
		imul edx
		idiv ebx
	}
}

inline void vm_FixSubVectors (fix_vector *result,fix_vector *a,fix_vector *b)
{
	result->x=a->x-b->x;
	result->y=a->y-b->y;
	result->z=a->z-b->z;
}

inline void vm_FixScaleAddVector (fix_vector *d,fix_vector *p,fix_vector *v,fix s)
{
	// Scales all components of vector v by value s
	// adds the result to p and stores result in vector d
	// dest can equal source

	d->x=p->x+vm_FixMul(v->x,s);
	d->y=p->y+vm_FixMul(v->y,s);
	d->z=p->z+vm_FixMul(v->z,s);
}

inline fix vm_FixGetMagnitude (fix_vector *a)
{
	float f;
	fix r;

	f=FixToFloat (a->x) * FixToFloat (a->x) +
	FixToFloat (a->y) * FixToFloat (a->y) +
	FixToFloat (a->z) * FixToFloat (a->z); 

	r=FloatToFix (sqrt(f));

	return (r); 
}

inline fix vm_FixGetMagnitudeFast(fix_vector *v)
{
	fix a,b,c,bc;

	a = labs(v->x);
	b = labs(v->y);
	c = labs(v->z);

	if (a < b) 
	{
		fix t=a; a=b; b=t;
	}

	if (b < c) 
	{
		fix t=b; b=c; c=t;

		if (a < b) 
		{
			fix t=a; a=b; b=t;
		}
	}

	bc = (b>>2) + (c>>3);

	return a + bc + (bc>>1);
}


inline void vm_FixDivVector (fix_vector *dest,fix_vector *src,fix n)
{
	// Divides a vector into n portions
	// Dest can equal src

	dest->x=vm_FixDiv(src->x,n);
	dest->y=vm_FixDiv(src->y,n);
	dest->z=vm_FixDiv(src->z,n);
}
inline void vm_FixAddVectors (fix_vector *result,fix_vector *a,fix_vector *b)
{
	result->x=a->x+b->x;
	result->y=a->y+b->y;
	result->z=a->z+b->z;
}










