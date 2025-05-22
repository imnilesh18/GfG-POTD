/*
 * GfG Link: https://www.geeksforgeeks.org/problems/dice-throw5349/1
 *
 * Dice throw
 *
 * Difficulty: Medium Accuracy: 36.52% Submissions: 36K+ Points: 4 Average Time: 30m
 *
 * Given n dice each with m faces. Find the number of ways to get sum x which is the summation of values on each face when all the dice are thrown.
 *
 * Example:
 *
 * Input: m = 6, n = 3, x = 12
 * Output: 25
 * Explanation: There are 25 total ways to get the Sum 12 using 3 dices with faces from 1 to 6.
 *
 * Input: m = 2, n = 3, x = 6
 * Output: 1
 * Explanation: There is only 1 way to get the Sum 6 using 3 dices with faces from 1 to 2. All the dices will have to land on 2.
 *
 * Constraints:
 * 1 <= m,n,x <= 50
 */

/************************************************************ C++ ************************************************/

// Approach: Use top-down dynamic programming with memoization to count the number of ways to reach sum x with n dice and m faces.
// Time Complexity: O(n * x * m), where n is number of dice, x is target sum, and m is the number of faces (due to recursive calls and memoization).
// Space Complexity: O(n * x), for the memoization table dp[n][x].
class Solution {
public:

    int dp[51][51]; // Memoization table to store results of subproblems

    // Recursive function to calculate the number of ways to get sum 'x' with 'n' dice and 'm' faces
    int solve(int m, int n, int x) {
        if (x < 0) {
            return 0; // If the remaining sum is negative, no valid combination
        }

        if (dp[n][x] != -1) {
            return dp[n][x]; // Return previously computed result
        }

        if (n == 0 && x == 0) {
            return 1; // Base case: exact match of dice used and sum required
        }

        if (n == 0) {
            return 0; // No dice left but sum not reached
        }

        int result = 0;
        for (int faceVal = 1; faceVal <= m; faceVal++) {
            // Try all face values from 1 to m and recurse
            result += solve(m, n - 1, x - faceVal);
        }

        return dp[n][x] = result; // Store result in dp table
    }
    
    int noOfWays(int m, int n, int x) {
        memset(dp, -1, sizeof(dp)); // Initialize dp table with -1
        return solve(m, n, x);      // Start the recursive computation
    }
};

/*
 *
 * Dry Run
 * Input: m = 6, n = 2, x = 7
 * Goal: Find the number of ways to get sum 7 using 2 dice, each with 6 faces.
 *
 * solve(6, 2, 7)
 *→ First dice: Try face values from 1 to 6
 *    → face = 1 → solve(6, 1, 6)
 *    → face = 2 → solve(6, 1, 5)
 *    → face = 3 → solve(6, 1, 4)
 *    → face = 4 → solve(6, 1, 3)
 *    → face = 5 → solve(6, 1, 2)
 *    → face = 6 → solve(6, 1, 1)
 *
 * Now solve(6, 1, k) means we have 1 die left to get sum k.
 * For each solve(6, 1, k):
 *    → Try face = k → solve(6, 0, 0) → base case → returns 1
 *    → Other faces will give x < 0 or x > 6 → invalid
 *
 * So valid combinations:
 * 1st die: 1, 2, 3, 4, 5, 6
 * 2nd die must be: 6, 5, 4, 3, 2, 1 respectively
 * Total valid pairs:
 * (1,6), (2,5), (3,4), (4,3), (5,2), (6,1) → 6 ways
 *
 * Return value = 6
 */

/************************************************************ JAVA ************************************************/

// Approach: Use top-down dynamic programming with memoization to count the number of ways to get sum x with n dice and m faces.
// Time Complexity: O(n * x * m), where n is number of dice, x is target sum, and m is the number of faces.
// Space Complexity: O(n * x), for the memoization table dp[n][x].
class Solution {
    static int[][] dp = new int[51][51];

    static int solve(int m, int n, int x) {
        if (x < 0) {
            return 0; // Invalid path if remaining sum is negative
        }

        if (dp[n][x] != -1) {
            return dp[n][x]; // Return cached result
        }

        if (n == 0 && x == 0) {
            return 1; // Base case: exact sum and exact dice used
        }

        if (n == 0) {
            return 0; // No dice left but sum not matched
        }

        int result = 0;
        for (int faceVal = 1; faceVal <= m; faceVal++) {
            result += solve(m, n - 1, x - faceVal); // Try all face values
        }

        return dp[n][x] = result; // Memoize and return
    }

    static int noOfWays(int m, int n, int x) {
        for (int i = 0; i <= 50; i++) {
            for (int j = 0; j <= 50; j++) {
                dp[i][j] = -1; // Initialize dp array
            }
        }
        return solve(m, n, x); // Start solving
    }
}

/*
 *
 * Dry Run
 * Input: m = 6, n = 2, x = 7
 * We want the number of ways to get sum 7 using 2 dice with 6 faces.
 *
 * solve(6, 2, 7)
 *→ Try face values from 1 to 6 for the first dice:
 *    → face = 1 → solve(6, 1, 6)
 *    → face = 2 → solve(6, 1, 5)
 *    → face = 3 → solve(6, 1, 4)
 *    → face = 4 → solve(6, 1, 3)
 *    → face = 5 → solve(6, 1, 2)
 *    → face = 6 → solve(6, 1, 1)
 *
 * Now for each solve(6, 1, k), we check:
 *    → Only one die left → can only match if face == k
 *    → solve(6, 0, 0) for valid → return 1
 *    → Else return 0
 *
 * Valid face pairs: (1,6), (2,5), (3,4), (4,3), (5,2), (6,1)
 *
 * Total valid ways = 6
 */
