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
 

#include "3d.h"
#include "Globvars.h"

#define MAX_INSTANCE_DEPTH	30

struct instance_context {
	matrix m;
	matrix um;	// unscaled matrix
	vector p;
} instance_stack[MAX_INSTANCE_DEPTH];

int instance_depth = 0;

//instance at specified point with specified orientation
//if matrix==NULL, don't modify matrix.  This will be like doing an offset   
void g3_StartInstanceMatrix(vector *pos,matrix *orient)
{
	vector tempv;
	matrix tempm,tempm2;

	ASSERT(instance_depth<MAX_INSTANCE_DEPTH);

	instance_stack[instance_depth].m = View_matrix;
	instance_stack[instance_depth].p = View_position;
	instance_stack[instance_depth].um = Unscaled_matrix;
	instance_depth++;

	//step 1: subtract object position from view position

	tempv = View_position - *pos;


	if (orient) {

		//step 2: rotate view vector through object matrix

		View_position = tempv * *orient;

		//step 3: rotate object matrix through view_matrix (vm = ob * vm)

		tempm2 = ~*orient;

		tempm = tempm2 * View_matrix;

		View_matrix = tempm;

		tempm = tempm2 * Unscaled_matrix;

		Unscaled_matrix = tempm;
	}
}


//instance at specified point with specified orientation
//if angles==NULL, don't modify matrix.  This will be like doing an offset
void g3_StartInstanceAngles(vector *pos,angvec *angles)
{
	matrix tm;

	if (angles==NULL) {
		g3_StartInstanceMatrix(pos,NULL);
		return;
	}

	vm_AnglesToMatrix(&tm,angles->p,angles->h,angles->b);

	g3_StartInstanceMatrix(pos,&tm);

}


//pops the old context
void g3_DoneInstance()
{
	instance_depth--;

	ASSERT(instance_depth >= 0);

	View_position = instance_stack[instance_depth].p;
	View_matrix = instance_stack[instance_depth].m;
	Unscaled_matrix=instance_stack[instance_depth].um;
}


