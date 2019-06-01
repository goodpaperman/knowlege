
#include <iostream> 
#include <vector> 
#include <deque> 
#include <algorithm> 
#include <iterator> 
#include <string> 

using std::cout; 
using std::endl; 
using std::vector; 
using std::deque; 
using std::string; 


template <typename T, class Cont>
class Heap {
public:
  void push(const T &val); 
  T pop(); 
  bool empty() const { return h_.empty(); }
private:
  Cont h_; 
};

template <typename T, class Cont>
void Heap<T, Cont>::push(const T &val)
{
  h_.push_back(val); 
  std::push_heap(h_.begin(), h_.end()); 
} 

template <typename T, class Cont>
T Heap<T, Cont>::pop()
{
  std::pop_heap(h_.begin(), h_.end()); 
  T tmp(h_.back()); 
  h_.pop_back(); 
  return tmp; 
}

template <typename T, class Cont, typename Out>
void extractHeap(Heap<T, Cont> &h, Out dest)
{
  while(!h.empty())
    *dest ++ = h.pop(); 
}

int main()
{
  Heap<string, vector<string> > strHeap; 
  for(int i=0; i<10; ++ i)
    strHeap.push(string(i, 'a')); 

  vector<string> strVec; 
  extractHeap(strHeap, std::back_inserter(strVec));   
  for(int i=0; i<strVec.size(); ++ i)
    cout << strVec[i] << ", "; 
/*
  Heap<string, deque<char *> > strHeap2; 
  for(int i=10; i>0; -- i)
    strHeap2.push(string(i, 'b')); 

  cout << endl; 
  strVec.clear(); 
  extractHeap(strHeap2, std::back_inserter(strVec)); 
  for(int i=0; i<strVec.size(); ++ i)
    cout << strVec[i] << ", "; 
*/
  cout << endl; 
  return 0; 
}
