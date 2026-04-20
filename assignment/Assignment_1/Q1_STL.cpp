// Assignment 1 - Question 1: STL Usage in C++
// Topics: vector, deque, std::array

#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <numeric>      // for std::accumulate
#include <algorithm>    // for std::reverse_copy
#include <iterator>     // for std::ostream_iterator

using namespace std;

// ─────────────────────────────────────────────
// Part (a): vector - store N integers, print in reverse
// ─────────────────────────────────────────────
void part_a() {
    cout << "=== Part (a): Vector in Reverse ===" << endl;

    int n;
    cout << "Enter N: ";
    cin >> n;

    vector<int> vec(n);
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) cin >> vec[i];

    // Print in reverse using reverse iterators
    cout << "Reversed: ";
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
        cout << *it << " ";
    cout << endl;
}

// ─────────────────────────────────────────────
// Part (b): deque - push front, push back, pop front
// ─────────────────────────────────────────────
void part_b() {
    cout << "\n=== Part (b): Deque Operations ===" << endl;

    deque<int> dq;

    // Simulate a fixed sequence of operations
    // Format: 0 = push_back, 1 = push_front, 2 = pop_front
    vector<pair<int,int>> ops = {
        {0, 10},   // push_back  10  → [10]
        {0, 20},   // push_back  20  → [10, 20]
        {1, 5},    // push_front  5  → [5, 10, 20]
        {1, 1},    // push_front  1  → [1, 5, 10, 20]
        {2, -1},   // pop_front      → [5, 10, 20]
        {0, 30},   // push_back  30  → [5, 10, 20, 30]
        {2, -1},   // pop_front      → [10, 20, 30]
    };

    cout << "Operations performed:" << endl;
    for (auto& [op, val] : ops) {
        if (op == 0) {
            dq.push_back(val);
            cout << "  push_back(" << val << ")";
        } else if (op == 1) {
            dq.push_front(val);
            cout << "  push_front(" << val << ")";
        } else {
            if (!dq.empty()) {
                cout << "  pop_front() → removed " << dq.front();
                dq.pop_front();
            }
        }
        // Print current state
        cout << "  | deque: [";
        for (size_t i = 0; i < dq.size(); i++) {
            cout << dq[i];
            if (i + 1 < dq.size()) cout << ", ";
        }
        cout << "]" << endl;
    }

    cout << "Final deque contents: ";
    for (int x : dq) cout << x << " ";
    cout << endl;
}

// ─────────────────────────────────────────────
// Part (c): std::array - fixed size, compute sum
// ─────────────────────────────────────────────
void part_c() {
    cout << "\n=== Part (c): std::array Sum ===" << endl;

    const int SIZE = 6;
    array<int, SIZE> arr = {3, 7, 1, 9, 4, 6};

    cout << "Array contents: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Compute sum using std::accumulate (from <numeric>)
    int total = accumulate(arr.begin(), arr.end(), 0);
    cout << "Sum using std::accumulate: " << total << endl;
}

// ─────────────────────────────────────────────
int main() {
    part_a();
    part_b();
    part_c();
    return 0;
}

