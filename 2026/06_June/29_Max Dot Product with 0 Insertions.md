# ✖️ Max Dot Product with 0 Insertions

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-13.27%25-orange?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two arrays `a[]` and `b[]` of positive integers of size `n` and `m` respectively, where `m ≤ n`. You are allowed to insert zeros anywhere into the second array `b` so that its length becomes equal to `n`. 

The dot product of two arrays of equal length `n` is defined as: 
$$a[0] \times b[0] + a[1] \times b[1] + \dots + a[n-1] \times b[n-1]$$

**Task:** Return the maximum possible dot product of the two arrays.

---

## 💡 Examples

```text
Input: a[] = [2, 3, 1, 7, 8], b[] = [3, 6, 7]
Output: 107
Explanation: Maximum dot product is obtained after inserting 0 at the first and third positions in array b.
Therefore b becomes [0, 3, 0, 6, 7]. 
Maximum dot product = 2*0 + 3*3 + 1*0 + 7*6 + 8*7 = 107.
```

```text
Input: a[] = [1, 2, 3], b[] = [4]
Output: 12
Explanation: Maximum dot product is obtained after inserting 0 at the first and second positions in array b.
Therefore b becomes [0, 0, 4]. 
Maximum Dot Product = 1*0 + 2*0 + 3*4 = 12.
```

<details>
<summary><b>📖 Example Breakdown</b></summary>
<br>

Let's break down the second example: `a = [1, 2, 3]`, `b = [4]`
Since `n = 3` and `m = 1`, we need to insert two `0`s into `b`.
Possible configurations for `b`:
1. `[4, 0, 0]` => Dot product: `(1*4) + (2*0) + (3*0) = 4`
2. `[0, 4, 0]` => Dot product: `(1*0) + (2*4) + (3*0) = 8`
3. `[0, 0, 4]` => Dot product: `(1*0) + (2*0) + (3*4) = 12`

The maximum dot product is **12**.
</details>

---

## ⚠️ Constraints

> * $1 \le m \le n \le 10^3$
> * $1 \le a[i], b[i] \le 10^3$

---

## 🚀 Solution Approach

Below is the optimized Dynamic Programming approach. By recognizing that inserting a zero in `b` is equivalent to skipping an element in `a` (since $a[i] \times 0 = 0$), we can iterate through the arrays and make a choice: either match `a[i]` with `b[j]`, or skip `a[i]`. We can optimize the standard 2D DP matrix down to a 1D array to save space.

```cpp
// Intuition: The problem asks us to find the maximum dot product by pairing all 'm' elements of array 'b' with 'm' elements of array 'a' (preserving their relative order). The remaining 'n - m' elements in 'a' are effectively paired with inserted 0s. This is a classic "choose or skip" scenario, making Dynamic Programming the perfect fit.
// Approach:
// 1. Create a 1D DP array of size 'm + 1' initialized to 0. `dp[j]` will store the max dot product using the first 'i' elements of 'a' and 'j' elements of 'b'.
// 2. Iterate through each element of array 'a' using index 'i' (from 1 to n).
// 3. For each element in 'a', iterate backwards through array 'b' using index 'j' (from min(i, m) down to 1). Iterating backwards ensures we don't reuse the current 'a[i-1]' multiple times in the same step.
// 4. Update `dp[j]` by taking the maximum of:
//    - Skipping the current element of 'a' (leaving `dp[j]` unchanged).
//    - Pairing the current element `a[i-1]` with `b[j-1]` (adding their product to `dp[j-1]`).
// 5. Finally, `dp[m]` will contain the maximum dot product.
// Time Complexity: O(n * m), where 'n' is the size of array 'a' and 'm' is the size of array 'b'. We evaluate transitions for every valid state.
// Space Complexity: O(m), as we optimized the space down to a 1D array instead of using an O(n * m) 2D matrix.

class Solution {
  public:
    int maxDotProduct(vector<int>& a, vector<int>& b) {
        int n = a.size();
        int m = b.size();
        
        // 1D DP array to store the maximum dot product for 'j' elements of b
        vector<int> dp(m + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            // Traverse backwards to optimize space and prevent reusing a[i-1]
            for (int j = min(i, m); j >= 1; j--) {
                // Two choices: Skip a[i-1] OR pair a[i-1] with b[j-1]
                dp[j] = max(dp[j], dp[j - 1] + (a[i - 1] * b[j - 1]));
            }
        }
        
        // Return the max dot product using all 'm' elements of 'b'
        return dp[m];
    }
};

/*
*
* Dry Run
*
* Input: a = [1, 2, 3], b = [4] (n=3, m=1)
* dp array initialization: dp = [0, 0]
*
* Iteration i = 1 (a[0] = 1):
*  - j = 1: dp[1] = max(dp[1], dp[0] + a[0]*b[0]) = max(0, 0 + 1*4) = 4
*  dp becomes: [0, 4]
*
* Iteration i = 2 (a[1] = 2):
*  - j = 1: dp[1] = max(dp[1], dp[0] + a[1]*b[0]) = max(4, 0 + 2*4) = 8
*  dp becomes: [0, 8]
*
* Iteration i = 3 (a[2] = 3):
*  - j = 1: dp[1] = max(dp[1], dp[0] + a[2]*b[0]) = max(8, 0 + 3*4) = 12
*  dp becomes: [0, 12]
*
* Output: dp[1] = 12
*/
```

---

## 🧠 Key Insights

* **Insertions equal Skips:** Padding `b` with zeros is exactly the same as "ignoring" or "skipping" extra elements in `a`. Since any number multiplied by zero is zero, skipping costs nothing.
* **1D Array Optimization:** In a standard 2D DP matrix `dp[i][j]`, the current row `i` only ever relies on data from the immediate previous row `i-1`. By updating a 1D array in reverse (right to left), we prevent data overwrites and drastically reduce memory consumption.

---

## 🔗 Further Exploration

*   **Related Problem:** [Longest Increasing Subsequence (LIS)](https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/)
*   **Related Problem:** [Longest Common Subsequence (LCS)](https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/)

---

## 📚 References

*   **GeeksforGeeks Problem:** [Max Dot Product](https://www.geeksforgeeks.org/problems/maximize-dot-product2649/1)

---

## 👨‍💻 Author

Created by [imnilesh18](https://github.com/imnilesh18).

---

## 🏷️ Tags

- `dynamic-programming`
- `algorithms`
- `arrays`
- `directi`
- `geeksforgeeks`