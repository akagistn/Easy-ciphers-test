#include "Ciphers.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <algorithm>

namespace cp9 {

  int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

  int inverse(int num, int mod) {
    if (mod <= 0) {
      throw std::runtime_error("mod <= 0");
    }
    if (gcd(num, mod) != 1) {
      return 0;
    }
    // bruteforce because we work with small numbers
    for (int i = 1; i < mod; ++i) {
      if ((num * i) % mod == 1) return i;
    }
    return 0;
  }

  bool upperCase(const char& symb) { return (symb >= 'A' && symb <= 'Z'); }
  bool lowerCase(const char& symb) { return (symb >= 'a' && symb <= 'z'); }
  bool isLetter(const char& symb) { return upperCase(symb) || lowerCase(symb); }
  
  std::vector<std::string> parse(const std::string& str) {
    std::vector<std::string> result;
    std::string word = "";
    size_t sz = str.length();
    for (int i = 0; i < sz; ++i) {
      if (isLetter(str[i])) {
        word.push_back(str[i]);
      }
      else {
        if (word != "") {
          result.push_back(word);
          word = "";
        }
      }
    }
    if (word != "") {
      result.push_back(word);
      word = "";
    }
    return result;
  }

  void Dictionary::clear() {
    words = std::vector<std::string>();
  }

  void Dictionary::loadFromFile(const std::string& file_name) {
    std::ifstream is(file_name);
    if (!is.is_open()) {
      throw std::runtime_error("wrong file name (dictionary)");
    }
    std::string tmp;
    while (!is.eof()) {
      is >> tmp;
      words.push_back(tmp);
    }
  }

  void Dictionary::printDictionary(std::ostream& os) {
    for (auto& t : words) {
      os << t << "\n";
    }
  }

  void Dictionary::sort() {
    std::sort(words.begin(), words.end());
  }

  void Dictionary::reverse() {
    size_t sz = words.size();
    for (int i = 0; i <= sz / 2; ++i) {
      std::swap(words[i], words[sz - i - 1]);
    }
  }

  bool Dictionary::find(const std::string& word) {
    int lhs = -1, rhs = words.size() + 1;
    while (rhs - lhs > 1) {
      int mid = lhs + (rhs - lhs) / 2;
      if (words[mid] <= word) {
        lhs = mid;
      }
      else {
        rhs = mid;
      }
    }
    if (lhs == -1) {
      return false;
    }
    // std::cout << "[ " << words[lhs] << " | " << word << " ]";
    if (words[lhs] == word) {
      return true;
    }
    return false;
  }

  Caesar::Caesar() { message = ""; }

  Caesar::Caesar(std::string str) { message = str; }

  void Caesar::setMessage(const std::string& str) { message = str; }

  std::string Caesar::getMessage() { return message; }

  void Caesar::loadFromFile(const std::string& file_name) {
    std::ifstream is(file_name);
    if (!is.is_open()) {
      throw std::runtime_error("cannot open file (Caesar)");
    }
    message = "";
    while (!is.eof()) {
      message.push_back(is.get());
    }
    // std::cout << message;
  }

  void Caesar::encrypt(int key) {
    if (key < 0 || key >= 25) {
      throw std::runtime_error("wrong key");
    }
    for (auto& symb : message) {
      if (!isLetter(symb)) continue;
      char anchor = 'a';
      if (upperCase(symb)) anchor = 'A';
      int shift = symb - anchor;
      symb = anchor + (shift + key) % 26;
    }
  }

  void Caesar::decryptProcess() {
    Caesar machine(message);
    for (int i = 0; i < 26; ++i) {
      machine.encrypt(1);
      std::cout << machine.message << " ~ PRESS ENTER UNTIL IT MAKES SENSE";
      std::string user_answer;
      std::getline(std::cin, user_answer);
      if (user_answer.empty()) continue;
      break;
    }
  }

  void Caesar::decryptAuto(Dictionary& dict) {
    Caesar machine(message);
    for (int i = 0; i < 26; ++i) {
      machine.encrypt(1);
      std::vector<std::string> possible_words = parse(machine.getMessage());
      int cnt = 0, mass = possible_words.size();
      for (auto& t : possible_words) {
        if (dict.find(t)) {
          ++cnt;
        }
        if (cnt * 5 >= mass) { // requires the message to have at least 20% known words
          message = machine.message;
          return;
        }
      }
    }
  }

  Affine::Affine(std::string str) : Caesar(str) {}

  void Affine::encrypt(std::pair<int, int> key) {
    int a = key.first, b = key.second; // y = a * x + b
    if (a < 0 || b < 0 || a > 25 || b > 25) {
      throw std::runtime_error("wrong key");
    }
    if (a % 2 == 0 || a == 13) {
      throw std::runtime_error("wrong key for Affine, gcd(a, 26) != 1");
    }
    for (auto& symb : message) {
      if (!isLetter(symb)) continue;
      char anchor = 'a';
      if (upperCase(symb)) anchor = 'A';
      int shift = symb - anchor;
      symb = anchor + (a * shift + b) % 26;
    }
  }

  void Affine::decryptAttempt(std::pair<int, int> key) {
    int a = key.first, b = key.second;  // y = a * x + b
    if (a < 0 || b < 0 || a > 25 || b > 25) {
      throw std::runtime_error("wrong key");
    }
    if (a % 2 == 0 || a == 13) {
      throw std::runtime_error("wrong key for Affine, gcd(a, 26) != 1");
    }
    for (auto& symb : message) {
      if (!isLetter(symb)) continue;
      char anchor = 'a';
      if (upperCase(symb)) anchor = 'A';
      int shift = symb - anchor;
      symb = anchor + (inverse(a, 26) * (shift - b + 26)) % 26;
    }
  }

  void Affine::decryptProcess() {
    bool flag = false;
    for (int a = 1; a < 26; ++a) {
      if (a % 2 == 0 || a == 13) continue;
      for (int b = 0; b < 26; ++b) {
        Affine machine(message); 
        machine.decryptAttempt(std::make_pair(a, b));
        std::cout << machine.message << " ~ PRESS ENTER UNTIL IT MAKES SENSE";
        std::string user_answer;
        std::getline(std::cin, user_answer);
        if (user_answer.empty()) continue;
        flag = true;
        break;
      }
      if (flag) {
          break;
      }
    }
  }

  void Affine::decryptAuto(Dictionary& dict) {
    bool flag = false;
    for (int a = 1; a < 26; ++a) {
      if (a % 2 == 0 || a == 13) continue;
      for (int b = 0; b < 26; ++b) {
        Affine machine(message);
        machine.decryptAttempt(std::make_pair(a, b));
        std::vector<std::string> possible_words = parse(machine.getMessage());
        int cnt = 0, mass = possible_words.size();
        for (auto& t : possible_words) {
          if (dict.find(t)) {
            ++cnt;
          }
          if (cnt * 5 >= mass) { // requires the message to have at least 20% known words
            message = machine.message;
            return;
          }
        }
      }
    }
  }

}
