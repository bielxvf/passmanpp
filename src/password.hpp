#include <iostream>

class Password {
private:
  std::string password;
  std::string password_encrypted;

public:
  Password(std::string pwd) {
    this->password = pwd;
  }

  std::string value(void) {
    return this->password;
  }

  std::string value_encrypted(void) {
    return this->password_encrypted;
  }

  void encrypt(std::string master_password) {
  }

  void decrypt(std::string master_password) {
    // TODO
    this->password = this->password_encrypted + ":This was decrypted";
  }
};
