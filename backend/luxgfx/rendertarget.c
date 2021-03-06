// Copyright (C) 2010-2011 Christoph Kubisch
// This file is part of the "Luxinia Engine".
// See copyright notice in luxplatform.h

#include <luxinia/luxgfx/texture.h>
#include <luxinia/luxgfx/luxgfx.h>
#include <luxinia/luxplatform/debug.h>
#include <luxinia/luxmath/misc.h>
#include <luxinia/luxcore/scalarmisc.h>

#include "state_inl.h"


LUX_API void lxgRenderTarget_init(lxgRenderTargetPTR rt, lxgContextPTR ctx )
{
  memset(rt,0,sizeof(lxgRenderTarget_t));

  rt->ctx = ctx;

  glGenFramebuffers(1,&rt->glid);
}

LUX_API void lxgRenderTarget_deinit( lxgRenderTargetPTR rt, lxgContextPTR ctx )
{
  glDeleteFramebuffers(1,&rt->glid);
}

LUX_API void lxgRenderTarget_resetAssigns(lxgRenderTargetPTR rt)
{
  rt->dirty = LUX_TRUE;

}



static LUX_INLINE void lxgRenderTarget_applyAssign(GLenum target, GLenum what,lxgRenderAssignCPTR assign)
{
  if (assign->tex){
    lxgTextureCPTR tex = assign->tex;
	switch (tex->gltarget){
    case LUXGL_TEXTURE_1D:
      glFramebufferTexture1DEXT(target,what,GL_TEXTURE_1D,tex->glid,assign->mip);
      return;
    case LUXGL_TEXTURE_2D:
    case LUXGL_TEXTURE_RECT:
      glFramebufferTexture2DEXT(target,what,tex->gltarget,tex->glid,assign->mip);
      return;
    case LUXGL_TEXTURE_3D:
      if (assign->layer == -1){
        glFramebufferTextureEXT(target,what,tex->glid,assign->mip);
      }
      else{
        glFramebufferTexture3DEXT(target,what,GL_TEXTURE_3D,tex->glid,assign->mip,assign->layer);
      }
      return;
    case LUXGL_TEXTURE_CUBE:
      if (assign->layer == -1){
        glFramebufferTextureEXT(target,what,tex->glid,assign->mip);
      }
      else{
        glFramebufferTextureFaceEXT(target, what, tex->glid,assign->mip, GL_TEXTURE_CUBE_MAP_POSITIVE_X + assign->layer);
      }
      return;
    case LUXGL_TEXTURE_2DMS:
      glFramebufferTexture2DEXT(target, what, tex->gltarget,tex->glid,assign->mip);
      return;
    case LUXGL_TEXTURE_1DARRAY:
    case LUXGL_TEXTURE_2DARRAY:
    case LUXGL_TEXTURE_CUBEARRAY:
    case LUXGL_TEXTURE_2DMSARRAY:
      if (assign->layer == -1){
        glFramebufferTextureEXT(target,what,tex->glid,assign->mip);
      }
      else{
        glFramebufferTextureLayerEXT(target, what, tex->glid,assign->mip,assign->layer);
      }
      return;
    }
  }
  else if (assign->rbuf){
    glFramebufferRenderbufferEXT(target,what,GL_RENDERBUFFER,assign->rbuf->glid);
  }
  else{
    glFramebufferTexture2DEXT(target,what,GL_TEXTURE_2D,0,0);
    glFramebufferRenderbufferEXT(target,what,GL_RENDERBUFFER,0);
  }
}

