// Substitution Failure Is Not An Error.
#include <iostream>
 // Purpose of this lesson is understanding SFINAE easily.
 // By creating two weird functions we are gonna observe the fall back mechanism.

 // Questions
 // 1 - Why we are using arrays as a paramater?
 // We have to create error to apply SFINAE and fall back.
 // Since you cannot define -1 size of error. This will serve our course.
 // 1 - Why we are using two dimentional arrays as a paramater?
 // In C++ two dimentional arrays are actually pointer namely int*[] so that
 // we can use the default nullptr parameter to prevent using dummy arguments,
 // since we dont need parameter.



 // If N is even it creates error and falls back to other.
template<int N>
bool is_odd(int[1][N % 2 == 1 ? 1 : -1] = nullptr)
{
  return true;
}

// If N is odd it creates error and falls back to other.
template<int N>
bool is_odd(int[1][N % 2 == 0 ? 1 : -1] = nullptr)
{
  return false;
}

#if C17
template<int N>
bool is_odd()
{
  if constexpr( N % 2 = 1)
  {
    return true;
  }
  return false;
}
#endif


int main()
{
  // int x[-1] this generates compile error.


  std::cout<<"Odd 5 "<< is_odd<5>() <<std::endl;
  std::cout<<"Odd 4 "<< is_odd<4>() <<std::endl;
  std::cout<<"Odd 0 "<< is_odd<0>() <<std::endl;
}