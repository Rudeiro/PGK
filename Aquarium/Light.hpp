#ifndef LIGHT_HPP
#define LIGHT_HPP

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

class Light
{
private:
    vec3 position;
    vec3 color;
    int type; // 0 - no light, 1 - player, 2 - bubbles
public:
    Light(){}
    Light(vec3 position, vec3 color, int type)
        : position (position),
          color (color),
          type (type)
    {}
    vec3 GetPos();
    vec3 GetCol();

    int GetType();
    void ChangePos(vec3 NewPos);
};


#endif
