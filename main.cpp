#include <iostream>
#include <ifstream>
#include <sstream>
#include <string>
using namespace std;

void displayIntro();
void displayMenu();
void addNewPatientManually();
void addNewPatientsFromFile();
void deletePatient();
void undoDeletePatient();
void searchWithPatientID();
void listAllPatientsSortedByID();
void saveAllPatientsToFile();
void showDatabaseStatistics();
void menuManager();

int main() {
    int userChoice;
    string patID, patName, patDoB, patAddy, patDiag;
    displayIntro();
    menuManager();

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
    cout << "[5] - search with patient ID" << endl;
    cout << "[6] - list all patients sorted by ID" << endl;
    cout << "[7] - save all existing patients to file" << endl;
    cout << "[8] - show database statistics" << endl;
    cout << "[9] - exit application" << endl;
}

void addNewPatientManually() {
    cout << "Adding a new patient manually..." << endl;
    // Add your code here
    cout << "Enter Patient ID: \n";
    cin >> patID;
    cout << "Enter Patient Full Name: \n";
    cin >> patName;
    cout << "Enter Patient Date of Birth (MM/DD/YYYY) \n";
    cin >> patDoB;
    cout << "Enter Patient Address \n";
    cin >> patAddy;
    cout << "Enter Patient Diagnosis \n";
    cin >> patDiag;
}

void addNewPatientsFromFile() {
    cout << "Adding new patient(s) from input file..." << endl;
    // Add your code here
    cout << "Enter the filename: ";
    ifstream inputFile(filename);
    cout << "Reading data from \"" << filename << "\"" << endl;
    if(!inputFile){
        cout << "Error opening the input file: \""<< filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(inputFile, line)){
    stringstream temp(line);   // create temp with data from line
    getline(temp, patID, ';');   // stop reading name at ';'
    temp.ignore();  // to ignore space in front of description
    getline(temp, patName, ';');  
    temp.ignore();  
    getline(temp, patAddy, ';');  
    temp.ignore();  
    getline(temp, patDoB, ';');  
    temp.ignore();  
    temp >> patDiag;
    }
}

void deletePatient() {
    cout << "Deleting a patient..." << endl;
    // Add your code here
}

void undoDeletePatient() {
    cout << "Undoing delete patient..." << endl;
    // Add your code here
}

void searchWithPatientID() {
    cout << "Searching with patient ID..." << endl;
    // Add your code here
}

void listAllPatientsSortedByID() {
    cout << "Listing all patients sorted by ID..." << endl;
    // Add your code here
}

void saveAllPatientsToFile() {
    cout << "Saving all existing patients to file..." << endl;
    // Add your code here
}

void showDatabaseStatistics() {
    cout << "Showing database statistics..." << endl;
    // Add your code here
}

void menuManager() {
    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNewPatientManually();
                break;
            case 2:
                addNewPatientsFromFile();
                break;
            case 3:
                deletePatient();
                break;
            case 4:
                undoDeletePatient();
                break;
            case 5:
                searchWithPatientID();
                break;
            case 6:
                listAllPatientsSortedByID();
                break;
            case 7:
                saveAllPatientsToFile();
                break;
            case 8:
                showDatabaseStatistics();
                break;
            case 9:
                cout << "Exiting application..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);
}

