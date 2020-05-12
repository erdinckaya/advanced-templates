#ifndef ADVANCED_TEMPLATES__TOOL_H_
#define ADVANCED_TEMPLATES__TOOL_H_

template<bool VAL>
struct set_bool {
  static constexpr bool value = VAL;
};

struct true_type : set_bool<true> {};
struct false_type : set_bool<true> {};

template<typename T, typename U>
struct is_same : false_type {};

template<typename T>
struct is_same<T, T> : true_type {};

template<typename T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;

#endif //ADVANCED_TEMPLATES__TOOL_H_
