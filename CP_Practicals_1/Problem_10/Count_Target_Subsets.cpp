#include <bits/stdc++.h>

using namespace std;

/*
 * Count Subsets with Sum Equal to Target using Dynamic Programming
 * 
 * Approach: Tabulation (Bottom-up DP)
 * - Create a 2D DP table where dp[i][j] = number of subsets from first i elements with sum j
 * - dp[0][0] = 1 (empty subset has sum 0)
 * - For each element, we either include it or exclude it
 * - Time: O(n*target), Space: O(n*target)
 */

int perfectSum(vector<int>& arr, int target) {
    int n = arr.size();
    
    // Create a 2D DP table
    // dp[i][j] = number of subsets using first i elements with sum j
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
    
    // Base case: empty subset has sum 0
    dp[0][0] = 1;
    
    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            // Case 1: Exclude current element
            dp[i][j] = dp[i - 1][j];
            
            // Case 2: Include current element (if possible)
            if (j >= arr[i - 1]) {
                dp[i][j] += dp[i - 1][j - arr[i - 1]];
            }
        }
    }
    
    return dp[n][target];
}

int main() {
    int n, target;
    
    cout << "Enter the number of elements: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "Enter the target sum: ";
    cin >> target;
    
    int result = perfectSum(arr, target);
    cout << "\nNumber of subsets with sum equal to " << target << ": " << result << endl;
    
    return 0;
}
