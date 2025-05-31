/*
 * GfG Link: https://www.geeksforgeeks.org/problems/count-pairs-sum-in-matrices4332/1
 *
 * Count pairs Sum in matrices
 *
 * Difficulty: Easy Accuracy: 45.66% Submissions: 47K+ Points: 2
 *
 * Given two matrices mat1[][] and mat2[][] of size n x n, where the elements in each matrix are arranged in strictly ascending order. Specifically, each row is sorted from left to right, and the last element of a row is smaller than the first element of the next row.
 * You're given a target value x, your task is to find and count all pairs {a, b} such that a is from mat1 and b is from mat2 where the sum of a + b is equal to x.
 *
 * Examples:
 *
 * Input: n = 3, x = 21,
 * mat1[][] = [[1, 5, 6], [8, 10, 11], [15, 16, 18]],
 * mat2[][] = [[2, 4, 7], [9, 10, 12], [13, 16, 20]]
 * OUTPUT: 4
 * Explanation: The pairs whose sum is found to be 21 are (1, 20), (5, 16), (8, 13) and (11, 10).
 *
 * Input: n = 2, x = 10,
 * mat1[][] = [[1, 2], [3, 4]]
 * mat2[][] = [[4, 5], [6, 7]]
 * Output: 2
 * Explanation: The pairs whose sum found to be 10 are (4, 6) and (3, 7).
 *
 * Constraints:
 * 1 ≤ n ≤ 100
 * 1 ≤ x ≤ 10^5
 * 1 ≤ mat1[i][j] , mat2[i][j] ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach 1: Store mat2 elements in a hash set and iterate through mat1 to check if x - mat1[i][j] exists in the set
// Time Complexity: O(n^2) for traversing mat1 + O(n^2) for inserting mat2 into set = O(n^2)
// Space Complexity: O(n^2) for storing mat2 elements in the hash set
class Solution {
public:
    // Helper: scan mat2 to see if val exists anywhere
    bool find(const vector<vector<int> >& mat2, int needed) {
        int n = mat2.size();

        for (int i2 = 0; i2 < n; i2++) {
            for (int j2 = 0; j2 < n; j2++) {
                if (mat2[i2][j2] == needed) {
                    return true;
                }
            }
        }
        return false;
    }
    int countPairs(vector<vector<int> >& mat1, vector<vector<int> >& mat2, int x) {
        int n     = mat1.size();
        int count = 0;

        // For each element in mat1:
        for (int i1 = 0; i1 < n; i1++) {
            for (int j1 = 0; j1 < n; j1++) {
                int needed = x - mat1[i1][j1]; // Calculate the required complement to form sum x
                if (find(mat2, needed)) {      // Check if the complement exists in mat2
                    count++;
                }
            }
        }

        return count;
    }
};

/*
 *
 * Dry Run
 *
 * Input:
 * n = 3, x = 21
 * mat1 = [[1, 5, 6], [8, 10, 11], [15, 16, 18]]
 * mat2 = [[2, 4, 7], [9, 10, 12], [13, 16, 20]]
 *
 * We iterate over mat1:
 * mat1[0][0] = 1 → need 20 → found in mat2 → count = 1
 * mat1[0][1] = 5 → need 16 → found → count = 2
 * mat1[0][2] = 6 → need 15 → not found → count = 2
 * mat1[1][0] = 8 → need 13 → found → count = 3
 * mat1[1][1] = 10 → need 11 → not found → count = 3
 * mat1[1][2] = 11 → need 10 → found → count = 4
 * mat1[2][0] = 15 → need 6 → not found
 * ...
 * Final count = 4
 *
 */

// Approach 2: Store mat2 elements in a hash set and iterate through mat1 to check if x - mat1[i][j] exists in the set
// Time Complexity: O(n^2) for traversing mat1 + O(n^2) for inserting mat2 into set = O(n^2)
// Space Complexity: O(n^2) for storing mat2 elements in the hash set
class Solution {
public:
    int countPairs(vector<vector<int> >& mat1, vector<vector<int> >& mat2, int x) {
        int n = mat1.size();
        unordered_set<int> st;

        // Step 1: Insert every mat2[i][j] into the hash set
        for (int i2 = 0; i2 < n; i2++) {
            for (int j2 = 0; j2 < n; j2++) {
                st.insert(mat2[i2][j2]); // Add all values of mat2 into set
            }
        }

        int count = 0;

        // Step 2: For each element in mat1, check if (x - mat1[i][j]) exists in the set
        for (int i1 = 0; i1 < n; i1++) {
            for (int j1 = 0; j1 < n; j1++) {
                int needed = x - mat1[i1][j1]; // Compute needed complement
                if (st.count(needed)) {        // Check if complement exists in mat2
                    count++;
                }
            }
        }

        return count;
    }
};

