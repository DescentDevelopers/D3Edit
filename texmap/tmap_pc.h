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
ushort pix;

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

fix rl = LeftRedLight;
fix gl = LeftGreenLight;
fix bl = LeftBlueLight;

Current_tex_palette = bm_palette(Tex_bitmap);
ubyte *src = bm_data8(Tex_bitmap, Current_mip);

for (i = 0; i < BigSteps; i++) {
  right_z = 1 / right_z_over_1;
  right_u = right_u_over_z * right_z;
  right_v = right_v_over_z * right_z;

  fx_u = FloatToFix(left_u);
  fx_v = FloatToFix(left_v);

  dudx = FloatToFix((right_u - left_u) / PIX_PER_SPAN);
  dvdx = FloatToFix((right_v - left_v) / PIX_PER_SPAN);

  for (t = 0; t < PIX_PER_SPAN; t++) {
    int rc = FixToInt(rl);
    int gc = FixToInt(gl);
    int bc = FixToInt(bl);

    ubyte pix8;
    int r, g, b;
    uint offset = (FixToInt(fx_v) << 8) + FixToInt(fx_u);
    offset &= Ander;

    pix8 = src[offset];
    pix = Current_tex_palette[((MAX_TEXTURE_SHADES - 1) * 256) + pix8];

    // Get each of our components separated and normalized between 0 and 31
    r = (pix & 0xF800) >> 11;
    g = (pix & 0x7E0) >> 6; // Scale green down an extra bit, we'll scale up below
    b = pix & 0x001F;

    if (r - rc < 0)
      r = 0;
    else
      r -= rc;

    if (b - bc < 0)
      b = 0;
    else
      b -= bc;

    if (g - gc < 0)
      g = 0;
    else
      g -= gc;

    r <<= 11;
    g <<= 6;

    pix = r | g | b;

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
    int rc = FixToInt(rl);
    int gc = FixToInt(gl);
    int bc = FixToInt(bl);

    ubyte pix8;
    int r, g, b;
    uint offset = (FixToInt(fx_v) << 8) + FixToInt(fx_u);
    offset &= Ander;

    pix8 = src[offset];
    pix = Current_tex_palette[((MAX_TEXTURE_SHADES - 1) * 256) + pix8];

    // Get each of our components separated and normalized between 0 and 31
    r = (pix & 0xF800) >> 11;
    g = (pix & 0x7E0) >> 6; // Scale green down an extra bit, we'll scale up below
    b = pix & 0x001F;

    if (r - rc < 0)
      r = 0;
    else
      r -= rc;

    if (b - bc < 0)
      b = 0;
    else
      b -= bc;

    if (g - gc < 0)
      g = 0;
    else
      g -= gc;

    r <<= 11;
    g <<= 6;

    pix = r | g | b;

    fx_u += dudx;
    fx_v += dvdx;
  }
}

#endif