/*
 * @author - Ethan Tran
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "StackADT.h"
#include "HashNode.h"
#include <iostream>
using std::cout;
using std::endl;

template<class ItemType>
class HashTable {

private:
    HashNode<ItemType>* hashAry;
    int hashSize;
    int count;

    bool isPrime(int n) const;
    int nextPrime(int n) const;

public:
    HashTable() { count = 0; hashSize = 53; hashAry = new HashNode<ItemType>[hashSize]; }
  HashTable(int n)	{ count = 0; hashSize = n;	hashAry = new HashNode<ItemType>[hashSize]; }
  ~HashTable(){ delete [] hashAry; }

    int getCount() const	{ return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const {return 100.0 * count / hashSize; }
    bool isEmpty() const	{ return count == 0; }
    bool isFull()  const	{ return count == hashSize; }
    HashNode<ItemType> getNode(int i) const { return hashAry[i]; }

    bool insert(const ItemType &itemIn, int h(const ItemType &key, int size) );
    bool remove(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size));
    int  search(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size)) const;
    void displayAll() const;
    void rehash(int h(const ItemType &key, int size));
};

/*~*~*~*
   Insert an item into the hash table
   It does not reject duplicates
*~**/
template<class ItemType>
bool HashTable<ItemType>::insert( const ItemType &itemIn, int h(const ItemType &key, int size) )
{
    if ( count == hashSize)
        return false;

    int bucket = h(itemIn, hashSize);
    int collisions = 0;

    while (hashAry[bucket].getOccupied() == 1) {
        bucket = (bucket + 1) % hashSize;
        collisions++;
    }

    hashAry[bucket].setItem(itemIn);
    hashAry[bucket].setOccupied(1);
    hashAry[bucket].setNoCollisions(collisions);
    count++;

    return true;
}

/*~*~*~*
   Removes the item with the matching key from the hash table
   if found:
     - copies data in the hash node to itemOut
     - replaces data in the hash node with an empty record (occupied = -1: deleted!)
     - returns true
   if not found:
     - returns false
*~**/
template<class ItemType>
bool HashTable<ItemType>::remove( ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size))
{
    int bucket = h(key, hashSize);
    int n = 0;

    while (n < getSize()) {
       if ((hashAry[bucket].getOccupied() == 1) && (hashAry[bucket].getItem() == key)) {
          itemOut = hashAry[bucket].getItem();
          hashAry[bucket] = HashNode<ItemType>();
          hashAry[bucket].setOccupied(-1);
          count--;
          return true;
       }
       n++;
       bucket = (bucket + 1) % getSize();
    }

    return false;
}

/*~*~*~*
   hash search - linear probe
   if found:
      - copy data to itemOut
      - returns the number of collisions for this key
   if not found, returns -1
*~**/
template<class ItemType>
int HashTable<ItemType>::search(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size)) const
{

    /* Write your code here */
    int bucket = h(key, hashSize);
    int n = 0;

    while (n < hashSize) {
        if (hashAry[bucket].getOccupied() == 1 && hashAry[bucket].getItem() == key) {
            itemOut = hashAry[bucket].getItem();
            return hashAry[bucket].getNoCollisions();
        }
        bucket = (bucket + 1) % hashSize;
        n++;
    }

    return -1;
}

/*~*~*~*
   displays all the patients in the hash table
*~**/
template<class ItemType>
void HashTable<ItemType>::displayAll() const {

    for (int i = 0; i < getSize(); i++) {
        if (hashAry[i].getOccupied() == 1) {
            cout << hashAry[i] << endl;
        }
    }
}

/*~*~*~*
   Rehashes the hash table - Lewis
*~**/
template<class ItemType>
void HashTable<ItemType>::rehash(int h(const ItemType &key, int size)) {
    if (getLoadFactor() < 75.0) {
        return;
    }

    int newSize = nextPrime(2 * hashSize);

    HashNode<ItemType>* newHashAry = new HashNode<ItemType>[newSize];

    for (int i = 0; i < hashSize; i++) {
        if (hashAry[i].getOccupied() == 1) {
            ItemType item = hashAry[i].getItem();
            int bucket = h(item, newSize);
            int collisions = 0;

            while (newHashAry[bucket].getOccupied() == 1) {
                bucket = (bucket + 1) % newSize;
                collisions++;
            }

            newHashAry[bucket].setItem(item);
            newHashAry[bucket].setOccupied(1);
            newHashAry[bucket].setNoCollisions(collisions);
        }
    }

    delete[] hashAry;
    hashAry = newHashAry;
    hashSize = newSize;
}

template<class ItemType>
bool HashTable<ItemType>::isPrime(int n) const{
    if (n<=1) return false;

    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

template<class ItemType>
int HashTable<ItemType>::nextPrime(int n) const{
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

#endif
