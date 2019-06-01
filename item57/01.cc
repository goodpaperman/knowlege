
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 

template <typename R, typename E>
R cast(const E &expr) 
{
  return R(expr); 
}

template <int n, typename T>
void repeat(const T &msg)
{
  for(int i=0; i<n; ++ i)
    cout << msg; //<< endl; 
}

template <int bound, typename T>
void zeroOut(T (&ary)[bound])
{
  for(int i=0; i<bound; ++ i)
    ary[i] = i; 
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

template <typename A1, typename A2, typename R>
intComp<A1, A2, R> makeIntComp( R (*fp)(A1, A2) )
{
  return intComp<A1, A2, R>(fp); 
}

int main()
{
  int a = cast<int, double>(12.3); 
  cout << a << endl; 
  a = cast<int>(2.3); 
  cout << a << endl; 
  a = cast<char>(256); 
  cout << a << endl; 
  a = cast<unsigned char>(513); 
  cout << a << endl; 
  cout << endl; 

  repeat<12>(42); 
  repeat<1024>('a'); 
  cout << endl; 

  const int hrsinweek = 7 * 24; 
  float reading[hrsinweek]; 
  zeroOut(reading); 
  for(int i=0; i<hrsinweek; ++ i)
    cout << reading[i] << ","; 

  cout << endl; 
  int iarr[6] = { 1, 3, 5, 2, 4, 8 }; 

  vector<int> ivec(iarr, iarr+6); 
  //sort(ivec.begin(), ivec.end(), isGreater); 
  //sort(ivec.begin(), ivec.end(), intComp<int, int, bool>(isGreater)); 
  sort(ivec.begin(), ivec.end(), makeIntComp(isGreater)); 
  for(int i=0; i<ivec.size(); ++ i)
    cout << ivec[i] << ","; 

  cout << endl; 
  return 0; 
}


