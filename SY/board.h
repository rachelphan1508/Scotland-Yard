

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
    bool movablewalltrans (vector<Player>& agents, int playerid, int src, int dest, string alltrans);
    
    string at(int row, int col);
    char getTicketName (int src, int playerid, vector<Player>& agents, int dest);
    void DisplayTickets(int playerid, vector<Player>& agents);
    
    vector <Travel> possibleMoves (Player myplayer, int playerid, vector<Player>& agents);
    
    void setPos(int playerid, int pos);
    
    int getPos(int playerid);
    bool destOccupied(int dest);
    string getPlayerName(int playerid);
    
    int getDistance (int orig, int dest);
    
    //vector<int> getAllDest(
    

private:
    vector<vector<string>> map;
    vector<int> positions; //detective 0: 0 -  detective 1: 1 - ... - mr X: 5
    vector<string> playernames;
    
};

#endif
