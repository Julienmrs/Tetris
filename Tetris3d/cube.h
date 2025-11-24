#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ctime>
#include <cstdlib>

#include "shader.h"

class Cube {
public:
    Cube(const glm::vec3& position, const glm::vec3& color = randomColor(), float size = 1.0f);
    ~Cube();

    void Draw(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const;
    void SetColor(const glm::vec3& newColor);

    static glm::vec3 randomColor();

private:
    GLuint VAO, VBO, EBO;
    glm::vec3 position;
    glm::vec3 color;
    float size;

    void setupCube();
};

#endif
