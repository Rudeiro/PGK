// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <string>
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
#include "DataReader.hpp"
#include "Camera.hpp"
#include "CameraControler.hpp"



double lastMX;
double lastMY;
bool aut = false;
int autLvl = 2;
bool view = true;
Camera camera = Camera(glm::vec3(0, 0, 63700), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_E)
    {
        view = !view;
		Mesh::SwitchView(view);
    }
    else if(key == GLFW_KEY_1)
	{
		Mesh::SwitchLOD(0);
		aut = false;
		autLvl = 0;
	}
	else if(key == GLFW_KEY_2)
	{
		Mesh::SwitchLOD(1);
		aut = false;
		autLvl = 1;
	}
	else if(key == GLFW_KEY_3)
	{
		Mesh::SwitchLOD(2);
		
		aut = false;
		autLvl = 2;
	}
	else if(key == GLFW_KEY_4)
	{
		Mesh::SwitchLOD(3);
		
		aut = false;
		autLvl = 3;
	}
	else if(key == GLFW_KEY_5)
	{
		Mesh::SwitchLOD(4);
		
		aut = false;
		autLvl = 4;
	}
	else if(key == GLFW_KEY_0)
	{
		
		aut = true;
		
	}
}

void window_size(GLFWwindow* window, int width, int height)
{
	glfwGetWindowSize(window, &width, &height);
    glViewport((width - height)/2, 0, height, height);
}
int main(int argc, char* argv[] )
{
	
	std::string folder = argv[1];
	int psz = std::stoi(argv[3]);
	int ksz = std::stoi(argv[4]);
	int pdl = std::stoi(argv[6]);
	int kdl = std::stoi(argv[7]);
	float x = (63800.0f)*cos(radians(psz*1.0f + 1.0f))*sin(radians(1.0f*pdl+ 1.0f));
	float y = (63800.0f)*sin(radians(psz*1.0f+ 1.0f));
    float z = (63800.0f)*cos(radians(psz*1.0f+ 1.0f))*cos(radians(1.0f*pdl+ 1.0f));
	
	CameraControler::ChangeLTLN((ksz + psz)/2.0f, (kdl + pdl)/2.0f, 100); 
    camera.ChangeWorldPos(vec3(x, y, z));
	
    
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    Mesh::init(folder, psz, ksz, pdl, kdl);
	std::vector<short> heights;
	int vertices = 0;
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	double currentTime;
    do{
        // Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		//triangle.draw(camera);
		vertices += Mesh::DrawElem(camera, view, round(camera.getLTLN_POS()[0]), round(camera.getLTLN_POS()[1]));
		CameraControler::MoveCamera(window, camera, delta_time, view);
		/////////////////////////
		
		currentTime = glfwGetTime();
     	nbFrames++;
     	if ( currentTime - lastTime >= 1.0 )
		{ 
			std::cout << nbFrames << " FPS\n" << vertices << std::endl;
			vertices  = 0;
			
			lastTime += 1.0;
			if(aut && nbFrames >= 60 && autLvl > 0)
			{
				autLvl--;
				
				Mesh::SwitchLOD(autLvl);
			}
			else if(aut && nbFrames < 30 && autLvl < 3)
			{
				autLvl++;
				
				Mesh::SwitchLOD(autLvl);
			}
			std::cout << "LOD: " << autLvl << std::endl;
			nbFrames = 0;
			 
				
			

     	}
		/////////////////////////



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
