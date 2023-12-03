#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "absl/strings/str_split.h"

using std::cout;
using std::string;

const char BLUE[] = "blue";
const char RED[] = "red";
const char GREEN[] = "green";

class Set {
 public:
  std::vector<std::pair<string, string>> pairs;
};

class Game {
 public:
  std::vector<Set> sets;
};

// part 2
int min_sum_power(std::vector<Game> games) {
  int sum_power = 0;
  for (auto& game : games) {
    int max_red = 0;
    int max_blue = 0;
    int max_green = 0;
    for (auto& set : game.sets) {
      for (auto& pair : set.pairs) {
        int count = atoi(pair.first.c_str());
        if (pair.second == BLUE) {
          max_blue = count > max_blue ? count : max_blue;
        } else if (pair.second == RED) {
          max_red = count > max_red ? count : max_red;
        } else {
          max_green = count > max_green ? count : max_green;
        }
      }
    }
    sum_power += (max_red * max_blue * max_green);
  }
  return sum_power;
}

// part 1
const int RED_TOTAL = 12;
const int GREEN_TOTAL = 13;
const int BLUE_TOTAL = 14;

bool is_set_valid(const Set& set) {
  for (auto& pair : set.pairs) {
    int count = atoi(pair.first.c_str());
    if (pair.second == BLUE) {
      if (count > BLUE_TOTAL) return false;
    } else if (pair.second == RED) {
      if (count > RED_TOTAL) return false;
    } else {
      if (count > GREEN_TOTAL) return false;
    }
  }
  return true;
}

bool is_game_valid(const Game& game) {
  for (auto& set : game.sets) {
    if (!is_set_valid(set)) return false;
  }
  return true;
}

int sum_possible(const std::vector<Game>& games) {
  int total_sum = 0;
  for (int i = 0; i < games.size(); i++) {
    if (is_game_valid(games[i])) {
      total_sum += (i + 1);
    }
  }
  return total_sum;
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

  std::vector<Game> games;
  string tmp = "";
  while (!input_stream.eof()) {
    std::getline(input_stream, tmp, ':');  // "Game [n]:"
    std::getline(input_stream, tmp);
    if (tmp.empty()) continue;
    Game game;
    std::vector<string> draws = absl::StrSplit(tmp, ";");
    for (auto draw : draws) {
      std::vector<string> pairs = absl::StrSplit(draw, ",", absl::SkipEmpty());
      Set set;
      for (auto pair : pairs) {
        std::vector<string> num_to_colour =
            absl::StrSplit(pair, " ", absl::SkipEmpty());
        set.pairs.emplace_back(num_to_colour[0], num_to_colour[1]);
      }
      game.sets.push_back(set);
    }
    games.push_back(game);
  }
  printf("answer to part 1: %d\n", sum_possible(games));
  printf("answer to part 2: %d\n", min_sum_power(games));
  return 0;
}
