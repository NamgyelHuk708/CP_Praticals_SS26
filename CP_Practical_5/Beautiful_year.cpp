#include <bits/stdc++.h>
using namespace std;

int main() {
    int y;
    cin >> y;
    
    // Start checking from the next year
    for (int year = y + 1; ; year++) {
        string s = to_string(year);
        
        // Check if all digits are distinct
        set<char> digits(s.begin(), s.end());
        
        // If the set size equals string length, all digits are unique
        if (digits.size() == s.length()) {
            cout << year << endl;
            break;
        }
    }
    
    return 0;
}