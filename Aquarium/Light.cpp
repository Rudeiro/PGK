#include "Light.hpp"

vec3 Light::GetPos()
{
    return position;
}
vec3 Light::GetCol()
{
    return color;
}


void Light::ChangePos(vec3 NewPos)
{
    position = NewPos;
}

int Light::GetType()
{
    return type;
}
