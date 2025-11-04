# 🐸 Frog Jump

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-49.55%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)

---

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/geek-jump/1).

---

## Problem Statement

Given an integer array `height[]` where `height[i]` represents the height of the `i-th` stair, a frog starts from the **first stair** and wants to reach the **last stair**.

From any stair `i`, the frog has two options:
1.  Jump to the `(i+1)th` stair.
2.  Jump to the `(i+2)th` stair.

The cost of a jump is the **absolute difference** in height between the two stairs. Determine the **minimum total cost** required for the frog to reach the last stair.

## Examples

**Example 1:**

```
Input: heights[] = [20, 30, 40, 20]
Output: 20
Explanation:
Minimum cost is incurred when the frog jumps from stair 0 to 1 then 1 to 3:
jump from stair 0 to 1: cost = |30 - 20| = 10
jump from stair 1 to 3: cost = |20 - 30| = 10
Total Cost = 10 + 10 = 20
```

<details>
<summary>📖 Example 1 Breakdown</summary>

Let's trace `heights[] = [20, 30, 40, 20]` (n=4).
The frog starts at index 0 (height 20) and wants to reach index 3 (height 20).

**Path 1: 0 -> 1 -> 2 -> 3**
* Jump 0 -> 1: `|30 - 20| = 10`
* Jump 1 -> 2: `|40 - 30| = 10`
* Jump 2 -> 3: `|20 - 40| = 20`
* *Total Cost: 10 + 10 + 20 = 40*

**Path 2: 0 -> 1 -> 3**
* Jump 0 -> 1: `|30 - 20| = 10`
* Jump 1 -> 3: `|20 - 30| = 10`
* *Total Cost: 10 + 10 = 20*

**Path 3: 0 -> 2 -> 3**
* Jump 0 -> 2: `|40 - 20| = 20`
* Jump 2 -> 3: `|20 - 40| = 20`
* *Total Cost: 20 + 20 = 40*

Comparing the total costs (40, 20, 40), the minimum cost is **20**.

</details>

**Example 2:**

```
Input: heights[] = [30, 20, 50, 10, 40]
Output: 30
Explanation:
Minimum cost will be incurred when frog jumps from stair 0 to 2 then 2 to 4:
jump from stair 0 to 2: cost = |50 - 30| = 20
jump from stair 2 to 4: cost = |40 - 50| = 10
Total Cost = 20 + 10 = 30
```

## Constraints

> ```
> 1 ≤ height.size() ≤ 10^5
> 0 ≤ height[i] ≤ 10^4
> ```

---

## Solution Approaches

### 1. Recursion (Brute-Force)

This approach uses a simple recursive function, `solve(i)`, which calculates the minimum cost to reach the end (`n-1`) from the current stair `i`.

