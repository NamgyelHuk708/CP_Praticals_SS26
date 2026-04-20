#include<bits/stdc++.h>
using namespace std;

const int d = 256;
const long long q = 1e9 + 9;

vector<int> multiPattern(const string& text, const vector<string>& pats) {
    int m = pats[0].size(); // assume equal-length patterns
    unordered_set<long long> phashes;
    vector<int> matches;
    long long h = 1;
    
    for(int i = 0; i < m-1; i++) h = (h * d) % q;
    
    cout << "Hash set built: {";
    for(const auto& p : pats) { // hash all patterns -> set
        long long ph = 0;
        for(char c : p) ph = (d * ph + c) % q;
        phashes.insert(ph);
        cout << "hash(\"" << p << "\")=" << ph;
        if(p != pats.back()) cout << ", ";
    }
    cout << "}\n";
    cout << "d=" << d << ", q=" << q << "\n\n";
    cout << "Single pass:\n";
    
    long long wh = 0;
    for(int i = 0; i < m; i++) wh = (d * wh + text[i]) % q;
    
    for(int i = 0; i <= (int)text.size() - m; i++) {
        cout << "Window[" << i << ".." << (i+m-1) << "] \"" << text.substr(i, m) << "\" hash=" << wh;
        
        if(phashes.count(wh)) {
            cout << " in set -> MATCH at " << i;
            for(const auto& p : pats) {
                long long ph = 0;
                for(char c : p) ph = (d * ph + c) % q;
                if(ph == wh && text.substr(i, m) == p) {
                    cout << " (pattern \"" << p << "\")";
                    break;
                }
            }
            matches.push_back(i);
        } else {
            cout << " not in set";
        }
        cout << "\n";
        
        if(i < (int)text.size() - m) {
            wh = (d * (wh - (long long)text[i] * h) + text[i+m]) % q;
            if(wh < 0) wh += q;
        }
    }
    
    return matches;
}

int main() {
    string text = "AABABCABAB";
    vector<string> patterns = {"ABAB", "ABCA", "BCAB"};
    
    cout << "multiPattern(\"" << text << "\", {\"ABAB\",\"ABCA\",\"BCAB\"}):\n";
    cout << "================================\n\n";
    
    vector<int> matches = multiPattern(text, patterns);
    
    cout << "\n================================\n";
    cout << "Output: [ ";
    for(int idx : matches) {
        cout << idx << " ";
    }
    cout << "]\n";
    cout << "Total matches: " << matches.size() << endl;
    cout << "\nBenefit: 1 pass vs " << patterns.size() << " separate KMP runs\n";
    cout << "Efficiency: O(n + m*k) instead of O(n*k) for k patterns" << endl;
    
    return 0;
}
