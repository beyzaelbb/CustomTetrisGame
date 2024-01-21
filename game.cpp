#include "game.hpp"
#include <random>
#include <ctime>

Game::Game() {
    Music();
    init_sounds();
    srand(time(NULL));
    grid = Grid();
    grid.printGridMatrix();
    colorLs = grid.getCellColors(),
    tet_shape = {plusSign, smallSquare, cornerPiece, tallTower,zigzag, uShape, stepShape, arrowUp, doubleZigzag, pyramid};
    current_block = GetRandomTet();
    next_block = GetRandomTet(); 
    gameOver = false;  
    grid.clear_sound();  
    OpenProtal();
}


Tetriminos Game::GetRandomTet() {
    int randomIndex = rand() % tet_shape.size();
    Tetriminos tetrimino(tet_shape[randomIndex]);

    return tetrimino;
}

void Game::Draw(sf::RenderWindow& window) {
    grid.Draw(window);
    current_block.Draw(window);
    grid.DrawText(window);
    DrawScore(window);
    Preview(window);
    DrawHold(window);
    if(gameOver) {
        grid.GameOver(window);
    }
    if(!current_block.max_rotate) {
        Draw_Rotation_not_possible(window);
    }
    if(!gameOver)
        DrawPortal(window);
}

void Game::HandleInput(sf::Keyboard::Key key) {

    switch (key)
    {
    case sf::Keyboard::A:
        MoveBLockLeft();
        break;

    case sf::Keyboard::S:
        MoveBLockDown();
        UpdateScore(0, 1);
        break;

    case sf::Keyboard::D:
        MoveBLockRight();
        break;

    case sf::Keyboard::W:
        RotateBlock();
        BringTetriminoBack();
        break;
    
    case sf::Keyboard::Q:
        Hold();
        break;
    
    case sf::Keyboard::Space:
        FreeFall();
        break;
    
    case sf::Keyboard::Enter:
        if(gameOver) {
            Reset();
        }

    default:
        break;
    }
}

void Game::MoveBLockRight() {
    if(!gameOver) {
    if(current_block.position.x < 10 - current_block.shapeMatrix[0].size() && BlockFits_horizontal_R())
        current_block.Move(1, 0);

    }
}

void Game::MoveBLockDown() {
    if(!gameOver) {
    if(current_block.position.y < 20 - current_block.shapeMatrix.size() && BlockFits_vertical())
        current_block.Move(0, 1);
    else 
        EndReached();

    }
}

void Game::MoveBLockLeft() {
    if(!gameOver) {
    if(current_block.position.x > 0 && BlockFits_horizontal_L())
        current_block.Move(-1, 0);
        
    }
}

void Game::RotateBlock() {

    if(!gameOver) {
    int flag = true;
    int row = current_block.shapeMatrix.size();
    int column = current_block.shapeMatrix[0].size();

    std::vector<std::vector<int>> Temp_matrix(column, std::vector<int>(row));
    
    for(int i = 0; i < column; i++) {
        for(int j = 0; j < row; j++) {
            Temp_matrix[i][j] = current_block.shapeMatrix[j][i];
        }
    }

    for(int i = 0; i < column; i++) {
        for (int j = 0; j < row/2; j++) {
            std::swap(Temp_matrix[i][j], Temp_matrix[i][row - j - 1]);
        }   
    }

    for(int i = 0; i < Temp_matrix.size(); i++) {
        for(int j =  0; j < Temp_matrix[0].size(); j++) {
            if(Temp_matrix[i][j] != 0) {
                if(grid.is_cell_empty(i + current_block.position.y, j + current_block.position.x) == false)
                    flag = false;
                
            } 
        }
    }

    if(flag && current_block.max_rotate) {
    current_block.shapeMatrix = Temp_matrix;   
    rotate.play();
    current_block.max_rotate--;
    }
}
}

void Game::BringTetriminoBack() {
    while(current_block.position.x > 10 - current_block.shapeMatrix[0].size()) {
        MoveBLockLeft();
    }

    while(current_block.position.y > 20 - current_block.shapeMatrix.size()) {
        current_block.Move(0, -1);
    }
}

void Game::EndReached() {
    for(int i = 0; i < current_block.shapeMatrix.size(); i++) {
        for(int j =  0; j < current_block.shapeMatrix[0].size(); j++) {
            if(current_block.shapeMatrix[i][j] != 0) {
                if(grid.is_cell_empty(i + current_block.position.y, j + current_block.position.x) == false) {
                    gameOver = true;
                     music.stop();
                }
                   
            } 
        }
    }
    auto pointerColor = std::find(colorLs.begin(), colorLs.end(), current_block.color);
    for (int i = 0; i < current_block.shapeMatrix.size(); i++){
        for (int j = 0; j < current_block.shapeMatrix[0].size(); j++){
            if(current_block.shapeMatrix[i][j])
                grid.grid_matrix[i + current_block.position.y][j + current_block.position.x] = std::distance(colorLs.begin(), pointerColor);
        }
    }


                    
    current_block = next_block;
    next_block = GetRandomTet();
    int cleared_rows = grid.ClearFullRows();
    UpdateScore(cleared_rows, 0);
}

bool Game::BlockFits_vertical() {
    for(int i = 0; i < current_block.shapeMatrix.size(); i++) {
        for(int j =  0; j < current_block.shapeMatrix[0].size(); j++) {
            if(current_block.shapeMatrix[i][j] != 0) {
                if(grid.is_cell_empty(i + 1 + current_block.position.y, j + current_block.position.x) == false)
                    return false;
                if(current_block.position.x + j == RandomColumn && current_block.position.y + i == RandomRow) {
                        OpenProtal();
                        FreeFall();
                        return false;
                }
                
            } 
        }
    }
    return true;
} 


