
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 
#include <string> 

using std::cout; 
using std::endl; 
using std::vector; 
using std::string; 
using std::swap; 

//template Array<int, 10>; 

template <typename T, int n>
class Array
{
public:
  Array() : a_(new T[n]) {}
  ~Array() { delete []a_; }
  void swap(Array &that) { std::swap(a_, that.a_); } 
  T& operator[] (int i) { return a_[i]; } 
  const T& operator[] (int i) const { return a_[i]; } 
  bool operator == (const Array &that) const; 
  bool operator != (const Array &that) const
  { return !(*this == that); } 

private:
  T *a_; 
}; 


//template void Array<int, 10>::swap(Array<int, 10> &that); 

template <typename T, int n>
bool Array<T, n>::operator== (const Array &that) const 
{
  for(int i=0; i<n; ++ i)
    if(!(a_[i] == that.a_[i]))
      return false; 

  return true; 
}

class Widget
{
public:
  void print() { cout << "widget" << endl; }
};

 
template Array<int, 10>::Array(); 
//template Array<>; 
//template Array<int,10>; 
//template Array<Widget, 10>; 
//template vector<int>; 

int main()
{
  //template Array<int,10>; 
  //template vector<int>; 
  Array<int, 10> a, b; 
  cout << "a == b ? " << (a == b) << endl; 
  for(int i=0; i<10; ++ i)
    a[i] = i; 

  cout << "a == b ? " << (a == b) << endl; 

  Array<Widget, 100> w; 
  w[2].print(); 
  //w == w; 
  //template Array<Widget, 2>; 
  cout << endl; 
  return 0; 
}


