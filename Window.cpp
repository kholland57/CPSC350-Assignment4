


/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 4
*/


#include "Window.h"

//Default Constructor
Window::Window()
{
  idleTime = 0;
  hasStudent = false;
  idnum = 0;
  student = Student();
}
//-----------

//Overloaded Constructor
Window::Window(int idleTime, bool hasStudent, int idnum)
{
  this->idleTime = idleTime;
  this->hasStudent = hasStudent;
  this->idnum = idnum;
  student = Student();
}
//-----------


//Copy Constructor
Window::Window(const Window& origWindow)
{
  this->idleTime = origWindow.idleTime;
  this->hasStudent = origWindow.hasStudent;
  this->idnum = origWindow.idnum;
  this->student = origWindow.student;
}
//-----------

//Destructor
Window::~Window(){
  //cout <<"Deleting Window" << endl;
}


//-----------------------------------------------------------------------------

//Method for overriding assignment operator
Window& Window::operator=(const Window &origWindow)
{
  if (this != &origWindow)
  {
    this->idleTime = origWindow.idleTime;
    this->hasStudent = origWindow.hasStudent;
    this->idnum = origWindow.idnum;
    this->student = origWindow.student;
  }
  return *this;
}
//------


//Overriding cout << operator for printing
std::ostream& operator<<(std::ostream& os, const Window& window)
{
  os << "Window : " << window.idnum << endl;
  os << "Idle Time : " << window.idleTime << endl;
  os << "Has Student : " << window.hasStudent << endl;
  os << "idNum : " << window.idnum << endl;
  os << "Student : " << window.student << endl;

  return os;
};
//------

//Accessor And Mutators

//returns idleTime var
int Window::getIdleTime()
{
  return this->idleTime;
}

//sets idleTime var
void Window::setIdleTime(int newTime)
{
  this->idleTime = newTime;
}

//increases idleTime var by 1
void Window::incIdleTime()
{
  idleTime += 1;
}

//set hasStudent var, if var is false resets student var
void Window::setHasStudent(bool hasStudent)
{
  this->hasStudent = hasStudent;
  if (hasStudent == false)
  {
    student = Student();
  }
}

//returns hasStudent variable
bool Window::getHasStudent()
{
  return this->hasStudent;
}

//sets the student variable
void Window::setStudent(const Student& newStudent)
{
  this->student = newStudent;
  setHasStudent(true);
  this->hasStudent = true;
}


//remvoves and resturns the student variable
Student Window::removeStudent()
{
  Student tempStudent = student;
  return tempStudent;

}
