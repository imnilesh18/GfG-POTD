/*
 * GfG Link: https://www.geeksforgeeks.org/problems/unique-paths-in-a-grid--170647/1
 *
 * Unique Paths in a Grid
 *
 * Difficulty: Medium Accuracy: 50.47% Submissions: 38K+ Points: 4
 *
 * You are given a 2d list grid[][] of size n x m consisting of values 0 and 1.
 * A value of 0 means that you can enter that cell and 1 implies that entry to that cell is not allowed.
 * You start at the upper-left corner of the grid (1, 1) and you have to reach the bottom-right corner (n, m) such that you can only move in the right or down direction from every cell.
 * Your task is to calculate the total number of ways of reaching the target.
 *
 * Note: The first (1, 1) and last (n, m) cell of the grid can also be 1.
 * It is guaranteed that the total number of ways will fit within a 32-bit integer.
 *
 * Examples:
 *
 * Input: n = 3, m = 3,
 * grid[][] = [[0, 0, 0], [0, 1, 0], [0, 0, 0]]
 * Output: 2
 * Explanation: There are two ways to reach the bottom-right corner:
 * 1. Right -> Right -> Down -> Down
 * 2. Down -> Down -> Right -> Right
 *
 * Input: n = 1, m = 3,
 * grid[][] = [[1, 0, 1]]
 * Output: 0
 * Explanation: There is no possible path to reach the end.
 *
 * Constraints:
 * 1 ≤ n*m ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Approach 1: Use memoized recursion (Top-down DP) to explore all right and down paths avoiding cells with value 1. Store intermediate results in dp to avoid recomputation.
// Time Complexity: O(n * m), where n and m are grid dimensions, since each cell is computed only once due to memoization.
// Space Complexity: O(n * m), for the dp array used in memoization.
class Solution {
public:
    // Helper function to recursively calculate number of unique paths from (i, j) to (n-1, m-1)
    int solve(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {
        int m = grid.size();      // total number of rows
        int n = grid[0].size();   // total number of columns

        // Base case: Out of bounds or cell is blocked
        if (i >= m || j >= n || grid[i][j] == 1) {
            return 0;
        }

        // Reached the destination cell
        if (i == m - 1 && j == n - 1) {
            return 1;
        }

        // If already computed, return stored result
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // Move to the right and down cells
        int right = solve(i, j + 1, grid, dp);
        int down  = solve(i + 1, j, grid, dp);

        // Store the total paths from current cell
        return dp[i][j] = right + down;
    }

    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();      // total rows
        int n = grid[0].size();   // total columns

        // If start or end cell is blocked, no path exists
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1) {
            return 0;
        }

        // Initialize dp array with -1 for memoization
        vector<vector<int>> dp(m, vector<int>(n, -1));

        // Start solving from the top-left cell
        return solve(0, 0, grid, dp);
    }
};

/*
 *
 * Dry Run
 *
 * Input: grid = [[0, 0, 0], [0, 1, 0], [0, 0, 0]]
 *
 * Call: uniquePaths(grid)
 * → m = 3, n = 3
 * → grid[0][0] = 0, grid[2][2] = 0 → both valid
 *
 * Initialize dp as:
 * dp = [
 * [-1, -1, -1],
 * [-1, -1, -1],
 * [-1, -1, -1]
 * ]
 *
 * Call solve(0, 0)
 * → grid[0][0] = 0 → valid
 *
 * → right = solve(0, 1)
 *  → grid[0][1] = 0 → valid
 *  → right = solve(0, 2)
 *      → grid[0][2] = 0 → valid
 *      → right = solve(0, 3) → out of bounds → return 0
 *      → down = solve(1, 2)
 *          → grid[1][2] = 0 → valid
 *          → right = solve(1, 3) → out of bounds → return 0
 *          → down = solve(2, 2)
 *              → grid[2][2] = 0 → destination → return 1
 *          → dp[1][2] = 1
 *      → dp[0][2] = 1
 *  → down = solve(1, 1)
 *      → grid[1][1] = 1 → blocked → return 0
 *  → dp[0][1] = 1
 * → down = solve(1, 0)
 *  → grid[1][0] = 0 → valid
 *  → right = solve(1, 1) → blocked → return 0
 *  → down = solve(2, 0)
 *      → grid[2][0] = 0 → valid
 *      → right = solve(2, 1)
 *          → grid[2][1] = 0 → valid
 *          → right = solve(2, 2) → destination → return 1
 *          → down = solve(3, 1) → out of bounds → return 0
 *          → dp[2][1] = 1
 *      → down = solve(3, 0) → out of bounds → return 0
 *      → dp[2][0] = 1
 *  → dp[1][0] = 1
 * → dp[0][0] = 2
 *
 * Final answer = 2
 */

