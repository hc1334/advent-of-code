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

long part1(vector<int> right, vector<int> left) {
  long sum = 0;
  std::sort(right.begin(), right.end());
  std::sort(left.begin(), left.end());
  for(int i = 0; i < right.size(); i++) {
    sum += abs(right[i] - left[i]);
  }
  return sum;
}

long part2(const vector<int>& right, const vector<int>& left) {
  long score = 0;
  std::map<int, int> map;
  for(auto right_num : right) {
    if (map.find(right_num) != map.end()) {
      map[right_num] = map[right_num] + 1;
    } else {
      map[right_num] = 1;
    }
  }
  for (auto left_num : left) {
    if(map.find(left_num) != map.end()) {
      score += left_num * map[left_num];
    }
  }
  return score;
}

int main(int argc, char* argv[]) {
  ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2024/inputs/2024-day1.txt");
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  std::vector<int> right = {};
  std::vector<int> left= {};
  string tmp = "";

  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp == "") {
      continue;
    }
    std::vector<string> split = absl::StrSplit(tmp, "   ");
    left.push_back(std::stoi(split[0]));
    right.push_back(std::stoi(split[1]));
  }
  printf("answer to part 1: %ld\n", part1(right, left));
  printf("answer to part 2: %ld\n", part2(right, left));
  return 0;
}
