#include <iostream>
#include <string>
// Purpose of this lesson how to use decltype and declval

// decltype = declare type
//    It creates l-value namely type.
// declval = declare value
//    It creates r-value.
// Bot of them are compile time so that they accept only constant expressions.


int fun();

int main()
{
  decltype(7u + 5u) a; // unsigned int a;
  decltype(std::declval<float>() * std::declval<double>()) b; // double b;
  decltype(std::declval<std::string>().cbegin()) c; // std::string::const_iterator c;

  decltype(fun()) x; // int x;

  std::cout<<sizeof(fun())<<std::endl; // also allowed
}