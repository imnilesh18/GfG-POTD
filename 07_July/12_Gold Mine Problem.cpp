/*
 * GfG Link:https://www.geeksforgeeks.org/problems/gold-mine-problem2608/1
 *
 * Gold Mine Problem
 *
 * Difficulty: Medium Accuracy: 29.73% Submissions: 126K+ Points: 4
 *
 * Given a gold mine called mat[][]. Each field in this mine contains a positive integer which is the amount of gold in tons. Initially, the miner can start from any row in the first column. From a given cell, the miner can move -
 *
 * to the cell diagonally up towards the right
 * to the right
 * to the cell diagonally down towards the right
 * Find out the maximum amount of gold that he can collect until he can no longer move.
 *
 * Examples:
 *
 * Input: mat[][] = [[1, 3, 3], [2, 1, 4], [0, 6, 4]]
 * Output: 12
 * Explaination: The path is (1, 0) -> (2, 1) -> (2, 2). Total gold collected is 2 + 6 + 4 = 12.
 *
 * Input: mat[][] = [[1, 3, 1, 5], [2, 2, 4, 1], [5, 0, 2, 3], [0, 6, 1, 2]]
 * Output: 16
 * Explaination: The path is (2, 0) -> (3, 1) -> (2, 2) -> (2, 3) or (2, 0) -> (1, 1) -> (1, 2) -> (0, 3).
 * Total gold collected is (5 + 6 + 2 + 3) or (5 + 2 + 4 + 5) = 16.
 *
 * Input: mat[][] = [[1, 3, 3], [2, 1, 4], [0, 7, 5]]
 * Output: 14
 * Explaination: The path is (1,0) -> (2,1) -> (2,2). Total gold collected is 2 + 7 + 5 = 14.
 *
 * Constraints:
 * 1 ≤ mat.size(), mat[0].size() ≤ 500
 * 0 ≤ mat[i][j] ≤ 100
 */

/************************************************************ C++ ************************************************/

// Approach: Use DFS with memoization to explore all three possible moves (right-up, right, right-down) from each cell, and cache results in a dp table to avoid recomputation.
// Time Complexity: O(n * m) — each of the n*m cells is computed at most once.
// Space Complexity: O(n * m) — dp table of size up to 501×501, plus recursion stack up to O(n + m).
class Solution {
public:

    // dfs helper that returns max gold from cell (i, j)
    int solve(int i, int j, vector<vector<int>>& mat, vector<vector<int>>& dp) {
        int n = mat.size();
        int m = mat[0].size();

        // base case: out of bounds or beyond last column
        if (i < 0 || i >= n || j >= m) {
            return 0;
        }

        // if already computed, reuse it
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // move to right-up cell
        int rightUp = solve(i - 1, j + 1, mat, dp);
        // move to right cell
        int right = solve(i, j + 1, mat, dp);
        // move to right-down cell
        int rightDown = solve(i + 1, j + 1, mat, dp);

        // cache and return the best of three moves plus current gold
        return dp[i][j] = mat[i][j] + max({ rightUp, right, rightDown });
    }

