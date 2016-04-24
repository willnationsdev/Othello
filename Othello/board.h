#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include "graphic.h"
#include <cmath>

const int COLLINE0 = 0;
const int COLLINE1 = 80;
const int COLLINE2 = 160;
const int COLLINE3 = 240;
const int COLLINE4 = 320;
const int COLLINE5 = 400;
const int COLLINE6 = 480;
const int COLLINE7 = 560;
const int COLLINE8 = 639;
const int ROWLINE0 = 0;
const int ROWLINE1 = 60;
const int ROWLINE2 = 120;
const int ROWLINE3 = 180;
const int ROWLINE4 = 240;
const int ROWLINE5 = 300;
const int ROWLINE6 = 360;
const int ROWLINE7 = 420;
const int ROWLINE8 = 479;


class board:public graphic
{
    private:
        //int rows;
        //int cols;
        //int **data;


    public:
        board();
        void drawLine(int startX, int stopX, int startY, int stopY, int color);
        void drawRectangle(int x, int y);
        void drawCircle(int row, int col, int color);
};

board::board()
{
    for( int i = 64; i <= 64*8; i+=64)
    {
        for( int j = 48; j <= 48*8; j+=48)
        {
            drawRectangle(i,j);
        }
    }

    for(int a = 64; a <= 64*8; a+=64)
    {
        drawLine(a,a,48,432,0x007700);
    }

    for(int b = 48; b <= 48*8; b+=48)
    {
        drawLine(64,576,b,b,0x007700);
    }

    drawCircle(3,3,0xffffff);
    drawCircle(4,4,0xffffff);
 	drawCircle(3,4,0x000000);
    drawCircle(4,3,0x000000);

}

void board::drawLine(int startX, int stopX, int startY, int stopY, int color = 0x007700)
{
    //clear();
    if(startX == stopX)
    {
        for(int i = startY; i < stopY; i++)
        {
            plotPixel(startX, i, color);
        }
    }

    if(startY == stopY)
    {
        for(int i = startX; i < stopX; i++)
        {
            plotPixel(i, startY, color);
        }
    }
    update();
}

void board::drawRectangle(int x, int y)//coordinates of the top left corner
{
    //clear();
    for(int i = x; i < x+64; i++)
    {
        drawLine(i,i,y,y+48,0xddbb00);
    }
    update();
}

void board::drawCircle(int row, int col, int color)
{
    const int r = 22;
    int centerX = 64 + col*64 + 32;
    int centerY = 48 + row*48 + 24;
    for(int i = r; i >= 0; i--)
    {
        drawLine(centerX - sqrt(r*r - ((r-i)*(r-i))),
                 centerX + sqrt(r*r - ((r-i)*(r-i))),
                 centerY+r-i, centerY+r-i,color);
    }

    for(int i = r; i >= 0; i--)
    {
        drawLine(centerX - sqrt(r*r - ((r-i)*(r-i))),
                 centerX + sqrt(r*r - ((r-i)*(r-i))),
                 centerY-r+i, centerY-r+i, color);
    }

}


#endif // BOARD_H_INCLUDED
