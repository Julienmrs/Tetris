#include "cube.h"

Cube::Cube(const glm::vec3& position, const glm::vec3& color, float size)
    : position(position), color(color), size(size)
{

    setupCube();
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

glm::vec3 Cube::randomColor() {
    return glm::vec3(
        (rand() % 100) / 100.0f,
        (rand() % 100) / 100.0f,
        (rand() % 100) / 100.0f
        );
}

void Cube::SetColor(const glm::vec3& newColor)
{
    color = newColor;
}

void Cube::setupCube()
{
    float half = size / 2.0f;

    float vertices[] = {
        // Positions
        -half, -half, -half,
        half, -half, -half,
        half,  half, -half,
        -half,  half, -half,
        -half, -half,  half,
        half, -half,  half,
        half,  half,  half,
        -half,  half,  half
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,   // face arrière
        4, 5, 6, 6, 7, 4,   // face avant
        0, 4, 7, 7, 3, 0,   // face gauche
        1, 5, 6, 6, 2, 1,   // face droite
        3, 2, 6, 6, 7, 3,   // face haut
        0, 1, 5, 5, 4, 0    // face bas
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
}

void Cube::Draw(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const
{
    shader.Bind();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    shader.setUniformMat4f("model", model);
    shader.setUniformMat4f("view", view);
    shader.setUniformMat4f("projection", projection);
    shader.setUniform3fv("objectColor", color);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
