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
    bool isSUround();
    
    int getNextPos (vector<Player>& agents, board& myboard, int playerid, vector<int>& locs);
    int getNextPosAtLength(vector<Player>& agents, board &myboard, int playerid, vector<int>& locs, int length);
    
    vector<vector<int>> getPath(board& myboard, vector<Player>& agents, int playerid, vector<int> locs);
    vector<vector<int>> getPathAtLength(board& myboard, vector<Player>& agents, int playerid, vector<int> locs, int length);
    
    
    void printPath(board& myboard, vector<Player>& agents, int playerid, vector<int> locs);
    
    bool BFS(vector<Player>& agents, int playerid, board& myboard, vector<int>& pred, vector <int>& dist, vector<int>& dest, vector<int> locs);
    bool BFSatlength(vector<Player>& agents, int playerid, board& myboard, vector<int>& pred, vector <int>& dist, vector<int>& dest, vector<int> locs, int length);
    
    //calculate the smallest number of tickets it takes to go from one location to another
    int calculateDistance (board& myboard, int orig, int dest);
    
    bool reachDest(int pos, vector<Player>& agents, int playerid, vector<int> locs);
    
    void moveDetectives (vector<Player>& agents, board& myboard);
    
    
    void moveToUnderground (vector<Player>& agents, board& myboard, int playerid);
    void movePredict (vector<Player>& agents, board& myboard, int playerid);
    
    int getToSomewhere(int playerid, vector<Player>& agents, board& myboard);
    
    void moveBeforeAppear (vector<Player>& agents, board& myboard);
    void moveAfterAppear (vector<Player>& agents, board& myboard);
    
    bool checkAppeared(vector<int> v, int val);
    bool checkPlanned(int val);
    bool repeated (vector<int> v, int pos, board& myboard, vector<Player>& agents, vector<int> locs);
    bool isAtUG (int pos);
    bool hasUGticket (vector<vector<int>> path, int playerid);
    
    char getDecision (vector<Player>& agents, board& myboard, int playerid);
    
    void sortbyDist(vector< pair<int, int> >& v, vector<int>& target);
    vector<int> exceptStation (vector<int> src, vector<int> station);
    
    //void move
private:
    //vector<int> adj;
    int round;
    vector<int> nextmove;

};


#endif /* Planner_h */
