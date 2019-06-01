
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

using std::cout; 
using std::endl; 
using std::vector; 

template <typename Cont>
struct ContainerTraits
{
  typedef typename Cont::Elem Elem; 
  typedef typename Cont::Temp Temp; 
  typedef typename Cont::Ptr Ptr;
}; 

template <typename T>
struct ContainerTraits<T *>
{
  typedef T Elem; 
  typedef T Temp; 
  typedef T* Ptr;  
}; 

template <typename T>
struct ContainerTraits<const T *>
{
  typedef const T Elem; 
  typedef T Temp; 
  typedef const T* Ptr; 
};

template <typename T, int n>
struct ContainerTraits<T[n]>
{
  typedef T Elem; 
  typedef T Temp; 
  typedef T* Ptr; 
};  

//template <typename T>
//struct ContainerTraits< vector<T> >
//{
//  typedef typename vector<T>::value_type Elem; 
//  typedef typename std::iterator_traits<typename vector<T>::iterator>::value_type Temp; 
//  typedef typename std::iterator_traits<typename vector<T>::iterator>::pointer Ptr; 

//}; 

template <typename T, template<typename> class Cont>
struct ContainerTraits< Cont<T> >
{
  typedef typename Cont<T>::value_type Elem; 
  typedef typename std::iterator_traits<typename Cont<T>::iterator>::value_type Temp; 
  typedef typename std::iterator_traits<typename Cont<T>::iterator>::pointer Ptr; 

}; 


template <typename T>
class Heap {
public:
  typedef T Elem; 
  typedef T Temp; 
  typedef T* Ptr; 

  void push(const T &val); 
  T pop(); 
  bool empty() const { return h_.empty(); }
  size_t size() const { return h_.size(); } 
  T operator[](int i) { return h_[i]; } 
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


template <class Container>
typename ContainerTraits<Container>::Elem process(Container &c, int size)
{
  typename ContainerTraits<Container>::Temp tmp = 
           typename ContainerTraits<Container>::Elem(); 
  for(int i=0; i<size; ++ i)
    tmp += c[i]; 

  return tmp; 
}

int main()
{
  int iarr[6] = { 1, 3, 5, 2, 4, 8 }; 
  //Heap<int> intHeap; 
  //for(int i=0; i<10; ++ i)
  //  intHeap.push(i); 

  //Heap<int>::Elem ret = process(intHeap, intHeap.size()); 
  //cout << "ret = " << ret << endl; 
 
  const int *pint = iarr;  
  int total = process(pint, 6); 
  cout << "total(const) = " << total << endl; 

  int *pint2 = iarr; 
  total = process(pint2, 6); 
  cout << "total = " << total << endl; 

  double darr[6] = { 1.2, 2.1, 3.4, 4.3, 5.6, 6.5 }; 
  double *pdbl = darr; 
  cout << "double = " << process(pdbl, 6) << endl; 
  cout << "double[n] = " << process(darr, 6) << endl; 

  vector<int> intVec(iarr, iarr+6); 
  //extractHeap(intHeap, std::back_inserter(intVec));   
  cout << "vector = " << process(intVec, intVec.size()) << endl; 
  //for(int i=0; i<intVec.size(); ++ i)
  //  cout << intVec[i] << ", "; 

  cout << endl; 
  return 0; 
}
