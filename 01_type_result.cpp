#include "00_tool.h"


// Purpose of this lesson is removing the const keyword and compare with
// another type in compile time. Using this technique we are not gonna waste our time
// by getting cast errors in runtime.


// Think about it like if else and this one is the else case.
// And in this case it will not change, since if it has const keyword it will
// go to other case not this one.
template<typename T>
struct remove_const
{
  using type = T;
};


// First we created our base case
// If it has cost our type will be ripped from const.
template<typename T>
struct remove_const<const T>
{
  // ripping the const.
  using type = T;
};

// Shortcut for remove_const
// Note that we have to add `typename` keyword in front of our type
// since we are using the type and `using` keyword. On the other hand
// we use `constexpression bool` for our value case.
template<typename T>
using remove_const_t = typename remove_const<T>::type;


int main()
{
  // static_assert is basic compile time assert. If the value is not true
  // code will not compile.

  // Full usage
  static_assert(is_same<remove_const<int>::type, int>::value, "");
  static_assert(is_same<remove_const<const int>::type, int>::value, "");
  static_assert(is_same<remove_const<const float>::type, float>::value, "");

  // is_same_v usage
  static_assert(is_same_v<remove_const<int>::type, int>, "");
  static_assert(is_same_v<remove_const<const volatile int>::type, volatile int>, "");
  static_assert(is_same_v<remove_const<const float>::type, float>, "");

  // Full shortcut usage.
  static_assert(is_same_v<remove_const_t<int>, int>, "");
  static_assert(is_same_v<remove_const_t<const int>, int>, "");
  static_assert(is_same_v<remove_const_t<const float>, float>, "");

  // Note that all performs same.
  return 0;
}
