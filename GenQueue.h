
//Linked List Queue Template


/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 4
*/



//Libraries included here
#include <iostream>
#include "GenLinkedList.h"
#include <string>
#ifndef  GENQUEUE_H
#define  GENQUEUE_H

template<typename Type>
class GenQueue
{

  public:
    //Constructors
    GenQueue();
    GenQueue(int maxSize);
    ~GenQueue();

  //core functions
    void insert(const Type& d); // enqueue
    Type remove(); //dequeue

  //aux functions
    Type peek();
    bool isFull();
    bool isEmpty();
    int getSize();
    void print();

  //Variables
    int front; //aka head
    int rear; // aka tail
    int mSize;
    int numElements;


    DoublyLinkedList<Type> *myQueue; //array

  //  friend std::ostream& operator<<(std::ostream& os, const GenQueue<>& genqueue);
  private:

};
//----------------------------------------------------------------------------------

//Default Constructor
template<typename Type>
GenQueue<Type>::GenQueue(){
  myQueue = new DoublyLinkedList<Type>();
  mSize = 10;
  front = 0;
  rear = -1;
  numElements = 0;
}
//-------

//Overloaded constructor
template<typename Type>
GenQueue<Type>::GenQueue(int maxSize){
  myQueue = new DoublyLinkedList<Type>();
  mSize = maxSize;
  front = 0;
  rear = -1;
  numElements = 0;
}
//-------

//Destructor
template<typename Type>
GenQueue<Type>::~GenQueue(){
  cout << "Deleting GenQueue" << endl;

  delete  myQueue;
}
//-------
//------------------------------------------------------
// template<typename Type>
// std::ostream& operator<<(std::ostream& os, const GenQueue<Type>& genqueue)
// {
//   os << genqueue.print() << endl;
//
//   return os;
// };
//

//Inserts the data in the back of the queue, and increases the vars
//Rear and numElements by one
template<typename Type>
void GenQueue<Type>::insert(const Type& d){
  myQueue->insertBack(d);
  rear++;
  numElements++;
}
//-------


//Removes the Front of the Queue , increments the front and decreases the
//number of elements
template<typename Type>
Type GenQueue<Type>::remove(){
  //ADD A CHECK HERE
  //error checking - check if its not empty before you remove

  if (isEmpty())
  {
    cout << "EMPTY" << endl;
  }
  ++front;
  Type c  = myQueue->removeFront();
  --numElements;
  return c;
}
//-------


//Returns the data at the front of the list but does not remove it.
template<typename Type>
Type GenQueue<Type>::peek(){
  //add more checks here
  if (isEmpty())
  {
    cout <<"Queue is empty." << endl;
  }
  return myQueue->getFront();
}
//-------

//Prints out the contents of the list.
template<typename Type>
void GenQueue<Type>::print(){
  //add more checks here
  if (isEmpty())
  {
    cout <<"Queue is empty." << endl;
  }
  else
  {
    myQueue->printList();
  }
}
//-------

//Returns bool true or false if the queue is full
template<typename Type>
bool GenQueue<Type>::isFull(){
  return (numElements == mSize);
}
//-------

//Returns bool true or false is the queue is empty
template<typename Type>
bool GenQueue<Type>::isEmpty(){
  return (numElements == 0);
}
//-------


//returns the size of the queue
template<typename Type>
int GenQueue<Type>::getSize(){
  return numElements;
}
//-------

#endif
