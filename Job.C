
#include <iostream>
#include <functional>
#include <ctime>
#include <thread>

#include "Debug.h"
#include "Job.h"

//
// The jobs generateo fibonacci sequences, and print them.  
// 
void Job::callback(void)
{
  Locker lock(Job::s_Mutex);

  std::cout << "Generating Fibonacci series (" << mFibs << ")" << std::endl;
  std::cout << "\t[ " ;    

  // By definition first two are [0,1] or [1,1]. 
  int prev = 0;
  int cur = 1;
  for (int i=0; i<mFibs; i++)
  {
    if (i)
      std::cout << ", "; 

    std::cout << prev ;
    int t = prev;
    prev = prev + cur;
    cur = t; 


  }
  std::cout << ", " <<prev << "]" << std::endl << std::endl; 

  std::cout << "waiting: " << prev << " seconds" << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(prev));
}

Job::Job(std::time_t time, int fibs)
  :mTime(time),mFibs(fibs),mThread(nullptr)
{
}

Job::Job(Job&& moved)
{
  //std::cout << "moving" << std::endl; 

  mThread = moved.mThread;
  mTime = moved.mTime;
  mFibs = moved.mFibs;

  moved.mThread = nullptr;
  moved.mFibs = -1;
}

Job::Job(const Job& copy)
{
  //std::cout << "copying" << std::endl;

  mThread = copy.mThread;
  mTime = copy.mTime;
  mFibs = copy.mFibs;
}

Job& Job::operator=(const Job& copy)
{
  //std::cout << "assigning" << std::endl; 

  mThread = copy.mThread;
  mTime = copy.mTime;
  mFibs = copy.mFibs;

  return *this;
}

// How long in seconds until this job will
// run?
std::time_t Job::when(std::time_t now)
{
  return mTime - now;
}

bool Job::ready(std::time_t time)
{
  //Debug::debugPrint("comparing Job: %lu Current: %lu\n", mTime, time);
  return mTime < time;
} 

void Job::run(void)
{
  mThread = new std::thread(&Job::callback, this);
} 

void Job::Join()
{
  // thread running in job? 
  if (mThread)
  {
    mThread->join();
    delete mThread; 
    mThread = nullptr;
  }
}

std::mutex Job::s_Mutex;


