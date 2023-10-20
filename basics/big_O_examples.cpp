#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Big O runtime examples

/*** Example 1: What is the runtime of the below code? ***/
void foo(const vector<int> &vec) {
  int sum = 0;
  int product = 1;
  for (int num : vec) {
    sum += num;
  }
  for (int num : vec) {
    product *= num;
  }
  cout << sum << ", " << product;
}
// This will take O(n) time.
// The fact that we iterate through the vector twice doesn't matter.

/*** Example 2: What is the runtime of the below code? ***/
void print_pairs(const vector<int> &vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    for (size_t j = 0; j < vec.size(); j++) {
      cout << "(" << vec[i] << ", " << vec[j] << ") ";
    }
  }
}
// The inner for loop has O(n) iterations and it is called N times.
// Therefore, the runtime is O(n^2).

/*** Example 3: What is the runtime of the below code? ***/
// This is very similar code to the above example,
// but now the inner for loop starts at i + 1.
void print_unordered_pairs(const vector<int> &vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    for (size_t j = i + 1; j < vec.size(); j++) {
      cout << "(" << vec[i] << ", " << vec[j] << ") ";
    }
  }
}
// The first time through j runs for n-1 steps.
// The second time, it's n-2 steps. Then n-3 steps. And so on.
// Therefore, the number of steps total is: (n-1) + (n-2) + (n-3) + ... + 2 + 1.
// The sum of 1 through n-1 is n*(n-1)/2 so the runtime is O(n^2).

/*** Example 4: What is the runtime of the below code? ***/
// This is similar to example 2, but now we have two different vectors.
void print_unordered_pairs(const vector<int> &vecA, const vector<int> &vecB) {
  for (int numA : vecA) {
    for (int numB : vecB) {
      cout << "(" << numA << ", " << numB << ") ";
    }
  }
}
// For each element of vector A, the inner for loop goes through b
// iterations, where b = vecB.size().
// If a = vecA.size(), then the runtime is O(a * b).

/*** Example 5: What is the runtime of the below code? ***/
void print_unordered_pairs_multiple(const vector<int> &vecA,
                                    const vector<int> &vecB) {
  for (int numA : vecA) {
    for (int numB : vecB) {
      for (int i = 0; i < 10; ++i) {
        cout << "(" << numA << ", " << numB << ") ";
      }
    }
  }
}
// Nothing has really changed here. 10 units of work is still constant,
// so the runtime is 0(a * b).

/*** Example 6: What is the runtime of the below code? ***/
// The following code reverses a vector
void reverse(vector<int> &vec) {
  for (size_t i = 0; i < vec.size() / 2; ++i) {
    size_t other = vec.size() - i - 1;
    int temp = vec[i];
    vec[i] = vec[other];
    vec[other] = temp;
  }
}
// This algorithm runs in O(n) time.
// The fact that it only goes through half of the vector (in terms of
// iterations) does not impact the big O time.

/*** Example 7: What is the runtime of the below code? ***/
// The following method checks if a number is prime
// by checking for divisibility on numbers less than it.
// It only needs to go up to the square root of n because
// if n is divisible by a number greater than its square root then
// it's divisible by something smaller than it.
//
// For example, while 33 is divisible by 11 (which is greater than the square
// root of 33), the "counterpart" to 11 is 3 (3 * 11 = 33). 33 will have already
// been eliminated as a prime number by 3.
bool is_prime(const uint64_t n) {
  for (uint64_t x = 2; x * x <= n; ++x) {
    if (n % x == 0) {
      return false;
    }
  }
  return n > 1;
}
// The work inside the for loop is constant. Therefore, we just need to know how
// many iterations the for loop goes through in the worst case.
// The for loop will start when x = 2 and end when x*x = n. Or, in other words,
// it stops when x = sqrt(n) (when x equals the square root of n).
// This runs in O(sqrt(n)) time. Same as O(n^0.5).

/*** Example 8: What is the runtime of the below code? ***/
// The following code computes n! (n factorial).
uint64_t factorial(uint64_t n) {
  if (n == 0) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}
