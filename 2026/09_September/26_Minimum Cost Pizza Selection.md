# 🍕 Minimum Cost Pizza Selection

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/pizza-mania0155/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-60.18%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem[cite: 1].

---

## 📝 Problem Statement

Given the area of Small, Medium, and Large pizzas as `s`, `m`, and `l` units, and their respective costs as `cs`, `cm`, and `cl`, find the minimum amount of money required to buy pizzas whose total area is **at least `x`**[cite: 1]. 

You may buy any number of pizzas of each type[cite: 1].

---

## 💡 Examples

### Example 1
```text
Input: x = 16, s = 3, m = 6, l = 9, cs = 50, cm = 150, cl = 300[cite: 1]
Output: 300[cite: 1]
```
<details>
<summary>📖 Example Breakdown</summary>

* We want at least `16` sq. units of Pizza[cite: 1].
* One unit of each `s`, `m` and `l` = 3 + 6 + 9 = 18 sq units, Cost = 500[cite: 1].
* 6 units of `s` = 18 sq units, Cost = 300[cite: 1].
* 2 units of `l` = 18 sq units, Cost = 600 etc[cite: 1].
* Of all the arrangements, Minimum Cost is Rs. 300[cite: 1].
</details>

### Example 2
```text
Input: x = 10, s = 1, m = 3, l = 10, cs = 10, cm = 20, cl = 50[cite: 1]
Output: 50[cite: 1]
Explanation: Of all the Arrangements possible, Minimum Cost is Rs. 50[cite: 1].
```

---

## ⚙️ Constraints

> - `1 ≤ x ≤ 500`[cite: 1]
> - `1 ≤ s ≤ m ≤ l ≤ 100`[cite: 1]
> - `1 ≤ cs ≤ cm ≤ cl ≤ 100`[cite: 1]

---

## 🧠 Solution Approach

### Dynamic Programming (Unbounded Knapsack Variant)
This problem is a variation of the classic Unbounded Knapsack. Instead of trying to find the exact target `x`, we need an area of *at least* `x`. Since the maximum area a single pizza can add is `l`, the maximum boundary we need to check is `x + l`. We build a DP array to store the minimum cost for every exact area up to `x + l`, then find the minimum cost in the range `[x, x + l]`[cite: 1].

```cpp
// Intuition: We need the minimum cost for an area >= x. Because we can overshoot x by at most the size of the largest pizza (l), we calculate DP states up to x + l. This is an unbounded knapsack problem where we minimize cost rather than maximize profit.[cite: 1]
// Approach: Initialize a DP array of size (x + l + 1) with INT_MAX, setting dp[0] = 0. Iterate through all areas up to x + l. From each reachable state i, transition to i+s, i+m, and i+l by adding their respective costs. Finally, iterate from x to x+l to find the minimum cost achieved.[cite: 1]
// Time Complexity: O(x + l) - We traverse an array of size x + l exactly once, doing constant time (O(1)) operations at each step[cite: 1].
// Space Complexity: O(x + l) - We use a vector of size x + l + 1 to store the DP states[cite: 1].

class Solution {
  public:
    int minimumCost(int x, int s, int m, int l,
                    int cs, int cm, int cl) {

        // Compute DP up to the maximum useful area.
        int limit = x + l;
        vector<int> dp(limit + 1, INT_MAX); // dp[i] stores min cost for exactly area i

        dp[0] = 0; // Base case: 0 cost for 0 area

        // Build minimum cost for every achievable area.
        for (int i = 0; i <= limit; i++) {

            if (dp[i] == INT_MAX) // Skip unreachable states
                continue;

            if (i + s <= limit) // Buy small pizza
                dp[i + s] = min(dp[i + s], dp[i] + cs);

            if (i + m <= limit) // Buy medium pizza
                dp[i + m] = min(dp[i + m], dp[i] + cm);

            if (i + l <= limit) // Buy large pizza
                dp[i + l] = min(dp[i + l], dp[i] + cl);
        }

        // Find the minimum cost for an area of at least x.
        int res = INT_MAX;

        for (int i = x; i <= limit; i++) // Check all areas >= x up to limit
            res = min(res, dp[i]);

        return res;
    }
};

/*
*
* Dry Run
* Input: x=10, s=1, m=3, l=10, cs=10, cm=20, cl=50
* limit = 10 + 10 = 20
* dp size = 21, filled with INT_MAX. dp[0] = 0
*
* i = 0: dp[1] = 10, dp[3] = 20, dp[10] = 50
* i = 1: dp[2] = 20, dp[4] = 30, dp[11] = 60
* i = 2: dp[3] = min(20, 30) = 20, dp[5] = 40, dp[12] = 70
* i = 3: dp[4] = min(30, 30) = 30, dp[6] = 40, dp[13] = 70
* ... iterations continue ...
* 
* Searching for answer in range [x, limit] -> [10, 20]:
* min(dp[10], dp[11], ..., dp[20])
* dp[10] was directly populated as 50 (1 large pizza).
* The cost of 10 small pizzas is 100.
* The cost of 4 medium pizzas (area 12) is 80.
* Minimum value found >= area 10 is 50.
* Output: 50
*
*/
```

---

## 🔑 Key Insights

1. **Unbounded Knapsack Concept:** Since an unlimited number of pizzas can be bought, this naturally maps to an Unbounded Knapsack algorithm where the weight is the *area* and value is the *cost*[cite: 1].
2. **State Overshoot Handling:** The required area is *at least* `x`, meaning an exact match isn't strictly necessary. Setting the DP limit to `x + l` guarantees we check all minimal overshoot cases (since adding a pizza larger than `l` wouldn't be possible, and overshooting past `x + l - 1` would imply an unnecessary extra purchase)[cite: 1].

---

## 🔎 Further Exploration

- **Coin Change Problem:** A very similar DP problem where you need to make up a sum `x` with given coin denominations.
- **0/1 Knapsack Problem:** What if you could only buy one pizza of each type?
- **Rod Cutting Problem:** Maximizing profit for breaking a rod into pieces (the inverse maximization problem).

---

## 🔗 References

- **GeeksforGeeks Problem:** [Minimum Cost Pizza Selection](https://www.geeksforgeeks.org/problems/pizza-mania0155/1)[cite: 1]

---

## 👨‍💻 Author

Built with ❤️ by **[imnilesh18](https://github.com/imnilesh18)**.  
Follow me on GitHub to explore more coding solutions and projects!

---

## 🏷️ Tags

`Dynamic Programming`  `Unbounded Knapsack`  `Array` `GeeksforGeeks`  `C++`