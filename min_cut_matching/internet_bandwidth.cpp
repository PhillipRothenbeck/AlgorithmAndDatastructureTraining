#include <cstdio>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// bfs code from the slides modified to produce the shortest path
vector<int> get_path(int** RC, int s, int t, int num_nodes) {
    queue<int> q;
    vector<int> visited(num_nodes, 0);
    vector<int> distance(num_nodes, 1001);
    vector<int> predecessor(num_nodes, -1);
    vector<int> shortest_path;

    // start with arbitrary node, we choose the node with index 0:
    q.push(0);
    visited[0] = 1;
    distance[0] = 0;
    // go through the graph until queue is empty:
    int current_node;
    while (!q.empty()) {
        // get first element from queue and remove it from queue:
        current_node = q.front();
        q.pop();

        // add all unqueued neighbors of the current node to the queue:
        for (int i = 0; i < num_nodes; i++) {
            if (RC[current_node][i] > 0) {
                if (visited[i] == 0) {
                    // update the distance if shorter path is found
                    if (distance[current_node] + RC[current_node][i] < distance[i]) {
                        distance[i] = distance[current_node] + RC[current_node][i];
                        predecessor[i] = current_node;
                    }
                    q.push(i);
                    // set neighbor as queued:
                    visited[i] = 1;
                }
            }
        }
    }

    // rewind with the shortest path and construct the vector
    current_node = t;
    if (predecessor[t] != -1) {
        while (current_node != -1) {
            shortest_path.insert(shortest_path.begin(), current_node);
            current_node = predecessor[current_node];
        }
    }
    return shortest_path;
}

// edmond karp algorithm form the slides modified for to use for the problem (array and no vectors)
int edmond_karp(int** A, int s, int t, int num_nodes) {
    // data structure for remaining capacities
    int** RC = new int*[num_nodes];
    for (int i = 0; i < num_nodes; i++) {
        RC[i] = new int[num_nodes];
        for (int j = 0; j < num_nodes; j++) {
            RC[i][j] = A[i][j];
        }
    }

    // initialize some variables for computing the flow:
    bool finished = false;
    int total_flow_so_far = 0;
    vector<int> current_path;
    int flow_of_current_path;
    while (!finished) {
        // look for a new shortest path that uses the remaining capacities:
        current_path = get_path(RC, s, t, num_nodes);
        if (current_path.empty()) {
            // case no path was found. Algorithm is finished:
            finished = true;
            break;
        }
        // compute maximum flow on current path: find edge with minimum remaining capacity
        flow_of_current_path = RC[current_path[0]][current_path[1]];
        // iterate through path, check each edge of path and find the minimum remaining capacity:
        for (size_t i = 1; i < current_path.size() - 1; i++) {
            if (flow_of_current_path > RC[current_path[i]][current_path[i + 1]]) {
                flow_of_current_path = RC[current_path[i]][current_path[i + 1]];
            }
        }
        // add new flow to total flow:
        total_flow_so_far += flow_of_current_path;
        // adjust the remaining capacities:
        for (size_t i = 0; i < current_path.size() - 1; i++) {
            RC[current_path[i]][current_path[i + 1]] -= flow_of_current_path;
            RC[current_path[i + 1]][current_path[i]] += flow_of_current_path;
        }
    }
    for (int i = 0; i < num_nodes; i++) {
        delete[] RC[i];
    }
    delete[] RC;
    return total_flow_so_far;
}

int main() {
    string row;
    int num_nodes = 0;
    int num_network = 0;
    int** A;
    int s, t, e;
    while (getline(cin, row)) {
        if (row.size() == 1) {
            if (num_network != 0) {
                // calculate bandwidth of the old network
                int bandwidth = edmond_karp(A, s, t, num_nodes);
                cout << bandwidth << endl;
            }
            // initialize new network
            num_nodes = stoi(row);
            if (num_nodes == 0) {
                return 0;
            }
            getline(cin, row);
            // read configuration of new network (s, t and number of edges)
            stringstream ss;
            ss << row;
            ss >> s >> t >> e;
            s--;
            t--;
            // initialize adjacency matrix
            A = new int*[num_nodes];
            for (int i = 0; i < num_nodes; i++) {
                A[i] = new int[num_nodes];
                for (int j = 0; j < num_nodes; j++) {
                    A[i][j] = 0;
                }
            }
            num_network++;
        } else {
            // read edge of the network
            int n1, n2, bandwidth;
            stringstream ss;
            ss << row;
            ss >> n1 >> n2 >> bandwidth;
            A[n1 - 1][n2 - 1] = bandwidth;
        }
    }
}