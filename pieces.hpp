#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "board.hpp"

enum tetrimino_enum {
    plusSign,
    smallSquare,
    cornerPiece,
    tallTower,
    zigzag,
    uShape,
    stepShape,
    arrowUp,
    doubleZigzag,
    pyramid
};

class Tetriminos 
{
private:    
    sf::Vector2i position;
    std::vector<std::vector<int>> shapeMatrix;
    sf::Color color;
    int cell_size;
    friend class Game;

public:
    int max_hold = 3;
    int max_rotate = 5;
    Tetriminos(tetrimino_enum tet_shape);
    Tetriminos();

    void Draw(sf::RenderWindow& window);

    void Move(int rows, int columns);

    

};
