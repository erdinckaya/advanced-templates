#ifndef ADVANCED_TEMPLATES__TOOL_H_
#define ADVANCED_TEMPLATES__TOOL_H_
// First thing of meta programming is different from real programming.
// The differences are like that.
// 1 - structs = function -> In below example set_bool is like a function.
// 2 - return values = static constexpre <type>, this variables are your return values.
// 3 - Loops = recursion. The most tricky part is using loops instead of recursions. Most cases
// We will use base cases and the false cases, in further lessons you can see more that two cases.



// In this example it gets a const time bool value to store it.
// It represents most likely to call member function a.set_bool(bool val);
template<bool VAL>
struct set_bool {
  static constexpr bool value = VAL;
};

// We can pass the features with using inheritance, since set_bool has boolean return value
// Our true_type struct will have it either, therefore we can use true_type as shortcut of set_bool<true>
// Same dynamics are valid for false_type
struct true_type : set_bool<true> {};
struct false_type : set_bool<false> {};

// Since we have true and false values we can compare two types.
// The tricky part is that branching of template programming is working like that.
// For every template usage compiler create samples by using recursion.
// After that it checks every each of them and finds the proper one.
// Writing the same classes or functions with different template parameters is called Template Specialization.
// And there is a rule to understand which special version is tried first
// The order is
// T > T[N] > int[N] ~ T[8]
// T, U<V>  > T, U<char> > T, std::vector<char>
// I know it sounds complicated but you will understand with examples intuitively.




// In this specialization it says us this will take two types
// and they will not same each other so that we are returning false
// by inheriting false_type.
template<typename T, typename U>
struct is_same : false_type {};

// In this specialization we are writing our base case which is the same types.
// In order to do that we design our type with one template parameter, because in our
// base case to take same result they will be same and we need one type.
// Note that we added new parameters in is_same signature which is <T, T> this indicates us
// this version get same type two times at the same time. After that modification we finally reached
// the result. Another very crucial mechanic is SINAE technic, but we will discuss later, not to confuse your mind.
template<typename T>
struct is_same<T, T> : true_type {};


// This is a traditional marking technic to shorten our usage
// Instead of using ::value we are hiding it. Mostly we are using _v suffix for
// Getting value _t for getting type.
template<typename T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;


// Finally we have our basic tools to build our new meta programs.
// Note that all of these definitions and much more is available in standard library :)

#endif //ADVANCED_TEMPLATES__TOOL_H_
