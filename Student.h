



/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 4
*/



//Libraries Included Here
#include <string>
#include <iostream>

using namespace std;

#ifndef  STUDENT_H
#define  STUDENT_H
class Student
{
public:
//Constructors
  Student();
  Student(int waitTime, int timeAtWindow, bool atWindow, int idnum);
  Student(const Student& origStudent);
  ~Student();

//Accessors and Mutators
  int getWaitTime();
  void setWaitTime(int newTime);
  void incWaitTime();

  void setTimeAtWindow(int newTime);
  int getTimeAtWindow();
  void decTimeAtWindow();


  void setAtWindow(bool isAtWindow);
  bool getAtWindow();

//Assignment operator and cout overwritting
  Student& operator=(const Student& origStudent);
  friend std::ostream& operator<<(std::ostream& os, const Student& student);



private:
  //Private Variables
  int waitTime;
  int timeAtWindow;
  bool atWindow;
  int idnum;

};
#endif
