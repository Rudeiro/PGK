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
#include "Light.hpp"

extern GLfloat a;
extern GLfloat b;

class Mesh
{
protected:
    vec3 color;
    int shape;
    int v_num;

    static GLint r_y;
    static GLuint programID;
    static GLint t;
    static GLint s;
    static GLint c;
    static GLint m;
    static GLint v;
    static GLint p;
    static GLint mvp;
    static GLfloat vertex[100000];
    static GLfloat Normals[100000];
    static GLfloat cube[1000];
    static GLint BubLigWorldSpace;
    static GLint BubLigCol;
    static GLint NumOfLights;
    static int LightBubbles;
    static vec3 BubbleLightsPos[15];
    static vec3 BubbleLightsCol[15];
    static GLint PLightColor;
    static GLint PLightPos;
    static GLuint vertexbuffer;
    static GLuint vertexnormal;
    static GLuint posbuffer;
    static GLuint colbuffer;
    static GLint isInstanced;
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
    void DrawInstanced(GLfloat PosAndSize[100000], GLfloat ColorAndLight[100000], Camera camera, int n);
    static void ChangeBubbleLight(int n, vec3 Pos[15], vec3 Col[15]);
    void draw(glm::mat4 model, float angle, Camera camera, Light light);

};

#endif
