
#include <iostream>
#include <chrono>
#include <ctime>

#include "Debug.h"
#include "Scheduler.h"



// Create some jobs. 
void createJobs(Scheduler &s, int items)
{
  std::time_t delta = std::time(nullptr);

  for (int i = 0 ; i < items; i++)
  {
    delta  += (std::rand()%5)+2;
    s.addQueue(delta);
  }

};

int main(void)
{
  Debug::debugPrint("Entered Main\n");
  
  srand(time(0));

  Scheduler s;

  // create 25 test jobs, with random start times.  
  createJobs(s,5);

  // execute the threaded callback jobs. 
  s.execute();

  // wait for all jobs to complete. 
  s.Join();

  return 0;
} 
