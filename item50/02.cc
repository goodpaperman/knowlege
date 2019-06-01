
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 

template <typename T, typename Comp>
class Heap {
public:
  template <typename In> Heap(In begin, In end); 
  void push(const T &val); 
  T pop(); 
  bool empty() const { return h_.empty(); }
private:
  Comp comp_; 
  vector<T> h_; 
};

template <typename T, typename Comp>
template <typename In>
Heap<T, Comp>::Heap(In begin, In end)
{
  for(In it = begin; it != end; ++ it)
    push(*it); 
}

template <typename T, typename Comp>
void Heap<T, Comp>::push(const T &val)
{
  h_.push_back(val); 
  std::push_heap(h_.begin(), h_.end(), comp_); 
} 

template <typename T, typename Comp>
T Heap<T, Comp>::pop()
{
  std::pop_heap(h_.begin(), h_.end(), comp_); 
  T tmp(h_.back()); 
  h_.pop_back(); 
  return tmp; 
}

template <typename T, typename Comp, typename Out>
void extractHeap(Heap<T, Comp> &h, Out dest)
{
  while(!h.empty())
    *dest ++ = h.pop(); 
}

int main()
{
  int iarr[6] = { 3, 5, 7, 2, 4, 8}; 
  float farr[6] = { 1.2, 2.1, 3.4, 4.3, 5.6, 6.5 }; 
  Heap<int, std::less<int> > intHeap(iarr, iarr+6); 
//  Heap<float> fltHeap(iarr, iarr+6); 
//  Heap<float> fltHeap(farr, farr+6); 
//  Heap<float> fltHeap(intHeap); 
//  Heap<float> fltHeap; 
//  fltHeap = intHeap; 
//  Heap<int> fltHeap(intHeap); 
//  fltHeap = intHeap; 
  Heap<float, std::greater<float> > fltHeap(iarr, iarr+6); 
//  fltHeap = intHeap; 

  vector<float> fltVec; 
  extractHeap(fltHeap, std::back_inserter(fltVec));   
  for(int i=0; i<fltVec.size(); ++ i)
  {
    cout << fltVec[i] << ", "; 
  }

  cout << endl; 
  return 0; 
}
