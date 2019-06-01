
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

template <> 
class Heap<const char*>
{
public:
  void push(const char *str); 
  const char* pop(); 
  bool empty() const { return h_.empty(); }
private:
  vector<const char*> h_;   
}; 

bool strLess(const char *lhs, const char *rhs)
{
  return strcmp(lhs, rhs) < 0; 
}

void Heap<const char*>::push(const char *str)
{
  h_.push_back(str); 
  std::push_heap(h_.begin(), h_.end(), strLess); 
}

const char* Heap<const char*>::pop()
{
  std::pop_heap(h_.begin(), h_.end(), strLess); 
  const char* ret = h_.back(); 
  h_.pop_back(); 
  return ret; 
}


int main()
{
  Heap<const char *> strHeap; 
  for(int i=10; i>=0; -- i)
  {
    char *str = new char[128]; 
    sprintf(str, "%d", i); 
    strHeap.push(str); 
  }

  vector<const char *> strVec; 
  extractHeap(strHeap, std::back_inserter(strVec));   
  for(int i=0; i<strVec.size(); ++ i)
  {
    cout << strVec[i] << ", "; 
    delete []strVec[i]; 
  }

  cout << endl; 
  return 0; 
}
