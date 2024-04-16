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

left_height = l2->screeny - l1->screeny;
if (left_height > 0) {
  if (left_height < RECIP_TABLE_SIZE)
    fx_recip_dyl = Fix_recip_table[left_height];
  else
    fx_recip_dyl = F1_0 / left_height;

  Left_x = IntToFix(l1->screenx);
  Delta_left_x = FixMul(IntToFix(l2->screenx - l1->screenx), fx_recip_dyl);

#ifdef TEXTURING
#ifdef PERSPECTIVE

  FLeft_DZ = (l2->flzcoord - l1->flzcoord) / left_height;
  FLeftZ = (l1->flzcoord);
  FLeft_DU = (l2->flucoord - l1->flucoord) / left_height;
  FLeftU = (l1->flucoord);
  FLeft_DV = (l2->flvcoord - l1->flvcoord) / left_height;
  FLeftV = (l1->flvcoord);
#else
  Left_DU = FixMul((l2->ucoord - l1->ucoord), fx_recip_dyl);
  LeftU = (l1->ucoord);
  Left_DV = FixMul((l2->vcoord - l1->vcoord), fx_recip_dyl);
  LeftV = (l1->vcoord);
#endif
#endif

#ifdef MONO_LIGHTING
  LeftMonoLight = l1->monolight;
  LeftDeltaMonoLight = FixMul((l2->monolight - l1->monolight), fx_recip_dyl);
#endif
#ifdef COLORED_LIGHTING
  LeftRedLight = l1->redlight;
  LeftDeltaRedLight = (l2->redlight - l1->redlight) / left_height;
  LeftGreenLight = l1->greenlight;
  LeftDeltaGreenLight = (l2->greenlight - l1->greenlight) / left_height;
  LeftBlueLight = l1->bluelight;
  LeftDeltaBlueLight = (l2->bluelight - l1->bluelight) / left_height;
#endif
}
