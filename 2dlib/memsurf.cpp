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

#include "bitmap.h"

#include <string.h>
#include <stdlib.h>
#include "mem.h"

//	----------------------------------------------------------------------------
//	constructor and destructor
//	----------------------------------------------------------------------------

grMemorySurface::grMemorySurface() : grSurface() {
  m_FirstTimeInit = 1;
  m_AllowInit = 1;
}

grMemorySurface::grMemorySurface(int w, int h, int bpp, unsigned flags, const char *name)
    : grSurface(w, h, bpp, SURFTYPE_MEMORY, flags, name) {
  m_FirstTimeInit = 0;
  m_AllowInit = 0;
}

grMemorySurface::grMemorySurface(int bm) {
  m_FirstTimeInit = 1;
  m_AllowInit = 1;

  grMemorySurface::init(bm_w(bm, 0), bm_h(bm, 0), bm_bpp(bm), (char *)bm_data(bm, 0), bm_rowsize(bm, 0),
                        SURFFLAG_COLORKEY);
}

grMemorySurface::~grMemorySurface() {
  // this should invoke the grSurface destructor
  // even if we just initialized the surface, the memory routines should know this and
  // do appropriate deinitialization.
}

//	----------------------------------------------------------------------------
//	initialize a memory surface with these values
//	----------------------------------------------------------------------------

bool grMemorySurface::init(int w, int h, int bpp, char *data, int rowsize, unsigned flags, const char *name) {
  ASSERT(m_AllowInit);

  if (m_FirstTimeInit) {
    //	add to list ONLY ONCE!
    add_to_list(&ddsfObj);
    m_FirstTimeInit = 0;
  }

  ddsfObj.w = w;
  ddsfObj.h = h;
  ddsfObj.bpp = bpp;
  ddsfObj.type = SURFTYPE_MEMORY;
  ddsfObj.flags = (ushort)flags;
  if (name)
    strncpy(ddsfObj.name, name, 15);

  if (!gr_mem_surf_Init(&ddsfObj, data, rowsize))
    return 0;

  surf_init(1);

  return true;
}

//	---------------------------------------------------------------------------
//	gr_mem_xxx functions for memory surfaces
//
//	internal functions
//	---------------------------------------------------------------------------

static mem_bitmap grMemSurf_object;

bool gr_bm_mem_Blt16(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh);
bool gr_bm_mem_Blt16ck(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh);

//	---------------------------------------------------------------------------
//	initializes a memory surface by allocating memory based on bit depth

bool gr_mem_surf_Create(ddgr_surface *sf) {
  mem_bitmap *bm;

  bm = new mem_bitmap;

  switch (sf->bpp) {
  case BPP_16:
    bm->bpp = BPP_16;
    bm->rowsize = sf->w * 2;
    bm->alloced = 1;
    break;

  case BPP_32:
    bm->bpp = BPP_32;
    bm->rowsize = sf->w * 4;
    bm->alloced = 1;
    break;

  default:
    Int3();
  }

  bm->data = (char *)mem_malloc(bm->rowsize * sf->h);
  if (!bm->data) {
    mprintf((0, "mem_Create malloc fail <%s>\n", sf->name));
    delete bm;
    return false;
  }

  sf->obj = (void *)bm;

  return true;
}

//	---------------------------------------------------------------------------
//	deallocates memory created in a mem_Create

bool gr_mem_surf_Destroy(ddgr_surface *sf) {
  ASSERT(sf);

  mem_bitmap *bm = (mem_bitmap *)sf->obj;

  //	here, we check if we initialized, or allocated this memory surface.
  if (bm->alloced == 2) {
    delete bm;
    return false;
  } else if (bm->alloced == 0) {
    return false;
  }

  //	otherwise free all objects
  mem_free(bm->data);
  delete bm;

  return true;
}

//	---------------------------------------------------------------------------
//	initializes a memory surface

bool gr_mem_surf_Init(ddgr_surface *sf, char *data, int rowsize) {
  //	initialize a memory surface, with preallocated memory
  mem_bitmap *mbm;

  //	create new memory bitmap object for initialized surface
  if (!sf->obj) {
    mbm = new mem_bitmap;
    mbm->alloced = 2;
  } else {
    mbm = (mem_bitmap *)sf->obj;
    mbm->alloced = 0;
  }

  mbm->data = data;
  mbm->rowsize = rowsize;
  mbm->bpp = (short)sf->bpp;
  mbm->flag = 0;

  sf->obj = (void *)mbm;

  return true;
}

