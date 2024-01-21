#include "pieces.hpp"

Tetriminos::Tetriminos() {

}

Tetriminos::Tetriminos(tetrimino_enum tet_shape) {
    position = {3, 0};
    

    Grid temp_grid;
    std::vector<sf::Color> colors_list = temp_grid.getCellColors();
    cell_size = temp_grid.cell_size;

        switch (tet_shape)
    {
        case plusSign:
        shapeMatrix =  {{0, 1, 0},
                        {1, 1, 1},
                        {0, 1, 0}};
        color = colors_list[plusSign + 1];
        this->position.x += 3 - shapeMatrix[0].size();

        break;

        case smallSquare:
        shapeMatrix =  {{1, 1},
                        {1, 1},};
        color = colors_list[smallSquare + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case cornerPiece:
        shapeMatrix =  {{1, 0},
                        {1, 1}};
        color = colors_list[cornerPiece + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case tallTower:
        shapeMatrix =  {{1},
                        {1},
                        {1}};
        color = colors_list[tallTower + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case zigzag:
        shapeMatrix =  {{0, 1, 1},
                        {1, 1, 0}};
        color = colors_list[zigzag + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case uShape:
        shapeMatrix =  {{1, 0, 1},
                        {1, 1, 1}};
        color = colors_list[uShape + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case stepShape:
        shapeMatrix =  {{0, 1},
                        {1, 1},
                        {1, 0}};
        color = colors_list[stepShape + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case arrowUp:
        shapeMatrix =  {{0, 1, 0},
                        {1, 1, 1},
                        {1, 0, 1}};
        color = colors_list[arrowUp + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case doubleZigzag:
        shapeMatrix =  {{1, 0, 0},
                        {1, 1, 1},
                        {0, 0, 1}};
        color = colors_list[doubleZigzag + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case pyramid:
        shapeMatrix =  {{0, 1, 0},
                        {1, 1, 1}};
        color = colors_list[pyramid + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

    default:
        break;
    }
}


void Tetriminos::Draw(sf::RenderWindow& window)
{
    for(int row = 0; row < shapeMatrix.size(); row++)
    {
        for(int col = 0; col < shapeMatrix[0].size(); col++)
        {
            int cellColorVal = shapeMatrix[row][col];
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(cell_size - 1, cell_size - 1));
            cell.setPosition((col + position.x) * cell_size + 201, (row + position.y) * cell_size + 11);
            if(cellColorVal != 0)
            {
            cell.setFillColor(this->color);
            }else
            {
                continue;
            }

            window.draw(cell);

        }
    }
    
}

void Tetriminos::Move(int x, int y) { // row and column offset gives the amount shift the matrix for  
    this->position.x += x;
    this->position.y += y;
    
}



