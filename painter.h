#ifndef H_PAINTER
#define H_PAINTER

#include <graphics.h>
#include "configs\graphicUtilities.h"
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>


class Painter
{
public:
    Painter();
    void drawSquare(int leftUpRow, int leftUpColumn, int rightDownRow, int rightDownColumn);
};



#endif // H_PAINTER
