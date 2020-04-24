
/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 4
*/





//Libraries included here
#include <iostream>

using namespace std;
#ifndef  GENLINKEDLIST_H
#define  GENLINKEDLIST_H


//Template Class for a Listnode
template<class Type>
class ListNode{
  public:
    //Has a data of any type, and a listnode pointer pointing to next and previous
    Type data;
    ListNode<Type> *next;
    ListNode<Type> *prev;

    //Constructors
    ListNode();
    ListNode(const Type &val = Type(), ListNode *previous = NULL, ListNode *nextNode = NULL); //overloaded constructor
    ~ListNode(); //destructor

};
//------------------------------------------

//Default Constructor, sets everything to NULL
template<class Type>
ListNode<Type>::ListNode(){
  data = NULL;
  next = NULL;
  prev = NULL;
}
//---------


//Overloaded constructor, including parameters for pointers to next and previous
template<class Type>
ListNode<Type>::ListNode(const Type &val, ListNode<Type> *previous, ListNode<Type> *nextNode)
{

  this->data = val;
  this->next = nextNode;
  this->prev = previous;

}
//---------

//Destructor
template<typename Type>
ListNode<Type>::~ListNode(){
  next = NULL;
  prev = NULL;
  delete next;
  delete prev;
}
//---------


//------------------------------------------------------------------------------
//Template Class For Doubly Linked List

template<class Type>
class DoublyLinkedList{
  private:
    //Private Variables
    ListNode<Type> *front; //front listnode
    ListNode<Type> *back; //back listnode
    unsigned int size;

  public:
    //Constructors
    DoublyLinkedList();
    DoublyLinkedList(int size);
    ~DoublyLinkedList();

    //Aux Functions
    void insertFront(const Type &val);
    void insertBack(const Type &val);
    Type removeFront();
    void removeBack();
    Type remove(ListNode<Type> *node);
    int search(Type val);
    Type removeAtPos(int pos);

    Type getFront();

    unsigned int getSize();
    bool isEmpty();
    void printList();
    string getPrintList();
};
//--------------------------------

//Default Constructor
template<class Type>
DoublyLinkedList<Type>::DoublyLinkedList(){
  size = 0;
  front = NULL;
  back = NULL;
}
//---------

//Overloaded Constructor
template<class Type>
DoublyLinkedList<Type>::DoublyLinkedList(int size){
  this->size = 0;
  front = NULL;
  back = NULL;

}
//---------

//Destructor
template<class Type>
DoublyLinkedList<Type>::~DoublyLinkedList(){
  while(!isEmpty())
  {
    removeFront();
  }
  delete front;
  delete back;
}
//---------


//Returns the size of the list
template<class Type>
unsigned int DoublyLinkedList<Type>::getSize()
{
  return size;
}
//---------


//Returns if list is empty
template<class Type>
bool DoublyLinkedList<Type>::isEmpty()
{
  return(size == 0);
}
//---------


//Prints each element in the list
template<class Type>
void DoublyLinkedList<Type>::printList()
{
  ListNode<Type> *curr = front;

  while(curr != NULL)
  {
    cout << curr->data << endl;
    curr = curr->next;
  }
}
//---------


//Returns a string to print of each element
template<class Type>
string DoublyLinkedList<Type>::getPrintList()
{
  ListNode<Type> *curr = front;

  string totalString = "";
  while(curr != NULL)
  {
    totalString += dynamic_cast<string>(curr->data);
  }
  return totalString;
}
//---------




//Inserts a new node to the front of the list and increments size
template<class Type>
void DoublyLinkedList<Type>::insertFront(const Type &val){

  if (isEmpty())
  {
    //if list is empty a new front is made
    front = back = new ListNode<Type>(val);
    cout << "FRONT" << front << endl;
  }
  else
  {
    //else a new node is made and made the front
  ListNode<Type> *newNode = new ListNode<Type>(val,nullptr, front);
  front->prev = newNode;
  front = newNode;

  }
  size++;

}
//---------




//Inserts a new node to the back of the linked list
template<class Type>
void DoublyLinkedList<Type>::insertBack(const Type &val){

  if (isEmpty())
  {
    front = back = new ListNode<Type>(val,nullptr,nullptr);
  }
  else
  {
    ListNode<Type> *newNode = new ListNode<Type>(val, back, nullptr);
    back->next = newNode;
    back = newNode;
  }
  size++;

}
//---------




//Removes the front of the list and returns the data
template<class Type>
Type DoublyLinkedList<Type>::removeFront(){
  if (!isEmpty())
  {
    Type c = remove(front);
    return c;
  }
  else
  {
    cout << "List is empty." << endl;
    return front->data;
  }
}
//---------



//Removes the back node of the list
template<class Type>
void DoublyLinkedList<Type>::removeBack(){
  if (!isEmpty())
  {
    remove(back);
  }
}
//---------





//This removes a node from the list.
template<class Type>
Type DoublyLinkedList<Type>::remove(ListNode<Type> *node)
{
  //Value to look for
  ListNode<Type> *curr = front;

  //This while loop searches until it finds the node to remove
  while(curr != nullptr)
  {
    if (curr == node)
    {
      break;
    }
    curr = curr->next;

  }
  //These if statements reassign where the pointers point to depending on the
  //node's position in the list
  if (curr == node)
  {
    if (curr == front)
    {
      front = curr->next;
    }
    if (curr == back)
    {
      back = curr->prev;
    }
    if (curr->prev != nullptr)
    {
      curr->prev->next = curr->next;

    }
    if (curr->next != nullptr)
    {
      curr->next->prev = curr->prev;
    }
    Type temp = curr->data;
    delete curr;
    size --;


    return temp;
  }

  cout <<"COULD NOT REMOVE" << endl;
  return curr->data;
}
//---------



//This takes in a data type as a parameter and returns the position in the
//list of the data
template<class Type>
int DoublyLinkedList<Type>::search(Type val){
  int pos = -1;
  ListNode<Type> *curr = front;

//Loop to find the value
  while(curr != NULL){
    ++pos;

    if (curr->data == val){
      //we found it
        break;
    }
    else {
      //we didn't continue iterating
      curr = curr->next;
    }

    if(curr == NULL)
    {
      //didn't find it
      pos = -1;
    }
    //return pos;
  }
  return pos;
}
//---------


//This takes in a position integer as a parameter, searches for the position,
//and deletes the node at that position
template<typename Type>
Type DoublyLinkedList<Type>::removeAtPos(int pos){
  int idx = 0;
  ListNode<Type> *curr = front;
  ListNode<Type> *previous = front;

  while(idx != pos){
    //loop until position is found
    if (pos >= size)
    {
      cout <<"Error, position is not in list. Null will be returned" << endl;
      return '\0';
    }

    previous = curr;
    curr = curr->next;
    idx ++;

  }

  Type temp = curr->data;

  remove(curr);
  cout <<"REMOVED." <<endl;
  return temp;

}
//---------

//Returns the data of the front node.
template<typename Type>
Type DoublyLinkedList<Type>::getFront(){

  return this->front->data;
}
#endif