/*
 *
 * Dry Run
 *
 * Input:
 * n = 3, x = 21
 * mat1 = [[1, 5, 6], [8, 10, 11], [15, 16, 18]]
 * mat2 = [[2, 4, 7], [9, 10, 12], [13, 16, 20]]
 *
 * Step 1: Insert all elements of mat2 into the hash set:
 * set = {2, 4, 7, 9, 10, 12, 13, 16, 20}
 *
 * Step 2: Iterate mat1 and look for complement:
 * mat1[0][0] = 1 → need 20 → in set → count = 1
 * mat1[0][1] = 5 → need 16 → in set → count = 2
 * mat1[0][2] = 6 → need 15 → not found → count = 2
 * mat1[1][0] = 8 → need 13 → in set → count = 3
 * mat1[1][1] = 10 → need 11 → not found
 * mat1[1][2] = 11 → need 10 → in set → count = 4
 * ...
 * Final count = 4
 *
 */

// Approach 3: Flatten both matrices logically, use two pointers (one from start of mat1, one from end of mat2)
// and find pairs whose sum equals x.
// Time Complexity: O(n^2) - each element is visited once
// Space Complexity: O(1) - no extra space used apart from counters
class Solution {
public:
    int countPairs(vector<vector<int> >& mat1, vector<vector<int> >& mat2, int x) {
        int n = mat1.size();

        int i = 0;              // pointer for mat1 (from start)
        int j = n * n - 1;      // pointer for mat2 (from end)

        int count = 0;

        while (i <= n * n - 1 && j >= 0) {
            int a = mat1[i / n][i % n];  // Convert 1D index to 2D for mat1
            int b = mat2[j / n][j % n];  // Convert 1D index to 2D for mat2

            int sum = a + b;

            if (sum == x) {
                count++;
                i++;
                j--;
            } else if (sum < x) {
                i++; // Need bigger sum
            } else {
                j--; // Need smaller sum
            }
        }

        return count;
    }
};

/*
 * Dry Run
 *
 * Input:
 * n = 3, x = 21
 * mat1 = [[1, 5, 6], [8, 10, 11], [15, 16, 18]]
 * mat2 = [[2, 4, 7], [9, 10, 12], [13, 16, 20]]
 *
 * mat1 is traversed in forward direction:
 * → [1, 5, 6, 8, 10, 11, 15, 16, 18]
 *
 * mat2 is traversed in reverse:
 * ← [20, 16, 13, 12, 10, 9, 7, 4, 2]
 *
 * Step-by-step:
 * - a=1, b=20 → sum=21 → count=1
 * - a=5, b=16 → sum=21 → count=2
 * - a=6, b=13 → sum=19 → i++
 * - a=8, b=13 → sum=21 → count=3
 * - a=10, b=12 → sum=22 → j--
 * - a=10, b=10 → sum=20 → i++
 * - a=11, b=10 → sum=21 → count=4
 * ...
 * Final count = 4
 */

/************************************************************ JAVA ************************************************/

// Approach 1: For each element in mat1, search linearly through all elements in mat2 to check if x - a exists
// Time Complexity: O(n^4) because we scan every element of mat1 (n^2) and for each, search through mat2 (n^2)
// Space Complexity: O(1) as no extra space is used apart from variables
class Solution {
    // Helper: scan mat2 to see if val exists anywhere
    boolean find(int[][] mat2, int needed) {
        int n = mat2.length;

        for (int i2 = 0; i2 < n; i2++) {
            for (int j2 = 0; j2 < n; j2++) {
                if (mat2[i2][j2] == needed) {
                    return true;
                }
            }
        }
        return false;
    }
    int countPairs(int[][] mat1, int[][] mat2, int x) {
        int n     = mat1.length;
        int count = 0;

        // For each element in mat1:
        for (int i1 = 0; i1 < n; i1++) {
            for (int j1 = 0; j1 < n; j1++) {
                int needed = x - mat1[i1][j1]; // Calculate the required complement to form sum x
                if (find(mat2, needed)) {      // Check if the complement exists in mat2
                    count++;
                }
            }
        }

        return count;
    }
}

