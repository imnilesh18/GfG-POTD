/*
 * GfG Link: https://www.geeksforgeeks.org/problems/make-matrix-beautiful-1587115620/1
 *
 * Make Matrix Beautiful
 *
 * Difficulty: Medium Accuracy: 64.75% Submissions: 65K+ Points: 4 Average Time: 20m
 *
 * A beautiful matrix is defined as a square matrix in which the sum of elements in every row and every column is equal. Given a square matrix mat[][], your task is to determine the minimum number of operations required to make the matrix beautiful.
 * In one operation, you are allowed to increment the value of any single cell by 1.
 *
 * Examples:
 *
 * Input: mat[][] = [[1, 2],
 *              [3, 4]]
 * Output: 4
 * Explanation:
 * Increment value of cell(0, 0) by 3,
 * Increment value of cell(0, 1) by 1.
 * Matrix after the operations: [[4, 3],
 *                          [3, 4]]
 * Here, sum of each row and column is 7.
 * Hence total 4 operation are required.
 *
 * Input: mat[][] = [[1, 2, 3],
 *              [4, 2, 3],
 *              [3, 2, 1]]
 * Output: 6
 * Explanation:
 * Increment value of cell(0, 0) by 1,
 * Increment value of cell(0, 1) by 2,
 * Increment value of cell(2, 1) by 1,
 * Increment value of cell(2, 2) by 2.
 * Matrix after the operations: [[2, 4, 3],
 *                          [4, 2, 3],
 *                          [3, 3, 3]]
 * Here, sum of each row and column is 9.
 * Hence total 6 operation are required.
 * Constraints:
 * 1 ≤ mat.size() ≤ 900
 * 0 ≤ mat[i][j] ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Intuition: To make a matrix beautiful, all row sums and column sums must be equal. Since we can only increment values, the final sum for each row and column must be at least the maximum sum that currently exists in any row or column. The goal is to find this target sum (the maximum of all initial row and column sums) and then calculate the total number of increments needed to make every row sum equal to this target sum. The sum of these increments will be the minimum number of operations.
// Approach:
// 1. Find the maximum sum among all rows and all columns. Let's call this 'maxSum'. This will be the target sum for every row and column in the beautiful matrix.
// 2. Iterate through each row of the matrix.
// 3. For each row, calculate its current sum.
// 4. The number of operations needed for that row is the difference between 'maxSum' and the row's current sum.
// 5. Add this difference to a running total, which represents the total minimum operations.
// 6. The final running total is the answer. It's sufficient to only balance the rows, as balancing all row sums to 'maxSum' guarantees that the sum of all elements in the matrix will be n * maxSum, which will also satisfy the column sum requirements.
// Time Complexity: O(N*N), where N is the number of rows (or columns). We traverse the matrix three times: once for row sums, once for column sums, and once more to calculate the final result.
// Space Complexity: O(1), as we only use a few variables to store sums and the result, not dependent on the input matrix size.
class Solution {
public:
    int balanceSums(vector<vector<int> >& mat) {
        int n      = mat.size(); // Get the size of the square matrix (N x N)
        int result = 0;          // Initialize the total operations count
        int maxSum = 0;          // Stores the target sum for each row and column

        // find maximum sum across all rows
        // This loop calculates the sum of each row and finds the maximum among them.
        for (int i = 0; i < n; i++) {
            int sum = 0;               // Sum for the current row
            for (int j = 0; j < n; j++) {
                sum += mat[i][j];      // Add element to the row sum
            }
            maxSum = max(sum, maxSum); // Update maxSum if current row sum is greater
        }

        // find maximum sum across all columns
        // This loop does the same for columns, ensuring maxSum is the max of ALL row/column sums.
        for (int j = 0; j < n; j++) {
            int sum = 0;               // Sum for the current column
            for (int i = 0; i < n; i++) {
                sum += mat[i][j];      // Add element to the column sum
            }
            maxSum = max(sum, maxSum); // Update maxSum if current column sum is greater
        }

        // sum of operations across all rows
        // Calculate the total increments needed by making each row sum equal to maxSum.
        for (int i = 0; i < n; i++) {
            int sum = 0;              // Sum for the current row
            for (int j = 0; j < n; j++) {
                sum += mat[i][j];     // Recalculate the row sum
            }
            result += (maxSum - sum); // Add the deficit for this row to the total operations
        }
        return result;                // Return the total minimum operations
    }
};

/*
 *
 * Dry Run
 *
 * Input: mat[][] = [[1, 2, 3],
 * [4, 2, 3],
 * [3, 2, 1]]
 *
 * Initial values:
 * n = 3
 * result = 0
 * maxSum = 0
 *
 * 1. Find maximum sum across all rows:
 * - Row 0 sum: 1 + 2 + 3 = 6.  maxSum = max(0, 6) = 6.
 * - Row 1 sum: 4 + 2 + 3 = 9.  maxSum = max(6, 9) = 9.
 * - Row 2 sum: 3 + 2 + 1 = 6.  maxSum = max(9, 6) = 9.
 * After this loop, maxSum = 9.
 *
 * 2. Find maximum sum across all columns:
 * - Col 0 sum: 1 + 4 + 3 = 8.  maxSum = max(9, 8) = 9.
 * - Col 1 sum: 2 + 2 + 2 = 6.  maxSum = max(9, 6) = 9.
 * - Col 2 sum: 3 + 3 + 1 = 7.  maxSum = max(9, 7) = 9.
 * After this loop, maxSum remains 9.
 *
 * 3. Sum of operations across all rows:
 * - result is currently 0.
 * - For Row 0 (sum = 6): result += (9 - 6) => result = 3.
 * - For Row 1 (sum = 9): result += (9 - 9) => result = 3.
 * - For Row 2 (sum = 6): result += (9 - 6) => result = 3 + 3 = 6.
 *
 * 4. Return result:
 * The final value of result is 6.
 *
 * Output: 6
 *
 */

