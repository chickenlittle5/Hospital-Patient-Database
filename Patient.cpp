#include "Patient.h"

int hashFunction(const Patient &key, int hashSize) {
    string k = key.getID();
    int sum = 0;
    for (int i = 0; i < hashSize; i++) {
        sum += k[i];
    }
    return sum % hashSize;
}
