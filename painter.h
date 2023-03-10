#ifndef H_PAINTER
#define H_PAINTER

#include <graphics.h>
#include "configs\graphicUtilities.h"
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>

class Painter
{
public:
    Painter();
    friend class Table;

private:
    void drawSquare(int leftUpRow, int leftUpColumn, int rightDownRow, int rightDownColumn);
    void printMessage(char message[], int height, int width, char font[], int x, int y, int size);
};



#endif // H_PAINTER
