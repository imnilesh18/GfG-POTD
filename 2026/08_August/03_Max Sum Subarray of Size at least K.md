# 🟧 Max Sum Subarray of Size at least K

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/largest-sum-subarray-of-size-at-least-k3121/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy: 37.64%](https://img.shields.io/badge/Accuracy-37.64%25-blue?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-success?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` and an integer `k`, find the maximum sum among all contiguous subarrays having a length **greater than or equal to `k`**.

### ⚙️ Constraints:
* `1 ≤ arr.size() ≤ 10^5`
* `-10^4 ≤ arr[i] ≤ 10^4`
* `1 ≤ k ≤ arr.size()`

---

## 💡 Examples

```text
Input: arr[] = [1, -2, 2, -3], k = 3
Output: 1
Explanation: The sub-array of length at least 3 that produces the greatest sum is [1, -2, 2]
```

```text
Input: arr[] = [1, 1, 1, 1, 1, 1], k = 2
Output: 6
Explanation: The sub-array of length at least 2 that produces the greatest sum is [1, 1, 1, 1, 1, 1]
```

```text
Input: arr[] = [-4, -2, 1, -3], k = 2
Output: -1
Explanation: The sub-array of length at least 2 that produces the greatest sum is [-2, 1]
```

<details>
<summary>📖 Example Breakdown</summary>

**Let's dry run the first example: `arr[] = [1, -2, 2, -3], k = 3`**

1. We need a contiguous subarray of size *at least* 3.
2. The possible subarrays of length $\ge 3$ are:
   * `[1, -2, 2]` -> Sum: $1 - 2 + 2 = 1$
   * `[-2, 2, -3]` -> Sum: $-2 + 2 - 3 = -3$
   * `[1, -2, 2, -3]` -> Sum: $1 - 2 + 2 - 3 = -2$
3. Comparing the sums: `1`, `-3`, and `-2`.
4. The maximum sum is **`1`**.
</details>

---

## 🛠️ Solution Approaches

### Optimized Sliding Window & Prefix Sum

```cpp
// Intuition: To find the maximum subarray sum of length >= K, we can use a sliding window of size K and a prefix sum tracking the elements before the window.
// Approach: First, calculate the sum of the initial K elements. Then, slide the window one element at a time. Maintain the prefix sum of elements prior to the window and track its minimum. The maximum sum ending at the current position is the current window sum minus the minimum prefix sum seen so far.
// Time Complexity: O(N) - We traverse the array exactly once, making it a linear time operation.
// Space Complexity: O(1) - We only use a few integer variables for tracking sums, requiring constant extra space.

class Solution {
  public:
    int maxSumWithK(vector<int>& arr, int k) {
        int n = arr.size();
        int maxSum = -1e9;
        int currWindowSum = 0;
        
        // Calculate initial window sum of size K
        for (int j = 0; j < k; j++) {
            currWindowSum += arr[j];
        }
        maxSum = currWindowSum;
        
        int prevSum = 0;
        int minPrevSum = 0;
        int i = 0;
        int j = k;
        
        // Expand window and process remaining elements
        while (j < n) {
            // Add the new element to the current sliding window
            currWindowSum += arr[j];
            
            // Calculate the prefix sum of elements excluded from the K-window
            prevSum += arr[i];
            
            // Update the minimum prefix sum encountered so far (to maximize our result)
            minPrevSum = min(minPrevSum, prevSum);
            
            // Update the global max sum using the minimum prefix sum
            maxSum = max(maxSum, currWindowSum - minPrevSum);
            
            // Shrink/Slide the window forward
            j++;
            i++;
        }
        
        return maxSum;
    }
};

/*
*
* Dry Run
* Input: arr = [1, -2, 2, -3], k = 3
* Initialization:
* currWindowSum (first 3 elements) = 1 + (-2) + 2 = 1
* maxSum = 1
* prevSum = 0, minPrevSum = 0
* i = 0, j = 3
*
* Iteration 1 (j = 3):
* currWindowSum += arr[3] -> 1 + (-3) = -2
* prevSum += arr[0] -> 0 + 1 = 1
* minPrevSum = min(0, 1) = 0
* maxSum = max(1, -2 - 0) = 1
* j = 4, i = 1
*
* Loop terminates (j < n is false)
* Output: 1
*
*/
```

---

## 🧠 Key Insights

* **Why it works:** A subarray of length $\ge K$ can be viewed as a fixed window of length $K$ plus a prefix subarray preceding it. By keeping track of the minimum possible prefix sum (`minPrevSum`) leading up to our sliding window, we can subtract it from our total expanding sum (`currWindowSum`) to consistently find the absolute maximum possible yield for lengths $\ge K$.
* **Sliding Window:** Rather than recalculating overlapping segments, the algorithm organically shifts right, modifying the boundary dynamically in $O(1)$ time per step.

---

## 🔍 Further Exploration
* **Kadane's Algorithm (Maximum Subarray):** Understanding standard Kadane's algorithm builds a great foundation for handling negative prefix accumulations.
* **Maximum Sum Subarray of Size K:** The standard fixed-size variant of this sliding window problem.

---

## 🔗 References
* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/largest-sum-subarray-of-size-at-least-k3121/1)

---

## 👨‍💻 Author
[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
* `dynamic-programming`
* `sliding-window`
* `arrays`
* `geeksforgeeks`