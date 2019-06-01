
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 

template <class T>
class AnAlloc 
{
public:
  template <class Other>
  class rebind
  {
  public:
    typedef AnAlloc<Other> other; 
  }; 

  T* alloc() { return new T; }
};

int main()
{
  typedef AnAlloc<int> AI; 
  typedef AI::rebind<double>::other AD; 
  typedef AnAlloc<double> Ad; 

  AI ai; 
  AD ad; 
  Ad ad2; 

  int *pint = ai.alloc(); 
  cout << *pint << endl; 
  delete pint; 
  double *pdbl = ad.alloc(); 
  cout << *pdbl << endl; 
  delete pdbl; 
  pdbl = ad2.alloc(); 
  cout << *pdbl << endl; 
  delete pdbl; 
  return 0; 
}
