#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    int n, k;
    cout << "Enter the size of array: ";
    cin >> n;
    cout << "Enter the window size: ";
    cin >> k;
    
    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    deque<int> dq;  // Store indices of useful elements
    vector<int> result;
    
    // Process first window
    for (int i = 0; i < k; i++) {
        // Remove smaller elements from the back
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    
    // The front of deque has the index of maximum of first window
    result.push_back(arr[dq.front()]);
    
    // Process remaining elements
    for (int i = k; i < n; i++) {
        // Remove elements outside the current window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Remove smaller elements from the back
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        result.push_back(arr[dq.front()]);
    }
    
    // Print the result
    cout << "Output: ";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}
