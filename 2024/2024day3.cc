#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>

using std::string;
using std::ifstream;

int main(int argc, char* argv[]) {
  ifstream input_stream("/Users/helenchang/Code/advent-of-code/advent-of-code/2024/inputs/2023-day3pt1-pairs.txt");
  if (!input_stream.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  int result = 0;
  string tmp = "";

  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp == "") {
      continue;
    }
    int first = atoi(tmp.c_str());
    std::getline(input_stream, tmp);
    result += first * atoi(tmp.c_str());
  }
  std::cout << result;
  return 0;
}
