

#ifndef MrX_h
#define MrX_h

#include "Player.h"
using namespace std;

class MrX : public Player {
private:
    int numDouble;
    int numBoat;
    int numBlack; // the black card that hides MrX's move
    
public:

    void addTrans(string trans);
    void setDouble (int val);
    void setBoat (int val);
    void setBlack (int val);
    
    void decreaseBlack();
    void decreaseBoat();
    void decreaseDouble();
    
    
};

#endif /* MrX_h */
