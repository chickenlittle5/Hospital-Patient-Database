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
    
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType &target, bool &success);

    BinaryNode<ItemType>* _removeNode(BinaryNode<ItemType> *nodePtr);

    BinaryNode<ItemType>* _removeLeftmostNode(BinaryNode<ItemType> *nodePtr, ItemType &inorderSuccessor);

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

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &item) {
    bool success = false;
    this->rootPtr = _remove(this->rootPtr, item, success);
    if (success) {
        this->count--;
    }
    return success;
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

// Iterative implementation of the insert operation
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

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, const ItemType &target, bool &success) {
    if (nodePtr == nullptr) {
        success = false;
        return nodePtr;
    }

    if (target < nodePtr->getItem()) {
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    } else if (target > nodePtr->getItem()) {
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    } else {
        nodePtr = _removeNode(nodePtr);
        success = true;
    }
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeNode(BinaryNode<ItemType>* nodePtr) {
    if (nodePtr->isLeaf()) {
        delete nodePtr;
        return nullptr;
    } else if (nodePtr->getLeftPtr() == nullptr) {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        return nodeToConnectPtr;
    } else if (nodePtr->getRightPtr() == nullptr) {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        return nodeToConnectPtr;
    } else {
        ItemType newNodeValue;
        nodePtr->setRightPtr(_removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType &inorderSuccessor) {
    if (nodePtr->getLeftPtr() == nullptr) {
        inorderSuccessor = nodePtr->getItem();
        return _removeNode(nodePtr);
    } else {
        nodePtr->setLeftPtr(_removeLeftmostNode(nodePtr->getLeftPtr(), inorderSuccessor));
        return nodePtr;
    }
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