static LUX_INLINE void lxgRenderTarget_applyNamedAssign(lxgRenderTargetPTR rt, GLenum what,lxgRenderAssignCPTR assign)
{
  GLuint target = rt->glid;

  if (assign->tex){
    lxgTextureCPTR tex = assign->tex;
    switch (tex->gltarget){
    case LUXGL_TEXTURE_1D:
      glNamedFramebufferTexture1DEXT(target,what,GL_TEXTURE_1D,tex->glid,assign->mip);
      return;
    case LUXGL_TEXTURE_2D:
    case LUXGL_TEXTURE_RECT:
      glNamedFramebufferTexture2DEXT(target,what,tex->gltarget,tex->glid,assign->mip);
      return;
    case LUXGL_TEXTURE_3D:
      if (assign->layer == -1){
        glNamedFramebufferTextureEXT(target,what,tex->glid,assign->mip);
      }
      else{
        glNamedFramebufferTexture3DEXT(target,what,GL_TEXTURE_3D,tex->glid,assign->mip,assign->layer);
      }
      return;
    case LUXGL_TEXTURE_CUBE:
      if (assign->layer == -1){
        glNamedFramebufferTextureEXT(target,what,tex->glid,assign->mip);
      }
      else{
        glNamedFramebufferTextureFaceEXT(target, what, tex->glid,assign->mip, GL_TEXTURE_CUBE_MAP_POSITIVE_X + assign->layer);
      }
      return;
    case LUXGL_TEXTURE_2DMS:
      glNamedFramebufferTexture2DEXT(target, what, tex->gltarget,tex->glid,assign->mip);
      return;
    case LUXGL_TEXTURE_1DARRAY:
    case LUXGL_TEXTURE_2DARRAY:
    case LUXGL_TEXTURE_CUBEARRAY:
    case LUXGL_TEXTURE_2DMSARRAY:
      if (assign->layer == -1){
        glNamedFramebufferTextureEXT(target,what,tex->glid,assign->mip);
      }
      else{
        glNamedFramebufferTextureLayerEXT(target, what, tex->glid,assign->mip,assign->layer);
      }
      return;
    }
  }
  else if (assign->rbuf){
    glNamedFramebufferRenderbufferEXT(target,what,GL_RENDERBUFFER,assign->rbuf->glid);
  }
  else{
    glNamedFramebufferTexture2DEXT(target,what,GL_TEXTURE_2D,0,0);
    glNamedFramebufferRenderbufferEXT(target,what,GL_RENDERBUFFER,0);
  }
}

static const GLenum l_FBOmode[]={
  GL_DRAW_FRAMEBUFFER_EXT,
  GL_READ_FRAMEBUFFER_EXT,
};

static const GLenum l_FBOAssigns[LUXGFX_RENDERASSIGNS]= { 
  GL_DEPTH_ATTACHMENT_EXT,
  GL_STENCIL_ATTACHMENT_EXT,
  GL_COLOR_ATTACHMENT0_EXT,
  GL_COLOR_ATTACHMENT1_EXT,
  GL_COLOR_ATTACHMENT2_EXT,
  GL_COLOR_ATTACHMENT3_EXT,
  GL_COLOR_ATTACHMENT4_EXT,
  GL_COLOR_ATTACHMENT5_EXT,
  GL_COLOR_ATTACHMENT6_EXT,
  GL_COLOR_ATTACHMENT7_EXT,
  GL_COLOR_ATTACHMENT8_EXT,
  GL_COLOR_ATTACHMENT9_EXT,
  GL_COLOR_ATTACHMENT10_EXT,
  GL_COLOR_ATTACHMENT11_EXT,
  GL_COLOR_ATTACHMENT12_EXT,
  GL_COLOR_ATTACHMENT13_EXT,
  GL_COLOR_ATTACHMENT14_EXT,
  GL_COLOR_ATTACHMENT15_EXT,
};

LUX_API LUX_INLINE void lxgRenderTarget_applyAssigns(lxgRenderTargetPTR rt, lxgRenderTargetType_t mode)
{
  GLenum target = l_FBOmode[mode];
  uint i;

  if (!rt->dirty)
    return;

  LUX_DEBUGASSERT(mode < LUXGFX_RENDERTARGETS);

  for (i = 0; i < rt->maxidx; i++){
    if (rt->dirty & (1<<i)){
      lxgRenderTarget_applyAssign(target,l_FBOAssigns[i],&rt->assigns[i]);
    }
  }
  rt->maxidx = 0;
}

LUX_API LUX_INLINE void  lxgContext_applyRenderTarget( lxgContextPTR ctx, lxgRenderTargetPTR rt, lxgRenderTargetType_t mode )
{
  GLenum target = l_FBOmode[mode];
  glBindFramebuffer(target,rt ? rt->glid : 0);

  ctx->rendertargets[mode] = rt;
  if (mode == LUXGFX_RENDERTARGET_DRAW){
    ctx->framebounds = rt ? rt->bounds : ctx->window;
  }
  if (rt && rt->dirty){
    lxgRenderTarget_applyAssigns(rt,mode);
  }
}

