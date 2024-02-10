#include <cassert>
#include <iostream>

using namespace std;

int solve(int n) {
    bool under_n = true;
    int i = 1;
    int sum = 0;
    // run loop until i * 3 and i * 5 is larger than n
    while (under_n) {
        if (i * 3 < n) {
            sum += i * 3;
        }
        if (i * 5 < n) {
            // prune out all multiples of 5 and 3 that already added as an multiple of 3
            sum += (i * 5) * ((i * 5) % 3 != 0);
        }
        if (i * 3 > n & i * 5 > n) {
            under_n = false;
        }
        i++;
    }
    return sum;
}

int main() {
    int sum = solve(10);
    assert(sum == 23);
    sum = solve(1000);
    assert(sum == 233168);
    cout << "all test passed" << endl;
}