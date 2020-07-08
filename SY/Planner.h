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
    Planner();
    void setRound(int num);
    int nextShowupRound();
    
    int getNextPos (vector<Player>& agents, board& myboard, int playerid, vector<int>& locs);
    vector<vector<int>> getPath(board& myboard, vector<Player>& agents, int playerid, vector<int> locs);
    void printPath(board& myboard, vector<Player>& agents, int playerid, vector<int> locs);
    bool BFS(vector<Player>& agents, int playerid, board& myboard, vector<int>& pred, vector <int>& dist, vector<int>& dest, vector<int> locs);
    //calculate the smallest number of tickets it takes to go from one location to another
    int calculateDistance (board& myboard, int orig, int dest);
    
    bool reachDest(int pos, vector<Player>& agents, int playerid, vector<int> locs);
    
    void buildMap(board& myboard, vector<int> adj);
    void add_edge( vector<int>adj[], int src, int dest);
    void decideDetectiveMoves (vector<Player>& agents, board& myboard);
    void moveToUnderground (vector<Player>& agents, board& myboard, int playerid);
    bool isAtUG (int pos);
    
    void sortbyDist(vector< pair<int, int> >& v, vector<int>& target);
    
    //void move
private:
    //vector<int> adj;
    int round;

};


#endif /* Planner_h */
