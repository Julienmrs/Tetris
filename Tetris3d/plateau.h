#ifndef PLATEAU_H
#define PLATEAU_H

#include <vector>
#include <glm/glm.hpp>
#include "cube.h"
#include "shader.h"
#include "tetromino.h"

class Plateau {
public:
    Plateau(int L, int P, int H, const glm::vec3& borderColor = glm::vec3(0.2f,0.2f,0.8f));

    void Draw(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const;

    bool isInside(int x, int y, int z) const;
    bool isOccupied(int x, int y, int z) const;

    void lockTetromino(const Tetromino& t);

    Tetromino spawnTetromino() const;

    int getWidth()  const { return L; }
    int getDepth()  const { return P; }
    int getHeight() const { return H; }
    bool canPlace(const Tetromino& t) const;

    glm::vec3 gridToWorld(int x, int y) const;

    // Gestion des lignes
    bool isLineFull(int y) const;     // teste si ligne y est pleine
    void clearLine(int y);            // supprime une ligne et fait descendre celles au-dessus
    void clearFullLines();            // supprime toutes les lignes pleines

    // Gestion du score
    int getscore(){return score;}
    void scoreup(){score += L - 2;}
private:
    int L, P, H; // largeur (x), profondeur (z), hauteur (y)
    int score;

    // grille stockant les cases occupées [x][y][z]
    std::vector<std::vector<std::vector<bool>>> grid;

    std::vector<std::vector<std::vector<glm::vec3>>> colorGrid;

    std::vector<Cube> cadre;

    // blocs verrouillés
    std::vector<Cube> fixedBlocks;

    glm::vec3 borderColor;

    void initGrid();
    void buildFrame(const glm::vec3& color);
    void rebuildFixedBlocks();
};

#endif
