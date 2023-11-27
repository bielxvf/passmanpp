#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "./colors.hpp"
#include "./password.hpp"

Color::Modifier c_red(Color::FG_RED);
Color::Modifier c_yel(Color::FG_YELLOW);
Color::Modifier c_res(Color::RESET);
Color::Modifier c_bold(Color::BOLD);

static const float VERSION = 0.1;
bool DEBUG;

template <typename T>
void print_error(T t) {
  std::cerr << t << c_red << c_bold << " <-- ERROR" << c_res << std::endl;
}

template <typename T, typename... Args>
void print_error(T t, Args... args) {
  std::cerr << t;
  print_error(args...);
}

template <typename T>
void dbgln(T t) {
  if (DEBUG) {
    std::cerr << t << c_yel << c_bold << " <-- DEBUG" << c_res << std::endl;
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

void create_new_password(std::string pass_dir, std::string pass_name) {
  std::string password_path = pass_dir + pass_name;
  if (!std::filesystem::exists(password_path)) {
    Password new_password;
    std::string password, master_password;
    std::cout << "Enter new password: ";
    std::cin >> password; // TODO: Hide input on terminal screen
    new_password.set(password);
    dbgln("Password input: ", new_password.value());

    std::cout << "Enter Master password";
    std::cin >> master_password; // TODO: Hide input on terminal screen
    new_password.encrypt(master_password);
    dbgln("Encrypted: ", new_password.value());

    std::ofstream password_file;
    password_file.open(password_path);
    password_file << new_password.value();
    password_file.close();
  } else {
    print_error("'", pass_dir + pass_name, "' already exists");
    exit(EXIT_FAILURE);
  }
}
