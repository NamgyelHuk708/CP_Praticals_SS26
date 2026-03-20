#include <iostream>
#include <deque>
#include <string>

using namespace std;

void printDeque(deque<int>& dq) {
    if (dq.empty()) {
        cout << "Line is empty" << endl;
    } else {
        for (int i = 0; i < dq.size(); i++) {
            cout << dq[i];
            if (i < dq.size() - 1) cout << " ";
        }
        cout << endl;
    }
}

int main() {
    deque<int> line;
    int operations;
    
    cout << "Enter the number of operations: ";
    cin >> operations;
    
    for (int i = 0; i < operations; i++) {
        string operation;
        cout << "Operation " << i + 1 << ": ";
        cin >> operation;
        
        if (operation == "push_front") {
            int x;
            cin >> x;
            line.push_front(x);
            cout << "After push_front " << x << ": ";
            printDeque(line);
        }
        else if (operation == "push_back") {
            int x;
            cin >> x;
            line.push_back(x);
            cout << "After push_back " << x << ": ";
            printDeque(line);
        }
        else if (operation == "pop_front") {
            if (line.empty()) {
                cout << "Error: Line is empty, cannot pop_front" << endl;
            } else {
                int removed = line.front();
                line.pop_front();
                cout << "Removed " << removed << " from front: ";
                printDeque(line);
            }
        }
        else if (operation == "pop_back") {
            if (line.empty()) {
                cout << "Error: Line is empty, cannot pop_back" << endl;
            } else {
                int removed = line.back();
                line.pop_back();
                cout << "Removed " << removed << " from back: ";
                printDeque(line);
            }
        }
        else {
            cout << "Invalid operation!" << endl;
        }
    }
    
    return 0;
}
