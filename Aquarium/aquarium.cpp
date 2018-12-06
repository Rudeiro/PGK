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
#include "game_object.hpp"
#include "PlayerControler.hpp"
#include "BubbleControler.hpp"
#include "Camera.hpp"
#include "Light.hpp"
;
Camera camera = Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -10), glm::vec3(0, 1, 0));
game_object player = game_object(vec3(0.0f, 0.0f, 0.0f), vec3(0.2f, 0.2f, 0.2f), Mesh(vec3(1, 0, 0), 0,15360/4), Light(vec3(0,0,0), vec3(1,0,0),  1));
bool pause = false;
bool RenderFront = true;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_TAB)
    {
        camera.ChangeWorldPos(vec3(30.0f, 15.0f, player.get_trans().z));
        camera.ChangeLookDir(vec3(0.0f, 0.0f, player.get_trans().z));
        camera.ChangeUpVec(vec3(0, 1, 0));
        RenderFront = !RenderFront;
        pause = !pause;
    }
}



int main(int argc, char* argv[] )
{
    //std::queue<game_object> bubbles;
    game_object AquaBottom = game_object(vec3(0.0f, -5.1f, 0.0f), vec3(10.4f, 0.2f, 30.4f), Mesh(vec3(0.93f, 0.86f, 0.43f), 34560/3, 36), Light(vec3(0,0,0), vec3(0,0,0),  0)); //
    game_object AquaLeft = game_object(vec3(-5.1, 0.0f, 0.0f), vec3(0.2f, 10.4f, 30.4f), Mesh(vec3(0, 0, 0), 34560/3, 36), Light(vec3(0,0,0), vec3(0,0,0),  0));
    game_object AquaRight = game_object(vec3(5.1, 0.0f, 0.0f), vec3(0.2f, 10.4f, 30.4f), Mesh(vec3(0, 0, 0), 34560/3, 36), Light(vec3(0,0,0), vec3(0,0,0),  0));
    game_object AquaFront = game_object(vec3(0.0f, 0.0f, 15.1f), vec3(10.4f, 10.4f, 0.2f), Mesh(vec3(0, 0, 0), 34560/3, 36), Light(vec3(0,0,0), vec3(0,0,0),  0));
    game_object AquaBack = game_object(vec3(0.0f, 0.0f, -15.1f), vec3(10.4f, 10.4f, 0.2f), Mesh(vec3(0, 0, 0), 34560/3, 36), Light(vec3(0,0,0), vec3(0,0,0),  0));
    srand((unsigned)time(0));




    /////////////////////////////////////
    std::queue<vec4> bubblesPosAndSize;
    std::queue<vec4> bubblesColAndLight;
   // bubblesPosAndSize.push(vec4(1, 0, 0, 0.5));
    //bubblesColAndLight.push(vec4(1, 0, 0, 0.5));
    game_object inst = game_object(vec3(0.0f, 0.0f, 0.0f), vec3(0.2f, 0.2f, 0.2f), Mesh(vec3(1, 0, 0), 0,15360/4), Light(vec3(0,0,0), vec3(1,0,0),  1));





    //////////////////////////////////////////

    /*glm::mat4 camera = glm::lookAt(
        glm::vec3(0, 1, 2),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0));*/

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

	window = glfwCreateWindow( 720, 720, "Bubbles", NULL, NULL);
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

    float frame;
    float pre_frame;
    float delta_time;
    float time = 0.0f;
    int ktory = 0;
    float k = 0.0f;
    frame = glfwGetTime();
    delta_time = 1.0f /60.0f;
    pre_frame = frame - delta_time;
    Mesh::init();
    bool is_set = false;
    ////////////////////////////////

    float bubble_size = 0.3f;
    float bubble_frequency = 0.1f;
    float bubble_speed = 2.0f;
    float LevelTime = 0.0f;
    std::cout << "\033[2J\033[0;0H" << std::endl;
    std::cout << "GAME DESCRIPTION\n";
    std::cout << "Your goal is to travel through the aquarium as far as you can.\n";
    std::cout << "You can collect light bubbles to temporarily increase your speed \n";
    std::cout << "but be careful about other bubbles cause if you touch theme you start\n";
    std::cout << "from the beginnig.\n";
    std::cout << "PLAYER CONTROL\n";
    std::cout << "You move with the arrows according to camera view.\n";
    std::cout << "You can zoom camera view using 'Z' and 'X'";
    std::cout << "You can use TAB to pause the game and see the aquarium from outside.\n";
    ///////////////////////////////////
    do{
        LevelUp(player, delta_time, bubble_size, bubble_frequency, bubble_speed, LevelTime);
        if(!pause) create_bubble(bubblesPosAndSize, bubblesColAndLight, delta_time, player, bubble_size, bubble_frequency, bubble_speed);

        ChangingSpeed(delta_time);
        //glCullFace(GL_FRONT);
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        //ground.draw(glm::radians(k), camera);

        AquaBottom.draw(glm::radians(k), camera);
        AquaLeft.draw(glm::radians(k), camera);
        if(RenderFront)
            AquaRight.draw(glm::radians(k), camera);
        AquaFront.draw(glm::radians(k), camera);
        AquaBack.draw(glm::radians(k), camera);
        player.draw(glm::radians(k), camera);

        player = PlayerCollide(player, bubblesPosAndSize, bubblesColAndLight, bubble_size, bubble_frequency, bubble_speed);
        //inst.DrawInstanced(p, c, camera, 1);
        //k += 0.5f;
        //move_bubbles(bubbles, delta_time, camera, pause);
        move_bubbles(inst, bubblesPosAndSize, bubblesColAndLight, delta_time, camera, pause, player, bubble_speed);
        if(!pause)
        {

            if(!pause) PlayerBehavior(player, window, delta_time, camera, AquaBottom, AquaLeft, AquaRight, AquaFront, AquaBack);//
        }


        //time += delta_time;
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
