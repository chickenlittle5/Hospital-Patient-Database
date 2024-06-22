/*
 * @author - Ethan Tran
 * This file contains the hash function that we use to store
 * each of the patients in accordance with their ID.
 */
#include "Patient.h"

 int hashFunction(const Patient &key, int hashSize) {
    string k = key.getID();
    int sum = 0;
    for (int i = 0; i < k.size(); i++) {
        sum += k[i];
    }
    return sum % hashSize;
}