# 🌳 Balanced Binary Tree Counter

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy: 38.47%](https://img.shields.io/badge/Accuracy-38.47%25-blue?style=for-the-badge)
![Points: 2](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a height `h`, find the maximum number of distinct balanced binary trees of height exactly `h`. 

A binary tree is balanced if, for every node, the heights of its left and right subtrees differ by at most `1`. 
* A tree with a single node has height `1`. 
* An empty tree has height `0`.

**Note:** Since the answer can be very large, return it modulo `10^9 + 7`.

---

## 💡 Examples

<details>
<summary>📖 <strong>Example Breakdown (h = 3)</strong></summary>

```text
Input: h = 3
Output: 15
Explanation: 15 distinct balanced trees of height 3 exist.
A tree of height 3 can be formed by combining subtrees of heights:
- (2, 2)
- (2, 1)
- (1, 2)
Using the counts from lower heights, the mathematical combinations yield exactly 15 distinct structural variations.

```

```text
Input: h = 1
Output: 1
Explanation: Only one tree of height 1 exists i.e., a single node.

```

```text
Input: h = 2
Output: 3
Explanation: 3 distinct balanced trees of height 2 exist.

```
</details>

## ⚠️ Constraints

> * `1 ≤ h ≤ 10^6`
> 
> 

---

## 🛠️ Solution Approach

### Dynamic Programming (Space Optimized)

**Summary:**
A balanced binary tree of height `h` requires its left and right subtrees to have a height difference of at most 1. This gives us three possible height combinations for the subtrees: `(h-1, h-1)`, `(h-1, h-2)`, and `(h-2, h-1)`. This translates to a clear mathematical recurrence relation: `dp[i] = dp[i-1] * dp[i-1] + 2 * dp[i-1] * dp[i-2]`. Factoring this out gives `dp[i-1] * (2 * dp[i-2] + dp[i-1])`. By tracking only the last two computed heights, we reduce the space complexity from `O(h)` to `O(1)`.

```cpp
// Intuition: A balanced binary tree of height h requires its subtrees to have a height difference of at most 1. This means the subtrees can either both be of height h-1, or one is h-1 and the other is h-2. This builds a clear mathematical recurrence relation based on previously calculated heights.
// Approach: We use Dynamic Programming. Let dp[i] be the count of balanced trees of height i. The transition is dp[i] = dp[i-1] * (2 * dp[i-2] + dp[i-1]). Since dp[i] only depends on dp[i-1] and dp[i-2], we can achieve O(1) space by tracking only the last two results instead of an entire array.
// Time Complexity: O(h) because we run a single loop from 2 to h doing constant time arithmetic operations.
// Space Complexity: O(1) because we only use three variables to keep track of the tree counts.

class Solution {
  public:
    int countBT(int h) {
        // base cases for height 0 or 1
        if (h == 0 || h == 1) return 1;
        
        long long mod = 1e9 + 7;
        
        // represents trees of height i-2
        long long dp0 = 1;
        
        // represents trees of height i-1
        long long dp1 = 1;
        
        // stores current trees of height i
        long long dp2 = 0;
        
        for (int i = 2; i <= h; ++i) {
            // calculate dp[i] = dp[i-1] * (2 * dp[i-2] + dp[i-1]) % mod
            dp2 = (dp1 * ((2 * dp0) % mod + dp1) % mod) % mod;
            
            // shift states for the next iteration
            dp0 = dp1;
            dp1 = dp2;
        }
        
        return dp2;
    }
};

/*
Dry Run

Input: h = 3
Constant mod = 1000000007

Initialization:
dp0 = 1
dp1 = 1
dp2 = 0

Iteration i = 2:
Calculate dp2 = (dp1 * (2 * dp0 + dp1)) % mod
dp2 = (1 * (2 * 1 + 1)) = 3
Update states:
dp0 becomes 1
dp1 becomes 3

Iteration i = 3:
Calculate dp2 = (dp1 * (2 * dp0 + dp1)) % mod
dp2 = (3 * (2 * 1 + 3)) = 15
Update states:
dp0 becomes 3
dp1 becomes 15

Loop finishes.
Return dp2 which holds the value 15.
*/

```

---

## 🧠 Key Insights

* **Recurrence Relation:** The problem boils down to understanding how trees of height `h` are constructed from trees of height `h-1` and `h-2`.
* **State Shifting:** Just like calculating the Fibonacci sequence efficiently, you don't need a full array of size `h` to store the answers. You only ever look back `2` steps, allowing space optimization using three variables (`dp0`, `dp1`, `dp2`).
* **Modulo Arithmetic:** Because the formula involves multiplying large numbers, taking the modulo `10^9 + 7` at every step of the calculation prevents integer overflow.

---

## 🔍 Further Exploration

* Look into standard Fibonacci sequence optimizations.
* Practice other structural tree DP problems like "Count Unique BSTs" (Catalan Numbers).

---

## 🔗 References

* **GeeksforGeeks Problem:** [Balanced Binary Tree Counter](https://www.geeksforgeeks.org/problems/bbt-counter4914/1)

---

## 👨‍💻 Author

**Nilesh Kumar**

* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#mathematics` `#tree` `#dynamic-programming` `#geeksforgeeks` `#cpp`