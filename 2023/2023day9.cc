#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "absl/strings/str_split.h"

using std::string;
using std::vector;

int get_prev(const vector<int> seq) {
  bool all_zero = true;
  for (int i : seq) {
    if (i != 0) {
      all_zero = false;
      break;
    }
  }
  if (all_zero) return 0;

  vector<int> diff = {};
  for (int i = 1; i < seq.size(); i++) {
    diff.emplace_back(seq[i] - seq[i-1]);
  }
  int prev = get_prev(diff);
  return seq[0] - prev;
}

int get_next(const vector<int> seq) {
  bool all_zero = true;
  for (int i : seq) {
    if (i != 0) {
      all_zero = false;
      break;
    }
  }
  if (all_zero) return 0;

  vector<int> diff = {};
  for (int i = 1; i < seq.size(); i++) {
    diff.emplace_back(seq[i] - seq[i-1]);
  }
  int next = get_next(diff);
  return seq[seq.size() - 1] + next;
}

int part2(const vector<vector<int>> seqs) {
  int sum = 0;
  for (const auto& seq : seqs) {
    sum += get_prev(seq);
  }
  return sum;
}

int part1(const vector<vector<int>> seqs) {
  int sum = 0;
  for (const auto& seq : seqs) {
    sum += get_next(seq);
  }
  return sum;
}

vector<int> to_int(const vector<string>& sv) {
  vector<int> i = {};
  for (auto s : sv) {
    i.push_back(stoi(s));
  }
  return i;
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

  string tmp = "";

  vector<vector<int>> input = {};
  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    input.push_back(to_int(absl::StrSplit(tmp, " ", absl::SkipEmpty())));
  }

  printf("answer to part 1: %d\n", part1(input));
  printf("answer to part 2: %d\n", part2(input));
  return 0;
}
