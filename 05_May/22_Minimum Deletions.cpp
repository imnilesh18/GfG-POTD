/*
 * GfG Link: https://www.geeksforgeeks.org/problems/minimum-deletitions1648/1
 *
 * Minimum Deletions
 *
 * Difficulty: Medium Accuracy: 58.8% Submissions: 57K+ Points: 4
 *
 * Given a string s, write a program to delete the minimum number of characters from the string so that the resultant string is a palindrome, while maintaining the order of characters.
 *
 * Examples:
 *
 * Input: s = "aebcbda"
 * Output: 2
 * Explanation: Remove characters 'e' and 'd'.
 *
 * Input: s = "geeksforgeeks"
 * Output: 8
 * Explanation: To make "geeksforgeeks" a palindrome, the longest palindromic subsequence is "eefee" (length 5). The minimum deletions are:
 * 13 (length of s) - 5 = 8.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach: Use top-down dynamic programming (memoization) to minimize deletions needed to convert the string into a palindrome. If characters at both ends match, move inward; otherwise, delete one character and recurse.
// Time Complexity: O(n^2) — There are O(n^2) subproblems and each subproblem takes O(1) time.
// Space Complexity: O(n^2) — Due to the DP array used for memoization.
class Solution {
public:

    int dp[1001][1001]; // Declare a memoization table to store results of subproblems

    // Recursive function to find minimum deletions to make s[i..j] a palindrome
    int solve(int i, int j, string& s) {
        // Base case: if left index crosses or meets right, it's already a palindrome
        if (i >= j) {
            return 0;
        }

        // Return cached result if already computed
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // If both characters match, no need to delete, move inward
        if (s[i] == s[j]) {
            return dp[i][j] = solve(i + 1, j - 1, s);
        }

        // Else, try deleting one character (either from start or end) and take min
        return dp[i][j] = 1 + min(solve(i + 1, j, s), solve(i, j - 1, s));
    }

    // Main function
    int minDeletions(string s) {
        int n = s.length();

        // Initialize dp array with -1 (uncomputed)
        memset(dp, -1, sizeof(dp));

        // Compute result for the full string
        return solve(0, n - 1, s);
    }
};

/*
 *
 * Dry Run
 *
 * Input: "aebcbda"
 *
 * Initial call: solve(0, 6)
 * Characters: s[0] = 'a', s[6] = 'a' → match → recurse inside
 * solve(1, 5)
 * Characters: s[1] = 'e', s[5] = 'd' → no match → try:
 *     solve(2, 5) and solve(1, 4)
 *
 * solve(2, 5) → s[2] = 'b', s[5] = 'd' → no match →
 *     solve(3, 5) and solve(2, 4)
 * solve(3, 5) → 'c' vs 'd' → no match →
 *     solve(4, 5) and solve(3, 4)
 * solve(4, 5) = 'b', 'd' → no match → returns 1
 * solve(3, 4) = 'c', 'b' → no match → returns 1
 * → dp[3][5] = 1 + min(1, 1) = 2
 *
 * solve(2, 4) = 'b', 'b' → match → solve(3, 3) = 0
 * → dp[2][4] = 0
 * → dp[2][5] = 1 + min(2, 0) = 1
 *
 * solve(1, 4) = 'e', 'b' → no match →
 *     solve(2, 4) = 0 and solve(1, 3) = 2 → dp[1][4] = 1
 *
 * dp[1][5] = 1 + min(1, 1) = 2
 *
 * dp[0][6] = dp[1][5] = 2 → Answer: 2
 *
 * You can delete 'e' and 'd' to make "abcba" which is a palindrome
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use top-down dynamic programming (memoization) to minimize deletions needed to convert the string into a palindrome. If characters at both ends match, move inward; otherwise, delete one character and recurse.
// Time Complexity: O(n^2) — There are O(n^2) subproblems and each subproblem takes O(1) time.
// Space Complexity: O(n^2) — Due to the DP array used for memoization.
class Solution {
    static int[][] dp; // Memoization table

    // Recursive function to find minimum deletions to make s[i..j] a palindrome
    static int solve(int i, int j, String s) {
        // Base case: if left index crosses or meets right, it's already a palindrome
        if (i >= j) {
            return 0;
        }

        // Return cached result if already computed
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // If both characters match, no need to delete, move inward
        if (s.charAt(i) == s.charAt(j)) {
            return dp[i][j] = solve(i + 1, j - 1, s);
        }

        // Else, try deleting one character (either from start or end) and take min
        return dp[i][j] = 1 + Math.min(solve(i + 1, j, s), solve(i, j - 1, s));
    }
    
    // Main function to be called
    static int minDeletions(String s) {
        int n = s.length();

        dp = new int[n][n];

        // Initialize dp array with -1 (uncomputed)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = -1;
            }
        }

        // Compute result for the full string
        return solve(0, n - 1, s);
    }
}

/*
 *
 * Dry Run
 *
 * Input: "aebcbda"
 *
 * Initial call: solve(0, 6)
 * Characters: s[0] = 'a', s[6] = 'a' → match → recurse inside
 * solve(1, 5)
 * Characters: s[1] = 'e', s[5] = 'd' → no match → try:
 *     solve(2, 5) and solve(1, 4)
 *
 * solve(2, 5) → s[2] = 'b', s[5] = 'd' → no match →
 *     solve(3, 5) and solve(2, 4)
 * solve(3, 5) → 'c' vs 'd' → no match →
 *     solve(4, 5) and solve(3, 4)
 * solve(4, 5) = 'b', 'd' → no match → returns 1
 * solve(3, 4) = 'c', 'b' → no match → returns 1
 * → dp[3][5] = 1 + min(1, 1) = 2
 *
 * solve(2, 4) = 'b', 'b' → match → solve(3, 3) = 0
 * → dp[2][4] = 0
 * → dp[2][5] = 1 + min(2, 0) = 1
 *
 * solve(1, 4) = 'e', 'b' → no match →
 *     solve(2, 4) = 0 and solve(1, 3) = 2 → dp[1][4] = 1
 *
 * dp[1][5] = 1 + min(1, 1) = 2
 *
 * dp[0][6] = dp[1][5] = 2 → Answer: 2
 *
 * You can delete 'e' and 'd' to make "abcba" which is a palindrome
 *
 */
