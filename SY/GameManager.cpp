
#include "GameManager.h"

GameManager:: GameManager() {
    
}

//this function sets up the game
void GameManager:: setUp() {
    
    //set up the board
    myBoard.setUp();
    gameOver = false;
    computer =false;
    srand(time(0));
    //give each person a random starting position (using 20 because the board is not yet finished)
    int v0 = rand() % 200 + 1;
    int v1 = rand() % 200 + 1;
    while (v1==v0) {
        v1 = rand() % 200 + 1;
    }
    int v2 = rand() % 200 + 1;
    while (v2==v1 || v2==v0) {
        v2 = rand() % 200 + 1;
    }
    int v3 = rand() % 200 + 1;
    while (v3==v2 || v3==v1 || v3==v0) {
        v3 = rand() % 200 + 1;
    }
    int v4 = rand() % 200 + 1;
    while (v4==v3 || v4==v2 || v4==v1 || v4==v0) {
        v4 = rand() % 200 + 1;
    }
    
    int v5 = rand() % 200 + 1;
    while (v5==v4 || v5==v3 || v5==v2 || v5==v1 || v5==v0) {
        v5 = rand() % 200 + 1;
    }
    
    myBoard.setPos(5, v0);
    myBoard.setPos(0, v1);
    myBoard.setPos(1, v2);
    myBoard.setPos(2, v3);
    myBoard.setPos(3, v4);
    myBoard.setPos(4, v5);

    
    //set the default numbers of tickets for each player
    
    //MrX: 4 taxis, 3 buses, 3 UG, 5 black, 2 2X
    MisterX.setTaxi(4);
    MisterX.setBus(3);
    MisterX.setUg(3);
    MisterX.setDouble(2);
    MisterX.setBlack(5);
    
    cout << "Mr. X is at " << myBoard.getPos(5) << endl;
    
    //each Detective: 10 taxis, 8 buses, 4 UG
    agents.resize(5);
    for (int i =0; i<5; i++) {
        agents[i].setTaxi(10);
        agents[i].setBus(8);
        agents[i].setUg(4);
        agents[i].setDouble(0);
        agents[i].setBlack(0);
        cout << "Detective " << myBoard.getPlayerName(i) << " is at " << myBoard.getPos(i) << endl;
    }
    
}

void GameManager:: setComputer() {
    computer = true;
}

// do the move for each detective
void GameManager:: playDetective(int playerid) {
    int dest;
    char trans;
    bool movable;

    cout << endl << "It's Detective "<<  myBoard.getPlayerName(playerid) << "'s turn. " << endl;
    
    agents[playerid].Display();
    cout << "Detective " << myBoard.getPlayerName(playerid) << " is currently at " << myBoard.getPos(playerid) << endl;
    
    //print all kind of transportations
    cout << "Detective " << myBoard.getPlayerName(playerid)  << " has: " << endl;
    cout << agents[playerid].getBus() << " bus tickets." << endl;
    cout << agents[playerid].getUg() << " underground tickets." << endl;
    cout << agents[playerid].getTaxi() << " taxi tickets." << endl;
    cout << "All your possible moves: " << endl;
    vector<Travel> v = myBoard.possibleMoves(agents[playerid], playerid, agents);
    //cout << "here" << endl;
    for (int i=0; i < v.size(); i++) {
        cout << "Destination: " << v[i].getDest() << endl;
        cout << "Transportation: " << v[i].getTrans() << endl;
    }
    
    //here, replace by playing using the bot
    
    //cout << "right before bot" << endl;
    
    if (computer==true) {
    D.moveDetectives(agents, myBoard, playerid);
    for (int i=0; i< agents.size();i++) {
        agents[i].updateFromDetective(myBoard, playerid);
    }
    
    //check if game over
    if (myBoard.getPos(playerid) == myBoard.getPos(5)) {
        cout << "GAME OVER! MR.X WAS CAUGHT." << endl;
        gameOver = true;
    }
    }
    else if (v.size()!=0) {
            cout << "Enter your desired destination: " << endl;
            cin >> dest;
            cout << "Enter your kind of transportation (T,B,U)" << endl;
            cin >> trans;
            
            movable = myBoard.movable(playerid, dest, trans, agents);
            if (movable==true){
                cout << "Detective " << myBoard.getPlayerName(playerid) << " just moved" << endl;
            }
            
            else while (movable == false) {
                cout << "Detective " << myBoard.getPlayerName(playerid) << " just made an illegal move. Do your move again, sir." << endl;
                cout << "Enter your desired destination: " << endl;
                cin >> dest;
                cout << "Enter your kind of transportation (T,B,U)" << endl;
                cin >> trans;
                movable = myBoard.movable(playerid, dest, trans, agents);
            }
            myBoard.setPos(playerid, dest);
            agents[playerid].decreaseTicket(trans);
            for (int i=0; i< agents.size();i++) {
                agents[i].updateFromDetective(myBoard, playerid);
            }
     
            //check if game over
            if (myBoard.getPos(playerid) == myBoard.getPos(5)) {
            cout << "GAME OVER! MR.X WAS CAUGHT." << endl;
            gameOver = true;
     }
     
        

    }
    else {
            cout << "Detective " << myBoard.getPlayerName(playerid) << "can't move anywhere." << endl;
    }
    
    
}

