#include <iostream>
using namespace std;

int numMoves = 0;

void moveOneDisk(string startPeg, string endPeg){
    cout << "move on disk from " << startPeg << " to " << endPeg << endl;
    numMoves++;
}

void moveTower(int numDisks, string startPeg, string endPeg, string tempPeg) {
    if (numDisks == 1) {
        moveOneDisk(startPeg, endPeg);
    }
    else {
        moveTower(numDisks - 1, startPeg, tempPeg, endPeg);
        moveOneDisk(startPeg, endPeg);
        moveTower(numDisks - 1, tempPeg, endPeg, startPeg);
    }
}

int main() {
    int numDisks;
    string startPeg = "A";
    string endPeg = "C";
    string tempPeg = "B";

    cout << "*** Welcome to Jewels' Tower of Hanoi Simulator ***\n";
    cout << "Enter the amount of disks starting on peg A: ";
    cin >> numDisks;
    cout << "\nStarting simulation: " << endl;

    moveTower(numDisks, startPeg, endPeg, tempPeg);
    cout << "\nTotal number of moves was: " << numMoves;
    cout << "\nThanks for playing! \n*** :) Goodbye (: ***";
}
