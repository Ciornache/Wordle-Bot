#include "table.h"

Table::Table() {};

void Table::init()
{
    initwindow(WINDOW_HEIGHT, WINDOW_WIDTH, "WORDLE_BOT");
    initGrid();
}

void Table::refresh()
{
    initGrid();
}

void Table::initGrid()
{
    if(coord[1].size() > 0)
    {
        for(int row = 1; row <= NUMBER_OF_ROWS; ++row)
        {
            for(int column = 1; column <= NUMBER_OF_COLUMNS; ++column)
                readimagefile("assets/background.jpg", coord[row][column - 1].x1, coord[row][column - 1].y1, coord[row][column - 1].x2, coord[row][column - 1].y2);
        }
    }

    for(int row = 1; row <= NUMBER_OF_ROWS; ++row)
    {
        coord[row].clear();
        for(int column = 1; column <= NUMBER_OF_COLUMNS; ++column)
        {
            painter.drawSquare(START_X + (column - 1) * (SQUARE_SIZE + MARGIN), START_Y + (row - 1) * (SQUARE_SIZE + MARGIN),
                               START_X + column * SQUARE_SIZE + (column - 1) * MARGIN, START_Y + row * SQUARE_SIZE + (row - 1) * MARGIN);

            coord[row].push_back({START_X + (column - 1) * (SQUARE_SIZE + MARGIN),
                                  START_Y + (row - 1) * (SQUARE_SIZE + MARGIN),
                                  START_X + column * SQUARE_SIZE + (column - 1) * MARGIN,
                                  START_Y + row * SQUARE_SIZE + (row - 1) * MARGIN});
        }
    }
}

void Table::place(int round, std::string word)
{
    int count = 0;
    std::ifstream tin ("configs\letters.txt");
    std::string green, yellow, gray;
    getline(tin, green), getline(tin, yellow), getline(tin, gray);
    for(auto letter : word)
    {
        char path[PATH_SIZE] = {0}, let[2] = {0};
        strcat(path, "assets/");
        let[0] = letter - 'a' + 'A', let[1] = '\0';

        bool isGreen = false;
        for(int index = 6; index < green.size(); ++index)
            isGreen |= (green[index] == letter);
        if(isGreen)
            strcat(path, "greenLetters/");

        bool isYellow = false;
        for(int index = 7; index < yellow.size(); ++index)
            isYellow |= (yellow[index] == letter);

        if(!isGreen)
        {
            if(isYellow)
                strcat(path, "yellowLetters/");
            else
                strcat(path, "grayLetters/");
        }
        strcat(path, let);
        strcat(path, ".jpg");
//        std::cout << path << '\n';
        readimagefile(path, coord[round][count].x1, coord[round][count].y1, coord[round][count].x2, coord[round][count].y2);
        count++;
    }
    tin.close();
}
