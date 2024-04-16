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
// #define PERSPECTIVE		1=PERSPECTIVE 0=LINEAR
// #define MONO_LIGHTING	1=MONO LIGHTING 0=FULLY BRIGHT
// #define COLORED_LIGHTING 1=COLORED LIGHTS 0=FULLY BRIGHT

#ifdef COLORED_LIGHTING
fix LeftRedLight, LeftDeltaRedLight, LeftGreenLight, LeftDeltaGreenLight, LeftBlueLight, LeftDeltaBlueLight;
fix RightRedLight, RightDeltaRedLight, RightGreenLight, RightDeltaGreenLight, RightBlueLight, RightDeltaBlueLight;
fix dlred_dx, dlgreen_dx, dlblue_dx;
#elif defined(MONO_LIGHTING)
fix LeftMonoLight, LeftDeltaMonoLight;
fix RightMonoLight, RightDeltaMonoLight;
fix dldx;
#else
fix LeftMonoLight, dldx;
#endif

#ifdef PERSPECTIVE
float fldzdx, fldudx, fldvdx;
float fl_recip_dyl, fl_recip_dyr, fl_recipx;
#endif

int i;
texs_texpoint cp[100];

int height, left_height, right_height, y;
int vlt, vlb, vrt, vrb, max_y_vertex, top_y, bottom_y, desty;
int next_break_left, next_break_right;

float closest_z = 90000000;
fix dudx, dvdx, fx_recip_dyl, fx_recip_dyr, fx_recipx;
ushort *destptr, *dest;

int new_triangle = 1;

// change points into texpoints

for (i = 0; i < nv; i++) {
  // g3Point tp=p[i];

  ASSERT(p[i].p3_flags & PF_PROJECTED);

  if (p[i].p3_vec.z < closest_z)
    closest_z = p[i].p3_vec.z;

  cp[i].screenx = p[i].p3_sx + Tex_x1;
  cp[i].screeny = p[i].p3_sy + Tex_y1;

#ifndef PERSPECTIVE
  cp[i].ucoord = FloatToFix(p[i].p3_u);
  cp[i].vcoord = FloatToFix(p[i].p3_v);
#else
  cp[i].flucoord = (p[i].p3_u);
  cp[i].flvcoord = (p[i].p3_v);
#endif

#ifdef PERSPECTIVE
  cp[i].flzcoord = p[i].p3_vec.z;
  cp[i].flscreenx = p[i].p3_sx + Tex_x1;
  cp[i].flscreeny = p[i].p3_sy + Tex_y1;
  if (cp[i].flzcoord < 0.000015)
    cp[i].flzcoord = 0.000015f;
#endif

#ifdef MONO_LIGHTING
  ASSERT(p[i].p3_l >= 0 && p[i].p3_l <= 1);
  cp[i].monolight = FloatToFix(p[i].p3_l * (MAX_TEXTURE_SHADES - 1));
#endif

#ifdef COLORED_LIGHTING
  ASSERT(p[i].p3_r >= 0 && p[i].p3_r <= 1);
  ASSERT(p[i].p3_g >= 0 && p[i].p3_g <= 1);
  ASSERT(p[i].p3_b >= 0 && p[i].p3_b <= 1);

  cp[i].redlight = FloatToFix((1 - p[i].p3_r) * (MAX_TEXTURE_SHADES - 1));
  cp[i].greenlight = FloatToFix((1 - p[i].p3_g) * (MAX_TEXTURE_SHADES - 1));
  cp[i].bluelight = FloatToFix((1 - p[i].p3_b) * (MAX_TEXTURE_SHADES - 1));
#endif
}

if (bm_mipped(Tex_bitmap) && Mips_on && Renderer_type != RENDERER_SOFTWARE_16BIT) {
  for (i = 0; i < NUM_MIP_LEVELS; i++) {
    if (closest_z <= MipChoices[i]) {
      Current_mip = i;
      break;
    }
    Current_mip = NUM_MIP_LEVELS - 1;
  }
} else
  Current_mip = 0;

ASSERT(Current_mip < NUM_MIP_LEVELS);

// Get our AND value for this polygon
Ander = tex_GetAnder(Tex_bitmap, Current_mip);

for (i = 0; i < nv; i++) {
#ifndef PERSPECTIVE
  cp[i].ucoord = cp[i].ucoord * (bm_w(Tex_bitmap, Current_mip));
  cp[i].vcoord = cp[i].vcoord * (bm_h(Tex_bitmap, Current_mip));
#else
  cp[i].flucoord = cp[i].flucoord * (bm_w(Tex_bitmap, Current_mip));
  cp[i].flvcoord = cp[i].flvcoord * (bm_h(Tex_bitmap, Current_mip));
#endif
}

