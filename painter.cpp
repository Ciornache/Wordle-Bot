#include "painter.h"

Painter::Painter() {};

void Painter::drawSquare(int leftUpRow, int leftUpColumn, int rightDownRow, int rightDownColumn)
{
    line(leftUpRow, leftUpColumn, leftUpRow, rightDownColumn);
    line(leftUpRow, leftUpColumn, rightDownRow, leftUpColumn);
    line(rightDownRow, leftUpColumn, rightDownRow, rightDownColumn);
    line(leftUpRow, rightDownColumn, rightDownRow, rightDownColumn);
}
