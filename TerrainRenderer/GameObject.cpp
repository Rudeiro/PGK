
#include "GameObject.hpp"


GameObject::GameObject(vec3 trans, vec3 scale, Mesh mesh)
                : trans (trans),
                  scale (scale),
                   mesh (mesh)
                   
                {}

void GameObject::draw(Camera camera)
{
    mat4 model = glm::translate(glm::mat4(1.0f), trans) * glm::scale(glm::mat4(1.0f), scale);
    mesh.draw(model, camera);
}

void GameObject::change_trans(vec3 t)
{
    trans = t;
}

vec3 GameObject::get_trans()
{
    return trans;
}

void GameObject::change_scale(vec3 s)
{
    scale = s;
}

vec3 GameObject::get_scale()
{
    return scale;
}



