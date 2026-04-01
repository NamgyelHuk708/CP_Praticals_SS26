#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = 1e9; // Represent infinity

void floyd_warshall(int n, vector<vector<int>>& dist) {
    // dist[i][j] = shortest distance from vertex i to vertex j
    
    // k is the intermediate vertex
    for (int k = 0; k < n; k++) {
        // For each source vertex i
        for (int i = 0; i < n; i++) {
            // For each destination vertex j
            for (int j = 0; j < n; j++) {
                // If path through k is shorter, update
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

bool detectNegativeCycle(int n, vector<vector<int>>& dist) {
    // Check if any diagonal element is negative
    // If dist[i][i] < 0, then there's a negative cycle
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            return true; // Negative cycle detected
        }
    }
    return false; // No negative cycle
}

void printMatrix(int n, vector<vector<int>>& matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == INF)
                cout << "INF ";
            else
                cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Number of vertices
    int n = 4;
    
    // Create adjacency matrix (distance matrix)
    // INF means no direct edge
    vector<vector<int>> dist(n, vector<int>(n, INF));
    
    // Distance from a vertex to itself is 0
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    
    // Add edges (format: dist[from][to] = weight)
    // Example graph
    dist[0][1] = 5;
    dist[0][3] = 10;
    dist[1][2] = 3;
    dist[2][3] = 1;
    dist[3][0] = 2;
    dist[3][2] = 9;
    
    cout << "=== Floyd-Warshall Algorithm ===" << endl;
    cout << "\nInitial Distance Matrix:" << endl;
    printMatrix(n, dist);
    
    // Apply Floyd-Warshall algorithm
    floyd_warshall(n, dist);
    
    cout << "\nShortest Path Matrix (after Floyd-Warshall):" << endl;
    printMatrix(n, dist);
    
    // Check for negative cycle
    cout << "\nChecking for negative cycle..." << endl;
    if (detectNegativeCycle(n, dist)) {
        cout << "⚠️  Negative cycle detected!" << endl;
    } else {
        cout << "✓ No negative cycle found" << endl;
    }
    
    // Print shortest paths between some vertices
    cout << "\nShortest Paths:" << endl;
    cout << "From 0 to 2: " << dist[0][2] << endl;
    cout << "From 1 to 3: " << dist[1][3] << endl;
    cout << "From 3 to 1: " << dist[3][1] << endl;
    
    return 0;
}
