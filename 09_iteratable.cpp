#include "00_tool.h"
#include <vector>

template<typename... Ts>
struct make_void { typedef void type; };
template<typename... Ts> using void_t = typename make_void<Ts...>::type;

template<typename T, typename V = void>
struct is_iteratable : false_type {};

template<typename T>
struct is_iteratable<T, void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>> : true_type {};

struct Foo {
  int data[10];
  int begin() { return 0; }
  int end() { return 10; }
};

template<typename T>
constexpr bool is_iteratable_v = is_iteratable<T>::value;

struct Bar {};

int main() {
  static_assert(is_iteratable_v<Foo>);
  static_assert(!is_iteratable_v<Bar>);
  static_assert(is_iteratable_v<std::vector<int>>);
}

