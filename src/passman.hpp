#pragma once
#include <iostream>
#include <filesystem>

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

#define PROGRAM_NAME "passmanpp"

void init_pass_dir_path(std::string &pass_dir) {
  std::string home_dir = std::getenv("HOME");
  if (!home_dir.empty()) {
    // Construct the config dir based on $HOME variable
    pass_dir = home_dir + "/.config/" + PROGRAM_NAME + "/";
    dbgln("$HOME: ", home_dir);
    dbgln("pass_dir: ", pass_dir);

  } else {
    std::string username = std::getenv("USER");
    if (!username.empty()) {
      // Construct the config dir based on $USER variable
      print_error("No $HOME env variable found, using /home/$USER/");
      pass_dir = "/home/" + username + "/.config/" + PROGRAM_NAME + "/";
      dbgln("$USER: ", username);
      dbgln("pass_dir", pass_dir);

    } else {
      // If neither $HOME nor $USER have a value, crash the program, since we can't
      // safely assume the correct path to the config dir
      print_error("No $USER env variable found");
      exit(EXIT_FAILURE);
    }
  }
}

void create_pass_dir(std::string pass_dir) {
  if(!std::filesystem::create_directories(pass_dir)) {
    if (std::filesystem::is_directory(pass_dir)) {
      dbgln("'", pass_dir, "' already exists");
    } else {
      print_error("Failed to create directory '", pass_dir, "'");
      exit(EXIT_FAILURE);
    }
  } else {
    dbgln("Created '", pass_dir, "' successfully");
  }
}
