/*
 * GfG Link: https://www.geeksforgeeks.org/problems/find-all-possible-palindromic-partitions-of-a-string/1
 *
 * Find all possible palindromic partitions of a String
 *
 * Difficulty: Medium Accuracy: 61.47% Submissions: 20K+ Points: 4 Average Time: 30m
 *
 * Given a string s, find all possible ways to partition it such that every substring in the partition is a palindrome.
 *
 * Examples:
 *
 * Input: s = "geeks"
 * Output: [[g, e, e, k, s], [g, ee, k, s]]
 * Explanation: [g, e, e, k, s] and [g, ee, k, s] are the only partitions of "geeks" where each substring is a palindrome.
 *
 * Input: s = "abcba"
 * Output: [[a, b, c, b, a], [a, bcb, a], [abcba]]
 * Explanation: [a, b, c, b, a], [a, bcb, a] and [abcba] are the only partitions of "abcba" where each substring is a palindrome.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 20
 */

/************************************************************ C++ ************************************************/

// Approach: Use recursive backtracking to explore all possible partitions. For each index, expand and include substrings that are palindromes, then recursively partition the rest.
// Time Complexity: O(2^n * n) – At each index, we make 2 choices (cut or not) and check for palindrome in O(n) time.
// Space Complexity: O(n) – for recursion stack and current path storage.
class Solution {
public:
    // Check if s[l..r] is a palindrome
    bool isPalindrome(string& s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r]) {
                return false; // Return false if characters at both ends don't match
            }
            l++;              // Move left pointer forward
            r--;              // Move right pointer backward
        }
        return true;          // All characters matched, hence it's a palindrome
    }

    // Recursive backtracking to explore all palindromic partitions
    void backtrack(int idx,
                   string& s,
                   vector<string>& curr,
                   vector<vector<string> >& result) {
        if (idx == s.size()) {
            result.push_back(curr); // Add current partition to result if end of string is reached
            return;
        }

        for (int i = idx; i < s.size(); i++) {
            // Check if s[idx..i] is a palindrome
            if (isPalindrome(s, idx, i)) {
                // If yes, add it to the current path
                curr.push_back(s.substr(idx, i - idx + 1));

                // Recurse for the remaining substring
                backtrack(i + 1, s, curr, result);

                // Backtrack: remove last added substring and try next possibility
                curr.pop_back();
            }
        }
    }

    // Entry function to initiate backtracking
    vector<vector<string> > palinParts(string& s) {
        vector<vector<string> > result; // Final result of all partitions
        vector<string>          curr;   // Current partition path

        backtrack(0, s, curr, result);  // Start from index 0
        return result;
    }
};

/*
 *
 * Dry Run
 * Input: s = "aab"
 *
 * Start: idx = 0, current = []
 *
 * 1. i = 0 → s[0..0] = "a" → palindrome
 * → current = ["a"]
 * → Recurse from idx = 1
 *
 * 2. i = 1 → s[1..1] = "a" → palindrome
 * → current = ["a", "a"]
 * → Recurse from idx = 2
 *
 * 3. i = 2 → s[2..2] = "b" → palindrome
 * → current = ["a", "a", "b"]
 * → Recurse from idx = 3 (end of string)
 * → Add to result: ["a", "a", "b"]
 * → Backtrack: remove "b" → current = ["a", "a"]
 *
 * Backtrack: remove "a" → current = ["a"]
 *
 * 4. i = 1 → s[1..2] = "ab" → not a palindrome → skip
 *
 * Backtrack: remove "a" → current = []
 *
 * 5. i = 0 → s[0..1] = "aa" → palindrome
 * → current = ["aa"]
 * → Recurse from idx = 2
 *
 * 6. i = 2 → s[2..2] = "b" → palindrome
 * → current = ["aa", "b"]
 * → Recurse from idx = 3 (end of string)
 * → Add to result: ["aa", "b"]
 * → Backtrack: remove "b" → current = ["aa"]
 *
 * Backtrack: remove "aa" → current = []
 *
 * 7. i = 0 → s[0..2] = "aab" → not a palindrome → skip
 *
 * Final result:
 * [
 * ["a", "a", "b"],
 * ["aa", "b"]
 * ]
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use recursive backtracking to explore all possible partitions. For each index, expand and include substrings that are palindromes, then recursively partition the rest.
// Time Complexity: O(2^n * n) – At each index, we make 2 choices (cut or not) and check for palindrome in O(n) time.
// Space Complexity: O(n) – for recursion stack and current path storage.
class Solution {
    // Function to check if a substring s[l..r] is a palindrome
    boolean isPalindrome(String s, int l, int r) {
        while (l < r) {
            if (s.charAt(l) != s.charAt(r)) {
                return false; // Return false if characters at both ends don't match
            }
            l++;              // Move left pointer forward
            r--;              // Move right pointer backward
        }
        return true;          // All characters matched, hence it's a palindrome
    }

    // Recursive backtracking to explore all palindromic partitions
    void backtrack(int idx,
                   String s,
                   ArrayList<String> curr,
                   ArrayList<ArrayList<String> > result) {
        if (idx == s.length()) {
            result.add(new ArrayList<>(curr)); // Add current partition to result if end of string is reached
            return;
        }

        for (int i = idx; i < s.length(); i++) {
            // Check if s[idx..i] is a palindrome
            if (isPalindrome(s, idx, i)) {
                // If yes, add it to the current path
                curr.add(s.substring(idx, i + 1));

                // Recurse for the remaining substring
                backtrack(i + 1, s, curr, result);

                // Backtrack: remove last added substring and try next possibility
                curr.remove(curr.size() - 1);
            }
        }
    }
    
    // Entry function to initiate backtracking
    public ArrayList<ArrayList<String> > palinParts(String s) {
        ArrayList<ArrayList<String> > result = new ArrayList<>(); // Final result of all partitions
        ArrayList<String>             curr   = new ArrayList<>(); // Current partition path

        backtrack(0, s, curr, result);                            // Start from index 0
        return result;
    }
}

/*
 *
 * Dry Run
 * Input: s = "aab"
 *
 * Start: idx = 0, current = []
 *
 * 1. i = 0 → s[0..0] = "a" → palindrome
 * → current = ["a"]
 * → Recurse from idx = 1
 *
 * 2. i = 1 → s[1..1] = "a" → palindrome
 * → current = ["a", "a"]
 * → Recurse from idx = 2
 *
 * 3. i = 2 → s[2..2] = "b" → palindrome
 * → current = ["a", "a", "b"]
 * → Recurse from idx = 3 (end of string)
 * → Add to result: ["a", "a", "b"]
 * → Backtrack: remove "b" → current = ["a", "a"]
 *
 * Backtrack: remove "a" → current = ["a"]
 *
 * 4. i = 1 → s[1..2] = "ab" → not a palindrome → skip
 *
 * Backtrack: remove "a" → current = []
 *
 * 5. i = 0 → s[0..1] = "aa" → palindrome
 * → current = ["aa"]
 * → Recurse from idx = 2
 *
 * 6. i = 2 → s[2..2] = "b" → palindrome
 * → current = ["aa", "b"]
 * → Recurse from idx = 3 (end of string)
 * → Add to result: ["aa", "b"]
 * → Backtrack: remove "b" → current = ["aa"]
 *
 * Backtrack: remove "aa" → current = []
 *
 * 7. i = 0 → s[0..2] = "aab" → not a palindrome → skip
 *
 * Final result:
 * [
 * ["a", "a", "b"],
 * ["aa", "b"]
 * ]
 *
 */
