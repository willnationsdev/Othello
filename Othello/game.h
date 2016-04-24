#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "board.h"
#include "cell.h"
#include "SDL/SDL.h"
#include "player.h"


class game:public board
{
    private:
        Cell** cell;
        int mouseX;
        int mouseY;
    public:
        game();
        ~game();
        int getMX() {return mouseX;}
        int getMY() {return mouseY;}
        //void drawCircle(int row, int col, int color);
        bool click(int& clickedCellRow, int& clickedCellCol);//finds xy coord of mouse when left mouse button pressed, checks that it is p1's turn, checks to see if the xy coord's are within the Cell's rect, and if all true, then drawCircle
        //friend void board::drawCircle(int row, int col, int color);
        bool isSame(int originalX, int originalY, int compareX, int compareY);
        void infect(int& clickedCellRow, int& clickedCellCol);  //add halo "infected" sound effect. also do last man standing! LOL : This function is what causes a clicked on tile to change the tile-type of adjacent tiles
        void setTile(int x, int y, int z) {cell[x][y].setTile(z);}
};

game::game()
{
    cell = new Cell*[8];
    for( int i = 0; i < 8; i++)
    {
        cell[i] = new Cell[8];
    }
    mouseX = 0;
    mouseY = 0;
    cell[3][3].setTile(WHITE);
    cell[4][4].setTile(WHITE);
    cell[3][4].setTile(BLACK);
    cell[4][3].setTile(BLACK);
}

game::~game()
{
    for( int i = 0; i < 8; i++)
    {
        delete[] cell;
    }
    delete cell;
}

bool game::click(int& clickedCellRow, int& clickedCellCol)
{
    bool clicked;
    ////////////////////////////////////////////
    //Retrieved from lazyfoo.net
    ////////////////////////////////////////////

     //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            mouseX = event.button.x;
            mouseY = event.button.y;

    ////////////////////////////////////////////
    //End Usage of lazyfoo.net
    ////////////////////////////////////////////

            //Determine the current cell
            for(int i = 64; i <= 8*64; i+=64)
            {
                if(mouseX > i && mouseX < i+64)
                {
                    //Determine the column(x value) of the clicked on cell
                    clickedCellCol = (i/64)-1;
                    for(int j = 48; j <= 8*48; j+=48)
                    {
                        if(mouseY > j && mouseY < j+48)
                        {
                            //Determine the row(y value) of the clicked on cell
                            clickedCellRow = (j/48)-1;
                        }
                    }
                }
            }

             if( ( mouseX > (clickedCellRow+1)*64 ) && ( mouseX < (clickedCellRow+2)*64 ) && ( mouseY > (clickedCellCol+1)*48 ) && ( mouseY < (clickedCellCol+2)*48 ) )
            {
                clicked = true;
                /*if(cell[clickedCellRow][clickedCellCol].isWhite() && cell[destX][destY].isBlack())
                    clicked = true;*/
                //totalTurns++;
            }
        }
    }

    return clicked;

}

bool game::isSame(int sourceX, int sourceY, int destX, int destY)
{
    return cell[sourceX][sourceY].getTile() == cell[destX][destY].getTile();
}

/*bool game::isOpposite(int sourceX, int sourceY, int destX, int destY)
{
    if(cell[sourceX][sourceY].isWhite() && cell[destX][destY].isBlack())
        return true;
    else if(cell[sourceX][sourceY].isBlack() && cell[destX][destY].isWhite())
        return true;
    else
        return false;
}*/

