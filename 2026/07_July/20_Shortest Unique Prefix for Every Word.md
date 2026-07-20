# 🔴 Shortest Unique Prefix for Every Word

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/shortest-unique-prefix-for-every-word/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)](https://www.geeksforgeeks.org/problems/shortest-unique-prefix-for-every-word/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-50.02%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/shortest-unique-prefix-for-every-word/1)
[![Points](https://img.shields.io/badge/Points-8-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/shortest-unique-prefix-for-every-word/1)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](#license)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array of strings `arr[]`, find the shortest prefix of each string that uniquely identifies it among all strings in the array. A prefix is unique if it is not a prefix of any other string in the array.

**Note:** No string in the given array is a prefix of another string.

---

## 💡 Examples

```text
Input: arr[] = ["zebra", "dog", "duck", "dove"]
Output: ["z", "dog", "du", "dov"]
```

<details>
<summary><b>📖 Example Breakdown</b></summary>
<br>

* **"zebra"**: The prefix `"z"` does not appear at the start of any other word.
* **"dog"**: `"d"` is shared with "duck" and "dove". `"do"` is shared with "dove". `"dog"` is unique.
* **"duck"**: `"d"` is shared. `"du"` is unique to "duck".
* **"dove"**: `"d"` is shared. `"do"` is shared. `"dov"` is unique to "dove".

</details>

```text
Input: arr[] = ["geeksgeeks", "geeksquiz", "geeksforgeeks"]
Output: ["geeksg", "geeksq", "geeksf"]
Explanation: 
geeksgeeks => geeksg
geeksquiz => geeksq
geeksforgeeks => geeksf
```

---

## ⚙️ Constraints

> * `1 ≤ |arr| ≤ 1000`
> * `1 ≤ |arr[i]| ≤ 1000`

---

## 🚀 Solution Approach

### Trie (Prefix Tree) Based Approach

A **Trie** is the optimal data structure for solving prefix-related string problems. By maintaining a frequency count at each node, we can track how many words pass through a particular character sequence. A node with a frequency of `1` indicates that the prefix ending at that character is unique to exactly one word.

```cpp
// Intuition: A Trie (Prefix Tree) is perfect for prefix-related problems. By keeping a frequency count at each node, we can identify the shortest unique prefix. When a node's count is 1, it means no other word shares this prefix.
// Approach:
// 1. Build a Trie where each node stores the frequency of its visits.
// 2. Insert all words from the array into the Trie, incrementing the visit count for each character node.
// 3. To find the shortest unique prefix for a word, traverse the Trie. Stop and return the prefix as soon as you hit a node with a frequency of 1.
// Time Complexity: O(N * M), where N is the number of words and M is the maximum length of a word. Inserting and searching take O(M) time per word.
// Space Complexity: O(N * M) auxiliary space for storing the Trie nodes.

// Trie Node structure
class TrieNode {
public:
    TrieNode* children[26];
    int count; // To keep track of how many words share this prefix
    
    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        count = 0;
    }
};

class Solution {
private:
    TrieNode* root;
    
    // Helper function to insert a word into the Trie
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            // Create a new node if it doesn't exist
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
            node->count++; // Increment frequency for this prefix node
        }
    }
    
    // Helper function to find the shortest unique prefix
    string getUniquePrefix(string word) {
        TrieNode* node = root;
        string prefix = "";
        for (char c : word) {
            int index = c - 'a';
            prefix += c;
            node = node->children[index];
            
            // If count is 1, this prefix is unique
            if (node->count == 1) {
                break;
            }
        }
        return prefix;
    }

public:
    vector<string> findPrefixes(vector<string>& arr) {
        root = new TrieNode();
        vector<string> result;
        
        // Step 1: Insert all words into the Trie
        for (string word : arr) {
            insert(word);
        }
        
        // Step 2: Find the shortest unique prefix for each word
        for (string word : arr) {
            result.push_back(getUniquePrefix(word));
        }
        
        return result;
    }
};

/*
*
* Dry Run
* Input: arr[] = ["zebra", "dog", "duck", "dove"]
* 
* Insert "zebra": 
* 'z'(1) -> 'e'(1) -> 'b'(1) -> 'r'(1) -> 'a'(1)
* 
* Insert "dog":
* 'd'(1) -> 'o'(1) -> 'g'(1)
* 
* Insert "duck":
* 'd'(2) -> 'u'(1) -> 'c'(1) -> 'k'(1)
* 
* Insert "dove":
* 'd'(3) -> 'o'(2) -> 'v'(1) -> 'e'(1)
* 
* Find Prefixes:
* "zebra": 'z' has count 1. Unique Prefix: "z"
* "dog": 'd' has count 3. 'o' has count 2. 'g' has count 1. Unique Prefix: "dog"
* "duck": 'd' has count 3. 'u' has count 1. Unique Prefix: "du"
* "dove": 'd' has count 3. 'o' has count 2. 'v' has count 1. Unique Prefix: "dov"
* 
* Output: ["z", "dog", "du", "dov"]
*
*/
```

---

## 🔑 Key Insights

* **Why Trie?** Generating all prefixes for every string and matching them against each other would result in a massive time complexity overhead. A Trie elegantly overlays shared prefixes, turning a computationally heavy lookup task into a simple node traversal operation based on frequency.
* **Frequency Threshold:** The moment a traversal encounters a character node holding `count == 1`, we are guaranteed that the branch stems off into a single string.

---

## 🌍 Further Exploration

If you enjoyed diving into Tries, consider practicing these similar concepts on GeeksforGeeks:
* Trie (Insert and Search)
* Longest Common Prefix using Trie
* Word Boggle (Trie + DFS)

---

## 🔗 References

* **GeeksforGeeks Problem:** [Shortest Unique Prefix for Every Word](https://www.geeksforgeeks.org/problems/shortest-unique-prefix-for-every-word/1)
* **Topics:** Trie, Advanced Data Structure, Strings

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

## 🏷️ Tags

`dynamic-programming` `LIS` `array` `geeksforgeeks` `trie` `advanced-data-structure`