#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"

using std::cout;
using std::map;
using std::string;
using std::vector;

struct Line {
  string condition;
  vector<int> sizes;
};

vector<int> to_int(const vector<string>& sv) {
  vector<int> i = {};
  for (auto s : sv) {
    i.push_back(stoi(s));
  }
  return i;
}

void PrintLines(std::vector<Line> lines) {
  for (auto line : lines) {
    cout << line.condition << " ";
    for (auto i : line.sizes) {
      cout << i << ',';
    }
    cout << "\n";
  }
}

// must be reset per line
map<string, map<int, long>> cache;

long recur(string condition, int c_index, const vector<int>& sizes,
           int s_index) {
  // printf("%s, %d, size_index=%d\n", condition.c_str(), c_index, s_index);
  auto cur = condition[c_index];
  if (sizes.size() == s_index) {
    // make sure all remaining is . or ?
    for (int i = c_index; i < condition.size(); i++) {
      if (condition[i] == '#') return 0;
    }
    // printf("returning 1\n");
    return 1;
  }
  if (condition.size() <= c_index) {
    return 0;
  }

  // cache
  auto it = cache.find(condition.substr(c_index));
  if (it != cache.end() && it->second.find(s_index) != it->second.end()) {
    // printf("cache hit! returning %d\n", it->second[s_index]);
    return it->second[s_index];
  }

  int size = sizes[s_index];
  long result = 0;
  if (cur == '?') {
    condition[c_index] = '.';
    long skip = recur(condition, c_index, sizes, s_index);
    condition[c_index] = '#';
    long count = recur(condition, c_index, sizes, s_index);
    return skip + count;
  } else if (cur == '.') {
    result = recur(condition, c_index + 1, sizes, s_index);
  } else {
    if (c_index + size > condition.size()) return 0;
    for (int i = c_index; i < c_index + size; i++) {
      if (condition[i] == '.') return 0;
    }
    if (c_index + size == condition.size() && s_index == sizes.size() - 1) {
      // printf("returning 1\n");
      return 1;
    };
    if (condition[c_index + size] == '#') return 0;
    result = recur(condition, c_index + size + 1, sizes, s_index + 1);
  }
  cache[condition.substr(c_index)][s_index] = result;
  // printf("returning %d\n", result);
  return result;
}

long solution(vector<Line> lines) {
  long sum = 0;
  for (auto& line : lines) {
    // global cache reset per line
    cache = {};
    sum += recur(line.condition, 0, line.sizes, 0);
  }
  return sum;
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

  vector<Line> lines_pt1 = {};
  vector<Line> lines_pt2 = {};
  // ???.### 1,1,3
  while (!input_stream.eof()) {
    std::getline(input_stream, tmp, ' ');
    if (tmp == "") continue;
    Line line_pt1;
    Line line_pt2;

    // part 1
    line_pt1.condition = tmp;
    // part 2
    tmp += "?";
    line_pt2.condition = absl::StrCat(tmp, tmp, tmp, tmp, tmp);
    line_pt2.condition.pop_back();

    std::getline(input_stream, tmp);

    // part 1
    line_pt1.sizes = to_int(absl::StrSplit(tmp, ",", absl::SkipEmpty()));
    // part 2
    tmp += ",";
    line_pt2.sizes = to_int(absl::StrSplit(
        absl::StrCat(tmp, tmp, tmp, tmp, tmp), ",", absl::SkipEmpty()));

    lines_pt1.push_back(line_pt1);
    lines_pt2.push_back(line_pt2);
  }

  PrintLines(lines_pt1);
  PrintLines(lines_pt2);

  printf("answer to part 1: %ld\n", solution(lines_pt1));
  printf("answer to part 2: %ld\n", solution(lines_pt2));
  return 0;
}
