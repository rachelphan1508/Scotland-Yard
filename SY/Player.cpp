
#include "Player.h"
#include "board.h"
#include <algorithm>



// initialize Player class that holds a player's number of tickets, Mr.X's last seen location & Mr.X's all possible locations
Player:: Player() {
    mrXlocation = {13, 26, 29, 50, 53, 91, 94,112, 117, 132, 138, 155, 174, 197};
    lastseen =0;
    numTaxi = 0 ;
    numBus = 0;
    numUg = 0;
    numBlack = 0;
    numDouble = 0;
}

//set the number of Underground ticket
void Player:: setUg(int val){
    numUg = val;
}


//set the number of Bus tickets
void Player:: setBus(int val) {
    numBus = val;
}


//set the number of Taxi tickets
void Player:: setTaxi(int val) {
    numTaxi = val;
}

//set the number of Black tickets
void Player:: setBlack(int val) {
    numBlack = val;
}


//set the number of Double tickets
void Player:: setDouble(int val) {
    numDouble = val;
}



//get the number of UG tickets
int Player:: getUg() {
    return numUg;
}

//get the number of Bus tickets
int Player:: getBus() {
    return numBus;
}

//get the number of Tazi tickets
int Player:: getTaxi() {
    return numTaxi;
}

//get the number of Double tickets
int Player:: getDouble() {
    return numDouble;
}

//get the number of Black tickets
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

//increase the number of tickets (used for Mr.X)
void Player:: increaseTicket(char trans) {
    if (trans == 'U') numUg++;
    else if (trans == 'B') numBus++;
    else if (trans == 'T') numTaxi++;
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

//get all Mr.X's possible locations
vector<int> Player:: getMrXloc() {
    return mrXlocation;
    
}

//update the vector of Mr.X's locations whenever a detective makes a move
void Player:: updateFromDetective (board& myboard, int playerid) {
    int pos = myboard.getPos(playerid);
    for (int i=0; i< mrXlocation.size(); i++) {
        if (mrXlocation[i] == pos) {
            mrXlocation.erase(mrXlocation.begin()+i);
            break;
        }
    }
}

// update Mr.X's locations based on each detective's planned move
void Player:: updateFromPlanner(board& myboard, int val) {
    for (int i=0; i< mrXlocation.size(); i++) {
        if (mrXlocation[i] == val) {
            mrXlocation.erase(mrXlocation.begin()+i);
            break;
        }
    }
}

//update Mr.X's locations after each round based on his previous possible locations and the ticket he used
void Player:: updateMrX(char trans, board& myboard) {
    vector<int> v;
    v.resize(0);
    
    for (int i =0; i<5; i++) {
        updateFromDetective(myboard, i);
    }
    for (int i=0; i<mrXlocation.size();i++) {
        //go through the board
        for (int j=0; j<200; j++) {
            string at = myboard.at(mrXlocation[i],j);
            if (at!="" && !myboard.destOccupied(j)) {
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

// return Mr.X's possible locations next round
vector<int> Player:: getNextRound(board& myboard) {
    vector<int> v(0);
    for (int i=0; i<mrXlocation.size();i++) {
        //go through the board
        for (int j=0; j<200; j++) {
            string at = myboard.at(mrXlocation[i],j);
            if (at!="" && !myboard.destOccupied(j)) {
                    v.push_back(j);

            }
        }
    }
    //delete all duplicates
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()), v.end());
    return v;
    
}

//update Mr.X's possible locations when his location is revealed
void Player:: updatelastseen(int pos, board& myboard) {
    lastseen = pos;
    //here, update all Mr.X's possible locations
    mrXlocation.resize(1);
    //cout << "size " << mrXlocation.size();
    mrXlocation[0] = pos;
}

//Display Mr.X's current possible locations
void Player:: Display() {
    
    cout << endl << "All Mr.X's possible locations now: " << endl;
    for (int i=0; i<mrXlocation.size();i++) {
        cout << mrXlocation[i] << " ";
    }
    cout << endl;
}
