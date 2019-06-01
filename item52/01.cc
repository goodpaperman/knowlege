
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 

template <typename T>
struct IsInt
{ enum { result = false }; }; 
template <>
struct IsInt<int>
{ enum { result = true }; }; 

template <typename X>
bool isInt(const X &arg) 
{
  return IsInt<X>::result; 
}

struct No {}; 
struct Yes {}; 

template <typename T>
struct IsArray
{
  enum { result = false }; 
  typedef No Result; 
}; 

template <typename T, int n>
struct IsArray<T [n]>
{
  enum { result = true, bound = n }; 
  typedef Yes Result; 
  typedef T Etype; 
}; 


template <typename T>
bool isArray(const T &a)
{
  return IsArray<T>::result; 
}

template <typename T, int n>
bool isArray(T a[n])
{
  return IsArray<T>::result; 
}


int main()
{
  cout << isInt(1) << endl; 
  cout << isInt(1u) << endl; 
  cout << isInt(1L) << endl; 
  cout << isInt(3.14) << endl; 
  cout << isInt("a") << endl; 
  int a; 
  cout << isInt(a) << endl; 
  cout << endl; 

  int b[6] = { 0 }; 
  cout << isArray(a) << endl; 
  cout << isArray(b) << endl; 
  return 0; 
}
