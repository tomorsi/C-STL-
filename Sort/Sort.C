#include <iostream>

class Interval
{
private:
  int mStartTime;
  int mEndTime;
  
  Interval *mNext;
        
public:
  Interval(int StartTime, int EndTime) : mStartTime(StartTime),mEndTime(EndTime),mNext(nullptr)
  {
  }

  void setNext(Interval *next) { mNext = next; }
  Interval* getNext(void) { return mNext; }       
  
  bool operator <= (const Interval &rhs)
  {
    return mStartTime <= rhs.mStartTime;    
  }
  bool operator > (const Interval &rhs)
  {
    return mStartTime > rhs.mStartTime;    
  }
  
  void Print(void)
  {
    std::cout << "[" << mStartTime << "," << mEndTime << "] " << std::endl;
  }
};


class List
{

private:
  Interval *head;

public:
  List(void) : head(nullptr) { }
  void addNode(int Start, int End)
  {

    if (!head)
      head = new Interval(Start,End);
    else
    {
      Interval *newNode = new Interval(Start,End);

      Interval *node = head;
      if (*newNode<=*head)
      {
	  newNode->setNext(head);
	  head = newNode;
	  return;
      }
      
      while(node)
      {	
        if (!node->getNext()) 
	{
	  node->setNext(newNode);
	  break;
        }
	else if (*newNode>*node && *newNode<=*node->getNext())
	{
	  newNode->setNext(node->getNext());
	  node->setNext(newNode);
	  break;
        }
        node = node->getNext();
      }
    }  
  }  

  void Print(void)
  {
    Interval *node = head;
    while(node)
    {
      node->Print();
      node = node->getNext();
    }	
  }
};

// Failure case
int IntervalArrayFail[6] = { 2,3, 3,5, 1,2 }; 

// Success case
int IntervalArraySuccess[6] = { 4,3, 3,5, 6,2 }; 

int main(void)
{
  List list;

  int size = sizeof(IntervalArrayFail)/sizeof(IntervalArrayFail[0]);

  for (int i=0; i<size; i+=2)
  {
    list.addNode(IntervalArrayFail[i],IntervalArrayFail[i+1]);
  }  

  size = sizeof(IntervalArraySuccess)/sizeof(IntervalArraySuccess[0]);
  for (int i=0; i<size; i+=2)
  {
    list.addNode(IntervalArraySuccess[i],IntervalArraySuccess[i+1]);
  }

  list.Print();
}
