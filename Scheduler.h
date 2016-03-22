
#include <queue>
#include <ctime>
#include <chrono>


#include "Job.h"


#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

typedef std::queue<Job> JobQueue;
typedef std::vector<Job> RunningVector;

//
// Scheduler maintains a queue of jobs, starts a thread to service jobs.  Jobs are serviced
// if their time stamp has gone past now, once a job is scheduled, it is kept in a vector until
// it completes. The scheduler will wait / join on all the jobs in the vector, before the program
// is allowed to exit. 
//
class Scheduler
{
public:
  void addQueue(size_t time);
  void execute();

  void doneScheduling();

  void Join(void);

private:
  // Queue of jobs to schedule. 
  JobQueue mQueue;
  // Vector of jobs running 
  RunningVector mVector;

  std::mutex mMutex;
};

#endif
