#include <iostream>

// Purpose of this lesson is learning recursion and incremanting the results.
// Problem is get the dimension count of array in compile time.


// First we have to define our function whose name is dimof
// It will take one parameter and return int value.
template <typename T>
struct dimof
{
  static constexpr int value = 0;
};

// We have specialize our function with our recursive case
// In our recursive case, since we are querying arrays we have to get
// array size which is compile time constant and we can get it by adding int Size
// in our parameters. Another important note is we used T[Size] because to specialize with get arrays
// we have to use like array and we have to give the array size as well.

// After we ripped the first part of array T will represent the rest of the part
// hence we can continue recursion with T.
template <typename T, int Size>
struct dimof<T[Size]>
{
  static constexpr int value = dimof<T>::value + 1;
};


// Lets resolve the example more elegant way.
// First create value base struct

template<int VAL>
struct set_value {
  static constexpr int value = VAL;
};

// Create new dimof
template<typename T>
struct dimof2 : set_value<0> {};

// Create our recusive case.
template<typename T, int Size>
struct dimof2<T[Size]> : set_value<dimof2<T>::value + 1> {};

// Finally create shortcut.
template<typename T>
constexpr int dimof2_v = dimof2<T>::value;

int main()
{
  std::cout<<"size "<<dimof<int>::value<<std::endl;
  std::cout<<"size int[1] "<<dimof<int[1]>::value<<std::endl;
  std::cout<<"size int[1][1] "<<dimof<int[1][2]>::value<<std::endl;
  std::cout<<"size int[1][1][1] "<<dimof<int[1][2][3]>::value<<std::endl;


  // Elegant way
  std::cout<<"size "<<dimof2_v<int><<std::endl;
  std::cout<<"size int[1] "<<dimof2_v<int[1]><<std::endl;
  std::cout<<"size int[1][1] "<<dimof2_v<int[1][2]><<std::endl;
  std::cout<<"size int[1][1][1] "<<dimof2_v<int[1][2][3]><<std::endl;
}
