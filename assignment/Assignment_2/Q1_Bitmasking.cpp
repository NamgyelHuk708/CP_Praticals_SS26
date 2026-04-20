// Assignment 2 - Question 1: Bitmasking
// - Generate ALL subsets of a set using bitmasks
// - Count subsets whose sum is divisible by K

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cout << "Enter N (number of integers, max 20): ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    int K;
    cout << "Enter K: ";
    cin >> K;

    int totalSubsets = (1 << n);  // 2^N subsets
    int count = 0;                // Count of subsets with sum % K == 0

    cout << "\nAll subsets and their sums:" << endl;
    cout << "------------------------------------" << endl;

    for (int mask = 0; mask < totalSubsets; mask++) {
        vector<int> subset;
        int sum = 0;

        // Check each bit of the mask
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subset.push_back(arr[i]);
                sum += arr[i];
            }
        }

        // Print subset
        cout << "{ ";
        if (subset.empty()) {
            cout << "(empty)";
        } else {
            for (int i = 0; i < (int)subset.size(); i++) {
                cout << subset[i];
                if (i + 1 < (int)subset.size()) cout << ", ";
            }
        }
        cout << " }  →  sum = " << sum;

        // Check divisibility
        if (sum % K == 0) {
            cout << "  ✓ divisible by " << K;
            count++;
        }
        cout << endl;
    }

    cout << "------------------------------------" << endl;
    cout << "Total subsets:                  " << totalSubsets << endl;
    cout << "Subsets with sum divisible by " << K << ": " << count << endl;

    return 0;
}

/*
────────────────────────────────────────────────────────────
HOW BITMASKING WORKS:
  For N elements, we iterate mask from 0 to (2^N - 1).
  Each mask is an N-bit binary number.
  If bit i is set in mask → element arr[i] is in the subset.

  Example: N=3, arr={1,2,3}
    mask=0 (000) → {}
    mask=1 (001) → {1}
    mask=2 (010) → {2}
    mask=3 (011) → {1,2}
    mask=4 (100) → {3}
    mask=5 (101) → {1,3}
    mask=6 (110) → {2,3}
    mask=7 (111) → {1,2,3}

Time Complexity: O(2^N × N)
Space Complexity: O(N)
────────────────────────────────────────────────────────────

SAMPLE INPUT:
N = 4
arr = {1, 2, 3, 4}
K = 3

SAMPLE OUTPUT (excerpt):
{}              → sum = 0   ✓ divisible by 3
{3}             → sum = 3   ✓ divisible by 3
{1,2}           → sum = 3   ✓ divisible by 3
{2,4}           → sum = 6   ✓ divisible by 3
{1,2,3}         → sum = 6   ✓ divisible by 3
{3,4}           → sum = 7
{1,2,3,4}       → sum = 10
...
────────────────────────────────────────────────────────────
*/
