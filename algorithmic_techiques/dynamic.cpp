// Dynamic programming is a very important problem solving strategy in
// competitive programming problems.
//
// In the backtracking assignment you had to work with code you didn't write.
// In this assignment you write everything yourself from the beginning.
//
// TODO: Read chapter 7 from the "Competitive Programmer’s Handbook"
// https://cses.fi/book/book.pdf --> pp. 65 - 76
// TODO: Choose one of the three following problems presented in the book:
//       - Longest increasing subsequence
//       - Paths in a grid
//       - Knapsack (all possible sums)
//       Implement for your chosen problem with dynamic programming
//       1. an iterative solution
//                and
//       2. a recursive solution
//       Test your implementations thoroughly. Start by writing your test cases
//       before you implement the algorithms.
//       Document your solutions thoroughly by writing meaningful comments.

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>

using namespace std;

// Paths in a grid
class Grid {
   protected:
    uint32_t m_width, m_height;
    // data is the original grid and sum hold the already computed sums of the original grid
    uint32_t *m_data, *m_sum;

   public:
    Grid(uint32_t i_width, uint32_t i_height, uint32_t *i_data) {
        m_data = i_data;
        m_width = i_width;
        m_height = i_height;

        // initialize sums as 0
        m_sum = new uint32_t[i_width * i_height];
        for (uint32_t i = 0; i < i_width * i_height; i++) {
            m_sum[i] = 0;
        }
    }

    ~Grid() {
        delete[] m_data;
        delete[] m_sum;
    }

    // get value of the original grid at a givin position
    uint32_t value(uint32_t i_x, uint32_t i_y) {
        if (i_x < m_width && i_y < m_height) {
            return m_data[i_y * m_width + i_x];
        } else {
            cerr << "Point with coordinates: (" << i_x << ", " << i_y << ") does not exist in width: " << m_width << ", height: " << m_height << ", in value" << endl;
            return 0;
        }
    }

    // get value of the sum array at a givin position
    uint32_t sum_value(uint32_t i_x, uint32_t i_y) {
        if (i_x < m_width && i_y < m_height) {
            return m_sum[i_y * m_width + i_x];
        } else {
            cerr << "Point with coordinates: (" << i_x << ", " << i_y << ") does not exist in width: " << m_width << ", height: " << m_height << ", in sum_value" << endl;
            return 0;
        }
    }

    // put sum into the sum array into a certain position
    void put_sum(uint32_t i_x, uint32_t i_y, uint32_t i_sum) {
        if (i_x < m_width && i_y < m_height) {
            if (m_sum[i_y * m_width + i_x] < i_sum) {
                m_sum[i_y * m_width + i_x] = i_sum;
            }
        } else {
            cerr << "Point with coordinates: (" << i_x << ", " << i_y << ") does not exist in width: " << m_width << ", height: " << m_height << ", in pu_sum" << endl;
        }
    }

