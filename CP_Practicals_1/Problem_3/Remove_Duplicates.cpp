#include <iostream>
#include <vector>
#include <algorithm>

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
    
    // Sort the array first
    sort(arr.begin(), arr.end());
    
    // Print unique elements
    cout << "Unique elements: ";
    cout << arr[0];  // Print first element
    
    // Compare each element with the previous one
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[i - 1]) {
            cout << " " << arr[i];
        }
    }
    cout << endl;
    
    return 0;
}
