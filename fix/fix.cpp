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

#include <time.h>
#include <stdlib.h>
#include "psrand.h"
// Tables for trig functions
float sincos_table[321]; // 256 entries + 64 sin-only + 1 for interpolation
angle asin_table[257];   // 1 quadrants worth, +1 for interpolation
angle acos_table[257];

#define PI 3.141592654

// Generate the data for the trig tables
void InitMathTables() {
  int i;
  float rad, s, c;

  for (i = 0; i < 321; i++) {
    rad = (float)((double)i / 256.0 * 2 * PI);
    sincos_table[i] = (float)sin(rad);
  }

  for (i = 0; i < 256; i++) {

    s = asin((float)i / 256.0);
    c = acos((float)i / 256.0);

    s = (s / (PI * 2));
    c = (c / (PI * 2));

    asin_table[i] = FloatToFix(s);
    acos_table[i] = FloatToFix(c);
  }

  asin_table[256] = asin_table[255];
  acos_table[256] = acos_table[255];

  //	Initialize a random seed.
  ps_srand(time(NULL));
}

// Returns the sine of the given angle.  Linearly interpolates between two entries in a 256-entry table
float FixSin(angle a) {
  int i, f;
  float s0, s1;

  i = (a >> 8) & 0xff;
  f = a & 0xff;

  s0 = sincos_table[i];
  s1 = sincos_table[i + 1];
  return (float)(s0 + ((s1 - s0) * (double)f / 256.0));
}

// Returns the cosine of the given angle.  Linearly interpolates between two entries in a 256-entry table
float FixCos(angle a) {
  int i, f;
  float c0, c1;

  i = (a >> 8) & 0xff;
  f = a & 0xff;

  c0 = sincos_table[i + 64];
  c1 = sincos_table[i + 64 + 1];
  return (float)(c0 + ((c1 - c0) * (double)f / 256.0));
}

// Returns the sine of the given angle, but does no interpolation
float FixSinFast(angle a) {
  int i;

  i = ((a + 0x80) >> 8) & 0xff;

  return sincos_table[i];
}

// Returns the cosine of the given angle, but does no interpolation
float FixCosFast(angle a) {
  int i;

  i = ((a + 0x80) >> 8) & 0xff;

  return sincos_table[i + 64];
}

// use this instead of:
// for:  (int)floor(x+0.5f) use FloatRound(x)
//       (int)ceil(x-0.5f)  use FloatRound(x)
//       (int)floor(x-0.5f) use FloatRound(x-1.0f)
//       (int)floor(x)      use FloatRound(x-0.5f)
// for values in the range -2048 to 2048

// Set a vector to {0,0,0}
int FloatRound(float x) {
  float nf;
  nf = x + 8390656.0f;
  return ((*((int *)&nf)) & 0x7FFFFF) - 2048;
}

// A fast way to convert floats to fix
fix FloatToFixFast(float x) {

  float nf;
  nf = x * 65536.0f + 8390656.0f;
  return ((*((int *)&nf)) & 0x7FFFFF) - 2048;
}

// Get rid of the "no return value" warnings in the next three functions
#pragma warning(disable : 4035)

// compute inverse sine
angle FixAsin(float v) {
  fix vv;
  int i, f, aa;

  vv = FloatToFix(fabs(v));

  if (vv >= F1_0) // check for out of range
    return 0x4000;

  i = (vv >> 8) & 0xff;
  f = vv & 0xff;

  aa = asin_table[i];
  aa = aa + (((asin_table[i + 1] - aa) * f) >> 8);

  if (v < 0)
    aa = F1_0 - aa;

  return aa;
}

// compute inverse cosine
angle FixAcos(float v) {
  fix vv;
  int i, f, aa;

  vv = FloatToFix(fabs(v));

  if (vv >= F1_0) // check for out of range
    return 0;

  i = (vv >> 8) & 0xff;
  f = vv & 0xff;

  aa = acos_table[i];
  aa = aa + (((acos_table[i + 1] - aa) * f) >> 8);

  if (v < 0)
    aa = 0x8000 - aa;

  return aa;
}

// given cos & sin of an angle, return that angle.
// parms need not be normalized, that is, the ratio of the parms cos/sin must
// equal the ratio of the actual cos & sin for the result angle, but the parms
// need not be the actual cos & sin.
// NOTE: this is different from the standard C atan2, since it is left-handed.
angle FixAtan2(float cos, float sin) {
  float q, m;
  angle t;

  // find smaller of two

  q = (sin * sin) + (cos * cos);

  m = sqrt(q);

  if (m == 0)
    return 0;

  if (fabs(sin) < fabs(cos)) {
    // sin is smaller, use arcsin
    t = FixAsin(sin / m);
    if (cos < 0)
      t = 0x8000 - t;

    return t;
  } else {
    t = FixAcos(cos / m);
    if (sin < 0)
      t = F1_0 - t;

    return t;
  }
}

// Does a ceiling operation on a fixed number
fix FixCeil(fix num) {
  int int_num;
  fix new_num;

  int_num = FixToInt(num);

  if (num & 0xFFFF) {
    new_num = IntToFix(int_num + 1);
    return new_num;
  }

  new_num = IntToFix(int_num);
  return (new_num);
}

// Floors a fixed number
fix FixFloor(fix num) {
  int int_num = FixToInt(num);

  return (IntToFix(int_num));
}
