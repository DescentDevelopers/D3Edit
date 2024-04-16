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

dest = (destptr + x1);
fix fx_u, fx_v;
int i, t;
ubyte pix;
int tw = bm_w(Tex_bitmap, Current_mip);
int th = bm_h(Tex_bitmap, Current_mip);

TexSrc = bm_data8(Tex_bitmap, Current_mip);

BigSteps = width / PIX_PER_SPAN;
Leftovers = width % PIX_PER_SPAN;

float u_affine = fldudx * PIX_PER_SPAN;
float v_affine = fldvdx * PIX_PER_SPAN;
float z_affine = fldzdx * PIX_PER_SPAN;

float left_u_over_z = FLeftU;
float left_v_over_z = FLeftV;
float left_z_over_1 = FLeftZ;

float right_u_over_z = FLeftU + u_affine;
float right_v_over_z = FLeftV + v_affine;
float right_z_over_1 = FLeftZ + z_affine;

float left_z = 1 / left_z_over_1;
float left_u = left_u_over_z * left_z;
float left_v = left_v_over_z * left_z;

float right_z, right_u, right_v;

for (i = 0; i < BigSteps; i++) {
  right_z = 1 / right_z_over_1;
  right_u = right_u_over_z * right_z;
  right_v = right_v_over_z * right_z;

  fx_u = FloatToFix(left_u);
  fx_v = FloatToFix(left_v);

  dudx = FloatToFix((right_u - left_u) / PIX_PER_SPAN);
  dvdx = FloatToFix((right_v - left_v) / PIX_PER_SPAN);

  for (t = 0; t < PIX_PER_SPAN; t++) {
    int u = abs(FixToInt(fx_u) % tw);
    int v = (abs((FixToInt(fx_v)) % th)) << 8; // each row is 256 bytes

    int src_texel = (u + v);
    pix = TexSrc[src_texel];

    if (pix != 0)
      *dest++ = FLAT_SHADE_COLOR;
    else
      dest++;

    fx_u += dudx;
    fx_v += dvdx;
  }

  left_z = right_z;
  left_u = right_u;
  left_v = right_v;

  right_z_over_1 += z_affine;
  right_u_over_z += u_affine;
  right_v_over_z += v_affine;
}
if (Leftovers) {
  right_z_over_1 = FRightZ;
  right_u_over_z = FRightU;
  right_v_over_z = FRightV;

  right_z = 1 / right_z_over_1;
  right_u = right_u_over_z * right_z;
  right_v = right_v_over_z * right_z;

  fx_u = FloatToFix(left_u);
  fx_v = FloatToFix(left_v);

  dudx = FloatToFix((right_u - left_u) / Leftovers);
  dvdx = FloatToFix((right_v - left_v) / Leftovers);

  for (t = 0; t < Leftovers; t++) {
    int u = (FixToInt(fx_u)) % tw;
    int v = ((FixToInt(fx_v)) % th) << 8; // each row is 256 bytes

    int src_texel = (u + v);
    pix = TexSrc[src_texel];

    if (pix != 0)
      *dest++ = FLAT_SHADE_COLOR;
    else
      dest++;

    fx_u += dudx;
    fx_v += dvdx;
  }
}

#endif