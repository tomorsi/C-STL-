
#include <queue>
#include <ctime>
#include <chrono>
#include <thread>

#include "Debug.h"
#include "Job.h"
#include "Scheduler.h"

using namespace std::chrono;

bool operator<(const Job& lhs, const Job& rhs)
{
  return lhs.mTime < rhs.mTime;
}

void Scheduler::addQueue(size_t time)
{
  int randFibs = (std::rand()%8)+1;

  Job job(time, randFibs);
  {
    
    long seconds = time;

    Debug::debugPrint("adding fibonacci(%d) job to start on: %s\n", randFibs, std::asctime(std::localtime(&seconds)));

    Locker lock(mMutex); 

    mQueue.push(job);
  }

}

//
// Schedule each Job, then put it on 
// the queue to wait to be joined. 
//
void Scheduler::execute()
{
  

  while(!mQueue.empty())
  {
      std::time_t current = std::time(nullptr);

      {
        Locker lock(mMutex);
	Job &j = mQueue.front();
	if (j.ready(current))
	{
	  Job &j = mQueue.front();
          j.run();
	  mVector.push_back(j);
	  mQueue.pop(); 
	}
	else
	{
	  std::time_t when = j.when();
	  if (when>0)
	    std::cout << "sleeping for: " << when << " seconds" << std::endl;
	  std::this_thread::sleep_for(std::chrono::seconds(when));
	}
      }
  }
}

void Scheduler::Join()
{
  Debug::debugPrint("waiting for jobs to complete\n");
  
  std::vector<Job>::iterator iter;
  for (iter = mVector.begin(); iter != mVector.end(); iter++)
  {
    Job &j = (*iter);
    j.Join();
  }  
}



