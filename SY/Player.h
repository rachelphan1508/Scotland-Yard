
#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <string>
using namespace std;

class Player {
    
public:
    void Move (char trans);
    //int getPos();
    void decreaseTaxi();
    void decreaseBus();
    void decreaseUg();
    void setTaxi (int val);
    void setBus (int val);
    void setUg (int val);
    int getUg();
    int getTaxi();
    int getBus();
    bool enoughTicket (char trans);
    
    
private:
    int numTaxi;
    int numBus;
    int numUg;
};

#endif /* Player_h */
