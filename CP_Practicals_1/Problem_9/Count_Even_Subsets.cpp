#include <bits/stdc++.h>

using namespace std;

/*
 * Count Subsets with Even Sum using Bitmasking
 * 
 * Approach:
 * 1. Generate all 2^N subsets using bitmask from 0 to 2^N - 1
 * 2. For each bitmask, calculate the sum of elements in that subset
 * 3. If sum is even, increment the count
 * 4. Return the total count
 */

int countSubsetsWithEvenSum(vector<int>& arr, int n) {
    int count = 0;
    
    // Generate all 2^n subsets
    int totalSubsets = 1 << n;  // 2^n
    
    for (int mask = 0; mask < totalSubsets; mask++) {
        int sum = 0;
        
        // For each bit position, check if it's set
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += arr[i];
            }
        }
        
        // Check if sum is even
        if (sum % 2 == 0) {
            count++;
        }
    }
    
    return count;
}

int main() {
    int n;
    cout << "Enter the number of elements (N): ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter " << n << " numbers: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int result = countSubsetsWithEvenSum(arr, n);
    cout << "\nNumber of subsets with even sum: " << result << endl;
    
    return 0;
}
