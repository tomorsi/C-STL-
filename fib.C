#include <iostream>



void fib(int mFibs)
{


std::cout << "Generating Fibonacci series (" << mFibs << ")" << std::endl;

std::cout << "\t[ " ;

// By definition first two are [0,1] or [1,1].                                                                                                                                                                       
int prev = 0;
int cur = 1;
 for (int i=0; i<(mFibs-1); i++)
  {
    if (i)
      std::cout << ", ";

    std::cout << prev ;
    int t = prev;
    prev = prev + cur;
    cur = t;
  }
 std::cout << ", " <<prev << "]" << std::endl << std::endl;
}

int main(void)
{
  fib(5);
  fib(2);
  fib(3);
  fib(2);
  fib(7);


  return 0;
}
