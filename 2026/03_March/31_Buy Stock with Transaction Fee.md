# 📈 Buy Stock with Transaction Fee

![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy: 63.85%](https://img.shields.io/badge/Accuracy-63.85%25-green?style=for-the-badge)
![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

You are given an array `arr[]`, in which `arr[i]` is the price of a given stock on the `i`th day and an integer `k` represents a **transaction fee**. Find the **maximum profit** you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.

**Note:** You may not engage in **multiple transactions** simultaneously (i.e., you must sell the stock before you buy again).

---

## 💡 Examples

```text
Input: arr[] = [6, 1, 7, 2, 8, 4], k = 2
Output: 8
Explanation:
Buy the stock on day 2 and sell it on day 3 => 7 - 1 - 2 = 4
Buy the stock on day 4 and sell it on day 5 => 8 - 2 - 2 = 4
Maximum Profit = 4 + 4 = 8
```

```text
Input: arr[] = [7, 1, 5, 3, 6, 4], k = 1
Output: 5
Explanation: 
Buy the stock on day 2 and sell it on day 3 => 5 - 1 - 1 = 3
Buy the stock on day 4 and sell it on day 5 => 6 - 3 - 1 = 2
Maximum Profit = 3 + 2 = 5
```

<details>
<summary>📖 <b>Example Breakdown (Example 1)</b></summary>

Given prices `[6, 1, 7, 2, 8, 4]` and transaction fee `k = 2`:
- We want to maximize profit by picking non-overlapping buy-sell intervals.
- The best times to buy are when prices dip locally, and to sell when prices peak locally, considering the fee.
- If we buy at `1` (Day 2) and sell at `7` (Day 3), profit is `7 - 1 - 2(fee) = 4`.
- If we buy at `2` (Day 4) and sell at `8` (Day 5), profit is `8 - 2 - 2(fee) = 4`.
- Total accumulated profit = `4 + 4 = 8`.
- Any other combination yields a smaller profit due to the recurring transaction fee `k`.

</details>

---

## ⚙️ Constraints

- `1 ≤ arr.size() ≤ 10^6`
- `1 ≤ arr[i] ≤ 10^6`
- `0 ≤ k ≤ 10^6`

---

## 💻 Solution Approach

Here is the optimized approach using Dynamic Programming with state variables to achieve $O(N)$ Time and $O(1)$ Space.

```cpp
// Intuition: We can model this problem using dynamic programming with state transitions. At any given day, we can either have a stock (inHand) or not have a stock (noStock). We want to maximize our profit at each step going backwards.
// Approach: We iterate from the last day to the first day. `noStock` represents the max profit if we don't own a stock on day `i` (we can either skip or buy). `inHand` represents the max profit if we own a stock on day `i` (we can either skip or sell, paying the fee `k`). We update these states iteratively.
// Time Complexity: O(n) where n is the number of days, as we only traverse the array once.
// Space Complexity: O(1) since we only use a few variables (noStock, inHand, newNoStock, newInHand) to keep track of the states, regardless of the input size.

class Solution {
  public:
    int maxProfit(vector<int> &arr, int k) {
        int n = arr.size(); // Total number of days
    
        // noStock: max profit if we don't hold a stock
        // inHand: max profit if we currently hold a stock
        int noStock = 0, inHand = 0;
    
        for (int i = n - 1; i >= 0; i--) {
    
            // Choose to buy or skip
            int newNoStock = max(noStock, inHand - arr[i]);
    
            // Choose to sell (and pay fee k) or skip
            int newInHand = max(inHand, arr[i] - k + noStock);
    
            // Update states for the next iteration
            noStock = newNoStock;
            inHand = newInHand;
        }
    
        // Return the max profit when no stock is held on day 0
        return noStock;
    }
};

/*
*
* Dry Run
* arr = [6, 1, 7], k = 2
* n = 3
* Initialize noStock = 0, inHand = 0
*
* i = 2 (arr[2] = 7)
* newNoStock = max(0, 0 - 7) = 0
* newInHand = max(0, 7 - 2 + 0) = 5
* noStock = 0, inHand = 5
*
* i = 1 (arr[1] = 1)
* newNoStock = max(0, 5 - 1) = 4
* newInHand = max(5, 1 - 2 + 0) = 5
* noStock = 4, inHand = 5
*
* i = 0 (arr[0] = 6)
* newNoStock = max(4, 5 - 6) = 4
* newInHand = max(5, 6 - 2 + 4) = 8
* noStock = 4, inHand = 8
*
* Final Result: noStock = 4
*/
```

---

## 🔍 Key Insights

- **State Machine Optimization:** Instead of maintaining a full `N x 2` 2D array, we compress the space to `O(1)` by noticing that the state on day `i` relies exclusively on the state from day `i + 1`.
- **Right-to-Left Traversal:** Iterating backwards organically solves the dependency issue of "what future profit can I get if I buy/sell today?"
- **Accounting for Fee:** The fee is strictly subtracted when a sell decision is evaluated, ensuring it is paid once per valid transaction pair.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might want to try these similar challenges:
- **Best Time to Buy and Sell Stock I** (Only 1 transaction allowed)
- **Best Time to Buy and Sell Stock II** (Infinite transactions, no fee)
- **Best Time to Buy and Sell Stock with Cooldown** (1 day cooldown after selling)

---

## 🔗 References

- **GeeksForGeeks Problem:** [Buy Stock with Transaction Fee](https://www.geeksforgeeks.org/problems/buy-stock-with-transaction-fee/1)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#Dynamic-Programming` `#Arrays` `#Algorithms` `#GeeksforGeeks` `#State-Machine`