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

right_height = cp[vrb].screeny - cp[vrt].screeny;

if (right_height < RECIP_TABLE_SIZE)
  fx_recip_dyr = Fix_recip_table[right_height];
else
  fx_recip_dyr = F1_0 / right_height;

Delta_right_x = FixMul(IntToFix(cp[vrb].screenx - cp[vrt].screenx), fx_recip_dyr);
Right_x = IntToFix(cp[vrt].screenx);
next_break_right = cp[vrb].screeny;

#ifdef PERSPECTIVE

if (right_height < RECIP_TABLE_SIZE)
  fl_recip_dyr = Float_recip_table[right_height];
else
  fl_recip_dyr = 1.0 / right_height;

FRightZ = cp[vrt].flzcoord;
FRight_DZ = (cp[vrb].flzcoord - FRightZ) * fl_recip_dyr;

FRightU = cp[vrt].flucoord;
FRight_DU = (cp[vrb].flucoord - FRightU) * fl_recip_dyr;

FRightV = cp[vrt].flvcoord;
FRight_DV = (cp[vrb].flvcoord - FRightV) * fl_recip_dyr;

#else
RightU = cp[vrt].ucoord;
Right_DU = FixMul(cp[vrb].ucoord - RightU, fx_recip_dyr);
RightV = cp[vrt].vcoord;
Right_DV = FixMul(cp[vrb].vcoord - RightV, fx_recip_dyr);

#endif
#ifdef MONO_LIGHTING
RightMonoLight = cp[vrt].monolight;
RightDeltaMonoLight = FixMul(cp[vrb].monolight - RightMonoLight, fx_recip_dyr);
#endif
#ifdef COLORED_LIGHTING
RightRedLight = cp[vrt].redlight;
RightDeltaRedLight = FixMul(cp[vrb].redlight - RightRedLight, fx_recip_dyr);
RightGreenLight = cp[vrt].greenlight;
RightDeltaGreenLight = FixMul(cp[vrb].greenlight - RightGreenLight, fx_recip_dyr);
RightBlueLight = cp[vrt].bluelight;
RightDeltaBlueLight = FixMul(cp[vrb].bluelight - RightBlueLight, fx_recip_dyr);
#endif
