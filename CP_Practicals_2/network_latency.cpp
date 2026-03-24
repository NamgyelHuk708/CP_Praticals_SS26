// ============================================================
// Problem 5a: Network Latency (Standard Shortest Path)
// Approach: Dijkstra with min-heap on undirected weighted graph.
// ============================================================
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
int main(){
    int N, M; cin >> N >> M;
    vector<vector<pair<int,int>>> adj(N + 1);
    for(int i = 0; i < M; i++){
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<ll> dist(N + 1, LLONG_MAX);
    priority_queue<pli, vector<pli>, greater<>> pq;
    dist[1] = 0; pq.push({0, 1});
    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        for(auto [v, w] : adj[u])
            if(dist[u] + w < dist[v])
                pq.push({dist[v] = dist[u] + w, v});
    }
    cout << (dist[N] == LLONG_MAX ? -1LL : dist[N]) << "\n";
}
