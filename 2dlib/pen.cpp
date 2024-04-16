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
 

#include "lib2d.h"
#include "pserror.h"


#define CLIP_LEFT (vp_InitLeft+vp_Left)
#define CLIP_TOP (vp_InitTop+vp_Top)
#define CLIP_RIGHT (vp_InitLeft+vp_Right)
#define CLIP_BOTTOM (vp_InitTop+vp_Bottom)


void grViewport::hline(ddgr_color col, int x1, int x2, int y1)
{
	ASSERT(vp_Locked);
		
	x1 = global_x(x1);
	y1 = global_y(y1);
	x2 = global_x(x2);

	if (x1>x2)
	{
		int t=x2;
		x2=x1;
		x1=t;
	}

	if (y1 < CLIP_TOP) return;
	if (y1 > CLIP_BOTTOM) return;
	if (x1 > CLIP_RIGHT) return;
	if (x2 < CLIP_LEFT) return;
	if (x1 < CLIP_LEFT) x1 = CLIP_LEFT;
	if (x2 > CLIP_RIGHT) x2 = CLIP_RIGHT;

	rend_SetFlatColor(col);
	rend_DrawLine(x1,y1,x2,y1);
}


//	grViewport::line
//		draws a clipped line

void grViewport::line(ddgr_color color, int x1, int y1, int x2, int y2)
{
	int xa, ya, xb, yb;
	ASSERT(vp_Locked);

	xa = global_x(x1);
	ya = global_y(y1);
	xb = global_x(x2);
	yb = global_y(y2);
	
	rend_SetFlatColor(color);
	rend_DrawLine(x1,y1,x2,y2);
}

void grViewport::rect(ddgr_color color, int l, int t, int r, int b)
{
	ASSERT(vp_Locked);

	l = global_x(l);
	t = global_y(t);
	r = global_x(r);
	b = global_y(b);

	rend_SetFlatColor(color);
	rend_DrawLine(l,t,r,t);
	rend_DrawLine(r,t,r,b);
	rend_DrawLine(l,b,r,b);
	rend_DrawLine(l,t,l,b);
}


void grViewport::fillrect(ddgr_color color, int l, int t, int r, int b)
{
	ASSERT(vp_Locked);

	l = global_x(l);
	t = global_y(t);
	r = global_x(r);
	b = global_y(b);

	rend_FillRect(color, l, t, r, b);
}


void grViewport::circle(ddgr_color col, int xc, int yc, int r)
{
	ASSERT(vp_Locked);

	xc = global_x(xc);
	yc = global_y(yc);

	rend_SetFlatColor(col);
	rend_DrawCircle(xc,yc,r);
}


void grViewport::fillcircle(ddgr_color col, int xc, int yc, int r)
{
	ASSERT(vp_Locked);

	xc = global_x(xc);
	yc = global_y(yc);

	rend_FillCircle(col, xc, yc, r);
}