/************************************************************ JAVA ************************************************/

// Intuition: To make a matrix beautiful, all row sums and column sums must be equal. Since we can only increment values, the final sum for each row and column must be at least the maximum sum that currently exists in any row or column. The goal is to find this target sum (the maximum of all initial row and column sums) and then calculate the total number of increments needed to make every row sum equal to this target sum. The sum of these increments will be the minimum number of operations.
// Approach:
// 1. Find the maximum sum among all rows and all columns. Let's call this 'maxSum'. This will be the target sum for every row and column in the beautiful matrix.
// 2. Iterate through each row of the matrix.
// 3. For each row, calculate its current sum.
// 4. The number of operations needed for that row is the difference between 'maxSum' and the row's current sum.
// 5. Add this difference to a running total, which represents the total minimum operations.
// 6. The final running total is the answer. It's sufficient to only balance the rows, as balancing all row sums to 'maxSum' guarantees that the sum of all elements in the matrix will be n * maxSum, which will also satisfy the column sum requirements.
// Time Complexity: O(N*N), where N is the number of rows (or columns). We traverse the matrix three times: once for row sums, once for column sums, and once more to calculate the final result.
// Space Complexity: O(1), as we only use a few variables to store sums and the result, not dependent on the input matrix size.
class Solution {
    public static int balanceSums(int[][] mat) {
        int n      = mat.length; // Get the size of the square matrix (N x N)
        int result = 0;          // Initialize the total operations count
        int maxSum = 0;          // Stores the target sum for each row and column

        // find maximum sum across all rows
        // This loop calculates the sum of each row and finds the maximum among them.
        for (int i = 0; i < n; i++) {
            int sum = 0;                    // Sum for the current row
            for (int j = 0; j < n; j++) {
                sum += mat[i][j];           // Add element to the row sum
            }
            maxSum = Math.max(sum, maxSum); // Update maxSum if current row sum is greater
        }

        // find maximum sum across all columns
        // This loop does the same for columns, ensuring maxSum is the max of ALL row/column sums.
        for (int j = 0; j < n; j++) {
            int sum = 0;                    // Sum for the current column
            for (int i = 0; i < n; i++) {
                sum += mat[i][j];           // Add element to the column sum
            }
            maxSum = Math.max(sum, maxSum); // Update maxSum if current column sum is greater
        }

        // sum of operations across all rows
        // Calculate the total increments needed by making each row sum equal to maxSum.
        for (int i = 0; i < n; i++) {
            int sum = 0;              // Sum for the current row
            for (int j = 0; j < n; j++) {
                sum += mat[i][j];     // Recalculate the row sum
            }
            result += (maxSum - sum); // Add the deficit for this row to the total operations
        }
        return result;                // Return the total minimum operations
    }
}

/*
 *
 * Dry Run
 *
 * Input: mat[][] = {{1, 2, 3},
 * {4, 2, 3},
 * {3, 2, 1}}
 *
 * Initial values:
 * n = 3
 * result = 0
 * maxSum = 0
 *
 * 1. Find maximum sum across all rows:
 * - Row 0 sum: 1 + 2 + 3 = 6.  maxSum = Math.max(0, 6) = 6.
 * - Row 1 sum: 4 + 2 + 3 = 9.  maxSum = Math.max(6, 9) = 9.
 * - Row 2 sum: 3 + 2 + 1 = 6.  maxSum = Math.max(9, 6) = 9.
 * After this loop, maxSum = 9.
 *
 * 2. Find maximum sum across all columns:
 * - Col 0 sum: 1 + 4 + 3 = 8.  maxSum = Math.max(9, 8) = 9.
 * - Col 1 sum: 2 + 2 + 2 = 6.  maxSum = Math.max(9, 6) = 9.
 * - Col 2 sum: 3 + 3 + 1 = 7.  maxSum = Math.max(9, 7) = 9.
 * After this loop, maxSum remains 9.
 *
 * 3. Sum of operations across all rows:
 * - result is currently 0.
 * - For Row 0 (sum = 6): result += (9 - 6) => result = 3.
 * - For Row 1 (sum = 9): result += (9 - 9) => result = 3.
 * - For Row 2 (sum = 6): result += (9 - 6) => result = 3 + 3 = 6.
 *
 * 4. Return result:
 * The final value of result is 6.
 *
 * Output: 6
 *
 */
