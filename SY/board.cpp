
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
    map[32][45] = "T";
    map[33][20] = "T";
    map[33][21] = "T";
    map[33][32] = "T";
    map[33][46] = "T";
    map[34][10] = "T";
    map[34][22] = "TB";
    map[34][47] = "T";
    map[34][48] = "T";
    map[34][46] = "B";
    map[34][63] = "B";
    map[35][22] = "T";
    map[35][36] = "T";
    map[35][48] = "T";
    map[35][65] = "T";
    map[36][35] = "T";
    map[36][37] = "T";
    map[36][49] = "T";
    map[37][23] = "T";
    map[37][24] = "T";
    map[37][36] = "T";
    map[37][50] = "T";
    map[38][24] = "T";
    map[38][25] = "T";
    map[38][50] = "T";
    map[38][51] = "T";
    map[39][25] = "T";
    map[39][26] = "T";
    map[39][51] = "T";
    map[39][52] = "T";
    map[40][27] = "T";
    map[40][41] = "T";
    map[40][52] = "T";
    map[40][53] = "T";
    map[41][28] = "T";
    map[41][29] = "TB";
    map[41][40] = "T";
    map[41][54] = "T";
    map[41][15] = "B";
    map[41][52] = "B";
    map[41][87] = "B";
    map[42][29] = "TB";
    map[42][30] = "T";
    map[42][56] = "T";
    map[42][72] = "TB";
    map[42][7] = "B";
    map[42][7] = "B";
    map[43][18] = "T";
    map[43][31] = "T";
    map[43][57] = "T";
    map[44][31] = "T";
    map[44][32] = "T";
    map[44][58] = "T";
    map[45][32] = "T";
    map[45][46] = "T";
    map[45][58] = "T";
    map[45][59] = "T";
    map[45][60] = "T";
    map[46][33] = "T";
    map[46][45] = "T";
    map[46][47] = "T";
    map[46][61] = "T";
    map[46][1] = "BU";
    map[46][34] = "B";
    map[46][58] = "B";
    map[46][78] = "B";
    map[46][13] = "U";
    map[46][74] = "U";
    map[46][79] = "U";
    map[47][34] = "T";
    map[47][46] = "T";
    map[47][62] = "T";
    map[48][34] = "T";
    map[48][35] = "T";
    map[48][62] = "T";
    map[48][63] = "T";
    map[49][36] = "T";
    map[49][50] = "T";
    map[49][66] = "T";
    map[50][37] = "T";
    map[50][38] = "T";
    map[50][49] = "T";
    map[51][38] = "T";
    map[51][39] = "T";
    map[51][52] = "T";
    map[51][52] = "T";
    map[51][67] = "T";
    map[51][68] = "T";
    map[52][39] = "T";
    map[52][40] = "T";
    map[52][51] = "T";
    map[52][69] = "T";
    map[52][13] = "B";
    map[52][41] = "B";
    map[52][67] = "B";
    map[52][86] = "B";
    map[53][40] = "T";
    map[53][54] = "T";
    map[53][69] = "T";
    map[54][41] = "T";
    map[54][53] = "T";
    map[54][55] = "T";
    map[54][70] = "T";
    map[55][54] = "T";
    map[55][71] = "T";
    map[55][29] = "B";
    map[55][89] = "B";
    map[56][42] = "T";
    map[56][91] = "T";
    map[57][43] = "T";
    map[57][59] = "T";
    map[57][73] = "T";
    map[58][44] = "T";
    map[58][45] = "T";
    map[58][57] = "T";
    map[58][59] = "T";
    map[58][74] = "T";
    map[58][75] = "T";
    map[58][1] = "B";
    map[58][46] = "B";
    map[58][74] = "B";
    map[58][77] = "B";
    map[59][45] = "T";
    map[59][58] = "T";
    map[59][75] = "T";
    map[59][76] = "T";
    map[60][45] = "T";
    map[60][61] = "T";
    map[60][76] = "T";
    map[61][46] = "T";
    map[61][60] = "T";
    map[61][62] = "T";
    map[61][76] = "T";
    map[61][78] = "T";
    map[62][47] = "T";
    map[62][48] = "T";
    map[62][61] = "T";
    map[62][79] = "T";
    map[63][48] = "T";
    map[63][64] = "T";
    map[63][79] = "TB";
    map[63][80] = "T";
    map[63][34] = "B";
    map[63][65] = "B";
    map[63][100] = "B";
    map[64][63] = "T";
    map[64][65] = "T";
    map[64][81] = "T";
    map[65][66] = "T";
    map[65][82] = "T";
    map[65][22] = "B";
    map[65][63] = "B";
    map[65][67] = "B";
    map[65][82] = "B";
    map[66][49] = "T";

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
    for (int i =0; i<positions.size(); i++) {
        if (dest == positions[i]) return true;
    }
    return false;
}
//check if the move is legal
bool board:: movable(int playerid, int dest, char trans, vector<Player>& agents) {
    int curpos = positions[playerid];
    //cout << "current pos " << curpos << endl;
    //if there is no available kind of transportation -> return false
    if (map[curpos][dest]=="") return false;
    else if (playerid!=5 && destOccupied(dest)==true) {
        cout << "Your desired location is occupied by another detective. " << endl;
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

