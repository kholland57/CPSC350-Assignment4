


/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 4
*/



//Libraries Included Here
#include "Simulation.h"
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;


//Constructor
Simulation::Simulation()
{
  clockTick = 0;
  totalIdleTime = 0;
  totalWaitTime = 0;
  numWindows = 0;

  studentWaitLine = new GenQueue<Student>();
  studentProcessed = new GenQueue<Student>();
  windows = new DoublyLinkedList<Window>();
}
//------


//Overloaded Constructor
Simulation::Simulation(int newClockTick, int newTotalIdle, int newTotalWait, int numWindows)
{

  clockTick = newClockTick;
  totalIdleTime = newTotalIdle;
  totalWaitTime = newTotalWait;
  this->numWindows = numWindows;


  studentWaitLine = new GenQueue<Student>();
  studentProcessed = new GenQueue<Student>();
  windows = new DoublyLinkedList<Window>();
}
//------

//Destructor
Simulation::~Simulation()
{
  cout <<"Deleting Simulation " <<endl;
  delete numArray;
  delete studentWaitLine;
  delete studentProcessed;
  delete windows;
}
//------------------------------------------------------------------------------


//File IO Read in File, if file is invalid program will exit.
void Simulation::readInFile(string fileName)
{
  string userString = "";
  ifstream inFS;

  string fileContent = "";
  string totalString = "";
  cout << "Opening " << fileName << endl;
  inFS.open(fileName);

  if (!inFS.is_open())
  {
    cout << "ERROR, could not open file " << fileName  << endl;
    cout << "Exiting Program." << endl;
    exit(1);
  }

  while (!inFS.eof()) {

    getline(inFS, fileContent);
    if (!inFS.fail()) {
        for (int i = 0; i <fileContent.length(); ++i)
        {
          if (!isdigit(fileContent[i]))
          {
            cout <<"ERROR : invalid file. Element is not Integer."<< endl;
            cout <<"Exiting Program." << endl;
            exit(1);
          }
        }
        totalString = totalString + fileContent + "\n";
     }
  }
  inFS.close();
  userString = totalString;


  setVariables(userString);

}
//------



//Sets the String read in to variables and puts them in a number queue to
//be used for the simulation later
void Simulation::setVariables(string userString)
{

  cout << userString << endl;

  int stringInt = 0;

  numArray = new GenQueue<int>();
  string stringNum= "";


  for (int i = 0; i < userString.length(); ++i)
  {
    if (userString[i] != '\n')
    {
      stringNum += userString[i];
    }
    else
    {

      numArray->insert(stoi(stringNum));
      stringInt ++;
      stringNum = "";
    }
  }
  numArray->print();
  setNumberWindows();
}
//------


//Sets the number of windows for the simulation, and creates new windows
//and places them in a linked list so that they are all organized.
//The Simulation method is then called.

void Simulation::setNumberWindows()
{
  numWindows = numArray->remove();

  //cout << "numWindows : " <<  numWindows << endl;
  for (int i = 0 ; i < numWindows; ++ i)
  {
      int num = i +1;
      Window window = Window(0, false, num );
      windows->insertBack(window);
  }

  //windows->printList();

  Simulate();
}
//------





//Method that runs and updates the simulation.
void Simulation::Simulate()
{
  //The localClockTick keeps track of what clock tick the simulation is on.
  int localClockTick = 0;

  bool notEmpty = true;


  //Maint loop for the simulation
  while ((!numArray->isEmpty()) || (notEmpty == true))
  {

    //If the clock tick stored in the number array matches the current clock
    //tick then students will enter the line
    if (!numArray->isEmpty()){
      clockTick = numArray->peek();
      if (clockTick == localClockTick)
      {
        clockTick = numArray->remove();
        if (!numArray->isEmpty()){
          //The number of students should be the next number stored in the queue.
          int numStudents = numArray->remove();

          for (int i = 0; i < numStudents; i ++)
          {
            if (!numArray->isEmpty()){
              //A student is then created and added to a wait line queue
              int timeWindow = numArray->remove();
              Student student = Student(0,timeWindow,false,0);
              studentWaitLine->insert(student);
            }
            else
            {
              cout <<"ERROR : Numbers in Read-In File Do not Match up." << endl;
              cout <<"There is no time needed at window number in file." << endl;
              cout <<"Exiting Program." << endl;
              exit(1);

            }
          }
        }
        else
        {
          cout <<"ERROR : Numbers in Read-In File Do not Match up." << endl;
          cout <<"There is no Student Numbers left in file" << endl;
          cout <<"Exiting Program." << endl;
          exit(1);
        }
      }
    }

    //Check windows checks for window availability, and inc wait increases
    //the wait times for the students.
    checkWindows();
    incWait();



    localClockTick ++;


    //If wait time, number queues, and windows do not have students,
    //then the loop will break.
    if (numArray->isEmpty())
    {
      if (studentWaitLine->isEmpty())
      {
        if (checkStudents() == false)
        {
          //cout << "GOT HERE "<< endl;
          notEmpty = false;
          break;
        }
      }
    }
  }

  // cout <<"\nWAIT LINE" << endl;
  // studentWaitLine->print();
  //
  //
  // cout <<"\nWINDOWS" << endl;
  // windows->printList();
  //
  // cout << "\nPROCESSED STUDENTS : "<< endl;
  // studentProcessed->print();

  printOut();
}
//--------



//Checks if window is availiable for a student by removing the
//window from the linked list. If it does not have a student, one is added
//from the wait line. Else, idle time is incremented.
//The window is then added back to the linked list.
void Simulation::checkWindows()
{

  for (int i = 0; i < numWindows; ++i)
  {
    Window windowCheck = windows->removeFront();

    if (windowCheck.getHasStudent() == false)
    {
      if (!studentWaitLine->isEmpty())
      {
        windowCheck.setStudent(studentWaitLine->remove());
      }
      else
      {
        windowCheck.incIdleTime();
      }
    }
    else
    {
      windowCheck = decreaseTimeAtWindow(windowCheck);
    }

    windows->insertBack(windowCheck);
  }
}
//--------



