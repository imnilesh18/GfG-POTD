/*
 * GfG Link: https://www.geeksforgeeks.org/problems/set-matrix-zeroes/1
 *
 * Set Matrix Zeros
 *
 * Difficulty: Medium Accuracy: 52.54% Submissions: 49K+ Points: 4
 *
 * You are given a 2D matrix mat[][] of size n x m. The task is to modify the matrix such that if mat[i][j] is 0, all the elements in the i-th row and j-th column are set to 0.
 *
 * Constraints:
 * 1 ≤ n, m ≤ 500
 * - 2^31 ≤ mat[i][j] ≤ 2^31 - 1
 */

/************************************************************ C++ ************************************************/

// Intuition: The core idea is to use auxiliary arrays to store the state of rows and columns that need to be zeroed. Modifying the matrix in-place during the first scan would corrupt the data for subsequent checks. By using marker arrays, we can first identify all target rows/columns and then modify the matrix in a second, separate pass.
// Approach:
// 1. Create two boolean arrays, `rows` of size N and `cols` of size M, initialized to `false`.
// 2. Perform a first pass over the matrix. If an element `mat[i][j]` is 0, set `rows[i]` to `true` and `cols[j]` to `true`.
// 3. Perform a second pass over the matrix. For each element `mat[i][j]`, check if `rows[i]` or `cols[j]` is `true`.
// 4. If the condition in step 3 is met, update the element `mat[i][j]` to 0.
// Time Complexity: O(N * M), where N is the number of rows and M is the number of columns. We traverse the matrix twice, which results in a linear time complexity proportional to the number of cells.
// Space Complexity: O(N + M). We use two extra boolean arrays, `rows` (size N) and `cols` (size M), to store the markers.
class Solution {
public:
    void setMatrixZeroes(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size(); // Get matrix dimensions

        // These boolean vectors will mark which rows and columns need to be set to zero.
        vector<bool> rows(n, false), cols(m, false);

        // First pass: Traverse the matrix to identify and mark rows/cols with zeros.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // If a zero is found, mark its corresponding row and column for zeroing.
                if (mat[i][j] == 0) {
                    rows[i] = true; // Mark the i-th row
                    cols[j] = true; // Mark the j-th column
                }
            }
        }

        // Second pass: Set elements to zero if their row or column is marked.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // If the current row or column is marked, set the element to 0.
                if (rows[i] || cols[j]) {
                    mat[i][j] = 0;
                }
            }
        }
    }
};

/*
 *
 * Dry Run
 *
 * Example Matrix `mat`:
 * [[1, 1, 1],
 * [1, 0, 1],
 * [1, 1, 1]]
 *
 * 1. Initialization:
 * n = 3, m = 3
 * rows = [false, false, false]
 * cols = [false, false, false]
 *
 * 2. First Pass (Marking):
 * The code iterates through the matrix.
 * At mat[1][1], it finds a 0.
 * It sets rows[1] to true.
 * It sets cols[1] to true.
 *
 * After the first pass:
 * rows = [false, true, false]
 * cols = [false, true, false]
 * `mat` is unchanged.
 *
 * 3. Second Pass (Zeroing):
 * The code iterates through the matrix again.
 * For each cell (i, j), it checks if `rows[i]` or `cols[j]` is true.
 * - i=0: rows[0] is false. cols[0]=false, cols[1]=true, cols[2]=false.
 * - mat[0][1] becomes 0.
 * - i=1: rows[1] is true. All elements in this row become 0.
 * - mat[1][0], mat[1][1], mat[1][2] become 0.
 * - i=2: rows[2] is false. cols[0]=false, cols[1]=true, cols[2]=false.
 * - mat[2][1] becomes 0.
 *
 * Final Matrix:
 * [[1, 0, 1],
 * [0, 0, 0],
 * [1, 0, 1]]
 *
 */

/************************************************************ JAVA ************************************************/

// Intuition: The core idea is to use auxiliary arrays to store the state of rows and columns that need to be zeroed. Modifying the matrix in-place during the first scan would corrupt the data for subsequent checks. By using marker arrays, we can first identify all target rows/columns and then modify the matrix in a second, separate pass.
// Approach:
// 1. Create two boolean arrays, `rows` of size N and `cols` of size M, initialized to `false`.
// 2. Perform a first pass over the matrix. If an element `mat[i][j]` is 0, set `rows[i]` to `true` and `cols[j]` to `true`.
// 3. Perform a second pass over the matrix. For each element `mat[i][j]`, check if `rows[i]` or `cols[j]` is `true`.
// 4. If the condition in step 3 is met, update the element `mat[i][j]` to 0.
// Time Complexity: O(N * M), where N is the number of rows and M is the number of columns. We traverse the matrix twice, which results in a linear time complexity proportional to the number of cells.
// Space Complexity: O(N + M). We use two extra boolean arrays, `rows` (size N) and `cols` (size M), to store the markers.
class Solution {
    public void setMatrixZeroes(int[][] mat) {
        // code here
        int n = mat.length;    // Get number of rows
        int m = mat[0].length; // Get number of columns

        // Boolean arrays to mark which rows and columns need to be zeroed.
        boolean[] rows = new boolean[n];
        boolean[] cols = new boolean[m];

        // First pass: Traverse the matrix to identify and mark rows/cols with zeros.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // If a zero is found, mark its corresponding row and column for zeroing.
                if (mat[i][j] == 0) {
                    rows[i] = true; // Mark the i-th row
                    cols[j] = true; // Mark the j-th column
                }
            }
        }

        // Second pass: Set elements to zero if their row or column is marked.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // If the current row or column is marked, set the element to 0.
                if (rows[i] || cols[j]) {
                    mat[i][j] = 0;
                }
            }
        }
    }
}

/*
 *
 * Dry Run
 *
 * Example Matrix `mat`:
 * [[1, 1, 1],
 * [1, 0, 1],
 * [1, 1, 1]]
 *
 * 1. Initialization:
 * n = 3, m = 3
 * rows = [false, false, false]
 * cols = [false, false, false]
 *
 * 2. First Pass (Marking):
 * The code iterates through the matrix.
 * At mat[1][1], it finds a 0.
 * It sets rows[1] to true.
 * It sets cols[1] to true.
 *
 * After the first pass:
 * rows = [false, true, false]
 * cols = [false, true, false]
 * `mat` is unchanged.
 *
 * 3. Second Pass (Zeroing):
 * The code iterates through the matrix again.
 * For each cell (i, j), it checks if `rows[i]` or `cols[j]` is true.
 * - i=0: rows[0] is false. cols[0]=false, cols[1]=true, cols[2]=false.
 * - mat[0][1] becomes 0.
 * - i=1: rows[1] is true. All elements in this row become 0.
 * - mat[1][0], mat[1][1], mat[1][2] become 0.
 * - i=2: rows[2] is false. cols[0]=false, cols[1]=true, cols[2]=false.
 * - mat[2][1] becomes 0.
 *
 * Final Matrix:
 * [[1, 0, 1],
 * [0, 0, 0],
 * [1, 0, 1]]
 *
 */
