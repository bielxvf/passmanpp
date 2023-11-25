#include <iostream>
#include <cxxopts.hpp>

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


int main(int argc, char **argv) {
  cxxopts::Options options("passman", "Simple password manager");

  options.add_options()
    ("h,help", "Print usage")
    ("v,version", "Print version")
    ("d,debug", "Print debugging info", cxxopts::value<bool>()->default_value("false"))
    ;
  auto args = options.parse(argc, argv);

  bool DEBUG = args["debug"].as<bool>();

  if (args.count("help")) {
    std::cout << options.help() << std::endl;
    exit(EXIT_SUCCESS);
  } else if (args.count("version")) {
    print_version();
    exit(EXIT_SUCCESS);
  } else {
    // No valid option was given
    print_error("No option given, printing help");
    std::cout << options.help() << std::endl;
    exit(EXIT_FAILURE);
  }
}
