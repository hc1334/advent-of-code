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

long part1(InputType in) {
    std::cout << "running pt1\n";
}
long part2(InputType in) {
    std::cout << "running pt2\n";
}

int main(int argc, char* argv[]) {
  ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2024inputs/2024-day9.txt");
  //ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2024/tmp.txt");
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  InputType input = {};
  string tmp = "";

  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp == "") {
      continue;
    }
    vector<string> colon_split = absl::StrSplit(tmp, ":");
    vector<string> val_strings = absl::StrSplit(colon_split[1], " ");
    vector<int> val_ints = {};
    for (auto val_str : val_strings) {
        if (val_str.size() == 0) continue;
        val_ints.emplace_back(atoi(val_str.c_str()));
    }
    input.emplace_back(atol(colon_split[0].c_str()), val_ints);
  }

  for (auto in : input) {
      std::cout << in.first << ": ";
      for (auto i : in.second) {
          std::cout << i << " ";
      }
      std::cout << "\n";
  }

  printf("answer to part 1: %ld\n", part1(input));
  printf("answer to part 2: %ld\n", part2(input));
  return 0;
}
