// ============================================================
// Problem 1: Dinner Table Arrangements
// Approach: Bitmask DP (Hamiltonian Cycle)
// dp[seated_mask][last] = can we seat those friends with 'last' at the open end?
// Fix friend 0 as start to eliminate circular duplicates.
// ============================================================
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    while(T--){
        int N; cin >> N;
        vector<int> mask(N, 0);
        for(int i = 0; i < N; i++){
            int M; cin >> M;
            for(int j = 0; j < M; j++){
                int a; cin >> a;
                mask[i] |= (1 << a);
            }
        }
        auto compat = [&](int i, int j){ return (mask[i] & mask[j]) == 0; };
        if(N == 1){ cout << "YES\n"; continue; }
        if(N == 2){ cout << (compat(0,1) ? "YES" : "NO") << "\n"; continue; }
        int FULL = (1 << N) - 1;
        vector<vector<bool>> dp(1 << N, vector<bool>(N, false));
        dp[1 << 0][0] = true;
        for(int s = 1; s < (1 << N); s++)
            for(int last = 0; last < N; last++){
                if(!dp[s][last] || !(s & (1 << last))) continue;
                for(int nxt = 0; nxt < N; nxt++){
                    if((s & (1 << nxt)) || !compat(last, nxt)) continue;
                    dp[s | (1 << nxt)][nxt] = true;
                }
            }
        bool ok = false;
        for(int last = 1; last < N; last++)
            if(dp[FULL][last] && compat(last, 0)){ ok = true; break; }
        cout << (ok ? "YES" : "NO") << "\n";
    }
}
