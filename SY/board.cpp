
#include "board.h"

using namespace std;


void board:: setUp() {
    // ORDER: MrX -> Blue -> Red -> Orange -> Green -> Yellow
    // MrX -> 5  --- Blue: 0 --- Red: 1 --- Orange: 2 --- Green: 3 --- Yellow: 4
    map.resize(200);
    positions.resize(6);
    for (int i=0; i< map.size();i++) {
        map[i].resize(199);
    }
    
    //set up with a map of " "
    for (int i=0; i<199; i++) {
        for (int j=0; j<199; j++) {
            map[i][j] = "";
        }
    }
    
    //fill up the map with transportation
    // B = Bus, T = Taxi, U = Underground, R = Boat (River)
    map[1][8] = "T";
    map[1][9] = "T";
    map[1][46] = "BU";
    map[1][58] = "B";
    map[2][10] = "T";
    map[2][20] = "T";
    map[3][4] = "T";
    map[3][11] = "T";
    map[3][12] = "T";
    map[3][22] = "B";
    map[4][3] = "T";
    map[4][13] = "T";
    map[5][15] = "T";
    map[5][16] = "T";
    map[6][7] = "T";
    map[6][29] = "T";
    map[7][6] = "T";
    map[7][17] = "T";
    map[7][42] = "B";
    map[8][1] = "T";
    map[8][18] = "T";
    map[8][19] = "T";
    map[9][1] = "T";
    map[9][19] = "T";
    map[9][20] = "T";
    map[10][2] = "T";
    map[10][11] = "T";
    map[10][21] = "T";
    map[10][34] = "T";
    map[11][3] = "T";
    map[11][10] = "T";
    map[11][22] = "T";
    map[12][3] = "T";
    map[12][23] = "T";
    map[13][4] = "T";
    map[13][14] = "TB";
    map[13][23] = "TB";
    map[13][24] = "T";
    map[13][52] = "B";
    map[13][46] = "U";
    map[13][67] = "U";
    map[13][89] = "U";
    map[14][13] = "TB";
    map[14][15] = "TB";
    map[14][25] = "T";
    map[15][5] = "T";
    map[15][14] = "TB";
    map[15][16] = "T";
    map[15][26] = "T";
    map[15][28] = "T";
    map[15][29] = "B";
    map[15][41] = "B";
    map[16][5] = "T";
    map[16][15] = "T";
    map[16][28] = "T";
    map[16][29] = "T";
    map[17][7] = "T";
    map[17][29] = "T";
    map[17][30] = "T";
    map[18][8] = "T";
    map[18][31] = "T";
    map[18][43] = "T";
    map[19][8] = "T";
    map[19][9] = "T";
    map[19][32] = "T";
    map[20][2] = "T";
    map[20][9] = "T";
    map[20][33] = "T";
    map[21][10] = "T";
    map[21][33] = "T";
    map[22][11] = "T";
    map[22][23] = "TB";
    map[22][34] = "TB";
    map[22][35] = "T";
    map[22][65] = "B";
    map[23][12] = "T";
    map[23][13] = "TB";
    map[23][22] = "TB";
    map[23][37] = "T";
    map[23][67] = "B";
    map[24][13] = "T";
    map[24][37] = "T";
    map[24][38] = "T";
    map[25][14] = "T";
    map[25][38] = "T";
    map[25][39] = "T";
    map[26][15] = "T";
    map[26][27] = "T";
    map[26][39] = "T";
    map[27][26] = "T";
    map[27][28] = "T";
    map[27][40] = "T";
    map[28][15] = "T";
    map[28][16] = "T";
    map[28][27] = "T";
    map[28][41] = "T";
    map[29][6] = "T";
    map[29][16] = "T";
    map[29][17] = "T";
    map[29][41] = "TB";
    map[29][42] = "TB";
    map[29][13] = "T";
    map[29][55] = "B";
    map[30][17] = "T";
    map[30][42] = "B";
    map[31][18] = "T";
    map[31][43] = "T";
    map[31][44] = "T";
    map[32][19] = "T";
    map[32][33] = "T";
    map[32][44] = "T";
    
}

vector<Travel> board:: possibleMoves(Player myplayer, int playerid, vector<Player>& agents) {
    //get current location
    int curpos = positions[playerid];
    vector<Travel> res;
    Travel move;
    
    //get all possible moves from that location
    for (int i=0; i<199; i++) {
        if (map[curpos][i].size() >= 1) {
            //cout << ">=1" << endl;
            // there is more than one kind of transportation
            move.setDest(i);
            for (int j=0; j< map[curpos][i].size(); j++) {
                if (movable(playerid, i, map[curpos][i][j], agents)) {
                    move.setTrans(map[curpos][i][j]);
                    res.push_back(move);
                }
            }
        }
    }
    cout << "size " << res.size() << endl;
    return res;
}

int board:: getPos(int playerid) {
    return positions[playerid];
}

void board:: setPos(int playerid, int pos) {
    positions[playerid] = pos;
}

bool board:: movable(int playerid, int dest, char trans, vector<Player>& agents) {
    int curpos = positions[playerid];
    cout << "current pos " << curpos << endl;
    if (map[curpos][dest]=="") return false;
    else {
        for (int i=0; i< map[curpos][dest].size(); i++) {
            if (map[curpos][dest][i]==trans && playerid==5) {
                cout << "movable " << endl;
                return true;
                break;
            }
            else if ((agents[playerid].enoughTicket(trans) == true) || map[curpos][dest][i]==trans) return true;
        }
    }
    return false;
}

