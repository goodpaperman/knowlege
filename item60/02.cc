
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

int main()
{
  int iarr[] = { 1, 3, 6, 2, 4, 5 }; 
  slowSort(iarr, 6); 
  for(int i=0; i<6; ++ i)
    cout << iarr[i] << ","; 

  cout << endl; 
  string names[] = { "my", "dog", "has", "fleece" }; 
  slowSort(names, 4); 
  for(int i=0; i<4; ++ i)
    cout << names[i] << ","; 
  
  cout << endl; 
  return 0; 
}


