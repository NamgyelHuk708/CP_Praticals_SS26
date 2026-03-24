// ============================================================
// Problem 4: Sliding Window Maximum with Point Updates
// Approach: Segment tree for O(log N) update and range-max query.
// Query: max in [i-K+1, i] after each type-2 query.
// ============================================================
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int seg[4 * MAXN], N;

void build(vector<int>& A, int v, int s, int e){
    if(s == e){ seg[v] = A[s]; return; }
    int m = (s + e) / 2;
    build(A, 2*v, s, m); build(A, 2*v+1, m+1, e);
    seg[v] = max(seg[2*v], seg[2*v+1]);
}
void upd(int v, int s, int e, int pos, int val){
    if(s == e){ seg[v] = val; return; }
    int m = (s + e) / 2;
    if(pos <= m) upd(2*v, s, m, pos, val);
    else         upd(2*v+1, m+1, e, pos, val);
    seg[v] = max(seg[2*v], seg[2*v+1]);
}
int qry(int v, int s, int e, int l, int r){
    if(r < s || e < l) return INT_MIN;
    if(l <= s && e <= r) return seg[v];
    int m = (s + e) / 2;
    return max(qry(2*v, s, m, l, r), qry(2*v+1, m+1, e, l, r));
}
int main(){
    int K, Q; cin >> N >> K >> Q;
    vector<int> A(N + 1);
    for(int i = 1; i <= N; i++) cin >> A[i];
    build(A, 1, 1, N);
    while(Q--){
        int t; cin >> t;
        if(t == 1){
            int p, v; cin >> p >> v;
            upd(1, 1, N, p, v);
        } else {
            int i; cin >> i;
            cout << qry(1, 1, N, i - K + 1, i) << "\n";
        }
    }
}
