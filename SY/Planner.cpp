

#include "Planner.h"
#include "GameManager.h"

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

void Planner:: moveDetectives(vector<Player>& agents, board &myboard, int playerid) {
    
    //first get the vector of all mrX's current possible locations
    vector <int> mrX = agents[0].getMrXloc();
    int pos= myboard.getPos(playerid);;
    string alltrans;
    
    vector<int> dsize;
    dsize.resize(mrX.size());
    
    int minpos = 0;
    //check & get a vector of distances from player's position to mrx's possible location
    int minsize =200;
    for (int j=0; j<mrX.size(); j++) {
        dsize[j] = calculateDistance(myboard, pos, mrX[j]);
        if (dsize[j] < minsize) {
            minsize = dsize[j];
            minpos = j;
        }
    }
    
    //currently have the minimum distance from one pos to another ... 
    
    /*
    
    
    
        //if movable between
        //alltrans=myboard.at(pos, mrX[j]);
        //if (alltrans!=""){
          //  cout << "movable to " << mrX[j] << " using " << alltrans << endl;
            //for (int i=0; i<alltrans.size();i++) {
              //  if (myboard.movable(playerid, mrX[j], alltrans[i], agents)){
                //    cout << "Player " << myboard.getPlayerName(playerid) << " can move to " << mrX[j]  << endl;
                  //  break;
                //}
            //}
        //}
        
        //else if there is no direct path from detective to Mr.X's possible locations
        
        // how to calculate the distance?
    }
     
     */
    
    //now we have the shortest possible path from
    
    
}
