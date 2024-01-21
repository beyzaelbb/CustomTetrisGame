#pragma once
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "board.hpp"
#include "pieces.hpp"
#include <SFML/Audio.hpp>


class Game {
private:
    std::vector<tetrimino_enum> tet_shape;
    Tetriminos current_block;
    Tetriminos next_block;
    std::vector<sf::Color> colorLs;
    sf::Music music;
    sf::Sound rotate;
    sf::SoundBuffer buffer;
    bool is_holding = false;
    Tetriminos holdBlock;
   
     
public:
    Game();
    Grid grid;
    bool gameOver;
    Tetriminos GetRandomTet();
    void Draw(sf::RenderWindow& window);
    void HandleInput(sf::Keyboard::Key key);
    void MoveBLockLeft();
    void MoveBLockRight();
    void MoveBLockDown();
    void RotateBlock(); 
    void BringTetriminoBack();
    void EndReached();
    bool BlockFits_vertical();     
    bool BlockFits_horizontal_R();
    bool BlockFits_horizontal_L();
    void Reset();
    int score;
    void UpdateScore(int linesCleared, int MoveDownPoints);
    void DrawScore(sf::RenderWindow& window);
    void Preview(sf::RenderWindow& window);
    void Music();
    void init_sounds();
    void Draw_Rotation_not_possible(sf::RenderWindow& window);
    void Hold();
    void DrawHold(sf::RenderWindow& window);
    void FreeFall();   
    void OpenProtal(); 
    void DrawPortal(sf::RenderWindow& window);
    int RandomRow;
    int RandomColumn;

};


