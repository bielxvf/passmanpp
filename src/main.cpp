#include "./passmanpp.hpp"
#include <cstdlib>
#include <cxxopts.hpp>
#include <iostream>

int main(int argc, char **argv) {

  cxxopts::Options options("passmanpp", "Simple password manager");

  options.add_options()
    ("h,help", "Print usage")("v,version", "Print version")
    ("d,debug", "Print debugging info", cxxopts::value<bool>()->default_value("false"))
    ("n,new", "Create a new password", cxxopts::value<std::string>())
    ("p,print", "Print a password", cxxopts::value<std::string>())
    ("l,list", "List passwords");

  auto args = options.parse(argc, argv);

  passmanpp::DEBUG = args["debug"].as<bool>();

  if (args.count("help")) {
      std::cout << options.help() << std::endl;
      exit(EXIT_SUCCESS);
  } else if (args.count("version")) {
      passmanpp::print_version();
      exit(EXIT_SUCCESS);
  } else if (args.count("new")) {
      std::string pass_dir;
      passmanpp::init_pass_dir_path(pass_dir);
      passmanpp::create_pass_dir_if_needed(pass_dir);
      std::string pass_name = args["new"].as<std::string>();
      passmanpp::create_new_password(pass_dir, pass_name);
      exit(EXIT_SUCCESS);
  } else if (args.count("print")) {
      std::string pass_dir;
      passmanpp::init_pass_dir_path(pass_dir);
      passmanpp::create_pass_dir_if_needed(pass_dir);
      std::string pass_name = args["print"].as<std::string>();
      passmanpp::print_password(pass_dir, pass_name);
      exit(EXIT_SUCCESS);
  } else if (args.count("list")) {
      std::string pass_dir;
      passmanpp::init_pass_dir_path(pass_dir);
      passmanpp::create_pass_dir_if_needed(pass_dir);
      passmanpp::list_passwords(pass_dir);
      exit(EXIT_SUCCESS);
  } else {
      // No valid option was given
      passmanpp::print_error("No option given, printing help");
      std::cout << options.help() << std::endl;
      exit(EXIT_FAILURE);
  }
}
