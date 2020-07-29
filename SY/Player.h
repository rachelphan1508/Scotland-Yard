


#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <string>
#include "Travel.h"
#include <vector>

using namespace std;

class board;

//Class: Player
//A player holds his number of tickets, Mr.X's last seen location, and Mr.X's possible locations
class Player {
    
public:
    Player();
    void decreaseTicket (char trans);
    void increaseTicket (char trans);
    void setTaxi (int val);
    void setBus (int val);
    void setUg (int val);
    void setDouble (int val);
    void setBlack (int val);
    int getUg();
    int getTaxi();
    int getBus();
    int getDouble();
    int getBlack();
    
    bool enoughTicket (char trans);
    
    vector<int> getMrXloc();
    vector<int> getNextRound(board& myboard);
    void updateMrX(char trans, board& myboard);
    void updatelastseen(int pos, board& myboard);
    void updateFromDetective (board& myboard, int playerid);
    void updateFromPlanner (board& myboard, int val);
    
    void Display();
    
    
private:
    int numTaxi;
    int numBus;
    int numUg;
    int numBlack;
    int numDouble;
    vector<int> mrXlocation;
    int lastseen;
    
};

#endif /* Player_h */