/*
 *
 * Dry Run
 *
 * Input:
 * n = 3, x = 21
 * mat1 = [[1, 5, 6], [8, 10, 11], [15, 16, 18]]
 * mat2 = [[2, 4, 7], [9, 10, 12], [13, 16, 20]]
 *
 * We iterate over mat1:
 * mat1[0][0] = 1 → need 20 → found in mat2 → count = 1
 * mat1[0][1] = 5 → need 16 → found → count = 2
 * mat1[0][2] = 6 → need 15 → not found → count = 2
 * mat1[1][0] = 8 → need 13 → found → count = 3
 * mat1[1][1] = 10 → need 11 → not found → count = 3
 * mat1[1][2] = 11 → need 10 → found → count = 4
 * mat1[2][0] = 15 → need 6 → not found
 * mat1[2][1] = 16 → need 5 → not found
 * mat1[2][2] = 18 → need 3 → not found
 *
 * Final count = 4
 *
 */

// Approach 2: Store mat2 elements in a hash set and iterate through mat1 to check if x - mat1[i][j] exists in the set
// Time Complexity: O(n^2) for traversing mat1 + O(n^2) for inserting mat2 into set = O(n^2)
// Space Complexity: O(n^2) for storing mat2 elements in the hash set
class Solution {
    int countPairs(int[][] mat1, int[][] mat2, int x) {
        int n = mat1.length;
        HashSet<Integer> set = new HashSet<>();

        // Step 1: Insert all elements from mat2 into the set
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                set.add(mat2[i][j]); // Insert mat2[i][j] into set
            }
        }

        int count = 0;

        // Step 2: For each element in mat1, check if x - mat1[i][j] exists in the set
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int needed = x - mat1[i][j]; // Find needed complement
                if (set.contains(needed)) {  // Check if it's present in mat2 set
                    count++;
                }
            }
        }

        return count;
    }
}

/*
 *
 * Dry Run
 *
 * Input:
 * n = 3, x = 21
 * mat1 = [[1, 5, 6], [8, 10, 11], [15, 16, 18]]
 * mat2 = [[2, 4, 7], [9, 10, 12], [13, 16, 20]]
 *
 * Step 1: Insert all elements of mat2 into the hash set:
 * set = {2, 4, 7, 9, 10, 12, 13, 16, 20}
 *
 * Step 2: Iterate mat1 and check for complement:
 * mat1[0][0] = 1 → need 20 → in set → count = 1
 * mat1[0][1] = 5 → need 16 → in set → count = 2
 * mat1[0][2] = 6 → need 15 → not found → count = 2
 * mat1[1][0] = 8 → need 13 → in set → count = 3
 * mat1[1][1] = 10 → need 11 → not found
 * mat1[1][2] = 11 → need 10 → in set → count = 4
 * ...
 * Final count = 4
 *
 */

// Approach 3: Flatten both matrices logically and use two pointers to find pairs summing to x
// Time Complexity: O(n^2)
// Space Complexity: O(1)
class Solution {
    public int countPairs(int[][] mat1, int[][] mat2, int x) {
        int n = mat1.length;

        int i = 0;
        int j = (n * n) - 1;

        int count = 0;

        while (i <= (n * n) - 1 && j >= 0) {
            int a = mat1[i / n][i % n];  // Convert index to 2D for mat1
            int b = mat2[j / n][j % n];  // Convert index to 2D for mat2

            int sum = a + b;

            if (sum == x) {
                count++;
                i++;
                j--;
            } else if (sum < x) {
                i++;
            } else {
                j--;
            }
        }

        return count;
    }
}

/*
 * Dry Run:
 *
 * Input:
 * n = 3, x = 21
 * mat1 = [[1, 5, 6], [8, 10, 11], [15, 16, 18]]
 * mat2 = [[2, 4, 7], [9, 10, 12], [13, 16, 20]]
 *
 * mat1 (flattened): [1, 5, 6, 8, 10, 11, 15, 16, 18]
 * mat2 (flattened): [2, 4, 7, 9, 10, 12, 13, 16, 20] ← traversed in reverse
 *
 * Pairs:
 * 1+20=21 ✅ → count=1
 * 5+16=21 ✅ → count=2
 * 6+13=19 ❌
 * 8+13=21 ✅ → count=3
 * 10+12=22 ❌
 * 10+10=20 ❌
 * 11+10=21 ✅ → count=4
 * ...
 * Final count = 4
 */