#ifdef PERSPECTIVE
// If this is a perspective map, change our coords to be u/z v/z and 1/z
for (i = 0; i < nv; i++) {
  cp[i].flzcoord = 1.0 / cp[i].flzcoord;
  cp[i].flucoord *= cp[i].flzcoord;
  cp[i].flvcoord *= cp[i].flzcoord;
}
#endif

// Determine top and bottom y coords.
tex_GetVertexOrdering(cp, nv, &vlt, &vlb, &vrt, &vrb, &max_y_vertex);

top_y = cp[vlt].screeny;
bottom_y = cp[max_y_vertex].screeny;

height = bottom_y - top_y;
if (height == 0)
  return;

#include "quadleftedge.h"
#include "quadrightedge.h"

// Set the destptr to equal the first row to draw to
destptr = (ushort *)Tex_framebuffer + (top_y * Tex_pitch / 2);
desty = top_y;

for (y = top_y; y < bottom_y; y++) {
  if (y == next_break_left) {
    while (y == cp[vlb].screeny) {
      vlt = vlb;
      vlb = tex_PrevIndex(vlb, nv);
    }
    new_triangle = 1;
#include "quadleftedge.h"
  }

  if (y == next_break_right) {
    while (y == cp[vrb].screeny) {
      vrt = vrb;
      vrb = tex_NextIndex(vrb, nv);
    }
    new_triangle = 1;
#include "quadrightedge.h"
  }

  // Draw a scanline

  int x1 = FixToInt(Left_x);
  int width = (FixToInt(Right_x) - x1) + 1;

  if (desty < 0 || desty >= Tex_height)
    goto UpdateExtents;

  if (x1 < 0 || x1 >= Tex_width)
    goto UpdateExtents;
  if ((x1 + width) > Tex_width) {
    width = (Tex_width - x1);
  }

  if (width > 0) {

    if (width < RECIP_TABLE_SIZE)
      fx_recipx = Fix_recip_table[width - 1];
    else
      fx_recipx = F1_0 / width;

#ifdef COLORED_LIGHTING

    dlred_dx = FixMul(RightRedLight - LeftRedLight, fx_recipx);
    dlgreen_dx = FixMul(RightGreenLight - LeftGreenLight, fx_recipx);
    dlblue_dx = FixMul(RightBlueLight - LeftBlueLight, fx_recipx);

#elif defined(MONO_LIGHTING)
    dldx = FixMul(RightMonoLight - LeftMonoLight, fx_recipx);
    Lighting8 = dldx >> 8;

    if (Lighting8 < 0)
      Lighting8++; // round towards 0 for negative deltas

#else // Uses lighted inner loop, but just set full brightness
    LeftMonoLight = IntToFix(MAX_TEXTURE_SHADES - 1);
    Lighting8 = 0;
    dldx = 0;
#endif

#ifdef PERSPECTIVE

    if (width < RECIP_TABLE_SIZE)
      fl_recipx = Float_recip_table[width - 1];
    else
      fl_recipx = 1.0 / (width - 1);

    fldudx = (FRightU - FLeftU) * fl_recipx;
    fldvdx = (FRightV - FLeftV) * fl_recipx;
    fldzdx = (FRightZ - FLeftZ) * fl_recipx;
#else
    dudx = FixMul(RightU - LeftU, fx_recipx);
    dvdx = FixMul(RightV - LeftV, fx_recipx);
#endif

#define ACTIVATE_INNER_LOOP

#include TEX_INNER_LOOP

#undef ACTIVATE_INNER_LOOP
  }

UpdateExtents:

  destptr += (Tex_pitch / 2);
  desty++;

  Left_x += Delta_left_x;
  Right_x += Delta_right_x;

#ifdef PERSPECTIVE
  FLeftZ += FLeft_DZ;
  FLeftU += FLeft_DU;
  FLeftV += FLeft_DV;

  FRightZ += FRight_DZ;
  FRightU += FRight_DU;
  FRightV += FRight_DV;
#else
  LeftU += Left_DU;
  LeftV += Left_DV;

  RightU += Right_DU;
  RightV += Right_DV;
#endif

#ifdef MONO_LIGHTING
  LeftMonoLight += LeftDeltaMonoLight;
  RightMonoLight += RightDeltaMonoLight;
#endif

#ifdef COLORED_LIGHTING
  LeftRedLight += LeftDeltaRedLight;
  LeftGreenLight += LeftDeltaGreenLight;
  LeftBlueLight += LeftDeltaBlueLight;

  RightRedLight += RightDeltaRedLight;
  RightGreenLight += RightDeltaGreenLight;
  RightBlueLight += RightDeltaBlueLight;
#endif
}

#undef PERSPECTIVE
#undef COLORED_LIGHTING
#undef MONO_LIGHTING
#undef TEX_INNER_LOOP
#undef LIGHT_INNER_LOOP
