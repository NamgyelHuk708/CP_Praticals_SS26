#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    int pages[7];
    for (int i = 0; i < 7; i++) {
        cin >> pages[i];
    }
    
    int total_read = 0;
    int day = 0;  // 0 = Monday, 1 = Tuesday, ..., 6 = Sunday
    
    // Keep reading until we finish the book
    while (total_read < n) {
        total_read += pages[day];
        if (total_read >= n) {
            // Finished on this day
            cout << (day + 1) << endl;  // Convert to 1-indexed
            break;
        }
        day = (day + 1) % 7;  
    }
    
    return 0;
}
