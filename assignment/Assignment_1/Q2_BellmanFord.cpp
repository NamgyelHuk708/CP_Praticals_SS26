// Assignment 1 - Question 2: Bellman-Ford Algorithm
// - Shortest paths from a source vertex
// - Detects negative weight cycles
// - Handles directed graphs with negative edge weights

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Edge structure
struct Edge {
    int u, v, w;  // from, to, weight
};

// ─────────────────────────────────────────────
// Bellman-Ford Algorithm
// Returns true if no negative cycle exists
// dist[] will hold shortest distances from src
// ─────────────────────────────────────────────
bool bellmanFord(int V, int src, const vector<Edge>& edges, vector<int>& dist) {
    // Step 1: Initialize distances
    dist.assign(V, INT_MAX);
    dist[src] = 0;

    // Step 2: Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (const Edge& e : edges) {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    // Step 3: Check for negative weight cycles
    // If we can still relax any edge, a negative cycle exists
    for (const Edge& e : edges) {
        if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
            return false;  // Negative cycle detected
        }
    }
    return true;  // No negative cycle
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (u v w):" << endl;
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        // Convert to 0-indexed if input is 1-indexed
        edges[i].u--;
        edges[i].v--;
    }

    int src;
    cout << "Enter source vertex (1-indexed): ";
    cin >> src;
    src--;  // Convert to 0-indexed

    vector<int> dist;
    bool noNegCycle = bellmanFord(V, src, edges, dist);

    if (!noNegCycle) {
        cout << "\n*** Negative weight cycle detected! Shortest paths are undefined. ***" << endl;
    } else {
        cout << "\nShortest distances from vertex " << src + 1 << ":" << endl;
        cout << "Vertex\tDistance" << endl;
        for (int i = 0; i < V; i++) {
            cout << i + 1 << "\t";
            if (dist[i] == INT_MAX)
                cout << "UNREACHABLE" << endl;
            else
                cout << dist[i] << endl;
        }
    }

    return 0;
}

/*
────────────────────────────────────────────────────────────
SAMPLE INPUT (no negative cycle):
5 8
1 2 -1
1 3 4
2 3 3
2 4 2
2 5 2
4 3 5
4 2 1
5 4 -3
Source: 1

EXPECTED OUTPUT:
Vertex  Distance
1       0
2       -1
3       2
4       -2
5       1

────────────────────────────────────────────────────────────
SAMPLE INPUT (with negative cycle):
3 3
1 2 1
2 3 -5
3 1 1
Source: 1

EXPECTED OUTPUT:
*** Negative weight cycle detected! ***
────────────────────────────────────────────────────────────
*/
