#ifndef DATAREADER_HPP
#define DATAREADER_HPP

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <fstream>


// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>


// Include GLM
#include <glm/glm.hpp>

using namespace glm;

#include <common/shader.hpp>

class DataReader
{
public:
    static std::vector<short> ReadBinaryFile(std::vector<short> heights);

};
#endif