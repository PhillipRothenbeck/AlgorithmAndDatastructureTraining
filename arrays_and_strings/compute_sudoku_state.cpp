// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <array>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

/************** begin assignment **************/
// Sudoku is a popular logic-based combinatorial number placement puzzle. The
// objective is to fill a 9 x 9 grid with digits subject to the constraint that
// each column, each row, and each of the nine 3 x 3 sub-grids that compose the
// grid contains unique integers.
// In case you need an introduction to Sudoku:
// https://www.learn-sudoku.com/sudoku-rules.html

// We define three different states in which a Sudoku board can be.
enum class state { invalid,
                   valid,
                   solved };
// invalid --> board violates the Sudoku rules
// valid --> board corresponds to the Sudoku rules
// solved --> the puzzle is solved

// Note that the only valid characters are "123456789" and the space ' ' meaning
// an empty field.
// Note that we do not care if a board can actually be solved, we only check if
// it violates the rules, or is valid, or is in a solved state.
// Of course a solved board is also valid, but we only return solved.

bool has_valid_chars(const string &board) {
    for (size_t i = 0; i < 81; i++) {
        if (!((board[i] > 48 && board[i] < 58) || board[i] == 32)) {
            return false;
        }
    }
    return true;
}

uint64_t pow_of_ten(uint32_t n) {
    uint64_t product = 1;
    n--;
    while (n > 0) {
        product *= 10;
        n--;
    }
    return product;
}

uint64_t get_representation(char c) {
    return (c == ' ') + (c != ' ') * pow_of_ten(c - 48);
}

// TODO: implement a function that returns the state of a Sudoku board
state compute_sudoku_state(const string &board) {
    std::cout << "Begin analyzing new sudoku" << std::endl;

    // filter out invalid sizes
    if (board.length() != 81) {
        return state::invalid;
    }

    // filter out invalid chars
    if (!has_valid_chars(board)) {
        return state::invalid;
    }

    std::bitset<9> line_set;
    line_set.reset();
    state sudoku_state = state::solved;
    size_t idx = 0;
    // check line correctness
    while (idx < 81) {
        if (board[idx] == ' ') {
            // if a ' ' appears the sudoku can't be valid anymore
            sudoku_state = state::valid;
        } else {
            // check if value has already appeared in line
            size_t value = (board[idx] - 48) - 1;
            if (line_set.test(value)) {
                return state::invalid;
            } else {
                line_set.flip(value);
            }
        }

        // at end of a line reset bitset
        if ((idx + 1) % 9 == 0) {
            line_set.reset();
        }
        idx++;
    }

    // check column correctness
    idx = 0;
    line_set.reset();
    // traverse the board column for column
    int32_t jump_pattern_column[9] = {9, 9, 9, 9, 9, 9, 9, 9, -71};
    size_t pattern_idx = 0;

    while (idx < 81) {
        if (board[idx] != ' ') {
            // check if value has already appeared in column
            size_t value = (board[idx] - 48) - 1;
            if (line_set.test(value)) {
                return state::invalid;
            } else {
                line_set.flip(value);
            }
        }
        idx += jump_pattern_column[pattern_idx++];
        if (pattern_idx >= 9) {
            pattern_idx = 0;
            line_set.reset();
        }
    }

    // check square correctness
    idx = 0;
    line_set.reset();
    // traverse board square for square
    int32_t jump_pattern_square[9] = {1, 1, 7, 1, 1, 7, 1, 1, -17};
    pattern_idx = 0;

    while (idx < 81) {
        if (board[idx] != ' ') {
            // check if value has already appeared in square
            size_t value = (board[idx] - 48) - 1;
            if (line_set.test(value)) {
                return state::invalid;
            } else {
                line_set.flip(value);
            }
        }
        idx += jump_pattern_square[pattern_idx++];
        if (pattern_idx >= 9) {
            if (idx % 9 == 0) {
                // shift square line
                idx += 18;
            }
            pattern_idx = 0;
            line_set.reset();
        }
    }

    return sudoku_state;
}
/*************** end assignment ***************/

