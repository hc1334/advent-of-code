#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

const long PT2 = 999999;
const long PT1 = 1;

long solution(vector<string>& grid, long add) {
  std::vector<int> empty_cols = {};
  std::vector<int> empty_rows = {};
  vector<std::pair<int, int>> galaxies = {};
  for (int j = 0; j < grid[0].size(); j++) {
    bool no_galaxy_col = true;
    for (int i = 0; i < grid.size(); i++) {
      if (grid[i][j] == '#') {
        no_galaxy_col = false;
      }
    }
    if (no_galaxy_col) {
      empty_cols.push_back(j);
    }
  }
  for (int i = 0; i < grid.size(); i++) {
    bool no_galaxy_row = true;
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == '#') {
        galaxies.emplace_back(std::make_pair(i, j));
        no_galaxy_row = false;
      }
    }
    // add rows
    if (no_galaxy_row) {
      empty_rows.push_back(i);
    }
  }

  long total_dist = 0;
  for (auto pair1 : galaxies) {
    for (auto pair2 : galaxies) {
      if (pair1 >= pair2) continue;
      total_dist +=
          abs(pair1.first - pair2.first) + abs(pair1.second - pair2.second);
      for (auto row : empty_rows) {
        if ((row > pair1.first && row < pair2.first) ||
            (row < pair1.first && row > pair2.first)) {
          total_dist += add;
        }
      }
      for (auto col : empty_cols) {
        if ((col > pair1.second && col < pair2.second) ||
            (col < pair1.second && col > pair2.second)) {
          total_dist += add;
        }
      }
    }
  }
  return total_dist;
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
    grid.push_back(tmp);
  }

  for (auto row : grid) {
    for (auto c : row) {
      cout << c;
    }
    cout << "\n";
  }

  printf("answer to part 1: %ld\n", solution(grid, PT1));
  printf("answer to part 2: %ld\n", solution(grid, PT2));
  return 0;
}
