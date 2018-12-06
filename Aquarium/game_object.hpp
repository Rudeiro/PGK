#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

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
#include "Mesh.hpp"
#include "Camera.hpp"
using namespace glm;

#include <common/shader.hpp>

class game_object
{
private:
    vec3 trans;
    vec3 scale;
    Mesh mesh;
    Light light;
public:
    game_object(){};
    game_object(vec3 trans, vec3 scale, Mesh mesh, Light light);
    void draw(float angle, Camera camera);
    void change_trans(vec3 t);
    vec3 get_trans();
    void change_scale(vec3 s);
    vec3 get_scale();
    int GetLightType();
    vec3 GetLightCol();
    void ChangeLightPos();
    void DrawInstanced(GLfloat PosAndSize[100000], GLfloat ColorAndLight[100000], Camera camera, int n);



};

#endif
