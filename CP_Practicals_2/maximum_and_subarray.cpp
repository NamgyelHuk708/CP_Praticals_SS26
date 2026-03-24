// ============================================================
// Problem 2: Maximum AND Subarray (length exactly K)
// Approach: Greedy bit-by-bit from MSB to LSB.
// For each bit, check if there's a run of K consecutive elements
// all having the current candidate bits set. If yes, keep the bit.
// ============================================================
#include <bits/stdc++.h>
using namespace std;
int main(){
    int T; cin >> T;
    while(T--){
        int N, K; cin >> N >> K;
        vector<int> A(N);
        for(auto &x : A) cin >> x;
        int ans = 0;
        for(int b = 29; b >= 0; b--){
            int cand = ans | (1 << b);
            int cnt = 0; bool ok = false;
            for(int i = 0; i < N; i++){
                cnt = ((A[i] & cand) == cand) ? cnt + 1 : 0;
                if(cnt >= K){ ok = true; break; }
            }
            if(ok) ans = cand;
        }
        cout << ans << "\n";
    }
}
