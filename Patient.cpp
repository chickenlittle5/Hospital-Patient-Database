#include "Patient.h"

int hashFunction(string key, int hashSize) {
    int sum = 0;
    for (int i = 0; i < hashSize; i++) {
        sum += key[i];
    }
    return sum % hashSize;
}