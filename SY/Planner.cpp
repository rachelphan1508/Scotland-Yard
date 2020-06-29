

#include "Planner.h"
#include "GameManager.h"
//#include <bits/stdc++.h>

//void Planner:: add_edge(vector<vector <int>> myboard, int src, int dest){
  //  adj[src].push_back(dest);
    
//}

//currently returning the distance from one position to another
//expect: return maybe a vector that has the destination + transportation for each move (vector<Travel>) ...
int Planner:: calculateDistance(board& myboard, int orig, int dest) {
    //a vector of all possible destinations from one pos
    vector<int> alldest;
    vector<int> newdest;
    newdest.resize(0);
    alldest.resize(0);
    int count=0;
    bool found = false;
    
    while (found==false) {
        
        if(count>40 ) return 40;
        count++;
        //for (int i = 0; i < alldest.size();i++)
        for (int i=0; i<alldest.size();i++) {
            //go through the board
            for (int j=0; j<200; j++) {
                string at = myboard.at(alldest[i],j);
                if (at!="") {
                    
                    if (i==dest) {
                        //found our destination
                        found=true;
                        return count;
                    }
                    else newdest.push_back(j);
                }
            }
        }
        //delete all duplicates
        sort(newdest.begin(), newdest.end());
        newdest.erase(unique(newdest.begin(),newdest.end()), newdest.end());
        
        //update alldest
        alldest.resize(newdest.size());
        for (int i=0; i<newdest.size(); i++) {
            alldest[i] = newdest[i];
        }
        newdest.resize(0);
        
        cout << "count " << count << endl;
    }
    
    return 0;
}

bool Planner:: reachDest(int pos, vector<Player>& agents, int playerid){
    vector<int> mrX = agents[playerid].getMrXloc();
    for (int i=0; i< mrX.size(); i++) {
        if (mrX[i] == pos) return true;
    }
    return false;
}

void Planner:: printShortestDistance(board& myboard, vector<Player>& agents, int playerid) {
    
    vector<int> pred(200);
    vector <int> dist(200);
    int dest = 0;
    
    if (BFS(agents, playerid, myboard, pred, dist, dest) == false) {
        cout << "Given source and destination are not connected." << endl;
        return;
    }
    
    //vector path
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl]!= -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
    
    //distance from source
    cout << "Shortest path length is : " << dist[dest] << endl;
    
    //print path
    cout << "Path is: \n" ;
    for (int i=path.size()-1; i>=0; i--) {
        cout << path[i] << " ";
    }
    cout << endl;
    int nextdest = path[path.size()-2];
    //cout << "next dest " << nextdest << endl;
    cout << "Player " << myboard.getPlayerName(playerid) << " should move to " << nextdest << endl;
    //move the detective
    agents[playerid].decreaseTicket(myboard.getTicketName(playerid, agents, nextdest));
    myboard.setPos(playerid, path[path.size()-2]);
}

bool Planner:: BFS(vector<Player>& agents, int playerid, board& myboard, vector<int>& pred, vector <int>& dist, int& dest) {
    vector<int> mrX = agents[playerid].getMrXloc();
    //Queue* queue;
    
    //cout << "beginning of bfs" << endl;
    vector<int> queue;
    vector<bool> visited;
    visited.resize(200);
    //cout << "1" << endl;
    for (int i =0; i<200; i++) {
        visited[i] = false;
        dist[i] = 30;
        pred[i] = -1;
    }
    //cout << "2" << endl;
    int src = myboard.getPos(playerid);
    //now source is the first to be visited
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
    
    //cout << "before while loop BFS" << endl;
    while (reachDest(src, agents, playerid) == false || !queue.empty()) {
        int nu = queue.front();
        queue.erase(queue.begin());
        for (int i=0; i<200; i++) {
            string alltrans = myboard.at(nu, i);
            //(myboard.movablewalltrans(playerid, i, alltrans, agents)==true)
            if (alltrans!= "") {
                if (myboard.movablewalltrans(agents, playerid, nu, i, alltrans)) {
                        if (visited[i]==false) {
                            visited[i] = true;
                            dist[i] = dist[nu] + 1;
                            pred[i] = nu;
                            queue.push_back(i);
                            
                            //we stop BFS when we find destination
                            
                            if (reachDest(i, agents, playerid)) {
                                //cout << "reached destination" << endl;
                                dest = i;
                                return true;
                            }
                        }
                }
                        
            }

            
        }
    }
    return false;
    
}

void Planner:: moveDetectives(vector<Player>& agents, board &myboard, int playerid) {
    printShortestDistance(myboard, agents, playerid);
    
}
