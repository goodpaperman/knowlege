
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 


template <typename T> void f( T ) { cout << "void f(T)" << endl; } 
template <typename T> void f( T* ) { cout << "void f(T*)" << endl; } 

typedef char True; 
typedef struct { char a[2]; } False; 

template <typename T> True isPtr(T*); 
False isPtr(...); 
#define is_ptr(e) (sizeof(isPtr(e)) == sizeof(True)) 

template <typename T>
struct IsClass 
{
  template <class C> 
  static True isClass(int C::*); 
  template <class C>
  static False isClass(...); 

  enum { r = 
    sizeof(isClass<T>(0)) == sizeof(True) }; 
}; 

template <class C>
True hasIterator(typename C::iterator const*); 
template <typename T>
False hasIterator(...); 

#define has_iterator(C) (sizeof(hasIterator<C>(0)) == sizeof(True))


template <typename T1, typename T2>
struct CanConvert 
{
  static True canConvert(T2); 
  static False canConvert(...); 
  static T1 makeT1(); 
  enum { r = sizeof(canConvert(makeT1())) == sizeof(True) }; 
}; 

template <typename T>
class Heap
{
public:
  //~Heap() { cout << is_ptr(T) << endl; } 
  void cleanup(bool v) { cout << "cleanup()" << v << endl; }
}; 

int main()
{
  int a; 
  f(1024); 
  f("hello"); 
  f(a); 
  f(&a); 
  
  cout << is_ptr(1024) << endl; 
  cout << is_ptr("hello") << endl;  
  cout << is_ptr(a) << endl; 
  cout << is_ptr(&a) << endl; 
  
  cout << endl; 
  cout << IsClass<int>::r << endl; 
  cout << IsClass<False>::r << endl; 
  cout << IsClass< vector<int> >::r << endl; 
  cout << IsClass<IsClass<int> >::r << endl; 
  cout << IsClass<vector<int>::iterator>::r << endl; 

  cout << endl; 
  cout << has_iterator(int) << endl; 
  cout << has_iterator(vector<int>) << endl; 
  cout << has_iterator(int (*)[4]) << endl; 
  cout << has_iterator(vector<int>::iterator) << endl; 
  cout << has_iterator(char *) << endl; 

  cout << endl; 
  cout << CanConvert<int, double>::r << endl; 
  cout << CanConvert<int, char *>::r << endl; 
  cout << CanConvert<True, char>::r << endl; 
  cout << CanConvert<True, False>::r << endl; 
  cout << CanConvert<void (*)(), int (*)()>::r << endl; 
  cout << CanConvert<int (*)[4], int (*)[3]>::r << endl; 
  cout << CanConvert<char*, const char*>::r << endl; 
  cout << CanConvert<const char*, char*>::r << endl; 
  cout << CanConvert<char*, void*>::r << endl; 
  cout << CanConvert<char**, const char**>::r << endl; 

  //Heap<int> intHeap; 
  //Heap<int*> pintHeap; 
  return 0; 
}


