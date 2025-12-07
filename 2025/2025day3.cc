#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

using std::string;
using std::ifstream;
using std::vector;

long part1(vector<string> banks) {
    long total_joltage = 0;

    for (auto bank : banks) {
        char max = bank[0];
        int max_idx = 0;
        for (int i = 0; i < bank.size() - 1; i++) {
            if (bank[i] > max) {
                max = bank[i];
                max_idx = i;
            }
        }
        char max2 = bank[max_idx + 1];
        for (int i = max_idx + 1; i < bank.size(); i++) {
            if (bank[i] > max2) {
                max2 = bank[i];
            }
        }
        string max_combined = "";
        max_combined += max;
        max_combined += max2;
        total_joltage += atol(max_combined.c_str());
    }

    return total_joltage;
}

long part2(vector<string> banks) {
    long total_joltage = 0;

    for (auto bank : banks) {
        string max_combined = "";
        int max_idx = -1;
        for (int i = 11; i >= 0; i--) {
            char max = '0';
            for (int j = max_idx + 1; j < bank.size() - i; j++) {
                if (bank[j] > max) {
                    max = bank[j];
                    max_idx = j;
                }
            }
            max_combined += max;
        }
        total_joltage += atol(max_combined.c_str());
    }

    return total_joltage;
}

int main(int argc, char* argv[]) {
  // ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2025/tmp.txt");
  ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2025/inputs/2025-day3.txt");
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  string tmp = "";
  vector<string> banks = vector<string>();

  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp == "") {
      continue;
    }
    banks.emplace_back(tmp);
  }
  for (auto s : banks) {
      std::cout << s << "\n";
  }
  printf("answer to part 1: %ld\n", part1(banks));
  printf("answer to part 2: %ld\n", part2(banks));
  return 0;
}
