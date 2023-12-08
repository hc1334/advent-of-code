#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "absl/strings/match.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

using std::string;
using std::vector;

typedef std::map<string, std::pair<string, string>> CamelMap;

const string START = "AAA";
const string END = "ZZZ";
const string LEFT = "L";
const string RIGHT = "R";

string step(CamelMap& map, string step, string key) {
  if (step == LEFT) {
    return map[key].first;
  }
  return map[key].second;
}

int find_steps(CamelMap& map, vector<string> steps, string start, string end) {
  string cur = start;
  int step_count = 0;
  int step_idx = 0;
  while (!absl::EndsWith(cur, end)) {
    string next_step = steps[step_idx % steps.size()];
    printf("curr: %s, step %s\n", cur.c_str(), next_step.c_str());
    cur = step(map, next_step, cur);
    step_count++;
    step_idx++;
  }
  return step_count;
}

int part1(CamelMap& map, vector<string> steps) {
  return find_steps(map, steps, START, END);
}

// all possible # of steps that will return z
vector<int> get_all_possible_z(CamelMap& map, vector<string> steps,
                               string start) {
  printf("%s \n", start.c_str());
  std::set<string> seen = {};
  int step_idx = 0;
  int step_count = 0;
  vector<int> counts;
  string cur = start;
  string next_step = steps[step_idx];
  // while (seen.insert(cur + next_step).second) {
  while (counts.size() != 5) {
    printf("cur insert %s!\n", (cur + next_step).c_str());
    step_count++;
    printf("taking step %s \n", next_step.c_str());
    cur = step(map, next_step, cur);
    step_idx++;
    next_step = steps[step_idx % steps.size()];
    if (absl::EndsWith(cur, "Z")) {
      printf("%s gets to z at step %d\n", (cur + next_step).c_str(),
             step_count);
      counts.emplace_back(step_count);
    } else {
      printf("%s no z. next!\n", (cur + next_step).c_str());
    }
    printf("next insert %s!\n", (cur + next_step).c_str());
  }
  printf("got counts ok!}\n");
  return counts;
}

long part2(CamelMap& map, vector<string> steps) {
  std::vector<vector<int>> steps_for_nodes = {};
  for (auto key : map) {
    // XVA, GGA, DXA, LTA, BJA, AAA,
    if (absl::EndsWith(key.first, "A")) {
      printf("Starting at node %s{\n", key.first.c_str());
      auto all_possible = get_all_possible_z(map, steps, key.first);
      std::cout << "set size set " << all_possible.size();
      steps_for_nodes.emplace_back(all_possible);
      // printf("Starting at node %s got z at %d\n", key.first.c_str(),
      //        a_node_steps[a_node_steps.size() - 1]);
    }
  }
  long lcm = 1;
  for (auto single_set : steps_for_nodes) {
    std::sort(single_set.begin(), single_set.end());
    std::cout << "sorted set " << single_set.size();
    for (int i : single_set) {
      std::cout << i << ",";
    }
    std::cout << "\n";
    lcm = std::lcm(lcm, (long)single_set[0]);
  }
  return lcm;
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
  // must use c++17 or newer for lcm
  if (__cplusplus == 202101L)
    std::cout << "C++23";
  else if (__cplusplus == 202002L)
    std::cout << "C++20";
  else if (__cplusplus == 201703L)
    std::cout << "C++17";
  else if (__cplusplus == 201402L)
    std::cout << "C++14";
  else if (__cplusplus == 201103L)
    std::cout << "C++11";

  string tmp = "";
  std::getline(input_stream, tmp);
  vector<string> steps = absl::StrSplit(tmp, "", absl::SkipEmpty());

  std::map<string, std::pair<string, string>> camel_map = {};

  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    // AAA = (BBB, CCC)
    if (tmp == "") continue;
    absl::StrReplaceAll({{"=", ""}, {"(", ""}, {")", ""}, {",", ""}}, &tmp);
    vector<string> inputs = absl::StrSplit(tmp, " ", absl::SkipEmpty());
    camel_map[inputs[0]] = std::make_pair(inputs[1], inputs[2]);
  }

  for (auto pair : camel_map) {
    printf("%s: %s, %s\n", pair.first.c_str(), pair.second.first.c_str(),
           pair.second.second.c_str());
  }

  // printf("answer to part 1: %d\n", part1(camel_map, steps));
  printf("answer to part 2: %ld\n", part2(camel_map, steps));
  return 0;
}
