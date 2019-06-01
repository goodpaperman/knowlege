
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

template <typename T, int n>
class Heap<T[n]>
{
public:
  void push(T val); 
  T pop(); 
  bool empty() const { return h_.empty(); }
private:
  vector<T> h_; 
}; 

template <typename T>
struct PtrCmp : public std::binary_function<T *, T *, bool> 
{
  bool operator() (const T *lhs, const T *rhs) const 
  { return *lhs < *rhs; } 
}; 

template <typename T, int n>
void Heap<T[n]>::push(T pval)
{
  //  if(pval)
  {
    h_.push_back(pval); 
    push_heap(h_.begin(), h_.end()); //, PtrCmp<T>()); 
  }
}

template <typename T, int n>
T Heap<T[n]>::pop()
{
  pop_heap(h_.begin(), h_.end()); //, PtrCmp<T>()); 
  T tmp = h_.back(); 
  h_.pop_back(); 
  return tmp; 
}


int main()
{
  int iarr[6] = { 1, 3, 5, 7, 2, 4 }; 
  Heap<int[6]> intHeap; 
  for(int i=0; i<6; ++ i)
    intHeap.push(iarr[i]); 

  vector<int> intVec; 
  extractHeap(intHeap, std::back_inserter(intVec)); 
  for(int i=0; i<intVec.size(); ++ i)
    cout << intVec[i] << ", "; 

  cout << endl; 
  return 0; 
}
