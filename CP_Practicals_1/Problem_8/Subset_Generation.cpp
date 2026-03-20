#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Total number of subsets = 2^n
    int totalSubsets = 1 << n;  // 2^n using bit shift
    
    cout << "All possible subsets:" << endl;
    
    // Iterate through all possible bitmasks from 0 to 2^n - 1
    for (int mask = 0; mask < totalSubsets; mask++) {
        cout << "{";
        
        // Check each bit in the mask
        for (int i = 0; i < n; i++) {
            // If i-th bit is set, include arr[i] in the subset
            if (mask & (1 << i)) {
                cout << arr[i];
                // Check if there are more elements to print
                bool hasMore = false;
                for (int j = i + 1; j < n; j++) {
                    if (mask & (1 << j)) {
                        hasMore = true;
                        break;
                    }
                }
                if (hasMore) cout << " ";
            }
        }
        
        cout << "}" << endl;
    }
    
    return 0;
}
