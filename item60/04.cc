
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

template <typename For>
void slowSort(For b, For e)
{
  for(For i(b); i!=e; ++ i)
    for(For j(i); j!=e; ++ j)
      if(*j < *i)
        swap(*j, *i); 
}

template <typename For, typename Comp>
void slowSort(For b, For e, Comp less)
{
  for(For i=b; i!=e; ++ i)
    for(For j=i; j!=e; ++ j)
      if(less(*j, *i))
        swap(*j, *i); 
}

class Swaper
{
public:
  Swaper(int v) : v_(v) { }
  void swap(Swaper &s)
  {
    cout << "swap " << v_ << " and " << s.v_ << endl; 
    int tmp = s.v_; 
    s.v_ = v_; 
    v_ = tmp; 
  }

  bool operator<(const Swaper &s)
  { return v_ < s.v_; } 

  int v() const { return v_; } 

private:
  int v_; 
}; 

void swap(Swaper &v1, Swaper &v2)
{
  v1.swap(v2); 
}

int main()
{
  int iarr[] = { 1, 3, 6, 2, 4, 5 }; 
  slowSort(iarr, iarr+6); 
  for(int i=0; i<6; ++ i)
    cout << iarr[i] << ","; 

  cout << endl; 
  slowSort(iarr, iarr+6, std::greater<int>()); 
  for(int i=0; i<6; ++ i)
    cout << iarr[i] << ","; 

  cout << endl; 
  string names[] = { "my", "dog", "has", "fleece" }; 
  slowSort(names, names+4); 
  for(int i=0; i<4; ++ i)
    cout << names[i] << ","; 
  
  cout << endl; 
  slowSort(names, names+4, std::greater<string>()); 
  for(int i=0; i<4; ++ i)
    cout << names[i] << ","; 

  cout << endl; 
  Swaper ss[] = { 1, 3, 5, 2, 4, 6 }; 
  slowSort(ss, ss+6); 
  for(int i=0; i<6; ++ i)
    cout << ss[i].v() << ","; 
  
  cout << endl; 
  return 0; 
}


