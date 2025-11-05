# 🟩 Get Minimum Squares

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-45.22%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-purple?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

---

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/get-minimum-squares0538/1).

---

## Problem Statement

Given a positive integer **n**, find the minimum number of perfect squares (square of an integer) that sum up to **n**.

**Note:** Every positive integer can be expressed as a sum of square numbers since **1** is a perfect square, and any number can be represented as `1*1 + 1*1 + 1*1 + ....`

## Examples

Here are the sample test cases provided:

**Example 1:**

```
Input: n = 100
Output: 1
Explanation: 10 * 10 = 100
```

**Example 2:**

```
Input: n = 6
Output: 3
Explanation: 1 * 1 + 1 * 1 + 2 * 2 = 6
```

<details>
<summary>📖 Example 2 Breakdown (n = 6)</summary>

We need to find the _minimum_ number of perfect squares that sum to 6. Let's explore the options:

1.  **Using `3*3 = 9`:** This is too large.
2.  **Using `2*2 = 4`:**
    - If we use `4`, we are left with `6 - 4 = 2`.
    - To make 2, we must use `1*1 + 1*1`.
    - Total squares: `(2*2) + (1*1) + (1*1)`. This is **3** squares.
3.  **Using `1*1 = 1`:**
    - If we use `1`, we are left with `6 - 1 = 5`.
    - To make 5, we can use `2*2 = 4`, leaving `1`.
    - To make 1, we use `1*1`.
    - Total squares: `(1*1) + (2*2) + (1*1)`. This is also **3** squares.
    - Alternatively, to make 5, we could use five 1s: `(1*1) + (1*1) + (1*1) + (1*1) + (1*1)`. This would be `(1*1)` + five more, totaling 6 squares, which is not minimal.

Both minimal paths lead to 3 squares. Therefore, the output is 3.

</details>

---

## Constraints

<div style="background-color: #f0f0f0; border-left: 5px solid #yellow; padding: 10px; border-radius: 5px;">
  <ul>
    <li><code>1 ≤ n ≤ 10^4</code></li>
  </ul>
</div>

---

## Solution Approaches

The problem has optimal substructure and overlapping subproblems, making it a classic candidate for Dynamic Programming.

### 🚀 Optimized Approach (Recursion + Memoization)

**Intuition:**
We can define a function, `minSquares(n)`, that returns the minimum squares for `n`. To calculate this, we can try subtracting every possible perfect square (`1*1`, `2*2`, `3*3`, ...) from `n` and recursively call the function on the remainder.

For example, `minSquares(n) = 1 + min(minSquares(n - 1*1), minSquares(n - 2*2), ...)`

This recursive approach will recalculate the same subproblems many times (e.g., `minSquares(5)` will be called when solving for 6 and 9). We can store the results of these subproblems in a **memoization** array to avoid re-computation.

