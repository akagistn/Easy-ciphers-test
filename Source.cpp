#include <iostream>
#include <string>
#include <stdexcept>
#include "Ciphers.h"

int main() {

  try {

    std::string line = "Dagi slamdagi Slum gagi";
    cp9::Caesar machine(line);
    machine.encrypt(rand() % 26);
    std::cout << machine.getMessage() << "\n";
  }

  catch (std::exception exc) {
    std::cout << "\n" << exc.what();
  }
  catch (...) {
    std::cout << "\nunknown exception";
  }
  return 0;
}
