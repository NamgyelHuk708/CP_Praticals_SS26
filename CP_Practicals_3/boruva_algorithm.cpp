#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v;
    int weight;
};

// Union-Find (Disjoint Set Union) data structure
class UnionFind {
public:
    vector<int> parent, rank;
    
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find the root of the set containing x
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    // Union two sets
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if (px == py) return false; // Already in same set
        
        // Union by rank
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

// Borůvka's Algorithm for Minimum Spanning Tree
vector<Edge> boruvasAlgorithm(int n, vector<Edge> edges) {
    vector<Edge> mst;
    UnionFind uf(n);
    int edgesInMST = 0;
    
    // Continue until we have n-1 edges in MST
    while (edgesInMST < n - 1) {
        // For each component, find the minimum weight edge to another component
        vector<int> cheapest(n, -1); // cheapest[i] = index of cheapest edge from component i
        
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            
            int root_u = uf.find(u);
            int root_v = uf.find(v);
            
            // If u and v are in different components
            if (root_u != root_v) {
                // Update cheapest edge for component root_u
                if (cheapest[root_u] == -1 || 
                    edges[i].weight < edges[cheapest[root_u]].weight) {
                    cheapest[root_u] = i;
                }
                
                // Update cheapest edge for component root_v
                if (cheapest[root_v] == -1 || 
                    edges[i].weight < edges[cheapest[root_v]].weight) {
                    cheapest[root_v] = i;
                }
            }
        }
        
        // Add all cheapest edges to MST (if they connect different components)
        for (int i = 0; i < n; i++) {
            if (cheapest[i] != -1) {
                int u = edges[cheapest[i]].u;
                int v = edges[cheapest[i]].v;
                
                if (uf.unite(u, v)) {
                    mst.push_back(edges[cheapest[i]]);
                    edgesInMST++;
                }
            }
        }
    }
    
    return mst;
}

int main() {
    // Number of vertices
    int n = 5;
    
    // Create edge list (undirected graph)
    vector<Edge> edges = {
        {0, 1, 4},
        {0, 2, 2},
        {1, 2, 1},
        {1, 3, 5},
        {2, 3, 8},
        {2, 4, 10},
        {3, 4, 2}
    };
    
    cout << "=== Borůvka's Algorithm (Minimum Spanning Tree) ===" << endl;
    cout << "\nNumber of vertices: " << n << endl;
    cout << "Edges (from, to, weight):" << endl;
    for (auto& edge : edges) {
        cout << "  " << edge.u << " -- " << edge.v << " : " << edge.weight << endl;
    }
    
    // Apply Borůvka's Algorithm
    vector<Edge> mst = boruvasAlgorithm(n, edges);
    
    cout << "\nMinimum Spanning Tree:" << endl;
    int totalWeight = 0;
    for (auto& edge : mst) {
        cout << "  " << edge.u << " -- " << edge.v << " : " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    
    cout << "\nTotal Weight of MST: " << totalWeight << endl;
    cout << "Number of edges in MST: " << mst.size() << " (should be " << n-1 << ")" << endl;
    
    return 0;
}