bool Game:: BlockFits_horizontal_R() {
    for(int i = 0; i < current_block.shapeMatrix.size(); i++) {
        for(int j = 0; j < current_block.shapeMatrix[0].size(); j++) {
            if(current_block.shapeMatrix[i][j] != 0) {
                if(grid.is_cell_empty(i + current_block.position.y, j + 1 + current_block.position.x) == false)
                return false;
            }
        }
    }
    return true;
}

bool Game:: BlockFits_horizontal_L() {
    for(int i = 0; i < current_block.shapeMatrix.size(); i++) {
        for(int j = 0; j < current_block.shapeMatrix[0].size(); j++) {
            if(current_block.shapeMatrix[i][j] != 0) {
                if(grid.is_cell_empty(i + current_block.position.y, j  - 1 + current_block.position.x) == false)
                return false;
            }
        }
    }
    return true;
}

void Game::Reset() {
    grid.initialize();
    tet_shape = {plusSign, smallSquare, cornerPiece, tallTower,zigzag, uShape, stepShape, arrowUp, doubleZigzag, pyramid};
    current_block = GetRandomTet();
    next_block = GetRandomTet();
    score = 0; 
    Music();
    is_holding = false;
    grid.game_speed = 400;
    gameOver = false;

}


void Game::UpdateScore(int linesCleared, int MoveDownPoints) {
    switch(linesCleared) {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3: 
            score += 500;
            break;
        default:
            break; 
    }

    score += MoveDownPoints; 
}


void Game::DrawScore(sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile("source/fonts/04B_20__.TTF");

    char scoreText[10];
    snprintf(scoreText, sizeof(scoreText), "%d", score);
    sf::Text gameScoreText(scoreText, font, 20);

    int scoreWidth = gameScoreText.getLocalBounds().width;
    int scoreHeight = gameScoreText.getLocalBounds().height;

    gameScoreText.setPosition(10 + ((180 - scoreWidth) / 2), 60 + ((50 - scoreHeight) / 2));

    gameScoreText.setFillColor(sf::Color::Red);

    window.draw(gameScoreText);
}

void Game::Preview(sf::RenderWindow& window) {

    int num_rows = next_block.shapeMatrix.size();
    int num_columns = next_block.shapeMatrix[0].size();
    
    for(int row = 0; row < num_rows; row++) {
        for(int column = 0; column < num_columns; column++) {
            int cellvalue = next_block.shapeMatrix[row][column];
            if(cellvalue){
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(grid.cell_size - 1, grid.cell_size - 1 ));
            rectangle.setPosition(520 + ((180 - num_columns * grid.cell_size) / 2 ) + column * grid.cell_size, 230 + ((180 - num_rows * grid.cell_size) / 2 ) + row * grid.cell_size);
            rectangle.setFillColor(next_block.color);
            
            window.draw(rectangle);
            }

        }
    }
}


void Game::Music() {
    music.openFromFile("source/audio/soundtrack.wav");
    music.play();
    music.setLoop(true);
}

void Game::init_sounds() {
    buffer.loadFromFile("source/audio/beep.wav");
    rotate.setBuffer(buffer);

}

void Game::Draw_Rotation_not_possible(sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile("source/fonts/04B_20__.TTF");

    sf::Text warning("Rotation limit \n   exceeded!", font, 10);
    warning.setPosition(10, 550);
    warning.setFillColor(sf::Color::Red);

    window.draw(warning);

}

void Game::Hold() {
    if(current_block.max_hold > 0 && !gameOver) {
        if(!is_holding) {
        holdBlock = current_block;
        current_block = next_block;
        next_block = GetRandomTet();
        is_holding = true;
        current_block.max_hold--;
    }   
    else {
        Tetriminos block_unhold = holdBlock;
        holdBlock = current_block;
        current_block = block_unhold;
        current_block.max_hold--;
    } 
} 

}

void Game::DrawHold(sf::RenderWindow& window) {
    if(is_holding) {
    int num_rows = holdBlock.shapeMatrix.size();
    int num_columns = holdBlock.shapeMatrix[0].size();

    for(int row = 0; row < num_rows; row++) {
        for(int column = 0; column < num_columns; column++) {
            int cellvalue = holdBlock.shapeMatrix[row][column];
            if(cellvalue){
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(grid.cell_size - 1, grid.cell_size - 1 ));
            rectangle.setPosition(10 + ((180 - num_columns * grid.cell_size) / 2 ) + column * grid.cell_size, 230 + ((180 - num_rows * grid.cell_size) / 2 ) + row * grid.cell_size);
            rectangle.setFillColor(holdBlock.color);
            
            window.draw(rectangle);
            }

        }
    }

    }

}

void Game::FreeFall() {
    int cnt = 0;
    while(BlockFits_vertical()) {
        cnt++;
        MoveBLockDown();
    }
    UpdateScore(0, cnt);
}

void Game::OpenProtal() {
    RandomRow = rand() % 10 + 5;
    RandomColumn = rand() % 9 + 1;
    while(grid.grid_matrix[RandomRow][RandomColumn] != 0) {
        RandomRow = rand() % 10 + 5;
        RandomColumn = rand() % 9 + 1;
    }

}


void Game::DrawPortal(sf::RenderWindow& window) {
    sf::RectangleShape portal;
    portal.setSize({30, 30});
    portal.setPosition({static_cast<float>(200 + 30*(RandomColumn)), static_cast<float>(10 + 30*(RandomRow+1))});
    portal.setFillColor(sf::Color::Green);
    window.draw(portal);
}



