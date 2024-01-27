#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    uint32_t i, j, z;
    unordered_map<uint32_t, uint32_t> hash_map;
    while (cin >> i >> j) {
        z = 0;
        for (uint32_t idx = i; idx <= j; idx++) {
            uint32_t count = 1;  // every number is counted
            uint32_t n = idx;
            while (n != 1) {
                if (hash_map.find(n) == hash_map.end()) {
                    // if n was not yet calculated, then follow the original algorithm
                    if (n % 2 == 1) {
                        n = 3 * n + 1;
                    } else {
                        n = (uint32_t)(n / 2);
                    }
                    count++;  // another cycle done
                } else {
                    // if n was already calculated, then take that (value - 1) and add it to the current count -> finish
                    count += hash_map.at(n);
                    n = 1;
                }
            }
            // add to the already calculated counts
            if (hash_map.find(idx) == hash_map.end()) {
                hash_map.insert(make_pair(idx, count - 1));
            }
            z = max(count, z);
        }
        cout << i << " " << j << " " << z << endl;
    }
}