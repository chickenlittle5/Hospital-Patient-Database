/*
 * @author - Benjamin Tonthat
 */

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
public:
    // insert a node at the correct location
    bool insert(const ItemType &item);
    // remove a node if found
    bool remove(const ItemType &item);
    // find a target node
    bool search(const ItemType &target, ItemType &returnedItem) const;
    
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
	// search for target node
	BinaryNode<ItemType>* _search(BinaryNode<ItemType>* treePtr, const ItemType &target) const;
};

// Wrapper for _insert - Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	this->count++;
	
	return true;
}  

// Wrapper for _search
// - it calls the private _search function that returns a Node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller 
//   via the output parameter, and returns true, otherwise it returns false.
template<class ItemType>
bool BinarySearchTree<ItemType>::search(const ItemType& anEntry, ItemType & returnedItem) const
{
    BinaryNode<ItemType>* temp = _search(this->rootPtr, anEntry);
    if (temp != nullptr)
    {
        returnedItem = temp->getItem();
        return true;
    }
    return false;
}

//////////////////////////// private functions ////////////////////////////////////////////

// Iterative implementation of the insert operation (TO DO: change it to a recursive function!)
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{ 
    if(!nodePtr) // == NULL
    {
        nodePtr = newNodePtr;
        return nodePtr;
    }
    else
    {
        if (newNodePtr->getItem() < nodePtr->getItem())
        {
            nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
        }
        else
        {
            nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
        }
    }

    return nodePtr;
}

// Recursive implementation of the search operation
// - return NULL if target not found, otherwise
// - returns a pointer to the node that matched the target
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_search(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType &target) const
{
    BinaryNode<ItemType>* found = nullptr;
    
    if (nodePtr == nullptr) {
       return found;
    }
    
    if (nodePtr->getItem() == target) {
        found = nodePtr;
    } else if (nodePtr->getItem() > target) {
        found = _search(nodePtr->getLeftPtr(), target);
    } else {
        found = _search(nodePtr->getRightPtr(), target);
    }
    
    return found;
}

#endif