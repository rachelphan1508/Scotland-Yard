
#include "board.h"
#include <fstream>

using namespace std;

//initialize the board
void board:: setUp() {
    // ORDER: MrX -> Blue -> Red -> Orange -> Green -> Yellow
    // MrX -> 5  --- Blue: 0 --- Red: 1 --- Orange: 2 --- Green: 3 --- Yellow: 4
    
    //set players' names
    playernames.resize(6);
    playernames[0] = "Blue";
    playernames[1] = "Red";
    playernames[2] = "Orange";
    playernames[3] = "Green";
    playernames[4] = "Yellow";
    playernames[5] = "Mr X";
    map.resize(200);
    positions.resize(6);
    for (int i=0; i< map.size();i++) {
        map[i].resize(200);
    }
    
    //set up with a map of empty string
    for (int i=0; i<200; i++) {
        for (int j=0; j<200; j++) {
            map[i][j] = "";
        }
    }
    
    //fill up the map with transportation
    // B = Bus, T = Taxi, U = Underground, R = Boat (River)
    int a, b;
    string c;
    ifstream infile;
    infile.open("/Users/rachelphan/Desktop/SSRP/SY/SY/map.txt");
    if (!infile) cout << "can not open file" << endl;
    
    while (infile >> a) {
        //infile >> a;
        infile >> b;
        infile >> c;
        map[a][b] = c;
        //cout << "hi " << a << " " << b << " " << c << endl;
    }

}

vector<Travel> board:: possibleMoves(Player myplayer, int playerid, vector<Player>& agents) {
    //get current location
    int curpos = positions[playerid];
    vector<Travel> res;
    Travel move;
    
    //get all possible moves from that location
    for (int i=0; i<199; i++) {
        if (map[curpos][i].size() >= 1) {
            move.setDest(i);
            for (int j=0; j< map[curpos][i].size(); j++) {
                if (movable(playerid, i, map[curpos][i][j], agents)) {
                    move.setTrans(map[curpos][i][j]);
                    res.push_back(move);
                }
            }
        }
    }
    return res;
}


//get a player's position
int board:: getPos(int playerid) {
    return positions[playerid];
}

//set a player's position
void board:: setPos(int playerid, int pos) {
    positions[playerid] = pos;
}

//check if the destination a player plan to be at is still available
bool board:: destOccupied(int dest) {
    for (int i =0; i<positions.size()-1; i++) {
        if (dest == positions[i]) return true;
    }
    return false;
}
//check if the move is legal
bool board:: movable(int playerid, int dest, char trans, vector<Player>& agents) {
    int curpos = positions[playerid];
    //if there is no available kind of transportation -> return false
    if (map[curpos][dest]=="") return false;
    else if (playerid!=5 && destOccupied(dest)==true) {
        //cout << "Your desired location is occupied by another detective. " << endl;
        return false;
    }
    else {
        for (int i=0; i< map[curpos][dest].size(); i++) {
            //for Mr. X
            if ( (map[curpos][dest][i]==trans || trans == 'L') && playerid==5) {
                //cout << "movable " << endl;
                return true;
                break;
            }
            //for other players
            else if ((agents[playerid].enoughTicket(trans) == true) && map[curpos][dest][i]==trans) return true;
        }
    }
    return false;
}
bool board:: movablewalltrans (int playerid, int dest, string alltrans, vector<Player>& agents) {
    for (int i =0; i <alltrans.size(); i++) {
        if (movable(playerid, dest, alltrans[i], agents)) return true;
    }
    return false;
}

string board:: getPlayerName(int playerid) {
    return playernames[playerid];
}

string board:: at(int row, int col) {
    return map[row][col];
}
char board:: getTicketName (int playerid, vector<Player>& agents, int dest) {
    string alltrans = map[positions[playerid]][dest];
    for (int i = 0; i<alltrans.size();i++) {
        if (agents[playerid].enoughTicket(alltrans[i]) == true) {
            //cout << "yessss" << endl;
            return alltrans[i];
        }
    }
    return ' ';
}

