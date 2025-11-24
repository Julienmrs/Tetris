#include "tetromino.h"
#include <cstdlib>
#include <ctime>

static void aleatoire() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
}

glm::vec3 Tetromino::randomColor() {
    aleatoire();
    return glm::vec3(
        static_cast<float>(std::rand()) / RAND_MAX,
        static_cast<float>(std::rand()) / RAND_MAX,
        static_cast<float>(std::rand()) / RAND_MAX
        );
}

Tetromino::Tetromino(TetrominoType t, const glm::ivec3& spawnPos)
    : type(t), pos(spawnPos), color(randomColor())
{
    initShape(t);
}

Tetromino Tetromino::randomTetromino(const glm::ivec3& spawnPos) {
    aleatoire();
    int r = std::rand() % 7;
    return Tetromino(static_cast<TetrominoType>(r), spawnPos);
}

void Tetromino::initShape(TetrominoType t) {
    cells.clear();

    switch (t) {
    case TetrominoType::I:
        cells = { {0,1,0}, {0,0,0}, {0,-1,0}, {0,-2,0} };
        break;
    case TetrominoType::O:
        cells = { {0,0,0}, {1,0,0}, {0,-1,0}, {1,-1,0} };
        break;
    case TetrominoType::T:
        cells = { {0,0,0}, {-1,0,0}, {1,0,0}, {0,-1,0} };
        break;
    case TetrominoType::L:
        cells = { {0,0,0}, {0,-1,0}, {0,-2,0}, {1,0,0} };
        break;
    case TetrominoType::J:
        cells = { {0,0,0}, {0,-1,0}, {0,-2,0}, {-1,0,0} };
        break;
    case TetrominoType::S:
        cells = { {0,0,0}, {1,0,0}, {0,-1,0}, {-1,-1,0} };
        break;
    case TetrominoType::Z:
        cells = { {0,0,0}, {-1,0,0}, {0,-1,0}, {1,-1,0} };
        break;
    }
}

void Tetromino::moveDown() {
    pos.y -= 1;
}

void Tetromino::moveBy(const glm::ivec3& d) {
    pos += d;
}

std::vector<glm::ivec3> Tetromino::getBlocks() const {
    std::vector<glm::ivec3> out;
    out.reserve(cells.size());
    for (const auto& c : cells)
        out.emplace_back(pos + c);
    return out;
}
