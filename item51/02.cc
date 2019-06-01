
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 

template <typename T, class A = std::allocator<T> >
class SList
{
public:
  SList() { node = nalloc.allocate(1); cout << node->placeholder << endl; }
  ~SList() { nalloc.deallocate(node, 1); }
private:
  struct Node 
  {
    int placeholder; 
    Node *next; 
  }; 

  typedef typename A::template rebind<Node>::other NodeAlloc; 
  NodeAlloc nalloc; 
  Node *node; 
}; 

int main()
{
  SList<int> intList; 
  SList<double> dblList; 
  SList<float> fltList; 
  return 0; 
}
