// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

/************** begin assignment **************/
// given a smaller string s and a bigger string b, design an algorithm to count
// all permutation appearances of the shorter string within the longer string
// assumption: only the 26 characters from a to z are allowed in both strings
//
// example:
// s = abbc
// b = cbabadcbbabbcba
//     cbab
//           cbba
//              abbc
//                bcba
// answer: permutations of the shorter string s
//         appear 4 times in the longer string b

// An obvious brute force solution is to generate all permutations of s and then
// look for each in b. Since there are S! permutations, this will take O(S! * B)
// time, where S is the length of s and B is the length of b. This works, but
// it's an extraordinarily slow algorithm. It's actually worse than an
// exponential algorithm. If s has 14 characters, that's over 87 billion
// permutations. Add one more character into s and we have 15 times more
// permutations. -->  implement an algorithm that needs at most O(B * S^2) time
//
// Before you start coding: Try to find the places where the permutations appear
// on your own. Observe how you do this. This will help you to develop a decent
// algorithm quite easily.

int count_permutations(const string &s, const string &b) {
  int count = 0;
  if(s.length() > b.length() || (s.empty() || b.empty())) {
      return 0;
  }

  for(int i = 0; i < (b.length() - (s.length() - 1)); i++) {
      int letter_count = s.length();
      char *snip_it = (char*) malloc(s.length() * sizeof(char));
      for(int j = 0; j < s.length(); j++) {
          snip_it[j] = b[i + j];
      }

      for(int j = 0; j < s.length(); j++) {
          for(int k = 0; k < s.length(); k++) {
              if(s[j] == snip_it[k]) {
                  letter_count--;
                  snip_it[k] = 'A';
                  break;
              }
          }
      }
      if(letter_count == 0) {
          count++;
      }
  }
  std::cout << count << std::endl;
  // TODO: given a smaller string s and a bigger string b, design an algorithm
  //  that needs at most O(B * S^2) time to count all permutation appearances
  //  of the shorter string within the longer string

  return count;
}

/*************** end assignment ***************/

int main() {
  // longer string is not a permutation of shorter string
  assert(count_permutations("cbabadcbbabbcba", "abbc") == 0);

  assert(count_permutations("xyz", "xyz") == 1);
  assert(count_permutations("xyz", "xzy") == 1);

  // no common permutations
  assert(count_permutations("abzc", "cbabadcbbabbcba") == 0);
  assert(count_permutations("", "cbabadcbbabbcba") == 0);
  assert(count_permutations("cbabadcbbabbcba", "") == 0);

  assert(count_permutations("abbc", "cbabadcbbabbcba") == 4);
  assert(count_permutations("abbc", "cbabadcbbabbcbabaabccbabc") == 7);

  string s = "cat";
  string b =
      "ydwztctaaaatxocabnpgcircgysctattacqtklzypxzqtvmwejcbvqhgljulsopnldoifefp"
      "kjnvipxkfnamdsacaxosactbrnioabfxixseyetzackxhmuqnpjwfzesjwktacatfqlxxmqb"
      "jnaceobxyvqahrjdofrdhhciatcgaoueybnqsklwhfkzvltcaiacty";
  assert(count_permutations(s, b) == 9);

  // some longer word
  s = "Psychotomimetic";
  b = "PsychoxtomimetiPsycotomimehticcunyaschPoetcomyimtixkjnvipxkfnamdsacaxosa"
      "ctbrnioabfxixseyetzackxhmuqunyaschePocomtyimti";
  assert(count_permutations(s, b) == 3);

  cout << "all tests passed" << endl;
}
