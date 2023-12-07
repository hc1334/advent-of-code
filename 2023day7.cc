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
using std::vector;

struct Hand {
  vector<string> cards;
  int bid;
};

enum HandType {
  FIVE_A_KIND,
  FOUR_A_KIND,
  FULL_HOUSE,
  THREE_A_KIND,
  TWO_PAIR,
  ONE_PAIR,
  HIGH_CARD,
};

HandType GetHandType2(const Hand& hand) {
  std::map<string, int> card_to_count = {};
  for (auto card : hand.cards) {
    card_to_count[card] = card_to_count[card] + 1;
  }
  int pair_count = 0;
  int three_count = 0;
  int j_count = card_to_count["J"];
  card_to_count["J"] = 0;
  for (auto pair : card_to_count) {
    if (pair.second + j_count == 5) {
      return HandType::FIVE_A_KIND;
    }
    if (pair.second + j_count == 4) {
      return HandType::FOUR_A_KIND;
    }
    if (pair.first == "J") continue;
    if (pair.second == 3) {
      three_count++;
    }
    if (pair.second == 2) {
      pair_count++;
    }
  }
  if ((three_count && pair_count) || (pair_count == 2 && j_count) ||
      (pair_count && j_count == 2)) {
    return HandType::FULL_HOUSE;
  }
  if (three_count || (pair_count >= 1 && j_count >= 1) || j_count == 2) {
    return HandType::THREE_A_KIND;
  }
  if (pair_count == 2 || j_count == 2 || (pair_count && j_count)) {
    return HandType::TWO_PAIR;
  }
  if (pair_count || j_count) {
    return HandType::ONE_PAIR;
  }
  return HandType::HIGH_CARD;
}

HandType GetHandType(const Hand& hand) {
  std::map<string, int> card_to_count = {};
  for (auto card : hand.cards) {
    card_to_count[card] = card_to_count[card] + 1;
  }
  int pair_count = 0;
  int three_count = 0;
  for (auto pair : card_to_count) {
    if (pair.second == 5) {
      return HandType::FIVE_A_KIND;
    }
    if (pair.second == 4) {
      return HandType::FOUR_A_KIND;
    }
    if (pair.second == 3) {
      three_count++;
    }
    if (pair.second == 2) {
      pair_count++;
    }
  }
  if (three_count && pair_count) {
    return HandType::FULL_HOUSE;
  }
  if (three_count) {
    return HandType::THREE_A_KIND;
  }
  if (pair_count == 2) {
    return HandType::TWO_PAIR;
  }
  if (pair_count) {
    return HandType::ONE_PAIR;
  }
  return HandType::HIGH_CARD;
}

std::map<string, int> card_to_value = {
    {"1", 1}, {"2", 2}, {"3", 3},  {"4", 4},  {"5", 5},  {"6", 6},  {"7", 7},
    {"8", 8}, {"9", 9}, {"T", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14},
};

std::map<string, int> card_to_value2 = {
    {"1", 1}, {"2", 2}, {"3", 3},  {"4", 4}, {"5", 5},  {"6", 6},  {"7", 7},
    {"8", 8}, {"9", 9}, {"T", 10}, {"J", 0}, {"Q", 12}, {"K", 13}, {"A", 14},
};

// only compares same hand types. returns true if h1 > h2
bool IsSameTypeHandBetter(const Hand& h1, const Hand& h2,
                          std::map<string, int>& card_to_value) {
  for (int i = 0; i < h1.cards.size(); i++) {
    auto card1 = h1.cards[i];
    auto card2 = h2.cards[i];
    if (card1 == card2) {
      continue;
    }
    return card_to_value[card1] < card_to_value[card2];
  }
  // both equal, doesn't matter what we return.
  return false;
}

struct hand_comparator {
  inline bool operator()(const Hand& h1, const Hand& h2) {
    HandType type1 = GetHandType(h1);
    HandType type2 = GetHandType(h2);

    if (type1 != type2) {
      return type1 > type2;
    }
    return IsSameTypeHandBetter(h1, h2, card_to_value);
  }
};

struct hand_comparator2 {
  inline bool operator()(const Hand& h1, const Hand& h2) {
    HandType type1 = GetHandType2(h1);
    HandType type2 = GetHandType2(h2);

    if (type1 != type2) {
      return type1 > type2;
    }
    return IsSameTypeHandBetter(h1, h2, card_to_value2);
  }
};

int part1(vector<Hand>& hands) {
  std::sort(hands.begin(), hands.end(), hand_comparator());
  int sum = 0;
  for (int i = 0; i < hands.size(); i++) {
    auto hand = hands[i];

    sum += hand.bid * (i + 1);
  }
  return sum;
}

int part2(vector<Hand>& hands) {
  std::sort(hands.begin(), hands.end(), hand_comparator2());
  int sum = 0;
  cout << "sorted \n";
  for (int i = 0; i < hands.size(); i++) {
    auto hand = hands[i];

    cout << "\n";
    for (auto card : hand.cards) {
      cout << card;
    }

    sum += hand.bid * (i + 1);
  }
  return sum;
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

  vector<Hand> hands = {};
  string tmp = "";
  while (!input_stream.eof()) {
    // 32T3K 765
    std::getline(input_stream, tmp);
    if (tmp.empty()) continue;
    vector<string> split = absl::StrSplit(tmp, " ");
    hands.emplace_back(
        Hand{absl::StrSplit(split[0], "", absl::SkipEmpty()), stoi(split[1])});
  }

  printf("answer to part 1: %d\n", part1(hands));
  printf("answer to part 2: %d\n", part2(hands));
  return 0;
}

