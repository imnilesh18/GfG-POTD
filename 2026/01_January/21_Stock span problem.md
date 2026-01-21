# 📈 Stock Span Problem

![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks)
![Accuracy](https://img.shields.io/badge/Accuracy-43.56%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-lightgrey?style=for-the-badge)

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

The **Stock Span Problem** is a financial problem where we have a series of daily price quotes for a stock and we need to calculate the **span** of stock price for all days.

You are given an array `arr[]` representing daily stock prices. The **stock span** for the `i-th` day is the number of consecutive days up to day `i` (including day `i` itself) for which the price of the stock is **less than or equal to** the price on day `i`.

Return the span of stock prices for each day in the given sequence.

### 🔗 Constraints
- $1 \leq arr.size() \leq 10^5$
- $1 \leq arr[i] \leq 10^5$

---

## 🎯 Examples

### Example 1
```text
Input: arr[] = [100, 80, 90, 120]
Output: [1, 1, 2, 4]

```

<details>
<summary>📖 <strong>Example Breakdown</strong></summary>

* **Day 0 (100)**: Greater than or equal to itself only. No previous days. Span = 1.
* **Day 1 (80)**: Greater than or equal to itself. Smaller than previous day (100). Span = 1.
* **Day 2 (90)**: Greater than 80 and 90. Smaller than 100. Consecutive days: [80, 90]. Span = 2.
* **Day 3 (120)**: Greater than 100, 80, 90, 120. All previous prices are smaller. Span = 4.

</details>

### Example 2

```text
Input: arr[] = [10, 4, 5, 90, 120, 80]
Output: [1, 1, 2, 4, 5, 1]

```

---

## 💡 Solution Approach

### Optimized Approach: Monotonic Stack

#### Intuition

The naive approach checks all previous elements for every day, leading to  complexity. We can optimize this by observing that we only need to find the **index of the previous greater element**. Everything between that index and the current index is guaranteed to be smaller or equal.

Using a stack, we can maintain prices in a way that allows us to quickly "skip" over smaller prices. Specifically, we store pairs of `(price, span)` in the stack. If the current price is greater than the stack top, we can add the top's accumulated span to the current day's span and pop it, effectively merging the spans of smaller elements.

#### Code

```cpp
// Intuition: Use a monotonic stack to efficiently aggregate spans of consecutive smaller previous prices.
// Approach: Iterate through prices, popping elements from stack <= current price and accumulating their spans. Push current {price, total_span}.
// Time Complexity: O(N) - Each element is pushed and popped at most once.
// Space Complexity: O(N) - Stack stores at most N elements in the worst case (decreasing order).

class Solution {
  public:
    vector<int> calculateSpan(vector<int>& arr) {
        int n = arr.size();
        vector<int> span(n, 0);
        stack<pair<int, int>> st; // pair of(price, span)
        
        for(int i = 0; i < n; i++) {
            int currSpan = 1; // Default span is 1 (the day itself)
            
            // While stack isn't empty and top price is less/equal to current
            while(!st.empty() && st.top().first <= arr[i]) {
                currSpan = currSpan + st.top().second; // Add the span of the smaller element
                st.pop(); // Remove the smaller element since it's covered by current
            }
            st.push({arr[i], currSpan}); // Push current price and its calculated total span
            span[i] = currSpan; // Store result
        }
        return span;
    }
};

/*
*
* Dry Run
* Input: arr = [100, 80, 90, 120]
*
* i = 0, Price = 100
* - Stack empty.
* - currSpan = 1.
* - Push {100, 1}. Stack: [{100, 1}]
* - span[0] = 1.
*
* i = 1, Price = 80
* - Top (100) > 80. Loop condition fails.
* - currSpan = 1.
* - Push {80, 1}. Stack: [{100, 1}, {80, 1}]
* - span[1] = 1.
*
* i = 2, Price = 90
* - Top (80) <= 90.
* - currSpan = 1 + 1 = 2.
* - Pop {80, 1}. Stack: [{100, 1}]
* - Top (100) > 90. Loop ends.
* - Push {90, 2}. Stack: [{100, 1}, {90, 2}]
* - span[2] = 2.
*
* i = 3, Price = 120
* - Top (90) <= 120.
* - currSpan = 1 + 2 = 3.
* - Pop {90, 2}. Stack: [{100, 1}]
* - Top (100) <= 120.
* - currSpan = 3 + 1 = 4.
* - Pop {100, 1}. Stack: []
* - Stack empty. Loop ends.
* - Push {120, 4}. Stack: [{120, 4}]
* - span[3] = 4.
*
* Final Output: [1, 1, 2, 4]
*/

```

---

## 🔑 Key Insights

1. **Monotonic Stack**: This problem is a variation of the "Nearest Greater Element to the Left". Instead of finding the index, we are effectively calculating the distance.
2. **Span Compression**: By storing the `span` directly in the stack (or calculating it via indices), we avoid re-scanning elements that have already been "consumed" by a larger element on the right.
3. **Linear Time**: Even though there is a `while` loop inside the `for` loop, every element is added to the stack once and removed at most once, guaranteeing  total operations.

---

## 🚀 Further Exploration

* **Stock Span Problem (LeetCode Version)**: Often implemented as a class `StockSpanner`.
* **Next Greater Element**: Find the next greater element for every element.
* **Largest Rectangle in Histogram**: Another classic problem solvable with a monotonic stack.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/stock-span-problem-1587115621/1)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## ⚖️ License

**MIT License**

This project is open-source and available under the MIT License.

> **Note**: This repository is for educational purposes only. Please solve the problems on your own before referring to the solutions.
