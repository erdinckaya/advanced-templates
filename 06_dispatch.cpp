#include <iostream>
#include <type_traits>

// Beware! This is the most advanced and most practical lesson to learn, hence most of the dark points in your mind will
// be vanished. So the purpose is by using of template meta programming, escaping the code duplication and also providing
// auto integration of future features.

// Problem is we have different predefined structs and we want to dump them, however they are supporting different type
// of printing as you can see in below in A, B, C, D, E. While A,B,C is supporting print_to, others are supporting overloaded
// methods.

struct A {
  void print_to(std::ostream &o) {
    o << "A\n";
  }
};

struct B {
  void print_to(std::ostream &o) {
    o << "B\n";
  }
};

struct C {
  void print_to(std::ostream &o) {
    o << "C\n";
  }
};

struct D {};
std::ostream &operator<<(std::ostream &o, D) {
  return o << "D\n";
}

struct E {};
std::ostream &operator<<(std::ostream &o, E) {
  return o << "E\n";
}

// We can easily overload the dump function for each every class or struct.
// Lets analyze this approach.
// First we have to declare dump function for all structs that will violate the code duplication
// principle, but before that it will cause extra work for user, since we all are lazy creatures, no developer wants to
// do extra meaningless work.
// Second is since we copied all code it increased the file size and made it hard to track.
// Hence this can be doable but we want more elegant and efficient way.
#if false
void dump(A a) {
  a.print_to(std::cerr);
}
void dump(B b) {
  b.print_to(std::cerr);
}
void dump(C c) {
  c.print_to(std::cerr);
}
void dump(D d) {
  std::cerr << d;
}
void dump(E e) {
  std::cerr << e;
}
#endif

// So why dont we use templates!
// Yes child your aim is true but we templates are not enough we need meta programming additionally.
// Note that after we defined this function how can we decide that which one is using print_to or which one is
// using operator overloading. The answer is we cant! Thus this is failed.
#if false
template<typename T>
void dump(T t)
{
  // so what next?!
}
#endif

// Yes!, Use meta programming
// Lets start! But before that
// PLEASE READ COMMENTS ACCORDING ITS NUMBER, IT IS IMPORTANT TO UNDERSTAND WITH THIS ORDER!!


// ==========  1 =============
// First things first. We have to decide which objects has print_to or not. Lets create has_print_to



// ==========  4 =============
// This code is obtained from standard library web site.
// Although it seems very complicated, actually it is pretty simple.
// It creates make_void with unlimited parameters and returns void as a type for all cases.
// So that I always returns void, it there wasn't any error before this expression.
template<typename... Ts>
struct make_void { typedef void type; };
template<typename... Ts> using void_t = typename make_void<Ts...>::type;



// ==========  2 =============
// Fail case namely base case for our recursion
// Since void_t creates void always, in order to match our cases second parameter is assigned void as default.
template<typename T, typename = void>
struct has_print_to : std::false_type {};


// ==========  1 =============
// The function is simple itself. It tells us, it takes one parameter then checks for the print_to
// definition if it has print_to returns true otherwise it will fall to false type.
// Lets go unlike the eating courtesy rules, we will go inside to outside.
// First look at this code snipped `decltype(std::declval<T>().print_to(std::declval<std::ostream &>()))`
// And lest evaluate it inside to outside.
// 1 - `std::declval<std::ostream &>()` creates `std::ostream &` instance without constructing it, since declval gets type
// but it does not constructs it.
// 2 - `std::declval<T>()` and look at this code after, it obviously creates T instance but after that it uses .print_to function
// 3 - The most tricky part is this part. We cannot guarantee that all objects have print_to so that we expect that this
// template should not work properly since this is a clear compile error. However in meta programming for template branching
// there is a rule came with C++11 which is SFINAE, Substitution Failure Is Not An Error. Hence we are creating error on purpose
// to benefit from this rule. By creating error we want to get redirect our template specialization into other cases.
// In this case it is false case which is above. On the whole the basic idea is if object has print_to function it goes into
// true state otherwise it goes into false state. Please take attention to power of declval and declval.
// ==========  3 =============
// Another weird part is void_t, you can find the implementation of void_t which is pretty simple.
// Note that you can find void_t in standard library as well. Lets analyze it
// Lest take A as an example it has print_to function and see the steps.

// 1. step
//  template<>
//  struct has_print_to<A, void_t<decltype(std::declval<A>().print_to(std::declval<std::ostream &>()))>>
//      : std::true_type {
//  };

// 2. step
//  template<>
//  struct has_print_to<A, void_t<decltype(std::declval<A>().print_to(std::ostream &))>>
//      : std::true_type {
//  };

// 3. step
//  template<>
//  struct has_print_to<A, void_t<decltype(a.print_to(std::ostream &))>>
//      : std::true_type {
//  };

// 4. step
// Since a.print_to(std::ostream &) is valid case it converted to void, because void_t converts everything to void.
//  template<>
//  struct has_print_to<A, void>
//      : std::true_type {
//  };
// Now we have two type first one takes T and void, second one is taking A and void since their parameters are same
// type compiler match them. Since A does not create any error compiler chooses the true_type and returns it.
// If we have used the D one it is gonna create an error in `.print_to part  and falls back to false case.

template<typename T>
struct has_print_to<T, void_t<decltype(std::declval<T>().print_to(std::declval<std::ostream &>()))>>
    : std::true_type {
};


// Shortcut
template<typename T>
constexpr bool has_print_to_v = has_print_to<T>::value;


template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

template< bool B, class T = void >
using enable_if_t = typename enable_if<B,T>::type;


// ==========  5 =============
// So far so good. We managed to create our template and now we have to use them.
// std::enable_if_t is basically enables if value is true otherwise code will be ignored.
// Because it falls back to other template specialization, by applying SFINAE.
template<typename  T>
enable_if_t<has_print_to_v<T>> dump(T t)
{
  t.print_to(std::cerr);
}

template<typename  T>
enable_if_t<!has_print_to_v<T>> dump(T t)
{
  std::cerr << t;
}

// ==========  6 =============
// If we are using C++17 we can use const expressions if to evaluate our template struct.
// Code will be even clearer.
#if false // version >= C++17
template<typename  T>
void dump(T t)
{
  if constexpr(has_print_to_v<T>) {
    t.print_to(std::cerr);
  } else {
    std::cerr << t;
  }
}
#endif

int main()
{
  A a;
  B b;
  C c;
  D d;
  E e;

  dump(a);
  dump(b);
  dump(c);
  dump(d);
  dump(e);

  return 0;
}