

/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 4
*/





#include "Student.h"
#include <iostream>

//Default Constructor
Student::Student()
{
  waitTime = 0;
  timeAtWindow = 0;
  atWindow = false;
  idnum = 0;
}
//-----------


//Overloaded Constructor
Student::Student(int waitTime, int timeAtWindow, bool atWindow,int  idnum)
{
    this->waitTime = waitTime;
    this->timeAtWindow = timeAtWindow;
    this->atWindow = atWindow;
    this->idnum = idnum;
}
//-----------

//Copy Constructor
Student::Student(const Student& origStudent)
{
    this->waitTime = origStudent.waitTime;
    this->timeAtWindow = origStudent.timeAtWindow;
    this->atWindow = origStudent.atWindow;
    this->idnum = origStudent.idnum;
}

//Destructor
Student::~Student()
{
  //cout << "Deleting Student" << endl;
}

//-------------------------------------------------------------------------------

//Method for overriding assignment operator
Student& Student::operator=(const Student &origStudent)
{

    this->waitTime = origStudent.waitTime;
    this->timeAtWindow = origStudent.timeAtWindow;
    this->atWindow = origStudent.atWindow;
    this->idnum = origStudent.idnum;


  return *this;


}
//---------


//Method for overriding cout <<  operator
std::ostream& operator<<(std::ostream& os, const Student& student)
{
  os << "Student : " << student.idnum << endl;
  os << "Wait time : " << student.waitTime << endl;
  os << "Time left at window : " << student.timeAtWindow << endl;
  os << "Is at Window : " << student.atWindow << endl;

  return os;
}
//---------
//-------------------------------------------------------------------------------


//Accessors and Mutators


//returns wait time
int Student::getWaitTime()
{
  return this->waitTime;
}

//returns student time needed at window
int Student::getTimeAtWindow()
{
  return this->timeAtWindow;
}

//returns if student is at window
bool Student::getAtWindow()
{
  return this->atWindow;
}

//sets the wait time in line
void Student::setWaitTime(int newTime)
{
  this->waitTime = newTime;
}

//increases the wait time by one
void Student::incWaitTime()
{
  waitTime += 1;
}

//decreases the wait time by one
void Student::decTimeAtWindow()
{
  this->timeAtWindow = (getTimeAtWindow() - 1) ;
}

//sets the time needed at the window
 void Student::setTimeAtWindow(int newTime)
{
  this->timeAtWindow = newTime;
}

//sets if student is at window
void Student::setAtWindow(bool isAtWindow)
{
  this->atWindow = isAtWindow;
}
