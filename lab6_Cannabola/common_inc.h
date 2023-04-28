#pragma once

#ifdef _MSC_VER
#pragma comment(lib, "opengl32.lib")
#endif

#include <GL/glew.h>
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include <numbers>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>