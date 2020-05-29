
#include "GameManager.h"

GameManager:: GameManager() {
    
}

void GameManager:: setUp() {
    
    //set up the board
    myBoard.setUp();
    gameOver = false;
    //srand(time(0));
    //give each person a starting position
    int v0 = rand() % 20 + 1;
    int v1 = rand() % 20 + 1;
    while (v1==v0) {
        v1 = rand() % 20 + 1;
    }
    int v2 = rand() % 20 + 1;
    while (v2==v1 || v2==v0) {
        v2 = rand() % 20 + 1;
    }
    int v3 = rand() % 20 + 1;
    while (v3==v2 || v3==v1 || v3==v0) {
        v3 = rand() % 20 + 1;
    }
    int v4 = rand() % 20 + 1;
    while (v4==v3 || v3==v2 || v2==v1 || v1==v0) {
        v4 = rand() % 20 + 1;
    }
    
    int v5 = rand() % 20 + 1;
    while (v5==v4 || v5==v3 || v5==v2 || v5==v1 || v5==v0) {
        v5 = rand() % 20 + 1;
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
        cout << "Detective " << i+1 << " is at " << myBoard.getPos(i) << endl;
    }
    
}

void GameManager:: playerTurn(int playerid) {
    int dest;
    char trans;

        cout << "It's Detective "<<  playerid << "'s turn. " << endl;
        if (myBoard.possibleMoves(agents[playerid], playerid, agents).size()!=0) {
            cout << "Enter your desired destination: " << endl;
            cin >> dest;
            cout << "Enter your kind of transportation (T,B,U)" << endl;
            cin >> trans;
            
            //this loop may suck when a detective runs of of ticket
            while (!(myBoard.movable(myBoard.getPos(playerid), dest, trans, agents)) || !(agents[playerid].enoughTicket(trans)) ) {
                cout << "Detective " << playerid+1 << " just made an illegal move. Do your move again, sir." << endl;
                cin >> dest;
                cin >> trans;
            }
            myBoard.setPos(playerid, dest);
            agents[playerid].Move(trans);
            
            //check if game over
            if (myBoard.getPos(playerid) == myBoard.getPos(5)) {
                cout << "GAME OVER! MR.X WAS CAUGHT." << endl;
                gameOver = true;
            }
        }
        else {
            cout << "Detective " << playerid << "can't move anywhere." << endl;
        }
    
    
}

void GameManager:: playRound(int& num_round) {
    
    int dest;
    char trans;
    //bool blackUsed = false;

    // ORDER: MrX -> Blue -> Red -> Orange -> Green -> Yellow
    // MrX -> 5  --- Blue: 0 --- Red: 1 --- Orange: 2 --- Green: 3 --- Yellow: 4
    
    cout << "We are currently at round " << num_round << endl;
    
    // Mr X's turn
    cout << "It's Mr. X's turn. " << endl;
    //get the destination + means of transportation
    if (myBoard.possibleMoves(MisterX, 5,agents).size()!=0) {
        cout << "Enter your desired destination: " << endl;
        cin >> dest;
        cout << "Enter your kind of transportation (T,B,U,L)" << endl;
        cin >> trans;
        
        //print all possible moves
        vector<Travel> v = myBoard.possibleMoves(MisterX, 5, agents);
        for (int i=0; i < v.size(); i++) {
            cout << "Destination: " << v[i].getDest() << endl;
            cout << "Transportation: " << v[i].getTrans() << endl;
        }
    
        while ((myBoard.movable(myBoard.getPos(5), dest, trans,agents)) == false) {
        cout << "Mr.X just made an illegal move. Do your move again, Mr. X." << endl;
        cout << "Enter your desired destination: " << endl;
        cin >> dest;
        cout << "Enter your kind of transportation (T,B,U,L)" << endl;
        cin >> trans;
    }
        cout << "Mr.X just moved" << endl;
    myBoard.setPos(5, dest);
    
    MisterX.Move(trans);
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
        
    }
    else {
        cout << "Mr.X can't move anywhere else." << endl;
        gameOver = true;
    }
    //have to save Mr. X's trans somewhere & hide it if Mr.X's using Black


    //reveal Mr.X's location if in round 3-8-13-18-24
    if (num_round == 3 || num_round==8 || num_round == 13 ||num_round == 18 || num_round == 24) {
        cout << "Mr. X is now at " << myBoard.getPos(5) << endl;
    }
    //have to change the cur_round number if Mr.X used a double!
    
    //detectives' turn
    int cur_player = 0;
    bool roundOver = false;
    while (!gameOver || !roundOver) {
        playerTurn(cur_player);
        if (cur_player==4) { // done with all detectives
            roundOver = true;
        }
        cur_player++;
        
    }
    
}

void GameManager:: playFullGame() {
    int cur_round =1;
    while (cur_round!= 25 || gameOver== false) {
        playRound(cur_round);
        cur_round++;
    }
    if (cur_round==25) {
        cout << "Mr.X won the game!" << endl;
        gameOver=true;
    }
}
