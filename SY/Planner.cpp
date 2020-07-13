

#include "Planner.h"
#include "GameManager.h"
#include <algorithm>

using namespace std;


Planner:: Planner(){
    round=0;
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
    //int curlength = 0;
    
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

int Planner:: getNextPos(vector<Player>& agents, board &myboard, int playerid, vector<int>& locs) {
    vector<vector<int>> path = getPath(myboard, agents, playerid, locs);
    int nextdest = path[0][path[0].size()-2];
    return nextdest;
    
}

void Planner:: decideDetectiveMoves (vector<Player>& agents, board& myboard) {
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
        for (int i=0; i < 5; i++) {

            //myboard.printDetails(i, agents);
            
            vector<int> locs = agents[i].getMrXloc();
            
            // if cur round + path.size > next showup round => move to UG station
            path = getPath(myboard, agents, i, locs);
            /*
            cout << "path[0].size " << path[0].size() << endl;
            cout << "round " << round << endl;
            cout << "next SU round " << nextShowupRound() << endl;
             */
            if (round + path[0].size() - nextShowupRound() > 0 && locs.size()>=5) {
                moveToUnderground(agents, myboard, i);
            }
            
            //
            else {
                int nextpos = getNextPos(agents, myboard, i, locs);
                myboard.setPos(i, nextpos);
                int curpos = myboard.getPos(i);
                agents[i].decreaseTicket(myboard.getTicketName(curpos, i, agents, nextpos));
                cout << "Detective " << myboard.getPlayerName(i) << " is moving to " << nextpos << endl;
                for (int k=0; k<5; k++) {
                    agents[k].updateFromDetective(myboard, i);
                }
                if (myboard.getPos(i) == myboard.getPos(5)) {
                    cout << endl << "GAME OVER! MR.X WAS CAUGHT BY DETECTIVE " << myboard.getPlayerName(i) <<"." << endl;
                    break;
                }
            }
            
        }
    }
    
    
    /*
    vector< pair<int,int> > v;
    
    vector<int> distance(5);
    //keep track of the target that each detective is trying to get to.
    vector<int> target(5);
    
    //keep track of the next move for each detective
    vector<int> nextmove(5);
    
    //if Mr.X hasn't made a move, try to reach an underground station before Mr.X's turn
    if (round<3) {
        for (int i=0; i<5; i++) {
            moveToUnderground(agents, myboard, i);
            for (int j=0; j< path.size(); j++) {
                path[j].resize(0);
            }
        }
    }
    else if (round >=3)
    {
        for (int i=0; i<5; i++) {
            vector<int> locs = agents[i].getMrXloc();
            path = getPath(myboard, agents, i, locs);
            printPath(myboard, agents, i, locs);
            target[i] = path[0][0];
            cout << "target " << target[i] << endl;
            distance[i] = path[0].size();
            v.push_back(make_pair(distance[i], i));
            //moveDetectives(agents, myboard, i, path);
            path.resize(0);
            
        }
        //HAVE TO DECIDE HERE WHICH LOCATION EACH DETECTIVE IS HEADING TOs
        sortbyDist(v, target);
        for (int i=0; i<5; i++) {
            vector<int> locs = agents[v[i].second].getMrXloc();
            int nextdest = getNextPos(agents, myboard, v[i].second, locs);
            //if the next detective's aiming to the same dest, remove that dest from the locs vector?
            if (locs.size() > 1 && i <4 && target[i]==target[i+1]) {
                //print locs before
                cout << "before" << endl;
                for (int k=0; k<locs.size(); k++) {
                    cout << locs[k] << " ";
                }
                cout << endl;
                //cout << "target[i] " << target[i] << endl;
                locs.erase(remove(locs.begin(), locs.end(), target[i]), locs.end());
                //cout << "after" << endl;
                for (int k=0; k<locs.size(); k++) {
                    cout << locs[k] << " ";
                }
                cout << endl;
            }
        }
    }
     */
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
    printPath(myboard, agents, playerid, locs);
    int nextdest = path[0][path[0].size()-2];
    cout << "Detective " << myboard.getPlayerName(playerid) << " is moving to " << nextdest << endl;
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
            //cout << "myboard.at(curpos,i) " << myboard.at(curpos, i) << endl;
            //cout << "get to i " << i << endl;
            return i;
        }
    }
    return 0;
}

void Planner:: moveBeforeAppear (vector<Player>& agents, board& myboard) {
    
    //make sure each detective is not using any Underground ticket before round 3
    
    vector<int> locs {13, 46, 67, 74, 79, 89, 111, 140, 153, 159, 163, 185};
    vector<int> station;
    vector<bool> UGtarget (5, true);
    station.resize(5);
    
    bool UGused = false;

    vector< vector<int>> dest;
    //vector to keep track of the number of times each dest appear
    vector<int> count (200,0);
    dest.resize(5);
    for (int i=0; i<5; i++) {
        int curpos = myboard.getPos(i);
        
        //if currently at at UG station, move somewhere else but not to an UG station
        if (isAtUG(curpos) == true) {
            cout << "Detective " << myboard.getPlayerName(i) << " is at an Underground station." << endl;
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
            printPath(myboard, agents, i, locs);
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
    
    //now, move each detective to its next location
    for (int i=0; i<5; i++)
    {
        //myboard.printDetails(i, agents);
        vector<int> finalug(1);
        finalug[0]=station[i];
        int val = getNextPos(agents, myboard, i, finalug);
        int curpos = myboard.getPos(i);
        cout << "Detective " << myboard.getPlayerName(i) << " is moving to " << val << "." << endl;
        myboard.setPos(i, val);
        agents[i].decreaseTicket(myboard.getTicketName(curpos, i, agents, val));
        finalug[0] = 0;
        
    }
    
}
