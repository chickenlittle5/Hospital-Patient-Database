/* 
Written by:
Ethan Tran
   Stack template
*/
using namespace std;

#ifndef STACK_ADT
#define STACK_ADT

template <typename T>
class Stack
{
private:
    // Structure for the stack nodes
    struct StackNode
    {
      T value;          // Value in the node
      StackNode *next;  // Pointer to next node
    };

    StackNode *top;     // Pointer to the stack top
    int length;

public:
    // Constructor
    Stack() {
       top = nullptr;
       length = 0;
    }
    // Destructor
    ~Stack();
    // Stack operations:
     bool push(T value);
     T pop();
     T peek() {
        return top->value;
     }
     bool isEmpty() {
        return top == nullptr;
     }
     int getLength() {
        return length;
     }
};

/* 
  Member function push inserts the argument onto
  the stack.
*/
template <typename T>
bool Stack<T>::push(T value) {
   
   StackNode *newNode = new StackNode;
   if (!newNode)
       return false;
   newNode->value = value;

   // Update links and counter
   newNode->next = top;
   top = newNode;
   length++;

   return true;
}



/* 
  Member function pop deletes the value at the top
  of the stack and returns it.
  Assume stack is not empty.
*/
template <typename T>
T Stack<T>::pop() {
   
   StackNode *temp = top;
   T value = temp->value;
   top = top->next;
   delete temp;
   length--;
   return value;
   
}



/* 
  Destructor:
  Traverses the list deleting each node (without calling pop)
*/
template <typename T>
Stack<T>::~Stack() {
   StackNode *currNode;

   // Position nodePtr at the top of the stack.
   currNode = top;

   // Traverse the list deleting each node.
   while (currNode != nullptr) 
   {
      StackNode *tempNode = currNode;
      currNode = currNode->next;
      delete tempNode;
   }
   
}




#endif
