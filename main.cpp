
/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 4
*/

//Libraries included here

#include "GenLinkedList.h"
#include "GenQueue.h"
#include "Student.h"
#include "Window.h"

#include "Simulation.h"
#include <string>

using namespace std;

//Main method for the program
int main(int argc, char **argv){


  if (argc <2){
    cout << "Invalid text file input. Exiting program." << endl;
    return 1;
  }
  string fName = argv[1];

  //Simulation for the program
  Simulation* run = new Simulation();
  run->readInFile(fName);


  delete run;

}