void GameManager:: playMrX() {
    
    //PRINT ALL DETECTIVES' LOCATIONS BEFORE MR.X'S MOVE
    
    for (int i = 0; i<5; i++) {
        cout << "Detective " << myBoard.getPlayerName(i) << " is at " << myBoard.getPos(i) << endl;
    }

    
    int dest;
    char trans;
    bool movable = false;
    

    //get the destination + means of transportation
    vector<Travel> v = myBoard.possibleMoves(MisterX, 5, agents);
    if (v.size()==0) {
        cout << "Mr.X can't move anywhere else." << endl;
        gameOver = true;
    }
    else {
        //print all special kind of transportation.
        cout << "Mr. X's special tickets: " << endl;
        cout << MisterX.getBlack() << " Black tickets." << endl;
        cout << MisterX.getDouble() << " Double tickets." << endl;
        
        //print all possible moves
        
        cout << "All your possible moves: " << endl;
        for (int i=0; i < v.size(); i++) {
            cout << "Destination: " << v[i].getDest() << endl;
            cout << "Transportation: " << v[i].getTrans() << endl;
        }

        
        //if Mr. X doesn't use a Double ticket
        //if (MisterX.enoughTicket('D')==false && doubleticket=='y') cout << "Sorry Mr.X, you don't have enough Double tickets to use." << endl;
        //if (doubleticket != 'y' || MisterX.enoughTicket('D')==false) {
            
            cout << "Enter your desired destination: " << endl;
            cin >> dest;
            cout << "Enter your kind of transportation (T,B,U,L)" << endl;
            cin >> trans;
            
            movable = myBoard.movable(5, dest, trans, agents);
            
            while ((myBoard.movable(5, dest, trans,agents)) == false) {
                cout << "Mr.X just made an illegal move. Do your move again, Mr. X." << endl;
                cout << "Enter your desired destination: " << endl;
                cin >> dest;
                cout << "Enter your kind of transportation (T,B,U,L)" << endl;
                cin >> trans;
                movable = myBoard.movable(5, dest, trans, agents);
            }
            myBoard.setPos(5, dest);
            MisterX.decreaseTicket(trans);
            if (trans == 'L' ) {
                cout << "Mr.X just used a Black ticket." << endl;
            }
            else if (trans == 'T' ) {
                cout << "Mr.X just used a Taxi." << endl;
            }
            else if (trans == 'B' ) {
                cout << "Mr.X just used a Bus." << endl;
            }
            else if (trans == 'U' ) {
                cout << "Mr.X just used an Underground ticket." << endl;
            }
            
        for(int i=0;i <agents.size();i++) {
                agents[i].updateMrX(trans, myBoard);
                //cout << "here I updated Mr.X's trans" << endl;
                
        }
            
            //check if Mr.X's destination is one of the detectives' current location
            if (myBoard.destOccupied(dest)==true) {
                gameOver = true;
                cout << "Mr.X, you just moved to one of the detectives' location. GAME OVER!" << endl;
            }

    
}
}

//play each round
void GameManager:: playRound(int& num_round, bool& dtused) {
    
    agents[0].Display();
    char doubleticket='N';
    // ORDER: MrX -> Blue -> Red -> Orange -> Green -> Yellow
    // MrX -> 5  --- Blue: 0 --- Red: 1 --- Orange: 2 --- Green: 3 --- Yellow: 4
    
    cout << endl <<  "We are currently at round " << num_round << endl;

    // Mr X's turn
    cout << endl << "It's Mr. X's turn. " << endl;
    //ask if Mr.X wants to use a Double ticket
    if(MisterX.enoughTicket('D')==true && dtused ==false) {
    cout << "Mr.X, do you want to use a Double ticket? (Y/N)" << endl;
    cin >> doubleticket;
    }
    if (doubleticket=='Y' && MisterX.enoughTicket('D')==true) {
        MisterX.decreaseTicket('D');
        dtused =true;
        playMrX();
        if (num_round == 3 || num_round==8 || num_round == 13 ||num_round == 18 || num_round == 24) {
            //update Mr.X's last seen
            for(int i=0; i<agents.size();i++) {
                agents[i].updatelastseen(myBoard.getPos(5), myBoard);
                //cout << "here I update last seen... " << endl;
                agents[i].Display();
                
            }
            cout << "Mr. X is now at " << myBoard.getPos(5) << endl;
            //here, save Mr.X current location
        }
        //reveal Mr.X's location if in round 3-8-13-18-24

    }
    
    else {
        dtused = false;
        playMrX();
        if (num_round == 3 || num_round==8 || num_round == 13 ||num_round == 18 || num_round == 24) {
            //update Mr.X's last seen
            for(int i=0; i<agents.size();i++) {
                agents[i].updatelastseen(myBoard.getPos(5), myBoard);
                //cout << "here I update last seen... " << endl;
                agents[i].Display();
                
            }
            cout << "Mr. X is now at " << myBoard.getPos(5) << endl;
            //here, save Mr.X current location
        }
        //detectives' turn
        if (gameOver!=true) {
            for (int i=0; i<5; i++) {
                playDetective(i);
                cout << "Playing Dectective " << myBoard.getPlayerName(i) << endl;
                if (gameOver==true) break;
            }
        }
    

    }
    
}

//play the complete game
void GameManager:: playFullGame() {
    int cur_round =1;
    bool dtused = false;
    while (cur_round!= 25 || gameOver== false) {
        playRound(cur_round, dtused);
        cur_round++;
        if (gameOver==true) break;
    }
    if (cur_round==25) {
        cout << "Mr.X won the game!" << endl;
        gameOver=true;
    }
}
