// Copyright (C) 2004-2011 Christoph Kubisch
// This file is part of the "Luxinia Engine".
// See copyright notice in luxplatform.h
//
// Forwards to Code by Martin Storsj�, Ignacio Castanio, Tom Forsyth

#ifndef __LUXBACKEND_MESHVCACHEOPT_H__
#define __LUXBACKEND_MESHVCACHEOPT_H__

#include <luxplatform/luxplatform.h>
#include <luxbackend/meshbase.h>

#if defined(__cplusplus)
extern "C"
{
#endif

//////////////////////////////////////////////////////////////////////////
// Vertex Cache Optimizations


// Original Algorithm:
// http://www.cs.princeton.edu/gfx/pubs/Sander_2007_%3ETR/tipsy.pdf
LUX_API void* lxVertexCacheOptimize_tipsify(
  void* indices,
  int nTriangles,
  int nVertices,
  int k,
  lxMeshIndexType_t type );


// Original Algorithm:
// http://home.comcast.net/~tom_forsyth/papers/fast_vert_cache_opt.html
//
// NOT THREADSAFE!!
// vcachesize <= 32
LUX_API void* lxVertexCacheOptimize_forsyth(
  void* indices,
  int nTriangles,
  int nVertices,
  int vcache,
  lxMeshIndexType_t type );


// Optimal Grid VertexCache, by Igancio Castano
// http://castano.ludicon.com/blog/2009/02/02/optimal-grid-rendering
//
// if buffer was too small, NULL
// is returned
LUX_API void* lxVertexCacheOptimize_grid_castano(
  void* indices,
  int maxTriangles,
  int width,
  int height,
  int vcache,
  lxMeshIndexType_t type,
  int *writtenTriangles);

#if defined(__cplusplus)
}
#endif

#endif
