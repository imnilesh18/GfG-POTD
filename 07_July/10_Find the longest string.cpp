/*
 * GfG Link: https://www.geeksforgeeks.org/problems/find-the-longest-string--170645/1
 *
 * Find the longest string
 *
 * Difficulty: Medium Accuracy: 56.04% Submissions: 21K+ Points: 4
 *
 * Given an array of strings arr[]. Find the longest string in arr[] such that every prefix of it is also present in the array arr[].
 *
 * Note: If multiple strings have the same maximum length, return the lexicographically smallest one.
 *
 * Examples:
 *
 * Input: arr[] = ["p", "pr", "pro", "probl", "problem", "pros", "process", "processor"]
 * Output: pros
 * Explanation: "pros" is the longest word with all prefixes ("p", "pr", "pro", "pros") present in the array arr[].
 *
 * Input: arr[] = ["ab", "a", "abc", "abd"]
 * Output: abc
 * Explanation: Both "abc" and "abd" has all the prefixes in arr[]. Since, "abc" is lexicographically smaller than "abd", so the output is "abc".
 *
 * Constraints:
 * 1 ≤ arr.length() ≤ 10^3
 * 1 ≤ arr[i].length ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach: Build a Trie of all words, then for each word ensure every prefix is marked as an end‐of‐word in the Trie, keeping track of the longest valid word (breaking ties lexicographically).
// Time Complexity: O(N * L) where N = number of words and L = average word length, since we insert and search each word in O(L).
// Space Complexity: O(N * L) for storing up to N words of length L in the Trie.
class Solution {
public:

    struct TrieNode {
        bool      isEndOfWord;
        TrieNode* children[26];

        TrieNode() {
            isEndOfWord = false;
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
        }
    };

    TrieNode* root = new TrieNode();

    // Insert a word into the Trie
    void insert(string& word) {
        TrieNode* crawler = root;

        for (char c : word) {
            int index = c - 'a';
            if (crawler->children[index] == nullptr) {
                crawler->children[index] = new TrieNode();
            }
            crawler = crawler->children[index];
        }
        crawler->isEndOfWord = true; // mark end of this word
    }
    
    // Return true if all prefixes of word exist and are ends of words
    bool search(string& word) {
        TrieNode* crawler = root;

        for (char c : word) {
            int index = c - 'a';
            crawler = crawler->children[index];
            if (crawler == nullptr || crawler->isEndOfWord == false) {
                return false; // missing prefix or prefix not a completed word
            }
        }
        return true;
    }

    string longestString(vector<string>& arr) {
        // build Trie
        for (string& word : arr) {
            insert(word);
        }

        string result = "";
        // check each word
        for (string& word : arr) {
            if (search(word)) {
                // choose longer or lexicographically smaller on tie
                if (word.length() > result.length() ||
                    (word.length() == result.length() && word < result)) {
                    result = word;
                }
            }
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example 1:
 * Input: arr = ["p", "pr", "pro", "probl", "problem", "pros", "process", "processor"]
 *
 * 1. Insert all words into Trie, marking endOfWord at each complete word node.
 * 2. Initialize result = "".
 * 3. For each word in arr:
 *    - "p": search sees 'p'→isEnd=true → valid → result = "p"
 *    - "pr": 'p'(end)→'r'(end) → valid → length 2 > 1 → result = "pr"
 *    - "pro": 'p'→'r'→'o'(end) → valid → length 3 > 2 → result = "pro"
 *    - "probl": prefixes "p","pr","pro","prob","probl"? "prob" missing → invalid
 *    - "problem": prefix "probl" was invalid → invalid
 *    - "pros": 'p'→'r'→'o'→'s'(end) → valid → length 4 > 3 → result = "pros"
 *    - "process": prefix "proce"? "proce" missing → invalid
 *    - "processor": prefix "process" invalid → invalid
 * 4. Return "pros".
 *
 * Output: "pros"
 */

