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

long part1(vector<string> ranges) {
    long invalid_id_sum = 0;
    for (auto range : ranges) {
        vector<string> r = absl::StrSplit(range, '-');
        long start = atol(r[0].c_str());
        long end = atol(r[1].c_str());
        std::cout << start << " to " << end << "\n";
        for (long i = start; i <= end; i++) {
            string pattern = std::to_string(i);
            int patt_size = pattern.size();
            if (patt_size % 2 != 0) continue;
            if (pattern.substr(0, patt_size/2) ==
                pattern.substr(patt_size/2)) {
              // std::cout << pattern << " INVALID ID\n";
              invalid_id_sum += i;
            }
        }
    }
    return invalid_id_sum;
}

long part2(vector<string> ranges) {
    long invalid_id_sum = 0;
    for (auto range : ranges) {
        vector<string> r = absl::StrSplit(range, '-');
        long start = atol(r[0].c_str());
        long end = atol(r[1].c_str());
        std::cout << start << " to " << end << "\n";
        for (long i = start; i <= end; i++) {
            string pattern = std::to_string(i);
            int patt_size = pattern.size();
            for (int k = 2; k <= patt_size; k++) {
              if (patt_size % k != 0) continue;
              int idx = 0;
              string sub_pattern = pattern.substr(0, patt_size/k);
              bool invalid = true;
              while (idx < pattern.size()) {
                  if (sub_pattern != pattern.substr(idx, patt_size/k)) {
                      idx = pattern.size();
                      invalid = false;
                  }
                  idx += patt_size/k;
              }
              if (invalid) {
                std::cout << pattern << " INVALID ID\n";
                invalid_id_sum += i;
                k = patt_size + 1;
              }
            }
        }
    }
    return invalid_id_sum;
}

int main(int argc, char* argv[]) {
  //ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2025/tmp.txt");
  ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2025/inputs/2025-day2.txt");
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  string tmp = "";
  vector<string> ranges = vector<string>();

  if (std::getline(input_stream, tmp)) {
    if (tmp != "") {
      ranges = absl::StrSplit(tmp, ',');
    }
  }
  for (auto s : ranges) {
      std::cout << s << "\n";
  }
  printf("answer to part 1: %ld\n", part1(ranges));
  printf("answer to part 2: %ld\n", part2(ranges));
  return 0;
}
