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

typedef std::pair<std::vector<string>, std::vector<string>> Game;
typedef std::vector<Game> Games;

bool vector_contains(const std::vector<string>& v, string x) {
  return std::find(v.begin(), v.end(), x) != v.end();
}

int get_match_count(const Game& game) {
  int winning_num_count = 0;
  for (auto mine : game.second) {
    if (vector_contains(game.first, mine)) {
      winning_num_count += 1;
    }
  }
  return winning_num_count;
}

int part2(const Games& games) {
  int card_count = 0;
  std::map<int, int> card_index_to_num = {};
  for (int i = 0; i < games.size(); i++) {
    card_index_to_num[i] = 1;
  }
  for (int i = 0; i < games.size(); i++) {
    int winning_count = get_match_count(games[i]);
    for (int j = i + 1; j <= i + winning_count; j++) {
      card_index_to_num[j] += card_index_to_num[i];
    }
    card_count += card_index_to_num[i];
  }
  return card_count;
}

int part1(const Games& games) {
  int total_points = 0;
  for (auto game : games) {
    total_points += pow(2, get_match_count(game) - 1);
  }
  return total_points;
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

  Games games = {};
  string tmp = "";
  string winning_numbers = "";
  string my_numbers = "";
  while (!input_stream.eof()) {
    // Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
    std::getline(input_stream, tmp, ':');  // strip Game:
    if (tmp.empty()) continue;
    std::getline(input_stream, winning_numbers, '|');
    std::getline(input_stream, my_numbers);
    games.emplace_back(
        std::make_pair(absl::StrSplit(winning_numbers, " ", absl::SkipEmpty()),
                       absl::StrSplit(my_numbers, " ", absl::SkipEmpty())));
  }

  printf("answer to part 1: %d\n", part1(games));
  printf("answer to part 2: %d\n", part2(games));
  return 0;
}

