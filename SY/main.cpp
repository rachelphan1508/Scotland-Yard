#include "GameManager.h"
#include <iostream>

using namespace std;

int main() {
    string again = "Y";
    while (again=="Y")
    {
        GameManager g1;
        string answer;
        cout << "Play with Computer? (Y/N) " << endl;
        cin >> answer;
        g1.setUp();
        if (answer=="Y") g1.setComputer();
        g1.playFullGame();
        //ask if user wants to play again
        cout << "Do you want to play again? (Y/N)" << endl;
        cin >> again;
    }
}
