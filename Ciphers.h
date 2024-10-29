#pragma once
#include <string>
#include <vector>

namespace cp9 { // cipher police
  class Caesar {
  protected:
    std::string message;
  public:
    Caesar();
    Caesar(std::string str);
    void setMessage(const std::string& str);
    std::string getMessage();
    void encrypt(int key);
    void decryptProcess();
  };

  class Affine : public Caesar {
    void encrypt(std::pair<int, int>);
    void decryptProcess();
  };
}
