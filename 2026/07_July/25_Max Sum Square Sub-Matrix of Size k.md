# 🟧 Max Sum Square Sub-Matrix of Size k

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)
![Accuracy: 50.41%](https://img.shields.io/badge/Accuracy-50.41%25-green?style=for-the-badge)
![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an `n × n` grid `mat[][]` of integers where values can be negative, find the **maximum sum** among all possible `k × k` sub-grids.

---

## 💡 Examples

### Example 1

```text
Input: k = 3, mat[][] = [[1, 2, -1, 4], [-8, -3, 4, 2], [3, 8, 10, -8], [-4, -1, 1, 7]]
Output: 20
Explanation: The 3 × 3 sub-grid [[-3, 4, 2], [8, 10, -8], [-1, 1, 7]] has the maximum sum of 20. 

```

1. We are looking for a `3 × 3` sub-matrix within the given `4 × 4` matrix.
2. If we evaluate the possible `3 × 3` grids:
* Top-Left 3x3 Sum: `1 + 2 - 1 - 8 - 3 + 4 + 3 + 8 + 10 = 16`
* Top-Right 3x3 Sum: `2 - 1 + 4 - 3 + 4 + 2 + 8 + 10 - 8 = 18`
* Bottom-Left 3x3 Sum: `-8 - 3 + 4 + 3 + 8 + 10 - 4 - 1 + 1 = 10`
* **Bottom-Right 3x3 Sum**: `-3 + 4 + 2 + 8 + 10 - 8 - 1 + 1 + 7 = 20`


3. The maximum sum among all these sub-grids is `20`.

### Example 2

```text
Input: k = 1, mat[][] = [[4]]
Output: 4
Explanation: Only one 1×1 sub-grid exists with sum 4.

```

---

## ⚠️ Constraints

> * `1 ≤ n ≤ 1000`
> * `1 ≤ k ≤ n`
> * `-1000 ≤ mat[i][j] ≤ 1000`
> 
> 

---

## 💻 Solution Approach

```cpp
// Intuition: Computing the sum of every k x k subgrid directly would result in O(n^2 * k^2) time complexity. We can optimize this by precomputing a 2D prefix sum array, allowing us to query the sum of any subgrid in O(1) time.
// Approach: 
// 1. Create a 2D `prefix` array of size (n+1) x (n+1) initialized to 0.
// 2. Compute prefix sums such that prefix[i][j] stores the sum of elements from mat[0][0] to mat[i-1][j-1].
// 3. Iterate through all possible bottom-right corners of k x k subgrids.
// 4. Use the prefix sum array to calculate the subgrid sum in O(1) time and track the maximum sum.
// Time Complexity: O(n^2) - We traverse the n x n matrix twice (once to build the prefix array, once to find the max sum).
// Space Complexity: O(n^2) - We use an auxiliary 2D array `prefix` of size (n+1) x (n+1).

class Solution {
public:
    int maximumSum(vector<vector<int>>& mat, int k) {
        int n = mat.size();
        
        // Step 1: Create a 2D prefix sum array with 1-based indexing
        vector<vector<int>> prefix(n + 1, vector<int>(n + 1, 0));
        
        // Step 2: Build the 2D prefix sum
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // Current element + left prefix + top prefix - diagonal overlap
                prefix[i][j] = mat[i - 1][j - 1] + 
                               prefix[i - 1][j] + 
                               prefix[i][j - 1] - 
                               prefix[i - 1][j - 1];
            }
        }
        
        int maxSum = INT_MIN;
        
        // Step 3: Find maximum sum of any k x k sub-matrix
        for (int i = k; i <= n; i++) {
            for (int j = k; j <= n; j++) {
                // Calculate current k x k sub-matrix sum in O(1)
                int currentSum = prefix[i][j] - 
                                 prefix[i - k][j] - 
                                 prefix[i][j - k] + 
                                 prefix[i - k][j - k];
                                 
                // Update maxSum if a larger sum is found
                maxSum = max(maxSum, currentSum);
            }
        }
        
        return maxSum;
    }
};

/*
*
* Dry Run
*
* Input: mat = [[1, 2], [3, 4]], k = 1, n = 2
* 
* Building prefix sum array (n+1 x n+1):
* prefix[1][1] = 1 + 0 + 0 - 0 = 1
* prefix[1][2] = 2 + 0 + 1 - 0 = 3
* prefix[2][1] = 3 + 1 + 0 - 0 = 4
* prefix[2][2] = 4 + 3 + 4 - 1 = 10
* Prefix array looks like:
* [0, 0,  0 ]
* [0, 1,  3 ]
* [0, 4, 10 ]
*
* Finding k x k (1 x 1) sums (i from 1 to 2, j from 1 to 2):
* i=1, j=1: sum = prefix[1][1] - prefix[0][1] - prefix[1][0] + prefix[0][0] = 1 - 0 - 0 + 0 = 1. maxSum = 1
* i=1, j=2: sum = prefix[1][2] - prefix[0][2] - prefix[1][1] + prefix[0][1] = 3 - 0 - 1 + 0 = 2. maxSum = 2
* i=2, j=1: sum = prefix[2][1] - prefix[1][1] - prefix[2][0] + prefix[1][0] = 4 - 1 - 0 + 0 = 3. maxSum = 3
* i=2, j=2: sum = prefix[2][2] - prefix[1][2] - prefix[2][1] + prefix[1][1] = 10 - 3 - 4 + 1 = 4. maxSum = 4
* 
* Final maxSum = 4
*
*/

```

---

## 🔑 Key Insights

* **2D Prefix Sum:** The naive approach forces us to loop through all `k x k` elements every time we slide our matrix, performing redundant calculations. A 2D prefix sum array acts as an algebraic cache.
* **Inclusion-Exclusion Principle:** To get a subgrid sum ending at `(i,j)`, we take the sum from the origin `(0,0)` to `(i,j)`, subtract the left and top non-overlapping portions, and add back the top-left diagonal overlap that was subtracted twice.

---

## 🔍 Further Exploration

* **Maximum sum rectangle in a 2D matrix** (Kadane's 2D Algorithm)
* **Range Sum Query 2D - Immutable**
* **Submatrix Sum Queries**

---

## 🔗 References

* **Original GFG Problem:** [Max Sum Square Sub-Matrix of Size k](https://www.geeksforgeeks.org/problems/coins-of-geekland--141631/1)
* **Concept Reference:** [2D Prefix Sum Arrays](https://www.geeksforgeeks.org/prefix-sum-2d-array/)

---

## 👨‍💻 Author

**Nilesh**

* [GitHub - imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

* `Array`
* `Matrix`
* `Prefix Sum`
* `Dynamic Programming`
* `GeeksforGeeks`