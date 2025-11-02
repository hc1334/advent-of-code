#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

using std::string;

// part 1
int sum_of_first_last_digits(const std::vector<string>& input) {
  int total_sum = 0;
  for (auto& word : input) {
    string digit_builder = "";
    for (int i = 0; i < word.size(); i++) {
      if (isdigit(word[i])) {
        digit_builder += word[i];
        break;
      }
    }
    for (int i = word.size() - 1; i >= 0; i--) {
      if (isdigit(word[i])) {
        digit_builder += word[i];
        break;
      }
    }
    total_sum += atoi(digit_builder.c_str());
  }
  return total_sum;
}

// part 2
// Doesnt support double digits
const string NUM_AS_STRING_REGEX =
    "^(one|two|three|four|five|six|seven|eight|nine|zero).*";
const std::map<string, int> WORDS_TO_INTS{
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"zero", 0},
};

// Returns if substring of word starting at index i is a digit (in word or
// numberic form). If so, appends `digit_builder` field with digit as string.
bool substring_start_with_digit(string word, int i, string& digit_builder) {
  if (isdigit(word[i])) {
    digit_builder += word[i];
    return true;
  }
  std::regex rx(NUM_AS_STRING_REGEX);
  std::cmatch match;
  if (std::regex_match(word.c_str() + i, match, rx)) {
    for (auto word_to_int : WORDS_TO_INTS) {
      if (word.compare(i, word_to_int.first.size(), word_to_int.first) == 0) {
        digit_builder += std::to_string(word_to_int.second);
        return true;
      }
    }
    // This should never happen. But who cares about error handling now.
  }
  return false;
}

int sum_of_first_last_word_digits(const std::vector<string>& input) {
  int total_sum = 0;
  for (auto& word : input) {
    string digit_builder = "";
    // first digit
    for (int i = 0; i < word.size(); i++) {
      if (substring_start_with_digit(word, i, digit_builder)) {
        break;
      }
    }

    // last digit
    for (int i = word.size() - 1; i >= 0; i--) {
      if (substring_start_with_digit(word, i, digit_builder)) {
        break;
      }
    }
    total_sum += atoi(digit_builder.c_str());
  }
  return total_sum;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "This program expects one parameter that is the input file to "
                 "read.\n";
    return 1;
  }
  std::ifstream input_stream(argv[1]);
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  std::vector<string> input = {};
  string tmp = "";
  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    input.push_back(tmp);
  }
  printf("answer to part 1: %d\n", sum_of_first_last_digits(input));
  printf("answer to part 2: %d\n", sum_of_first_last_word_digits(input));
  return 0;
}
