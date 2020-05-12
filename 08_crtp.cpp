// Curiously Recurring Template Pattern

#include <iostream>
// This is the additional lesson. We can use this technique, instead of virtual functions.
// We can use compile time polymorphism. It is faster than virtuals.

template<typename T>
struct Base
{
  void operation()
  {
    std::cout<<"Perform some general work in Base..."<<std::endl;
    static_cast<T*>(this)->implementation();
    std::cout<<"More general work in Base..."<<std::endl;
  }
};


struct Derived : Base<Derived> // CRTP
{
  void implementation()
  {
    std::cout<<"Specialized work in Derived..."<<std::endl;
  }
};

int main()
{

  Derived d;
  d.operation();

  Base<Derived> b = Derived();
  b.operation();

  return 0;
}