LUX_API void  lxgContext_applyRenderTargetDraw( lxgContextPTR ctx, lxgRenderTargetPTR rt, booln setViewport)
{
  lxgContext_applyRenderTarget(ctx, rt,LUXGFX_RENDERTARGET_DRAW);
  if (setViewport){
    lxRectanglei_t rect = {0,0,ctx->framebounds.width,ctx->framebounds.height};
    lxgContext_applyViewPortRect(ctx, &rect);
  }
}

LUX_API void lxgRenderTarget_applyBlit( lxgContextPTR ctx, lxgRenderTargetPTR to, lxgRenderTargetPTR from, lxgRenderTargetBlitPTR update, flags32 mask, booln linearFilter)
{
  lxgContext_checkedRenderTarget(ctx, to,LUXGFX_RENDERTARGET_DRAW);
  lxgContext_checkedRenderTarget(ctx, from,LUXGFX_RENDERTARGET_READ);
  glBlitFramebuffer(
    update->fromStart.x,  update->fromStart.y,  update->fromEnd.x,  update->fromEnd.y,
    update->toStart.x,    update->toStart.y,    update->toEnd.x,    update->toEnd.y, mask, linearFilter ? GL_LINEAR : GL_NEAREST);
}

LUX_API void lxgRenderTarget_setAssign(lxgRenderTargetPTR rt, lxgRenderAssignType_t idx,lxgRenderAssignCPTR assign)
{
  LUX_DEBUGASSERT(idx < LUXGFX_RENDERASSIGNS);
  if (memcmp(&rt->assigns[idx],assign,sizeof(lxgRenderAssign_t)) == 0) return;
  rt->assigns[idx] = *assign;
  rt->dirty |= (1<<idx);
  rt->maxidx = LUX_MAX(rt->maxidx,(uint)idx);
}

LUX_API booln lxgRenderTarget_checkSize(lxgRenderTargetPTR rt)
{
  uint i;
  int width = 0;
  int height = 0;
  booln cmp = LUX_FALSE;

  rt->bounds.width = 0;
  rt->bounds.height = 0;
  rt->equalsized = LUX_TRUE;

  for (i = 0; i < LUXGFX_RENDERASSIGNS; i++){
    lxgRenderAssign_t*assign = &rt->assigns[i];
    if (assign->tex){
      lxVec3i_t vec = *lxgTexture_getMipSize(assign->tex,assign->mip);
      width  = vec.x;
      height = vec.y;
    }
    else if (assign->rbuf){
      width = assign->rbuf->width;
      height = assign->rbuf->height;
    }
    if (!cmp){
      rt->bounds.width = width;
      rt->bounds.height = height;
      cmp = LUX_TRUE;
    }
    else if (rt->bounds.width != width || rt->bounds.height != height){
      rt->bounds.width  = LUX_MIN(rt->bounds.width, width);
      rt->bounds.height = LUX_MIN(rt->bounds.height,height);
      rt->equalsized = LUX_FALSE;
    }
  }
  return rt->equalsized;
}



//////////////////////////////////////////////////////////////////////////
// lxgViewPort


LUX_API void lxgViewPort_sync(lxgViewPortPTR view, lxgContextPTR ctx)
{
  glGetIntegerv(GL_VIEWPORT,&view->viewRect.x);
  glGetDoublev(GL_DEPTH_RANGE,&view->depth.near);
  view->scissor = glIsEnabled(GL_SCISSOR_TEST);
  glGetIntegerv(GL_SCISSOR_BOX,&view->scissorRect.x);
}

LUX_API booln lxgContext_applyViewPortRect(lxgContextPTR ctx, lxRectangleiCPTR viewRect)
{
  glViewport(LUX_ARRAY4UNPACK(&viewRect->x));
  ctx->viewport.viewRect = *viewRect;
  
  if (!ctx->viewport.scissor && !(
    viewRect->x == 0 && 
    viewRect->y == 0 &&
    viewRect->width  == ctx->framebounds.width &&
    viewRect->height == ctx->framebounds.height))
  {
    glEnable(GL_SCISSOR_TEST);
    glScissor(LUX_ARRAY4UNPACK(&viewRect->x));
    return LUX_TRUE;
  }
  else{
    return LUX_FALSE;
  }
  
}

