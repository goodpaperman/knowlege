
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 

struct Yes {}; 
struct No {}; 

template <typename T>
struct IsPtr
{ enum { result = false }; typedef No Result; }; 

template <typename T>
struct IsPtr<T *>
{ enum { result = true }; typedef Yes Result; }; 

template <typename T>
struct IsPtr<T *const>
{ enum { result = true }; typedef Yes Result; }; 

template <typename T>
struct IsPtr<T *volatile> 
{ enum { result = true }; typedef Yes Result; }; 

template <typename T>
struct IsPtr<T *const volatile> 
{ enum { result = true }; typedef Yes Result; }; 


template <typename T>
class Heap {
public:
  ~Heap(); 
  void cleanup(Yes); 
  void cleanup(No) { cout << "instantiation cleanup(No)" << endl; }
  void push(const T &val); 
  T pop(); 
  bool empty() const { return h_.empty(); }
private:
  vector<T> h_; 
};

template <typename T>
void Heap<T>::cleanup(Yes)
{
  cout << "instantiation cleanup(Yes)" << endl; 
  for(int i=0; i<h_.size(); ++ i)
    delete h_[i]; 
}

template <typename T>
Heap<T>::~Heap()
{
  cleanup(typename IsPtr<T>::Result()); 
}

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

//template void Heap<int>::cleanup(Yes); 

int main()
{
  Heap<int> intHeap; 
  for(int i=0; i<10; ++ i)
    intHeap.push(i); 

  Heap<int*> pintHeap; 
  for(int i=0; i<10; ++ i)
    pintHeap.push(new int(i)); 

  //vector<int> intVec; 
  //extractHeap(intHeap, std::back_inserter(intVec));   
  //for(int i=0; i<intVec.size(); ++ i)
  //  cout << intVec[i] << ", "; 

  cout << endl; 
  return 0; 
}
