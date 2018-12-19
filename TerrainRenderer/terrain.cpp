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
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>
#include "Mesh.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"

Camera camera = Camera(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_TAB)
    {
        
    }
    else if(key == GLFW_KEY_F)
    {
    }
}

void window_size(GLFWwindow* window, int width, int height)
{
	glfwGetWindowSize(window, &width, &height);
    glViewport((width - height)/2, 0, height, height);
}
int main(int argc, char* argv[] )
{
    GameObject triangle = GameObject(vec3(0, 0, 0), vec3(1, 1, 1), Mesh(vec3(1, 0, 0), 0, 9));
    srand((unsigned)time(0));
	//////////////////////////////////////////////////////////
    if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}
    srand((unsigned)time(0));
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context

	window = glfwCreateWindow( 720, 720, "Terrain", NULL, NULL);
    glfwSetWindowSizeCallback(window, window_size);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback); //connecting keys to window: key_callback function is called after clicking buttons
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	/////////////////////////////////////////////////////////////////////////////////////

    float frame;
    float pre_frame;
    float delta_time;
    frame = glfwGetTime();
    delta_time = 1.0f /60.0f;
    pre_frame = frame - delta_time;
    Mesh::init();
   
    do{
        // Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		triangle.draw(camera);
		

        frame = glfwGetTime();
        delta_time = -pre_frame + frame;
        pre_frame = frame;

        // Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO

	glDeleteVertexArrays(1, &VertexArrayID);
    Mesh::clear();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