LUX_API booln lxgContext_applyViewPortScissorState(lxgContextPTR ctx, booln state)
{
  booln retstate = state;
  if(state){
    glEnable(GL_SCISSOR_TEST);
  }
  else if (!(
    ctx->viewport.viewRect.x == 0 && 
    ctx->viewport.viewRect.y == 0 &&
    ctx->viewport.viewRect.width  == ctx->framebounds.width &&
    ctx->viewport.viewRect.height == ctx->framebounds.height))
  {
    glEnable(GL_SCISSOR_TEST);
    glScissor(LUX_ARRAY4UNPACK(&ctx->viewport.viewRect.x));
    retstate = LUX_TRUE;
  }
  else {
    glDisable(GL_SCISSOR_TEST);
  }
  ctx->viewport.scissor = state;

  return retstate;
}

LUX_API booln lxgContext_applyViewPort(lxgContextPTR ctx, lxgViewPortPTR view)
{
  booln res = lxgContext_applyViewPortRect(ctx, &view->viewRect);
  ctx->viewport = *view;
  glDepthRange(view->depth.near,view->depth.far);
  
  if (ctx->viewport.scissor){
    glEnable(GL_SCISSOR_TEST);
    glScissor(LUX_ARRAY4UNPACK(&ctx->viewport.scissorRect.x));
  }
  else{
    glDisable(GL_SCISSOR_TEST);
  }

  return res || ctx->viewport.scissor;
}

LUX_API void   lxgContext_applyViewPortMrt(lxgContextPTR ctx, lxgViewPortMrtPTR objmrt)
{
  uint i;
  uint numused = objmrt->numused;

  glViewportArrayv(0,numused,(const float*)objmrt->bounds);
  glScissorArrayv(0,numused,(const int*)objmrt->scissors);
  glDepthRangeArrayv(0,numused,(const double*)objmrt->depths);

  // prep scissor
  for (i = 0; i < objmrt->numused; i++){
    if (objmrt->scissored & (1<<i))
      glEnablei(i,GL_SCISSOR_TEST);
    else
      glDisablei(i,GL_SCISSOR_TEST);
  }
}

LUX_API void  lxgViewPortMrt_sync(lxgViewPortMrtPTR objmrt, lxgContextPTR ctx)
{
  int i;
  memset(objmrt,0,sizeof(lxgViewPortMrt_t));

  if (! (ctx->capbits & LUXGFX_CAP_SM4)) return;

  for (i = 0; i < ctx->capabilites.drawbuffers; i++){
    glGetIntegeri_v(GL_SCISSOR_BOX,i,&objmrt->scissors[i].x);
    glGetFloati_v(GL_VIEWPORT,i,&objmrt->bounds[i].x);
    glGetDoublei_v(GL_DEPTH_RANGE,i,&objmrt->depths[i].near);
    objmrt->scissored |= glIsEnabledi(i,GL_SCISSOR_TEST) ? (1<<i) : 0;
  }
}

LUX_API void lxgRenderAssign_set( lxgRenderAssignPTR rt, lxgTextureCPTR tex, lxgRenderBufferCPTR rbuf, uint mip, uint layer )
{
  LUX_DEBUGASSERT( (!tex && !rbuf) || (rbuf && !tex) || (tex && !rbuf));
  LUX_DEBUGASSERT( !rbuf || (mip == 0 && layer == 0 ));
  LUX_DEBUGASSERT( !tex  || (tex->mipsdefined & (1<<mip)) );
  if (tex){
    switch (tex->gltarget){
    case LUXGL_TEXTURE_1D:
    case LUXGL_TEXTURE_2D:
    case LUXGL_TEXTURE_RECT:
    case LUXGL_TEXTURE_2DMS:
      LUX_DEBUGASSERT(layer == 0);
      break;
    case LUXGL_TEXTURE_3D:
      LUX_DEBUGASSERT(layer == -1 || layer < (uint)tex->depth);
      break;
    case LUXGL_TEXTURE_CUBE:
      LUX_DEBUGASSERT(layer == -1 || layer < 6);
      break;
    case LUXGL_TEXTURE_1DARRAY:
    case LUXGL_TEXTURE_2DARRAY:
    case LUXGL_TEXTURE_CUBEARRAY:
    case LUXGL_TEXTURE_2DMSARRAY:
      LUX_DEBUGASSERT(layer == -1 || layer < (uint)tex->arraysize);
      break;
    }
  }
  
  rt->tex   = tex;
  rt->rbuf  = rbuf;
  rt->mip   = mip;
  rt->layer = layer;

}

LUX_API void lxgContext_setWindowBounds( lxgContextPTR ctx, int width, int height )
{
  ctx->window.width  = width;
  ctx->window.height = height;
}
