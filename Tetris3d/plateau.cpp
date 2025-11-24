#include "plateau.h"
#include <iostream>


// Initialisation / def du tableau et des tetrominos

Plateau::Plateau(int L_, int P_, int H_, const glm::vec3& color)
    : L(L_), P(P_), H(H_), borderColor(color), score(0)
{
    initGrid();
    buildFrame(color);
}


void Plateau::initGrid() {
    grid.resize(L);
    colorGrid.resize(L);
    for (int x = 0; x < L; ++x) {
        grid[x].resize(H);
        colorGrid[x].resize(H);
        for (int y = 0; y < H; ++y) {
            grid[x][y].resize(P, false);
            colorGrid[x][y].resize(P, glm::vec3(-1.0f, -1.0f, -1.0f)); // sentinel = empty
        }
    }
}

void Plateau::buildFrame(const glm::vec3& color) {
    cadre.clear();
    for (int x = 0; x < L; ++x) {
        for (int z = 0; z < P; ++z) {
            if (x == 0 || x == L - 1 || z == 0 || z == P - 1) {
                cadre.emplace_back(glm::vec3(x, 0, z), color);
            }
        }
    }
    for (int y = 1; y < H; ++y) {
        for (int z = 0; z < P; ++z) {
            cadre.emplace_back(glm::vec3(0, y, z), color);
            if (L > 1) cadre.emplace_back(glm::vec3(L - 1, y, z), color);
        }
    }
}

Tetromino Plateau::spawnTetromino() const {
    int spawnX = L / 2;
    int spawnZ = P / 2;
    int spawnY = H - 1;
    return Tetromino::randomTetromino(glm::ivec3(spawnX, spawnY, spawnZ));
}

void Plateau::Draw(const Shader& shader,
                   const glm::mat4& view,
                   const glm::mat4& projection) const
{
    for (const auto& b : fixedBlocks) b.Draw(shader, view, projection);

    for (const auto& c : cadre) c.Draw(shader, view, projection);
}


void Plateau::rebuildFixedBlocks() {
    fixedBlocks.clear();
    for (int x = 0; x < L; ++x) {
        for (int y = 0; y < H; ++y) {
            for (int z = 0; z < P; ++z) {
                if (grid[x][y][z]) {
                    glm::vec3 col = colorGrid[x][y][z];

                    if (col.x < -0.5f) col = glm::vec3(0.8f, 0.8f, 0.8f);
                    fixedBlocks.emplace_back(glm::vec3(x, y, z), col);
                }
            }
        }
    }
}

//Verification

bool Plateau::isInside(int x, int y, int z) const {
    return (x >= 0 && x < L && y >= 0 && y < H && z >= 0 && z < P);
}

bool Plateau::isOccupied(int x, int y, int z) const
{
    if (!isInside(x,y,z)) return true;
    return grid[x][y][z];
}


void Plateau::lockTetromino(const Tetromino& t)
{
    for (auto& b : t.getBlocks()) {
        if (isInside(b.x, b.y, b.z)) {
            grid[b.x][b.y][b.z] = true;
            colorGrid[b.x][b.y][b.z] = t.getColor();
        }
    }

    rebuildFixedBlocks();
    clearFullLines();
}


bool Plateau::isLineFull(int y) const
{
    if (y < 1 || y >= H) return false;
    for (int x = 1; x < L - 1; ++x) {
        if (!grid[x][y][0])
            return false;
    }
    return true;
}


bool Plateau::canPlace(const Tetromino& t) const
{
    for (auto& b : t.getBlocks()) {
        if (b.x < 1 || b.x > L - 2) return false;

        if (b.y < 1 || b.y >= H) return false;

        if (b.z < 0 || b.z >= P) return false;

        if (isOccupied(b.x, b.y, b.z)) return false;
    }
    return true;
}


void Plateau::clearLine(int y)
{
    for (int yy = y; yy < H - 1; ++yy) {
        for (int x = 0; x < L; ++x) {
            for (int z = 0; z < P; ++z) {
                grid[x][yy][z] = grid[x][yy + 1][z];
                colorGrid[x][yy][z] = colorGrid[x][yy + 1][z];
            }
        }
    }

    for (int x = 0; x < L; ++x) {
        for (int z = 0; z < P; ++z) {
            grid[x][H - 1][z] = false;
            colorGrid[x][H - 1][z] = glm::vec3(-1.0f, -1.0f, -1.0f);
        }
    }

    rebuildFixedBlocks();
}


void Plateau::clearFullLines()
{
    for (int y = 1; y < H - 1; ++y) {
        if (isLineFull(y)) {
            clearLine(y);
            scoreup();
            --y;
        }
    }
}


glm::vec3 Plateau::gridToWorld(int x, int y) const {
    return glm::vec3(x, y, 0);
}


