#pragma once
#include <string>
#include <vector>

namespace cp9 { // cipher police numba 9

	class Dictionary {
	private:
		std::vector<std::string> words;
	public:
		void clear();
		void loadFromFile(const std::string& file_name);
		void printDictionary(std::ostream& os);
		void sort();
		void reverse();
		bool find(const std::string& word);
		// needs new word on each line
	};

  class Caesar {
  protected:
		std::string message;
  public:
		Caesar();
		Caesar(std::string str);
		void setMessage(const std::string& str);
		void loadFromFile(const std::string& file_name);
		std::string getMessage();
		void encrypt(int key);
		void decryptProcess();
		void decryptAuto(Dictionary& dict);
	};

  class Affine : public Caesar {
  protected:
		void decryptAttempt(std::pair<int, int> key);
  public:
		Affine(std::string str);
		void encrypt(std::pair<int, int> key);
		void decryptProcess();
		void decryptAuto(Dictionary& dict);
  };
}
