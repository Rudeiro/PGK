#ifndef CAMERACONTROLER_HPP
#define CAMERACONTROLER_HPP


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
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.hpp"

class CameraControler
{
protected:
    static double lastMX;
    static double lastMY;
    static float  verticalAngle;
    static float horizontalAngle;
    static float lt;
    static float ln;
    static float h;
    static float zoom;
    static float middleLT;
    static float middleLN; 
    
public:
    static void ChangeLTLN(float sz, float dl, float height);
    static void MoveCamera(GLFWwindow* window, Camera &camera, float delta_time, bool view);


};

#endif