// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <cstring>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;

/************** begin assignment **************/
// People do not like reading text in which a word is used multiple times in a
// short paragraph. You are to write a program which helps identify such a
// problem.
//
// Write a program which takes as input an array and finds the indices between
// a closest pair of equal entries. For example, if s = < "all", "work", "and",
// "no", "play", "makes", "for", "no", "work", "no", "fun", "and", "no",
// "results" >, then the second and third occurrences of "no" is the closest
// pair (return index_1 = 7 and index_2 = 9).
//
// If there are multiple occurrences with the same minimum distance, return the
// first index pair found. If all words in the array are unique, return index_1
// = 0 and index_2 = 0. Look at the test cases if the instructions are unclear.
//
// Optimal: O(n) time, O(d) space, where d is the number of distinct entries in
// the array.
//
// Read here how to use unordered_map in C++.
// https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/



// struct for returning the closest pair indices
struct Nearest_Entries {
  size_t index_1;
  size_t index_2;

  // for testing your implementation (you don't need this)
  bool operator==(const Nearest_Entries &rhs) const {
    return index_1 == rhs.index_1 && index_2 == rhs.index_2;
  }
  bool operator!=(const Nearest_Entries &rhs) const { return !(rhs == *this); }
};

Nearest_Entries find_nearest_repeated(const vector<string> &words) {
  Nearest_Entries nearest_entries{0, 0};

  // TODO: write code here

  return nearest_entries;
}

/*************** end assignment ***************/

int main() {
  {
    vector<string> words;
    Nearest_Entries nearest_entries{0, 0};
    assert(find_nearest_repeated(words) == nearest_entries);
  }
  {
    vector<string> words{"cat", "dog"};
    Nearest_Entries nearest_entries{0, 0}; // all words different
    assert(find_nearest_repeated(words) == nearest_entries);
  }
  {
    vector<string> words{"cat", "cat"};
    Nearest_Entries nearest_entries{0, 1};
    assert(find_nearest_repeated(words) == nearest_entries);
  }
  {
    vector<string> words{"cat", "dog", "cat", "dog", "cat"};
    Nearest_Entries nearest_entries{0, 2}; // cat appears before dog
    assert(find_nearest_repeated(words) == nearest_entries);
  }
  {
    vector<string> words{"cat", "dog", "bird", "cow",
                         "cat", "dog", "cow",  "cat"};
    Nearest_Entries nearest_entries{3, 6}; // cow appears before cat
    assert(find_nearest_repeated(words) == nearest_entries);
  }
  {
    vector<string> words{"cat", "dog", "bird", "cow", "fox"};
    Nearest_Entries nearest_entries{0, 0}; // all words different
    assert(find_nearest_repeated(words) == nearest_entries);
  }
  {
    vector<string> words{"all",   "work", "and", "no",     "play",
                         "makes", "for",  "no",  "work",   "no",
                         "fun",   "and",  "no",  "results"};
    Nearest_Entries nearest_entries{7, 9};
    assert(find_nearest_repeated(words) == nearest_entries);
  }
  cout << "all tests passed" << endl;
}
