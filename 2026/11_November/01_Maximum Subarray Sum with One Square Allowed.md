# 🧮 Maximum Subarray Sum with One Square Allowed

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-75.78%25-green?style=for-the-badge" alt="Accuracy: 75.78%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given an integer array `arr[]`, find the maximum subarray sum by squaring **at most one** element.

## 💡 Examples

### Example 1
```text
Input: arr[] = [-1, -2, 3, -2, 3]
Output: 10
Explanation: The subarray {3, -2, 3} with squaring -2 will give the maximum sum as 3 + 4 + 3 = 10.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>
<br>
Let's analyze the subarray <code>[3, -2, 3]</code>. 
If we do not square any element, the sum is <code>3 + (-2) + 3 = 4</code>.
If we square the negative element <code>-2</code>, it becomes <code>4</code>.
The new sum is <code>3 + 4 + 3 = 10</code>. This yields the maximum possible sum across all subarrays.
</details>

### Example 2
```text
Input: arr[] = [-4, -4, -2, 5, 2, -1]
Output: 27
Explanation: The subarray {5, 2} with squaring 5 will give a maximum sum of 25 + 2 = 27.
```

## ⚙️ Constraints

> - 1 ≤ `arr.size()` ≤ 10⁵
> - -10³ ≤ `arr[i]` ≤ 10³

---

## 💻 Solution Approach

**Optimized Dynamic Programming (Kadane's Variation)**

```cpp
// Intuition: We can adapt Kadane's algorithm by tracking two separate states for the subarray ending at each index: the maximum sum without squaring any element, and the maximum sum with exactly one element squared.
// Approach: Iterate through the array while maintaining 'no_square' (standard Kadane's sum) and 'with_square' (sum containing one squared element). For 'with_square', we can either square the current element (starting fresh or extending 'no_square') or extend the previous 'with_square' without squaring the current element. Keep updating the global maximum.
// Time Complexity: O(n) because we traverse the array exactly once, performing constant time operations at each step.
// Space Complexity: O(1) as we only use a few integer variables to maintain the running maximums and states.

class Solution {
  public:
    int maximumSubarray(vector<int>& arr) {
        if (arr.empty()) return 0;

        int no_square = arr[0];
        int with_square = arr[0] * arr[0];
        int max_sum = max(no_square, with_square);

        for (int i = 1; i < arr.size(); ++i) {
            int prev_no_square = no_square;

            with_square = max({
                arr[i] * arr[i],                           // Start fresh with arr[i]^2
                prev_no_square + arr[i] * arr[i],          // Extend no_square and square arr[i]
                with_square + arr[i]                       // Extend with_square without squaring arr[i]
            });

            no_square = max(arr[i], prev_no_square + arr[i]); // Standard Kadane's logic

            max_sum = max({max_sum, no_square, with_square}); // Global max check
        }

        return max_sum;
    }
};

/*
*
* Dry Run
* Input: arr = [3, -2, 3]
* Init: 
* arr[0] = 3 -> no_square = 3, with_square = 9, max_sum = 9
* i = 1 (arr[1] = -2):
* prev_no_square = 3
* with_square = max(4, 3 + 4, 9 - 2) = max(4, 7, 7) = 7
* no_square = max(-2, 3 - 2) = max(-2, 1) = 1
* max_sum = max(9, 1, 7) = 9
* i = 2 (arr[2] = 3):
* prev_no_square = 1
* with_square = max(9, 1 + 9, 7 + 3) = max(9, 10, 10) = 10
* no_square = max(3, 1 + 3) = max(3, 4) = 4
* max_sum = max(9, 4, 10) = 10
* Final Output: 10
*
*/
```

---

## 🔑 Key Insights

- This problem is a textbook state-machine dynamic programming challenge built on top of **Kadane's Algorithm**. 
- The magic happens in the `with_square` state transition. You must check all three possibilities simultaneously: starting a brand new subarray with a squared element, squaring the *current* element to boost the standard subarray sum, or simply adding the current element to a subarray that *already* utilized its one allowed square.

## 🚀 Further Exploration

- [Maximum Subarray Sum (Standard Kadane's)](https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/)
- Try variations where you can square up to `K` elements to see how this translates into a 2D DP matrix.

## 🔗 References

- **GeeksforGeeks Problem:** [Maximum Subarray Sum with One Square Allowed](https://www.geeksforgeeks.org/problems/maximum-subarray--143510/1)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

## 🏷️ Tags

`#arrays` `#dynamic-programming` `#kadanes-algorithm` `#geeksforgeeks` `#c++`