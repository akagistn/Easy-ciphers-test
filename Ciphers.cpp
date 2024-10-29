#include "Ciphers.h"
#include <iostream>
#include <string>
#include <stdexcept>

namespace cp9 {

  bool upperCase(const char& symb) { return (symb >= 'A' && symb <= 'Z'); }
  bool lowerCase(const char& symb) { return (symb >= 'a' && symb <= 'z'); }
  bool isLetter(const char& symb) { return upperCase(symb) || lowerCase(symb); }

  Caesar::Caesar() { message = ""; }
  Caesar::Caesar(std::string str) { message = str; }
  void Caesar::setMessage(const std::string& str) { message = str; }
  std::string Caesar::getMessage() { return message; }

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

  void Affine::encrypt(std::pair<int, int> key) {
    int a = key.first, b = key.second; // y = a * x + b
    if (a < 0 || b < 0 || b > 25 || b > 25) {
      throw std::runtime_error("wrong key");
    }
    if (a % 2 == 0 || a == 13) {
      throw std::runtime_error("wrong key for Affine, gcd(a, 26) != 1");
    }
    
  }

  void Affine::decryptProcess() {

  }

}
