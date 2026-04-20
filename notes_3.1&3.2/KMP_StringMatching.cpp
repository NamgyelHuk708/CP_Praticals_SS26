#include<bits/stdc++.h>
using namespace std;

vector<int> buildLPS(const string& pat) { // O(m)
    int m = pat.size(); 
    vector<int> lps(m, 0);
    int len = 0, i = 1;
    while(i < m) {
        if(pat[i] == pat[len]) { 
            lps[i++] = ++len; 
        }
        else { 
            if(len != 0) len = lps[len-1]; // fall back, don't move i
            else lps[i++] = 0; 
        }
    }
    return lps; 
}

vector<int> kmpSearch(const string& text, const string& pat) {
    vector<int> lps = buildLPS(pat), matches;
    int n = text.size(), m = pat.size(), i = 0, j = 0;
    while(i < n) {
        if(text[i] == pat[j]) { 
            i++; j++; 
        }
        if(j == m) { 
            matches.push_back(i - j); 
            j = lps[j-1]; // found; check overlaps
        }
        else if(i < n && text[i] != pat[j]) {
            if(j != 0) j = lps[j-1]; 
            else i++; 
        }
    }
    return matches; 
}

int main() {
    string pattern = "ABABCABAB";
    string text = "ABABCABABABABCABAB";
    
    cout << "LPS for \"" << pattern << "\": [ ";
    vector<int> lps = buildLPS(pattern);
    for(int val : lps) {
        cout << val << " ";
    }
    cout << "]\n\n";
    
    cout << "kmpSearch(\"" << text << "\", \"" << pattern << "\"):\n";
    vector<int> matches = kmpSearch(text, pattern);
    
    cout << "MATCHES FOUND AT INDICES: [ ";
    for(int idx : matches) {
        cout << idx << " ";
    }
    cout << "]\n";
    cout << "Total matches: " << matches.size() << endl;
    
    return 0;
}
