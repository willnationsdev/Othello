#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED
#include "SDL/SDL.h"

const int VOID = 0;
const int WHITE = 1;
const int BLACK = 2;

class Cell
{
    private:
        SDL_Rect rect;
        bool p1valid;
        bool p2valid;
        int tile;

    public:
        Cell();
        Cell(int x, int y);
        bool getp1V() {return p1valid;}
        bool getp2V() {return p2valid;}
        int getTile() {return tile;}
        void setp1V(bool x) {p1valid = x;}
        void setp2V(bool x) {p2valid = x;}
        void setTile(int x) {tile = x;}
        bool isVoid() {if(tile == VOID) return true;}
        bool isBlack() {if(tile == BLACK) return true;}
        bool isWhite() {if(tile == WHITE) return true;}

};

Cell::Cell()
{
    rect.x = 64;
    rect.y = 48;
    tile = VOID;
}

Cell::Cell(int x, int y)
{
    rect.x = x;
    rect.y = y;
    tile = VOID;
}



#endif // CELL_H_INCLUDED
