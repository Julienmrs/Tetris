#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "cube.h"
#include "shader.h"
#include "camera.h"
#include "plateau.h"
#include "game.h"

int main() {

    // Init GLFW
    if (!glfwInit()) {
        std::cerr << "Erreur: GLFW init failed\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Tetris3D", nullptr, nullptr);
    if (!window) return -1;

    glfwMakeContextCurrent(window);

    // GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Erreur: GLEW init failed\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // SHADER
    Shader shader("../../shaders/vertex.glsl",
                  "../../shaders/fragment.glsl");

    // MATRICES
    glm::mat4 projection =
        glm::perspective(glm::radians(45.f), 800.f/600.f, 0.1f, 100.f);

    glm::mat4 view =
        glm::lookAt(glm::vec3(10, 15, 25),
                    glm::vec3(5, 7, 0),
                    glm::vec3(0, 1, 0));

    // PLATEAU + GAME
    Plateau plateau(10, 2, 20, glm::vec3(0.6f));
    Game game(plateau);

    float last = glfwGetTime();

    std::cout << "Boucle de jeu lancée." << std::endl;

    // MAIN LOOP
    while (!glfwWindowShouldClose(window)) {

        float now = glfwGetTime();
        float dt = now - last;
        last = now;

        game.update(dt);

        // INPUTS
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            game.onKeyPressed(GLFW_KEY_LEFT);

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            game.onKeyPressed(GLFW_KEY_RIGHT);

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            game.onKeyPressed(GLFW_KEY_DOWN);

        glClearColor(0.1f, 0.15f, 0.25f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        shader.setUniformMat4f("view", view);
        shader.setUniformMat4f("projection", projection);

        game.draw(shader, view, projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
