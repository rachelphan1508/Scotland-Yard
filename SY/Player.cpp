//
//  Agent.cpp
//  SY
//
//  Created by Rachel Phan on 5/27/20.
//  Copyright © 2020 Rachel Phan. All rights reserved.
//

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

void Player:: decreaseTaxi() {
    numTaxi--;
}
void Player:: decreaseBus() {
    numBus--;
}
void Player:: decreaseUg() {
    numUg--;
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

void Player:: Move(char trans) {
    if (trans == 'U') decreaseUg();
    else if (trans == 'B')  decreaseBus();
    else if (trans == 'T') decreaseTaxi();
}

bool Player:: enoughTicket(char trans) {
    if (trans == 'U' && getUg()==0) {
        return false;
    }
    else if (trans == 'B' && getBus() == 0) return false;
    else if (trans == 'T' && getTaxi() == 0) return false;
    else return true;
}