void game::infect(int& ccRow, int& ccCol)
{
    /*
    This function checks all values to the left until encounters either
    a value equal to its starting point OR until it encounters a voided
    space. If it's a voided space, it stops searching that direction.
    If it has an equal value, then it quickly moves from the starting
    position up to the discovered equal value, changing everything in
    between to match. Then it continues searching the remaining direction
    until it arrives at the boundary of the board. It does this in all
    8 directions in order left,right,up,down,up-left,up-right,down-right
    and finally down-left.

    It's currently REALLY jumbled up because I have trouble getting my
    Rows/Columns/X's/Y's mixed up. Will need to be fixed big time.
    It's currently not standardized in that cell[int a][int b] sometimes
    means down a, right b and other times down b, right a. I'm also
    sometimes plugging in ccCol where I should be plugging in ccRow (or
    I'm putting a variable that represents one those changing values in
    the pre-arranged spot for the OTHER value in the function parameters).

    ccRow = the row number of the clicked on cell.
    ccCol = the column number of the clicked on cell.
    the int "tile" variable is used to represent the WHITE, BLACK, or
    VOID "colors" of each cell and setTile(int) is used to assign these.
    */
    bool meetVoid = false;
    //////////////////////////////////////////LEFT
    for( int i = ccCol-1; i > 0 && !meetVoid; i--)
    {
        if(isSame(ccCol, ccRow, i, ccRow))
        {
            for( int j = ccCol-1; j >= i; j--)
            {
                cell[j][ccRow].setTile( cell[ccCol][ccRow].getTile() );
                if(cell[ccCol][ccRow].isWhite())
                    drawCircle(j, ccRow, 0xffffff);
                if(cell[ccCol][ccRow].isBlack())
                    drawCircle(j, ccRow, 0x000000);
            }
        }
        if(cell[ccRow][i].isVoid())
        {
            meetVoid = true;
        }
    }
    //////////////////////////////////////////RIGHT
    meetVoid = false;
    for( int i = ccCol+1; i < 8 && !meetVoid; i++)
    {
        if(isSame(ccRow,ccCol,ccRow,i))
        {
            for( int j = ccCol+1; j <= i; j++)
            {
                cell[ccRow][j].setTile( cell[ccRow][ccCol].getTile() );
                if(cell[ccRow][ccCol].isWhite())
                    drawCircle(ccRow, j, 0xffffff);
                if(cell[ccRow][ccCol].isBlack())
                    drawCircle(ccRow, j, 0x000000);
            }
        }
        if(cell[ccRow][i].isVoid())
        {
            meetVoid = true;
        }
    }
    //////////////////////////////////////////UP
    meetVoid = false;
    for( int i = ccRow-1; i > 0 && !meetVoid; i--)
    {
        if(isSame(ccRow,ccCol,i,ccCol))
        {
            for( int j = ccRow-1; j >= i; j--)
            {
                cell[j][ccCol].setTile( cell[ccRow][ccCol].getTile() );
                if(cell[ccRow][ccCol].isWhite())
                    drawCircle(j, ccCol, 0xffffff);
                if(cell[ccRow][ccCol].isBlack())
                    drawCircle(j, ccCol, 0x000000);
            }
        }
        if(cell[i][ccCol].isVoid())
        {
            meetVoid = true;
        }
    }
    //////////////////////////////////////////DOWN
    meetVoid = false;
    for( int i = ccRow+1; i < 8 && !meetVoid; i++)
    {
        if(isSame(ccRow,ccCol,i,ccCol))
        {
            for( int j = ccRow+1; j <= i; j++)
            {
                cell[j][ccCol].setTile( cell[ccRow][ccCol].getTile() );
                if(cell[ccRow][ccCol].isWhite())
                    drawCircle(j, ccCol, 0xffffff);
                if(cell[ccRow][ccCol].isBlack())
                    drawCircle(j, ccCol, 0x000000);
            }
        }
        if(cell[i][ccCol].isVoid())
        {
            meetVoid = true;
        }
    }
    //////////////////////////////////////////UP-LEFT
    meetVoid = false;
    for( int i = ccCol-1; i > 0 && !meetVoid; i--)
    {
        for( int j = ccRow-1; j > 0 && !meetVoid; j--)
        {
            if(isSame(ccRow,ccCol,j,i))
            {
                for( int k = ccCol-1; k >= i; k--)
                {
                    for( int l = ccRow-1; l >= j; l--)
                    {
                        cell[k][l].setTile(cell[ccRow][ccCol].getTile());
                        if(cell[ccRow][ccCol].isWhite())
                            drawCircle(l, k, 0xffffff);
                        if(cell[ccRow][ccCol].isBlack())
                            drawCircle(l, k, 0x000000);
                    }
                }
            }
            if(cell[i][j].isVoid())
            {
                meetVoid = true;
            }
        }
    }
    //////////////////////////////////////////UP-RIGHT
    meetVoid = false;
    for( int i = ccCol+1; i < 8 && !meetVoid; i++)
    {
        for( int j = ccRow-1; j > 0 && !meetVoid; j--)
        {
            if(isSame(ccRow,ccCol,j,i))
            {
                for( int k = ccCol+1; k <= i; k++)
                {
                    for( int l = ccRow-1; l >= j; l--)
                    {
                        cell[k][l].setTile(cell[ccRow][ccCol].getTile());
                        if(cell[ccRow][ccCol].isWhite())
                            drawCircle(l, k, 0xffffff);
                        if(cell[ccRow][ccCol].isBlack())
                            drawCircle(l, k, 0x000000);
                    }
                }
            }
            if(cell[i][j].isVoid())
            {
                meetVoid = true;
            }
        }
    }
    //////////////////////////////////////////DOWN-RIGHT
    meetVoid = false;
    for( int i = ccCol+1; i < 8 && !meetVoid; i++)
    {
        for( int j = ccRow+1; j < 8 && !meetVoid; j++)
        {
            if(isSame(ccRow,ccCol,j,i))
            {
                for( int k = ccCol+1; k <= i; k++)
                {
                    for( int l = ccRow+1; l <= j; l++)
                    {
                        cell[k][l].setTile(cell[ccRow][ccCol].getTile());
                        if(cell[ccRow][ccCol].isWhite())
                            drawCircle(l, k, 0xffffff);
                        if(cell[ccRow][ccCol].isBlack())
                            drawCircle(l, k, 0x000000);
                    }
                }
            }
            if(cell[i][j].isVoid())
            {
                meetVoid = true;
            }
        }
    }
    //////////////////////////////////////////DOWN-LEFT
    meetVoid = false;
    for( int i = ccCol-1; i > 0 && !meetVoid; i--)
    {
        for( int j = ccRow+1; j < 8 && !meetVoid; j++)
        {
            if(isSame(ccRow,ccCol,j,i))
            {
                for( int k = ccCol-1; k >= i; k--)
                {
                    for( int l = ccRow+1; l <= j; l++)
                    {
                        cell[k][l].setTile(cell[ccRow][ccCol].getTile());
                        if(cell[ccRow][ccCol].isWhite())
                            drawCircle(l, k, 0xffffff);
                        if(cell[ccRow][ccCol].isBlack())
                            drawCircle(l, k, 0x000000);
                    }
                }
            }
            if(cell[i][j].isVoid())
            {
                meetVoid = true;
            }
        }
    }
}

#endif // GAME_H_INCLUDED
