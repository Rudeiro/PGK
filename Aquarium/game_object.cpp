
#include "game_object.hpp"


game_object::game_object(vec3 trans, vec3 scale, Mesh mesh, Light light)
                : trans (trans),
                  scale (scale),
                   mesh (mesh),
                   light (light)
                {}

void game_object::draw(float angle, Camera camera)
{
    mat4 model = glm::translate(glm::mat4(1.0f), trans) * glm::rotate(glm::mat4(1.0f), angle, vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), scale);
    mesh.draw(model, angle, camera, light);
}

void game_object::change_trans(vec3 t)
{
    trans = t;
}

vec3 game_object::get_trans()
{
    return trans;
}

void game_object::change_scale(vec3 s)
{
    scale = s;
}

vec3 game_object::get_scale()
{
    return scale;
}

vec3 game_object::GetLightCol()
{
    return light.GetCol();
}

void game_object::ChangeLightPos()
{
    light.ChangePos(trans);
}

int game_object::GetLightType()
{
    return light.GetType();
}

void game_object::DrawInstanced(GLfloat PosAndSize[100000], GLfloat ColorAndLight[100000], Camera camera, int n)
{

    mesh.DrawInstanced(PosAndSize, ColorAndLight, camera, n);
}


