#include "./passmanpp.hpp"
#include <cstdlib>
#include <cxxopts.hpp>
#include <iostream>

int main(int argc, char **argv) {

  cxxopts::Options options("passmanpp", "Simple password manager");

  options.add_options()("h,help", "Print usage")("v,version", "Print version")(
      "d,debug", "Print debugging info",
      cxxopts::value<bool>()->default_value("false"))(
      "n,new", "Create a new password", cxxopts::value<std::string>());
  auto args = options.parse(argc, argv);

  DEBUG = args["debug"].as<bool>();

  std::string pass_dir;
  init_pass_dir_path(pass_dir);
  create_pass_dir(pass_dir);

  if (args.count("help")) {
    std::cout << options.help() << std::endl;
    exit(EXIT_SUCCESS);
  } else if (args.count("version")) {
    print_version();
    exit(EXIT_SUCCESS);
  } else if (args.count("new")) {
    std::string pass_name = args["new"].as<std::string>();
    dbgln("Pass name: ", pass_name);
    create_new_password(pass_dir, pass_name);
    exit(EXIT_SUCCESS);
  } else {
    // No valid option was given
    print_error("No option given, printing help");
    std::cout << options.help() << std::endl;
    exit(EXIT_FAILURE);
  }
}
