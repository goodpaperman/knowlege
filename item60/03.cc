
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

template <typename T>
void slowSort(T a[], int len)
{
  for(int i=0; i<len; ++ i)
    for(int j=i; j<len; ++ j)
      if(a[j] < a[i])
        swap(a[j], a[i]); 
}

template <typename T, typename Comp>
void slowSort(T a[], int len, Comp less)
{
  for(int i=0; i<len; ++ i)
    for(int j=i; j<len; ++ j)
      if(less(a[j], a[i]))
        swap(a[j], a[i]); 
}

int main()
{
  int iarr[] = { 1, 3, 6, 2, 4, 5 }; 
  slowSort(iarr, 6); 
  for(int i=0; i<6; ++ i)
    cout << iarr[i] << ","; 

  cout << endl; 
  slowSort(iarr, 6, std::greater<int>()); 
  for(int i=0; i<6; ++ i)
    cout << iarr[i] << ","; 

  cout << endl; 
  string names[] = { "my", "dog", "has", "fleece" }; 
  slowSort(names, 4); 
  for(int i=0; i<4; ++ i)
    cout << names[i] << ","; 
  
  cout << endl; 
  slowSort(names, 4, std::greater<string>()); 
  for(int i=0; i<4; ++ i)
    cout << names[i] << ","; 

  cout << endl; 
  return 0; 
}


