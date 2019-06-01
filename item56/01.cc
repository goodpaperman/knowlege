
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 

template <typename T>
class NoDeletePolicy
{
public:
  void operator()(const T& val) 
  { cout << "no delete " << val << endl; }
}; 

template <typename T>
class PtrDeletePolicy
{
public:
  void operator()(T ptr)
  { cout << "delete " << *ptr << endl; delete ptr; }
}; 

template <typename T>
class ArrayDeletePolicy
{
public:
  void operator()(T ptr)
  { cout << "delete[] " << *ptr << endl; delete []ptr; }
}; 


template <typename T, template <typename> class DeletionPolicy = NoDeletePolicy>
class Heap {
public:
  ~Heap(); 
  void push(const T &val); 
  T pop(); 
  bool empty() const { return h_.empty(); }
private:
  vector<T> h_; 
};

template <typename T, template <typename> class DeletionPolicy>
Heap<T, DeletionPolicy>::~Heap()
{
  for(typename vector<T>::iterator it = h_.begin(); it != h_.end(); ++ it)
    DeletionPolicy<T>()(*it); 
}

template <typename T, template <typename> class DeletionPolicy>
void Heap<T, DeletionPolicy>::push(const T &val)
{
  h_.push_back(val); 
  std::push_heap(h_.begin(), h_.end()); 
} 

template <typename T, template <typename> class DeletionPolicy>
T Heap<T, DeletionPolicy>::pop()
{
  std::pop_heap(h_.begin(), h_.end()); 
  T tmp(h_.back()); 
  h_.pop_back(); 
  return tmp; 
}

template <typename T, template <typename> class DeletionPolicy, typename Out>
void extractHeap(Heap<T, DeletionPolicy> &h, Out dest)
{
  while(!h.empty())
    *dest ++ = h.pop(); 
}


int main()
{
  Heap<int> intHeap; 
  for(int i=0; i<10; ++ i)
    intHeap.push(i); 

  Heap<int*, PtrDeletePolicy> pintHeap; 
  for(int i=0; i<10; ++ i)
    pintHeap.push(new int(i)); 

  Heap<char *, ArrayDeletePolicy> pstrHeap; 
  for(int i=0; i<=10; ++ i)
  {
    char *ptr = new char[48]; 
    sprintf(ptr, "%d", i); 
    pstrHeap.push(ptr); 
  }

  //vector<int> intVec; 
  //extractHeap(intHeap, std::back_inserter(intVec));   
  //for(int i=0; i<intVec.size(); ++ i)
  //  cout << intVec[i] << ", "; 

  cout << endl; 
  return 0; 
}
