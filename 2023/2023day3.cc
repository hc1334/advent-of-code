#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include "absl/strings/str_split.h"

using std::cout;
using std::string;

bool is_number(const std::string& s) {
  return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) {
                         return !std::isdigit(c);
                       }) == s.end();
}
// part2
// unpredictable if a single gear is adjacent to more than 2 part numbers
int multiple_of_parts(const std::vector<std::vector<string>>& grid) {
  int gear_ratio = 0;
  for (int i = 1; i < grid.size() - 1; i++) {
    for (int j = 1; j < grid[0].size() - 1; j++) {
      if (grid[i][j] != "*") {
        continue;
      }
      int first_num = 0;
      for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
          auto to_insert = grid[x][y];
          if (is_number(to_insert)) {
            if (first_num == 0) {
              first_num = stoi(to_insert);
            } else {
              gear_ratio += (first_num * stoi(to_insert));
              first_num = 0;
              continue;
            }
            while (is_number(grid[x][y])) {
              y++;
            }
          }
        }
      }
    }
  }
  return gear_ratio;
}

// part 1
int sum_of_parts(const std::vector<std::vector<string>>& grid) {
  std::vector<int> parts;
  for (int i = 1; i < grid.size() - 1; i++) {
    for (int j = 1; j < grid[0].size() - 1; j++) {
      if (grid[i][j] != "*") {
        continue;
      }
      for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
          auto to_insert = grid[x][y];
          if (is_number(to_insert)) {
            parts.push_back(stoi(grid[x][y]));
            while (is_number(grid[x][y])) {
              y++;
            }
          }
        }
      }
    }
  }
  for (auto& line : grid) {
    for (string c : line) {
      cout << c.c_str();
    }
    cout << "\n";
  }
  int sum = 0;
  for (int num : parts) {
    sum += num;
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

  std::vector<std::vector<string>> grid = {};
  string tmp = "";
  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp.empty()) continue;
    grid.push_back(absl::StrSplit("." + tmp + ".", ""));
  }
  std::vector<string> empty = {};
  for (auto c : grid[0]) {
    empty.push_back(".");
  }
  grid.push_back(empty);
  grid.insert(grid.begin(), 1, empty);

  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      int tmp_j = j;
      string num = "";
      while (isdigit(grid[i][tmp_j][0])) {
        num += grid[i][tmp_j];
        tmp_j++;
      }
      if (!num.empty()) {
        for (int k = j; k < tmp_j; k++) {
          grid[i][k] = num;
        }
        j = tmp_j - 1;
        continue;
      }
      // not num
      if (grid[i][j] != ".") {
        grid[i][j] = "*";
      }
    }
  }

  printf("answer to part 1: %d\n", sum_of_parts(grid));
  printf("answer to part 1: %d\n", multiple_of_parts(grid));
  return 0;
}

