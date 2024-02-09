#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>

using namespace std;

struct MatchingGraph {
    MatchingGraph(int i_n) {
        m_n = i_n * 3;
        m_nodes = i_n;
        m_distance_computed = false;

        // setup matrix for graph interpretation: two bipartite graphs chained behind each other, each level stands for one permutation
        // look at the produced graph, by calling <MatchingGraph>.print_graph()
        m_matrix = new int*[m_n];
        int set_counter = 0;
        int y_set = 0;  // divide graph into 9 parts (sets) like a 3x3 matrix
        for (int i = 0; i < m_n; i++) {
            m_matrix[i] = new int[m_n];
            int x_set = 0;
            int y_int = i % i_n;
            if (y_int == 0) {
                y_set++;
            }
            for (int j = 0; j < m_n; j++) {
                int x_int = j % i_n;
                if (x_int == 0) {
                    set_counter++;
                    x_set++;
                }
                // the graph is directed from left to right
                if (x_set - 1 == y_set) {  // only in the upper middle and middle right set connections can exist
                    m_matrix[i][j] = x_int != y_int;
                } else {
                    m_matrix[i][j] = 0;
                }
            }
        }
    }

    ~MatchingGraph() {
        for (int i = 0; i < m_n; i++) {
            delete[] m_matrix[i];
        }
        delete m_matrix;
    }

    void print_graph() {
        cout << endl;
        for (int i = 0; i < m_n; i++) {
            for (int j = 0; j < m_n; j++) {
                cout << m_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // check if any permutations exist
    bool permutaion_exists(int* init) {
        if (m_distance_computed) {
            // check every possible and correct path from the starting node (where the card starts) to the end node (where the card is supposed to go)
            vector<vector<int>> possible_paths;
            for (int node = 0; node < m_nodes; node++) {
                vector<int> node_paths;
                for (int i = m_nodes; i < m_nodes * 2; i++) {
                    for (int j = m_nodes * 2; j < m_nodes * 3; j++) {
                        if (m_matrix[node][i] == 1 && m_matrix[i][j] == 1 && init[node] == j % m_nodes) {
                            node_paths.push_back(i);
                        }
                    }
                }

                // if no paths can be detected no permutation is possible
                if (node_paths.size() == 0) {
                    return false;
                }
                possible_paths.push_back(node_paths);
            }

            set<int> crossed_nodes;
            // if between all possible paths nodes in the middle layer double and the respective starting node has no other opportunities
            // no permutation can be found
            for (int i = 0; i < m_nodes; i++) {
                for (unsigned j = 0; j < possible_paths[i].size(); j++) {
                    if (crossed_nodes.find(possible_paths[i][j]) != crossed_nodes.end() && possible_paths[i].size() == 1) {
                        return false;
                    } else {
                        crossed_nodes.insert(possible_paths[i][j]);
                    }
                }
            }
            return true;
        } else {
            cerr << "floyd-warshall has not been performed yet" << endl;
            return false;
        }
    }

    // get a correct permutation from the graph based on the fact, that a permutation exists
    void get_permutations(int* p, int* q, int* init) {
        if (!m_distance_computed) {
            cerr << "floyd-warshall has not been performed yet" << endl;
            return;
        }

        bool* nodes_finished = new bool[m_nodes];
        bool not_finished = true;

        // if an element of the array equals -1 no card is claiming this spot of the permutation
        for (int i = 0; i < m_nodes; i++) {
            nodes_finished[i] = false;
            p[i] = -1;
            q[i] = -1;
        }

        int current_node = 0;
        while (not_finished) {
            // get first possible and correct path for current node
            for (int i = m_nodes; i < m_nodes * 2; i++) {
                if (p[i - m_nodes] == -1 && m_matrix[current_node][i] != 0) {
                    if (m_matrix[i][init[current_node] + 2 * m_nodes] != 0) {
                        p[i - m_nodes] = current_node;
                        nodes_finished[current_node] = true;
                        q[init[current_node]] = i - m_nodes;
                        break;
                    }
                }
            }

            if (!nodes_finished[current_node]) {
                // if no path is found delete the path of the predecessor
                int free_node = current_node - 1;
                if (free_node < 0) {
                    free_node = m_nodes - 1;
                }

                nodes_finished[free_node] = false;
                for (int i = 0; i < m_nodes; i++) {
                    if (p[i] == free_node) {
                        p[i] = -1;
                        q[init[free_node]] = -1;
                    }
                }
            } else {
                // go to next node or finish
                not_finished = false;
                for (int i = 0; i < m_nodes; i++) {
                    if (!nodes_finished[i]) {
                        current_node = i;
                        not_finished = true;
                        break;
                    }
                }
            }
        }

        delete[] nodes_finished;
    }

    void floyd_warshall() {
        m_distance_computed = true;
        // set non edges to number of nodes + 1
        for (int i = 0; i < m_n; i++) {
            for (int j = 0; j < m_n; j++) {
                if (m_matrix[i][j] == 0) {
                    m_matrix[i][j] = m_n + 1;
                }
            }
        }
        // initialize all distances by edges, set distances to self to 0:
        for (int i = 0; i < m_n; i++)
            m_matrix[i][i] = 0;

        // run Floyd-Warshall:
        for (int k = 0; k < m_n; k++) {
            for (int i = 0; i < m_n; i++) {
                for (int j = 0; j < m_n; j++) {
                    // update distance of i,j by path via k:
                    m_matrix[i][j] = min(m_matrix[i][j], m_matrix[i][k] + m_matrix[k][j]);
                }
            }
        }

        for (int i = 0; i < m_n; i++) {
            for (int j = 0; j < m_n; j++) {
                if (m_matrix[i][j] > 2) {
                    m_matrix[i][j] = 0;
                }
            }
        }
    }

    int** m_matrix;
    int m_n;
    int m_nodes;
    bool m_distance_computed;
};

string get_permutations(int n, string init, int* p, int* q) {
    string solution = "Possible";

    // convert card line to integer
    int* init_int = new int[n];
    stringstream ss(init);
    string card;
    int idx = 0;
    while (ss >> card) {
        init_int[idx] = stoi(card) - 1;
        idx++;
    }

    // create graph
    MatchingGraph g(n);
    // g.print_graph();
    g.floyd_warshall();

    // check if permutations exist
    if (!g.permutaion_exists(init_int)) {
        solution = "Impossible";
    } else {
        // if so get them
        g.get_permutations(p, q, init_int);
    }
    return solution;
}

int main() {
    int t, n;
    string in;
    getline(cin, in);
    t = stoi(in);
    for (int i = 0; i < t; i++) {
        getline(cin, in);
        n = stoi(in);
        getline(cin, in);
        int* p = new int[n];
        int* q = new int[n];
        string solution = get_permutations(n, in, p, q);
        if (solution.compare("Impossible") == 0) {
            cout << "Impossible" << endl;
        } else {
            cout << "Possible" << endl;
            for (int i = 0; i < n; i++) {
                cout << p[i] + 1 << " ";
            }
            cout << endl;
            for (int i = 0; i < n; i++) {
                cout << q[i] + 1 << " ";
            }
            cout << endl;
        }
        delete[] p;
        delete[] q;
    }
}