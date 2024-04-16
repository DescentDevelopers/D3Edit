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
 // This file interpolates gradients down the left edge of the triangle

right_height = l2->screeny - l1->screeny;
if (right_height>0)
{
    Delta_right_x = IntToFix(l2->screenx - l1->screenx) / right_height;
    Right_x = IntToFix(l1->screenx);

#ifdef PERSPECTIVE 
	FRight_DZ = (l2->flzcoord - l1->flzcoord)/right_height;
	FRightZ=  (l1->flzcoord);
	FRight_DU = (l2->flucoord - l1->flucoord)/right_height;
	FRightU=  (l1->flucoord);
	FRight_DV = (l2->flvcoord - l1->flvcoord)/right_height;
	FRightV=  (l1->flvcoord);
#endif
}
