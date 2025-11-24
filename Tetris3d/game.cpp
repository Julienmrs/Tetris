#include "game.h"
#include <cstdlib>

Game::Game(Plateau& p)
    : plateau(p), active(nullptr), fallTimer(0.f), fallInterval(0.7f) , score(0)
{
    spawnNew();
}

void Game::spawnNew() {
    int x = plateau.getWidth() / 2;
    int y = plateau.getHeight() - 3; // top

    active = std::make_unique<Tetromino>(
        Tetromino::randomTetromino(glm::ivec3(x, y, 0))
        );

    if (!plateau.canPlace(*active)) {
        std::cout << "GAME OVER \n";
        std::cout << "Tu as effacé " << plateau.getscore()<<" cube(s)"<<std::endl;
        game_alive = false ;
    }
}

void Game::update(float dt) {
    fallTimer += dt;
    horizontalTimer += dt;

    if (fallTimer >= fallInterval && game_alive) {
        fallTimer = 0.5;

        if (!tryMoveActive(glm::ivec3(0, -1, 0))) {

            lockActive();

            plateau.clearFullLines();

            spawnNew();
        }
    }
}

bool Game::tryMoveActive(const glm::ivec3& delta) {
    if (!active) return false;

    Tetromino copy = *active;
    copy.moveBy(delta);

    if (plateau.canPlace(copy)) {
        active->moveBy(delta);
        return true;
    }
    return false;
}

void Game::lockActive() {
    if (!active) return;

    plateau.lockTetromino(*active);
    active.reset();
}

void Game::onKeyPressed(int key) {
    if (!active) return;

    if (horizontalTimer >= horizontalInterval) {
        if (key == GLFW_KEY_LEFT) {
            tryMoveActive(glm::ivec3(-1,0,0));
            horizontalTimer = 0.f;
        }
        else if (key == GLFW_KEY_RIGHT) {
            tryMoveActive(glm::ivec3(1,0,0));
            horizontalTimer = 0.f;
        }

        else if (key == GLFW_KEY_DOWN) {
            tryMoveActive(glm::ivec3(0,-1,0));
            horizontalTimer = 0.05f;

        }
    }}

void Game::draw(const Shader& shader,
                const glm::mat4& view,
                const glm::mat4& projection)
{
    plateau.Draw(shader, view, projection);

    if (active) {
        for (auto& p : active->getBlocks()) {
            glm::vec3 world = plateau.gridToWorld(p.x, p.y);

            Cube temp(world, active->color);
            temp.Draw(shader, view, projection);
        }
    }
}
