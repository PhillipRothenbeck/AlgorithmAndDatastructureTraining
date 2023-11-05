// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// helper macros for timings
#define TIMERSTART(label)                                                      \
  std::chrono::time_point<std::chrono::system_clock> a##label, b##label;       \
  a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                                       \
  b##label = std::chrono::system_clock::now();                                 \
  std::chrono::duration<double> delta##label = b##label - a##label;            \
  std::cout << #label << ": " << std::setprecision(4) << delta##label.count()  \
            << " seconds" << std::endl;

// parse input file and create baskets vector
vector<set<string>> get_baskets(const string &file_name) {
  ifstream ifs(file_name);
  if (ifs.fail()) {
    cerr << "failed to open " << file_name << endl;
    exit(-1);
  }
  string line;
  string word;
  vector<set<string>> baskets;
  while (getline(ifs, line)) {
    stringstream iss(line);
    set<string> basket;
    while (iss >> word)
      basket.insert(word);
    baskets.push_back(basket);
  }
  return baskets;
}

// count the common items between two sets of words
size_t intersection_count(const set<string> &b1, const set<string> &b2) {
  vector<string> v;
  set_intersection(begin(b1), end(b1), begin(b2), end(b2),
                   std::back_inserter(v));
  return v.size();
}

/************** begin assignment **************/
// The "vector baskets" contains 5000 baskets of fruits, for example baskets[5]
// contains the following fruits {Coconut, Watermelon, Apricot}.
// The "vector preferences" contains preferences for fruits of 1000 people, for
// example the person in preferences[2] prefers {Strawberry, Melon, Avocado,
// Jackfruit}. Count the baskets for each person that have at least 3 fruits of
// a person's preferences. A basket can contain 3 to 7 different (unique)
// fruits. Also the preferences of the persons are between 3 to 7 different
// (unique) fruits. There are only 28 different fruits.

// A naive solution uses sets of strings to compute intersections between
// baskets and preferences.
// It also iterates over all baskets for each user.
vector<size_t> count_matches_naive(const vector<set<string>> &baskets,
                                   const vector<set<string>> &preferences) {
  // matches_count contains the matches count for each person
  vector<size_t> matches_count(
      preferences.size()); // create vector of all zeros
  // iterate over all persons
  for (size_t i = 0; i < preferences.size(); ++i) {
    // iterate over all possible baskets
    for (const auto &basket : baskets) {
      // if a basket contains at least 3 fruits of a person's preferences, then
      // we have a match
      if (intersection_count(preferences[i], basket) >= 3) {
        matches_count[i]++;
      }
    }
  }
  return matches_count;
}

// TODO: implement a "fast matches counter" using bit operations
// Voluntary (not required): If you are really interested in speeding up the
// code, also develop a strategy to avoid iterating over all the baskets each
// time. (In a real speed competition this would be essential for winning!)

std::bitset<28> get_bitset(std::set<string> set, std::map<std::string, unsigned int> &map) {
  /**
   * Generate a bitset for a given set.
   * 
   * @param set to be convertet to bitset
   * @param map used as a guideline to map each element of a set to a bit digit
  */
    // define the return bitset and get the number of already known fruits
    std::bitset<28> b_set = 0;
    unsigned int found_fruits = map.size();

    // for each fruit get the mapped binary digit and flip the bit
    for(std::set<std::string>::iterator itr = set.begin(); itr != set.end(); itr++) {
      auto map_itr = map.find(*itr);

      // if fruit is not known add it to the map
      if (map_itr == map.end()) {
        map[*itr] = found_fruits++;
      }
      unsigned int  binary_digit = (*map.find(*itr)).second;
      b_set[binary_digit].flip();
    }

    return b_set;
}

vector<size_t> count_matches_fast(const vector<std::set<std::string>> &baskets,
                                  const vector<std::set<std::string>> &preferences) {
  std::map<std::string, unsigned int> fruit_map;
  vector<size_t> matches_count(preferences.size());
  vector<std::bitset<28>> bitset_baskets(baskets.size());

  // convert all baskets to bitsets
  for (int i = 0; i < baskets.size(); i++) {
    bitset_baskets[i] = get_bitset(baskets[i], fruit_map);
  }
  
  for (size_t i = 0; i < preferences.size(); ++i) {
    // convert preference to bitset
    std::bitset<28> preference_set = get_bitset(preferences[i], fruit_map);
    for (const auto &basket : bitset_baskets) {
      // calculate matches
      std::bitset<28> matches = preference_set & basket;
      if (matches.count() >= 3) {
        matches_count[i]++;
      }
    }
  }
  return matches_count;
}
/*************** end assignment ***************/

int main() {
  vector<set<string>> baskets = get_baskets("baskets.txt");
  vector<set<string>> preferences = get_baskets("preferences.txt");

  TIMERSTART(naive)
  auto results_naive = count_matches_naive(baskets, preferences);
  TIMERSTOP(naive)

  TIMERSTART(fast)
  auto results_fast = count_matches_fast(baskets, preferences);
  TIMERSTOP(fast)

  assert(results_naive == results_fast);
  
  cout << "all tests passed" << endl;
}
