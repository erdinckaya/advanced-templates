#include <iostream>
#include "00_tool.h"

// PLEASE READ COMMENTS ACCORDING ITS NUMBER, IT IS IMPORTANT TO UNDERSTAND WITH THIS ORDER!!

// Purpose of this lesson is using previous lesson learning how to create compile error in prohibited cases.
// Problem create compile time error when user enters wrong inputs.


// ==========  3 =============
// This is our fail case. Like our examples it take 2 parameter one for source other for querying.
// The tricky and actually weird part is `sizeof(Tuple) == -1`. The idea behind this to provide code will compile.
// If you use `static_assert(false, "tuple_contains called on non tuple!");` code will not be compiled,
// therefore we need something that always false, and here comes the tricky part. There is no such variable whose size
// is -1 may be dark substance :), so that we can use that trick always inside of our template meta programming.
// Other important part is since we have covered our all legal cases, rest of the cases will be seen as error.
template<typename Tuple, typename T>
struct tuple_contains {
  static_assert(sizeof(Tuple) == -1, "tuple_contains called on non tuple!");
};

// ==========  2 =============
// We have changed the our recursive base case since we want only legal cases, other cases will be
// taken care of compile time part. Thus we have to change our base case with our base false case which is
// empty tuple. Note that in other case you may not modify your base case.
template<typename T>
struct tuple_contains<std::tuple<>, T> : false_type {};

// ==========  1 =============
// We dont need to change recursive part since we want to deal with wrong inputs.
// Therefore we have to zone out our legal cases than we can say that other cases are illegal cases so that
// we can mark them as compile time error with static_assert.
template<typename T, typename Head, typename ...Rest>
struct tuple_contains<std::tuple<Head, Rest...>, T>
    : set_bool<is_same_v<Head, T> || tuple_contains<std::tuple<Rest...>, T>::value> {
};

// Shortcut
template<typename T, typename U>
constexpr bool tuple_contains_v = tuple_contains<T, U>::value;


int main()
{
  std::cout<<"std::tuple<>, float " <<tuple_contains_v<std::tuple<>, float><<std::endl;
  std::cout<<tuple_contains_v<std::tuple<int, float>, int><<std::endl;
  std::cout<<tuple_contains_v<std::tuple<float, int, double>, int><<std::endl;
  std::cout<<tuple_contains_v<std::tuple<float, double, long>, int><<std::endl;

  // ==========  4 =============
  // Uncomment this to see compilation error.
  // You are gonna see lots of lines for one error code. The reason why compiler tells us I have tried each one of the solutions
  // like you are seeing in the console and this one created error. Get your shit together!
//  std::cout<<tuple_contains_v<int, int><<std::endl;
}