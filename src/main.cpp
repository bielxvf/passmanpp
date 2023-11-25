#include <iostream>
#include <cxxopts.hpp>

template <typename T>
void dbgln(T t) {
  std::cerr << t << std::endl;
}

template<typename T, typename... Args>
void dbgln(T t, Args... args) {
  std::cerr << t;
  dbgln(args...) ;
}

int main(void) {
  return 0;
}
