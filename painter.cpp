#include "painter.h"

Painter::Painter() {};

void Painter::drawSquare(int leftUpRow, int leftUpColumn, int rightDownRow, int rightDownColumn)
{
    line(leftUpRow, leftUpColumn, leftUpRow, rightDownColumn);
    line(leftUpRow, leftUpColumn, rightDownRow, leftUpColumn);
    line(rightDownRow, leftUpColumn, rightDownRow, rightDownColumn);
    line(leftUpRow, rightDownColumn, rightDownRow, rightDownColumn);
}

void Painter::printMessage(char message[], int height, int width, char font[], int x, int y, int size)
{

    HFONT hFont=CreateFont(height,width,0,0,0,0,0,0,1,0,0,0,0,TEXT("Arial"));
    HDC hDC=BGI__GetWinbgiDC();
    DeleteObject(SelectObject(hDC,hFont));
    BGI__ReleaseWinbgiDC(NULL);

    outtextxy(x, y, message);
}
