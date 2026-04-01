#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const long long INF = 1e18;

// Structure to represent an edge
struct Edge {
    int from, to;
    long long weight;
};

// Bellman-Ford Algorithm for single source
bool bellmanFord(int n, vector<Edge>& edges, int source, vector<long long>& dist) {
    dist.assign(n, INF);
    dist[source] = 0;
    
    // Relax edges n-1 times
    for (int i = 0; i < n - 1; i++) {
        for (auto& edge : edges) {
            if (dist[edge.from] != INF && 
                dist[edge.from] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.weight;
            }
        }
    }
    
    // Check for negative cycle
    for (auto& edge : edges) {
        if (dist[edge.from] != INF && 
            dist[edge.from] + edge.weight < dist[edge.to]) {
            return false;
        }
    }
    
    return true;
}

// Dijkstra's Algorithm for single source
void dijkstra(int n, int source, vector<vector<pair<int, long long>>>& adj, 
              vector<long long>& dist) {
    dist.assign(n, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, 
                   greater<pair<long long, int>>> pq;
    
    dist[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (int k = 0; k < adj[u].size(); k++) {
            int v = adj[u][k].first;
            long long weight = adj[u][k].second;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

// Johnson's Algorithm
vector<vector<long long>> johnsonsAlgorithm(int n, vector<Edge>& edges) {
    // Step 1: Add auxiliary vertex with 0-weight edges to all vertices
    vector<Edge> edgesWithAux = edges;
    for (int i = 0; i < n; i++) {
        edgesWithAux.push_back({n, i, 0});
    }
    
    // Step 2: Run Bellman-Ford from auxiliary vertex (n+1 vertices: 0 to n)
    vector<long long> h(n + 1);
    if (!bellmanFord(n + 1, edgesWithAux, n, h)) {
        cout << "⚠️  Negative cycle detected!" << endl;
        return vector<vector<long long>>();
    }
    
    // Step 3: Reweight edges and build adjacency list
    vector<vector<pair<int, long long>>> adj(n);
    for (auto& edge : edges) {
        long long newWeight = edge.weight + h[edge.from] - h[edge.to];
        adj[edge.from].push_back(make_pair(edge.to, newWeight));
    }
    
    // Step 4: Run Dijkstra from each vertex
    vector<vector<long long>> result(n);
    for (int i = 0; i < n; i++) {
        vector<long long> dist;
        dijkstra(n, i, adj, dist);
        
        result[i].resize(n);
        // Convert back to original weights
        for (int j = 0; j < n; j++) {
            if (dist[j] != INF) {
                result[i][j] = dist[j] + h[j] - h[i];
            } else {
                result[i][j] = INF;
            }
        }
    }
    
    return result;
}

void printMatrix(int n, vector<vector<long long>>& matrix) {
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
    
    // Create edge list
    vector<Edge> edges = {
        {0, 1, 5},
        {0, 3, 10},
        {1, 2, 3},
        {2, 3, 1},
        {3, 0, 2},
        {3, 2, 9}
    };
    
    cout << "=== Johnson's Algorithm ===" << endl;
    cout << "\nNumber of vertices: " << n << endl;
    cout << "Edges (from, to, weight):" << endl;
    for (auto& edge : edges) {
        cout << "  " << edge.from << " -> " << edge.to << " : " << edge.weight << endl;
    }
    
    // Apply Johnson's Algorithm
    vector<vector<long long>> result = johnsonsAlgorithm(n, edges);
    
    cout << "\nShortest Path Matrix (from Johnson's Algorithm):" << endl;
    printMatrix(n, result);
    
    // Print some specific paths
    cout << "\nShortest Paths:" << endl;
    cout << "From 0 to 2: " << result[0][2] << endl;
    cout << "From 1 to 3: " << result[1][3] << endl;
    cout << "From 3 to 1: " << result[3][1] << endl;
    
    return 0;
}
