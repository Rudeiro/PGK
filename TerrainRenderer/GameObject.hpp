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

class GameObject
{
private:
    vec3 trans;
    vec3 scale;
    Mesh mesh;
public:
    GameObject(){};
    GameObject(vec3 trans, vec3 scale, Mesh mesh);
    void draw(Camera camera);
    void change_trans(vec3 t);
    vec3 get_trans();
    void change_scale(vec3 s);
    vec3 get_scale();
};

#endif
