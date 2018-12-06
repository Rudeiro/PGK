#ifndef PLAYERCONTROLER_HPP
#define PLAYERCONTROLER_HPP

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

extern float verticalAngle;
extern float horizontalAngle;
extern double lastMX;
extern double lastMY;
extern float speed;
extern float TimeBonus;
extern float Zoom;

void SetBegMousPos(GLFWwindow* window);
void PlayerBehavior(game_object &player, GLFWwindow* &window, float DeltaTime, Camera &camera, game_object &AquaBottom,game_object &AquaLeft,game_object &AquaRight,game_object &AquaFront,game_object &AquaBack);
void move(game_object &player, GLFWwindow* &window, float DeltaTime, Camera &camera,game_object &AquaBottom,game_object &AquaLeft,game_object &AquaRight,game_object &AquaFront,game_object &AquaBack);
game_object PlayerCollide(game_object player, std::queue<vec4> &PosAndSize, std::queue<vec4> &ColAndLight, float &bubble_size, float &bubble_frequency, float &bubble_speed);
void ChangeAquaPos(game_object &AquaBottom,game_object &AquaLeft,game_object &AquaRight,game_object &AquaFront,game_object &AquaBack, game_object player);
double vec3Length(vec3 v);
void ChangingSpeed(float DeltaTime);
#endif
