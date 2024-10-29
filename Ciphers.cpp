#include "Ciphers.h"
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
    for (auto& symb : message) {
      if (!isLetter(symb) && !(symb == ' ')) {
        throw std::runtime_error("unavailable symbols");
      }
      if (key < 0 || key > 26) {
        throw std::runtime_error("wrong key");
      }
      if (symb == ' ') continue;
      char anchor = 'a';
      if (upperCase(symb)) anchor = 'A';
      int shift = symb - anchor;
      symb = anchor + (shift + key) % 26;
    }
  }

}