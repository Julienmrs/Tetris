#include "camera.h"
#include <cmath>

Camera::Camera(glm::vec3 target, float distance)
    : Target(target), Distance(distance), Angle(0.0f), Up(0.0f, 1.0f, 0.0f)
{
    Position = Target + glm::vec3(0.0f, 0.0f, Distance);
}

// Option pour montrer le côté 3D du tetris
void Camera::Update(float deltaTime)
{
    Angle += deltaTime/2;
    if (Angle > 2 * glm::pi<float>()) Angle -= 2 * glm::pi<float>();

    Position.x = Target.x + Distance * cos(Angle);
    Position.z = Target.z + Distance * sin(Angle);
    Position.y = Target.y + Distance * 0.3f;
}

glm::mat4 Camera::GetViewMatrix() const
{

    return glm::lookAt(Position, Target, Up);
}
