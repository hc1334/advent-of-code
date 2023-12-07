#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "absl/strings/str_split.h"

using std::string;
using std::vector;

struct Game {
  long time;
  long distance;
};

int part1(const vector<Game> games) {
  int wins_product = 1;
  for (const auto game : games) {
    int wins = 0;
    for (long sec = 1; sec < game.time; sec++) {
      if (game.distance < sec * (game.time - sec)) {
        wins++;
      } else if (wins != 0) {
        break;
      }
    }
    wins_product *= wins;
  }
  return wins_product;
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

  // TIME
  std::getline(input_stream, tmp, ':');
  std::getline(input_stream, tmp);
  vector<string> times = absl::StrSplit(tmp, " ", absl::SkipEmpty());

  // DISTANCE
  std::getline(input_stream, tmp, ':');
  std::getline(input_stream, tmp);
  vector<string> distances = absl::StrSplit(tmp, " ", absl::SkipEmpty());

  vector<Game> games1 = {};
  vector<Game> games2 = {};
  string games2_time = "";
  string games2_distance = "";
  for (int i = 0; i < times.size(); i++) {
    games1.emplace_back(Game{stol(times[i]), stol(distances[i])});
    games2_time += times[i];
    games2_distance += distances[i];
  }
  games2.emplace_back(Game{stol(games2_time), stol(games2_distance)});

  printf("answer to part 1: %d\n", part1(games1));
  printf("answer to part 2: %d\n", part1(games2));
  return 0;
}
