#ifndef H_TABLE
#define H_TABLE

#include "painter.h"


class Table
{
    struct image
    {
        int x1, y1;
        int x2, y2;
    };

public:
    Table();
    void init();
    void place(int round, std::string word);
    void refresh();
    void message(char message[], int height, int width, char font[], int x, int y, int size);

private:
    Painter painter;
    void initGrid();
    std::vector <Table::image> coord[NUMBER_OF_ROWS + 1];
};



#endif // H_TABLE
