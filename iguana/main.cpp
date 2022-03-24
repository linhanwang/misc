#include <iostream>
#include <string_view>
#include <tuple>
#include <vector>

#define GET_ARG_COUNT(...) std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value

#define ADD_VIEW(str) std::string_view(#str, sizeof(#str) - 1)

#define SEPARATOR ,
#define CON_STR_1(element, ...) ADD_VIEW(element)
#define CON_STR_2(element, ...) ADD_VIEW(element) SEPARATOR MACRO_EXPAND(CON_STR_1(__VA_ARGS__))
#define CON_STR_3(element, ...) ADD_VIEW(element) SEPARATOR MACRO_EXPAND(CON_STR_2(__VA_ARGS__))
#define CON_STR_4(element, ...) ADD_VIEW(element) SEPARATOR MACRO_EXPAND(CON_STR_3(__VA_ARGS__))
#define CON_STR_5(element, ...) ADD_VIEW(element) SEPARATOR MACRO_EXPAND(CON_STR_4(__VA_ARGS__))
#define CON_STR_6(element, ...) ADD_VIEW(element) SEPARATOR MACRO_EXPAND(CON_STR_5(__VA_ARGS__))

#define MACRO_EXPAND(...) __VA_ARGS__

// todo add note
#define MACRO_CONCAT(A, B) MACRO_CONCAT1(A, B)
#define MACRO_CONCAT1(A, B) A##_##B

struct Haha {
  int a;
  int b;
  int c;
};

int main() {
  std::string a{"234"};
  std::vector<int> b{1, 2, 3, 4};
  MACRO_CONCAT(CON_STR, 3)(a, b, b);
  std::array<std::string_view, 3> c = {MACRO_EXPAND(MACRO_CONCAT(CON_STR, 3)(a, b, b))};

  static_assert(GET_ARG_COUNT(1, 2, 3, a, Haha{}, b) == 6);

  std::cout << "Hello, World!" << std::endl;
  return 0;
}
