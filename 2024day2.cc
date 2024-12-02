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

bool reportOk(const vector<string>& split) {
  bool increasing = atoi(split[0].c_str()) - atoi(split[1].c_str()) > 0 ?
      false : true;
  for (int i = 1; i < split.size(); i++) {
    int prev = atoi(split[i-1].c_str());
    int cur = atoi(split[i].c_str());
    if (prev == cur) return false;
      
    int diff = prev-cur;
    if (abs(diff) < 1 || abs(diff) > 3) return false;
    if (increasing && diff > 0) return false;
    if (!increasing && diff < 0) return false;
  }
  return true;
}

int part1(const vector<string>& reports) {
  int safe = 0;
  for (auto report : reports) {
    vector<string> split = absl::StrSplit(report, " ");
    if (reportOk(split)) {
      safe++;
    }
  }
  return safe;
}

bool isSafeWithDampener(vector<string>& report) {
  if (reportOk(report)) return true;
  for (int i = 0; i < report.size(); i++) {
    string tmp = report[i];
    report.erase(report.begin()+i);
    if (reportOk(report)) return true;
    report.insert(report.begin()+i, tmp);
  }
  return false;
}

int part2(vector<string> reports) {
  int safe = 0;
  for (auto report : reports) {
    vector<string> split = absl::StrSplit(report, " ");
    if (isSafeWithDampener(split)) {
      safe++;
    }
  }
  return safe;
}

int main(int argc, char* argv[]) {
  ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/inputs/2024-day2.txt");
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  std::vector<string> reports= {};
  string tmp = "";

  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp == "") {
      continue;
    }
    reports.push_back(tmp);
  }
  printf("answer to part 1: %d\n", part1(reports));
  printf("answer to part 2: %d\n", part2(reports));
  return 0;
}
