#include "PlayerControler.hpp"
#include "Mesh.hpp"
float  verticalAngle = 0.0f;
float horizontalAngle = 3.14f;

double lastMX;
double lastMY;

float speed = 3.0f;
float TimeBonus = 4.5f;
float Zoom = 2.0f;

void SetBegMousPos(GLFWwindow* window)
{
    glfwGetCursorPos(window, &lastMX, &lastMY);
}
void ChangingSpeed(float DeltaTime)
{
    if(TimeBonus < 4.0f) TimeBonus += DeltaTime;
    else speed = 3.0f;
}
void PlayerBehavior(game_object &player, GLFWwindow* &window, float DeltaTime, Camera &camera, game_object &AquaBottom,game_object &AquaLeft,game_object &AquaRight,game_object &AquaFront,game_object &AquaBack)
{
    move(player, window, DeltaTime, camera, AquaBottom, AquaLeft, AquaRight, AquaFront, AquaBack);

}

void move(game_object &player, GLFWwindow* &window, float DeltaTime, Camera &camera,game_object &AquaBottom,game_object &AquaLeft,game_object &AquaRight,game_object &AquaFront,game_object &AquaBack)
{

    /////////////////////////////////////////////////////// Changing camera view according to mouse position
    double mouseX;
    double mouseY;
    float mouseSpeed = 0.5f;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    horizontalAngle += mouseSpeed * DeltaTime * float( lastMX - mouseX );
    verticalAngle   += mouseSpeed * DeltaTime * float( lastMY - mouseY );

    lastMX = mouseX;
    lastMY = mouseY;

     glm::vec3 direction = glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );
    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );
    glm::vec3 up = glm::cross( right, direction );


    camera.ChangeWorldPos(player.get_trans() - direction*Zoom);
    camera.ChangeLookDir(player.get_trans() + direction);
    camera.ChangeUpVec(up);

    ////////////////////////////////////////////////////////// Moving player with arrows and zooming camera with 'Z' and 'X'
    vec3 new_pos;
    // Move forward
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        new_pos = player.get_trans() + direction * DeltaTime * speed;
        if(new_pos.y > -5.0f + 0.2*0.9511 &&
            new_pos.x > -5.0f + 0.2*0.9511 &&
            new_pos.x <  5.0f - 0.2*0.9511 &&
            new_pos.y <  5.0f - 0.2*0.9511)
        {
            player.change_trans(player.get_trans() += direction * DeltaTime * speed);
            player.ChangeLightPos();
        }
    }
    // Move backward
    if (glfwGetKey( window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        new_pos = player.get_trans() -= direction * DeltaTime * speed;
        if(new_pos.y > -5.0f + 0.2*0.9511 &&
            new_pos.x > -5.0f + 0.2*0.9511 &&
            new_pos.x <  5.0f - 0.2*0.9511 &&
            new_pos.y <  5.0f - 0.2*0.9511)
        {
            player.change_trans(player.get_trans() -= direction * DeltaTime * speed);
            player.ChangeLightPos();
        }
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS)
    {
        new_pos = player.get_trans() += right * DeltaTime * (speed/2);
        if(new_pos.y > -5.0f + 0.2*0.9511 &&
            new_pos.x > -5.0f + 0.2*0.9511 &&
            new_pos.x <  5.0f - 0.2*0.9511 &&
            new_pos.y <  5.0f - 0.2*0.9511)
        {
            player.change_trans(player.get_trans() += right * DeltaTime * (speed/2));
            player.ChangeLightPos();
        }
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        new_pos = player.get_trans() -= right * DeltaTime * (speed/2);
        if(new_pos.y > -5.0f + 0.2*0.9511 &&
            new_pos.x > -5.0f + 0.2*0.9511 &&
            new_pos.x <  5.0f - 0.2*0.9511 &&
            new_pos.y <  5.0f - 0.2*0.9511)
        {
           player.change_trans(player.get_trans() -= right * DeltaTime * (speed/2));
           player.ChangeLightPos();
        }
    }
     if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
     {
         if(Zoom > 0) Zoom -= DeltaTime;
         else Zoom = 0;
         camera.ChangeWorldPos(player.get_trans() - direction*Zoom);

     }
     if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
     {
         if(Zoom < 2.0f) Zoom += DeltaTime;
         camera.ChangeWorldPos(player.get_trans() - direction*Zoom);

     }
    ChangeAquaPos( AquaBottom, AquaLeft, AquaRight, AquaFront, AquaBack, player);

}

double vec3Length(vec3 v)
{
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

game_object PlayerCollide(game_object player, std::queue<vec4> &PosAndSize, std::queue<vec4> &ColAndLight, float &bubble_size, float &bubble_frequency, float &bubble_speed)
{
    std::queue<vec4> new_PosAndSize;
    std::queue<vec4> new_ColAndLight;
    vec4 Pos;
    vec4 Light;
    bool collided = false;
    while(!PosAndSize.empty())
    {
        Pos = PosAndSize.front();
        Light = ColAndLight.front();
        if(vec3Length(vec3(Pos) - player.get_trans()) < player.get_scale()[0]*0.9511f + Pos[3]*0.9511f )
        {
            if(Light[3] == 1) // if player collided with light bubble we increase speed temporarily
            {
                speed *= 2;
                TimeBonus = 0.0f;
                PosAndSize.pop();
                ColAndLight.pop();
                Pos = PosAndSize.front();
                Light = ColAndLight.front();
            }
            else // other bubbles kill player and return him to the starting position
            {
                collided = true;
                player.change_trans(vec3(0, 0 ,0));
                player.ChangeLightPos();
                bubble_size = 0.3f;
                bubble_speed = 2.0f;
                bubble_frequency = 0.1f;
            }
        }
        new_PosAndSize.push(Pos);
        new_ColAndLight.push(ColAndLight.front());
        if(!PosAndSize.empty())
        {
            PosAndSize.pop();
            ColAndLight.pop();
        }
    }
    if(!collided)
    {
        ColAndLight = new_ColAndLight;
        PosAndSize = new_PosAndSize;
    }
    return player;
}

//Moving aquarium with Z Axis of the player so it appear to be infinite
void ChangeAquaPos(game_object &AquaBottom,game_object &AquaLeft,game_object &AquaRight,game_object &AquaFront,game_object &AquaBack, game_object player)
{
    AquaBottom.change_trans(vec3(0, -5.1f, player.get_trans().z));
    AquaLeft.change_trans(vec3(- 5.1f, 0, player.get_trans().z));
    AquaRight.change_trans(vec3(5.1f, 0, player.get_trans().z));
    AquaFront.change_trans(vec3(0, 0, player.get_trans().z + 15.1));
    AquaBack.change_trans(vec3(0, 0, player.get_trans().z - 15.1));
}
