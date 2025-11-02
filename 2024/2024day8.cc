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
using std::cout;

typedef vector<vector<string>> InputType;

map<string, vector<std::pair<int, int>>> node_locations = {};

bool withinBounds(int max_x, int max_y, int x, int y) {
    return x >= 0 && x <= max_x && y >= 0 && y <= max_y;
}

long part1(InputType in) {
    std::cout << "running pt1\n";
    int max_x = in[0].size() - 1;
    int max_y = in.size() - 1;
    
    for (auto map_it : node_locations) {
        auto locations = map_it.second;
        for (auto coord1 : locations) {
            for (auto coord2 : locations) {
                if (coord1 == coord2) continue;
                int new_y = coord1.first + (coord1.first - coord2.first);
                int new_x = coord1.second + (coord1.second - coord2.second);
                        
                if (withinBounds(max_x, max_y, new_y, new_x)) {
                    in[new_y][new_x] = "#";
                }

            }
        }
    }

    long antinode_counter = 0;
    for (auto line : in) {
        for (auto node : line) {
            if (node == "#") antinode_counter++;
        }
    }
    return antinode_counter;
}

long part2(InputType in) {
    std::cout << "running pt2\n";
    int max_x = in[0].size() - 1;
    int max_y = in.size() - 1;
    
    for (auto map_it : node_locations) {
        auto locations = map_it.second;
        for (auto coord1 : locations) {
            for (auto coord2 : locations) {
                if (coord1 == coord2) continue;
                int y_diff = coord1.first - coord2.first;
                int x_diff = coord1.second - coord2.second;
                int new_y = coord1.first + y_diff;
                int new_x = coord1.second + x_diff;
                in[coord1.first][coord1.second] = "#";
                while (withinBounds(max_x, max_y, new_y, new_x)) {
                    in[new_y][new_x] = "#";
                    new_y = new_y + y_diff;
                    new_x = new_x + x_diff;
                }
            }
        }
    }

    long antinode_counter = 0;
    for (auto line : in) {
        for (auto node : line) {
            if (node == "#") antinode_counter++;
        }
    }
    return antinode_counter;
}

int main(int argc, char* argv[]) {
  ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2024/inputs/2024-day8.txt");
  // ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/tmp.txt");
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  InputType input = {};
  string tmp = "";

  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp == "") {
      continue;
    }
    input.push_back(absl::StrSplit(tmp, ""));
  }

  for (auto line: input) {
      for (auto item : line) {
          std::cout << item;
      }
      std::cout << "\n";
  }

  // map of node to all location coordinates
  for (int i = 0; i < input.size(); i++) {
      for (int j = 0; j < input[0].size(); j++) {
          auto cur = input[i][j];
          if (cur == ".") continue;
          if (node_locations.find(cur) == node_locations.end()) {
              node_locations[cur] = vector<std::pair<int, int>>();
          }
          node_locations[cur].emplace_back(i, j);
      }
  }
  // print map
  for (auto map_it : node_locations) {
      cout << map_it.first << " -- ";
      for (auto pair: map_it.second) {
          cout << pair.first << ", " << pair.second << "; ";
      }
      cout << "\n";
  }
    

  printf("answer to part 1: %ld\n", part1(input));
  printf("answer to part 2: %ld\n", part2(input));
  return 0;
}
