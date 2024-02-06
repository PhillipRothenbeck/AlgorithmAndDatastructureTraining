#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    Edge(unsigned long s,
         unsigned long t,
         unsigned long w) {
        source = s;
        target = t;
        weight = w;
    }
    unsigned long source;
    unsigned long target;
    unsigned long weight;

    bool operator==(const Edge &other) const {
        return (this->source == other.source) && (this->target == other.target) && (this->weight == other.weight);
    }

    bool operator<(const Edge &other) const {
        return (this->weight < other.weight);
    }
};

struct CompareEdges {
    bool operator()(const Edge e1, const Edge e2) {
        return e1.weight > e2.weight;
    }
};

Edge get_next_edge(set<Edge> E, set<unsigned long> W, set<unsigned long> V) {
    priority_queue<Edge, std::vector<Edge>, CompareEdges> pq;

    for (Edge e : E) {
        bool cond1 = W.find(e.source) != W.end() && ((V.find(e.target) != V.end()) && (W.find(e.target) == W.end()));
        bool cond2 = W.find(e.target) != W.end() && ((V.find(e.source) != V.end()) && (W.find(e.source) == W.end()));
        if (cond1 || cond2) {
            pq.push(e);
        }
    }
    if (pq.size() > 0) {
        return pq.top();
    } else {
        return {0, 0, 0};
    }
}

bool contains(set<unsigned long> set, unsigned long e) {
    return set.find(e) != set.end();
}

bool contains(set<Edge> set, Edge e) {
    return set.find(e) != set.end();
}

int main() {
    string file_name = "network.txt";
    fstream file;
    file.open(file_name, ios::in);
    if (file.is_open()) {
        string line;
        // adjacency matrix for original graph
        vector<vector<unsigned long>> matrix;

        // adjacency matrix for new graph
        vector<vector<unsigned long>> new_matrix;
        unsigned long i = 0;
        unsigned long j;

        // sets for nodes in original and new graph
        set<unsigned long> V, W;

        // set for edges in original graph
        set<Edge> E;

        // read input file
        while (getline(file, line)) {
            vector<unsigned long> matrix_line, new_matrix_line;
            string weight;
            stringstream ss(line);
            j = 0;
            while (getline(ss, weight, ',')) {
                if (weight[0] != '-') {
                    int w = stoul(weight);
                    if (i > j) {
                        Edge e = Edge(i, j, w);
                        E.insert(e);
                    }
                    matrix_line.push_back(w);
                } else {
                    matrix_line.push_back(0);
                }
                new_matrix_line.push_back(0);
                j++;
            }
            matrix.push_back(matrix_line);
            new_matrix.push_back(new_matrix_line);
            V.insert(i);
            i++;
        }

        // execute Prims algorithm
        while (W != V) {
            if (W.size() == 0) {
                // step 2 start with node 0
                W.insert(0);
            }

            // step 3.1
            Edge e = get_next_edge(E, W, V);

            // step 3.2
            W.insert(e.source);
            W.insert(e.target);
            new_matrix[e.target][e.source] = e.weight;
            new_matrix[e.source][e.target] = e.weight;
            E.erase(e);
        }

        // print adjacency matrix and compute total weight
        unsigned long total_weight = 0;
        for (auto v1 : V) {
            cout << endl;
            unsigned i = 0;
            for (auto v2 : V) {
                if (new_matrix[v1][v2] == 0) {
                    cout << "-";
                } else {
                    cout << new_matrix[v1][v2];
                    if (v1 < v2) {
                        total_weight += new_matrix[v1][v2];
                    }
                }
                i++;
                if (i < V.size()) {
                    cout << ",";
                }
            }
        }
        cout << endl
             << "total weight: " << total_weight << endl;
        file.close();
    } else {
        cout << "failed to open the file" << endl;
    }
}