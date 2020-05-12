#include <iostream>

template<unsigned long VAL>
struct set_value {
  static constexpr unsigned long value = VAL;
};

template<unsigned long V>
struct Fibonacci : set_value<Fibonacci<V - 1>::value + Fibonacci<V - 2>::value> {};

template<>
struct Fibonacci<0L> : set_value<1L> {};

template<>
struct Fibonacci<1> : set_value<1> {};


template<unsigned long V>
constexpr unsigned long Fibonacchi_v = Fibonacci<V>::value;

int main()
{
  std::cout<<Fibonacchi_v<0><<std::endl;
  std::cout<<Fibonacchi_v<1><<std::endl;
  std::cout<<Fibonacchi_v<2><<std::endl;
  std::cout<<Fibonacchi_v<5><<std::endl;
  std::cout<<Fibonacchi_v<10><<std::endl;
  return 0;
}