    int maxGold(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        int result = 0;
        // initialize dp table to -1 (uncomputed)
        vector<vector<int>> dp(501, vector<int>(501, -1));

        // try starting from each row in first column
        for (int i = 0; i < n; i++) {
            result = max(result, solve(i, 0, mat, dp));
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: mat = [[1, 3, 3],
 *               [2, 1, 4],
 *               [0, 6, 4]]
 * Output: 12
 *
 * solve(0,0):
 *   -> rightUp  = solve(-1,1) = 0
 *   -> right    = solve(0,1):
 *         rightUp  = solve(-1,2) = 0
 *         right    = solve(0,2)  = 3
 *         rightDown= solve(1,2)  = 4
 *         dp[0][1] = 3 + max(0,3,4) = 7
 *       returns 7
 *   -> rightDown= solve(1,1):
 *         rightUp  = solve(0,2)  = 3
 *         right    = solve(1,2)  = 4
 *         rightDown= solve(2,2)  = 4
 *         dp[1][1] = 1 + max(3,4,4) = 5
 *       returns 5
 *   dp[0][0] = 1 + max(0,7,5) = 8
 *
 * solve(1,0):
 *   -> rightUp  = solve(0,1)  = 7 (cached)
 *   -> right    = solve(1,1)  = 5 (cached)
 *   -> rightDown= solve(2,1):
 *         rightUp  = solve(1,2)  = 4
 *         right    = solve(2,2)  = 4
 *         rightDown= solve(3,2)  = 0
 *         dp[2][1] = 6 + max(4,4,0) = 10
 *       returns 10
 *   dp[1][0] = 2 + max(7,5,10) = 12
 *
 * solve(2,0):
 *   -> rightUp  = solve(1,1)  = 5 (cached)
 *   -> right    = solve(2,1)  = 10 (cached)
 *   -> rightDown= solve(3,1)  = 0
 *   dp[2][0] = 0 + max(5,10,0) = 10
 *
 * maxGold returns max(8, 12, 10) = 12
 *
 * Explanation: The optimal path is (1,0) -> (2,1) -> (2,2), collecting 2 + 6 + 4 = 12.
 */

/************************************************************ JAVA ************************************************/

// Approach: Use DFS with memoization to explore all three possible moves (right-up, right, right-down) from each cell, and cache results in a dp table to avoid recomputation.
// Time Complexity: O(n * m) — each of the n*m cells is computed at most once.
// Space Complexity: O(n * m) — dp table of size up to 501×501, plus recursion stack up to O(n + m).
class Solution {
    // helper that returns max gold from cell (i, j)
    private int solve(int i, int j, int[][] mat, int[][] dp) {
        int n = mat.length;
        int m = mat[0].length;

        // base case: out of bounds or beyond last column
        if (i < 0 || i >= n || j >= m) {
            return 0;
        }

        // if already computed, reuse it
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // move to right-up cell
        int rightUp = solve(i - 1, j + 1, mat, dp);
        // move to right cell
        int right = solve(i, j + 1, mat, dp);
        // move to right-down cell
        int rightDown = solve(i + 1, j + 1, mat, dp);

        // cache and return the best of three moves plus current gold
        return dp[i][j] = mat[i][j] + Math.max(right, Math.max(rightUp, rightDown));
    }
    
    public int maxGold(int[][] mat) {
        int n = mat.length;
        int m = mat[0].length;

        int result = 0;
        // initialize dp table to -1 (uncomputed)
        int[][] dp = new int[501][501];

        for (int[] row : dp) {
            Arrays.fill(row, -1);
        }

        // try starting from each row in first column
        for (int i = 0; i < n; i++) {
            result = Math.max(result, solve(i, 0, mat, dp));
        }
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: mat = [[1, 3, 3],
 *               [2, 1, 4],
 *               [0, 6, 4]]
 * Output: 12
 *
 * solve(0,0):
 *   -> rightUp  = solve(-1,1) = 0
 *   -> right    = solve(0,1):
 *         rightUp  = solve(-1,2) = 0
 *         right    = solve(0,2)  = 3
 *         rightDown= solve(1,2)  = 4
 *         dp[0][1] = 3 + max(0,3,4) = 7
 *       returns 7
 *   -> rightDown= solve(1,1):
 *         rightUp  = solve(0,2)  = 3
 *         right    = solve(1,2)  = 4
 *         rightDown= solve(2,2)  = 4
 *         dp[1][1] = 1 + max(3,4,4) = 5
 *       returns 5
 *   dp[0][0] = 1 + max(0,7,5) = 8
 *
 * solve(1,0):
 *   -> rightUp  = solve(0,1)  = 7 (cached)
 *   -> right    = solve(1,1)  = 5 (cached)
 *   -> rightDown= solve(2,1):
 *         rightUp  = solve(1,2)  = 4
 *         right    = solve(2,2)  = 4
 *         rightDown= solve(3,2)  = 0
 *         dp[2][1] = 6 + max(4,4,0) = 10
 *       returns 10
 *   dp[1][0] = 2 + max(7,5,10) = 12
 *
 * solve(2,0):
 *   -> rightUp  = solve(1,1)  = 5 (cached)
 *   -> right    = solve(2,1)  = 10 (cached)
 *   -> rightDown= solve(3,1)  = 0
 *   dp[2][0] = 0 + max(5,10,0) = 10
 *
 * maxGold returns max(8, 12, 10) = 12
 *
 * Explanation: The optimal path is (1,0) -> (2,1) -> (2,2), collecting 2 + 6 + 4 = 12.
 */
