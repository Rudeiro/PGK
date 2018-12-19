#ifndef MESH_HPP
#define MESH_HPP

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>


// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>


// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.hpp"

class Mesh
{
protected:
    vec3 color;
    int shape;
    int v_num;

    
    static GLuint programID;
    static GLint m;
    static GLint v;
    static GLint p;
    static GLint mvp;
    static GLfloat vertex[100000];
    static GLuint vertexbuffer;
    static glm::mat4 Projection;


public:
    Mesh(){};
    Mesh(vec3 c, int shape, int v_num)
        : color (c),
          shape (shape),
          v_num (v_num)
    {}
    static void init();
    static void clear();
   
};

#endif
