#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 target, float distance);

    // Met à jour la position selon le temps
    void Update(float deltaTime);

    // Retourne la matrice de vue
    glm::mat4 GetViewMatrix() const;

private:
    glm::vec3 Target;   // Point autour duquel on orbite
    float Distance;     // Distance par rapport au cube
    float Angle;        // Angle courant autour du cube
    glm::vec3 Position; // Position calculée de la caméra
    glm::vec3 Up;
};

#endif
