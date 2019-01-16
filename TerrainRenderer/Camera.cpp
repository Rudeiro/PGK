#include "Camera.hpp"

vec3 Camera::GetWorldPos()
{
    return WorldPos;
}
void Camera::ChangeWorldPos(vec3 NewWorldPos)
{
    WorldPos = NewWorldPos;
}
vec3 Camera::GetLookDir()
{
    return LookDir;
}
void Camera::ChangeLookDir(vec3 NewLookDir)
{
    LookDir = NewLookDir;
}
vec3 Camera::GetUpVec()
{
    return UpVec;
}
void Camera::ChangeUpVec(vec3 NewUpVec)
{
    UpVec = NewUpVec;
}
glm::mat4 Camera::View()
{
    return glm::lookAt(WorldPos, LookDir, UpVec);
}

void Camera::setLTLN_POS(float lt, float ln)
{
    LTLN_POS = vec2(lt, ln);
}

vec2 Camera::getLTLN_POS()
{
    return LTLN_POS;
}
