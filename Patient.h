
#ifndef PATIENT_H
#define PATIENT_H

#include <string>
using std::string;


int hashFunction(string key, int hashSize);

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
        return _id == other.getName();
    }

    friend int hashFunction(const string key, int hashSize);

};






#endif