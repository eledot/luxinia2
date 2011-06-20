// Copyright (C) 2004-2011 Christoph Kubisch
// This file is part of the "Luxinia Engine".
// For conditions of distribution and use, see copyright notice in LICENSE.txt

#ifndef __LUXLUXGFX_PROGRAM_H__
#define __LUXLUXGFX_PROGRAM_H__

#include <luxplatform/luxplatform.h>

#include "glconfig.h"

#ifdef __cplusplus
extern "C"{
#endif

  typedef enum lxgProgramType_e{
    LUXGFX_PROGRAM_NONE,
    LUXGFX_PROGRAM_GLSL,
    LUXGFX_PROGRAM_GLSLSEP,
    LUXGFX_PROGRAM_NV,
  }lxgProgramType_t;

  typedef enum lxgProgramStage_e{
    LUXGFX_STAGE_VERTEX,
    LUXGFX_STAGE_FRAGMENT,
    LUXGFX_STAGE_GEOMETRY,
    LUXGFX_STAGE_TESSCTRL,
    LUXGFX_STAGE_TESSEVAL,
    LUXGFX_STAGES,
  }lxgProgramStage_t;

  typedef void (*lxgParmeterUpdate_fn)(lxgProgramParameterPTR param, lxgContextPTR ctx, void* data);
  typedef uint32 lxgSubroutineKey;

  typedef struct lxgProgramSubroutine_s{
    GLuint              glindex;
    lxgSubroutineKey    namekey;
  }lxgProgramSubroutine_t;

  typedef struct lxgProgramParameter_s{
    lxgParameterType_t    type;
    lxgParmeterUpdate_fn  func;
    union{
      GLuint              glid;         // for SEP
      GLenum              gltarget;     // for NV
      lxgProgramStage_t   domain;       // for subroutines
    };
    GLuint                gllocation;
    union{
      struct {
        ushort            count;
        bool16            transpose;
      } uniform;
      struct{
        int               size;
      } buffer;
      struct{
        lxgProgramSubroutine_t    last;
        int                       numCompatible;
        lxgProgramSubroutine_t*   compatible;
      } subroutine;
      struct{
        uint32            userkey;
        void*             userdata;
      } user;
    };
    
    const char*           name;
  }lxgProgramParameter_t;

  typedef struct lxgStageProgram_s{
    union{
      lxGLShaderType_t    gltype;
      lxGLProgramType_t   gltarget;
    };
    GLuint                glid;
    uint                  numSubroutines;
    lxgContextPTR         ctx;
    lxgProgramType_t      progtype;
  }lxgStageProgram_t;

  typedef struct lxgProgram_s{
    GLuint                glid;
    lxgProgramType_t      type;
    flags32               usedProgs;
    union{
      lxgProgramPTR       sepPrograms[LUXGFX_STAGES];
      lxgStageProgramPTR  stagePrograms[LUXGFX_STAGES];
    };
    booln                 isSeparable;
    lxgContextPTR         ctx;
  }lxgProgram_t;

  typedef struct lxgProgramState_s{
    lxgProgramPTR         current;
    flags32               dirtySubroutines;
    uint                  numSubroutines[LUXGFX_STAGES];
    GLenum                typeSubroutines[LUXGFX_STAGES];
    GLuint                subroutines[LUXGFX_STAGES][LUXGFX_MAX_STAGE_SUBROUTINES];
  }lxgProgramState_t;


  // COMMON
  LUX_API void  lxgProgram_apply( lxgProgramPTR prog, lxgContextPTR ctx);
  LUX_API void  lxgProgram_applyParameters(lxgProgramPTR prog, lxgContextPTR ctx, uint num, lxgProgramParameterPTR *params, void **data);

  // GLSL
    // domain is only important to subroutines
  LUX_API void  lxgProgramParameter_initFunc(lxgProgramParameterPTR param);

  LUX_API void  lxgStageProgram_init(lxgStageProgramPTR stage, lxgContextPTR ctx, lxgProgramStage_t type);
  LUX_API void  lxgStageProgram_deinit(lxgStageProgramPTR stage, lxgContextPTR ctx);
  LUX_API booln lxgStageProgram_compile(lxgStageProgramPTR stage, const char *src, int len);
  LUX_API const char* lxgStageProgram_error(lxgStageProgramPTR stage, char *buffer, int len);

  LUX_API void  lxgProgram_init(lxgProgramPTR prog, lxgContextPTR ctx);
  LUX_API void  lxgProgram_deinit(lxgProgramPTR prog, lxgContextPTR ctx);
  LUX_API void  lxgProgram_setDomain(lxgProgramPTR prog, lxgProgramStage_t type, lxgStageProgramPTR stage);
  LUX_API booln lxgProgram_link(lxgProgramPTR prog);
  LUX_API const char* lxgProgram_log(lxgProgramPTR prog, char* buffer, int len);

  LUX_API int lxgProgram_getParameterCount( lxgProgramPTR prog, int* maxNameLen, int* totalCompatibleSubroutines);
    // namesBuffer[maxNameLen * num]
  LUX_API void lxgProgram_initParameters( lxgProgramPTR prog, int num, lxgProgramParameter_t* params, int maxNameLen, char* namesBuffer);

  // GLSL SEPERATE or DSA
  LUX_API void lxgProgramParameter_initFuncSEP(lxgProgramParameterPTR param, GLuint progid);

  // GLSLSEP
  LUX_API void  lxgProgram_initForSEP( lxgProgramPTR prog, lxgContextPTR ctx);
  LUX_API void  lxgProgram_initSEP( lxgProgramPTR prog, lxgContextPTR ctx);
  LUX_API void  lxgProgram_deinitSEP( lxgProgramPTR prog, lxgContextPTR ctx );
  LUX_API void  lxgProgram_setSEP( lxgProgramPTR prog, lxgProgramPTR stage );
  LUX_API const char* lxgProgram_logSEP( lxgProgramPTR prog, char* buffer, int len);

  // NV/ARB PROGRAM
    // domain is always important
  LUX_API void  lxgProgramParameter_initFuncNV(lxgProgramParameterPTR param, lxgProgramStage_t domain);

  LUX_API void  lxgStageProgram_initNV(lxgStageProgramPTR stage, lxgContextPTR ctx, lxgProgramStage_t type);
  LUX_API void  lxgStageProgram_deinitNV(lxgStageProgramPTR stage, lxgContextPTR ctx);
  LUX_API booln lxgStageProgram_compileNV(lxgStageProgramPTR stage, const char *src, int len);
  LUX_API const char* lxgStageProgram_errorNV(lxgStageProgramPTR stage, char *buffer, int len);

  LUX_API void  lxgProgram_initNV(lxgProgramPTR prog, lxgContextPTR ctx);
  LUX_API void  lxgProgram_deinitNV(lxgProgramPTR prog, lxgContextPTR ctx);
  LUX_API void  lxgProgram_setDomainNV(lxgProgramPTR prog, lxgProgramStage_t type, lxgStageProgramPTR stage);


#ifdef __cplusplus
}


#endif



#endif