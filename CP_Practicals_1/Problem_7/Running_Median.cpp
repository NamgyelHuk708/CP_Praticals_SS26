#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'runningMedian' function below.
 *
 * The function is expected to return a DOUBLE_ARRAY.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

vector<double> runningMedian(vector<int> a) {
    vector<double> medians;
    priority_queue<int> maxHeap;                    // Max heap for left half
    priority_queue<int, vector<int>, greater<int>> minHeap;  // Min heap for right half
    
    for (int num : a) {
        // Add to maxHeap first
        maxHeap.push(num);
        
        // Ensure every element in maxHeap is <= every element in minHeap
        if (!maxHeap.empty() && !minHeap.empty() && maxHeap.top() > minHeap.top()) {
            int maxHeapTop = maxHeap.top();
            maxHeap.pop();
            minHeap.push(maxHeapTop);
            
            int minHeapTop = minHeap.top();
            minHeap.pop();
            maxHeap.push(minHeapTop);
        }
        
        // Balance the heaps: maxHeap should have either same size or one more element
        if (maxHeap.size() > minHeap.size() + 1) {
            int maxHeapTop = maxHeap.top();
            maxHeap.pop();
            minHeap.push(maxHeapTop);
        } else if (minHeap.size() > maxHeap.size()) {
            int minHeapTop = minHeap.top();
            minHeap.pop();
            maxHeap.push(minHeapTop);
        }
        
        // Calculate median
        double median;
        if (maxHeap.size() == minHeap.size()) {
            // Even number of elements
            median = (maxHeap.top() + minHeap.top()) / 2.0;
        } else {
            // Odd number of elements
            median = maxHeap.top();
        }
        
        medians.push_back(median);
    }
    
    return medians;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string a_count_temp;
    getline(cin, a_count_temp);

    int a_count = stoi(ltrim(rtrim(a_count_temp)));

    vector<int> a(a_count);

    for (int i = 0; i < a_count; i++) {
        string a_item_temp;
        getline(cin, a_item_temp);

        int a_item = stoi(ltrim(rtrim(a_item_temp)));

        a[i] = a_item;
    }

    vector<double> result = runningMedian(a);

    for (size_t i = 0; i < result.size(); i++) {
        fout << fixed << setprecision(1) << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
