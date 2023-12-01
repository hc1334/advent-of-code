#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <vector>

using std::cout;
using std::string;

const int ROCK_SCORE = 1;
const int PAPER_SCORE = 2;
const int SCISSOR_SCORE = 3;

const int LOSE_SCORE = 0;
const int DRAW_SCORE = 3;
const int WIN_SCORE = 6;

// A represents opponent
const char A_ROCK = 'A';
const char A_PAPER = 'B';
const char A_SCISSOR = 'C';

// B represents you
const char B_ROCK = 'X';
const char B_PAPER = 'Y';
const char B_SCISSOR = 'Z';

// for part 2
const char LOSE_RESULT = 'X';
const char DRAW_RESULT = 'Y';
const char WIN_RESULT = 'Z';

// part 1
int get_shape_score(char b) {
  switch (b) {
    case B_ROCK:
      return ROCK_SCORE;
    case B_PAPER:
      return PAPER_SCORE;
    case B_SCISSOR:
      return SCISSOR_SCORE;
  }
  return 0;
}

int get_outcome_score(char a, char b) {
  switch (a) {
    case A_ROCK:
      switch (b) {
        case B_ROCK:
          return DRAW_SCORE;
        case B_PAPER:
          return WIN_SCORE;
        case B_SCISSOR:
          return LOSE_SCORE;
      }
    case A_PAPER:
      switch (b) {
        case B_ROCK:
          return LOSE_SCORE;
        case B_PAPER:
          return DRAW_SCORE;
        case B_SCISSOR:
          return WIN_SCORE;
      }
    case A_SCISSOR:
      switch (b) {
        case B_ROCK:
          return WIN_SCORE;
        case B_PAPER:
          return LOSE_SCORE;
        case B_SCISSOR:
          return DRAW_SCORE;
      }
  }
  return 0;
}

int get_score(const std::vector<std::pair<char, char>>& input) {
  int total_score = 0;
  for (auto& pair : input) {
    total_score += get_outcome_score(pair.first, pair.second);
    total_score += get_shape_score(pair.second);
  }
  return total_score;
}

// part 2
// TODO(helenchang): clean up huge switch blocks
int solve_pt2(char a, char result) {
  switch (a) {
    case A_ROCK:
      switch (result) {
        case WIN_RESULT:
          return WIN_SCORE + PAPER_SCORE;
        case LOSE_RESULT:
          return LOSE_SCORE + SCISSOR_SCORE;
        case DRAW_RESULT:
          return DRAW_SCORE + ROCK_SCORE;
      }
    case A_PAPER:
      switch (result) {
        case WIN_RESULT:
          return WIN_SCORE + SCISSOR_SCORE;
        case LOSE_RESULT:
          return LOSE_SCORE + ROCK_SCORE;
        case DRAW_RESULT:
          return DRAW_SCORE + PAPER_SCORE;
      }
    case A_SCISSOR:
      switch (result) {
        case WIN_RESULT:
          return WIN_SCORE + ROCK_SCORE;
        case LOSE_RESULT:
          return LOSE_SCORE + PAPER_SCORE;
        case DRAW_RESULT:
          return DRAW_SCORE + SCISSOR_SCORE;
      }
  }
  return 0;
}

int get_score2(const std::vector<std::pair<char, char>>& input) {
  int total_score = 0;
  for (auto& pair : input) {
    total_score += solve_pt2(pair.first, pair.second);
  }
  return total_score;
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
  std::vector<std::pair<char, char>> input = {};
  string tmp = "";
  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    // ooh so dangerous
    input.emplace_back(tmp[0], tmp[2]);
  }
  std::cout << "score following strategy guide is " << get_score(input) << "\n";
  std::cout << "score following strategy guide 2 is " << get_score2(input)
            << "\n";
  return 0;
}
