/*
 * @author - Ethan Tran
 * This file contains all the proper variables that a patient has.
 * It contains all the setters and getter variables that we will 
 * use to initialize and change the Patient's variables.
 */
#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>
using std::string;
using std::ostream;
using std::cout;
using std::endl;

class Patient;

int hashFunction(const Patient&, int);

class Patient {

private:
    string _id;
    string _name;
    string _address;
    string _dob;
    string _condition;

public:
    Patient() { _name = ""; _address = ""; _dob = ""; _condition = "unknown"; _id = ""; }
    Patient(string id, string name, string address, string dob, string condition) {
        _id = id;
        _name = name;
        _address = address;
        _dob = dob;
        _condition = condition;
    }


    void setID(string id) { _id = id; }
    void setName(string name) { _name = name; }
    void setAddress(string address) { _address = address; }
    void setDoB(string dob) { _dob = dob; }
    void setCondition(string condition) { _condition = condition; }
    string getID() const { return _id; }
    string getName() const { return _name; }
    string getAddress() const { return _address; }
    string getDoB() const { return _dob; }
    string getCondition() const { return _condition; }

    bool operator==(const Patient& other) {
        return _id == other.getID();
    }

    friend ostream& operator<<(ostream&, Patient& p) {
        cout << "ID: " << p.getID() << endl;
        cout << "Name: " << p.getName() << endl;
        cout << "Address: " << p.getAddress() << endl;
        cout << "Date of Birth: " << p.getDoB() << endl;
        cout << "Condition: " << p.getCondition() << endl;

        return cout;
    }

    friend int hashFunction(const Patient& key, int hashSize);

};






#endif