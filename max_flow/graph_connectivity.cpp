#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    string row;
    int_fast32_t **adjacency_matrix;
    int step = 0;
    getline(cin, row);
    // first line includes the number of test cases
    int test_cases = stoi(row);
    getline(cin, row);
    for (int i = 0; i < test_cases; i++) {
        // initialize adjacency matrix
        getline(cin, row);
        // get the number of node by converting the biggest node to a number
        int num_nodes = row[0] - 'A' + 1;
        adjacency_matrix = new int_fast32_t *[num_nodes];
        for (int j = 0; j < num_nodes; j++) {
            adjacency_matrix[j] = new int_fast32_t[num_nodes];
            for (int k = 0; k < num_nodes; k++) {
                // in preparation for floyd-warshall initialize all non connections
                // with the number of nodes plus one (bigger than the longest possible connection)
                adjacency_matrix[j][k] = num_nodes + 1;
            }
        }

        // put each edge into the adjacency matrix
        getline(cin, row);
        while (row.compare("") != 0) {
            adjacency_matrix[row[0] - 'A'][row[1] - 'A'] = 1;
            adjacency_matrix[row[1] - 'A'][row[0] - 'A'] = 1;
            getline(cin, row);
        }

        // put diagonal to 0 for floyd-warshall
        for (int j = 0; j < num_nodes; j++) {
            adjacency_matrix[j][j] = 0;
        }

        // floyd-warshall
        for (int j = 0; j < num_nodes; j++) {
            for (int n = 0; n < num_nodes; n++) {
                for (int m = 0; m < num_nodes; m++) {
                    if (adjacency_matrix[n][m] > adjacency_matrix[n][j] + adjacency_matrix[j][m]) {
                        adjacency_matrix[n][m] = adjacency_matrix[n][j] + adjacency_matrix[j][m];
                    }
                }
            }
        }

        // save each component in a list represented by the first node of it that was found
        list<int> l;
        int count = 0;
        // for each node check if the according component is already counted
        for (int j = 0; j < num_nodes; j++) {
            bool is_already_in_list = false;
            for (int e : l) {
                if (adjacency_matrix[j][e] < num_nodes + 1) {
                    is_already_in_list = true;
                    break;
                }
            }
            // add new component
            if (!is_already_in_list) {
                l.push_back(j);
                count++;
            }
        }

        cout << count << endl;
        for (int j = 0; j < num_nodes; j++) {
            delete[] adjacency_matrix[j];
        }
        delete[] adjacency_matrix;
    }
}