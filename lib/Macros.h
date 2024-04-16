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

#ifndef _MACROS_H
#define _MACROS_H
#define SWAP(a, b)                                                                                                     \
  do {                                                                                                                 \
    int _swap_var_ = (a);                                                                                              \
    (a) = (b);                                                                                                         \
    (b) = _swap_var_;                                                                                                  \
  } while (0)
#define SET_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define CHECK_FLAG(_var, _flag) ((_var) & (_flag))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define makeword(_h, _l) (((_h) << 16) + ((_l)&0xffff))
#define hiword(_v) ((_v) >> 16)
#define loword(_v) ((_v)&0x0000ffff)
#define makeshort(_h, _l) (((_h) << 8) + ((_l)&0x00ff))
#define hibyte(_w) ((_w) >> 8)
#define lobyte(_w) ((_w)&0x00ff)
#define kb_to_bytes(_kb) ((_kb)*1024)
#define _min(a, b) min(a, b)
#define _max(a, b) max(a, b)
#define ABS(a) ((a < 0) ? (-a) : (a))

#ifndef WIN32
#define __min(a, b) min(a, b)
#define __max(a, b) max(a, b)
#endif
#endif
