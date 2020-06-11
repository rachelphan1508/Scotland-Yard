
#include "Player.h"


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
    else return true;
}

vector<int> Player:: getMrXloc() {
    return mrXlocation;
    
}

void Player:: updateMrX(char trans, board* myboard) {
    //for every of mr X's possible location, update it with the next possible location he can be at with the ticket he just used
    vector<int> newpos;
    for (int i=0; i<mrXlocation.size();i++) {
        //go through the board
        for (int j=0; j<200; j++) {
            string at = myboard->at(i,j);
            
            if (at!="") {
                if (trans == 'L') newpos.push_back(j);
                else for (char c : at) {
                    if (c == trans) {
                        newpos.push_back(j);
                    }
                }
            }
        }
    }
    //delete all duplicates
    
    //replace the previous mrX
    
    
}

void Player:: updatelastseen(int pos, board* myboard) {
    lastseen = pos;
    //here, update all Mr.X's possible locations
    mrXlocation.resize(1);
    mrXlocation[0] = pos;
}