// Approach 2: Use Bottom-Up Dynamic Programming (Tabulation). Initialize dp[0][0] = 1. Then fill the first row and column considering blocked cells. For the rest of the grid, dp[i][j] = dp[i-1][j] + dp[i][j-1] if grid[i][j] is not blocked.
// Time Complexity: O(n * m), as every cell in the grid is visited once.
// Space Complexity: O(n * m), for the 2D dp array.
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // columns

        // If starting or ending cell is blocked, return 0
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1) {
            return 0;
        }

        // Create DP table
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // Starting cell
        dp[0][0] = 1;

        // Fill first row
        for (int j = 1; j < n; j++) {
            if (grid[0][j] == 0) {
                dp[0][j] = dp[0][j - 1];
            }
        }

        // Fill first column
        for (int i = 1; i < m; i++) {
            if (grid[i][0] == 0) {
                dp[i][0] = dp[i - 1][0];
            }
        }

        // Fill remaining cells
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (grid[i][j] == 0) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};

/*
 *
 * Dry Run
 *
 * Input: grid = [[0, 0, 0], [0, 1, 0], [0, 0, 0]]
 * → m = 3, n = 3
 *
 * Step 1: Initialize dp[0][0] = 1
 *
 * Step 2: Fill first row:
 * dp[0][1] = dp[0][0] = 1
 * dp[0][2] = dp[0][1] = 1
 *
 * Step 3: Fill first column:
 * dp[1][0] = dp[0][0] = 1
 * dp[2][0] = dp[1][0] = 1
 *
 * Step 4: Fill rest:
 * → dp[1][1] = grid[1][1] == 1 → blocked → dp[1][1] = 0
 * → dp[1][2] = dp[0][2] + dp[1][1] = 1 + 0 = 1
 * → dp[2][1] = dp[1][1] + dp[2][0] = 0 + 1 = 1
 * → dp[2][2] = dp[1][2] + dp[2][1] = 1 + 1 = 2
 *
 * Answer: dp[2][2] = 2
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Use memoized recursion (Top-down DP) to explore all right and down paths avoiding cells with value 1. Store intermediate results in dp to avoid recomputation.
// Time Complexity: O(n * m), where n and m are grid dimensions, since each cell is computed only once due to memoization.
// Space Complexity: O(n * m), for the dp array used in memoization.
class Solution {
    // Helper function to recursively calculate number of unique paths from (i, j) to (n-1, m-1)
    public int solve(int i, int j, int[][] grid, int[][] dp) {
        int m = grid.length;       // total number of rows
        int n = grid[0].length;    // total number of columns

        // Base case: Out of bounds or cell is blocked
        if (i >= m || j >= n || grid[i][j] == 1) {
            return 0;
        }

        // Reached the destination cell
        if (i == m - 1 && j == n - 1) {
            return 1;
        }

        // If already computed, return stored result
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // Move to the right and down cells
        int right = solve(i, j + 1, grid, dp);
        int down  = solve(i + 1, j, grid, dp);

        // Store the total paths from current cell
        return dp[i][j] = right + down;
    }

    public int uniquePaths(int[][] grid) {
        int m = grid.length;       // total rows
        int n = grid[0].length;    // total columns

        // If start or end cell is blocked, no path exists
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1) {
            return 0;
        }

        // Initialize dp array with -1 for memoization
        int[][] dp = new int[m][n];
        for (int[] row : dp) {
            Arrays.fill(row, -1);
        }

        // Start solving from the top-left cell
        return solve(0, 0, grid, dp);
    }
};

/*
 *
 * Dry Run
 *
 * Input: grid = [[0, 0, 0], [0, 1, 0], [0, 0, 0]]
 *
 * Call: uniquePaths(grid)
 * → m = 3, n = 3
 * → grid[0][0] = 0, grid[2][2] = 0 → both valid
 *
 * Initialize dp as:
 * dp = [
 * [-1, -1, -1],
 * [-1, -1, -1],
 * [-1, -1, -1]
 * ]
 *
 * Call solve(0, 0)
 * → grid[0][0] = 0 → valid
 *
 * → right = solve(0, 1)
 *  → grid[0][1] = 0 → valid
 *  → right = solve(0, 2)
 *      → grid[0][2] = 0 → valid
 *      → right = solve(0, 3) → out of bounds → return 0
 *      → down = solve(1, 2)
 *          → grid[1][2] = 0 → valid
 *          → right = solve(1, 3) → out of bounds → return 0
 *          → down = solve(2, 2)
 *              → grid[2][2] = 0 → destination → return 1
 *          → dp[1][2] = 1
 *      → dp[0][2] = 1
 *  → down = solve(1, 1)
 *      → grid[1][1] = 1 → blocked → return 0
 *  → dp[0][1] = 1
 * → down = solve(1, 0)
 *  → grid[1][0] = 0 → valid
 *  → right = solve(1, 1) → blocked → return 0
 *  → down = solve(2, 0)
 *      → grid[2][0] = 0 → valid
 *      → right = solve(2, 1)
 *          → grid[2][1] = 0 → valid
 *          → right = solve(2, 2) → destination → return 1
 *          → down = solve(3, 1) → out of bounds → return 0
 *          → dp[2][1] = 1
 *      → down = solve(3, 0) → out of bounds → return 0
 *      → dp[2][0] = 1
 *  → dp[1][0] = 1
 * → dp[0][0] = 2
 *
 * Final answer = 2
 */

