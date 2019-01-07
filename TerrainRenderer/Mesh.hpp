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
#include <string>
#include <cmath>
#include <dirent.h>


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
#include "DataReader.hpp"

class Mesh
{
protected:
    vec3 color;
    int shape;
    int v_num;

    
    static GLuint programID;
    static GLuint programID_3D;
    static GLint m;
    static GLint v;
    static GLint p;
    static GLint mvp;
    static GLint c;
    static GLfloat vertex[100000];
    static GLfloat map[4500000];
    static GLuint Order[4500000];
    static GLuint orderbuffer;
    static GLuint vertexbuffer;
    static glm::mat4 Projection;
    static std::vector<std::vector<short>> heights;
    static GLint pX;
    static GLint pY;
    static GLint siX;
    static GLint siY;
    static GLint pX_3D;
    static GLint pY_3D;
    static GLint siX_3D;
    static GLint siY_3D;
    static std::vector<int> GridPosX;
    static std::vector<int> GridPosY;
    static int szerokosc;
    static int dlugosc;

public:
    Mesh(){};
    Mesh(vec3 c, int shape, int v_num)
        : color (c),
          shape (shape),
          v_num (v_num)
    {}
    static void init(std::string dirname, int psz, int ksz, int pdl, int kdl);
    static void clear();
    void draw(glm::mat4 model, Camera camera);
    static void DrawElem(Camera camera, bool type);
    static void SwitchView(bool type);
   
};

#endif
