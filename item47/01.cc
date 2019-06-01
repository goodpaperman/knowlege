
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

template <typename T>
class Heap<T *>
{
public:
  void push(T *pval); 
  T* pop(); 
  bool empty() const { return h_.empty(); }
private:
  vector<T *> h_; 
}; 

template <typename T>
struct PtrCmp : public std::binary_function<T *, T *, bool> 
{
  bool operator() (const T *lhs, const T *rhs) const 
  { return *lhs < *rhs; } 
}; 

template <typename T>
void Heap<T *>::push(T *pval)
{
  if(pval)
  {
    h_.push_back(pval); 
    push_heap(h_.begin(), h_.end(), PtrCmp<T>()); 
  }
}

template <typename T>
T* Heap<T *>::pop()
{
  pop_heap(h_.begin(), h_.end(), PtrCmp<T>()); 
  T *tmp = h_.back(); 
  h_.pop_back(); 
  return tmp; 
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
  Heap<int *> pintHeap; 
  for(int i=10; i>=0; -- i)
  {
    int *tmp = new int; 
    *tmp = i; 
    pintHeap.push(tmp); 
  }

  vector<int *> pintVec; 
  extractHeap(pintHeap, std::back_inserter(pintVec));   
  for(int i=0; i<pintVec.size(); ++ i)
  {
    cout << *pintVec[i] << ", "; 
    delete pintVec[i]; 
  }

  cout << endl; 
  return 0; 
}
