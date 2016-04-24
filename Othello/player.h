#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "game.h"

static int totalTurns = 1;

//change to friend of game: give access to
class player
{
    private:
        int turns;
        int score;
        int color;
    public:
        player(int c = 0xffffff);
        bool getTurnP1();
        bool getTurnP2();
        int getScore() {return score;}
        int getColor() {return color;}
        int getTurns() {return turns;}
        double getAvg() {return (score*1.0)/turns;}
        void setTurns(int x) {turns = x;}
        void setScore(int x) {score = x;}
};

player::player(int c)
{
    turns = 0;
    score = 0;
    color = c;  //white
}

bool player::getTurnP1()
{
    if(totalTurns % 2 != 0) return true;
}

bool player::getTurnP2()
{
    if(totalTurns % 2 == 0) return true;
}

#endif // PLAYER_H_INCLUDED
