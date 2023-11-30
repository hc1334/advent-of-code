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

int get_score(std::istream& input) {
  int total_score = 0;
  char a;
  char b;
  char trash;
  while (!input.eof()) {
    if (!input.get(a)) {
      break;
    }
    input.get(trash);  // space
    input.get(b);
    input.get(trash);  // new line
    total_score += get_outcome_score(a, b);
    total_score += get_shape_score(b);
  }
  return total_score;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "This program expects one parameter that is the input file to "
                 "read.\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }
  std::cout << "score following strategy guide is " << get_score(input);
  return 0;
}
