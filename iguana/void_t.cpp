#include <type_traits>

template <class, class = void>
struct has_type_member : std::false_type {};

template <class T>
struct has_type_member<T, std::void_t<typename T::type>> : std::true_type {};

template <class, class = void>
struct has_hello_member : std::false_type {};

template <class T>
struct has_hello_member<T, std::void_t<decltype(T::hello)>> : std::true_type {};

struct Bowl {
  using type = void;
  int hello{};
};

struct Numbers {};

int main() {
  static_assert(has_type_member<Bowl>::value);
  static_assert(not has_type_member<Numbers>::value);

  static_assert(has_hello_member<Bowl>::value);
  static_assert(not has_hello_member<Numbers>::value);

  return 0;
}