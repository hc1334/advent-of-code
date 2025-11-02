#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

using std::string;
using std::ifstream;
using std::vector;

int part1(vector<vector<char>> grid) {
  // horizontal
  for (auto line : grid) {
    printf("%s\n", string(line.begin(), line.end()).c_str());
    std::reverse(line.begin(), line.end());
    printf("%s\n", string(line.begin(), line.end()).c_str());
    std::reverse(line.begin(), line.end());
  }
  printf("\n");
  
  // vertical
  for (int i = 0; i < grid[0].size(); i++) {
    string tmp = "";
    for (int j = 0; j < grid.size(); j++) {
      tmp += grid[j][i];
    }
    printf("%s\n", tmp.c_str());
    std::reverse(tmp.begin(), tmp.end());
    printf("%s\n", tmp.c_str());
  } 
  printf("\n");

  // right edge diagonal
  for (int x = 0; x < grid.size(); x++) {
    string tmp = "";
    // '\' diagonal
    int tmp_x = x;
    int tmp_y = grid[0].size()-1;
    while (tmp_x >= 0 && tmp_y >= 0) {
      tmp += grid[tmp_x][tmp_y];
      tmp_x--;
      tmp_y--;
    }
    printf("%s\n", tmp.c_str());
    std::reverse(tmp.begin(), tmp.end());
    printf("%s\n", tmp.c_str());

    // '/' diagonal
    tmp = "";
    tmp_x = x;
    tmp_y = grid[0].size()-1;
    while (tmp_y >= 0 && tmp_x <= grid.size()-1) {
      tmp += grid[tmp_x][tmp_y];
      tmp_x++;
      tmp_y--;
    }
    printf("%s\n", tmp.c_str());
    std::reverse(tmp.begin(), tmp.end());
    printf("%s\n", tmp.c_str());
  }

  // left edge diagonal
  for (int x = 1; x < grid.size() - 1; x++) {
    string tmp = "";
    // '\' diagonal
    int tmp_x = x;
    int tmp_y = 0;
    while (tmp_x <= grid.size()-1 && tmp_y <= grid[0].size()-1) {
      tmp += grid[tmp_x][tmp_y];
      tmp_x++;
      tmp_y++;
    }
    printf("%s\n", tmp.c_str());
    std::reverse(tmp.begin(), tmp.end());
    printf("%s\n", tmp.c_str());

    // '/' diagonal
    tmp = "";
    tmp_x = x;
    tmp_y = 0;
    while (tmp_y <= grid[0].size()-1 && tmp_x >= 0) {
      tmp += grid[tmp_x][tmp_y];
      tmp_x--;
      tmp_y++;
    }
    printf("%s\n", tmp.c_str());
    std::reverse(tmp.begin(), tmp.end());
    printf("%s\n", tmp.c_str());
  }
  return 0;
}

int part2(vector<vector<char>> grid) {
  for (auto line : grid) {
    line.insert(line.begin(), '.');
    line.push_back('.');
  }
  int count = 0;

  for (int i = 1; i < grid.size(); i++) {
    for (int j = 1; j < grid[0].size(); j++) {
      if (grid[i][j] == 'A') {
        if ((grid[i-1][j-1] != 'M' &&
            grid[i-1][j-1] != 'S')  ||
            (grid[i+1][j+1] != 'M' &&
            grid[i+1][j+1] != 'S') ||
            grid[i-1][j-1] == grid[i+1][j+1]) {
          continue;
        }
        if ((grid[i-1][j+1] != 'M' &&
            grid[i-1][j+1] != 'S')  ||
            (grid[i+1][j-1] != 'M' &&
            grid[i+1][j-1] != 'S') ||
            grid[i-1][j+1] == grid[i+1][j-1]) {
          continue;
        }
        count ++;
      }
    }
  }
  return count;
}

int main(int argc, char* argv[]) {
  ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2024/inputs/2024-day4.txt");
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  vector<vector<char>> grid= {};
  string tmp = "";

  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp == "") {
      continue;
    }
    grid.emplace_back(tmp.begin(), tmp.end());
  }

  // printf("answer to part 1: %d\n", part1(grid));
  printf("answer to part 2: %d\n", part2(grid));
  return 0;
}
