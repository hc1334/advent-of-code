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

const int N = 0;
const int E = 1;
const int S = 2;
const int W = 3;

typedef vector<vector<char>> GridType;

std::pair<int, int> findStart(const GridType& grid) {
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      // always starts facing up
      if (grid[i][j] == '^') return std::make_pair(i, j);
    }
  }
  return std::make_pair(-1, -1);
}

int countX(const GridType& grid) {
  int count = 0;
  for (auto line : grid) {
    for (auto c : line) {
      if (c == '|' || c == '-' || c == '+') count++;
    }
  }
  return count;
}

bool traverse(GridType& grid, int i, int j, int direction) {
  printf("at %d,%d, direction %d\n", i, j, direction % 4);
  if (i >= grid.size() || j >= grid[0].size()
      || i < 0 || j < 0) return true;

  if (grid[i][j] == '#') return false;

  for (auto line : grid) {
    for (auto c : line) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  switch (direction % 4) {
    case N:
      grid[i][j] = '|';
      if (!traverse(grid, i-1, j, direction)) {
        if(grid[i][j] == '+') return false;
        grid[i][j] = '+';
        return traverse(grid, i, j+1, direction+1);
      }
      return true;
    case E:
      grid[i][j] = '-';
      if (!traverse(grid, i, j+1, direction)) {
        if(grid[i][j] == '+') return false;
        grid[i][j] = '+';
        return traverse(grid, i+1, j, direction+1);
      }
      return true;
    case S:
      grid[i][j] = '|';
      if (!traverse(grid, i+1, j, direction)) {
        if(grid[i][j] == '+') return false;
        grid[i][j] = '+';
        return traverse(grid, i, j-1, direction+1);
      }
      return true;
    case W:
      grid[i][j] = '-';
      if (!traverse(grid, i, j-1, direction)) {
        if(grid[i][j] == '+') return false;
        grid[i][j] = '+';
        return traverse(grid, i-1, j, direction+1);
      }
      return true;
  }
  return true;
}

int part2(GridType grid) {
  auto start_pos = findStart(grid);
  GridType og_grid(grid);
  traverse(grid, start_pos.first, start_pos.second, N);

  int loop_count = 0;
  for (int i = 6; i < grid.size(); i++) {
    for (int j = 3; j < grid[0].size(); j++) {
      printf("replacing %d,%d\n", i, j);
      char tmp = grid[i][j];
      if (tmp != '.' && tmp != '^' && tmp != '#') {
        GridType tmp_grid = og_grid;
        tmp_grid[i][j] = '#';

        //for (auto line : tmp_grid) {
        //  for (auto c : line) {
        //    std::cout << c;
        //  }
        //  std::cout << std::endl;
        //}

        if (!traverse(tmp_grid, start_pos.first, start_pos.second, N)) {
          loop_count++;
          std::cout << "creates a loop" << std::endl;
        }
        //for (auto line : tmp_grid) {
        //  for (auto c : line) {
        //    std::cout << c;
        //  }
        //  std::cout << std::endl;
        //}
        //std::cout << std::endl;

        // grid[i][j] = tmp;
      }
    }
  }
  return loop_count;
}

int part1(GridType grid) {
  auto start_pos = findStart(grid);
  //std::cout << "starting at " << start_pos.first << "," << start_pos.second;
  traverse(grid, start_pos.first, start_pos.second, N);

  /*
  for (auto line : grid) {
    for (auto c : line) {
      std::cout << c;
    }
    std::cout << std::endl;
  }8*/
  
  return countX(grid);
}

int main(int argc, char* argv[]) {
  // ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2024/inputs/2024-day6.txt");
  ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/tmp.txt");
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  GridType grid= {};
  string tmp = "";

  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp == "") {
      continue;
    }
    grid.emplace_back(tmp.begin(), tmp.end());
  }

  //printf("answer to part 1: %d\n", part1(grid));
  printf("answer to part 2: %d\n", part2(grid));
  return 0;
}
