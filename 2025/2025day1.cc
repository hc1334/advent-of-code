#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include "absl/strings/str_split.h"

using std::string;
using std::ifstream;
using std::vector;

long part1(vector<string> seq) {
    int cur = 50;
    long count = 0;
    for (auto s : seq) {
        int num = atoi(s.substr(1).c_str());
        if (s[0] == 'L') {
            cur -= num;
        } else if (s[0] == 'R') {
            cur += num;
        } else {
            std::cout << "ERR";
        }
        if (cur % 100 == 0) {
            count++;
        }
    }
    return count;
}

int modulo(int k, int n) {
    return ((k % n) + n) % n;
}

long part2_2(vector<string> seq) {
    std::vector<string> new_seq = vector<string>();
    for (auto s : seq) {
        int num = atoi(s.substr(1).c_str());
        for (int i = 0; i < num; i++) {
            string new_cat = "";
            new_cat += s[0];
            new_seq.emplace_back(new_cat + "1");
        }
    }
    return part1(new_seq);
}

int main(int argc, char* argv[]) {
  // ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2025/tmp.txt");
  ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2025/inputs/2025-day1.txt");
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  string tmp = "";
  vector<string> sequence = vector<string>();

  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp == "") {
      continue;
    }
    sequence.emplace_back(tmp);
  }
  for (auto s : sequence) {
      std::cout << s << "\n";
  }
  printf("answer to part 1: %ld\n", part1(sequence));
  printf("answer to part 2: %ld\n", part2_2(sequence));
  return 0;
}
