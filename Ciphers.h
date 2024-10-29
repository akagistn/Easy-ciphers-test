#pragma once
#include <string>

namespace cp9 { // cipher police
  class Caesar {
  private:
    std::string message;
  public:
    Caesar();
    Caesar(std::string str);
    void setMessage(const std::string& str);
    std::string getMessage();
    void encrypt(int key);
  };
}
