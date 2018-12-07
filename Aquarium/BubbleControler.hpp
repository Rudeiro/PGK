#ifndef BUBBLECONTROLER_HPP
#define BUBBLECONTROLER_HPP

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>



// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>


// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "game_object.hpp"
#include "Camera.hpp"
#include "Light.hpp"
using namespace glm;

#include <common/shader.hpp>
extern float time_to_bubble;
extern int Level;

bool order(game_object g1, game_object g2);
void LevelUp(game_object player, float DeltaTime, float &bubble_size, float &bubble_frequency, float &bubble_speed, float &LevelTime);
void create_bubble(std::queue<vec4> &bubblesPosAndSize, std::queue<vec4> &bubblesColAndLight, float DeltaTime, game_object player,
                   float &bubble_size, float &bubble_frequency, float &bubble_speed);
void move_bubbles(game_object bubble, std::queue<vec4> &bubblesPosAndSize, std::queue<vec4> &bubblesColAndLight, float DeltaTime,
                   Camera camera, bool pause, game_object player,
                    float &bubble_speed);
#endif
