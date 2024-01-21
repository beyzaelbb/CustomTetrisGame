#include "board.hpp"

Grid::Grid() {
    num_columns = 10;
    num_rows = 20;
    cell_size = 30;
    initialize();
    colors = getCellColors();
    void clear_sound();

}

void Grid::initialize()
{
    for(int row = 0; row < num_rows; row++) {
        for(int column = 0; column < num_columns; column++) {
            grid_matrix[row][column] = 0;
        }
    }
}

void Grid::printGridMatrix() 
{
    for(int row= 0; row < num_rows; row++) {
        for(int column = 0; column < num_columns; column++) {
            std::cout << grid_matrix[row][column] << " ";
        }
        std::cout << std::endl; 
    }
}

void Grid::Draw(sf::RenderWindow& window) {
    for(int row = 0; row < num_rows; row++) {
        for(int column = 0; column < num_columns; column++) {
            int cellvalue = grid_matrix[row][column];
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(cell_size - 1, cell_size - 1 ));
            rectangle.setPosition(column * cell_size + 201, row * cell_size + 11);
            rectangle.setFillColor(colors[cellvalue]);
            window.draw(rectangle);

        }
    }

}

std::vector<sf::Color> Grid::getCellColors() {
    sf::Color gray(110, 110, 110);
    sf::Color Pink (255, 203, 164);
    sf::Color PastelBlue(173, 216, 230);
    sf::Color PastelPurple(221, 160, 221);
    sf::Color PastelGreen(144, 238, 144);
    sf::Color PastelYellow(255, 255, 224);
    sf::Color PastelOrange(255, 218, 185);
    sf::Color PastelTurquoise(175, 238, 238);
    sf::Color PastelLavender(230, 230, 250);
    sf::Color PastelPeach(255, 218, 185);
    sf::Color PastelMint(189, 252, 201);
    sf::Color PastelCoral(255, 127, 80);
    sf::Color PastelLilac(200, 162, 200);
    sf::Color PastelSalmon(250, 128, 114);

    return {gray, Pink, PastelBlue, PastelPurple, PastelGreen, PastelYellow, PastelOrange, PastelTurquoise, PastelLavender, PastelPeach, PastelMint, PastelCoral, PastelLilac, PastelSalmon};
}


bool Grid::is_cell_empty(int row, int column) {
    if(grid_matrix[row][column] == 0) {
        return true;
    }
    return false;
}

bool Grid::is_row_full(int row) {
    for(int column = 0; column < num_columns; column++) {
        if(grid_matrix[row][column] == 0) {
            return false;
        }
    }
    return true; 
}

void Grid::clear_row(int row) {
    for(int column = 0; column < num_columns; column++) {
        grid_matrix[row][column] = 0;
    }
    rows_cleared++;    
    game_speed -= 40;
}

void Grid::MoveRowDown(int row, int num) {
    for(int column = 0; column < num_columns; column++) {
        grid_matrix[row + num][column] = grid_matrix[row][column];
        grid_matrix[row][column] = 0;
    }
 }

 int Grid::ClearFullRows() {
    int completed = 0;

    for(int row = num_rows - 1; row >= 0; row--) {
        if(is_row_full(row)) {
            clear_row(row);
            completed++;
            clear.play();
        }
        else if(completed > 0) {
            MoveRowDown(row, completed);
        }
    } 
    return completed;
 }


void Grid::DrawText(sf::RenderWindow& window) {
    
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(180, 50));
    rectangle.setFillColor(sf::Color(135, 206, 250));
    rectangle.setPosition(10, 60);
    
    sf::RectangleShape rec2;
    rec2.setSize(sf::Vector2f(180, 180));
    rec2.setPosition(10, 230);
    rec2.setFillColor(sf::Color(135, 206, 250));
    
    sf::RectangleShape rec3;
    rec3.setSize(sf::Vector2f(180, 180));
    rec3.setFillColor(sf::Color(135, 206, 250));
    rec3.setPosition(520, 230);

    sf::Font font;
    font.loadFromFile("source/fonts/04B_20__.TTF");

    sf::Text text_score("Score", font, 20);
    text_score.setPosition(30, 30);
    text_score.setFillColor(sf::Color(0, 0, 130));

    sf::Text text_hold("Hold", font, 20);
    text_hold.setPosition(30, 200);
    text_hold.setFillColor(sf::Color(0, 0, 130));
    
    sf::Text text_preview("Preview", font, 20);
    text_preview.setPosition(520, 200);
    text_preview.setFillColor(sf::Color(0, 0, 130));

    sf::Text controls("A S D - control \n W - rotate \n Q - hold", font, 10);
    controls.setPosition(520, 520);
    controls.setFillColor(sf::Color::Black);

    window.draw(rectangle);
    window.draw(text_score);
    window.draw(rec2);
    window.draw(text_hold);
    window.draw(rec3);
    window.draw(text_preview);
    window.draw(controls);

}
 

void Grid::GameOver(sf::RenderWindow& window) {
    sf::RectangleShape rec;
    rec.setSize(sf::Vector2f(520, 100));
    rec.setFillColor(sf::Color::Black);
    rec.setPosition(90, 170);
    
    sf::Font font;
    font.loadFromFile("source/fonts/04B_20__.TTF");

    sf::Text Game_over_text("GAME OVER", font, 40);
    Game_over_text.setPosition(120, 200);
    Game_over_text.setFillColor(sf::Color::Red);

    sf::Text restart_txt("ENTER TO RESTART", font, 8);
    restart_txt.setPosition(10, 500);
    restart_txt.setFillColor(sf::Color::Red);

    window.draw(rec);
    window.draw(Game_over_text);
    window.draw(restart_txt);


}

void Grid::clear_sound() {
    buffer.loadFromFile("source/audio/clear.wav");
    clear.setBuffer(buffer);
}
