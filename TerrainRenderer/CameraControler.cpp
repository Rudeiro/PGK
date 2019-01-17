#include "CameraControler.hpp"

double CameraControler::lastMX;
double CameraControler::lastMY;
float  CameraControler::verticalAngle = 0.0f;
float  CameraControler::horizontalAngle = 3.14f;
float CameraControler::lt;
float CameraControler::ln;
float CameraControler::middleLT;
float CameraControler::middleLN;
float CameraControler::h;
float CameraControler::zoom = 1;
float CameraControler::posX2D = 0;
float CameraControler::posY2D = 0;

void CameraControler::ChangeLTLN(float sz, float dl, float height)
{
    lt = sz;
    ln = dl;
    middleLT = sz;
    middleLN = dl;
    h = height;
}
void CameraControler::MoveCamera(GLFWwindow* window, Camera &camera, float delta_time, bool view)
{
    
    
    if(!view)
    {
        float x;
        float y;
        float z;
        double mouseX;
        double mouseY;
        float mouseSpeed = 0.1f;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        horizontalAngle += mouseSpeed * delta_time * float( lastMX - mouseX );
        verticalAngle   += mouseSpeed * delta_time * float( lastMY - mouseY );

        lastMX = mouseX;
        lastMY = mouseY;
        glm::mat3 rotation = glm::mat3(cos(horizontalAngle), -sin(horizontalAngle), 0,
                                    sin(horizontalAngle), cos(horizontalAngle), 0,                  
                                    0,  0,  1);

        
    
        glm::vec3 dir2D = normalize(vec3(0, 1, 0)*rotation);
        glm::vec3 right2D = normalize(glm::cross(dir2D, vec3(0, 0, 1)));
    
        glm::vec3 direction = glm::vec3(
            (63700.0f + h)*cos(radians(dir2D.y))*sin(radians(dir2D.x)),
            (63700.0f + h)*sin(radians(dir2D.y)),
            (63700.0f + h)*cos(radians(dir2D.y))*cos(radians(dir2D.x))
        );
        glm::vec3 right = glm::vec3(
            (63700.0f + h)*cos(radians(right2D.y))*sin(radians(right2D.x)),
            (63700.0f + h)*sin(radians(right2D.y)),
            (63700.0f + h)*cos(radians(right2D.y))*cos(radians(right2D.x))
        );
        glm::vec3 up2D = vec3(0, 0, 1);
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        {
            h += 100*delta_time;
            
        }
        else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        {
            h -= 100*delta_time;
            
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            lt += dir2D.y*delta_time/3;
            ln += dir2D.x*delta_time/3;
            
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            lt -= dir2D.y*delta_time/3;
            ln -= dir2D.x*delta_time/3;
            
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            lt -= right2D.y*delta_time/3;
            ln -= right2D.x*delta_time/3;
            
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            lt += right2D.y*delta_time/3;
            ln += right2D.x*delta_time/3;
            
        }
        x = (63700.0f + h)*cos(radians(lt))*sin(radians(ln));
        y = (63700.0f + h)*sin(radians(lt));
        z = (63700.0f + h)*cos(radians(lt))*cos(radians(ln));
        glm::vec3 LookDir = vec3(ln, lt, 0) + dir2D;

        float heightView = 63700.0f + h + verticalAngle*500;

        float a = (heightView)*cos(radians(LookDir.y))*sin(radians(LookDir.x));
        float b = (heightView)*sin(radians(LookDir.y));
        float c = (heightView)*cos(radians(LookDir.y))*cos(radians(LookDir.x));
        camera.setLTLN_POS(lt, ln);
        camera.ChangeWorldPos(vec3(x, y, z));
        camera.ChangeLookDir(vec3(a, b, c));
        camera.ChangeUpVec(normalize(camera.GetWorldPos()));
    }
    else
    {
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        {
            h += 100*delta_time;
            
        }
        else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        {
            h -= 100*delta_time;
            
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            posY2D += delta_time;
            lt += 1*delta_time/3;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            lt -= 1*delta_time/3;
            posY2D -= delta_time;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            ln -= 1*delta_time/3;
            posX2D -= delta_time;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            
            ln += 1*delta_time/3;
            posX2D += delta_time;
            
        }
       
        camera.setLTLN_POS(lt, ln);
        camera.ChangeWorldPos(vec3(posX2D, posY2D, h/200.0f));
        camera.ChangeLookDir(vec3(posX2D, posY2D, 0));
        camera.ChangeUpVec(normalize(vec3(0, 1, 0)));
    }
}