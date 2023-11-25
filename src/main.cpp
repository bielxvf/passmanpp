#include <iostream>
#include <cxxopts.hpp>

const float VERSION = 0.1;

template <typename T>
void dbgln(T t) {
  std::cerr << t << std::endl;
}

template<typename T, typename... Args>
void dbgln(T t, Args... args) {
  std::cerr << t;
  dbgln(args...) ;
}

void print_version(void) {
  std::cout << VERSION << std::endl;
}


int main(int argc, char **argv) {
  cxxopts::Options options("passman", "Simple password manager");

  options.add_options()
    ("h,help", "Print usage")
    ("v,version", "Print version")
    ("d,debug", "Print debugging info", cxxopts::value<bool>()->default_value("false"))
    ;
  auto args = options.parse(argc, argv);

  if (args.count("help")) {
    std::cout << options.help() << std::endl;
    exit(EXIT_SUCCESS);
  } else if (args.count("version")) {
    print_version();
    exit(EXIT_SUCCESS);
  } else {
    // No arguments were given
    std::cout << options.help() << std::endl;
    exit(EXIT_FAILURE);
  }
}
