/*
 * GfG Link: https://www.geeksforgeeks.org/problems/cutting-binary-string1342/1
 *
 * Cutting Binary String
 *
 * Difficulty: Medium Accuracy: 49.71% Submissions: 37K+ Points: 4
 *
 * You are given a binary string s consisting only of characters '0' and '1'. Your task is to split this string into the minimum number of non-empty substrings such that:
 *
 * Each substring represents a power of 5 in decimal (e.g., 1, 5, 25, 125, ...).
 * No substring should have leading zeros.
 * Return the minimum number of such pieces the string can be divided into.
 * Note: If it is not possible to split the string in this way, return -1.
 *
 * Examples:
 *
 * Input: s = "101101101"
 * Output: 3
 * Explanation: The string can be split into three substrings: "101", "101", and "101", each of which is a power of 5 with no leading zeros.
 *
 * Input: s = "1111101"
 * Output: 1
 * Explanation: The string can be split into one binary string "1111101" which is 125 in decimal and a power of 5 with no leading zeros.
 *
 * Input: s = "00000"
 * Output: -1
 * Explanation: There is no substring that can be split into power of 5.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 30
 */

/************************************************************ C++ ************************************************/

// Approach: Use recursion with memoization to try all valid substrings starting from each index. Only consider substrings that are powers of 5 and have no leading zeros.
// Time Complexity: O(n^2), for each index we try all substrings ahead (up to n times) and memoize results.
// Space Complexity: O(n), for the dp memoization array.
class Solution {
public:

    // Helper function to check if a binary string represents a power of 5
    bool isPowerOf5(string s) {
        if (s.empty() || s[0] == '0') {
            return false;                           // Leading zeros not allowed or empty string
        }
        int num = 0;
        for (char c : s) {
            num = num * 2 + (c - '0'); // Convert binary to decimal
        }

        // Check if number is a power of 5
        while (num > 1) {
            if (num % 5 != 0) {
                return false;
            }
            num /= 5;
        }

        return num == 1; // Return true if number reduced to 1
    }

    // Recursive function with memoization to find minimum cuts
    int dfs(int i, string& s, vector<int>& dp) {
        if (i == s.size()) {
            return 0;                // Base case: reached end of string
        }
        if (dp[i] != -1) {
            return dp[i];  // Return already computed result
        }
        int ans = INT_MAX; // Initialize answer to max

        // Try all substrings starting from i
        for (int j = i; j < s.size(); ++j) {
            string substr = s.substr(i, j - i + 1); // Get substring from i to j

            // If substring is a valid power of 5
            if (isPowerOf5(substr)) {
                int nextCuts = dfs(j + 1, s, dp); // Recurse for remaining string
                if (nextCuts != -1) {
                    ans = min(ans, 1 + nextCuts); // 1 cut for current + cuts for remaining
                }
            }
        }

        // Store result in dp array
        return dp[i] = (ans == INT_MAX) ? -1 : ans;
    }

    // Main function to initiate dfs with memoization array
    int cuts(string s) {
        vector<int> dp(s.size(), -1); // Initialize dp array with -1

        return dfs(0, s, dp);         // Start recursion from index 0
    }
};

/*
 *
 * Dry Run
 * Input: s = "101101101"
 * Index 0:
 *  Substring "1" → 1 (Power of 5) ✅ → call dfs(1)
 *  Substring "10" → 2 ❌
 *  Substring "101" → 5 ✅ → call dfs(3)
 *    Index 3: Substring "1" → ✅ → dfs(4)
 *      Substring "0" → ❌
 *      Substring "10" → ✅ → dfs(6)
 *        Substring "1" → ✅ → dfs(7)
 *          Substring "0" → ❌
 *          Substring "10" → ✅ → dfs(9) → returns 0
 * Backtrack and add +1 at each level
 * Result: 3 cuts → "101", "101", "101"
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use recursion with memoization (top-down DP) to try all valid cuts starting at each index, only allowing substrings that are powers of 5 without leading zeros.
// Time Complexity: O(n^2), for each index we check all substrings up to n and memoize results.
// Space Complexity: O(n), for the memoization array.

class Solution {
    // Check if binary string is a power of 5
    private boolean isPowerOf5(String s) {
        if (s.length() == 0 || s.charAt(0) == '0') {
            return false;                                        // No leading zero or empty string
        }
        int num = 0;
        for (char c : s.toCharArray()) {
            num = num * 2 + (c - '0'); // Convert binary to decimal
        }

        // Check power of 5
        while (num > 1) {
            if (num % 5 != 0) {
                return false;
            }
            num /= 5;
        }

        return num == 1;
    }

    // Recursive function with memoization to find min cuts
    private int dfs(int i, String s, int[] dp) {
        if (i == s.length()) {
            return 0;                  // Reached end of string
        }
        if (dp[i] != -1) {
            return dp[i];              // Already computed
        }
        int ans = Integer.MAX_VALUE;

        for (int j = i; j < s.length(); j++) {
            String substr = s.substring(i, j + 1);

            if (isPowerOf5(substr)) {
                int nextCuts = dfs(j + 1, s, dp);
                if (nextCuts != -1) {
                    ans = Math.min(ans, 1 + nextCuts);
                }
            }
        }

        dp[i] = (ans == Integer.MAX_VALUE) ? -1 : ans;
        return dp[i];
    }
    
    public int cuts(String s) {
        int[] dp = new int[s.length()];

        Arrays.fill(dp, -1);
        return dfs(0, s, dp);
    }
}

/*
 *
 * Dry Run
 * Input: s = "101101101"
 * Start from index 0:
 * - "1" → 1 ✅ → dfs(1)
 * - "10" → 2 ❌
 * - "101" → 5 ✅ → dfs(3)
 *   At index 3:
 *   - "1" ✅ → dfs(4)
 *     - "0" ❌
 *     - "10" ✅ → dfs(6)
 *       - "1" ✅ → dfs(7)
 *         - "0" ❌
 *         - "10" ✅ → dfs(9) = 0
 * Return total cuts: 1 (101) + 1 (101) + 1 (101) = 3
 *
 */
