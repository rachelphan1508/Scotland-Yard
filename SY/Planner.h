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
    void printShortestDistance(board& myboard, vector<Player>& agents, int playerid);
    bool BFS(vector<Player>& agents, int playerid, board& myboard, vector<int>& pred, vector <int>& dist, int& dest);
    //calculate the smallest number of tickets it takes to go from one location to another
    int calculateDistance (board& myboard, int orig, int dest);
    
    bool reachDest(int pos, vector<Player>& agents, int playerid);
    
    void buildMap(board& myboard, vector<int> adj);
    void add_edge( vector<int>adj[], int src, int dest);
private:
    //vector<int> adj;

};


#endif /* Planner_h */