/*
 *
 * Dry Run
 *
 * Example 2:
 * Input: arr = ["ab", "a", "abc", "abd"]
 *
 * 1. Insert all words into Trie.
 * 2. result = "".
 * 3. For each word:
 *    - "ab": 'a'→'b'(end) valid → result = "ab"
 *    - "a": 'a'(end) valid → length 1 < 2 → ignore
 *    - "abc": 'a'→'b'→'c'(end) valid → length 3 > 2 → result = "abc"
 *    - "abd": 'a'→'b'→'d'(end) valid → length 3 == 3, but "abd" > "abc" lex → ignore
 * 4. Return "abc".
 *
 * Output: "abc"
 */

/************************************************************ JAVA ************************************************/

// Approach: Build a Trie of all words, then for each word ensure every prefix is marked as an end‐of‐word in the Trie, keeping track of the longest valid word (breaking ties lexicographically).
// Time Complexity: O(N * L) where N = number of words and L = average word length, since we insert and search each word in O(L).
// Space Complexity: O(N * L) for storing up to N words of length L in the Trie.
class Solution {
    // Trie node definition
    class TrieNode {
        boolean isEndOfWord;
        TrieNode[] children = new TrieNode[26];

        TrieNode() {
            isEndOfWord = false;
            for (int i = 0; i < 26; i++) {
                children[i] = null;
            }
        }
    }

    private TrieNode root = new TrieNode();

    // Insert a word into the Trie
    private void insert(String word) {
        TrieNode crawler = root;

        for (char c : word.toCharArray()) {
            int index = c - 'a';
            if (crawler.children[index] == null) {
                crawler.children[index] = new TrieNode();
            }
            crawler = crawler.children[index];
        }
        crawler.isEndOfWord = true; // mark end of this word
    }

    // Return true if all prefixes of word exist and are ends of words
    private boolean search(String word) {
        TrieNode crawler = root;

        for (char c : word.toCharArray()) {
            int index = c - 'a';
            crawler = crawler.children[index];
            if (crawler == null || !crawler.isEndOfWord) {
                return false; // missing prefix or prefix not a completed word
            }
        }
        return true;
    }
    
    public String longestString(String[] arr) {
        // build Trie
        for (String word : arr) {
            insert(word);
        }

        String result = "";
        // check each word
        for (String word : arr) {
            if (search(word)) {
                // choose longer or lexicographically smaller on tie
                if (word.length() > result.length() ||
                    (word.length() == result.length() && word.compareTo(result) < 0)) {
                    result = word;
                }
            }
        }
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Example 1:
 * Input: arr = ["p", "pr", "pro", "probl", "problem", "pros", "process", "processor"]
 *
 * 1. Insert all words into Trie, marking endOfWord at each complete word node.
 * 2. Initialize result = "".
 * 3. For each word in arr:
 *    - "p": search sees 'p'→isEnd=true → valid → result = "p"
 *    - "pr": 'p'(end)→'r'(end) → valid → length 2 > 1 → result = "pr"
 *    - "pro": 'p'→'r'→'o'(end) → valid → length 3 > 2 → result = "pro"
 *    - "probl": prefixes "p","pr","pro","prob","probl"? "prob" missing → invalid
 *    - "problem": prefix "probl" was invalid → invalid
 *    - "pros": 'p'→'r'→'o'→'s'(end) → valid → length 4 > 3 → result = "pros"
 *    - "process": prefix "proce"? "proce" missing → invalid
 *    - "processor": prefix "process" invalid → invalid
 * 4. Return "pros".
 *
 * Output: "pros"
 */

/*
 *
 * Dry Run
 *
 * Example 2:
 * Input: arr = ["ab", "a", "abc", "abd"]
 *
 * 1. Insert all words into Trie.
 * 2. result = "".
 * 3. For each word:
 *    - "ab": 'a'→'b'(end) valid → result = "ab"
 *    - "a": 'a'(end) valid → length 1 < 2 → ignore
 *    - "abc": 'a'→'b'→'c'(end) valid → length 3 > 2 → result = "abc"
 *    - "abd": 'a'→'b'→'d'(end) valid → length 3 == 3, but "abd" > "abc" lex → ignore
 * 4. Return "abc".
 *
 * Output: "abc"
 */
