
#include <iostream> 
#include <vector> 
#include <deque> 
#include <list> 
#include <set> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 
using std::deque; 
using std::list; 
using std::set; 


template <typename T, template <typename> class Cont = vector>
class Heap {
public:
  void push(const T &val); 
  T pop(); 
  bool empty() const { return h_.empty(); }
private:
  Cont<T> h_; 
};

template <typename T, template <typename> class Cont>
void Heap<T, Cont>::push(const T &val)
{
  h_.push_back(val); 
  std::push_heap(h_.begin(), h_.end()); 
} 

template <typename T, template <typename> class Cont>
T Heap<T, Cont>::pop()
{
  std::pop_heap(h_.begin(), h_.end()); 
  T tmp(h_.back()); 
  h_.pop_back(); 
  return tmp; 
}

template <typename T, template <typename> class Cont, typename Out>
void extractHeap(Heap<T, Cont> &h, Out dest)
{
  while(!h.empty())
    *dest ++ = h.pop(); 
}

int main()
{
  Heap<int> intHeap; 
  for(int i=0; i<10; ++ i)
    intHeap.push(i); 

  vector<int> intVec; 
  extractHeap(intHeap, std::back_inserter(intVec));   
  for(int i=0; i<intVec.size(); ++ i)
    cout << intVec[i] << ", "; 

  Heap<int, deque> intHeap2; 
  for(int i=10; i>0; -- i)
    intHeap2.push(i); 

  cout << endl; 
  intVec.clear(); 
  extractHeap(intHeap2, std::back_inserter(intVec)); 
  for(int i=0; i<intVec.size(); ++ i)
    cout << intVec[i] << ", "; 

  cout << endl; 
  return 0; 
}
