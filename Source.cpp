#include <iostream>
#include <string>
#include <stdexcept>
#include "Ciphers.h"

int main() {

  try {

    std::string test_string = "Read the following telephonic conversation between rahul and sonu. You have the following conversation with the speaker.";
    cp9::Caesar machine(test_string);
    machine.encrypt(rand() % 26);
    machine.decryptProcess();
  }

  catch (std::exception exc) {
    std::cout << "\n" << exc.what();
  }
  catch (...) {
    std::cout << "\nunknown exception";
  }
  return 0;
}
