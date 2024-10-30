#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
#include "Ciphers.h"

int main() {
  srand(time(0));
  std::string test_string = "(Can you hear it?) (Tick, tick, tick, gotta stop it) Timebomb,the countdown's on Time is running out, yeah,it's almost gone";

  cp9::Dictionary popular;
  popular.loadFromFile("data/dictionary.txt");
  popular.sort();
  // popular.printDictionary(std::cout);

  if (true) {
    try {
      cp9::Caesar machine(test_string);
      machine.loadFromFile("data/original text.txt");
      machine.encrypt(11);
      std::cout << "Encrypted message:\n" << machine.getMessage();
      machine.decryptAuto(popular);

      std::cout << "\n\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n";

      std::cout << "\nDecrypted message:\n";
      std::cout << machine.getMessage();
      int a;
      std::cin >> a;
    }

    catch (std::exception exc) {
      std::cout << "\n" << exc.what();
    }
    catch (...) {
      std::cout << "\nunknown exception";
    }
  }


  try {
    cp9::Affine machine(test_string);
    
    int a = rand() % 26;
    int b = rand() % 26;
    while (a % 2 == 0 || a == 13) {
      a = rand() % 26;
    }
    machine.encrypt(std::make_pair(a, b));
    std::cout << "Encrypted message:\n" << machine.getMessage();
    machine.decryptAuto(popular);
    std::cout << "\nDecrypted message:\n";
    std::cout << machine.getMessage();
  }

  catch (std::exception exc) {
    std::cout << "\n" << exc.what();
  }
  catch (...) {
    std::cout << "\nunknown exception";
  }
  

  char exit;
  std::cin >> exit;
  return 0;
}
