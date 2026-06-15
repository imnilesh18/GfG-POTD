# 🍊 Minimum Cost to Fill Given Weight

[![Link to GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/minimum-cost-to-fill-given-weight-in-a-bag1956/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-FFA116)](https://www.geeksforgeeks.org/problems/minimum-cost-to-fill-given-weight-in-a-bag1956/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-25.56%25-18A558)](https://www.geeksforgeeks.org/problems/minimum-cost-to-fill-given-weight-in-a-bag1956/1)
[![Points](https://img.shields.io/badge/Points-4-1C7ED6)](https://www.geeksforgeeks.org/problems/minimum-cost-to-fill-given-weight-in-a-bag1956/1)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org) problem.

---

## 📝 Problem Statement

Given a bag of size $w$ kg and you are provided costs of packets different weights of oranges in array `cost[]`, find the minimum total cost to buy exactly $w$ kg oranges. 

The cost of **1 kg** orange is present at index `0` and in general `cost[i]` has cost of `(i+1)` kg orange. 
`cost[i] = -1` means that `(i+1)` kg packet of orange is unavailable.

If it is not possible to buy exactly $w$ kg oranges then return `-1`. It may be assumed that there is an infinite supply of all available packet types.

---

## 💡 Examples

**Example 1:**

```text
Input: cost[] = [20, 10, 4, 50, 100], w = 5
Output: 14
Explanation: The minimum cost is 14 by purchasing a 2kg packet for 10 and a 3kg packet for 4.

```

**Example 2:**

```text
Input: cost[] = [-1, -1, 4, 3, -1], w = 5
Output: -1
Explanation: It is not possible to buy exactly 5 kgs.

```

* **Target Weight:** $w = 5$
* **Costs:**
* 1kg packet = 20
* 2kg packet = 10
* 3kg packet = 4
* 4kg packet = 50
* 5kg packet = 100


* We can form 5kg in several ways:
* 5 packets of 1kg = $5 \times 20 = 100$
* 1 packet of 5kg = $100$
* 1 packet of 2kg + 1 packet of 3kg = $10 + 4 = 14$


* The minimum cost configuration is picking the 2kg and 3kg packets, resulting in a total cost of **14**.

---

## 🚧 Constraints

> * $1 \le \text{cost.size()}, w \le 2*10^3$
> * $1 \le \text{cost}[i] \le 10^5$
> 
> 

---

## 🛠️ Solution Approaches

### 1. Dynamic Programming (Unbounded Knapsack)

**Brief Summary / Intuition:**
This problem perfectly maps to the classical Unbounded Knapsack Problem. We have a target capacity ($w$) and items of specific weights ($1$ to $n$) with corresponding costs. Since we can pick any available packet an infinite number of times, we evaluate the minimum cost at every weight step up to $w$ using a 2D DP array.

```cpp
// Intuition: This is a variation of the Unbounded Knapsack problem. We need to completely fill a bag of capacity 'w' using packets of various weights (1 to n) with given costs. Since we can pick any packet an infinite number of times, we minimize the total cost to exactly match the target weight.
// Approach: We use a 2D DP table where dp[i][j] represents the minimum cost to make weight 'j' using the first 'i' types of orange packets. We initialize the DP table with a very large value to represent impossible states. Base case is dp[i][0] = 0. For each packet, if its weight (i) is less than or equal to current target weight (j) and it's available (cost != -1), we take the minimum of either including the packet (cost[i-1] + dp[i][j-i]) or excluding it (dp[i-1][j]).
// Time Complexity: O(n * w) where n is the size of the cost array and w is the target weight, as we iterate through a 2D DP table.
// Space Complexity: O(n * w) to store the 2D DP table of dimensions (n+1) x (w+1).

class Solution {
  public:
    int minimumCost(vector<int> &cost, int w) {
        // start by determining available packet types
        int n = cost.size();
        
        // Initialize a 2D DP table with a large value representing infinity
        vector<vector<int>> dp(n + 1, vector<int>(w + 1, 1e9));
        
        // Base case: 0 cost to make exactly 0 weight
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }
        
        // Fill the DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= w; j++) {
                // Check if packet is available and fits in current weight 'j'
                if (cost[i - 1] != -1 && i <= j) {
                    // Take the minimum of including or excluding the current packet
                    dp[i][j] = min(dp[i - 1][j], cost[i - 1] + dp[i][j - i]);
                } else {
                    // Packet unavailable or strictly heavier than 'j', so exclude it
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        
        // If the target weight 'w' is still infinity, it's impossible to fill
        return dp[n][w] == 1e9 ? -1 : dp[n][w];
    }
};

/*
Dry Run

Input: cost = [20, 10, 4], w = 3
n = 3, w = 3

Initialization:
Create dp table of size 4x4 filled with 1e9 (infinity).
Set dp[i][0] = 0 for all i from 0 to 3.

Processing:
i = 1 (Weight 1, Cost 20):
j = 1: Fits. min(dp[0][1], 20 + dp[1][0]) = min(1e9, 20) = 20
j = 2: Fits. min(dp[0][2], 20 + dp[1][1]) = min(1e9, 40) = 40
j = 3: Fits. min(dp[0][3], 20 + dp[1][2]) = min(1e9, 60) = 60

i = 2 (Weight 2, Cost 10):
j = 1: Doesn't fit. dp[2][1] = dp[1][1] = 20
j = 2: Fits. min(dp[1][2], 10 + dp[2][0]) = min(40, 10) = 10
j = 3: Fits. min(dp[1][3], 10 + dp[2][1]) = min(60, 10 + 20) = 30

i = 3 (Weight 3, Cost 4):
j = 1: Doesn't fit. dp[3][1] = dp[2][1] = 20
j = 2: Doesn't fit. dp[3][2] = dp[2][2] = 10
j = 3: Fits. min(dp[2][3], 4 + dp[3][0]) = min(30, 4) = 4

Final Result:
Return dp[3][3]
Result is 4.
*/

```

---

## 🔑 Key Insights

* **Unbounded Capacity:** Unlike standard 0/1 knapsack where you only pick an item once, here `dp[i][j - i]` is used instead of `dp[i - 1][j - i]` allowing the algorithm to pick the same weight multiple times.
* **Infinity State:** Initializing impossible sums with an arbitrarily large number (like `1e9`) helps securely compare minimums without integer overflow.
* **Missing Items:** Dealing with `-1` conditions correctly ensures that unavailable packets never impact the DP logic.

---

## 🔭 Further Exploration

* **Coin Change Problem:** A very similar structural problem aiming to make a target amount with the fewest coins.
* **Knapsack with Duplicate Items:** General Unbounded Knapsack Problems on GfG.
* **Space Optimization:** The 2D DP array can be reduced to a 1D array `dp[w+1]` because the current state `i` only depends on the previous row `i-1` and earlier column values in the same row `i`.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Minimum Cost to Fill Given Weight](https://www.geeksforgeeks.org/problems/minimum-cost-to-fill-given-weight-in-a-bag1956/1)
* **Related Concepts:** [Unbounded Knapsack Algorithm](https://www.geeksforgeeks.org/unbounded-knapsack-repetition-items-allowed/)

---

## 🧑‍💻 Author

**Nilesh**

* GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

* `Dynamic Programming`
* `Algorithms`
* `Unbounded Knapsack`
* `GeeksforGeeks`