#include <iostream>
#include <tuple>

template <typename T>
struct reflect_members;

template <typename T>
using Reflect_members = reflect_members<std::decay_t<std::remove_reference_t<T>>>;

template <typename T, typename = void>
struct is_reflection : std::false_type {};

template <typename T>
struct is_reflection<T, std::void_t<typename Reflect_members<T>::type>> : std::true_type {};

template <typename T>
inline constexpr bool is_reflection_t = is_reflection<T>::value;

template <typename T>
constexpr std::string_view get_name() {
  using M = reflect_members<std::decay_t<std::remove_reference_t<T>>>;
  return M::name();
}

template <typename T, std::size_t I>
constexpr std::string_view get_name() {
  using M = reflect_members<std::decay_t<std::remove_reference_t<T>>>;
  return M::arr()[I];
}

template <typename... Args, typename F, std::size_t... Idx>
constexpr void for_each(std::tuple<Args...>& t, F&& f, std::index_sequence<Idx...>) {
  (std::forward<F>(f)(std::get<Idx>(t), std::integral_constant<std::size_t, Idx>{}), ...);
}

template <typename... Args, typename F, std::size_t... Idx>
constexpr void for_each(const std::tuple<Args...>& t, F&& f, std::index_sequence<Idx...>) {
  (std::forward<F>(f)(std::get<Idx>(t), std::integral_constant<std::size_t, Idx>{}), ...);
}

template <typename T, typename F>
constexpr std::enable_if_t<is_reflection_t<T>> for_each(T&& /*t*/, F&& f) {
  using M = reflect_members<std::decay_t<std::remove_reference_t<T>>>;
  for_each(M::apply_imp(), std::forward<F>(f), std::make_index_sequence<M::value()>{});
}

struct Bowl {
  int apple{};
  double banana{};
  bool orange{};
};

template <>
struct reflect_members<Bowl> {
  constexpr decltype(auto) static apply_imp() { return std::make_tuple(&Bowl::apple, &Bowl::banana, &Bowl::orange); }
  using type = void;
  using size_type = std::integral_constant<std::size_t, 3>;
  constexpr static std::string_view name() { return "Bowl"; }
  constexpr static std::size_t value() { return size_type::value; }
  constexpr static std::array<std::string_view, size_type::value> arr() { return {"apple", "banana", "orange"}; }
};

struct Numbers {
  int one{};
  double two{};
  bool three{};
};

int main() {
  static_assert(is_reflection<Bowl>::value);
  static_assert(not is_reflection<Numbers>::value);

  static_assert(is_reflection_t<Bowl>);
  static_assert(not is_reflection_t<Numbers>);

  constexpr auto bowl_name = get_name<Bowl>();

  Bowl b{1, 1.2, true};
  for_each(b, [&b](auto v, auto i) {
    std::cout << "class_name: " << get_name<decltype(b)>() << std::endl;
    std::cout << "member: " << get_name<decltype(b), i>() << std::endl;
    std::cout << "value: " << b.*v << std::endl;
    std::cout << std::endl;
  });

  return 0;
}