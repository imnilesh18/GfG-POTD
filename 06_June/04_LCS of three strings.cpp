/*
 * GfG Link: https://www.geeksforgeeks.org/problems/lcs-of-three-strings0028/1
 *
 * LCS of three strings
 *
 * Difficulty: Medium Accuracy: 48.52% Submissions: 73K+ Points: 4
 *
 * Given three strings s1, s2, and s3 containing uppercase letters, lowercase letters, and digits, find the length of longest common sub-sequence in all three given strings.
 *
 * Examples:
 *
 * Input: s1 = "geeks", s2 = "geeksfor", s3 = "geeksforgeeks"
 * Output: 5
 * Explanation: "geeks"is the longest common subsequence with length 5.
 *
 * Input: s1 = "abcd1e2", s2 = "bc12ea", s3 = "bd1ea"
 * Output: 3
 * Explanation:  Longest common subsequence is "b1e" i.e. length = 3.
 *
 * Constraints:
 * 1  ≤  s1.size(), s2.size(), s3.size()  ≤  100
 */

/************************************************************ C++ ************************************************/

// Approach: Top-down recursive DP with memoization. We compare last characters of the strings and recursively reduce the problem.
// Time Complexity: O(n1 * n2 * n3) since we compute each state (i, j, k) only once and memoize the result.
// Space Complexity: O(n1 * n2 * n3) for the memoization table plus O(n1 + n2 + n3) recursion stack space.
class Solution {
public:
    // Memoization table to store subproblem results
    int dp[101][101][101]; // Max length for each string is 100, so 101 for 0-based indexing

    // Recursive function to find LCS
    int solve(string& s1, string& s2, string& s3, int i, int j, int k) {
        // Base case: if any string is empty, LCS is 0
        if (i == 0 || j == 0 || k == 0) {
            return 0;
        }

        // Return already computed result
        if (dp[i][j][k] != -1) {
            return dp[i][j][k];
        }

        // If current characters match in all three strings, include in LCS
        if (s1[i - 1] == s2[j - 1] && s2[j - 1] == s3[k - 1]) {
            return dp[i][j][k] = 1 + solve(s1, s2, s3, i - 1, j - 1, k - 1);
        }

        // Else, take max by excluding one character from one of the strings
        return dp[i][j][k] = max({
            solve(s1, s2, s3, i - 1, j, k),   // Exclude from s1
            solve(s1, s2, s3, i, j - 1, k),   // Exclude from s2
            solve(s1, s2, s3, i, j, k - 1)    // Exclude from s3
        });
    }
    // Main function to call the recursive solver
    int lcsOf3(string& s1, string& s2, string& s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();

        // Initialize dp array with -1 to denote uncomputed states
        memset(dp, -1, sizeof(dp));

        // Start recursion with full lengths
        return solve(s1, s2, s3, n1, n2, n3);
    }
};

/*
 *
 * Dry Run
 * Input:
 * s1 = "abcd1e2"
 * s2 = "bc12ea"
 * s3 = "bd1ea"
 *
 * We start from (i = 7, j = 6, k = 5) => last characters: '2', 'a', 'a'
 * These don't match, so we try:
 *   -> solve(6,6,5), solve(7,5,5), solve(7,6,4)
 * We go deeper into each call until:
 * Characters at s1[5] = 'e', s2[5] = 'e', s3[4] = 'e' → match!
 * So we take 1 + solve(5,4,3)
 * Next match at s1[2] = 'b', s2[0] = 'b', s3[0] = 'b'
 * So we take 1 + solve(1, -1, -1) → base case hit → return 0
 * Accumulate back:
 * 1 ('b') + 1 ('e') + 1 ('1') = 3
 * Final Answer: 3 ("b1e")
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Top-down recursive Dynamic Programming with memoization (3D DP) for overlapping subproblems.
// Time Complexity: O(i * j * k) – every unique (i, j, k) state is computed only once.
// Space Complexity: O(i * j * k) – for dp table + recursion stack.
class Solution {
    static int solve(String s1, String s2, String s3, int i, int j, int k, int[][][] dp) {
        // Base case: If any string length is zero, LCS is 0
        if (i == 0 || j == 0 || k == 0) {
            return 0;
        }

        // If already computed, return from dp table
        if (dp[i][j][k] != -1) {
            return dp[i][j][k];
        }

        // If last characters of all three strings match
        if (s1.charAt(i - 1) == s2.charAt(j - 1) && s2.charAt(j - 1) == s3.charAt(k - 1)) {
            // Include this character in LCS and move one step back in all strings
            return dp[i][j][k] = 1 + solve(s1, s2, s3, i - 1, j - 1, k - 1, dp);
        }

        // If last characters don't match, explore all 3 options:
        // 1. Exclude last char of s1
        // 2. Exclude last char of s2
        // 3. Exclude last char of s3
        // Take maximum of all
        return dp[i][j][k] = Math.max(
                   Math.max(solve(s1, s2, s3, i - 1, j, k, dp),
                            solve(s1, s2, s3, i, j - 1, k, dp)),
                   solve(s1, s2, s3, i, j, k - 1, dp));
    }
    static int lcsOf3(String s1, String s2, String s3) {
        int i = s1.length();
        int j = s2.length();
        int k = s3.length();

        // Create dp table and initialize with -1
        int[][][] dp = new int[i + 1][j + 1][k + 1];

        for (int x = 0; x <= i; x++) {
            for (int y = 0; y <= j; y++) {
                for (int z = 0; z <= k; z++) {
                    dp[x][y][z] = -1;
                }
            }
        }

        // Start solving from full lengths
        return solve(s1, s2, s3, i, j, k, dp);
    }
}

/*
 *
 * Dry Run
 *
 * Input:
 * s1 = "abcd1e2", s2 = "bc12ea", s3 = "bd1ea"
 *
 * Call: solve(s1, s2, s3, 7, 6, 5)
 * Last characters: '2', 'a', 'a' → Not equal
 * → Explore:
 *   solve(6, 6, 5)
 *   solve(7, 5, 5)
 *   solve(7, 6, 4)
 *
 * Eventually matches:
 *   s1[5] = 'e', s2[5] = 'e', s3[4] = 'e' → contributes +1
 *   Recurse further:
 *     s1[3] = '1', s2[2] = '1', s3[2] = '1' → contributes +1
 *     s1[2] = 'b', s2[0] = 'b', s3[0] = 'b' → contributes +1
 *
 * Final LCS length = 3
 * LCS = "b1e"
 *
 */
