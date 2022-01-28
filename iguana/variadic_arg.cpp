#include <iostream>

template <typename... Args>
void print(const Args&... args) {
  ((std::cout << args << " "), ...);
  std::cout << std::endl;
}

int main() {
  print(3, 3.23, "asdfa");
  return 0;
}