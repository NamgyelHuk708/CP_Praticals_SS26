#include <iostream>
#include <vector>      // For using vector (dynamic array)
#include <climits>     // For INT_MAX and INT_MIN
using namespace std;

int main() {
    // Step 1: Read the number of elements
    int N;
    cout << "Enter the number of elements: ";
    cin >> N;
    
    // Step 2: Create a dynamic array (vector) to store N integers
    vector<int> arr;
    
    // Step 3: Read N integers from user
    cout << "Enter " << N << " integers: " << endl;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        arr.push_back(num);  // Add the number to our vector
    }
    
    // Step 4: Find maximum and minimum elements
    // Start by assuming first element is both max and min
    int maximum = arr[0];
    int minimum = arr[0];
    
    // Loop through all elements to find actual max and min
    for (int i = 1; i < N; i++) {
        if (arr[i] > maximum) {
            maximum = arr[i];  // Found a bigger number
        }
        if (arr[i] < minimum) {
            minimum = arr[i];  // Found a smaller number
        }
    }
    
    // Step 5: Calculate sum of all elements
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += arr[i];  // Add each element to sum
    }
    
    // Step 6: Print the results
    cout << "\nResults:" << endl;
    cout << "Maximum element: " << maximum << endl;
    cout << "Minimum element: " << minimum << endl;
    cout << "Sum of elements: " << sum << endl;
    
    return 0;
}
