

/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 4
*/


//Libraries Included Here
#include <iostream>
#include <fstream>
#include "GenQueue.h"
#include "Window.h"
#include "Student.h"
//#include "Registrar.h"
#include <string>


using namespace std;

class Simulation
{
public:

  //Constuctors
  Simulation();
  Simulation(int newClockTick, int newTotalIdle, int newTotalWait, int numWindows);
  ~Simulation();

//Methods for setting the variables and Reading in Files
  void readInFile(string fileName);
  void setVariables(string userString);
  void setNumberWindows();

//Methods for Changing the Variables
  void checkWindows();
  bool checkStudents();
  void Simulate();
  Window decreaseTimeAtWindow(Window newWindow);
  void incWait();

//Methods for Calculating the Output
  void printOut();
  float calcStudentMean();
  float calcStudentMedian();
  int calcStudentTime();
  int calcStudentTens();

  float calcMeanWindow();
  int calcWindowTime();
  int calcWindowFives();


//Private Variables
private:
  int clockTick;
  int totalIdleTime;
  int totalWaitTime;
  int numWindows;


//Queues and Linked Lists
  GenQueue<int> *numArray;

  GenQueue<Student> *studentWaitLine;
  GenQueue<Student> *studentProcessed;
  DoublyLinkedList<Window> *windows;
};
