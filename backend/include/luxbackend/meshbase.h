// Copyright (C) 2004-2011 Christoph Kubisch
// This file is part of the "Luxinia Engine".
// For conditions of distribution and use, see copyright notice in LICENSE.txt

#ifndef __LUXBACKEND_MESHBASE_H__
#define __LUXBACKEND_MESHBASE_H__

#include <luxplatform/luxplatform.h>
#include <luxmath/basetypes.h>

#if defined(__cplusplus)
extern "C"
{
#endif

  typedef enum lxMeshIndexType_e{
    LUX_MESH_INDEX_UINT16,
    LUX_MESH_INDEX_UINT32,
  }lxMeshIndexType_t;

    // segs = x,y
  LUX_API void lxMeshPlane_getMemsize(int segs[2], int* numVertices, int* numTriangleIndices, int* numOutlineIndices);
  LUX_API void lxMeshPlane_initTriangles(int segs[2], lxVector3* pos, lxVector3* normal, lxVector2* uv, uint32* indices);
  LUX_API void lxMeshPlane_initOutline(int segs[2], uint32* indices);

    // segs = outer (x,y),cap
  LUX_API void lxMeshDisc_getMemsize(int segs[2], int* numVertices, int* numTriangleIndices, int* numOutlineIndices);
  LUX_API void lxMeshDisc_initTriangles(int segs[2], lxVector3* pos, lxVector3* normal, lxVector2* uv, uint32* indices);
  LUX_API void lxMeshDisc_initOutline(int segs[2], uint32* indices);

    // segs = x,y,z
  LUX_API void lxMeshBox_getMemsize(int segs[3], int* numVertices, int* numTriangleIndices, int* numOutlineIndices);
  LUX_API void lxMeshBox_initTriangles(int segs[3], lxVector3* pos, lxVector3* normal, lxVector2* uv, uint32* indices);
  LUX_API void lxMeshBox_initOutline(int segs[3], uint32* indices);

    // segs = x & y,z
  LUX_API void lxMeshSphere_getMemsize(int segs[2], int* numVertices, int* numTriangleIndices, int* numOutlineIndices);
  LUX_API void lxMeshSphere_initTriangles(int segs[2], lxVector3* pos, lxVector3* normal, lxVector2* uv, uint32* indices);
  LUX_API void lxMeshSphere_initOutline(int segs[2], uint32* indices);

    // segs = outer,cap,z
  LUX_API void lxMeshCylinder_getMemsize(int segs[3], int* numVertices, int* numTriangleIndices, int* numOutlineIndices);
  LUX_API void lxMeshCylinder_initTriangles(int segs[3], lxVector3* pos, lxVector3* normal, lxVector2* uv, uint32* indices);
  LUX_API void lxMeshCylinder_initOutline(int segs[3], uint32* indices);


#if defined(__cplusplus)
}
#endif

#endif