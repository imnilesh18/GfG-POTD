# 🎨 Painting the Fence

[![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/painting-the-fence3727/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge)](#)
[![Accuracy: 32.89%](https://img.shields.io/badge/Accuracy-32.89%25-green?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a fence with `n` posts and `k` colours, find out the number of ways of painting the fence so that **not more than two** consecutive posts have the same colours.

*Note: Answers are guaranteed to be fit into a 32-bit integer.*

---

## 💡 Examples

### Example 1
```text
Input: n = 3, k = 2
Output: 6
Explanation: Let the 2 colours be 'R' and 'B'. We have following possible combinations:
1. RRB
2. RBR
3. RBB
4. BRR
5. BRB
6. BBR
```

### Example 2
```text
Input: n = 2, k = 4
Output: 16
Explanation: After coloring first post with 4 possible combinations, you can still color next posts with all 4 colors. Total possible combinations will be 4x4=16
```

<details>
<summary>📖 Example Breakdown (n = 3, k = 2)</summary>

When we have `n = 3` posts and `k = 2` colors (let's say Red `R` and Blue `B`):
- The **first post** can be painted in `2` ways (`R` or `B`).
- The **second post** can be painted in `2` ways, leading to `2 * 2 = 4` ways (`RR`, `RB`, `BR`, `BB`).
- The **third post** needs to follow the rule: *no more than two adjacent posts can have the same color*.
  - If post 1 & 2 are the **same** (e.g., `RR`), post 3 **must** be different (`B`) ➔ `RRB`.
  - If post 1 & 2 are **different** (e.g., `RB`), post 3 can be anything (`R` or `B`) ➔ `RBR`, `RBB`.
  
Total valid combinations: `RRB, RBR, RBB, BRR, BRB, BBR` = **6**.
</details>

---

## 🚫 Constraints

> - `1 ≤ n ≤ 300`
> - `1 ≤ k ≤ 10^5`

---

## 💻 Solution Approach

### Top-Down Dynamic Programming (Memoization)

**Intuition:** The total ways to paint the `n`-th post is the sum of two scenarios:
1. The `n`-th post has a **different** color than the `(n-1)`-th post.
2. The `n`-th post has the **same** color as the `(n-1)`-th post (which implies the `(n-1)`-th post must have had a different color from the `(n-2)`-th post to avoid three in a row).

```cpp
// Intuition: The number of ways to paint the nth post depends on whether it has the same color as the (n-1)th post or a different color. To avoid three consecutive identical colors, if the nth post shares the color of the (n-1)th post, the (n-1)th post must differ from the (n-2)th post.
// Approach: 1) Handle base cases for n=1 and n=2. 2) Use memoization to store previously computed results for n posts. 3) Calculate ways if the last post has a different color: countWaysRecur(n-1) * (k-1). 4) Calculate ways if the last two posts have the same color: countWaysRecur(n-2) * (k-1). 5) Sum these two possibilities and return.
// Time Complexity: O(n) - Each state from 1 to n is computed exactly once due to memoization.
// Space Complexity: O(n) - Space is used by the recursion call stack and the memoization array.

class Solution {
  public:
    int countWaysRecur(int n, int k, vector<int> &memo) {
        
        // base cases: 1 post = k ways, 2 posts = k*k ways
        if (n == 1) return k;
        if (n == 2) return k*k;
        
        // return already computed states
        if (memo[n] != -1) return memo[n];
        
        // Ways in which last fence 
        // is of different color.
        int cnt1 = countWaysRecur(n-1, k, memo)*(k-1);
        
        // Ways in which last 2 fences
        // are of same color.
        int cnt2 = countWaysRecur(n-2, k, memo)*(k-1);
        
        // store the result in memo and return
        return memo[n] = cnt1+cnt2;
    }
    
    // Returns count of ways to color k posts
    int countWays(int n, int k) {
        
        // initialize memoization array with -1
        vector<int> memo(n + 1, -1);
        return countWaysRecur(n, k, memo);
    }
};

/*
*
* Dry Run
*
* Input: n = 3, k = 2
*
* Call countWays(3, 2):
* Initializes memo array of size 4 with -1: [-1, -1, -1, -1]
* Calls countWaysRecur(3, 2, memo)
*
* Inside countWaysRecur(3, 2, memo):
* n=3 is not 1 or 2, memo[3] is -1.
* Evaluates cnt1: countWaysRecur(2, 2, memo) * (2-1)
* countWaysRecur(2, 2, memo) hits base case n=2, returns 2*2 = 4
* cnt1 = 4 * 1 = 4
*
* Evaluates cnt2: countWaysRecur(1, 2, memo) * (2-1)
* countWaysRecur(1, 2, memo) hits base case n=1, returns 2
* cnt2 = 2 * 1 = 2
*
* memo[3] = cnt1 + cnt2 = 4 + 2 = 6
* Returns 6
*
* Output: 6
*
*/
```

---

## 🧠 Key Insights

- **State Transition:** The core logic lies in the relation `Ways(n) = (Ways(n-1) + Ways(n-2)) * (k-1)`. By understanding how the current post's color depends on the historical choices of the previous one or two posts, we can efficiently narrow down valid combinations without generating them.
- **Memoization Avoids TLE:** A naive recursion would result in an exponential time complexity of $O(2^n)$. By caching the subproblem solutions in our `memo` array, we compress the time strictly down to $O(n)$.

---

## 🔍 Further Exploration

- [House Robber](https://leetcode.com/problems/house-robber/) - Similar dynamic programming pattern checking adjacent conditions.
- [Decode Ways](https://leetcode.com/problems/decode-ways/) - Another excellent sequence-based DP problem.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Painting the Fence](https://www.geeksforgeeks.org/problems/painting-the-fence3727/1)
- **Concept Reference:** Introduction to Dynamic Programming and Recurrence Relations.

---

## 👨‍💻 Author

**Nilesh** [![GitHub Profile](https://img.shields.io/badge/GitHub-imnilesh18-181717?style=flat-square&logo=github)](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Arrays` `Dynamic Programming` `Data Structures` `Algorithms` `Memoization` `GeeksForGeeks`