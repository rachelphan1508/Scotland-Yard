

#include "Planner.h"
#include "GameManager.h"
#include <algorithm>

using namespace std;


Planner:: Planner(){
    round=0;
}
//#include <bits/stdc++.h>

//void Planner:: add_edge(vector<vector <int>> myboard, int src, int dest){
  //  adj[src].push_back(dest);
    
//}

//currently returning the distance from one position to another
//expect: return maybe a vector that has the destination + transportation for each move (vector<Travel>) ...
/*
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

*/

int Planner:: nextShowupRound(int val) {
    if (val <3) return 3;
    else if (val <8) return 8;
    else if (val < 13) return 13;
    else if (val <18) return 18;
    else return 24;
}

bool Planner:: reachDest(int pos, vector<Player>& agents, int playerid, vector<int> locs){
    for (int i=0; i< locs.size(); i++) {
        if (locs[i] == pos) return true;
    }
    return false;
}

vector<vector<int>> Planner:: getPath(board& myboard, vector<Player>& agents, int playerid, vector<int> locs) {
    vector< vector<int>> path(0);
    vector<int> pred(200);
    vector <int> dist(200);
    vector<int> dest(0);
    
    if (BFS(agents, playerid, myboard, pred, dist, dest, locs) == false) {
        cout << "Given source and destination are not connected." << endl;
        return path;
    }
    
    //vector path
    path.resize(dest.size());
    for (int i=0; i<dest.size(); i++ ) {
        
        int crawl = dest[i];
        
        path[i].push_back(crawl);
        while (pred[crawl]!= -1) {
            path[i].push_back(pred[crawl]);
            crawl = pred[crawl];
        }
    }

    return path;

}

void Planner:: printPath(board& myboard, vector<Player>& agents, int playerid, vector<int> locs) {
    vector< vector<int>> path = getPath(myboard, agents, playerid, locs);
    //distance from source
    cout << "Shortest path length is : " << path[0].size()-1 << endl;
    
    //print path
    cout << "Path for Detective " << myboard.getPlayerName(playerid) << " is: \n" ;
    for (int i=0; i<path.size(); i++) {
        for (int j=path[0].size()-1; j>=0; j--) {
            cout << path[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool Planner:: BFS(vector<Player>& agents, int playerid, board& myboard, vector<int>& pred, vector <int>& dist, vector<int>& dest, vector<int> locs) {
    int curlength = 0;
    
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
                            //cout << "inside movablewalltrans " << endl;
                            if (reachDest(i, agents, playerid, locs)) {
                                //cout << "Reached " << endl;
                                //if
                                if (dest.size() > 0 && dist[i] > dist[dest[0]]) {
                                    return true;
                                }
                                else {
                                    dest.push_back(i);
                                    //destdis.push_back(dist[i]);
                                }
                            }
                        }
                }
                        
            }

            
        }
    }
    if (dest.size()>0) return true;

    return false;
    
}

void Planner:: moveDetectives(vector<Player>& agents, board &myboard, int playerid, vector<int>& locs) {
    vector<vector<int>> path = getPath(myboard, agents, playerid, locs);
    int nextdest = path[0][path[0].size()-2];
    cout << "Player " << myboard.getPlayerName(playerid) << " should move to " << nextdest << endl;
    //move the detective
    agents[playerid].decreaseTicket(myboard.getTicketName(playerid, agents, nextdest));
    myboard.setPos(playerid, path[0][path[0].size()-2]);
    
    
}

void Planner:: decideDetectiveMoves (vector<Player>& agents, board& myboard) {
    vector<vector<int>> path;
    path.resize(0);
    vector< pair<int,int> > v;
    
    vector<int> distance(5);
    vector<int> target(5);

    if (round<3) {
        for (int i=0; i<5; i++) {
            moveToUnderground(agents, myboard, i, path);
            for (int j=0; j< path.size(); j++) {
                path[j].resize(0);
            }
        }
    }
    else if (round >=3)
    {
        for (int i=0; i<5; i++) {
            vector<int> locs = agents[i].getMrXloc();
            printPath(myboard, agents, i, locs);
            distance[i] = path[0].size();
            v.push_back(make_pair(distance[i], i));
            //if (dis)
            target[i] = path[0][0];
            cout << "target " << target[i] << endl;
            //moveDetectives(agents, myboard, i, path);
            path.resize(0);
        }
        //HAVE TO DECIDE HERE WHICH LOCATION EACH DETECTIVE IS HEADING TOs
        sort(v.begin(), v.end());
        for (int i=0; i<5; i++) {
            vector<int> locs = agents[v[i].second].getMrXloc();
            moveDetectives(agents, myboard, v[i].second, locs);
            //if the next detective's aiming to the same dest, remove that dest from the locs vector?
            if (locs.size()>1 && i <4 && target[i]==target[i+1]) {
                locs.erase(remove(locs.begin(), locs.end(), target[i]), locs.end());
            }
        }
    }
}


void Planner:: setRound(int num) {
    round = num;
}

void Planner:: moveToUnderground (vector<Player>& agents, board& myboard, int playerid, vector<vector<int>>& path) {
    vector<int> locs {13, 46, 67, 74, 79, 89, 111, 140, 153, 159, 163, 185};
    printPath(myboard, agents, playerid, locs);
    int nextdest = path[0][path[0].size()-2];
    cout << "Player " << myboard.getPlayerName(playerid) << " should move to " << nextdest << endl;
    //move the detective
    agents[playerid].decreaseTicket(myboard.getTicketName(playerid, agents, nextdest));
    myboard.setPos(playerid, nextdest);
    path.resize(0);
}
