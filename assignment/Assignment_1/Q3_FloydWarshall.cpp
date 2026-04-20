// Assignment 1 - Question 3: Floyd-Warshall Algorithm
// - All-pairs shortest paths
// - Negative cycle detection
// - Prints final distance matrix

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

const int INF = 1e9;  // Use a large value (not INT_MAX to avoid overflow)

// ─────────────────────────────────────────────
// Floyd-Warshall Algorithm
// dist[i][j] = shortest path from i to j
// Returns false if a negative cycle is found
// ─────────────────────────────────────────────
bool floydWarshall(int V, vector<vector<int>>& dist) {
    // Core DP: try every vertex k as an intermediate node
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Detect negative cycles:
    // If any dist[i][i] < 0, vertex i is on a negative cycle
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) return false;
    }
    return true;
}

// ─────────────────────────────────────────────
// Print the distance matrix
// ─────────────────────────────────────────────
void printMatrix(int V, const vector<vector<int>>& dist) {
    cout << "\nShortest Distance Matrix:" << endl;

    // Header row
    cout << setw(6) << " ";
    for (int j = 0; j < V; j++)
        cout << setw(8) << j + 1;
    cout << endl;

    cout << "      ";
    for (int j = 0; j < V; j++) cout << "--------";
    cout << endl;

    for (int i = 0; i < V; i++) {
        cout << setw(4) << i + 1 << " |";
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << setw(8) << "INF";
            else
                cout << setw(8) << dist[i][j];
        }
        cout << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    // Initialize distance matrix
    // dist[i][i] = 0, everything else = INF
    vector<vector<int>> dist(V, vector<int>(V, INF));
    for (int i = 0; i < V; i++) dist[i][i] = 0;

    cout << "Enter edges (u v w):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;  // Convert to 0-indexed
        // For multiple edges between same pair, keep the minimum
        dist[u][v] = min(dist[u][v], w);
    }

    bool noNegCycle = floydWarshall(V, dist);

    if (!noNegCycle) {
        cout << "\n*** Negative weight cycle detected! "
             << "All-pairs shortest paths are undefined. ***" << endl;
        // Still print matrix to show which diagonal entries went negative
        printMatrix(V, dist);
    } else {
        printMatrix(V, dist);
        cout << "\nNo negative cycles detected." << endl;
    }

    return 0;
}

/*
────────────────────────────────────────────────────────────
THEORETICAL EXPLANATION (for part d):

1. WHY FLOYD-WARSHALL WORKS WITH NEGATIVE EDGE WEIGHTS:
   The algorithm uses dynamic programming to consider every
   intermediate vertex k. A negative edge weight simply means
   routing through that edge is beneficial — the DP correctly
   propagates this "cheaper" cost across all pairs (i,j).
   Unlike Dijkstra, it does not assume all weights are positive.

2. WHY IT FAILS WITH NEGATIVE CYCLES:
   If a negative cycle exists, you can loop around it infinitely,
   making paths arbitrarily small (−∞). The algorithm detects
   this when dist[i][i] < 0 for any vertex i, meaning the
   "shortest path" from i back to itself is negative — which
   has no well-defined meaning as a shortest path.
────────────────────────────────────────────────────────────

SAMPLE INPUT:
4 5
1 2 3
1 3 8
1 4 -4
2 4 1
3 2 4
4 3 2

EXPECTED OUTPUT (distance matrix):
       1       2       3       4
      --------------------------------
   1 |       0       1      -3      -4
   2 |     INF       0      -1       1
   3 |     INF       4       0       5
   4 |     INF       5       1       0
────────────────────────────────────────────────────────────
*/
