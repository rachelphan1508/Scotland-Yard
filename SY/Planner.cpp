

#include "Planner.h"
#include "GameManager.h"


Planner:: Planner(){
    round=0;
}
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

bool Planner:: reachDest(int pos, vector<Player>& agents, int playerid, vector<int> locs){
    for (int i=0; i< locs.size(); i++) {
        if (locs[i] == pos) return true;
    }
    return false;
}

void Planner:: printShortestDistance(board& myboard, vector<Player>& agents, int playerid, vector<int>& path, vector<int> locs) {
    
    vector<int> pred(200);
    vector <int> dist(200);
    vector<int> dest(0);
    
    if (BFS(agents, playerid, myboard, pred, dist, dest, locs) == false) {
        cout << "Given source and destination are not connected." << endl;
        return;
    }
    
    //vector path
    for (int i=0; i<dest.size(); i++ ) {
        int crawl = dest[i];
        path.push_back(crawl);
        while (pred[crawl]!= -1) {
            path.push_back(pred[crawl]);
            crawl = pred[crawl];
        }
    }
    //distance from source
    cout << "Shortest path length is : " << dist[dest[0]] << endl;
    
    //print path
    cout << "Path for Detective " << myboard.getPlayerName(playerid) << " is: \n" ;
    for (int i=path.size()-1; i>=0; i--) {
        cout << path[i] << " ";
    }
    cout << endl;
}

bool Planner:: BFS(vector<Player>& agents, int playerid, board& myboard, vector<int>& pred, vector <int>& dist, vector<int>& dest, vector<int> locs) {
    vector<int> mrX = agents[playerid].getMrXloc();
    int curlength = 0;
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
    vector<int> destdis(0);
    //cout << "2" << endl;
    int src = myboard.getPos(playerid);
    //now source is the first to be visited
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
    
    //cout << "before while loop BFS" << endl;
    while (!queue.empty()) {
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
                            
                            //when we find a destination
                            
                            if (reachDest(i, agents, playerid, locs)) {
                                dest.push_back(i);
                                destdis.push_back(dist[i]);
                            }
                        }
                }
                        
            }

            
        }
    }
    if (dest.size()>0) {
        int minval = 10000;
        for(int i=0; i<destdis.size();i++) {
            if (destdis[i] < minval) minval = destdis[i];
        }
        //remove all dests that are not
        for (int i=0; i<destdis.size(); i++) {
            if (destdis[i] > minval) {
                dest.erase(dest.begin()+i);
            }
        }
        return true;
    }
    
    else return false;
    
}

void Planner:: moveDetectives(vector<Player>& agents, board &myboard, int playerid, vector<int>& path) {
    vector<int> locs = agents[playerid].getMrXloc();
    printShortestDistance(myboard, agents, playerid, path, locs);
    int nextdest = path[path.size()-2];
    cout << "Player " << myboard.getPlayerName(playerid) << " should move to " << nextdest << endl;
    //move the detective
    agents[playerid].decreaseTicket(myboard.getTicketName(playerid, agents, nextdest));
    myboard.setPos(playerid, path[path.size()-2]);
    
    
}

void Planner:: decideDetectiveMoves (vector<Player>& agents, board& myboard) {
    vector<int> path(0);
    cout << "ROUND " << round << endl;
    if (round<3) {
        for (int i=0; i<5; i++) {
        moveToUnderground(agents, myboard, i);
        }
    }
    else if (round >=3)
    {
    for (int i=0; i<5; i++) {
        vector<int> locs = agents[i].getMrXloc();
        printShortestDistance(myboard, agents, i, path, locs);
        moveDetectives(agents, myboard, i, path);
    }
    }
}


void Planner:: setRound(int num) {
    round = num;
}

void Planner:: moveToUnderground (vector<Player>& agents, board& myboard, int playerid) {
    vector<int> locs { 13, 46, 67, 74, 79, 89, 111, 140, 153, 159, 163, 185};
    vector<int> path(0);
    printShortestDistance(myboard, agents, playerid, path, locs);
    int nextdest = path[path.size()-2];
    cout << "Player " << myboard.getPlayerName(playerid) << " should move to " << nextdest << endl;
    //move the detective
    agents[playerid].decreaseTicket(myboard.getTicketName(playerid, agents, nextdest));
    myboard.setPos(playerid, path[path.size()-2]);
}
