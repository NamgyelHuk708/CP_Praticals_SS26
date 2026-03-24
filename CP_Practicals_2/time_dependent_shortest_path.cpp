// ============================================================
// Problem 5b: Time-Dependent Shortest Path
// Approach: Modified Dijkstra. Edge (u→v) with f(t) = a*t + b:
//   if you leave u at time t, you arrive at v at t + f(t) = t*(1+a) + b.
// This is FIFO (monotone), so Dijkstra works correctly.
// ============================================================
#include <bits/stdc++.h>
using namespace std;
typedef double ld;
typedef pair<ld,int> pdi;
int main(){
    int N, M; cin >> N >> M;
    vector<vector<tuple<int,ld,ld>>> adj(N + 1);
    for(int i = 0; i < M; i++){
        int u, v; ld a, b; cin >> u >> v >> a >> b;
        adj[u].push_back({v, a, b});
    }
    vector<ld> dist(N + 1, 1e18);
    priority_queue<pdi, vector<pdi>, greater<>> pq;
    dist[1] = 0; pq.push({0.0, 1});
    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u] + 1e-9) continue;
        for(auto [v, a, b] : adj[u]){
            ld arrive = d * (1 + a) + b;  // depart at d, travel time = a*d+b
            if(arrive < dist[v])
                pq.push({dist[v] = arrive, v});
        }
    }
    if(dist[N] >= 1e17) cout << -1 << "\n";
    else cout << fixed << setprecision(2) << dist[N] << "\n";
}