//This method removes a student from the window, and decreases the variable
//for the time the student neeeds at window. If time at window = 0 then the
//student is removed and added to the processed list.

Window Simulation::decreaseTimeAtWindow(Window newWindow)
{
  Student changeStudent = newWindow.removeStudent();

  changeStudent.decTimeAtWindow();
  if (changeStudent.getTimeAtWindow() == 0)
  {

    studentProcessed->insert(newWindow.removeStudent());
    newWindow.setHasStudent(false);

  }
  else
  {
    newWindow.setStudent(changeStudent);

  }
  return newWindow;

}
//--------


//This method checks if there are any students at any windows.
bool Simulation::checkStudents()
{
  for (int i = 0; i < numWindows; ++i)
  {
    Window windowCheck = windows->removeFront();
    if (windowCheck.getHasStudent() == true)
    {
      windows->insertFront(windowCheck);
      return true;
    }
    windows->insertBack(windowCheck);
  }
  return false;

}
//--------


//This increments the wait time while the student is in the line.
void Simulation::incWait()
{

  int size = studentWaitLine->getSize();

  for (int i = 0; i < size; ++ i)
  {
    Student temp = studentWaitLine->remove();

    temp.incWaitTime();


    studentWaitLine->insert(temp);

  }

}
//--------




//This prints out the final results of the simulation.
void Simulation::printOut()
{
    cout << "\nResults of Registrar Simulation  :  \n" << endl;

    cout << "Student Wait Time Mean : " << calcStudentMean() << endl;
    cout <<"Student Longest Wait Time : " << calcStudentTime() << endl;
    cout <<"Student Wait Time Median: " << calcStudentMedian() << endl;
    cout <<"Number of Students Waiting over 10 Minutes : " << calcStudentTens() << endl;


    cout << "\nWindow Idle Time Mean : " << calcMeanWindow() << endl;
    cout << "Window Longest Idle Time : " << calcWindowTime() << endl;
    cout << "Windows Idle Over 5 Minutes : " << calcWindowFives() << endl;
    cout << "\n" << endl;

}






//------------------------------------------------------------------------------

//Math Functions for Calculating Output


//Calculates the student mean waittime by taking the number of students
//in the processed list. It then removes each student from the list,
//gets their wait time number, and calculates the total sum and mean
float Simulation::calcStudentMean()
{
  float count = studentProcessed->getSize();
  float sum = 0;
  for (int i = 0; i < count;  ++i )
  {
    Student temp = studentProcessed->remove();
    int num = temp.getWaitTime();
    sum += num;
    studentProcessed->insert(temp);

  }
  float mean = sum/count ;
  return mean;
}


//The median is calculated in a similar way but each wait time number is
//put into an array. The std::sort algorithm is then used to sort the
//numbers smallest to largest. The middle number, or average of the two
//middle numbers, is then returned.
float Simulation::calcStudentMedian()
{
  int count = studentProcessed->getSize();

  int sum[count];
  for (int i = 0; i < count;  ++i )
  {
    Student temp = studentProcessed->remove();
    int num = temp.getWaitTime();
    sum[i] = num;
    studentProcessed->insert(temp);

  }

  std::sort(sum, sum + count);


  if (count%2 == 1)
  {
    int a = count/2;
    int b = sum[a + 1];

    float median = (a + b)/2;
    return median;
  }
  else
  {
    int middle = count/2;
    int median = sum[middle];
    return median;
  }
}
//--------




//This calculates the longest student wait time
int Simulation::calcStudentTime()
{
  int count = studentProcessed->getSize();
  int largest = 0;
  for (int i = 0; i < count;  ++i )
  {
    Student temp = studentProcessed->remove();
    int num = temp.getWaitTime();

    if (num > largest)
    {
      largest = num;
    }
    studentProcessed->insert(temp);
  }
    return largest;
}
//--------


//This calculates the number of students waiting in line over 10 minutes
int Simulation::calcStudentTens()
{
  float count = studentProcessed->getSize();
  float sum = 0;
  for (int i = 0; i < count;  ++i )
  {
    Student temp = studentProcessed->remove();
    int num = temp.getWaitTime();
    if (num > 10)
    {
      sum += 1;
    }
    studentProcessed->insert(temp);

  }
  return sum;
}
//--------


//This calculates the mean idle time for the windows
float Simulation::calcMeanWindow()
{
  float count = windows->getSize();
  float sum = 0;
  for (int i = 0; i < count;  ++i )
  {
    Window temp = windows->removeFront();
    int num = temp.getIdleTime();
    sum += num;
    windows->insertBack(temp);

  }
  float mean = sum/count ;
  return mean;
}
//--------



//This calculates the longest idle time for a window.
int Simulation::calcWindowTime()
{
  float count = windows->getSize();
  int largest = 0;
  for (int i = 0; i < count;  ++i )
  {
    Window temp = windows->removeFront();
    int num = temp.getIdleTime();

      if (num > largest)
      {
        largest = num;
      }
      windows->insertBack(temp);
  }
    return largest;
}
//--------


//This calculates the number of windows with idle times longer than 5 minutes
int Simulation::calcWindowFives()
{
  float count = windows->getSize();
  int sum = 0;
  for (int i = 0; i < count;  ++i )
  {
    Window temp = windows->removeFront();
    int num = temp.getIdleTime();

      if (num > 5)
      {
        sum += 1;
      }
      windows->insertBack(temp);
  }
    return sum;
}
//--------
