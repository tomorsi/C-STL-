
#include <iostream>
#include <functional>
#include <ctime>
#include <thread>

#ifndef __JOB_H__
#define __JOB_H__

typedef std::lock_guard<std::mutex> Locker;

class Job
{
private:

  std::time_t mTime;
  int mFibs;

  std::thread *mThread;

  void callback(void);

  // This mutex assures that the fibonacii sequenc
  // is printed in its entirety. 
  static std::mutex s_Mutex;

public:
  // Add job with a schedule time, tried to use miliseconds but it become 
  // very complicated, see std::chrono. There is no standard for millisecond
  // granularity on Unix or in STL.  
  Job(std::time_t time, int fibs);

  // Not needed but for good measure.  
  Job(Job&& move);
  Job(const Job& copy);
  Job& operator=(const Job& copy);
  
  std::time_t when(std::time_t now = std::time(nullptr));

  bool ready(std::time_t time);

  bool operator<(const Job& rhs);

  void run(void);

  void Join();

  // Sort the jobs by time so the scheduler can find the
  // youngest job. 
  friend bool operator<(const Job& lhs, const Job& rhs);

};

#endif