    // print a grid
    void print(int mode = 0) {
        uint32_t *ptr;
        switch (mode) {
            case 0:
                ptr = m_data;
                break;
            case 1:
                ptr = m_sum;
                break;
            default:
                cerr << "invalid mode was entered" << endl;
                break;
        }

        cout << endl;
        for (uint32_t i = 0; i < m_height; i++) {
            for (uint32_t j = 0; j < m_width; j++) {
                int idx = i * m_width + j;
                cout << ptr[idx] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    virtual uint32_t sum(uint32_t, uint32_t) { return 0; }
};

class RecursiveGrid : public Grid {
   public:
    RecursiveGrid(uint32_t i_width, uint32_t i_height, uint32_t *i_data) : Grid(i_width, i_height, i_data) {
        // fill the sum array
        for (uint32_t i = 0; i < i_height; i++) {
            for (uint32_t j = 0; j < i_width; j++) {
                put_sum(j, i, sum(j, i));
            }
        }
    }

    uint32_t sum(uint32_t i_x, uint32_t i_y) {
        if (sum_value(i_x, i_y) == 0) {
            uint32_t l_sum;
            if (i_x == 0 && i_y == 0) {
                // if we look at the upper left element, just return the value
                l_sum = value(i_x, i_y);
            } else if (i_x == 0) {
                // if we reached the left border, return the sum of the element above
                l_sum = sum(0, i_y - 1) + value(i_x, i_y);
            } else if (i_y == 0) {
                // if we reached the upper border, return the sum of the element left to us
                l_sum = sum(i_x - 1, 0) + value(i_x, i_y);
            } else {
                // return the max sum of the upper or left neighbor
                l_sum = max(sum(i_x - 1, i_y), sum(i_x, i_y - 1)) + value(i_x, i_y);
            }
            return l_sum;
        } else {
            // if sum is already known, return it
            return sum_value(i_x, i_y);
        }
    }
};

class IterativeGrid : public Grid {
   public:
    IterativeGrid(uint32_t i_width, uint32_t i_height, uint32_t *i_data) : Grid(i_width, i_height, i_data) {
        // fill the sum array
        for (uint32_t i = 0; i < i_height; i++) {
            for (uint32_t j = 0; j < i_width; j++) {
                put_sum(j, i, sum(j, i));
            }
        }
    }

    uint32_t sum(uint32_t i_x, uint32_t i_y) {
        if (sum_value(i_x, i_y) == 0) {
            uint32_t x = 0;
            uint32_t y = 0;
            uint32_t l_sum = value(x, y);
            while (x < i_x || y < i_y) {
                if (x < i_x && y < i_y) {
                    // if both right and lower neighbor exist add the bigger one of them
                    if (value(x + 1, y) > value(x, y + 1)) {
                        x++;
                    } else {
                        y++;
                    }
                } else if (x < i_x) {
                    // if only right neighbor, add its value
                    x++;
                } else {
                    // if only lower neighbor, add its value
                    y++;
                }
                l_sum += value(x, y);
            }

            // if the sum of left or upper neighbor of last element in queried square exists and is bigger than what we have got take its sum
            if (i_x > 0) {
                if (sum_value(i_x - 1, i_y) > l_sum) {
                    l_sum = sum_value(i_x - 1, i_y) + value(i_x, i_y);
                }
            }

            if (i_y > 0) {
                if (sum_value(i_x, i_y - 1) > l_sum) {
                    l_sum = sum_value(i_x, i_y - 1) + value(i_x, i_y);
                }
            }

            return l_sum;
        } else {
            return sum_value(i_x, i_y);
        }
    }
};

int main() {
    {
        uint32_t width = 1;
        uint32_t height = 1;
        uint32_t *data = new uint32_t[width * height];

        uint32_t values[1] = {1};

        for (uint32_t i = 0; i < width * height; i++) {
            data[i] = values[i];
        }

        RecursiveGrid rg(width, height, data);
        uint32_t rec_sum = rg.sum(width - 1, height - 1);
        assert(rec_sum == 1);

        IterativeGrid ig(width, height, data);
        uint32_t it_sum = ig.sum(width - 1, height - 1);
        assert(it_sum == 1);
    }
    {
        uint32_t width = 2;
        uint32_t height = 2;
        uint32_t *data = new uint32_t[width * height];

        uint32_t values[4] = {1, 8,
                              4, 7};

        for (uint32_t i = 0; i < width * height; i++) {
            data[i] = values[i];
        }

        RecursiveGrid rg(width, height, data);
        uint32_t rec_sum = rg.sum(width - 1, height - 1);
        assert(rec_sum == 16);

        IterativeGrid ig(width, height, data);
        uint32_t it_sum = ig.sum(width - 1, height - 1);
        assert(it_sum == 16);
    }
    {
        uint32_t width = 2;
        uint32_t height = 3;
        uint32_t *data = new uint32_t[width * height];

        uint32_t values[6] = {1, 8,
                              9, 4,
                              3, 1};

        for (uint32_t i = 0; i < width * height; i++) {
            data[i] = values[i];
        }

        RecursiveGrid rg(width, height, data);
        uint32_t rec_sum = rg.sum(width - 1, height - 1);
        assert(rec_sum == 15);

        IterativeGrid ig(width, height, data);
        uint32_t it_sum = ig.sum(width - 1, height - 1);
        assert(it_sum == 15);
    }
    {
        uint32_t width = 5;
        uint32_t height = 5;
        uint32_t *data = new uint32_t[width * height];

        uint32_t values[25] = {3, 7, 9, 2, 7,
                               9, 8, 3, 5, 5,
                               1, 7, 9, 8, 5,
                               3, 8, 6, 4, 10,
                               50, 3, 9, 7, 8};

        for (uint32_t i = 0; i < width * height; i++) {
            data[i] = values[i];
        }

        RecursiveGrid rg(width, height, data);
        uint32_t rec_sum = rg.sum(width - 1, height - 1);
        assert(rec_sum == 93);

        IterativeGrid ig(width, height, data);
        uint32_t it_sum = ig.sum(width - 1, height - 1);
        assert(it_sum == 93);
    }
    {
        uint32_t width = 5;
        uint32_t height = 5;
        uint32_t *data = new uint32_t[width * height];

        uint32_t values[25] = {3, 7, 9, 2, 7,
                               9, 8, 3, 5, 5,
                               1, 7, 9, 8, 5,
                               3, 8, 6, 4, 10,
                               6, 3, 9, 7, 8};

        for (uint32_t i = 0; i < width * height; i++) {
            data[i] = values[i];
        }

        RecursiveGrid rg(width, height, data);
        uint32_t rec_sum = rg.sum(width - 1, height - 1);
        assert(rec_sum == 67);

        IterativeGrid ig(width, height, data);
        uint32_t it_sum = ig.sum(width - 1, height - 1);
        assert(it_sum == 67);
    }
    cout << "all tests passed" << endl;
}
