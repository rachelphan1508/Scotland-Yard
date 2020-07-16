

#include "Planner.h"
#include "GameManager.h"
#include <algorithm>
#include <cmath>

using namespace std;


Planner:: Planner(){
    round=0;
    nextmove.resize(5);
}

int Planner:: nextShowupRound() {
    if (round <3) return 3;
    else if (round <8) return 8;
    else if (round < 13) return 13;
    else if (round <18) return 18;
    else return 24;
}


bool Planner:: reachDest(int pos, vector<Player>& agents, int playerid, vector<int> locs){
    for (int i=0; i< locs.size(); i++) {
        if (locs[i] == pos) return true;
    }
    return false;
}

bool Planner:: checkPlanned(int val) {
    for (int i = 0; i < nextmove.size();i++) {
        if (val == nextmove[i]) return true;
    }
    return false;
}

void Planner:: sortbyDist(vector< pair<int,int> >& v, vector<int>& target) {
    pair <int, int> temp;
    int temp2;
    
    for (int i=0; i<v.size();i++) {
        for (int j=i; j< v.size(); j++) {
            if (v[i].first > v[j].first) {
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
                
                temp2 = target[i];
                target[i] = target[j];
                target[j] = temp2;
            }
        }
    }
}


vector<vector<int>> Planner:: getPath(board& myboard, vector<Player>& agents, int playerid, vector<int> locs) {
    vector< vector<int>> path(0);
    vector<int> pred(200);
    vector <int> dist(200);
    vector<int> dest(0);
    
    if (BFS(agents, playerid, myboard, pred, dist, dest, locs) == false) {
        //cout << "Given source and destination are not connected." << endl;
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
    //check if the next move's dest is occupied by other detectives
    for (int i =0; i<path.size(); i++) {
        
        if (myboard.destOccupied(path[i][path[i].size()-2]) && path.size()>1 && checkPlanned(path[i][path[i].size()-2] == false)) {
            //if the next move is occupied, delete that path
            path.erase(path.begin() + i);
        }
    }

    return path;

}


vector<vector<int>> Planner:: getPathAtLength(board& myboard, vector<Player>& agents, int playerid, vector<int> locs, int length) {
    vector< vector<int>> path(0);
    vector<int> pred(200);
    vector <int> dist(200);
    vector<int> dest(0);
    
    if (BFSatlength(agents, playerid, myboard, pred, dist, dest, locs, length) == false) {
        cout << "BFS couldn't find" << endl;
        //cout << "Given source and destination are not connected." << endl;
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
    //check if the next move's dest is occupied by other detectives
    for (int i =0; i<path.size(); i++) {
        
        if (myboard.destOccupied(path[i][path[i].size()-2]) && path.size()>1) {
            //if the next move is occupied, delete that path
            path.erase(path.begin() + i);
        }
    }
    
    return path;
    
}

void Planner:: printPath(board& myboard, vector<Player>& agents, int playerid, vector<int> locs) {
    vector< vector<int>> path = getPath(myboard, agents, playerid, locs);
    if (path.size()==0)
    {
        cout << "Detective " << myboard.getPlayerName(playerid) << " can't move anywhere." << endl;
        return;
    }
    //distance from source
    cout << endl << "Shortest path length is : " << path[0].size()-1 << endl;
    
    //print path
    cout << "Path for Detective " << myboard.getPlayerName(playerid) << " is: \n" ;
    for (int i=0; i<path.size(); i++) {
        for (int j=path[0].size()-1; j>=0; j--) {
            cout << path[i][j] << " ";
        }
        cout << endl;
    }

}



bool Planner:: BFS(vector<Player>& agents, int playerid, board& myboard, vector<int>& pred, vector <int>& dist, vector<int>& dest, vector<int> locs) {
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
    int src = myboard.getPos(playerid);
    //now source is the first to be visited
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
    
    while (!queue.empty()) {
        int nu = queue.front();
        queue.erase(queue.begin());
        for (int i=0; i<200; i++) {
            string alltrans = myboard.at(nu, i);
            if (alltrans!= "") {
                if (myboard.movablewalltrans(agents, playerid, nu, i, alltrans)) {
                        if (visited[i]==false) {
                            visited[i] = true;
                            dist[i] = dist[nu] + 1;
                            pred[i] = nu;
                            queue.push_back(i);
                            

                            if (reachDest(i, agents, playerid, locs)) {
                                if (dest.size() > 0 && dist[i] > dist[dest[0]]) {
                                    return true;
                                }
                                else {
                                    dest.push_back(i);
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

//do the BFS to find if there exists a path at a specific length
bool Planner:: BFSatlength(vector<Player>& agents, int playerid, board& myboard, vector<int>& pred, vector <int>& dist, vector<int>& dest, vector<int> locs, int length) {
    vector<int> queue;
    vector<bool> visited;
    visited.resize(200);
    
    for (int i =0; i<200; i++) {
        visited[i] = false;
        dist[i] = 30;
        pred[i] = -1;
    }
    vector<int> destdis(0);
    int src = myboard.getPos(playerid);
    //now source is the first to be visited
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
    
    //cout << "length is " << length << endl;
    
    while (!queue.empty()) {
        int nu = queue.front();
        queue.erase(queue.begin());
        for (int i=0; i<200; i++) {
            string alltrans = myboard.at(nu, i);
            if (alltrans!= "") {
                if (myboard.movablewalltrans(agents, playerid, nu, i, alltrans) && visited[i]==false) {
                        visited[i] = true;
                        dist[i] = dist[nu] + 1;
                        pred[i] = nu;
                        queue.push_back(i);
                        
                    //cout << " dist[i] " << dist[i] << endl;
                        if (reachDest(i, agents, playerid, locs) && dist[i] == length) {
                            //cout << "found 1 dest " << i << endl;
                            dest.push_back(i);
                            return true;
                            break;
                        }
                    
                    if( dist[i] - length == 2 && dest.size() == 0 ) return false;
                    
                }
                
            }
            
            
        }
    }
    if (dest.size()>0) return true;
    
    return false;
    
}

int Planner:: getNextPos(vector<Player>& agents, board &myboard, int playerid, vector<int>& locs) {
    vector<vector<int>> path = getPath(myboard, agents, playerid, locs);
    printPath(myboard, agents, playerid, locs);
    int nextdest = path[0][path[0].size()-2];
    return nextdest;
    
}

int Planner:: getNextPosAtLength(vector<Player>& agents, board &myboard, int playerid, vector<int>& locs, int length) {
    vector<vector<int>> path = getPathAtLength(myboard, agents, playerid, locs, length);
    if (path.size()==0) return 0;
   // printPath(myboard, agents, playerid, locs);
    int nextdest = path[0][path[0].size()-2];
    cout << "next dest " << nextdest << endl;
    return nextdest;
    
}

void Planner:: moveDetectives (vector<Player>& agents, board& myboard) {
    vector<vector<int>> path;
    path.resize(0);
    
    //here, each detective only thinks about his next move & make the decision of moving to an UG station or one of Mr.X's possible locations.
    
    //for (int i=0; i < 5; i++) {
        //if round < 3, move to an underground station
    if (round < 3) {
            
        //lead the detectives to move to different UG stations at round 3 or after
         moveBeforeAppear(agents, myboard);
    }
    // if round > 3
    else if (round >=3) {
        moveAfterAppear(agents, myboard);
    }
    cout << endl;
    for (int i=0; i<5; i++) {
        myboard.DisplayTickets(i, agents);
        agents[i].Display();
        int curpos = myboard.getPos(i);
        int val = nextmove[i];
        cout << "Detective " << myboard.getPlayerName(i) << " is moving to " << val << "." << endl << endl;
        myboard.setPos(i, val);
        agents[i].decreaseTicket(myboard.getTicketName(curpos, i, agents, val));
        for (int k=0; k<5; k++) {
            agents[k].updateFromDetective(myboard, i);
        }
        if (myboard.getPos(i) == myboard.getPos(5)) {
            cout << endl << "GAME OVER! MR.X WAS CAUGHT BY DETECTIVE " << myboard.getPlayerName(i) <<"." << endl;
            break;
        }
    }
    
    //reset all next moves
    for (int i =0; i<nextmove.size(); i++) {
        nextmove[i] = 0;
    }
    
}

//set the current round
void Planner:: setRound(int num) {
    round = num;
}

//check if a position is an UG station
bool Planner:: isAtUG(int pos) {
    if (pos == 1 || pos == 13 || pos == 46 || pos == 67 || pos == 74 || pos == 79 || pos ==89 || pos == 111 || pos == 140 || pos == 153 || pos == 159 || pos == 163 || pos == 185) return true;
    else return false;
}

void Planner:: moveToUnderground (vector<Player>& agents, board& myboard, int playerid) {
    
    vector<int> locs {13, 46, 67, 74, 79, 89, 111, 140, 153, 159, 163, 185};
    vector< vector<int>> path = getPath(myboard, agents, playerid, locs);
    //printPath(myboard, agents, playerid, locs);
    int nextdest = path[0][path[0].size()-2];
    cout << endl << "Detective " << myboard.getPlayerName(playerid) << " is moving to " << nextdest << endl;
    //move the detective
    int curpos = myboard.getPos(playerid);
    agents[playerid].decreaseTicket(myboard.getTicketName(curpos, playerid, agents, nextdest));
    myboard.setPos(playerid, nextdest);
    path.resize(0);
}




bool Planner:: checkAppeared(vector<int> v, int val) {
    for (int i=0; i<v.size(); i++) {
        if (v[i] == val) return true;
    }
    return false;
}
//check if there is a similar value before position pos && path's size is the same
bool Planner:: repeated(vector<int> v, int pos, board& myboard, vector<Player>& agents, vector<int> locs) {
    for (int i=0; i<pos; i++) {
        if (v[i] == v[pos] && getPath(myboard, agents, i, locs)[0].size() == getPath(myboard, agents, pos, locs)[0].size()) return true;
    }
    return false;
}

//return a vector that includes everything except similar elements to station
vector<int> Planner:: exceptStation (vector<int> src, vector<int> station) {
    vector<int> v;
    for(int i=0; i< src.size();i++) {
        if (!checkAppeared(station, src[i]))
        {
            v.push_back(src[i]);
        }
    }
    return v;
}

// when a detective is at an UG station, let him move somewhere (NOT AN UG STATION - to avoid wasting UG ticket)
int Planner:: getToSomewhere(int playerid, vector<Player>& agents, board& myboard) {
    int curpos = myboard.getPos(playerid);
    
    for (int i =0; i<200; i++) {
        if (myboard.at(curpos, i) != "U" && myboard.at(curpos, i) != "" && agents[playerid].enoughTicket(myboard.getTicketName(curpos, playerid, agents, i))==true) {
            return i;
        }
    }
    return 0;
}


//all the moves before Mr.X appears (round 1-2)
void Planner:: moveBeforeAppear (vector<Player>& agents, board& myboard) {
    
    //make sure each detective is not using any Underground ticket before round 3
    vector<int> locs {13, 46, 67, 74, 79, 89, 111, 140, 153, 159, 163, 185};
    vector<int> station;
    vector<bool> UGtarget (5, true);
    station.resize(5);
    vector< vector<int>> dest;
    //vector to keep track of the number of times each dest appear
    vector<int> count (200,0);
    dest.resize(5);
    for (int i=0; i<5; i++) {
        int curpos = myboard.getPos(i);
        //if currently at at UG station, move somewhere else but not to an UG station
        // avoid using UG tickets
        if (isAtUG(curpos) == true) {
            //cout << "Detective " << myboard.getPlayerName(i) << " is at an Underground station." << endl;
            int nextdest = getToSomewhere(i, agents, myboard);
            UGtarget[i] = false;
            station[i] = nextdest;
            dest[i].push_back(nextdest);
        }
        else {
            vector< vector<int>> path = getPath(myboard, agents, i, locs);
            for (int j=0; j<path.size(); j++) {
                dest[i].push_back(path[j][0]);
                count[path[j][0]]++;
            }
        }
    }

    // now we have all UG stations that each detective is trying to get to
    // delete the paths
    for (int i =0; i<dest.size(); i++)
    {
        //if the detective has only one reachable UG station, do nothing
        if (dest[i].size()==1 ) {
            
        }
        else {
            for (int j=0; j< dest[i].size();j++) {
                //if a station appears only once, keep it and delete the others
                //cout << "count " << count[dest[i][j]] << endl;
                if (count[dest[i][j]]==1)
                {
                    int val = dest[i][j];
                    dest[i].resize(0);
                    dest[i].push_back(val);
                    break;
                }
            }
        }
    }
    bool found = false;
    bool appeared = false;

    for (int i=0; i< 5;i++)
    {

        if (UGtarget[i] == true)
        {
        //if the station hasn't appeared in the list, add it to the list of stations
        for (int j=0; j<dest[i].size();j++) {
            if (dest[i].size()==1) {
                station[i] = dest[i][0];
            }
            else if(found==false) {
                if (j == dest[i].size()-1)
                {
                    station[i] = dest[i][j];
                }
                //try to eliminate the dests that appeared
                else
                {
                    if (checkAppeared(station, dest[i][j]) == false) {
                        found=true;
                        station[i] = dest[i][j];
                    }
                }
            }
            
        }
        found=false;
        appeared=false;
        }
    }
    //check if there are more than one detective moving to one spot at the one time, make the others move somewhere else
    for (int i =0; i<5; i++) {
        if (repeated(station, i, myboard, agents, locs) && UGtarget[i] == true)
        {
            //move the detective to a possible  station (not the chosen stations)
            vector<int> possibledests = exceptStation(locs, station);
            station[i] = getPath(myboard, agents, i, possibledests)[0][0];
        }
    }
    
    //return the vector of each detective's next location
    for (int i=0; i<5; i++)
    {
        vector<int> finalug(1);
        finalug[0]=station[i];
        nextmove[i] = getNextPos(agents, myboard, i, finalug);
        //printPath(myboard, agents, i, finalug);
        finalug[0] = 0;
        
    }
    
    
}


//decide the moves of each detective after Mr.X appeared
void Planner:: moveAfterAppear(vector<Player>& agents, board& myboard) {
    
    vector<vector<int>> path;
    int next=0;
    
    for (int i=0; i < 5; i++) {
        
        char decision = getDecision(agents, myboard, i);
        vector<int> locs = agents[i].getMrXloc();
        vector<int> nextlocs = agents[i].getNextRound(myboard);
        vector<int> UG = {13, 46, 67, 74, 79, 89, 111, 140, 153, 159, 163, 185};

        if (decision == 'N')
        {
            next = getNextPos(agents, myboard, i, locs);
        }
        else if (decision == 'P') next = getNextPos(agents, myboard, i, nextlocs);
        else next = getNextPos(agents, myboard, i, UG);
        
        nextmove[i] = next;
        for (int k =0; k < 5; k++) {
            agents[k].updateFromPlanner(myboard, next);
        }
        
    }
}

//check if a player still has UG ticket after completing his path
bool Planner:: hasUGticket(vector<vector<int>> path, int playerid) {
    return true;
}

char Planner:: getDecision(vector<Player>& agents, board& myboard, int playerid) {
    vector<int> locs = agents[playerid].getMrXloc();
    vector<int> nextlocs = agents[playerid].getNextRound(myboard);
    vector<int> UG = {13, 46, 67, 74, 79, 89, 111, 140, 153, 159, 163, 185};
    
    int SU = nextShowupRound();
    vector< vector<int>> pathtoX = getPath(myboard, agents, playerid, locs);
    vector< vector<int> > pathtoU = getPath(myboard, agents, playerid, UG);
    //decide here whether a detective is trying to get to one of UG stations | Mr.X's locations | Mr.X's next round locations
    int roundtilSU = SU - round;
    if (pathtoX[0].size() < roundtilSU) {
        return 'N';
    }
    /*
    else if (pathtoU[0].size() - roundtilSU + 1 > 0  && hasUGticket(pathtoU, playerid)==true && checkPlanned(getNextPos(agents, myboard, playerid, UG)== false)  ) {
        return 'U';
    }
     */
    else return 'P';

    
    //
}
