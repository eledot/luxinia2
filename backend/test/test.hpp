// Copyright (C) 2004-2011 Christoph Kubisch
// This file is part of the "Luxinia Engine".
// For conditions of distribution and use, see copyright notice in LICENSE.txt

#ifndef __LUXTEST_TEST_H__
#define __LUXTEST_TEST_H__

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <luxmath/luxmath.h>
#include <luxmath/basetypes.hpp>

#include <string.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////

inline float randomFloat(){
  return (float) rand()/RAND_MAX;
}

inline float randomFloat(float max){
  return ((float) rand()/RAND_MAX) * max;
}

inline float randomFloat(float min, float max){
  return (((float) rand()/RAND_MAX) * (max - min)) + min;
}

//////////////////////////////////////////////////////////////////////////
class KeyTracker
{
public:
  struct KeyState{
    int   last;
    int   toggled;
  };

  KeyTracker() {
    memset(m_states,0,sizeof(m_states));
  }
  void update(GLFWwindow win){
    for (size_t i = 0; i < m_tracked.size(); i++){
      int key = m_tracked[i];
      int state = glfwGetKey(win,key);
      m_states[key].toggled = m_states[key].last != state;
      m_states[key].last = state;
    }
  }

  void add(int key){
    m_tracked.push_back(key);
  }
  inline int pressed(int key) const {
    return m_states[key].last;
  }
  inline int toggled(int key) const {
    return m_states[key].toggled;
  }
  inline int onPress(int key) const {
    return m_states[key].last && m_states[key].toggled;
  }
  inline const KeyState& get(int key) const {
    return m_states[key];
  }

private:
  KeyState          m_states[GLFW_KEY_LAST];
  std::vector<int>  m_tracked;
};

//////////////////////////////////////////////////////////////////////////

struct VertexDefault{
  lxCVector2  uv;
  lxCVector3  normal;
  lxCVector3  pos;
};

class Geometry {
public:

  Geometry() : vbo(0), ibo(0), dltris(0), dlline(0) {}
  ~Geometry();

  std::vector<lxCVector3>   pos;
  std::vector<lxCVector3>   normal;
  std::vector<lxCVector2>   uv;
  std::vector<uint32>       indicesTris;
  std::vector<uint32>       indicesLines;
  GLuint                    vbo;
  GLuint                    ibo;
  GLuint                    dltris;
  GLuint                    dlline;

  void updateBO();
  void updateDL();

  void clearBO();
  void clearDL();

  void drawVBO(booln outline=0,booln bind=1);
  void drawDL(booln outline=0);
  void drawVA(booln outline=0);

protected:
  void allocMem(int numVertices, int numIndicesTris, int numIndicesLines);

};

class GeometryBox : public Geometry 
{
public:
  GeometryBox() { update(4,4,4); }
  GeometryBox(int x, int y, int z) { update(x,y,z); }
  void update(int x, int y, int z);
};

class GeometryDisc : public Geometry 
{
public:
  GeometryDisc() { update(32,4); }
  GeometryDisc(int x, int y){ update(x,y); }
  void update(int x, int y);
};

class GeometryPlane : public Geometry 
{
public:
  GeometryPlane() { update(4,4); }
  GeometryPlane(int x, int y) { update(x,y); }
  void update(int x, int y);
};

class GeometrySphere : public Geometry 
{
public:
  GeometrySphere() { update(32,16); }
  GeometrySphere(int x, int y) { update(x,y); }
  void update(int x, int y);
};

class GeometryCylinder : public Geometry 
{
public:
  GeometryCylinder() { update(32,4,4); }
  GeometryCylinder(int x, int y, int z) { update(x,y,z); }
  void update(int x, int y, int z);
};

//////////////////////////////////////////////////////////////////////////

struct Material{
  lxCVector4  ambient;
  lxCVector4  diffuse;
  lxCVector4  specular;
  lxCVector4  emission;

  void random();
};

class MaterialState{
public:
  Material  front;
  Material  back;
  GLuint    buffer;
  GLuint64  address;

  MaterialState() : buffer(0) { random(); }
  ~MaterialState();

  void      clearBO();
  void      updateBO();

  void      stateFixed();

  void      random();
};

struct DrawNode{
  MaterialState*  matstate;
  Geometry*       geometry;
  lxCMatrix44*    matrix;
};


//////////////////////////////////////////////////////////////////////////

class RenderHelper {
public:

  static GLuint generateUVTexture(int w, int h);
  static GLuint loadShader(GLenum type, const char* filename, const char* prepend );

  void init(GLFWwindow win, const lxCVector3& up);
  void cameraOrtho(lxBoundingBox_t* bbox);
  void cameraPerspective(lxBoundingBox_t* bbox, float fovdeg);
  void updateProjection(int width, int height);
  void setCameraGL();
  void doArcBall(int width, int height);

private:

  GLFWwindow  m_window;

  float       m_ortho;
  float       m_fov;
  lxCMatrix44 m_viewmatrix;
  lxCMatrix44 m_projmatrix;
  lxCVector3  m_sceneCenter;
  lxCVector3  m_sceneSize;

  lxCVector3  m_lastmpos;
  float       m_movespeed;
  float       m_rotspeed;
  lxCVector3  m_up;
};

//////////////////////////////////////////////////////////////////////////

class Test;
class TestManager {
public:
  static TestManager& Get(){
    static TestManager mgr;
    return mgr;
  }

  void addTest(Test* test){
    m_tests.push_back(test);
  }

  Test* getTest(const char* name);

private:
  std::vector<Test*>  m_tests;

};


class Test
{
public:
  Test(const char* name) : m_name(name){
    TestManager::Get().addTest(this);
  }

  const char* getName() const {
    return m_name;
  }
  virtual void onDraw(int width, int height) {}
  virtual void onInit(GLFWwindow window, int argc, const char** argv) {}
  virtual void onDeInit() {}

private:
  const char*   m_name;
};

//////////////////////////////////////////////////////////////////////////





#endif

