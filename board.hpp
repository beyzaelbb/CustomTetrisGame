#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <optional>


class Grid {
public:
    Grid();
    int grid_matrix[20][10];
    void initialize();
    void printGridMatrix();
    void Draw(sf::RenderWindow& window);
    bool is_cell_empty(int row, int column);
    int ClearFullRows();
    void DrawText(sf::RenderWindow& window);
    void GameOver(sf::RenderWindow& window);
    void clear_sound();
    int rows_cleared = 0;
    int game_speed = 400;


private:
    std::optional<sf::Sound> clear;
    sf::SoundBuffer buffer;
    bool is_row_full(int row);
    void clear_row(int row);
    void MoveRowDown(int row, int num_rows);
    std::vector<sf::Color> getCellColors();
    int num_rows;
    int num_columns;
    int cell_size;
    std::vector<sf::Color> colors;

    friend class Tetriminos;
    friend class Game;
};