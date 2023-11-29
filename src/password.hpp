#include <cryptopp/cryptlib.h>

#include <cryptopp/base64.h>
#include <cryptopp/hex.h>
#include <cryptopp/rsa.h>
#include <cryptopp/aes.h>
#include <cryptopp/files.h>
#include <cryptopp/randpool.h>
//#include <cryptopp/validate.h> // Gives compile time error
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/seckey.h>

#include <fstream>
#include <filesystem>

#define FILE_EXTENSION ".enc2"


using namespace CryptoPP;

class Password {
private:
  std::string path;
  std::string password;

public:
  Password(std::string pwd) {
    this->password = pwd;
  }

  std::string value(void) {
    return this->password;
  }

  void set_path(std::string pth) {
    this->path = pth;
  }

  void encrypt_to_path(std::string master_password) {
    unsigned char *key = (unsigned char *)master_password.c_str();
    unsigned char *iv = (unsigned char *)"0123456789012345";
    size_t key_size = strlen((const char *)key);
    std::string encrypted_path = this->path + FILE_EXTENSION;


    std::string plaintext_path = this->path;
    std::ofstream plaintext_file;
    plaintext_file.open(plaintext_path);
    plaintext_file << this->password;
    plaintext_file.close();

    std::ofstream encrypted_file;
    encrypted_file.open(encrypted_path);

    CBC_Mode<AES>::Encryption encryptor(key, key_size, iv);
    FileSource(plaintext_path.c_str(), true, new StreamTransformationFilter(encryptor, new FileSink(encrypted_path.c_str())));

    encrypted_file.close();
    std::filesystem::remove(plaintext_path);
  }

  void decrypt_from_path(std::string master_password) {
    // TODO
  }
};
