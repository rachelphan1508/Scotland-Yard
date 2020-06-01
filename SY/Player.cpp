
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

int Player:: getUg() {
    return numUg;
}
int Player:: getBus() {
    return numBus;
}
int Player:: getTaxi() {
    return numTaxi;
}

//decrease the number of tickets when a ticket is used
// (!) need to add - decrease Black Tickets  & Boat Tickets
void Player:: decreaseTicket(char trans) {
    if (trans == 'U') numUg--;
    else if (trans == 'B') numBus--;
    else if (trans == 'T') numTaxi--;
}


//check if a player has enough tickets to use
bool Player:: enoughTicket(char trans) {
    if (trans == 'U' && getUg()==0) {
        return false;
    }
    else if (trans == 'B' && getBus() == 0) return false;
    else if (trans == 'T' && getTaxi() == 0) return false;
    else return true;
}
