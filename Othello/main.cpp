#include <iostream>
#include "SDL.h"
#include "graphic.h"
#include "board.h"
#include "game.h"
#include "cell.h"
#include "player.h"

using namespace std;
void fill(int data[]);
void display(int data[], int s);

int main(int argc, char *argv[])
{
    bool    done = false;
    char    c;
    graphic screen;
    //board   b;
    game    g;
    int data[COL];
    int clickedCellRow = 5;
    int clickedCellCol = 5;

    player p1(0x000000);    //black
    player p2(0xffffff);    //white

 while(!done){
        SDL_Delay(DELAY);
        // Poll for events, and handle the ones we care about.
        while (SDL_PollEvent(&event))
        {
          switch (event.type)
          {
              case SDL_KEYDOWN:

                c = toupper(event.key.keysym.sym);
                if(c == 'R'){
                    fill(data);
                    //Later change to confirm which player's
                    //turn and then reflect the color accordingly

                }
                if(c == 'X') done = true;
                //if(c == 'B') BubbleSort(data,COL,screen);

                break;

              case SDL_KEYUP:
                // If escape is pressed, return (and thus, quit)
                if (event.key.keysym.sym == SDLK_ESCAPE)
                  done = true;
                break;

              case SDL_MOUSEBUTTONDOWN:
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    if(g.click(clickedCellRow, clickedCellCol) == true
                       && p1.getTurnP1() == true)
                       {
                            g.drawCircle(clickedCellRow,clickedCellCol,p1.getColor());
                            g.setTile(clickedCellRow,clickedCellCol,BLACK);
                            g.infect(clickedCellRow, clickedCellCol);
                            totalTurns++;
                           //print sprite signifying it is p1's turn on the left-hand side
                       }

                    if(g.click(clickedCellRow, clickedCellCol) == true
                       && p2.getTurnP2() == true)
                       {
                          g.drawCircle(clickedCellRow, clickedCellCol, p2.getColor());
                          g.setTile(clickedCellRow,clickedCellCol,WHITE);
                          g.infect(clickedCellRow, clickedCellCol);
                          totalTurns++;
                          //print sprite signifying it is p2's turn on the right-hand side
                       }

                }


                break;

              case SDL_QUIT:
                done = true;;


          }

        }
}



  return 0;
}


void fill(int data[]){
    for(int i = 0; i < COL; i++)
        data[i] = ROW%25;
}
