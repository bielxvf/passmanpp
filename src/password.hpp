#include <cryptopp/cryptlib.h>

#include <cryptopp/aes.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/randpool.h>
#include <cryptopp/rsa.h>
//#include <cryptopp/validate.h> // Gives compile time error
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/seckey.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <openssl/sha.h>


using namespace CryptoPP;

#define FILE_EXTENSION ".enc2"
#define KEYLEN 32

namespace passmanpp {

  void keygen(std::string pwd, unsigned char *key) {
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, pwd.c_str(), pwd.size());
  SHA256_Final(key, &sha256);
}

class Password {
private:
  std::string path;
  std::string password;

public:
  Password(std::string pwd) { this->password = pwd; }
  Password() {}

  std::string value(void) { return this->password; }

  void set_path(std::string pth) { this->path = pth; }

  void encrypt_to_path(std::string master_password) {

    unsigned char key[KEYLEN];
    keygen(master_password, key);
    unsigned char *iv = (unsigned char *)"0123456789012345";
    size_t key_size = KEYLEN;
    std::string encrypted_path = this->path + FILE_EXTENSION;

    std::string plaintext_path = this->path;
    std::ofstream plaintext_file;
    plaintext_file.open(plaintext_path);
    plaintext_file << this->password;
    plaintext_file.close();

    CBC_Mode<AES>::Encryption encryptor(key, key_size, iv);
    FileSource(plaintext_path.c_str(), true,
               new StreamTransformationFilter(
                   encryptor, new FileSink(encrypted_path.c_str())));

    std::filesystem::remove(plaintext_path);
  }

  void decrypt_from_path(std::string master_password) {
    unsigned char key[KEYLEN];
    keygen(master_password, key);
    unsigned char *iv = (unsigned char *)"0123456789012345";
    size_t key_size = KEYLEN;
    std::string encrypted_path = this->path + FILE_EXTENSION;
    std::string plaintext_path = this->path;

    CBC_Mode<AES>::Decryption decryptor(key, key_size, iv);
    FileSource(encrypted_path.c_str(), true,
               new StreamTransformationFilter(
                   decryptor, new FileSink(plaintext_path.c_str())));

    std::ifstream plaintext_file(plaintext_path);
    plaintext_file >> this->password;
    plaintext_file.close();
    std::filesystem::remove(plaintext_path);
  }
};
}
