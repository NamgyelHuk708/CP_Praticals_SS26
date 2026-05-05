#include <iostream>
#include <string>
#include <vector>
using namespace std;

// PATRICIA Tree (Practical Algorithm to Retrieve Information Coded in Alphanumeric) Node
struct PATRICIANode {
    bool isLeaf;
    int edgeLabel;           // Edge label bit position for internal node
    string edgeString;       // Edge string for internal node
    PATRICIANode* left;      // Child for bit 0 (or false)
    PATRICIANode* right;     // Child for bit 1 (or true)
    string value;            // Value stored in leaf node
    
    PATRICIANode(bool leaf = false) {
        isLeaf = leaf;
        edgeLabel = -1;
        left = nullptr;
        right = nullptr;
        value = "";
    }
};

class PATRICIA {
private:
    PATRICIANode* root;
    
    // Find bit at position
    int getBit(string& str, int position) {
        if (position < str.length()) {
            return (str[position / 8] >> (7 - (position % 8))) & 1;
        }
        return 0;
    }
    
    // Find the first bit position where two strings differ
    int findDifferenceBit(const string& str1, const string& str2) {
        int len = min(str1.length(), str2.length());
        for (int i = 0; i < len; i++) {
            if (str1[i] != str2[i]) {
                for (int bit = 7; bit >= 0; bit--) {
                    int bit1 = (str1[i] >> bit) & 1;
                    int bit2 = (str2[i] >> bit) & 1;
                    if (bit1 != bit2) {
                        return i * 8 + (7 - bit);
                    }
                }
            }
        }
        return len * 8;
    }
    
public:
    PATRICIA() {
        root = new PATRICIANode(false);
    }
    
    // Insert operation
    void insert(const string& key) {
        if (key.empty()) {
            cout << "Cannot insert empty string" << endl;
            return;
        }
        
        cout << "Inserting: " << key << endl;
        PATRICIANode* node = root;
        int position = 0;
        
        while (!node->isLeaf) {
            int bit = getBit(const_cast<string&>(key), node->edgeLabel);
            
            if (bit == 0) {
                if (node->left == nullptr) {
                    // Create new leaf
                    node->left = new PATRICIANode(true);
                    node->left->value = key;
                    return;
                }
                node = node->left;
            } else {
                if (node->right == nullptr) {
                    // Create new leaf
                    node->right = new PATRICIANode(true);
                    node->right->value = key;
                    return;
                }
                node = node->right;
            }
        }
    }
    
    // Search operation
    bool search(const string& key) {
        if (key.empty()) {
            return false;
        }
        
        PATRICIANode* node = root;
        
        while (!node->isLeaf) {
            int bit = getBit(const_cast<string&>(key), node->edgeLabel);
            
            if (bit == 0) {
                if (node->left == nullptr) {
                    return false;
                }
                node = node->left;
            } else {
                if (node->right == nullptr) {
                    return false;
                }
                node = node->right;
            }
        }
        
        return node->value == key;
    }
    
    // Delete operation
    bool deleteKey(const string& key) {
        cout << "Attempting to delete: " << key << endl;
        return deleteHelper(root, key, 0);
    }
    
private:
    bool deleteHelper(PATRICIANode* node, const string& key, PATRICIANode* parent) {
        if (node == nullptr) {
            return false;
        }
        
        if (node->isLeaf) {
            if (node->value == key) {
                cout << "Deleted: " << key << endl;
                return true;
            }
            return false;
        }
        
        int bit = getBit(const_cast<string&>(key), node->edgeLabel);
        PATRICIANode* child;
        PATRICIANode** childPtr;
        
        if (bit == 0) {
            child = node->left;
            childPtr = &(node->left);
        } else {
            child = node->right;
            childPtr = &(node->right);
        }
        
        if (child == nullptr) {
            return false;
        }
        
        if (deleteHelper(child, key, node)) {
            if (child->isLeaf) {
                *childPtr = nullptr;
            }
            return true;
        }
        
        return false;
    }
    
public:
    // Display all keys
    void displayAll() {
        cout << "\nAll keys in PATRICIA: ";
        displayHelper(root);
        cout << endl;
    }
    
private:
    void displayHelper(PATRICIANode* node) {
        if (node == nullptr) {
            return;
        }
        
        if (node->isLeaf) {
            cout << node->value << " ";
        } else {
            displayHelper(node->left);
            displayHelper(node->right);
        }
    }
};

