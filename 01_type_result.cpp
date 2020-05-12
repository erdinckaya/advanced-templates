#include "tool.h"

template<typename T>
struct remove_const
{
  using type = T;
};

template<typename T>
struct remove_const<const T>
{
  using type = T;
};

template<typename T>
using remove_const_t = typename remove_const<T>::type;


int main()
{

  static_assert(is_same<remove_const<int>::type, int>::value, "");
  static_assert(is_same<remove_const<const int>::type, int>::value, "");
  static_assert(is_same<remove_const<const float>::type, float>::value, "");

  static_assert(is_same_v<remove_const<int>::type, int>, "");
  static_assert(is_same_v<remove_const<const int>::type, int>, "");
  static_assert(is_same_v<remove_const<const float>::type, float>, "");

  static_assert(is_same_v<remove_const_t<int>, int>, "");
  static_assert(is_same_v<remove_const_t<const int>, int>, "");
  static_assert(is_same_v<remove_const_t<const float>, float>, "");
  return 0;
}
