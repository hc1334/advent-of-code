#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "absl/strings/str_split.h"

using std::cout;
using std::map;
using std::string;
using std::vector;

const int DEST_INDEX = 0;
const int SOURCE_INDEX = 1;
const int RANGE_INDEX = 2;

const int SEED_TO_SOIL = 0;
const int SOIL_TO_FERT = 1;
const int FERT_TO_WATER = 2;
const int WATER_TO_LIGHT = 3;
const int LIGHT_TO_TEMP = 4;
const int TEMP_TO_HUMIDITY = 5;
const int HUMIDITY_TO_LOC = 6;

struct Range {
  long start;
  long end;
  long add;
};

std::vector<long> seeds = {};
std::vector<Range> seeds_as_range = {};

vector<vector<Range>> ranges = {{{}}, {{}}, {{}}, {{}}, {{}}, {{}}, {{}}};
vector<vector<Range>> reverse_ranges = {{{}}, {{}}, {{}}, {{}},
                                        {{}}, {{}}, {{}}};

std::vector<long> string_to_int(const vector<string> in) {
  std::vector<long> out = {};
  for (auto i : in) {
    out.push_back(stol(i));
  }
  return out;
}

long get_corresponding(vector<Range> ranges, long key) {
  for (auto range : ranges) {
    if (key >= range.start && key < range.end) {
      return key + range.add;
    }
  }
  return key;
}

bool seed_in_range(const vector<Range>& ranges, long seed) {
  for (auto range : ranges) {
    if (seed >= range.start && seed < range.end) {
      return true;
    }
  }
  return false;
}

// this is not optimized and takes some time.
long part2() {
  long location = 0;
  long stop_location = 324724204; // answer to pt 1
  while (location != stop_location ) {
    long humidity = get_corresponding(reverse_ranges[HUMIDITY_TO_LOC], location);
    long temp = get_corresponding(    reverse_ranges[TEMP_TO_HUMIDITY], humidity);
    long light = get_corresponding(   reverse_ranges[LIGHT_TO_TEMP], temp);
    long water = get_corresponding(   reverse_ranges[WATER_TO_LIGHT], light);
    long fert = get_corresponding(    reverse_ranges[FERT_TO_WATER], water);
    long soil = get_corresponding(    reverse_ranges[SOIL_TO_FERT], fert);
    long seed = get_corresponding(    reverse_ranges[SEED_TO_SOIL], soil);
    if (seed_in_range(seeds_as_range, seed)) {
      printf(
          "seed %ld, soil %ld, fert %ld, water %ld, light %ld, temp %ld, "
          "humidity %ld,"
          "location %ld\n",
          seed, soil, fert, water, light, temp, humidity, location);
      return location;
    }
    location++;
  }
}

long part1() {
  int min_location = INT_MAX;
  for (long seed : seeds) {
    long soil = get_corresponding(ranges[SEED_TO_SOIL], seed);
    long fert = get_corresponding(ranges[SOIL_TO_FERT], soil);
    long water = get_corresponding(ranges[FERT_TO_WATER], fert);
    long light = get_corresponding(ranges[WATER_TO_LIGHT], water);
    long temp = get_corresponding(ranges[LIGHT_TO_TEMP], light);
    long humidity = get_corresponding(ranges[TEMP_TO_HUMIDITY], temp);
    long location = get_corresponding(ranges[HUMIDITY_TO_LOC], humidity);
    // printf(
    //     "seed %ld, soil %ld, fert %ld, water %ld, light %ld, temp %ld, "
    //     "humidity %ld,"
    //     "location %ld\n",
    //     seed, soil, fert, water, light, temp, humidity, location);
    min_location = location < min_location ? location : min_location;
  }
  return min_location;
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
  std::getline(input_stream, tmp, ':');
  std::getline(input_stream, tmp);
  std::vector<string> seeds_as_string(
      absl::StrSplit(tmp, " ", absl::SkipEmpty()));
  seeds = string_to_int(seeds_as_string);
  for (int i = 0; i < seeds.size(); i = i + 2) {
    seeds_as_range.emplace_back(Range{seeds[i], seeds[i] + seeds[i + 1], 0});
  }

  int map_idx = -1;
  while (!input_stream.eof()) {
    std::getline(input_stream, tmp);
    if (tmp.empty()) continue;
    if (absl::StrContains(tmp, ":")) {
      map_idx++;
      continue;
    }
    auto input_vec = string_to_int(absl::StrSplit(tmp, " ", absl::SkipEmpty()));
    long source_start = input_vec[SOURCE_INDEX];
    long dest_start = input_vec[DEST_INDEX];

    ranges[map_idx].emplace_back(Range{source_start,
                                       input_vec[RANGE_INDEX] + source_start,
                                       dest_start - source_start});
    reverse_ranges[map_idx].emplace_back(
        Range{dest_start, input_vec[RANGE_INDEX] + dest_start,
              source_start - dest_start});
  }
  printf("answer to part 1: %ld\n", part1());
  printf("answer to part 2: %ld\n", part2());
  return 0;
}
