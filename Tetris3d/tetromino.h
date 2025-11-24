#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>
#include <glm/glm.hpp>
#include "cube.h"

enum class TetrominoType { I, O, T, L, J, S, Z };

class Tetromino {
public:
    Tetromino(TetrominoType type, const glm::ivec3& spawnPos);
    static Tetromino randomTetromino(const glm::ivec3& spawnPos);

    std::vector<glm::ivec3> getBlocks() const;

    void moveDown();
    void moveBy(const glm::ivec3& d);
    const std::vector<glm::ivec3>& getBlockPositions() const { return cells; }
    glm::vec3 getColor() const { return color; }
    TetrominoType getType() const { return type; }
    glm::vec3 color;
private:
    TetrominoType type;
    std::vector<glm::ivec3> cells;
    glm::ivec3 pos;


    void initShape(TetrominoType t);
    static glm::vec3 randomColor();
};

#endif
