#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class ManachersAlgorithm {
private:
    string text;
    string expanded;
    vector<int> palindromeLength;
    
public:
    ManachersAlgorithm(string s) {
        text = s;
        expandText();
    }
    
    // Expand text by adding '#' between characters
    // This handles both odd and even length palindromes
    void expandText() {
        expanded = "#";
        for (char ch : text) {
            expanded += ch;
            expanded += "#";
        }
    }
    
    // Manacher's Algorithm - Find all palindromic substrings
    void findPalindromes() {
        int n = expanded.length();
        palindromeLength.resize(n, 0);
        
        int center = 0;      // Center of the rightmost palindrome found
        int right = 0;       // Right boundary of the rightmost palindrome found
        
        cout << "\nExpanded String: " << expanded << endl;
        cout << "\nManacher's Algorithm Execution:" << endl;
        cout << "Looking for palindromes in: " << text << endl << endl;
        
        for (int i = 0; i < n; i++) {
            // Mirror of i with respect to center
            int mirror = 2 * center - i;
            
            // If i is within the right boundary, use previously computed values
            if (i < right) {
                palindromeLength[i] = min(right - i, palindromeLength[mirror]);
            }
            
            // Try to expand palindrome centered at i
            try {
                while (i + palindromeLength[i] + 1 < n &&
                       i - palindromeLength[i] - 1 >= 0 &&
                       expanded[i + palindromeLength[i] + 1] == 
                       expanded[i - palindromeLength[i] - 1]) {
                    palindromeLength[i]++;
                }
            } catch (...) {
                // Handle boundary cases
            }
            
            // If palindrome centered at i extends past right, adjust center and right
            if (i + palindromeLength[i] > right) {
                center = i;
                right = i + palindromeLength[i];
            }
        }
    }
    
    // Display all palindromic substrings
    void displayPalindromes() {
        cout << "\n[PALINDROMIC SUBSTRINGS FOUND]" << endl;
        vector<string> palindromes;
        int n = expanded.length();
        
        for (int i = 0; i < n; i++) {
            if (palindromeLength[i] > 0) {
                // Extract substring from original text
                // Position in expanded = position in original * 2 + 1
                int origPos = (i - 1) / 2;
                int len = palindromeLength[i];
                
                if (origPos >= 0 && origPos < text.length()) {
                    string palindrome = text.substr(origPos, len);
                    
                    // Verify it's actually a palindrome
                    string rev = palindrome;
                    reverse(rev.begin(), rev.end());
                    
                    if (palindrome == rev && palindrome.length() > 0) {
                        palindromes.push_back(palindrome);
                    }
                }
            }
        }
        
        // Remove duplicates
        sort(palindromes.begin(), palindromes.end());
        palindromes.erase(unique(palindromes.begin(), palindromes.end()), 
                         palindromes.end());
        
        cout << "Unique palindromic substrings found: " << palindromes.size() << endl;
        for (const string& p : palindromes) {
            cout << "  - " << p << endl;
        }
    }
    
    // Find longest palindromic substring
    string getLongestPalindrome() {
        string longest = "";
        int maxLen = 0;
        
        for (int i = 0; i < expanded.length(); i++) {
            // Remove the '#' to get actual length
            int actualLen = palindromeLength[i];
            
            if (actualLen > maxLen) {
                maxLen = actualLen;
                // Extract from original text
                int start = (i - palindromeLength[i]) / 2;
                longest = text.substr(start, actualLen);
            }
        }
        
        return longest;
    }
    
    // Get palindrome length at each position
    void displayPalindromeLengths() {
        cout << "\nPalindrome radius at each position:" << endl;
        cout << "Expanded: ";
        for (char ch : expanded) cout << ch << " ";
        cout << endl;
        
        cout << "Lengths:  ";
        for (int len : palindromeLength) cout << len << " ";
        cout << endl;
    }
};

// Brute force approach for comparison
class BruteForcePalindrome {
public:
    static bool isPalindrome(const string& s) {
        int n = s.length();
        for (int i = 0; i < n / 2; i++) {
            if (s[i] != s[n - 1 - i]) {
                return false;
            }
        }
        return true;
    }
    
    static vector<string> findAllPalindromes(const string& text) {
        vector<string> palindromes;
        int n = text.length();
        
        for (int i = 0; i < n; i++) {
            for (int len = 1; len <= n - i; len++) {
                string sub = text.substr(i, len);
                if (isPalindrome(sub)) {
                    palindromes.push_back(sub);
                }
            }
        }
        
        // Remove duplicates
        sort(palindromes.begin(), palindromes.end());
        palindromes.erase(unique(palindromes.begin(), palindromes.end()), 
                         palindromes.end());
        
        return palindromes;
    }
};

int main() {
    cout << "===== MANACHER'S ALGORITHM IMPLEMENTATION =====" << endl;
    cout << "\n--- MANACHER'S ALGORITHM ---" << endl;
    cout << "Manacher's Algorithm efficiently finds all palindromic substrings in linear time." << endl;
    cout << "Time Complexity: O(n)" << endl;
    cout << "Space Complexity: O(n)" << endl;
    cout << "Key Idea: Avoid rechecking characters by using symmetry properties." << endl << endl;
    
    // Test cases
    vector<string> testCases = {"racecar", "bananas", "abba", "abcdefg", "aabaa"};
    
    for (const string& testStr : testCases) {
        cout << "\n" << string(60, '=') << endl;
        cout << "Test Case: \"" << testStr << "\"" << endl;
        cout << string(60, '=') << endl;
        
        ManachersAlgorithm manacher(testStr);
        manacher.findPalindromes();
        manacher.displayPalindromeLengths();
        manacher.displayPalindromes();
        
        cout << "\nLongest Palindrome: \"" << manacher.getLongestPalindrome() << "\"" << endl;
        
        // Compare with brute force
        cout << "\n[COMPARISON WITH BRUTE FORCE]" << endl;
        vector<string> bruteForcePalindromes = BruteForcePalindrome::findAllPalindromes(testStr);
        cout << "Brute Force found " << bruteForcePalindromes.size() << " unique palindromes" << endl;
    }
    
    // Additional detailed example
    cout << "\n\n" << string(60, '=') << endl;
    cout << "DETAILED EXAMPLE: \"babad\"" << endl;
    cout << string(60, '=') << endl;
    
    string example = "babad";
    ManachersAlgorithm detailed(example);
    
    cout << "\nStep-by-step explanation for: " << example << endl;
    cout << "Original:  b a b a d" << endl;
    cout << "Expanded:  # b # a # b # a # d #" << endl;
    cout << "Positions: 0 1 2 3 4 5 6 7 8 9 10 11" << endl;
    
    detailed.findPalindromes();
    detailed.displayPalindromeLengths();
    detailed.displayPalindromes();
    
    cout << "\nLongest Palindrome: \"" << detailed.getLongestPalindrome() << "\"" << endl;
    
    return 0;
}
