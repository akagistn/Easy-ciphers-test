#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
#include "Ciphers.h"

int main() {
  srand(time(0));
  std::string test_string = "(Can you hear it?) (Tick, tick, tick, gotta stop it) Timebomb,the countdown's on Time is running out, yeah,it's almost gone";

  try {
    cp9::Affine machine(test_string);
    machine.encrypt(std::make_pair(rand() % 26, rand() % 26));
    machine.decryptProcess();
  }

  catch (std::exception exc) {
    std::cout << "\n" << exc.what();
  }
  catch (...) {
    std::cout << "\nunknown exception";
  }


  if (false) {
    try {
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
  }
  

  char exit;
  std::cin >> exit;
  return 0;
}
