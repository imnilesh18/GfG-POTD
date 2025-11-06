# 🟧 Ways To Tile A Floor

![Ways To Tile A Floor](https://img.shields.io/badge/GFG-Medium-orange?logo=geeksforgeeks&logoColor=white)
![Accuracy](https://img.shields.io/badge/Accuracy-32.31%25-green)
![Points](https://img.shields.io/badge/Points-4-blue)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

---

> ⚠️ **Educational Use Only**: This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/problems/ways-to-tile-a-floor5836/1) problem.

---

## 📝 Problem Statement

Given a floor of dimensions `2 x n` and tiles of dimensions `2 x 1`, the task is to find the **number of ways** the floor can be tiled. A tile can either be placed horizontally i.e as a `1 x 2` tile or vertically i.e as `2 x 1` tile.

**Note**: Two tiling arrangements are considered different if the placement of at least one tile differs.

## 📊 Examples

```text
Input: n = 3
Output: 3
Explanation: We need 3 tiles to tile the board of size 2 x 3.
We can tile in following ways:
1) Place all 3 tiles vertically.
2) Place first tile vertically and remaining 2 tiles horizontally.
3) Place first 2 tiles horizontally and remaining tiles vertically.
````

```text
Input: n = 4
Output: 5
Explanation: We need 4 tiles to tile the board of size 2 x 4.
We can tile in following ways:
1) All 4 vertical
2) All 4 horizontal
3) First 2 vertical, remaining 2 horizontal.
4) First 2 horizontal, remaining 2 vertical.
5) Corner 2 vertical, middle 2 horizontal.
```

\<details\>
<summary>📖 <b>Example Breakdown (n=3)</b></summary>

To tile a `2 x 3` floor:

  - **Option A (Place Vertical)**: If we place one tile vertically at the start, we are left with a `2 x 2` floor.
  - **Option B (Place Horizontal)**: If we place tiles horizontally, we *must* place two of them stacked on top of each other to cover the full `2` height. This uses up a `2 x 2` area, leaving a `2 x 1` floor.
  - Total Ways(3) = Ways(2) + Ways(1) -\> This mirrors the Fibonacci sequence.

</details>

## 🛑 Constraints

  * `1 ≤ n ≤ 45`

-----

## 💡 Solution Approach

The problem can be solved using **Dynamic Programming** because it possesses optimal substructure and overlapping subproblems. The number of ways to tile a `2 x n` floor is the sum of ways to tile if the first tile is vertical (leaving `n-1` width) plus the ways if the first tiles are horizontal (leaving `n-2` width).

### 🧩 C++ Solution (Top-Down DP)

```cpp
// Intuition: To tile a 2xn floor, we can either place one tile vertically (reducing problem to 2x(n-1)) or place two tiles horizontally stacked (reducing problem to 2x(n-2)). This forms a Fibonacci-like recurrence: f(n) = f(n-1) + f(n-2).
// Approach: Use recursion with memoization (Top-Down DP). We maintain a 'dp' array where dp[i] stores the number of ways to tile a 2xi floor.
// Time Complexity: O(N) - We compute each state from 1 to N exactly once due to memoization.
// Space Complexity: O(N) - For the recursion stack depth and the DP array.

class Solution {
  public:
    int countRecur(int n, vector<int> &dp) {
      
        // Base Case: If n < 0, it's an invalid path (return 0). If n == 0, we successfully tiled the floor (return 1 way).
        if (n<0) return 0;
        if (n == 0) return 1;
        
        // If value is already computed and memoized, return it.
        if (dp[n] != -1) return dp[n];
        
        int ans = 0;
        
        // Option 1: Place one tile vertically, remaining width is n-1.
        ans = countRecur(n-1, dp);
        
        // Option 2: Place two tiles horizontally stacked, remaining width is n-2.
        ans += countRecur(n-2, dp);
        
        // Memoize and return the total ways for width n.
        return dp[n] = ans;
    }
    
    int numberOfWays(int n) {
        // Initialize DP array with -1. Size is n+1 to handle 1-based indexing convenience.
        vector<int> dp(n+1, -1);
        return countRecur(n, dp);
    }
};

/*
*
* Dry Run for n = 3
*
* numberOfWays(3) called -> initializes dp[-1, -1, -1, -1] -> calls countRecur(3, dp)
*
* 1. countRecur(3, dp):
* - dp[3] is -1.
* - calls countRecur(2, dp) for vertical placement.
*
* 2. countRecur(2, dp):
* - dp[2] is -1.
* - calls countRecur(1, dp) for vertical.
*
* 3. countRecur(1, dp):
* - dp[1] is -1.
* - calls countRecur(0, dp) -> returns 1 (Base Case).
* - calls countRecur(-1, dp) -> returns 0 (Base Case).
* - ans = 1 + 0 = 1.
* - dp[1] = 1. Returns 1.
*
* Back to step 2 (countRecur(2)):
* - first call returned 1.
* - calls countRecur(0, dp) for horizontal -> returns 1 (Base Case).
* - ans = 1 + 1 = 2.
* - dp[2] = 2. Returns 2.
*
* Back to step 1 (countRecur(3)):
* - first call returned 2.
* - calls countRecur(1, dp) for horizontal -> returns memoized dp[1] = 1.
* - ans = 2 + 1 = 3.
* - dp[3] = 3. Returns 3.
*
* Final Output: 3
*/
```

-----

## 🔑 Key Insights

  * **Identical to Fibonacci**: This problem is a classic variation of the Fibonacci sequence (similar to the "Climbing Stairs" problem).
  * **Base Cases Matter**: Notice `countRecur(-1)` returns 0. This neatly handles the `n=1` case where you can't place horizontal tiles, without needing an explicit `if (n == 1)` check, though adding it could slightly optimize.
  * **Constraints**: Since $N \le 45$, the result fits within a standard 32-bit integer (Fibonacci(45) is approx 1.1 billion, standard `int` holds up to \~2 billion).

## 🚀 Further Exploration

  * **Climbing Stairs**: Very similar logic (taking 1 step or 2 steps).
  * **Domino and Tromino Tiling**: A harder variation often found on LeetCode.
  * **Space Optimization**: Can you solve this using only $O(1)$ space by just keeping track of the last two values?

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

## 🏷️ Tags

-----

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

> **Note**: This repository is for educational purposes. Please do not use this code for academic dishonesty or plagiarism.