// This is just a straight recursion from n to n-1 to n-2 down to 1.
// It will take O(n) time.

/*** Example 9: What is the runtime of the below code? ***/
// The following code prints all Fibonacci numbers from O to n.
// It stores (i.e., caches) previously computed values in an vector.
uint64_t fib(uint64_t n, vector<uint64_t> &memo) {
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  else if (memo[n] != 0) // if we already computed the value at n
    return memo[n];
  memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
  return memo[n];
}
void all_fib(uint64_t n) {
  vector<uint64_t> memo(n); // vector contains only zeros
  for (uint64_t i = 0; i < n; i++) {
    cout << fib(i, memo) << " ";
  }
}
// At each call to fib(i), we have already computed and stored the values for
// fib(i-1) and fib(i-2). We just look up those values, sum them, store the new
// result, and return. This takes a constant amount of time.
// We're doing a constant amount of work n times, so this is O(n) time.
// This technique, called memoization, is a very common one to optimize
// exponential time recursive algorithms.

/*** Example 10: What is the runtime of the below code? ***/
// The following function prints the powers of 2 from 1 through n (inclusive).
// For example, if n is 4, it would print 1, 2, and 4. What is its runtime?
uint64_t powers_of_2(uint64_t n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    cout << 1 << " ";
    return 1;
  } else {
    uint64_t prev = powers_of_2(n / 2);
    uint64_t curr = prev * 2;
    cout << curr << " ";
    return curr;
  }
}
// Each call to powers_of_2 results in exactly one number being printed and
// returned. So if the algorithm prints 13 values at the end, then powers_of_2
// was called 13 times.
//
// In this case, we are told that it prints all the powers of 2 between 1 and n.
// Therefore, the number of times the function is called (which will be its
// runtime) must equal the number of powers of 2 between 1 and n.
//
// There are log n powers of 2 between 1 and n. Therefore, the runtime
// is 0(log n).

/*** Example 11: What is the runtime of the below code? ***/
// The following code computes a % b.
uint64_t mod(uint64_t a, uint64_t b) {
  if (b == 0) {
    throw overflow_error("Divide by zero exception!");
  }
  uint64_t div = a / b;
  return a - div * b;
}
// 0(1). It does a constant amount of work.

/*** Example 11: What is the runtime of the below code? ***/
// The following code computes the intersection (the number of elements in
// common) of two vectors. It assumes that neither vector has duplicates. It
// computes the intersection by sorting one vector (vector b) and then iterating
// through vector a checking (via binary search) if each value is in b.
int intersection(vector<int> &a, vector<int> &b) {
  sort(begin(b), end(b));
  int intersect = 0;
  for (int x : a) {
    if (binary_search(begin(b), end(b), x)) {
      intersect++;
    }
  }
  return intersect;
}
// O(b log b + a log b). First,we have to sort vector b, which takes O(b log b) time.
// Then, for each element in a, we do binary search in O(log b) time.
// The second part takes O(a log b) time.

int main() {
  vector<int> vecA{1, 2, 3, 4};
  vector<int> vecB{1, 2, 3};
  cout << "Example 1:\n";
  foo(vecA);
  cout << "\nExample 2:\n";
  print_pairs(vecA);
  cout << "\nExample 3:\n";
  print_unordered_pairs(vecA);
  cout << "\nExample 4:\n";
  print_unordered_pairs(vecA, vecB);
  cout << "\nExample 5:\n";
  print_unordered_pairs_multiple(vecA, vecB);
  cout << "\nExample 6:\n";
  reverse(vecA);
  for (auto num : vecA)
    cout << num << " ";
  cout << "\nExample 7:\n";
  uint64_t number = 792606555396977ull;
  cout << number << boolalpha << " is prime: " << is_prime(number);
  cout << "\nExample 8:\n";
  cout << factorial(7);
  cout << "\nExample 9:\n";
  all_fib(10);
  cout << "\nExample 10:\n";
  powers_of_2(100);
  cout << "\nExample 11:\n";
  cout << mod(24, 7);
  cout << "\nExample 12:\n";
  cout << intersection(vecA, vecB);
}
