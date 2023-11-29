#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <vector>

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

const int MAX_SUM = 3;
int get_top_3_sum(std::istream& input) {
  std::priority_queue<int> max_pq;
  string tmp = "";
  int tmp_sum = 0;
  while (!input.eof()) {
    std::getline(input, tmp);
    if (tmp != "") {
      tmp_sum += atoi(tmp.c_str());
    } else {
      max_pq.push(tmp_sum);
      tmp_sum = 0;
    }
  }
  int max_sum = 0;
  for (int i = 0; i < MAX_SUM; i++) {
    max_sum += max_pq.top();
    max_pq.pop();
  }
  return max_sum;
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
  // input is passed by reference so can't be shared between two methods
  // std::cout << "max is " << get_max_set(input);
  std::cout << "top 3 sum is " << get_top_3_sum(input);
  return 0;
}
