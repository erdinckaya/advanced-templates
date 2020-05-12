#include <iostream>
#include "tool.h"

// Purpose of this lesson is creating more complex expressions and using variadic
// templates in a nutshell tail recursions of template meta programming.

// Problem is checking tuple has specific type or not in compile time.

// First we create our tuple_contains struct it takes two parameters
// first one is source which represents the tuple, second one is type which we want to query.
template<typename T, typename U>
struct tuple_contains : false_type {};

// The tricky part is design of this part.
// First we want to query tuples so that we have to specialize our template with tuple.
// You can see that `<std::tuple<Head, Rest...>, T>`.
// T resembles the type we want to query
// Head is the first type that we compare. Rest is the rest of the types.
// We used set_bool assign the result of recursion, because we have to check all of the types, so that
// we cannot finalize the recursion by using tru_type, true_type must be result of the recursion.
// In first part we compared the two type, if it false we continue with tail recursion by using same pattern.
template<typename T, typename Head, typename ...Rest>
struct tuple_contains<std::tuple<Head, Rest...>, T> :
    set_bool<is_same_v<Head, T> || tuple_contains<std::tuple<Rest...>, T>::value> {};


// Shortcut
template<typename T, typename U>
constexpr bool tuple_contains_v = tuple_contains<T, U>::value;

int main()
{
  std::cout<<"std::tuple<>, float " <<tuple_contains_v<std::tuple<>, float><<std::endl;
  std::cout<<tuple_contains_v<std::tuple<int, float>, int><<std::endl;
  std::cout<<tuple_contains_v<std::tuple<float, int, double>, int><<std::endl;
  std::cout<<tuple_contains_v<std::tuple<float, double, long>, int><<std::endl;
}