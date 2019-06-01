
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
  template <typename In> Heap(In begin, In end); 
  template <typename S> Heap(Heap<S> &h); 
  template <typename S> Heap<T>& operator= (Heap<S> &h); 
  Heap() {} 
  Heap(Heap &h); 
  Heap& operator= (Heap &h); 
  void push(const T &val); 
  T pop(); 
  bool empty() const { return h_.empty(); }
private:
  vector<T> h_; 
};

template <typename T>
template <typename In>
Heap<T>::Heap(In begin, In end)
{
  for(In it = begin; it != end; ++ it)
    push(*it); 
}

template <typename T>
template <typename S>
Heap<T>::Heap(Heap<S> &h)
{
  cout << "Heap<T>::Heap(Heap<S> &h) " << endl; 
  while(!h.empty())
    push(h.pop()); 
}

template <typename T>
template <typename S>
Heap<T>& Heap<T>::operator= (Heap<S> &h)
{
  cout << "Heap<T>& Heap<T>::operator= (Heap<S> &h) " << endl; 
  while(!empty())
    pop(); 

  while(!h.empty())
    push(h.pop()); 

  return *this; 
}

template <typename T>
Heap<T>::Heap(Heap<T> &h)
{
  cout << "Heap<T>::Heap(Heap<T> &h) " << endl; 
  while(!h.empty())
    push(h.pop()); 
}

template <typename T>
Heap<T>& Heap<T>::operator=(Heap<T> &h)
{
  cout << "Heap<T>& Heap<T>::operator=(Heap<T> &h) " << endl; 
  while(!empty())
    pop(); 

  while(!h.empty())
    push(h.pop()); 

  return *this; 
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

int main()
{
  int iarr[6] = { 3, 5, 7, 2, 4, 8}; 
  float farr[6] = { 1.2, 2.1, 3.4, 4.3, 5.6, 6.5 }; 
  Heap<int> intHeap(iarr, iarr+6); 
//  Heap<float> fltHeap(iarr, iarr+6); 
//  Heap<float> fltHeap(farr, farr+6); 
//  Heap<float> fltHeap(intHeap); 
//  Heap<float> fltHeap; 
//  fltHeap = intHeap; 
  Heap<int> fltHeap(intHeap); 
  //fltHeap = intHeap; 

  vector<float> fltVec; 
  extractHeap(fltHeap, std::back_inserter(fltVec));   
  for(int i=0; i<fltVec.size(); ++ i)
  {
    cout << fltVec[i] << ", "; 
  }

  cout << endl; 
  return 0; 
}
