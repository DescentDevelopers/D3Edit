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
 
	left_height=cp[vlb].screeny-cp[vlt].screeny;
	if (left_height<RECIP_TABLE_SIZE)
		fx_recip_dyl=Fix_recip_table[left_height];
	else
		fx_recip_dyl=F1_0/left_height;
	
	Left_x=IntToFix(cp[vlt].screenx);
	Delta_left_x=FixMul(IntToFix(cp[vlb].screenx-cp[vlt].screenx),fx_recip_dyl);
	next_break_left = cp[vlb].screeny;
	
	
#ifdef PERSPECTIVE 
	
	if (left_height<RECIP_TABLE_SIZE)
		fl_recip_dyl=Float_recip_table[left_height];
	else
		fl_recip_dyl=1.0/left_height;
		
	FLeftZ= cp[vlt].flzcoord;
	FLeft_DZ = (cp[vlb].flzcoord-FLeftZ) * fl_recip_dyl;

	FLeftU= cp[vlt].flucoord;
	FLeft_DU = (cp[vlb].flucoord-FLeftU) * fl_recip_dyl;

	FLeftV= cp[vlt].flvcoord;
	FLeft_DV = (cp[vlb].flvcoord-FLeftV) * fl_recip_dyl;
	
#else
	LeftU=cp[vlt].ucoord;
    Left_DU = FixMul(cp[vlb].ucoord-LeftU,fx_recip_dyl);
	LeftV=cp[vlt].vcoord;
    Left_DV = FixMul(cp[vlb].vcoord-LeftV,fx_recip_dyl);
    
#endif
#ifdef MONO_LIGHTING 
	LeftMonoLight=cp[vlt].monolight;
	LeftDeltaMonoLight = FixMul(cp[vlb].monolight - LeftMonoLight,fx_recip_dyl);
#endif
#ifdef COLORED_LIGHTING 
	LeftRedLight=cp[vlt].redlight;
	LeftDeltaRedLight = FixMul(cp[vlb].redlight - LeftRedLight,fx_recip_dyl);
	LeftGreenLight=cp[vlt].greenlight;
	LeftDeltaGreenLight = FixMul(cp[vlb].greenlight - LeftGreenLight,fx_recip_dyl);
	LeftBlueLight=cp[vlt].bluelight;
	LeftDeltaBlueLight = FixMul(cp[vlb].bluelight - LeftBlueLight,fx_recip_dyl);
#endif
