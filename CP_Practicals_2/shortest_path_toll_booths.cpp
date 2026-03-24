// ============================================================
// Problem 6: Shortest Path with Toll Booths
// Approach: DP where dp[i][j] = max coins at booth i (0-indexed)
// having used j skips. Moving from booth i to i+1 costs toll[i+1].
// Minimize j (skips) → answer = (N-1) + j, checked in order j=0,1,...K.
// ============================================================
#include <bits/stdc++.h>
using namespace std;
int main(){
    int N, M, K; cin >> N >> M >> K;
    vector<int> toll(N);
    for(auto &x : toll) cin >> x;
    if(N == 1){ cout << 0; return 0; }

    const long long NEG_INF = -1e18;
    // dp[i][j] = max coins remaining at booth i with j skips used
    vector<vector<long long>> dp(N, vector<long long>(K + 1, NEG_INF));
    dp[0][0] = M;

    for(int i = 0; i < N - 1; i++)
        for(int j = 0; j <= K; j++){
            if(dp[i][j] == NEG_INF) continue;
            // Option 1: Pay toll at next booth
            if(dp[i][j] >= toll[i + 1])
                dp[i+1][j] = max(dp[i+1][j], dp[i][j] - toll[i+1]);
            // Option 2: Skip (costs 2 min instead of 1)
            if(j < K)
                dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]);
        }

    for(int j = 0; j <= K; j++)
        if(dp[N-1][j] != NEG_INF){ cout << (N-1) + j << "\n"; return 0; }
    cout << -1 << "\n";
}