```cpp
// Intuition: The problem seeks a minimum, suggesting DP. We can break n down by subtracting perfect squares.
// minSquares(n) is 1 (for the square we subtract) + the minimum of minSquares(n - x*x) for all x*x <= n.
// Approach: Use recursion with memoization.
// 1. Create a memoization array `memo` of size n+1, initialized to -1.
// 2. Define a recursive helper `minSquaresRec(n, memo)`.
// 3. Base Cases: If n <= 3, return n (1=1, 2=1+1, 3=1+1+1).
// 4. Memoization Check: If memo[n] != -1, return the stored value.
// 5. Recursive Step:
//    - Initialize `cnt` to `n` (worst case: 1*1 + 1*1 + ...).
//    - Loop with `x` from 1 as long as `x*x <= n`.
//    - Update `cnt = min(cnt, 1 + minSquaresRec(n - x*x, memo))`.
// 6. Store the result: `memo[n] = cnt` and return it.
// Time Complexity: O(n * sqrt(n)). Each state from 1 to n is computed once. Inside each, we loop up to sqrt(n).
// Space Complexity: O(n) for the memoization array and O(n) for the recursion stack.

class Solution {
  public:
    // Helper function with memoization
    int minSquaresRec(int n, vector<int>& memo) {

        // base cases:
        // minSquares(0) = 0
        // minSquares(1) = 1
        // minSquares(2) = 1+1 = 2
        // minSquares(3) = 1+1+1 = 3
        if (n <= 3)
            return n;

        // if the result for this subproblem is
        // already computed then return it
        if (memo[n] != -1)
            return memo[n];

        // Any positive number n, can be represented
        // as sum of 1*1 + 1*1 .... n times
        // so we can initialise count with n (worst case)
        int cnt = n;

        // Go through all smaller numbers (x*x)
        // to recursively find the minimum
        for (int x = 1; x*x <= n; x++) {
            // Try subtracting x*x and add 1 (for x*x itself)
            cnt = min(cnt, 1 + minSquaresRec(n - x*x, memo));
        }

        // store the result of this subproblem
        // to avoid re-computation
        return memo[n] = cnt;
    }

    // Main function
    int minSquares(int n) {

        // Memoization array to store the results
        // Initialize all states to -1 (uncomputed)
        vector<int> memo(n + 1, -1);

        // Start the recursion from n
        return minSquaresRec(n, memo);
    }

    /*
    *
    * Dry Run (n = 6)
    * memo = [-1, -1, -1, -1, -1, -1, -1]
    *
    * minSquares(6) -> minSquaresRec(6, memo)
    * n = 6. cnt = 6.
    * x = 1: cnt = min(6, 1 + minSquaresRec(5))
    * -> minSquaresRec(5)
    * n = 5. cnt = 5.
    * x = 1: cnt = min(5, 1 + minSquaresRec(4))
    * -> minSquaresRec(4)
    * n = 4. cnt = 4.
    * x = 1: cnt = min(4, 1 + minSquaresRec(3)) -> 1 + 3 = 4
    * x = 2: cnt = min(4, 1 + minSquaresRec(0)) -> 1 + 0 = 1
    * memo[4] = 1. Return 1.
    * cnt = min(5, 1 + 1) = 2
    * x = 2: cnt = min(2, 1 + minSquaresRec(1)) -> 1 + 1 = 2
    * memo[5] = 2. Return 2.
    * cnt = min(6, 1 + 2) = 3
    * x = 2: cnt = min(3, 1 + minSquaresRec(2))
    * -> minSquaresRec(2)
    * n = 2. Return 2 (base case).
    * cnt = min(3, 1 + 2) = 3
    * memo[6] = 3. Return 3.
    *
    * Final Answer: 3
    *
    */
};
```

---

## 💡 Key Insights

- **Optimal Substructure:** The minimum squares for `n` can be found by building upon the minimum squares for smaller numbers (`n - x*x`).
- **Overlapping Subproblems:** When calculating the result for `n`, the recursive calls will repeatedly ask for the same values (e.g., `minSquares(2)` is needed for `minSquares(3)` and `minSquares(6)`).
- **Memoization** (or a bottom-up DP table) is essential to store these intermediate results and avoid `O(2^n)` exponential complexity, reducing it to `O(n * sqrt(n))`.

---

## 🧭 Further Exploration

- **Coin Change Problem:** This problem is very similar to the "Coin Change" problem, where you need to find the minimum number of coins to make a given sum. Here, our "coins" are the perfect squares (1, 4, 9, 16, ...).
- **LeetCode 279. Perfect Squares:** This is the identical problem on LeetCode.
- **Lagrange's Four-Square Theorem:** A famous theorem in number theory states that any natural number can be represented as the sum of _at most_ four integer squares. This means the answer to this problem can only be 1, 2, 3, or 4.

---

## 🔗 References

- **Original GfG Problem:** [Get Minimum Squares](https://www.geeksforgeeks.org/problems/get-minimum-squares0538/1)
- **Related Concept:** [Lagrange's Four-Square Theorem](https://en.wikipedia.org/wiki/Lagrange%27s_four-square_theorem)

---

## 🏷️ Tags

![Dynamic Programming](https://img.shields.io/badge/dynamic--programming-4285F4?style=for-the-badge&logo=google&logoColor=white)
![Memoization](https://img.shields.io/badge/memoization-E94E77?style=for-the-badge)
![Recursion](https://img.shields.io/badge/recursion-C71585?style=for-the-badge)
![Math](https://img.shields.io/badge/math-FF7F50?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/geeksforgeeks-34A853?style=for-the-badge&logo=geeksforgeeks&logoColor=white)

---

## 👨‍💻 Author

<a href="https://github.com/imnilesh18" target="_blank">
  <img src="https://img.shields.io/badge/GitHub-imnilesh18-181717?style=for-the-badge&logo=github&logoColor=white" alt="GitHub"/>
</a>

---

## 📜 License

This project is licensed under the MIT License.

<strong>Note on Educational Use:</strong><br>
This solution is provided for educational and reference purposes only. It is strongly recommended to attempt the problem independently on GeeksforGeeks before reviewing the solution. Understanding the underlying concepts is crucial for learning and growth.
