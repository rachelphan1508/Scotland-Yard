

#ifndef board_h
#define board_h

#include <vector>
#include <string>
#include "Travel.h"
#include "Player.h"
#include "Detective.h"
#include <iostream>
#include <fstream>

using namespace std;

class board {
public:
    void setUp();
    bool movable (int playerid, int dest, char trans, vector<Player>& agents);
    string at(int row, int col);
    
    vector <Travel> possibleMoves (Player myplayer, int playerid, vector<Player>& agents);
    
    void setPos(int playerid, int pos);
    
    int getPos(int playerid);
    bool destOccupied(int dest);
    string getPlayerName(int playerid);
    

private:
    vector<vector<string>> map;
    vector<int> positions; //detective 0: 0 -  detective 1: 1 - ... - mr X: 5
    vector<string> playernames;
    
};

#endif
