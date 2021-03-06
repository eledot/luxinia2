// Copyright (C) 2010-2011 Christoph Kubisch
// This file is part of the "Luxinia Engine".
// See copyright notice in luxplatform.h

#ifndef __LUXLUXGFX_GLCONFIG_H__
#define __LUXLUXGFX_GLCONFIG_H__

#include <luxinia/luxplatform/luxplatform.h>

#include "gfxtypes.h"
#include <gl/glew.h>

#define LUXGFX_VALIDITY     1

#ifdef __cplusplus
extern "C"{
#endif

  enum{
    LUXGFX_MAX_TEXTURE_IMAGES = 32,
    LUXGFX_MAX_RENDERTARGETS =     16,
    LUXGFX_MAX_RWTEXTURE_IMAGES =  8,
    LUXGFX_MAX_STAGE_BUFFERS   =   12,
    LUXGFX_MAX_TEXTURE_MIPMAPS = 16,
    LUXGFX_MAX_VERTEX_STREAMS  = 8,
    LUXGFX_MAX_STAGE_SUBROUTINES = 1024,
  };

  typedef enum lxGLCompareMode_e{
    LUXGL_COMPARE_NEVER = GL_NEVER,
    LUXGL_COMPARE_LESS = GL_LESS,
    LUXGL_COMPARE_EQUAL = GL_EQUAL,
    LUXGL_COMPARE_LEQUAL = GL_LEQUAL,
    LUXGL_COMPARE_GREATER = GL_GREATER,
    LUXGL_COMPARE_NOTEQUAL = GL_NOTEQUAL,
    LUXGL_COMPARE_GEQUAL = GL_GEQUAL,
    LUXGL_COMPARE_ALWAYS = GL_ALWAYS,
    LUXGL_COMPARE_DONTEXECUTE = 0xFFFFFFFFu,
  }lxGLCompareMode_t;

  typedef enum lxGLBufferHint_e{
    LUXGL_STATIC_DRAW  = GL_STATIC_DRAW,
    LUXGL_STATIC_READ  = GL_STATIC_READ,
    LUXGL_STATIC_COPY  = GL_STATIC_COPY,
    LUXGL_DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    LUXGL_DYNAMIC_READ = GL_DYNAMIC_READ,
    LUXGL_DYNAMIC_COPY = GL_DYNAMIC_COPY,
    LUXGL_STREAM_DRAW  = GL_STREAM_DRAW,
    LUXGL_STREAM_READ  = GL_STREAM_READ,
    LUXGL_STREAM_COPY  = GL_STREAM_COPY,
  }lxGLBufferHint_t;

  typedef enum lxGLStencilMode_e{
    LUXGL_STENCIL_KEEP = GL_KEEP,
    LUXGL_STENCIL_ZERO = GL_ZERO,
    LUXGL_STENCIL_REPLACE = GL_REPLACE,
    LUXGL_STENCIL_INCR_SAT = GL_INCR,
    LUXGL_STENCIL_DECR_SAT = GL_DECR,
    LUXGL_STENCIL_INVERT = GL_INVERT,
    LUXGL_STENCIL_INCR = GL_INCR_WRAP,
    LUXGL_STENCIL_DECR = GL_DECR_WRAP,
  }lxGLStencilMode_t;

  typedef enum lxGLBlendWeight_e{
    LUXGL_BLENDW_ZERO = GL_ZERO,
    LUXGL_BLENDW_ONE = GL_ONE,
    LUXGL_BLENDW_RGB_SRC = GL_SRC_COLOR,
    LUXGL_BLENDW_RGB_DST = GL_DST_COLOR,
    LUXGL_BLENDW_A_SRC = GL_SRC_ALPHA,
    LUXGL_BLENDW_A_DST = GL_DST_ALPHA,
    LUXGL_BLENDW_INVRGB_SRC = GL_ONE_MINUS_SRC_COLOR,
    LUXGL_BLENDW_INVRGB_DST = GL_ONE_MINUS_DST_COLOR,
    LUXGL_BLENDW_INVA_SRC = GL_ONE_MINUS_SRC_ALPHA,
    LUXGL_BLENDW_INVA_DST = GL_ONE_MINUS_DST_ALPHA,
    LUXGL_BLENDW_UNKOWN = 0xFFFFABCD,
  }lxGLBlendWeight_t;

  typedef enum lxGLBlendEquation_e{
    LUXGL_BLENDE_ADD = GL_FUNC_ADD,
    LUXGL_BLENDE_SUB = GL_FUNC_SUBTRACT,
    LUXGL_BLENDE_SUB_REV = GL_FUNC_REVERSE_SUBTRACT,
    LUXGL_BLENDE_MIN = GL_MIN,
    LUXGL_BLENDE_MAX = GL_MAX,
    LUXGL_BLENDE_UNKOWN = 0xFFFFABCD,
  }lxGLBlendEquation_t;

  typedef enum lxGLLogicOp_e{
    LUXGL_LOGICOP_CLEAR = GL_CLEAR,
    LUXGL_LOGICOP_SET = GL_SET,
    LUXGL_LOGICOP_COPY = GL_COPY,
    LUXGL_LOGICOP_INVERTED = GL_COPY_INVERTED,
    LUXGL_LOGICOP_NOOP = GL_NOOP,
    LUXGL_LOGICOP_INVERT = GL_INVERT,
    LUXGL_LOGICOP_AND = GL_AND,
    LUXGL_LOGICOP_NAND = GL_NAND,
    LUXGL_LOGICOP_OR = GL_OR,
    LUXGL_LOGICOP_NOR = GL_NOR,
    LUXGL_LOGICOP_XOR = GL_XOR,
    LUXGL_LOGICOP_EQUIV = GL_EQUIV,
    LUXGL_LOGICOP_AND_REVERSE = GL_AND_REVERSE,
    LUXGL_LOGICOP_AND_INVERTED = GL_AND_INVERTED,
    LUXGL_LOGICOP_OR_REVERSE = GL_OR_REVERSE,
    LUXGL_LOGICOP_OR_INVERTED = GL_OR_INVERTED,
    LUXGL_LOGICOP_ILLEGAL = 0,
  }lxGLLogicOp_t;

  typedef enum lxGLPrimitiveType_e{
    LUXGL_POINTS = GL_POINTS,
    LUXGL_TRIANGLES = GL_TRIANGLES,
    LUXGL_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    LUXGL_TRIANGLE_FAN = GL_TRIANGLE_FAN,
    LUXGL_LINES = GL_LINES,
    LUXGL_LINE_LOOP = GL_LINE_LOOP,
    LUXGL_LINE_STRIP = GL_LINE_STRIP,
    LUXGL_QUADS = GL_QUADS,
    LUXGL_QUAD_STRIP = GL_QUAD_STRIP,
    LUXGL_LINE_ADJ = GL_LINES_ADJACENCY,
    LUXGL_LINE_STRIP_ADJ = GL_LINE_STRIP_ADJACENCY,
    LUXGL_TRIANGLE_STRIP_ADJ = GL_TRIANGLE_STRIP_ADJACENCY,
    LUXGL_TRIANGLE_ADJ = GL_TRIANGLES_ADJACENCY,
    LUXGL_PATCHES = GL_PATCHES,
    LUXGL_POLYGON = GL_POLYGON,
  }lxGLPrimitiveType_t;

  typedef enum  lxGLTextureTarget_e{
    LUXGL_TEXTURE_1D = GL_TEXTURE_1D,
    LUXGL_TEXTURE_2D = GL_TEXTURE_2D,
    LUXGL_TEXTURE_3D = GL_TEXTURE_3D,
    LUXGL_TEXTURE_RECT = GL_TEXTURE_RECTANGLE,
    LUXGL_TEXTURE_1DARRAY = GL_TEXTURE_1D_ARRAY,
    LUXGL_TEXTURE_2DARRAY = GL_TEXTURE_2D_ARRAY,
    LUXGL_TEXTURE_CUBE = GL_TEXTURE_CUBE_MAP,
    LUXGL_TEXTURE_CUBEARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
    LUXGL_TEXTURE_2DMS = GL_TEXTURE_2D_MULTISAMPLE,
    LUXGL_TEXTURE_2DMSARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
    LUXGL_TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
    LUXGL_TEXTURE_RENDERBUFFER = GL_TEXTURE_RENDERBUFFER_NV,
    LUXGL_TEXTURE_INVALID = 0,
  }lxGLTextureTarget_t;

  typedef enum lxGLBufferTarget_e{
    LUXGL_BUFFER_VERTEX = GL_ARRAY_BUFFER,
    LUXGL_BUFFER_INDEX = GL_ELEMENT_ARRAY_BUFFER,
    LUXGL_BUFFER_PIXELWRITE = GL_PIXEL_PACK_BUFFER,
    LUXGL_BUFFER_PIXELREAD = GL_PIXEL_UNPACK_BUFFER,
    LUXGL_BUFFER_UNIFORM = GL_UNIFORM_BUFFER,
    LUXGL_BUFFER_TEXTURE = GL_TEXTURE_BUFFER,
    LUXGL_BUFFER_FEEDBACK = GL_TRANSFORM_FEEDBACK_BUFFER,
    LUXGL_BUFFER_CPYWRITE = GL_COPY_WRITE_BUFFER,
    LUXGL_BUFFER_CPYREAD = GL_COPY_READ_BUFFER,
    LUXGL_BUFFER_DRAWINDIRECT = GL_DRAW_INDIRECT_BUFFER,
    LUXGL_BUFFER_NVVIDEO = 0x9020, //FIXME GL_VIDEO_BUFFER_NV;
    LUXGL_BUFFER_NVPARAM_VERTEX = GL_VERTEX_PROGRAM_PARAMETER_BUFFER_NV,
    LUXGL_BUFFER_NVPARAM_GEOMETRY = GL_GEOMETRY_PROGRAM_PARAMETER_BUFFER_NV,
    LUXGL_BUFFER_NVPARAM_FRAGMENT = GL_FRAGMENT_PROGRAM_PARAMETER_BUFFER_NV,
    LUXGL_BUFFER_NVPARAM_TESSCTRL = GL_TESS_CONTROL_PROGRAM_PARAMETER_BUFFER_NV,
    LUXGL_BUFFER_NVPARAM_TESSEVAL = GL_TESS_EVALUATION_PROGRAM_PARAMETER_BUFFER_NV,
    LUXGL_BUFFER_INVALID = 0,
  }lxGLBufferTarget_t;

  typedef enum lxGLShaderType_e{
    LUXGL_SHADER_VERTEX = GL_VERTEX_SHADER,
    LUXGL_SHADER_FRAGMENT = GL_FRAGMENT_SHADER,
    LUXGL_SHADER_GEOMETRY = GL_GEOMETRY_SHADER,
    LUXGL_SHADER_TESSCTRL = GL_TESS_CONTROL_SHADER,
    LUXGL_SHADER_TESSEVAL = GL_TESS_EVALUATION_SHADER,
  }lxGLShaderType_t;

  typedef enum lxGLProgramType_e{
    LUXGL_PROGRAM_VERTEX = GL_VERTEX_PROGRAM_ARB,
    LUXGL_PROGRAM_FRAGMENT = GL_FRAGMENT_PROGRAM_ARB,
    LUXGL_PROGRAM_GEOMETRY = GL_GEOMETRY_PROGRAM_NV,
    LUXGL_PROGRAM_TESSCTRL = GL_TESS_CONTROL_PROGRAM_NV,
    LUXGL_PROGRAM_TESSEVAL = GL_TESS_EVALUATION_PROGRAM_NV,
  }lxGLProgramType_t;

  typedef enum lxGLAccessFormat_e{
    LUXGL_ACCESSFORMAT_R8UI     = GL_R8UI,
    LUXGL_ACCESSFORMAT_R8I      = GL_R8I,

    LUXGL_ACCESSFORMAT_R16UI    = GL_R16UI,
    LUXGL_ACCESSFORMAT_R16I     = GL_R16I,

    LUXGL_ACCESSFORMAT_R32UI    = GL_R32UI,
    LUXGL_ACCESSFORMAT_R32I     = GL_R32I,
    LUXGL_ACCESSFORMAT_R32F     = GL_R32F,

    LUXGL_ACCESSFORMAT_RG32UI   = GL_RG32UI,
    LUXGL_ACCESSFORMAT_RG32I    = GL_RG32I,
    LUXGL_ACCESSFORMAT_RG32F    = GL_RG32F,

    LUXGL_ACCESSFORMAT_RGBA32UI = GL_RGBA32UI,
    LUXGL_ACCESSFORMAT_RGBA32I  = GL_RGBA32I,
    LUXGL_ACCESSFORMAT_RGBA32F  = GL_RGBA32F,
  }lxGLAccessFormat_t;

  typedef enum lxGLAccessMode_e{
    LUXGL_ACCESS_READ_ONLY = GL_READ_ONLY,
    LUXGL_ACCESS_WRITE_ONLY = GL_WRITE_ONLY,
    LUXGL_ACCESS_READ_WRITE = GL_READ_WRITE,
  }lxGLAccessMode_t;

  typedef enum lxGLParameterType_e{
    LUXGL_PARAM_FLOAT = GL_FLOAT,
    LUXGL_PARAM_FLOAT2 = GL_FLOAT_VEC2,
    LUXGL_PARAM_FLOAT3 = GL_FLOAT_VEC3,
    LUXGL_PARAM_FLOAT4 = GL_FLOAT_VEC4,
    LUXGL_PARAM_INT = GL_INT,
    LUXGL_PARAM_INT2 = GL_INT_VEC2,
    LUXGL_PARAM_INT3 = GL_INT_VEC3,
    LUXGL_PARAM_INT4 = GL_INT_VEC4,
    LUXGL_PARAM_UINT = GL_UNSIGNED_INT,
    LUXGL_PARAM_UINT2 = GL_UNSIGNED_INT_VEC2,
    LUXGL_PARAM_UINT3 = GL_UNSIGNED_INT_VEC3,
    LUXGL_PARAM_UINT4 = GL_UNSIGNED_INT_VEC4,
    LUXGL_PARAM_BOOL = GL_BOOL,
    LUXGL_PARAM_BOOL2 = GL_BOOL_VEC2,
    LUXGL_PARAM_BOOL3 = GL_BOOL_VEC3,
    LUXGL_PARAM_BOOL4 = GL_BOOL_VEC4,
    LUXGL_PARAM_MAT2 = GL_FLOAT_MAT2,
    LUXGL_PARAM_MAT3 = GL_FLOAT_MAT3,
    LUXGL_PARAM_MAT4 = GL_FLOAT_MAT4,
    LUXGL_PARAM_MAT2x3 = GL_FLOAT_MAT2x3,
    LUXGL_PARAM_MAT2x4 = GL_FLOAT_MAT2x4,
    LUXGL_PARAM_MAT3x2 = GL_FLOAT_MAT3x2,
    LUXGL_PARAM_MAT3x4 = GL_FLOAT_MAT3x4,
    LUXGL_PARAM_MAT4x2 = GL_FLOAT_MAT4x2,
    LUXGL_PARAM_MAT4x3 = GL_FLOAT_MAT4x3,

    LUXGL_PARAM_SAMPLER_1D = GL_SAMPLER_1D,
    LUXGL_PARAM_SAMPLER_2D = GL_SAMPLER_2D,
    LUXGL_PARAM_SAMPLER_3D = GL_SAMPLER_3D,
    LUXGL_PARAM_SAMPLER_CUBE = GL_SAMPLER_CUBE,
    LUXGL_PARAM_SAMPLER_2DRECT = GL_SAMPLER_2D_RECT,
    LUXGL_PARAM_SAMPLER_2DMS = GL_SAMPLER_2D_MULTISAMPLE,
    LUXGL_PARAM_SAMPLER_1DARRAY = GL_SAMPLER_1D_ARRAY,
    LUXGL_PARAM_SAMPLER_2DARRAY = GL_SAMPLER_2D_ARRAY,
    LUXGL_PARAM_SAMPLER_CUBEARRAY = GL_SAMPLER_CUBE_MAP_ARRAY,
    LUXGL_PARAM_SAMPLER_2DMSARRAY = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
    LUXGL_PARAM_SAMPLER_BUFFER = GL_SAMPLER_BUFFER,

    LUXGL_PARAM_ISAMPLER_1D = GL_INT_SAMPLER_1D,
    LUXGL_PARAM_ISAMPLER_2D = GL_INT_SAMPLER_2D,
    LUXGL_PARAM_ISAMPLER_3D = GL_INT_SAMPLER_3D,
    LUXGL_PARAM_ISAMPLER_CUBE = GL_INT_SAMPLER_CUBE,
    LUXGL_PARAM_ISAMPLER_2DRECT = GL_INT_SAMPLER_2D_RECT,
    LUXGL_PARAM_ISAMPLER_2DMS = GL_INT_SAMPLER_2D_MULTISAMPLE,
    LUXGL_PARAM_ISAMPLER_1DARRAY = GL_INT_SAMPLER_1D_ARRAY,
    LUXGL_PARAM_ISAMPLER_2DARRAY = GL_INT_SAMPLER_2D_ARRAY,
    LUXGL_PARAM_ISAMPLER_CUBEARRAY = GL_INT_SAMPLER_CUBE_MAP_ARRAY,
    LUXGL_PARAM_ISAMPLER_2DMSARRAY = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
    LUXGL_PARAM_ISAMPLER_BUFFER = GL_INT_SAMPLER_BUFFER,

    LUXGL_PARAM_USAMPLER_1D = GL_UNSIGNED_INT_SAMPLER_1D,
    LUXGL_PARAM_USAMPLER_2D = GL_UNSIGNED_INT_SAMPLER_2D,
    LUXGL_PARAM_USAMPLER_3D = GL_UNSIGNED_INT_SAMPLER_3D,
    LUXGL_PARAM_USAMPLER_CUBE = GL_UNSIGNED_INT_SAMPLER_CUBE,
    LUXGL_PARAM_USAMPLER_2DRECT = GL_UNSIGNED_INT_SAMPLER_2D_RECT,
    LUXGL_PARAM_USAMPLER_2DMS = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
    LUXGL_PARAM_USAMPLER_1DARRAY = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
    LUXGL_PARAM_USAMPLER_2DARRAY = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
    LUXGL_PARAM_USAMPLER_CUBEARRAY = GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY,
    LUXGL_PARAM_USAMPLER_2DMSARRAY = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
    LUXGL_PARAM_USAMPLER_BUFFER = GL_UNSIGNED_INT_SAMPLER_BUFFER,

    LUXGL_PARAM_SAMPLER_1D_SHADOW = GL_SAMPLER_1D_SHADOW,
    LUXGL_PARAM_SAMPLER_2D_SHADOW = GL_SAMPLER_2D_SHADOW,
    LUXGL_PARAM_SAMPLER_CUBE_SHADOW = GL_SAMPLER_CUBE_SHADOW,
    LUXGL_PARAM_SAMPLER_2DRECT_SHADOW = GL_SAMPLER_2D_RECT_SHADOW,
    LUXGL_PARAM_SAMPLER_1DARRAY_SHADOW = GL_SAMPLER_1D_ARRAY_SHADOW,
    LUXGL_PARAM_SAMPLER_2DARRAY_SHADOW = GL_SAMPLER_2D_ARRAY_SHADOW,
    LUXGL_PARAM_SAMPLER_CUBEARRAY_SHADOW = GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW,

    LUXGL_PARAM_IMAGE_1D = GL_IMAGE_1D_EXT,
    LUXGL_PARAM_IMAGE_2D = GL_IMAGE_2D_EXT,
    LUXGL_PARAM_IMAGE_3D = GL_IMAGE_3D_EXT,
    LUXGL_PARAM_IMAGE_CUBE = GL_IMAGE_CUBE_EXT,
    LUXGL_PARAM_IMAGE_2DRECT = GL_IMAGE_2D_RECT_EXT,
    LUXGL_PARAM_IMAGE_2DMS = GL_IMAGE_2D_MULTISAMPLE_EXT,
    LUXGL_PARAM_IMAGE_1DARRAY = GL_IMAGE_1D_ARRAY_EXT,
    LUXGL_PARAM_IMAGE_2DARRAY = GL_IMAGE_2D_ARRAY_EXT,
    LUXGL_PARAM_IMAGE_CUBEARRAY = GL_IMAGE_CUBE_MAP_ARRAY_EXT,
    LUXGL_PARAM_IMAGE_2DMSARRAY = GL_IMAGE_2D_MULTISAMPLE_ARRAY_EXT,
    LUXGL_PARAM_IMAGE_BUFFER = GL_IMAGE_BUFFER_EXT,

    LUXGL_PARAM_IIMAGE_1D = GL_INT_IMAGE_1D_EXT,
    LUXGL_PARAM_IIMAGE_2D = GL_INT_IMAGE_2D_EXT,
    LUXGL_PARAM_IIMAGE_3D = GL_INT_IMAGE_3D_EXT,
    LUXGL_PARAM_IIMAGE_CUBE = GL_INT_IMAGE_CUBE_EXT,
    LUXGL_PARAM_IIMAGE_2DRECT = GL_INT_IMAGE_2D_RECT_EXT,
    LUXGL_PARAM_IIMAGE_2DMS = GL_INT_IMAGE_2D_MULTISAMPLE_EXT,
    LUXGL_PARAM_IIMAGE_1DARRAY = GL_INT_IMAGE_1D_ARRAY_EXT,
    LUXGL_PARAM_IIMAGE_2DARRAY = GL_INT_IMAGE_2D_ARRAY_EXT,
    LUXGL_PARAM_IIMAGE_CUBEARRAY = GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT,
    LUXGL_PARAM_IIMAGE_2DMSARRAY = GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY_EXT,
    LUXGL_PARAM_IIMAGE_BUFFER = GL_INT_IMAGE_BUFFER_EXT,

    LUXGL_PARAM_UIMAGE_1D = GL_UNSIGNED_INT_IMAGE_1D_EXT,
    LUXGL_PARAM_UIMAGE_2D = GL_UNSIGNED_INT_IMAGE_2D_EXT,
    LUXGL_PARAM_UIMAGE_3D = GL_UNSIGNED_INT_IMAGE_3D_EXT,
    LUXGL_PARAM_UIMAGE_CUBE = GL_UNSIGNED_INT_IMAGE_CUBE_EXT,
    LUXGL_PARAM_UIMAGE_2DRECT = GL_UNSIGNED_INT_IMAGE_2D_RECT_EXT,
    LUXGL_PARAM_UIMAGE_2DMS = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_EXT,
    LUXGL_PARAM_UIMAGE_1DARRAY = GL_UNSIGNED_INT_IMAGE_1D_ARRAY_EXT,
    LUXGL_PARAM_UIMAGE_2DARRAY = GL_UNSIGNED_INT_IMAGE_2D_ARRAY_EXT,
    LUXGL_PARAM_UIMAGE_CUBEARRAY = GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT,
    LUXGL_PARAM_UIMAGE_2DMSARRAY = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY_EXT,
    LUXGL_PARAM_UIMAGE_BUFFER = GL_UNSIGNED_INT_IMAGE_BUFFER_EXT,

    LUXGL_PARAM_GPU_ADDRESS     = GL_GPU_ADDRESS_NV,
    LUXGL_PARAM_BUFFER          = 0x7FFFFFF0,
    LUXGL_PARAM_SUBROUTINE     = 0x7FFFFFF1,
    LUXGL_PARAM_USER            = 0x7FFFFFFF,
  }lxGLParameterType_t;

  typedef enum lxGLError_e{
    LUXGL_ERROR_NONE = GL_NO_ERROR,
    LUXGL_ERROR_OP = GL_INVALID_OPERATION,
    LUXGL_ERROR_ENUM = GL_INVALID_ENUM,
    LUXGL_ERROR_VALUE = GL_INVALID_VALUE,
    LUXGL_ERROR_INDEX = GL_INVALID_INDEX,
    LUXGL_ERROR_FBOP = GL_INVALID_FRAMEBUFFER_OPERATION,
  }lxGLError_t;


#ifdef _DEBUG
  LUX_INLINE void lxGLErrorCheck(){
    lxGLError_t err;
    while (err = (lxGLError_t)glGetError()){
      err = err;
    }
  }
#else
  #define lxGLErrorCheck  LUX_NOOP
#endif

  
#ifdef __cplusplus
}
#endif

#endif
