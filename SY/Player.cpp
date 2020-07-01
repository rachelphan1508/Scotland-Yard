
#include "Player.h"
#include "board.h"
#include <algorithm>


Player:: Player() {
    mrXlocation.resize(200);
    for (int i=0; i<200; i++) {
        mrXlocation[i] = i+1;
    }
    lastseen =0;
}
void Player:: setUg(int val){
    numUg = val;
}

void Player:: setBus(int val) {
    numBus = val;
}

void Player:: setTaxi(int val) {
    numTaxi = val;
}


void Player:: setBlack(int val) {
    numBlack = val;
}

void Player:: setDouble(int val) {
    numDouble = val;
}




int Player:: getUg() {
    return numUg;
}
int Player:: getBus() {
    return numBus;
}
int Player:: getTaxi() {
    return numTaxi;
}
int Player:: getDouble() {
    return numDouble;
}
int Player:: getBlack() {
    return numBlack;
}

//decrease the number of tickets when a ticket is used
void Player:: decreaseTicket(char trans) {
    if (trans == 'U') numUg--;
    else if (trans == 'B') numBus--;
    else if (trans == 'T') numTaxi--;
    else if (trans == 'L') numBlack--;
    else if (trans == 'D') numDouble--;
    
}


//check if a player has enough tickets to use
bool Player:: enoughTicket(char trans) {
    if (trans == 'U' && getUg()==0) {
        return false;
    }
    else if (trans == 'B' && getBus() == 0) return false;
    else if (trans == 'T' && getTaxi() == 0) return false;
    else if (trans == 'D' && getDouble()== 0) return false;
    else if (trans == 'L' && getBlack()==0) return false;
    else return true;
}

vector<int> Player:: getMrXloc() {
    return mrXlocation;
    
}

//update the vector of Mr.X's locations whenever a detective makes a move
void Player:: updateFromDetective (board& myboard, int playerid) {
    int pos = myboard.getPos(playerid);
    if (mrXlocation.size() == 200) return;
    for (int i=0; i< mrXlocation.size(); i++) {
        if (mrXlocation[i] == pos) {
            mrXlocation.erase(mrXlocation.begin()+i);
            break;
        }
    }
}

void Player:: updateMrX(char trans, board& myboard) {
    //for every of mr X's possible location, update it with the next possible location he can be at with the ticket he just used
    //cout << "trans: " << trans << endl;
    vector<int> v;
    v.resize(0);
    if (mrXlocation.size() ==200) return;
    for (int i=0; i<mrXlocation.size();i++) {
        //go through the board
        for (int j=0; j<200; j++) {
            string at = myboard.at(mrXlocation[i],j);
            //cout << at << endl;
            //cout << "inside" << endl;
            if (at!="") {
                //if Mr.X's used a black ticket, he can be at any location that has a connection with his previous location
                if (trans == 'L') {
                    v.push_back(j);
                }
                //if not, only get the locations that has connections with the ticket he used (Bus station for Bus, ... )
                else for (int k=0; k<at.size(); k++) {
                    if (at[k] == trans) {
                        v.push_back(j);
                    }
                }
            }
        }
    }
    //delete all duplicates
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()), v.end());
    
    
    //replace the previous vector with the new one
    mrXlocation.resize(v.size());
    for (int i=0; i<v.size(); i++) {
        mrXlocation[i] = v[i];
    }
    
    
}

void Player:: updatelastseen(int pos, board& myboard) {
    lastseen = pos;
    //here, update all Mr.X's possible locations
    mrXlocation.resize(1);
    //cout << "size " << mrXlocation.size();
    mrXlocation[0] = pos;
}

void Player:: Display() {
    cout << "Mr.X's possible locations now: " << endl;
    for (int i=0; i<mrXlocation.size();i++) {
        cout << mrXlocation[i] << " ";
    }
    cout << endl;
}
