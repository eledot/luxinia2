print "glfw-minimal-host"

local glfw = require "glfw"
local ffi  = require "ffi"
local gl   = require "glewgl"
local svPoll = LUXGLOBAL.svPoll

local function main()
  assert( glfw.glfwInit() )
  local status = glfw.glfwOpenWindow( 640, 480, 8,8,8,8,24,8, glfw.GLFW_WINDOW)
  assert( status == glfw.GLFW_TRUE )
  glfw.glfwSetWindowTitle( "glfw-minimal-host")
  gl.glewInit()
  gl.glClearColor(0.2,0.2,0.2,0)
  local clearbits = bit.bor(bit.bor(gl.GL_COLOR_BUFFER_BIT,gl.GL_STENCIL_BUFFER_BIT),gl.GL_DEPTH_BUFFER_BIT)

  glfw.glfwEnable(glfw.GLFW_STICKY_KEYS)
  glfw.glfwDisable(glfw.GLFW_AUTO_POLL_EVENTS)
  glfw.glfwSwapInterval(1)
  gl.glClear(clearbits)

  while glfw.glfwGetWindowParam( glfw.GLFW_OPENED ) ~= 0 and glfw.glfwGetKey(glfw.GLFW_KEY_ESC) ~= glfw.GLFW_PRESS 
  do
    local t = glfw.glfwGetTime()
    if( THINK ) then THINK(t) end
    gl.glClear(clearbits)

    glfw.glfwSwapBuffers()
    glfw.glfwPollEvents()
    svPoll()
  end
  glfw.glfwTerminate()
  os.exit(0)
end

main()
