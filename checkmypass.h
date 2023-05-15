#ifndef CHECKMYPASS_H
#define CHECKMYPASS_H

#include <string>
#include <vector>

class CheckMyPass {
public:
  static int pwned_api_check(const std::string &password);
  static std::string sha1(const std::string &str);
  static std::vector<std::string> split_string(const std::string &str,
                                               const std::string &delimiter);

private:
  static std::string get_password_leaks_count(const std::string &hashes,
                                              const std::string &hash_to_check);
  static std::string request_api_data(const std::string &password);
};

#endif // CHECKMYPASS_H
