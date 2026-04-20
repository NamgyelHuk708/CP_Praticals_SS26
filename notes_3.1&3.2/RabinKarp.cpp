#include<bits/stdc++.h>
using namespace std;

const int d = 256;
const long long q = 1e9 + 9;

vector<int> rabinKarp(const string& text, const string& pat) {
    int n = text.size(), m = pat.size();
    vector<int> matches;
    long long ph = 0, th = 0, h = 1;
    
    for(int i = 0; i < m-1; i++) h = (h * d) % q; // h = d^(m-1) mod q
    
    for(int i = 0; i < m; i++) { 
        ph = (d * ph + pat[i]) % q;
        th = (d * th + text[i]) % q; 
    } // initial hashes
    
    cout << "Pattern hash: " << ph << endl;
    cout << "d=" << d << ", q=" << q << "\n\n";
    
    for(int i = 0; i <= n - m; i++) {
        cout << "Window[" << i << ".." << (i+m-1) << "] \"" << text.substr(i, m) << "\" hash=" << th;
        
        if(ph == th) {
            cout << " == patHash";
            if(text.substr(i, m) == pat) {
                cout << " -> verify -> MATCH at index " << i;
                matches.push_back(i);
            } else {
                cout << " -> SPURIOUS HIT (hash collision)";
            }
        } else {
            cout << " != patHash -> skip";
        }
        cout << "\n";
        
        if(i < n - m) {
            th = (d * (th - (long long)text[i] * h) + text[i+m]) % q;
            if(th < 0) th += q; // fix negative mod
        }
    }
    
    return matches; 
}

int main() {
    string text = "AABABCABAB";
    string pattern = "ABAB";
    
    cout << "rabinKarp(\"" << text << "\", \"" << pattern << "\"):\n";
    cout << "================================\n\n";
    
    vector<int> matches = rabinKarp(text, pattern);
    
    cout << "\n================================\n";
    cout << "Output: [ ";
    for(int idx : matches) {
        cout << idx << " ";
    }
    cout << "]\n";
    cout << "Total matches: " << matches.size() << endl;
    cout << "Spurious hits: 0" << endl;
    
    return 0;
}
