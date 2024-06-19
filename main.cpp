#include <iostream>
#include <string>
using namespace std;

void displayIntro();

int main() {
    displayIntro();

    return 0;
}

void displayIntro() {
    cout << "=======================================================================" << endl;
    cout << "Welcome to the In-Patient Hospital Database System!" << endl;
    cout << "=======================================================================" << endl;
    cout << "The purpose of this application is to organize patients for easy access" << endl 
         << "to prevent confusion and inefficiency in crucial times. In other times " << endl
         << "just for the convenience and quick to find patients without much effort."<< endl;
}
void displayMenu() {
    cout << "[1] - add new patient manually" << endl;
    cout << "[2] - add new patient(s) from input file" << endl;
    cout << "[3] - delete patient" << endl;
    cout << "[4] - undo delete patient" << endl;
    cout << "[5] - add new patient" << endl;
    cout << "[6] - exit application" << endl;
}

