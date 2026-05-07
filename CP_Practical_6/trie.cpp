#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Trie Node Structure
struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;
    
    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    // Insert a word into the trie
    void insert(string word) {
        TrieNode* node = root;
        
        for (char ch : word) {
            int index = ch - 'a';
            
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
        cout << "Inserted: " << word << endl;
    }
    
    // Search for a word in the trie
    bool search(string word) {
        TrieNode* node = root;
        
        for (char ch : word) {
            int index = ch - 'a';
            
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return node->isEndOfWord;
    }
    
    // Check if there is any word in the trie that starts with the given prefix
    bool startsWith(string prefix) {
        TrieNode* node = root;
        
        for (char ch : prefix) {
            int index = ch - 'a';
            
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }
    
    // Helper function for delete
    bool deleteHelper(TrieNode* node, string word, int index) {
        if (index == (int)word.length()) {
            if (!node->isEndOfWord) {
                return false;  // Word does not exist
            }
            node->isEndOfWord = false;
            
            // If node has children, it's not safe to delete this node
            for (int i = 0; i < 26; i++) {
                if (node->children[i] != nullptr) {
                    return false;
                }
            }
            return true;  // Node can be safely deleted
        }
        
        char ch = word[index];
        int childIndex = ch - 'a';
        TrieNode* childNode = node->children[childIndex];
        
        if (childNode == nullptr) {
            return false;  // Word doesn't exist
        }
        
        bool shouldDeleteChild = deleteHelper(childNode, word, index + 1);
        
        if (shouldDeleteChild) {
            delete childNode;
            node->children[childIndex] = nullptr;
            
            // Current node can be deleted if it has no other children and is not end of another word
            if (!node->isEndOfWord) {
                for (int i = 0; i < 26; i++) {
                    if (node->children[i] != nullptr) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        return false;
    }
    
    // Delete a word from the trie
    bool deleteWord(string word) {
        bool result = deleteHelper(root, word, 0);
        if (result) {
            cout << "Deleted: " << word << endl;
        } else {
            cout << "Could not delete: " << word << " (not found or has common prefix)" << endl;
        }
        return result;
    }
    
    // Display all words in the trie (DFS traversal)
    void displayAll() {
        cout << "\nAll words in Trie: ";
        string currentWord = "";
        displayHelper(root, currentWord);
        cout << endl;
    }
    
private:
    void displayHelper(TrieNode* node, string& currentWord) {
        if (node->isEndOfWord) {
            cout << currentWord << " ";
        }
        
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                currentWord += char('a' + i);
                displayHelper(node->children[i], currentWord);
                currentWord.pop_back();
            }
        }
    }
};

int main() {
    cout << "===== TRIE IMPLEMENTATION =====" << endl;
    cout << "\n--- TRIE DATA STRUCTURE ---" << endl;
    cout << "A Trie is a tree-like data structure for storing strings." << endl;
    cout << "Time Complexity:" << endl;
    cout << "  Insert: O(m) where m is length of word" << endl;
    cout << "  Search: O(m)" << endl;
    cout << "  Delete: O(m)" << endl << endl;
    
    Trie trie;
    
    // Test Insert Operation
    cout << "\n[INSERT OPERATION]" << endl;
    trie.insert("hello");
    trie.insert("world");
    trie.insert("help");
    trie.insert("hero");
    trie.insert("heap");
    
    trie.displayAll();
    
    // Test Search Operation
    cout << "\n[SEARCH OPERATION]" << endl;
    vector<string> searchWords = {"hello", "world", "help", "hel", "xyz"};
    for (const string& word : searchWords) {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }
    
    // Test Prefix Search
    cout << "\n[PREFIX SEARCH]" << endl;
    vector<string> prefixes = {"he", "wo", "he", "xyz"};
    for (const string& prefix : prefixes) {
        bool found = trie.startsWith(prefix);
        cout << "Prefix '" << prefix << "' exists: " << (found ? "YES" : "NO") << endl;
    }
    
    // Test Delete Operation
    cout << "\n[DELETE OPERATION]" << endl;
    trie.deleteWord("help");
    trie.deleteWord("hero");
    trie.deleteWord("notexist");
    
    trie.displayAll();
    
    // Verify deletions
    cout << "\n[VERIFY AFTER DELETION]" << endl;
    cout << "Search 'help': " << (trie.search("help") ? "FOUND" : "NOT FOUND") << endl;
    cout << "Search 'hero': " << (trie.search("hero") ? "FOUND" : "NOT FOUND") << endl;
    cout << "Search 'hello': " << (trie.search("hello") ? "FOUND" : "NOT FOUND") << endl;
    cout << "Search 'heap': " << (trie.search("heap") ? "FOUND" : "NOT FOUND") << endl;
    
    return 0;
}
