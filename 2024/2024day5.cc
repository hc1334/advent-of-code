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
using std::map;

typedef map<string, vector<string>> rulesType;

int getMid(const vector<string>& line) {
  return atoi(line.at(line.size() / 2).c_str());
}

bool lineValid(std::vector<string>& line, rulesType& rules, bool fix) {
  bool continued = false;
  for (int i = 0; i < line.size(); i++) {
    for (int j = i+1; j < line.size(); j++) {
      for (auto later : rules[line[j]]) {
        if (later == line[i]) {
          if (fix) {
            string tmp = line[i];
            line[i] = line[j];
            line[j] = tmp;
            continued = true;
            continue;
          }
          return false;
        }
      }
    }
  }
  if (continued) return false;
  return true;
}
  
int part2(rulesType& rules, vector<vector<string>>& print) {
  int sum = 0;
  for (auto& line : print) {
    if (!lineValid(line, rules, true)) {
      sum += getMid(line);
    }
  }
  return sum;
}

int part1(rulesType& rules, const vector<vector<string>>& print) {
  int sum = 0;
  for (auto line : print) {
    if (lineValid(line, rules, false)) {
      sum += getMid(line);
    }
  }
  return sum;
}

int main(int argc, char* argv[]) {
  ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2024/inputs/2024-day5.txt");
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  string tmp = "";
  rulesType rules = rulesType ();
  vector<vector<string>> print = vector<vector<string>>();

  std::getline(input_stream, tmp);
  while (tmp!="") {
    vector<string> split = absl::StrSplit(tmp, "|");
    if (rules.find(split[0]) != rules.end()) {
      rules[split[0]].emplace_back(split[1]);
    } else {
      rules.emplace(std::make_pair(split[0], std::vector<string>()));
      rules[split[0]].emplace_back(split[1]);
    }

    std::getline(input_stream, tmp);
  }

  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp == "") {
      continue;
    }
    print.emplace_back(absl::StrSplit(tmp, ","));
  }

  printf("answer to part 1: %d\n", part1(rules, print));
  printf("answer to part 2: %d\n", part2(rules, print));
  return 0;
}
