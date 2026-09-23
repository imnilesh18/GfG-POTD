<div align="center">
  
# 🟧 Pyramid Array with Reduce Operations

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/pyramid-form3044/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](#)
[![Accuracy: 67.18%](https://img.shields.io/badge/Accuracy-67.18%25-green?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](#)

</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` consisting of stones, where `arr[i]` represents the height of the i-th stone.

You need to transform the stones into a pyramid by **only reducing the heights of the stones**. Reducing the height of a stone by 1 costs 1 unit, and stones cannot be increased or moved. 

A valid pyramid consists of a contiguous subarray whose heights follow the pattern: `1, 2, 3, ..., x - 1, x, x - 1, ..., 2, 1` for some positive integer `x`. Every stone outside this subarray must have a height of `0`.

Find the **minimum total cost** required to build a pyramid. It is guaranteed that at least one valid pyramid can always be formed.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [1, 2, 3, 4, 2, 1]
Output: 4
```
<details>
<summary>📖 Example Breakdown</summary>

We can obtain the array `[1, 2, 3, 2, 1, 0]` by subtracting 2 out of 4, 1 out of 2, and 1 out of 1. 
* Original: `[1, 2, 3, 4, 2, 1]`
* Pyramid:  `[1, 2, 3, 2, 1, 0]`
* Cost: `0 + 0 + 0 + 2 + 1 + 1 = 4`

In total, we will subtract 4 units of height.
</details>

### Example 2
```text
Input: arr[] = [1, 2, 1]
Output: 0
Explanation: The array is already in a valid pyramid form.
```

---

## ⚙️ Constraints

> - `1 ≤ arr.size() ≤ 10^5`
> - `1 ≤ arr[i] ≤ 10^5`

---

## 🚀 Solution Approaches

### Optimized Dynamic Programming Approach

**Brief Summary / Intuition:**
To minimize the cost of reducing stones, we need to maximize the number of stones we keep. A perfect pyramid of peak height `h` always contains exactly `h²` stones. Therefore, our goal is to find the maximum possible valid peak height at each index. We can do this efficiently by calculating the maximum valid increasing step sequence from the left and the decreasing step sequence from the right for every index. 

```cpp
// Intuition: Minimize cost by maximizing the preserved pyramid size. A pyramid of height h takes h^2 stones. We use two arrays to track max valid heights from the left and right, and test every index as a potential peak.
// Approach: 
// 1. Calculate the sum of all elements (total initial cost).
// 2. Precompute left[] where left[i] stores the max step-up height ending at i.
// 3. Precompute right[] where right[i] stores the max step-down height starting at i.
// 4. Iterate to treat each index as the peak. Max height at i is min(left[i], right[i]).
// 5. Calculate cost as (total sum - peak_height^2) and track the minimum.
// Time Complexity: O(n) - We traverse the array a constant number of times (sum, left pass, right pass, final calculation).
// Space Complexity: O(n) - Two extra vectors, left and right, each of size n.

class Solution {
  public:
    int formPyramid(vector<int> &arr) {
        int n = arr.size();
        int totalHeight = 0;

        // Calculate the total height of all stones.
        for (int i = 0; i < n; i++)
            totalHeight += arr[i];

        // Base case: small arrays can only form a height-1 pyramid.
        if (n <= 2)
            return totalHeight - 1;

        vector<int> left(n), right(n);

        // Max possible pyramid height considering left constraints.
        left[0] = 1;
        for (int i = 1; i < n; i++)
            left[i] = min(left[i - 1] + 1, arr[i]);

        // Max possible pyramid height considering right constraints.
        right[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--)
            right[i] = min(right[i + 1] + 1, arr[i]);

        int minCost = INT_MAX;

        // Try every index as the peak of the pyramid.
        for (int i = 0; i < n; i++) {

            // Limit peak height by both side boundaries.
            int peakHeight = min(left[i], right[i]);

            // Pyramid of height h always sums to h^2.
            int pyramidSum = peakHeight * peakHeight;

            // Cost is stones removed (original total - stones kept).
            minCost = min(minCost, totalHeight - pyramidSum);
        }

        return minCost;
    }
};

/*
* Dry Run
*
* Input: arr = [1, 2, 3, 4, 2, 1]
* n = 6
* totalHeight = 1 + 2 + 3 + 4 + 2 + 1 = 13
*
* Left pass calculation:
* i=0: left[0] = 1
* i=1: min(1+1, 2) = 2
* i=2: min(2+1, 3) = 3
* i=3: min(3+1, 4) = 4
* i=4: min(4+1, 2) = 2
* i=5: min(2+1, 1) = 1
* left array: [1, 2, 3, 4, 2, 1]
*
* Right pass calculation:
* i=5: right[5] = 1
* i=4: min(1+1, 2) = 2
* i=3: min(2+1, 4) = 3
* i=2: min(3+1, 3) = 3
* i=1: min(3+1, 2) = 2
* i=0: min(2+1, 1) = 1
* right array: [1, 2, 3, 3, 2, 1]
*
* Peak cost evaluations:
* i=0: peak = min(1, 1) = 1. cost = 13 - (1*1) = 12
* i=1: peak = min(2, 2) = 2. cost = 13 - (2*2) = 9
* i=2: peak = min(3, 3) = 3. cost = 13 - (3*3) = 4
* i=3: peak = min(4, 3) = 3. cost = 13 - (3*3) = 4
* i=4: peak = min(2, 2) = 2. cost = 13 - (2*2) = 9
* i=5: peak = min(1, 1) = 1. cost = 13 - (1*1) = 12
*
* minCost = 4
*/
```

---

## 🔑 Key Insights

1. **Math Shortcut:** The sum of a perfect continuous step pyramid series (`1 + 2 + ... + h-1 + h + h-1 + ... + 2 + 1`) mathematically resolves to exactly `h²`. Knowing this eliminates the need for inner loops to calculate the retained stones!
2. **Double-Pass DP:** We cannot simply pick the peak and expand outwards, as that would be $O(n^2)$. Using a `left` and `right` constraint array allows us to process the validity of the slopes in $O(n)$ time.
3. **Inversion of Cost:** Instead of figuring out *what* to delete, we figure out *what to keep*. The minimum cost is equivalent to the original array sum minus the largest valid pyramid sum we can form.

---

## 🔍 Further Exploration

- **Longest Bitonic Subsequence:** Uses similar bidirectional DP logic to find peaks.
- **Trapping Rain Water:** Another classic array problem utilizing `leftMax` and `rightMax` precomputation arrays.
- **Candy (LeetCode 135):** Uses a very similar dual-pass DP mechanism to ensure left and right constraints are satisfied.

---

## 🔗 References

- **Original Problem:** [Pyramid form on GeeksforGeeks](https://www.geeksforgeeks.org/problems/pyramid-form3044/1)
- **Topic Reference:** [Dynamic Programming on Arrays](https://www.geeksforgeeks.org/dynamic-programming/)

---

## 👨‍💻 Author

Created & Maintained by: **[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#dynamic-programming` `#array` `#geeksforgeeks` `#c++` `#optimization`