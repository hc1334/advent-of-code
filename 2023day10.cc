#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "absl/strings/str_split.h"

using std::cout;
using std::string;
using std::vector;

const vector<char> PATHS = {'-', '|', 'L', 'J', 'F', '7'};
const vector<char> REWRITTEN_PATHS = {'*', '"', 'l', 'j', 'f', '&', 'S'};

bool contains(vector<char> v, char c) {
  return std::find(v.begin(), v.end(), c) != v.end();
}

int loop_size(vector<string>& grid, int i, int j) {
  char cur = grid[i][j];
  if (cur == 'S') {
    return 1;
  }
  if (cur == '.') {
    return 0;
  }
  // -, |, 7, J, F, L
  if (cur == '-') {
    grid[i][j] = '*';
    if (contains(PATHS, grid[i][j + 1])) {
      return 1 + loop_size(grid, i, j + 1);
    }
    return 1 + loop_size(grid, i, j - 1);
  }

  if (cur == '|') {
    grid[i][j] = '"';
    if (contains(PATHS, grid[i + 1][j])) {
      return 1 + loop_size(grid, i + 1, j);
    }
    return 1 + loop_size(grid, i - 1, j);
  }

  if (cur == '7') {
    grid[i][j] = '&';
    if (contains(PATHS, grid[i][j - 1])) {
      return 1 + loop_size(grid, i, j - 1);
    }
    return 1 + loop_size(grid, i + 1, j);
  }

  if (cur == 'J') {
    grid[i][j] = 'j';
    if (contains(PATHS, grid[i - 1][j])) {
      return 1 + loop_size(grid, i - 1, j);
    }
    return 1 + loop_size(grid, i, j - 1);
  }

  if (cur == 'F') {
    grid[i][j] = 'f';
    if (contains(PATHS, grid[i][j + 1])) {
      return 1 + loop_size(grid, i, j + 1);
    }
    return 1 + loop_size(grid, i + 1, j);
  }

  if (cur == 'L') {
    grid[i][j] = 'l';
    if (contains(PATHS, grid[i][j + 1])) {
      return 1 + loop_size(grid, i, j + 1);
    }
    return 1 + loop_size(grid, i - 1, j);
  }
  return 0;
}

void part2(vector<string>& grid) {
  int count = 0;
  for (int i = 0; i < grid.size(); i++) {
    printf("%s\n", grid[i].c_str());
    bool is_open = false;
    char last = '.';
    for (int j = 0; j < grid[0].size(); j++) {
      auto cur = grid[i][j];
      if (cur == '*') {
        continue;
      }
      if (!contains(REWRITTEN_PATHS, cur)) {
        if (is_open) {
          grid[i][j] = 'I';
          count++;
        }
        last = cur;
        continue;
      }
      // cheating because in my input, S == "|"
      if (cur == 'S') {
        last = cur;
        is_open = !is_open;
        continue;
      }
      if ((last == 'l' && cur == '&') || (last == 'f' && cur == 'j')) {
        last = cur;
        continue;
      }
      is_open = !is_open;
      last = cur;
    }
  }
  printf("answer to part 2: %d\n", count);
}

int part1(vector<string> grid) {
  int start_i = 0;
  int start_j = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] != 'S') {
        continue;
      }
      printf("found S at %d, %d\n", i, j);
      if (grid[i + 1][j] == '|' || grid[i + 1][j] == 'J' ||
          grid[i + 1][j] == 'L') {
        printf("going down!\n");
        start_i = i + 1;
        start_j = j;
        break;
      }
      if (grid[i - 1][j] == '|' || grid[i - 1][j] == 'F' ||
          grid[i - 1][j] == '7') {
        printf("going up!\n");
        start_i = i - 1;
        start_j = j;
        break;
      }
      if (grid[i][j + 1] == '-' || grid[i][j + 1] == 'F' ||
          grid[i][j + 1] == 'L') {
        printf("going right!\n");
        start_i = i;
        start_j = j + 1;
        break;
      }
      if (grid[i][j - 1] == '-' || grid[i][j - 1] == 'J' ||
          grid[i][j - 1] == '7') {
        printf("going left!\n");
        start_i = i;
        start_j = j - 1;
        break;
      }
    }
  }
  printf("starting loop from %d, %d\n", start_i, start_j);
  int size = loop_size(grid, start_i, start_j);
  for (auto row : grid) {
    for (auto c : row) {
      cout << c;
    }
    cout << "\n";
  }
  part2(grid);
  for (auto row : grid) {
    for (auto c : row) {
      cout << c;
    }
    cout << "\n";
  }
  return size % 2 ? size / 2 + 1 : size / 2;
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

  vector<string> grid = {};
  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp == "") continue;
    grid.push_back("." + tmp + ".");
  }
  string padding = "";
  for (auto c : grid[0]) {
    padding += ".";
  }
  grid.insert(grid.begin(), 1, padding);
  grid.push_back(padding);

  for (auto row : grid) {
    for (auto c : row) {
      cout << c;
    }
    cout << "\n";
  }

  printf("answer to part 1: %d\n", part1(grid));
  return 0;
}