int main() {
    {
        string board =
            "274935168"
            "198726435"
            "563814729"
            "356187294"
            "419562873"
            "782493516"
            "821349657"
            "947651382"
            "63527894";  // invalid size
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "274935168"
            "198726435"
            "563814729"
            "356187294"
            "419562873"
            "782493516"
            "821349657"
            "947651382"
            "6352789412";  // invalid size
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "   9  1 4"
            " 2  5 7  "
            "     25 6"
            "    194 5"
            " 6574391 "
            "4 1 26  8"
            " 18375 4 "
            " : 4  631"  // |:|
            " 4  6    ";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "586937124"
            "129654783"
            "734182596"
            "372819465"
            "865743912"
            "491526308"  // |0|
            "618375249"
            "257498631"
            "943261857";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "586937124"
            "129654783"
            "734182596"
            "372819465"
            "865743912"
            "4915263a8"  // |a|
            "618375249"
            "257498631"
            "943261857";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "145673829"
            "389215674"
            "762948135"
            "296157483"
            "814369752"
            "573824961"
            "957436218"
            "628591347"
            "431782596";
        assert(compute_sudoku_state(board) == state::solved);
    }
    {
        string board =
            "495287163"
            "821369547"
            "367145298"
            "179854632"
            "634972815"
            "582613974"
            "216438759"
            "953721486"
            "748596321";
        assert(compute_sudoku_state(board) == state::solved);
    }
    {
        string board =
            "145673829"
            "381215674"  // 38|1|
            "762948135"
            "296157483"
            "814369752"
            "573824961"
            "957436218"
            "628591347"
            "431782596";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "145673829"
            "38 215674"
            "762948135"
            "296157483"
            "814369752"
            "573824961"
            "957436 18"
            "628591347"
            "431782596";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            " 4    897"
            " 379   52"
            "8 27  3  "
            "9  4 7  6"
            " 8  9  3 "
            "6 3 18 49"
            "  83 192 "
            "26   4  3"
            " 142596  ";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            " 4    897"
            " 379   52"
            "8 27  3  "
            "9  6 7  6"  // 9  |6|
            " 8  9  3 "
            "6 3 18 49"
            "  83 192 "
            "26   4  3"
            " 142596  ";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            " 4    897"
            " 379   52"
            "8 27  3  "
            "9  4 7  6"
            " 8  9  3 "
            "6 3 18 49"
            "  83 193 "  //   83 19|3|
            "26   4  3"
            " 142596  ";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "   9  1 4"
            " 2  5 7  "
            "     25 6"
            "    194 5"
            " 6574391 "
            "4 1 26  8"
            " 18375 4 "
            "   4  631"
            " 4  6    ";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            "2  9  1 4"  // |2|
            " 2  5 7  "
            "     25 6"
            "    194 5"
            " 6574391 "
            "4 1 26  8"
            " 18375 4 "
            "   4  631"
            " 4  6    ";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "         "
            "         "
            "         "
            "         "
            "         "
            "         "
            "         "
            "         "
            "         ";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   4     "
            "    5    "
            "     6   "
            "      7  "
            "       8 "
            "        9";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   1     "
            "    2    "
            "     3   "
            "      1  "
            "       2 "
            "        3";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   1     "
            "    2    "
            "     3   "
            "      1  "
            "      32 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   1    7"
            "    2 7  "
            "     3   "
            "      1  "
            "       2 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   1     "
            "    2    "
            "     3   "
            "  4   1  "
            " 4     2 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "1        "
            " 2 1     "
            "  3      "
            "   1     "
            "    2    "
            "     3   "
            "      1  "
            "       2 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   1 6   "
            "   62    "
            "     3   "
            "      1  "
            "       2 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            " 5 1     "
            "5   2    "
            "     3   "
            "      1  "
            "       2 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    cout << "all tests passed" << endl;
}
