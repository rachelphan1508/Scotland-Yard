
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
    cur_round=0;
    
    vector<int> spos = {13, 26, 29, 50, 53, 91, 94,112, 117, 132,138, 155, 174, 197};
    //give each person a random starting position (using 20 because the board is not yet finished)
    int v0 = rand() % 13 + 0;
    int v1 = rand() % 13 + 0;
    while (v1==v0) {
        v1 = rand() % 13 + 0;
    }
    int v2 = rand() % 13 + 0;
    while (v2==v1 || v2==v0) {
        v2 = rand() % 13 + 0;
    }
    int v3 = rand() % 13 + 0;
    while (v3==v2 || v3==v1 || v3==v0) {
        v3 = rand() % 13 + 0;
    }
    int v4 = rand() % 13 + 0;
    while (v4==v3 || v4==v2 || v4==v1 || v4==v0) {
        v4 = rand() % 13 + 0;
    }
    
    int v5 = rand() % 13 + 0;
    while (v5==v4 || v5==v3 || v5==v2 || v5==v1 || v5==v0) {
        v5 = rand() % 13 + 0;
    }
    
    myBoard.setPos(5, spos[v0]);
    myBoard.setPos(0, spos[v1]);
    myBoard.setPos(1, spos[v2]);
    myBoard.setPos(2, spos[v3]);
    myBoard.setPos(3, spos[v4]);
    myBoard.setPos(4, spos[v5]);

    
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

void GameManager:: playDetectiveBot() {
    myplanner.setRound(cur_round);
    myplanner.decideDetectiveMoves(agents, myBoard);
        
    for (int i=0; i< agents.size();i++) {
        //check if game over
        
        if (myBoard.getPos(i) == myBoard.getPos(5)) {
            cout << endl << "GAME OVER! MR.X WAS CAUGHT BY DETECTIVE " << myBoard.getPlayerName(i) <<"." << endl;
            gameOver = true;
            break;
        }
    }
    
    
}
void GameManager:: playDetective(int playerid) {
    int dest;
    char trans;
    bool movable;

    myBoard.printDetails(playerid, agents);
    cout << "All your possible moves: " << endl;
    vector<Travel> v = myBoard.possibleMoves(agents[playerid], playerid, agents);
    //cout << "here" << endl;
    for (int i=0; i < v.size(); i++) {
        cout << "Destination: " << v[i].getDest() << endl;
        cout << "Transportation: " << v[i].getTrans() << endl;
    }
    
    //here, replace by playing using the bot
    
    //cout << "right before bot" << endl;
    

    if (v.size()!=0) {
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
            MisterX.increaseTicket(trans);
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
void GameManager:: playRound(bool& dtused) {
    char doubleticket='N';
    // ORDER: MrX -> Blue -> Red -> Orange -> Green -> Yellow
    // MrX -> 5  --- Blue: 0 --- Red: 1 --- Orange: 2 --- Green: 3 --- Yellow: 4
    
    cout << endl <<  "We are currently at round " << cur_round << endl;

    // Mr X's turn
    cout << endl << "It's Mr. X's turn. " << endl;
    
    //ask if Mr.X wants to use a Double ticket
    if(MisterX.enoughTicket('D')==true && dtused ==false) {
    cout << "Mr.X, do you want to use a Double ticket? (Y/N)" << endl;
    cin >> doubleticket;
    }
    
    //if Mr. X's using a Double ticket
    if (doubleticket=='Y' && MisterX.enoughTicket('D')==true) {
        MisterX.decreaseTicket('D');
        dtused =true;
        playMrX();
        if (cur_round == 3 || cur_round==8 || cur_round == 13 ||cur_round == 18 || cur_round == 24) {
            //update Mr.X's last seen
            for(int i=0; i<agents.size();i++) {
                agents[i].updatelastseen(myBoard.getPos(5), myBoard);
                //cout << "here I update last seen... " << endl;
                agents[i].Display();
                
            }
            cout << "Mr. X is now at " << myBoard.getPos(5) << endl;
        }
        //reveal Mr.X's location if in round 3-8-13-18-24

    }
    //if not using a Double ticket
    else {
        dtused = false;
        playMrX();
        if (cur_round == 3 || cur_round==8 || cur_round == 13 ||cur_round == 18 || cur_round == 24) {
            //update Mr.X's last seen
            for(int i=0; i<agents.size();i++) {
                agents[i].updatelastseen(myBoard.getPos(5), myBoard);
                agents[i].Display();
                
            }
            cout << "Mr. X is now at " << myBoard.getPos(5) << endl;
            //here, save Mr.X current location
        }
        //detectives' turn
        if (gameOver!=true) {
            agents[0].Display();
            if (computer==true) playDetectiveBot();
            else {
                
                for (int i=0; i<5; i++) {
                    playDetective(i);
                    cout << "Playing Dectective " << myBoard.getPlayerName(i) << endl;
                    if (gameOver==true) break;
                }
            }
        }
    

    }
    
}

//play the complete game
void GameManager:: playFullGame() {
    cur_round =1;
    bool dtused = false;
    while (cur_round!= 25 || gameOver== false) {
        playRound(dtused);
        cur_round++;
        if (gameOver==true) break;
    }
    if (cur_round==25) {
        cout << "Mr.X won the game!" << endl;
        gameOver=true;
    }
}
