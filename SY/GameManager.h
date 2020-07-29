

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


//class GameManager manages the game (holds detectives, Mr.X, the map and the planner
class GameManager {
protected:
    vector <Player> agents;
    
    MrX MisterX;
    board myBoard;
    bool gameOver;
    Planner myplanner;
    bool computer;
    
private:
    int cur_round;
    
public:
    GameManager();
    void setUp(); // give 
    void playRound(bool& dtused); //each player takes turn to move - update the board
    void playFullGame();
    void playDetective(int playerid);
    void playDetectiveBot();
    void playMrX();
    void setComputer();
    
};


#endif /* GameManager_h */
