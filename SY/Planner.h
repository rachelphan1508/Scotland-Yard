#ifndef Planner_h
#define Planner_h

#include <stdio.h>
#include <vector>
#include "Player.h"
#include "board.h"

using namespace std;
//job: make all detectives communicative


//see if a detective can move to one of Mr. X's locations
// yes-> move there
// no -> use the shortest path


class GameManager;
class Planner {
public:
//try to communicate with all detectives
    void moveDetectives (vector<Player>& agents, board& myboard, int playerid);
    
    //calculate the smallest number of tickets it takes to go from one location to another
    int calculateDistance (board& myboard, int orig, int dest);

};


#endif /* Planner_h */
