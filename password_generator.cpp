#include <iostream>
#include <random>
#include <string>

std::string generate_password(int length) {
  static const std::string chars =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()"
      "_+-=[]{}\\|;:'\",.<>/?";
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(0, chars.size() - 1);
  std::string password;
  password.reserve(length);
  for (int i = 0; i < length; ++i) {
    password.push_back(chars[dis(gen)]);
  }
  return password;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <length>" << std::endl;
    return 1;
  }
  const int length = std::stoi(argv[1]);
  std::cout << generate_password(length) << std::endl;
  return 0;
}
