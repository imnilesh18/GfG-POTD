# 📈 Stock Buy and Sell – Max one Transaction Allowed

![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge&logo=geeksforgeeks)
![Accuracy](https://img.shields.io/badge/Accuracy-49.33%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-yellow?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

<div align="center">
  <h3>⚠️ Educational Use Only</h3>
  <p>This repository and its content are intended solely for educational purposes.</p>
  <p>Solutions are provided for learning, practice, and reference only.</p>
  <p>Problem statement and test cases are based on the <a href="https://www.geeksforgeeks.org/problems/buy-stock-2/1">GeeksforGeeks problem</a>.</p>
</div>

---

## 📝 Problem Statement

Given an array `prices[]` of non-negative integers, representing the prices of the stocks on different days. The task is to find the maximum profit possible by buying and selling the stocks on different days when **at most one** transaction is allowed. Here one transaction means 1 buy + 1 Sell.

If it is not possible to make a profit then **return 0**.

> **Note:** Stock must be bought before being sold.

---

## 🔍 Examples

### Example 1
```python
Input: prices[] = [7, 10, 1, 3, 6, 9, 2]
Output: 8
Explanation: You can buy the stock on day 2 at price = 1 and sell it on day 5 at price = 9. Hence, the profit is 8.

```

### Example 2

```python
Input: prices[] = [7, 6, 4, 3, 1]
Output: 0
Explanation: Here the prices are in decreasing order, hence if we buy any day then we cannot sell it at a greater price. Hence, the answer is 0.

```

### Example 3

```python
Input: prices[] = [1, 3, 6, 9, 11]
Output: 10
Explanation: Since the array is sorted in increasing order, we can make maximum profit by buying at price[0] and selling at price[n-1].

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's look at `prices = [7, 10, 1, 3, 6, 9, 2]`.

1. **Initialize**: `minSoFar` = 7, `res` (max profit) = 0.
2. **Day 1 (Price 10)**: `minSoFar` is 7. Potential profit: 10 - 7 = 3. `res` becomes 3.
3. **Day 2 (Price 1)**: Current price 1 is less than `minSoFar` (7). Update `minSoFar` to 1.
4. **Day 3 (Price 3)**: Potential profit: 3 - 1 = 2. `res` remains 3.
5. **Day 4 (Price 6)**: Potential profit: 6 - 1 = 5. `res` becomes 5.
6. **Day 5 (Price 9)**: Potential profit: 9 - 1 = 8. `res` becomes 8.
7. **Day 6 (Price 2)**: Potential profit: 2 - 1 = 1. `res` remains 8.

**Result**: 8

</details>

---

## 🚧 Constraints

* $1 \le prices.size() \le 10^5$
* $0 \le prices[i] \le 10^4$

---

## 💡 Solution Approach

### Optimized Approach: One Traversal

We can solve this efficiently by iterating through the array once. The core idea is to maintain the **minimum price seen so far** as we iterate. For every day, we calculate the profit if we were to sell on that specific day (current price minus minimum price so far). We keep track of the maximum profit encountered.

```cpp
// Intuition: We need to find the largest difference between a selling price and a buying price where the buy happens before the sell. This effectively means for every selling day, we want the minimum buying price before it.
// Approach: Iterate through the array while maintaining the minimum price seen so far. For each day, calculate the potential profit if sold today (current price - min price so far) and update the maximum profit found.
// Time Complexity: O(n) - Single pass through the prices array.
// Space Complexity: O(1) - Only a few variables used for tracking state.

class Solution {
  public:
    int maxProfit(vector<int> &prices) {
  
        // Initialize min price seen so far and max profit result
        int minSoFar = prices[0], res = 0;
       
        for (int i = 1; i < prices.size(); i++) {
    
            // Update the minimum value seen so far
            minSoFar = min(minSoFar, prices[i]);
           
            // Update result if we get more profit by selling today                
            res = max(res, prices[i] - minSoFar);
        }
        return res;
    }
};

/*
*
* Dry Run
* Input: prices[] = [7, 10, 1, 3, 6, 9, 2]
*
* Initialization: minSoFar = 7, res = 0
*
* i = 1 (price 10):
* minSoFar = min(7, 10) = 7
* res = max(0, 10 - 7) = 3
*
* i = 2 (price 1):
* minSoFar = min(7, 1) = 1
* res = max(3, 1 - 1) = 3
*
* i = 3 (price 3):
* minSoFar = min(1, 3) = 1
* res = max(3, 3 - 1) = 2 -> remains 3
*
* i = 4 (price 6):
* minSoFar = min(1, 6) = 1
* res = max(3, 6 - 1) = 5
*
* i = 5 (price 9):
* minSoFar = min(1, 9) = 1
* res = max(5, 9 - 1) = 8
*
* i = 6 (price 2):
* minSoFar = min(1, 2) = 1
* res = max(8, 2 - 1) = 1 -> remains 8
*
* Output: 8
*/

```

---

## 🔑 Key Insights

* **Greedy Choice**: At any given day, to maximize profit, we ideally want to have bought the stock at the lowest possible price seen previously.
* **Dynamic Updates**: By constantly updating `minSoFar`, we ensure that for any price `prices[i]`, we calculate the maximum possible profit if we sold on day `i`.
* **Single Pass**: This avoids the  complexity of comparing every pair of days.

---

## 🚀 Further Exploration

* **Stock Buy and Sell II**: What if you can make infinite transactions?
* **Stock Buy and Sell III**: What if you are limited to exactly two transactions?
* **Kadane's Algorithm**: This problem is a variation of the Maximum Subarray Sum problem logic (specifically, calculating differences).

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/buy-stock-2/1)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

<div align="center">
<p>This project is licensed under the MIT License.</p>
<p>⚠️ <strong>Educational Use Only</strong>: Solutions are for learning and reference.</p>
</div>