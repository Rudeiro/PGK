#ifndef CAMERA_HPP
#define CAMERA_HPP

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

class Camera
{
private:
    vec3 WorldPos;
    vec3 LookDir;
    vec3 UpVec;
public:

    Camera(vec3 WorldPos, vec3 LookDir, vec3 UpVec)
        : WorldPos (WorldPos),
          LookDir (LookDir),
          UpVec (UpVec)
    {}
    vec3 GetWorldPos();
    void ChangeWorldPos(vec3 NewWorldPos);
    vec3 GetLookDir();
    void ChangeLookDir(vec3 NewLookDir);
    vec3 GetUpVec();
    void ChangeUpVec(vec3 NewUpVec);
    glm::mat4 View();
};

#endif