// Approac 2h: Use Bottom-Up Dynamic Programming (Tabulation). Initialize dp[0][0] = 1. Then fill the first row and column considering blocked cells. For the rest of the grid, dp[i][j] = dp[i-1][j] + dp[i][j-1] if grid[i][j] is not blocked.
// Time Complexity: O(n * m), as every cell in the grid is visited once.
// Space Complexity: O(n * m), for the 2D dp array.
class Solution {
    public int uniquePaths(int[][] grid) {
        int m = grid.length;        // rows
        int n = grid[0].length;     // columns

        // If start or end is blocked
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1) {
            return 0;
        }

        int[][] dp = new int[m][n];
        dp[0][0]   = 1; // starting cell

        // Fill first row
        for (int j = 1; j < n; j++) {
            if (grid[0][j] == 0) {
                dp[0][j] = dp[0][j - 1];
            }
        }

        // Fill first column
        for (int i = 1; i < m; i++) {
            if (grid[i][0] == 0) {
                dp[i][0] = dp[i - 1][0];
            }
        }

        // Fill the rest of the grid
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (grid[i][j] == 0) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }

        return dp[m - 1][n - 1];
    }
}

/*
 *
 * Dry Run
 *
 * Input: grid = [[0, 0, 0], [0, 1, 0], [0, 0, 0]]
 * → m = 3, n = 3
 *
 * Step 1: Initialize dp[0][0] = 1
 *
 * Step 2: Fill first row:
 * dp[0][1] = dp[0][0] = 1
 * dp[0][2] = dp[0][1] = 1
 *
 * Step 3: Fill first column:
 * dp[1][0] = dp[0][0] = 1
 * dp[2][0] = dp[1][0] = 1
 *
 * Step 4: Fill rest:
 * → dp[1][1] = grid[1][1] == 1 → blocked → dp[1][1] = 0
 * → dp[1][2] = dp[0][2] + dp[1][1] = 1 + 0 = 1
 * → dp[2][1] = dp[1][1] + dp[2][0] = 0 + 1 = 1
 * → dp[2][2] = dp[1][2] + dp[2][1] = 1 + 1 = 2
 *
 * Answer: dp[2][2] = 2
 */