At each stair `i`, the function explores both possible moves:
1.  **1-Jump:** Jump to `i+1` and recursively find the cost from there.
2.  **2-Jump:** Jump to `i+2` (if it's a valid stair) and recursively find the cost from there.

The function then returns the minimum of these two path costs. This approach is intuitive but inefficient as it repeatedly calculates the cost for the same stairs (overlapping subproblems).

```cpp
// Intuition: To find the minimum cost to reach the end from stair 'i',
// we can find the cost of taking one step (to i+1) and the cost of
// taking two steps (to i+2), and choose the minimum of these two paths.
// Approach:
// 1. Create a recursive function `solve(i)` which returns the min cost from index `i` to `n-1`.
// 2. Base Case: If `i == n-1` (at the last stair), return 0 cost.
// 3. Recursive Step 1 (1-Jump): Calculate `cost1 = abs(h[i+1] - h[i]) + solve(i+1)`.
// 4. Recursive Step 2 (2-Jump): If `i+2 < n`, calculate `cost2 = abs(h[i+2] - h[i]) + solve(i+2)`.
// 5. Return `min(cost1, cost2)`.
// Time Complexity: O(2^n) - For each stair, we have two choices (1-jump or 2-jump),
// leading to an exponential number of calls.
// Space Complexity: O(n) - Due to the recursive call stack depth.
class Solution {
public:
    int solve(vector<int>& height, int i, int n) {
        // Base Case: We've reached the last stair. No more cost.
        if (i == n - 1) {
            return 0; // Cost to stay at the last stair is 0
        }

        // --- Option 1: Jump to i + 1 ---
        // This jump is always possible unless we are already at the end (handled by base case).
        // Cost = (cost of this jump) + (min cost from the next stair)
        int jump1_cost = abs(height[i + 1] - height[i]) + solve(height, i + 1, n);

        // --- Option 2: Jump to i + 2 ---
        int jump2_cost = INT_MAX; // Assume it's impossible initially (if n is small)
        
        // We can only make a 2-step jump if it's within bounds
        if (i + 2 < n) {
            // Cost = (cost of this 2-step jump) + (min cost from that stair)
            jump2_cost = abs(height[i + 2] - height[i]) + solve(height, i + 2, n);
        }

        // Return the minimum cost of the two options
        return min(jump1_cost, jump2_cost);
    }

    int minCost(vector<int>& height) {
        int n = height.size();
        if (n == 1) {
            return 0; // Already at the destination
        }
        // Start from the first stair (index 0)
        return solve(height, 0, n);
    }
};
/*
*
* Dry Run
*
* Input: height[] = [20, 30, 40, 20], n = 4
*
* solve(0, 4):
* -> jump1_cost = abs(30-20) + solve(1, 4) = 10 + solve(1)
* -> jump2_cost = abs(40-20) + solve(2, 4) = 20 + solve(2)
*
* solve(1, 4):
* -> jump1_cost = abs(40-30) + solve(2, 4) = 10 + solve(2)
* -> jump2_cost = abs(20-30) + solve(3, 4) = 10 + solve(3)
*
* solve(2, 4):
* -> jump1_cost = abs(20-40) + solve(3, 4) = 20 + solve(3)
* -> jump2_cost = INT_MAX (since 2+2 is not < 4)
*
* solve(3, 4):
* -> Base Case: i == n-1. Returns 0.
*
* solve(2) returns min(20 + 0, INT_MAX) = 20
*
* solve(1) returns min(10 + 20, 10 + 0) = min(30, 10) = 10
*
* solve(0) returns min(10 + 10, 20 + 20) = min(20, 40) = 20
*
* Final Answer: 20
*/
```

### 2. Memoization (Top-Down Dynamic Programming)

To optimize the recursive approach, we can store the results of subproblems in a **`dp` array** (our cache). This technique is called memoization.

Before computing `solve(i)`, we check if `dp[i]` has already been computed (i.e., it's not `-1`).
* If it has, we return the cached value immediately, avoiding redundant calculations.
* If it has not, we compute it recursively (as in the brute-force approach), store the result in `dp[i]`, and then return it.

This significantly reduces the time complexity from exponential to linear.

```cpp
// Intuition: The recursive solution calculates the same subproblems (e.g., solve(2))
// multiple times. We can avoid this by storing the result of solve(i) in a
// 'dp' array (cache) and reusing it.
// Approach:
// 1. Create a `dp` array of size `n`, initialized to -1 (to mark as "not computed").
// 2. In the `solve(i)` function:
// 3. Base Case: If `i == n-1`, return 0.
// 4. Check Cache: If `dp[i]` is not -1, return `dp[i]`.
// 5. Compute: Calculate `jump1_cost` and `jump2_cost` recursively (same as before).
// 6. Save to Cache: Store the result: `dp[i] = min(jump1_cost, jump2_cost)`.
// 7. Return `dp[i]`.
// Time Complexity: O(n) - Each state `dp[i]` (from 0 to n-1) is computed
// exactly once.
// Space Complexity: O(n) - For the `dp` array + O(n) for the recursive
// call stack. Total O(n).
class Solution {
public:
    /**
     * @param height The array of stair heights.
     * @param i The current stair index the frog is on.
     * @param n The total number of stairs.
     * @param dp Our memoization table (cache). dp[i] stores min cost from i to n-1.
     */
    int solve(vector<int>& height, int i, int n, vector<int>& dp) {
        // Base Case: We've reached the last stair. No more cost.
        if (i == n - 1) {
            return 0;
        }

        // 1. CHECK CACHE:
        // If we've already computed the min cost from stair 'i', return it.
        if (dp[i] != -1) {
            return dp[i]; // Avoids re-computation
        }

        // --- Option 1: Jump to i + 1 ---
        // Recursively find the min cost from stair i+1
        int jump1_cost = abs(height[i + 1] - height[i]) + solve(height, i + 1, n, dp);

        // --- Option 2: Jump to i + 2 ---
        int jump2_cost = INT_MAX; // Assume it's impossible initially
        
        // We can only make a 2-step jump if it's within bounds
        if (i + 2 < n) {
            // Recursively find the min cost from stair i+2
            jump2_cost = abs(height[i + 2] - height[i]) + solve(height, i + 2, n, dp);
        }

        // 2. SAVE TO CACHE AND RETURN:
        // Store the minimum of the two options in our cache before returning.
        return dp[i] = min(jump1_cost, jump2_cost);
    }

    int minCost(vector<int>& height) {
        int n = height.size();
        if (n == 1) {
            return 0; // Already at the destination
        }
        
        // Initialize our DP cache with -1 (meaning "not computed yet")
        // dp[i] will store the min cost to reach the end from stair 'i'.
        vector<int> dp(n, -1);
        
        // Start the process from the first stair (index 0)
        return solve(height, 0, n, dp);
    }
};
/*
*
* Dry Run
*
* Input: height[] = [20, 30, 40, 20], n = 4
* dp = [-1, -1, -1, -1]
*
* solve(0, 4, dp):
* dp[0] is -1.
* -> jump1_cost = 10 + solve(1, 4, dp)
* -> jump2_cost = 20 + solve(2, 4, dp)
*
* solve(1, 4, dp):
* dp[1] is -1.
* -> jump1_cost = 10 + solve(2, 4, dp)
* -> jump2_cost = 10 + solve(3, 4, dp)
*
* solve(2, 4, dp):
* dp[2] is -1.
* -> jump1_cost = 20 + solve(3, 4, dp)
* -> jump2_cost = INT_MAX
*
* solve(3, 4, dp):
* -> Base Case: i == n-1. Returns 0.
*
* solve(2) computes min(20 + 0, INT_MAX) = 20.
* Saves dp[2] = 20. Returns 20.
*
* solve(1) computes:
* -> jump1_cost = 10 + dp[2] (which is 20) = 30
* -> jump2_cost = 10 + solve(3) (which is 0) = 10
* Returns min(30, 10) = 10.
* Saves dp[1] = 10. Returns 10.
*
* solve(0) computes:
* -> jump1_cost = 10 + dp[1] (which is 10) = 20
* -> jump2_cost = 20 + dp[2] (which is 20) = 40
* Returns min(20, 40) = 20.
* Saves dp[0] = 20. Returns 20.
*
* Final Answer: 20
*/
```

---

## Key Insights

* **Overlapping Subproblems:** The brute-force recursive solution is slow because it re-calculates the minimum cost for the same stair multiple times. For example, `solve(2)` is called by both `solve(1)` and `solve(0)`.
* **Optimal Substructure:** The minimum cost to reach the end from stair `i` is based on the minimum cost to reach the end from stairs `i+1` and `i+2`. This property allows us to use Dynamic Programming.
* **Memoization:** By introducing a `dp` array (the cache), we store the result for each state `i` (the minimum cost to reach the end from stair `i`). This ensures that each state is computed only once, changing the time complexity from exponential `O(2^n)` to linear `O(n)`.
* **Further Optimization:** This top-down DP (memoization) can be converted into a bottom-up DP (tabulation) or even further optimized to O(1) space, as the cost for `dp[i]` only depends on `dp[i+1]` and `dp[i+2]`.

## Further Exploration

* [Geek Jump (Minimal Cost)](https://www.geeksforgeeks.org/problems/minimal-cost/1) (The same problem, but the frog can jump up to `k` steps)
* [Climbing Stairs](https://www.geeksforgeeks.org/problems/climbing-stairs1852/1) (A similar problem focused on *counting* the number of ways)
* [House Robber](https://www.geeksforgeeks.org/problems/stickler-theif-1587115621/1) (Another classic 1D DP problem with non-adjacent choices)

## References

* [Original GfG Problem Link](https://www.geeksforgeeks.org/problems/geek-jump/1)
* [GeeksforGeeks: Dynamic Programming](https://www.geeksforgeeks.org/dynamic-programming/)

## Author

Made with ❤️ by [imnilesh18](https://github.com/imnilesh18)

## Tags

![Dynamic Programming](https://img.shields.io/badge/Dynamic_Programming-4A148C?style=for-the-badge)
![Recursion](https://img.shields.io/badge/Recursion-B39DDB?style=for-the-badge)
![Memoization](https://img.shields.io/badge/Memoization-7E57C2?style=for-the-badge)
![Array](https://img.shields.io/badge/Array-673AB7?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge)

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

This repository's content, including solutions and explanations, is provided for educational purposes only. It is intended to assist in learning and understanding data structures and algorithms.