// Simplified PATRICIA using string comparison
class SimplePATRICIA {
private:
    struct Node {
        bool isLeaf;
        string key;
        Node* children[256];  // For byte values
        
        Node(bool leaf = false) {
            isLeaf = leaf;
            for (int i = 0; i < 256; i++) {
                children[i] = nullptr;
            }
        }
    };
    
    Node* root;
    
public:
    SimplePATRICIA() {
        root = new Node();
    }
    
    void insert(const string& key) {
        cout << "Inserting: " << key << endl;
        Node* node = root;
        
        for (unsigned char ch : key) {
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Node();
            }
            node = node->children[ch];
        }
        
        node->isLeaf = true;
        node->key = key;
    }
    
    bool search(const string& key) {
        Node* node = root;
        
        for (unsigned char ch : key) {
            if (node->children[ch] == nullptr) {
                return false;
            }
            node = node->children[ch];
        }
        
        return node->isLeaf && node->key == key;
    }
    
    bool deleteKey(const string& key) {
        cout << "Attempting to delete: " << key << endl;
        if (search(key)) {
            Node* node = root;
            for (unsigned char ch : key) {
                node = node->children[ch];
            }
            node->isLeaf = false;
            cout << "Deleted: " << key << endl;
            return true;
        }
        cout << "Could not delete: " << key << " (not found)" << endl;
        return false;
    }
    
    void displayAll() {
        cout << "\nAll keys in PATRICIA: ";
        string current = "";
        displayHelper(root, current);
        cout << endl;
    }
    
private:
    void displayHelper(Node* node, string& current) {
        if (node == nullptr) {
            return;
        }
        
        if (node->isLeaf) {
            cout << node->key << " ";
        }
        
        for (int i = 0; i < 256; i++) {
            if (node->children[i] != nullptr) {
                current += (char)i;
                displayHelper(node->children[i], current);
                current.pop_back();
            }
        }
    }
};

int main() {
    cout << "===== PATRICIA TREE IMPLEMENTATION =====" << endl;
    cout << "\n--- PATRICIA (Practical Algorithm to Retrieve Information Coded in Alphanumeric) ---" << endl;
    cout << "PATRICIA is a compressed trie structure that stores only essential characters." << endl;
    cout << "Time Complexity:" << endl;
    cout << "  Insert: O(k) where k is key length" << endl;
    cout << "  Search: O(k)" << endl;
    cout << "  Delete: O(k)" << endl << endl;
    
    SimplePATRICIA patricia;
    
    // Test Insert Operation
    cout << "\n[INSERT OPERATION]" << endl;
    patricia.insert("apple");
    patricia.insert("application");
    patricia.insert("apply");
    patricia.insert("apt");
    patricia.insert("are");
    patricia.insert("area");
    
    patricia.displayAll();
    
    // Test Search Operation
    cout << "\n[SEARCH OPERATION]" << endl;
    vector<string> searchWords = {"apple", "application", "apply", "app", "area", "xyz"};
    for (const string& word : searchWords) {
        bool found = patricia.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }
    
    // Test Delete Operation
    cout << "\n[DELETE OPERATION]" << endl;
    patricia.deleteKey("apply");
    patricia.deleteKey("apt");
    patricia.deleteKey("notfound");
    
    patricia.displayAll();
    
    // Verify deletions
    cout << "\n[VERIFY AFTER DELETION]" << endl;
    cout << "Search 'apply': " << (patricia.search("apply") ? "FOUND" : "NOT FOUND") << endl;
    cout << "Search 'apt': " << (patricia.search("apt") ? "FOUND" : "NOT FOUND") << endl;
    cout << "Search 'apple': " << (patricia.search("apple") ? "FOUND" : "NOT FOUND") << endl;
    cout << "Search 'area': " << (patricia.search("area") ? "FOUND" : "NOT FOUND") << endl;
    
    return 0;
}
