
#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <string>
#include "Travel.h"
#include <vector>

using namespace std;

class board;

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
    void updateMrX(char trans, board& myboard);
    void updatelastseen(int pos, board& myboard);
    void updateFromDetective (board& myboard, int playerid);
    
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
