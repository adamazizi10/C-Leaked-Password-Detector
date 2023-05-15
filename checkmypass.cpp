#include "checkmypass.h"
#include <cstring>
#include <curl/curl.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

int CheckMyPass::pwned_api_check(const std::string &password) {
  const std::string sha1password = sha1(password);
  const std::string first5_char = sha1password.substr(0, 5);
  const std::string tail = sha1password.substr(5);
  const std::string response = request_api_data(first5_char);
  const std::string count_str = get_password_leaks_count(response, tail);
  if (count_str.empty()) {
    return 0;
  }
  return std::stoi(count_str);
}

std::string CheckMyPass::sha1(const std::string &str) {
  unsigned char hash[20];
  SHA1(reinterpret_cast<const unsigned char *>(str.c_str()), str.size(), hash);
  std::ostringstream ss;
  ss << std::hex << std::uppercase << std::setfill('0');
  for (const auto &c : hash) {
    ss << std::setw(2) << static_cast<int>(c);
  }
  return ss.str();
}

std::vector<std::string>
CheckMyPass::split_string(const std::string &str,
                          const std::string &delimiter) {
  std::vector<std::string> tokens;
  size_t start = 0;
  size_t end = 0;
  while ((end = str.find(delimiter, start)) != std::string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delimiter.length();
  }
  tokens.push_back(str.substr(start));
  return tokens;
}

std::string
CheckMyPass::get_password_leaks_count(const std::string &hashes,
                                      const std::string &hash_to_check) {
  const std::vector<std::string> lines = split_string(hashes, "\r\n");
  for (const auto &line : lines) {
    const std::vector<std::string> parts = split_string(line, ":");
    if (parts.size() != 2) {
      throw std::runtime_error("Invalid hash format");
    }
    const std::string hash = parts[0];
    const std::string count_str = parts[1];
    if (hash == hash_to_check) {
      return count_str;
    }
  }
  return "";
}

std::string CheckMyPass::request_api_data(const std::string &password) {
  const std::string url = "https://api.pwnedpasswords.com/range/" + password;
  CURL *curl = curl_easy_init();
  if (!curl) {
  throw std::