/*
 * @author - Benjamin Tonthat
 * This file contains the initializing of the nodes in the tree.
 */

#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class ItemType>
class BinaryNode
{
private:
    ItemType              item;        // Data/Key
    BinaryNode<ItemType>* leftPtr;     // Pointer to left child
    BinaryNode<ItemType>* rightPtr;    // Pointer to right child

public:
    // Constructors
    BinaryNode(const ItemType & anItem) {item = anItem; leftPtr = 0; rightPtr = 0;}
    BinaryNode(const ItemType & anItem,
               BinaryNode<ItemType>* left,
               BinaryNode<ItemType>* right) {item = anItem; leftPtr = left; rightPtr = right;}
    // Setters
    void setItem(const ItemType & anItem) {item = anItem;}
    void setLeftPtr(BinaryNode<ItemType>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<ItemType>* right) {rightPtr = right;}

    // Getters
    ItemType getItem() const {return item;}
    BinaryNode<ItemType>* getLeftPtr() const  {return leftPtr;}
    BinaryNode<ItemType>* getRightPtr() const {return rightPtr;}

    // Other Functions
    bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
};

#endif