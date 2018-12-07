#include "BubbleControler.hpp"
;
float time_to_bubble = 0.0f;
int Level = 0;


void LevelUp(game_object player, float DeltaTime, float &bubble_size, float &bubble_frequency, float &bubble_speed, float &LevelTime)
{
    if(bubble_size <= 0.3f)
    {
        std::cout << "\033[2J\033[0;0H" << std::endl;
        std::cout << "GAME DESCRIPTION\n";
        std::cout << "Your goal is to travel through the aquarium as far as you can.\n";
        std::cout << "You can collect light bubbles to temporarily increase your speed \n";
        std::cout << "but be careful about other bubbles cause if you touch theme you start\n";
        std::cout << "from the beginnig.\n";
        std::cout << "PLAYER CONTROL\n";
        std::cout << "You move with the arrows according to camera view.\n";
        std::cout << "You can zoom camera view using 'Z' and 'X'\n";
        std::cout << "You can use TAB to pause the game and see the aquarium from outside.\n";
        std::cout << "You can use 'F' do enable/disable cursor\n";
        Level = 0;
    }
    if(LevelTime > 5.0f)
    {
        bubble_size += 0.1f;
        bubble_frequency -= 0.01f;
        bubble_speed += 0.1f;
        LevelTime = 0;
        Level++;
        std::cout << Level << " " << -player.get_trans().z << std::endl;


    }
    else LevelTime += DeltaTime;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void move_bubbles(game_object bubble, std::queue<vec4> &bubblesPosAndSize, std::queue<vec4> &bubblesColAndLight,
                  float DeltaTime, Camera camera, bool pause, game_object player, float &bubble_speed)
{
    std::queue<vec4> new_bubblesPosAndSize;
    std::queue<vec4> new_bubblesColAndLight;
    int k = 0;
    vec4 bubblePosAndSize;
    vec4 bubbleColAndLight;
    vec3 LightPos[15];
    vec3 LightCol[15];
    int n = 0;

    while(!bubblesPosAndSize.empty())
    {
        bubblePosAndSize = bubblesPosAndSize.front();
        bubbleColAndLight = bubblesColAndLight.front();

        if(bubblePosAndSize.y < 5.0f && !pause) // moving bubble up if he is not to high
        {
            bubblePosAndSize += vec4(0.0f, bubble_speed*DeltaTime, 0.0f, 0.1f/(10.0f/(0.5f*DeltaTime)));

            new_bubblesPosAndSize.push(bubblePosAndSize);
            new_bubblesColAndLight.push(bubbleColAndLight);
            k++;
            if(bubbleColAndLight[3] == 1 && n < 15) // if bubble is light
            {
                LightPos[n] = vec3(bubblePosAndSize);
                LightCol[n] = vec3(bubbleColAndLight);
                n++;
            }
        }
        if(pause) // if the game is paused we just rewrite the queue
        {

            new_bubblesPosAndSize.push(bubblePosAndSize);
            new_bubblesColAndLight.push(bubbleColAndLight);
            k++;
        }
        bubblesPosAndSize.pop();
        bubblesColAndLight.pop();
    }

    bubblesPosAndSize = new_bubblesPosAndSize;
    bubblesColAndLight = new_bubblesColAndLight;
    GLfloat PosAndSize[k*4];
    GLfloat ColAndLight[k*4];
    for(int i = 0; i < k*4; i += 4) // making positions/sizes and color/islight buffers to instanced drawing
    {
        PosAndSize[i] = new_bubblesPosAndSize.front()[0];
        PosAndSize[i+1] = new_bubblesPosAndSize.front()[1];
        PosAndSize[i+2] = new_bubblesPosAndSize.front()[2];
        PosAndSize[i+3] = new_bubblesPosAndSize.front()[3];
        ColAndLight[i] = new_bubblesColAndLight.front()[0];
        ColAndLight[i+1] = new_bubblesColAndLight.front()[1];
        ColAndLight[i+2] = new_bubblesColAndLight.front()[2];
        ColAndLight[i+3] = new_bubblesColAndLight.front()[3];
        new_bubblesPosAndSize.pop();
        new_bubblesColAndLight.pop();
    }

    if(!pause) Mesh::ChangeBubbleLight(n, LightPos, LightCol);
    bubble.DrawInstanced(PosAndSize, ColAndLight, camera, k);
}

void create_bubble(std::queue<vec4> &bubblesPosAndSize, std::queue<vec4> &bubblesColAndLight, float DeltaTime, game_object player,
                   float &bubble_size, float &bubble_frequency, float &bubble_speed)
{
    vec3 colors[11] =
    {
        {0, 0, 0.7},
        {0, 0.3, 0.9},
        {0, 0.6, 0.7},
        {0, 0.6, 0.8},
        {0, 0.5, 0.5},
        {0, 0.7, 0.7},
        {0.3, 0.5, 0.9},
        {0.5, 0.8, 0.9},
        {0.7, 0.9, 1},
        {0, 0.2, 0.5},
        {1, 1, 1}
    };
    float aquaX = 10.0f;
    float aquaY = 10.0f;
    float aquaZ = 30.0f;
    float x, y;
    float z;
    float R;
    float G;
    float B;
    int HasLight;
    time_to_bubble += DeltaTime;
    float size;
    if(time_to_bubble > bubble_frequency) // creating bubble every bubble_frequency time
    {
        x = ((double)rand() / RAND_MAX)*aquaX - aquaX/2;
        y = ((double)rand() / RAND_MAX)*aquaY - aquaY/2;
        z = ((double)rand() / RAND_MAX)*aquaZ - (aquaZ*0.8 - player.get_trans().z);
        size = ((double)rand() / RAND_MAX)*bubble_size + 0.1;
        vec3 color = colors[rand() %11];

        if(x < -5.0f + size*0.9511f*2)
        {
            x = -5.0f + size*0.9511f;
        }
        if(x > 5.0f - size*0.9511f*2) x = 5.0f - size*0.9511f;
        if(z < -aquaZ/2 + size*0.9511f*2 + player.get_trans().z) z = -aquaZ/2  + size*0.9511f + player.get_trans().z;
        if(z > aquaZ/2  - size*0.9511f*2 + player.get_trans().z) z = aquaZ/2  - size*0.9511f + player.get_trans().z;
        HasLight = rand()%20;
        bubblesPosAndSize.push(vec4(vec3(x, -5.0f - size*0.9511f, z), size));
        if(HasLight == 0)
            bubblesColAndLight.push(vec4(color, 1));

        else
            bubblesColAndLight.push(vec4(color,0));

       time_to_bubble = 0;
    }


}


