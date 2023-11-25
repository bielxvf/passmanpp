#pragma once
#include <iostream>

static const float VERSION = 0.1;
bool DEBUG;

template <typename T>
void print_error(T t) {
  std::cerr << t << " <-- ERROR" << std::endl;
}

template <typename T, typename... Args>
void print_error(T t, Args... args) {
  std::cerr << t;
  print_error(args...);
}

template <typename T>
void dbgln(T t) {
  if (DEBUG) {
    std::cerr << t << " <-- DEBUG" << std::endl;
  }
}

template <typename T, typename... Args>
void dbgln(T t, Args... args) {
  if (DEBUG) {
    std::cerr << t;
    dbgln(args...);
  }
}

void print_version(void) {
  std::cout << VERSION << std::endl;
}