//	---------------------------------------------------------------------------
//	clears a memory surface

void gr_mem_surf_Clear(ddgr_surface *dsf, ddgr_color col, int l, int t, int w, int h) {
  mem_bitmap *dbm = (mem_bitmap *)dsf->obj;

  switch (dbm->bpp) {
  case BPP_16: {
    ushort *sptr;
    ushort scol;

    scol = (ushort)GR_COLOR_TO_16(col);
    sptr = (ushort *)dbm->data + (t * ((dbm->rowsize) >> 1));

    for (int y = t; y < (t + h); y++) {
      for (int x = l; x < (l + w); x++)
        sptr[x] = scol;

      sptr += ((dbm->rowsize) >> 1);
    }
    break;
  }

  case BPP_32:
  default:
    Int3();
  }
}

//	---------------------------------------------------------------------------
//	blts a memory surface to another such surface

bool gr_mem_surf_Blt(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh) {
  //	Maybe we should allow slow 16bpp to 24bpp and vice-versa blts.
  //	for now, we wont.
  mem_bitmap *sbm = (mem_bitmap *)ssf->obj, *dbm = (mem_bitmap *)dsf->obj;

  ASSERT(dbm->bpp == sbm->bpp);

  switch (dbm->bpp) {
  case BPP_16:
    if (ssf->flags & SURFFLAG_COLORKEY)
      gr_bm_mem_Blt16ck(dsf, dx, dy, ssf, sx, sy, sw, sh);
    else
      gr_bm_mem_Blt16(dsf, dx, dy, ssf, sx, sy, sw, sh);
    break;

  case BPP_32:
  default:
    Int3();
  }

  return true;
}

//	---------------------------------------------------------------------------
//	just extracts info from mem_bitmap abstract object

bool gr_mem_surf_Lock(ddgr_surface *sf, void **ptr, int *rowsize) {
  mem_bitmap *bm = (mem_bitmap *)sf->obj;

  *ptr = (char *)bm->data;
  *rowsize = bm->rowsize;

  return true;
}

//	---------------------------------------------------------------------------
//	invalidates sf members

bool gr_mem_surf_Unlock(ddgr_surface *sf, void *ptr) { return true; }

//	---------------------------------------------------------------------------
//	does shit.

bool gr_mem_surf_AttachHandle(ddgr_surface *sf, unsigned handle) { return true; }

//	---------------------------------------------------------------------------
//	performs 16-bit blts.

bool gr_bm_mem_Blt16(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh) {
  mem_bitmap *dbm = (mem_bitmap *)dsf->obj, *sbm = (mem_bitmap *)ssf->obj;
  ushort *dbits;
  ushort *sbits;
  int srowsize_w, drowsize_w, row, col;

  //	set up blt.
  srowsize_w = sbm->rowsize >> 1; // rowsize in shorts
  drowsize_w = dbm->rowsize >> 1;
  dbits = (ushort *)dbm->data + (dy * drowsize_w) + dx;
  sbits = (ushort *)sbm->data + (sy * srowsize_w) + sx;

  for (row = 0; row < sh; row++) {
    for (col = 0; col < sw; col++)
      dbits[col] = sbits[col];
    sbits += srowsize_w;
    dbits += drowsize_w;
  }

  return true;
}

bool gr_bm_mem_Blt16ck(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh) {
  mem_bitmap *dbm = (mem_bitmap *)dsf->obj, *sbm = (mem_bitmap *)ssf->obj;
  ushort *dbits;
  ushort *sbits;
  int srowsize_w, drowsize_w, row, col;

  //	set up blt.
  srowsize_w = sbm->rowsize >> 1; // rowsize in shorts
  drowsize_w = dbm->rowsize >> 1;
  dbits = (ushort *)dbm->data + (dy * drowsize_w) + dx;
  sbits = (ushort *)sbm->data + (sy * srowsize_w) + sx;

  for (row = 0; row < sh; row++) {
    for (col = 0; col < sw; col++) {
      if (sbits[col] & OPAQUE_FLAG16)
        dbits[col] = sbits[col];
    }
    sbits += srowsize_w;
    dbits += drowsize_w;
  }

  return true;
}
