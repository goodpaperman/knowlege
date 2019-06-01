
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 


template <typename T>
class Heap {
public:
  typedef T Elem; 
  typedef T Temp; 
  void push(const T &val); 
  T pop(); 
  bool empty() const { return h_.empty(); }
private:
  vector<T> h_; 
};

template <typename T>
void Heap<T>::push(const T &val)
{
  h_.push_back(val); 
  std::push_heap(h_.begin(), h_.end()); 
} 

template <typename T>
T Heap<T>::pop()
{
  std::pop_heap(h_.begin(), h_.end()); 
  T tmp(h_.back()); 
  h_.pop_back(); 
  return tmp; 
}

template <typename T, typename Out>
void extractHeap(Heap<T> &h, Out dest)
{
  while(!h.empty())
    *dest ++ = h.pop(); 
}

template <class Container>
typename Container::Elem process(Container &c)
{
  typename Container::Temp tmp = typename Container::Elem(); 
  while(!c.empty())
    tmp += c.pop(); 

  return tmp; 
}

int main()
{
  Heap<int> intHeap; 
  for(int i=0; i<10; ++ i)
    intHeap.push(i); 

  Heap<int>::Elem ret = process(intHeap); 
  cout << "ret = " << ret << endl; 
  
  //vector<int> intVec; 
  //extractHeap(intHeap, std::back_inserter(intVec));   
  //for(int i=0; i<intVec.size(); ++ i)
  //  cout << intVec[i] << ", "; 

  cout << endl; 
  return 0; 
}
