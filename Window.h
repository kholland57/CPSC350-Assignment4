
/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 4
*/


//Libraries included Here
#include <string>
#include <iostream>
#include "Student.h"

using namespace std;
#ifndef  WINDOW_H
#define  WINDOW_H
class Window
{
public:
  //Constructors
  Window();
  Window(int idleTime, bool hasStudent, int idnum);
  Window(const Window& origWindow);
  ~Window();

  //Accessors and Mutators
  int getIdleTime();
  void setIdleTime(int newTime);
  void incIdleTime();

  void setHasStudent(bool hasStudent);
  bool getHasStudent();

  void setStudent(const Student& newStudent);
  Student removeStudent();

//Assignment operator and cout overwritting
  Window& operator=(const Window &origWindow);
  friend std::ostream& operator<<(std::ostream& os, const Window& window);


private:

//Private Variables
  int idleTime;
  bool hasStudent;
  int idnum;

  Student student;

};


#endif
