#include <bits/stdc++.h>

using namespace std;

/*
 * Count Subsets with Sum Equal to Target using Dynamic Programming (Tabulation)
 * 
 * Approach:
 * 1. Create a 2D DP table where dp[i][j] = number of subsets of arr[0...i-1] with sum j
 * 2. Base case: dp[0][0] = 1 (one way to get sum 0 - empty subset)
 * 3. For each element and sum value:
 *    - Exclude current element: dp[i-1][j]
 *    - Include current element: dp[i-1][j-arr[i-1]] (if j >= arr[i-1])
 * 4. Return dp[n][target]
 */

int perfectSum(vector<int>& arr, int target) {
    int n = arr.size();
    
    // Create a 2D DP table
    // dp[i][j] = number of ways to achieve sum j using first i elements
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
    
    // Base case: There's exactly one way to achieve sum 0 (by selecting no elements)
    dp[0][0] = 1;
    
    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            // Case 1: Exclude the current element
            dp[i][j] = dp[i - 1][j];
            
            // Case 2: Include the current element (if possible)
            if (j >= arr[i - 1]) {
                dp[i][j] += dp[i - 1][j - arr[i - 1]];
            }
        }
    }
    
    // Return the number of ways to achieve the target sum
    return dp[n][target];
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
    
    int target;
    cout << "Enter the target sum: ";
    cin >> target;
    
    int result = perfectSum(arr, target);
    cout << "\nNumber of subsets with sum equal to " << target << ": " << result << endl;
    
    return 0;
}
