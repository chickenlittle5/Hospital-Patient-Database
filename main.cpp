#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "StackADT.h"
#include "Patient.cpp"
#include "BinarySearchTree.h"
#include "HashTable.h"
using namespace std;

void displayIntro();
void displayMenu();
void addNewPatientManually(HashTable<Patient>&, BinarySearchTree<string>&);
void addNewPatientsFromFile(HashTable<Patient>&, BinarySearchTree<string>&, string&);
void deletePatient(HashTable<Patient>&, Stack<Patient>&);
void undoDeletePatient(HashTable<Patient>&, Stack<Patient>&);
void searchWithPatientID(HashTable<Patient>&);
void listAllPatientsSortedByID(BinarySearchTree<string>&, HashTable<Patient>&);
void saveAllPatientsToFile(HashTable<Patient>&);
void showDatabaseStatistics(HashTable<Patient>&);
void menuManager(HashTable<Patient>&, BinarySearchTree<string>&, Stack<Patient>&);

// Function to check if a number is prime - Lewis
bool isPrime(int n) {
    if (n<=1) return false;

    // Check for divisors from 2 up to the square root of n
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

// Function to find the next prime number greater than n - Lewis
int nextPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

// Function to count lines in the file and determine the hash table size - Lewis
int determineHashSize(const string& filename) {
    ifstream file(filename);
    if(!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return 0;
    }

    int lines = 0;
    string line;
    while (getline(file, line)) {
        lines++;
    }
    file.close();

    return nextPrime(lines *2);
}




int main() {
    string filename = "test1.txt"; // replace if needed
    int hashSize = determineHashSize(filename);

    HashTable<Patient> InfinityCore(hashSize);
    BinarySearchTree<string> InfCore;
    Stack<Patient> Bin;

    addNewPatientsFromFile(InfinityCore, InfCore, filename);

    displayIntro();
    menuManager(InfinityCore, InfCore, Bin);

    return 0;
}




// Function to display the introduction message - Ryan
void displayIntro() {
    cout << "=======================================================================" << endl;
    cout << "Welcome to the In-Patient Hospital Database System!" << endl;
    cout << "=======================================================================" << endl;
    cout << "The purpose of this application is to organize patients for easy access" << endl 
         << "to prevent confusion and inefficiency in crucial times. In other times " << endl
         << "just for the convenience and quick to find patients without much effort."<< endl;
}
// Function to display the menu - Ryan
void displayMenu() {
    cout << "=========== MENU ===========" << endl;
    cout << "[1] - add new patient manually" << endl;
    cout << "[2] - add new patient(s) from input file" << endl;
    cout << "[3] - delete patient" << endl;
    cout << "[4] - undo delete patient" << endl;
    cout << "[5] - search with patient ID" << endl;
    cout << "[6] - list all patients sorted by ID" << endl;
    cout << "[7] - save all existing patients to file" << endl;
    cout << "[8] - show database statistics" << endl;
    cout << "[9] - HELP" << endl;
    cout << "[0] - exit application" << endl;
    cout << "===========================" << endl;
    cout << endl;
}
/*
Asks user for patient information and adds it to the hash table and binary search tree - Ethan
*/
void addNewPatientManually(HashTable<Patient>& h, BinarySearchTree<string>& bst) {
    cout << "Adding a new patient manually:" << endl;

    string patID, patName, patDoB, patAddy, patDiag;
    cout << "Enter Patient ID: ";
    cin >> patID;
    cin.ignore(1,'\n');
    cout << "Enter Patient Full Name: ";
    getline(cin, patName);
    cout << "Enter Patient Date of Birth (MM/DD/YYYY): ";
    cin >> patDoB;
    cin.ignore(1,'\n');
    cout << "Enter Patient Address: ";
    getline(cin, patAddy);
    cout << "Enter Patient Diagnosis: ";
    getline(cin, patDiag);

    Patient newPatient = Patient(patID, patName, patAddy, patDoB, patDiag);
    if (!bst.insert(newPatient.getID())) {
        cout << "Duplicate ID detected! Invalid ID to insert!" << endl;
    }
    else {
        h.insert(newPatient, hashFunction);
    }

}

/*
Asks user for file name and adds patients from file to hash table and binary search tree - Lewis
*/
void addNewPatientsFromFile(HashTable<Patient>& h, BinarySearchTree<string>& bst, string& filename) {

    ifstream inputFile(filename);
    cout << "Reading data from \"" << filename << "\"" << endl;
    if(!inputFile){
        cout << "Error opening the input file: \""<< filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(inputFile, line)){
        string patID, patName, patDoB, patAddy, patDiag;
        stringstream temp(line);   // create temp with data from line
        getline(temp, patID, ';');   // stop reading name at ';'
        temp.ignore();  // to ignore space in front of description
        getline(temp, patName, ';');  
        temp.ignore();  
        getline(temp, patAddy, ';');  
        temp.ignore();  
        getline(temp, patDoB, ';');  
        temp.ignore();  
        getline(temp, patDiag);

        Patient newPatient = Patient(patID, patName, patAddy, patDoB, patDiag);
        bst.insert(newPatient.getID());
        h.insert(newPatient, hashFunction);
    }
}

/*
Asks user for patient ID and deletes patient from hash table and adds removed patient to the trashBin stack in case of an undo delete called
*/
void deletePatient(HashTable<Patient>& h, BinarySearchTree<string>& bst, Stack<Patient>& trashBin) {
    string deletedPatient;
    cout << "Enter patient to delete: ";
    cin.ignore(1, '\n');
    getline(cin, deletedPatient);
    cout << "Deleting a patient..." << endl;
    Patient itemOut;
    itemOut.setID(deletedPatient);
    h.remove(itemOut, itemOut, hashFunction);
    bst.remove(itemOut.getID());
    trashBin.push(itemOut);
}

/*
Pops from trash bin stack and inserts back into hash table, popped Patient attributes are then printed using an overloaded stream operator - Ethan
*/
void undoDeletePatient(HashTable<Patient>& h, BinarySearchTree<string>& bst, Stack<Patient>& trashBin) {

    if (trashBin.isEmpty()) {
        cout << "Nothing to undo!" << endl;
    } else {
        cout << "Undoing delete patient..." << endl;
        Patient itemOut;
        itemOut = trashBin.pop();
        h.insert(itemOut, hashFunction);
        bst.insert(itemOut.getID());
        cout << "Undo-ed patient: " << endl;
        cout << itemOut;
    }
}

/*
Asks user for patient ID and searches for patient in hash table and prints patient information if found - Benjamin
*/
void searchWithPatientID(HashTable<Patient>& h) {

    if (h.isEmpty()) {
        cout << "No patients available to search." << endl;
        return;
    }
    cout << "Searching with patient ID..." << endl;
    cout << "Enter the patient ID [Q to quit]: ";
    string patID;
    cin >> patID;
    Patient itemOut;
    itemOut.setID(patID);
    int numCollisions = h.search(itemOut, itemOut, hashFunction);
    bool found = false;


    while (patID != "Q" && patID != "q" && !found) {
        itemOut.setID(patID);
        numCollisions = h.search(itemOut, itemOut, hashFunction);

        if (numCollisions != -1) {
            cout << "Patient found." << endl;
            cout << itemOut << endl;
            found = true;
        } else {
            cout << "Patient ID: \"" << patID << "\" not found. \nPlease enter a valid patient ID [Q to quit]: ";
            cin >> patID;
        }
    }
}

/*
Prints all patients sorted order by ID using the binary search tree - Ethan
*/
void inorderTraversal(BinaryNode<string>* nodePtr, HashTable<Patient>& h) {
    if (nodePtr != nullptr) {
        // Traverse the left subtree
        inorderTraversal(nodePtr->getLeftPtr(), h);

        // Visit the node
        string patientID = nodePtr->getItem();
        Patient patient;
        patient.setID(patientID);
        int collisions = h.search(patient, patient, hashFunction);
        if (collisions >= 0) {
            cout << patient << endl;
        }

        // Traverse the right subtree
        inorderTraversal(nodePtr->getRightPtr(), h);
    }
}

/*
Wrapper function to inorderTraversal() - Ethan
*/
void listAllPatientsSortedByID(BinarySearchTree<string>& bst, HashTable<Patient>& h) {
    cout << "Listing all patients sorted by ID..." << endl;
    //while the left->next is null
    inorderTraversal(bst.getRoot(), h);
}

/*
Saves all patients data into "SavedPatients.txt" file - Lewis
*/
void saveAllPatientsToFile(HashTable<Patient>& h) {
    cout << "Saving all existing patients to file..." << endl;
    ofstream newFile;
    newFile.open("SavedPatients.txt");
    if(newFile.is_open()){
        for(int i = 0; i < h.getSize(); i++){
            if (h.getNode(i).getOccupied() == 1) {
                string ID = h.getNode(i).getItem().getID();
                string name = h.getNode(i).getItem().getName();
                string address = h.getNode(i).getItem().getAddress();
                string dob = h.getNode(i).getItem().getDoB();
                string condition = h.getNode(i).getItem().getCondition();
                newFile << ID << "; " << name << "; " << address << "; " << dob << "; " << condition << endl;
            }
        }
        newFile.close();
    }
    else{
        cout << "Unable to open file" << endl;
    }
}
/*
Shows statistical information about the database - Omar
*/
void showDatabaseStatistics(HashTable<Patient>& h) {
    cout << "Showing database statistics..." << endl;
    // Add your code here
    cout << "Load Factor: " << h.getLoadFactor() << endl;
    cout << "Size of Hash Table: " << h.getSize() << endl;
    cout << "Number of Collisions for each patient: " << endl;
    for(int i = 0; i < h.getSize(); i++) {
        if(h.getNode(i).getOccupied() == 1) {
            cout << h.getNode(i).getItem().getName() << " (" << h.getNode(i).getNoCollisions() << ")"<< endl;
        }
    }
}
/*
Prints indented tree - Benjamin
*/
void printIndentedTree(const string &item, int level) {
    cout << endl;
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item << endl;
}
/*
User picks which function to call based on menu option - Ryan/Omar
*/
void menuManager(HashTable<Patient>& h, BinarySearchTree<string>& bst, Stack<Patient>& trash) {
    int choice;
    displayMenu();
    do {
        cout << "Enter your menu choice (9 for help): ";
        cin >> choice;
        string filename;

        switch (choice) {
            case 1:
                addNewPatientManually(h, bst);
                break;
            case 2:
                cout << "Adding new patient(s) from input file..." << endl;
                cout << "Enter the filename: ";
                cin >> filename;
                addNewPatientsFromFile(h, bst, filename);
                break;
            case 3:
                deletePatient(h, bst, trash);
                break;
            case 4:
                undoDeletePatient(h, bst, trash);
                break;
            case 5:
                searchWithPatientID(h);
                break;
            case 6:
                listAllPatientsSortedByID(bst, h);
                break;
            case 7:
                saveAllPatientsToFile(h);
                break;
            case 8:
                showDatabaseStatistics(h);
                break;
            case 9:
                displayMenu();
                break;
            case 69: 
                bst.printTree(printIndentedTree);
                break;
            case 0:
                cout << "Exiting application. Thank you for using the In-Patient Hospital Database System!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 0);
}