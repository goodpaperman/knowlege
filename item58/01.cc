
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 

template <typename T>
void g(T a, T b) 
{
  cout << "void g(T, T)" << endl; 
}

void g(char a, char b)
{
  cout << "void g(char, char)" << endl; 
}

bool less5(int v)
{
  return v < 5; 
}

bool isGreater(int a, int b)
{
  return a > b; 
}

template <typename A1, typename A2, typename R>
class intComp : public std::binary_function<A1, A2, R>
{
public:
  explicit intComp( R (*fp)(A1, A2) ) : fp_(fp) {}
  R operator() (A1 a1, A2 a2) const 
  { return fp_(a1, a2); } 
private:
  R (*fp_)(A1, A2); 
}; 

template <typename A, typename R>
class PFun1 : public std::unary_function<A, R>
{
public:
  explicit PFun1( R (*fp)(A) ) : fp_(fp) {}
  R operator()( A a ) const 
  { return fp_(a); } 
private:
  R (*fp_)(A); 
}; 

template <typename R, typename A>
PFun1<A, R> makePFun( R (*fp)(A) )
{
  return PFun1<A, R>(fp); 
}

template <typename A1, typename A2, typename R>
intComp<A1, A2, R> makePFun( R (*fp)(A1, A2) )
{
  return intComp<A1, A2, R>(fp); 
}

int main()
{
  g(12.3, 45.6); 
  g(12.3, 45); 
  g(12, 45); 
  g('a', 'b'); 
  cout << endl; 


  int iarr[6] = { 1, 3, 5, 2, 4, 8 }; 

  vector<int> ivec(iarr, iarr+6); 
  //sort(ivec.begin(), ivec.end(), isGreater); 
  //sort(ivec.begin(), ivec.end(), intComp<int, int, bool>(isGreater)); 
  sort(ivec.begin(), ivec.end(), makePFun(isGreater)); 
  for(int i=0; i<ivec.size(); ++ i)
    cout << ivec[i] << ","; 

  cout << endl; 
  vector<int>::iterator it = find_if(ivec.begin(), ivec.end(), makePFun(less5)); 
  if(it != ivec.end())
    cout << "find_if(less5) = " << *it << endl; 

  cout << endl; 
  return 0; 
}


