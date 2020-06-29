

#ifndef GameManager_h
#define GameManager_h

#include <iostream>
#include "Detective.h"
#include "MrX.h"
#include "board.h"
#include <cstdlib>
#include "Player.h"
#include "Planner.h"

using namespace std;


class GameManager {
protected:
    vector <Player> agents;
    
    MrX MisterX;
    board myBoard;
    bool gameOver;
    Planner D;
    bool computer;
    
private:
    int cur_round;
    //vector<string> records; //record Mr.X's move
    
public:
    GameManager();
    void setUp(); // give 
    void playRound(int& num_round, bool& dtused); //each player takes turn to move - update the board
    void playFullGame();
    void playDetective(int playerid);
    void playMrX();
    void setComputer();
    
};


#endif /* GameManager_h */
