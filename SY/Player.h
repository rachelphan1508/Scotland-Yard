
#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <string>
using namespace std;

class Player {
    
public:
    void decreaseTicket (char trans);
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
    
    
private:
    int numTaxi;
    int numBus;
    int numUg;
    int numBlack;
    int numDouble;
};

#endif /* Player_h */
