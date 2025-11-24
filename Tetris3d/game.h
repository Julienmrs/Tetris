#ifndef GAME_H
#define GAME_H

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include "plateau.h"
#include "tetromino.h"

class Game
{
public:
    Game(Plateau& p);

    void update(float dt);

    void onKeyPressed(int key);

    void draw(const Shader& shader,
              const glm::mat4& view,
              const glm::mat4& projection);


private:
    Plateau& plateau;

    std::unique_ptr<Tetromino> active;

    float fallTimer;
    float fallInterval;
    float horizontalTimer = 0.f;
    float horizontalInterval = 0.15f;  // délai avant de respawn un bloc
    void spawnNew();
    bool game_alive = true;
    int score;
    bool tryMoveActive(const glm::ivec3& delta); // Essaye de déplacer le bloc actif
    void lockActive();
};

#endif // GAME_H
