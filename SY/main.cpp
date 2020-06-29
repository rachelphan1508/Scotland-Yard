#include "GameManager.h"
#include <iostream>

using namespace std;

int main() {
    /*
    Queue* queue = createQueue(1000);
    
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    
    cout << dequeue(queue)
    << " dequeued from queue\n";
    
    cout << "Front item is "
    << front(queue) << endl;
    cout << "Rear item is "
    << rear(queue) << endl; 
    */
    GameManager g1;
    string answer;
    cout << "Play with Computer? (Y/N) " << endl;
    cin >> answer;
    g1.setUp();
    if (answer=="Y") g1.setComputer();
    g1.playFullGame();
}
