class Password {
private:
  std::string password;

public:
  void set(std::string pwd) {
    this->password = pwd;
  }

  std::string value(void) {
    return this->password;
  }

  void encrypt(std::string master_password) {
    // TODO
    this->password += ":" + master_password;
  }

  void decrypt(std::string master_password) {
    // TODO
    this->password += ":This was decrypted";
  }
};
