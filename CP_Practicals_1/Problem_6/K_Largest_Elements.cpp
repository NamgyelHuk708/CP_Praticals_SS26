#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, k;
    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter K (number of largest elements to find): ";
    cin >> k;
    
    priority_queue<int> maxHeap;  // Max heap by default
    
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        maxHeap.push(x);
    }
    
    cout << "The " << k << " largest elements are: ";
    
    // Extract K largest elements
    for (int i = 0; i < k && !maxHeap.empty(); i++) {
        cout << maxHeap.top();
        maxHeap.pop();
        if (i < k - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}
