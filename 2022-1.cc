#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>

using std::cerr;
using std::string;

int get_max_set(std::istream& input) {
  int max = 0;
  string tmp = "";
  int tmp_max = 0;
  while (!input.eof()) {
    std::getline(input, tmp);
    if (tmp != "") {
      tmp_max += atoi(tmp.c_str());
    } else {
      max = tmp_max > max ? tmp_max : max;
      tmp_max = 0;
    }
  }
  return max;
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
  std::cout << "max is " << get_max_set(input);
  return 0;
}
