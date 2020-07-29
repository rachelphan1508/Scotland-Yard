#ifndef Travel_h
#define Travel_h

#include <stdio.h>
#include <string>

using namespace std;

//class Travel holds a position and a char to get to that position
class Travel {
    
private:
    char trans;
    int dest;
public:
    void setTrans(char tr);
    void setDest (int d);
    
    int getDest();
    char getTrans();
    
    
    
};

#endif /* Travel_h */
