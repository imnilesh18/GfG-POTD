# 🟧 Max Absolute Diff of Two Subarrays

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/max-absolute-difference4114/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-50.44%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <a href="LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
  </a>
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array of integers `arr[]`, find two **non-overlapping contiguous sub-arrays** such that the absolute difference between the sum of two sub-arrays is maximum.

---

## 💡 Examples

**Example 1:**
```text
Input: arr[] = [-2, -3, 4, -1, -2, 1, 5, -3]
Output: 12
Explanation: Two subarrays are [-2, -3] and [4, -1, -2, 1, 5]

```

**Example 2:**

```text
Input: arr[] = [2, -1, -2, 1, -4, 2, 8]
Output: 16
Explanation: Two subarrays are [-1, -2, 1, -4] and [2, 8] 

```

* The first subarray is `[-2, -3]` with a sum of **-5**.
* The second subarray is `[4, -1, -2, 1, 5]` with a sum of **7**.
* The absolute difference between their sums is `|(-5) - 7| = |-12| = 12`.
* This yields the maximum absolute difference possible from any two non-overlapping subarrays in the given input.

---

## ⚠️ Constraints

* `2 <= arr.size() <= 10^5`
* `-10^3 <= arr[i] <= 10^3`

---

## 💻 Solution Approach

### Optimized Approach (Kadane's Algorithm Variations)

This approach leverages **Kadane's Algorithm** to precompute the maximum and minimum subarray sums for prefixes and suffixes of the array, allowing us to find the optimal split point in linear time.

```cpp
// Intuition: To maximize the absolute difference between two non-overlapping subarrays, we need to find the maximum possible subarray sum and the minimum possible subarray sum on both the left and right sides of any split point.
// Approach: 
// 1. Create four arrays: leftMax, leftMin, rightMax, and rightMin to store prefix/suffix boundaries.
// 2. Traverse from left to right using Kadane's algorithm to fill leftMax and leftMin.
// 3. Traverse from right to left to fill rightMax and rightMin.
// 4. Iterate through all possible split points and calculate the maximum absolute difference by comparing abs(leftMax - rightMin) and abs(leftMin - rightMax).
// Time Complexity: O(n) as we are doing a few linear passes over the array.
// Space Complexity: O(n) to store the prefix and suffix maximum and minimum subarray sums.
class Solution {
public:
    int maxDiffSubArrays(vector<int>& arr) {
        int n = arr.size();
        
        // Arrays to store prefix/suffix variations
        vector<int> leftMax(n), leftMin(n), rightMax(n), rightMin(n);
        
        // Variables for left-to-right pass
        int currMax = 0, currMin = 0;
        int maxSoFar = INT_MIN, minSoFar = INT_MAX;
        
        // Pass 1: Build leftMax and leftMin
        for (int i = 0; i < n; i++) {
            currMax = max(arr[i], currMax + arr[i]);
            maxSoFar = max(maxSoFar, currMax);
            leftMax[i] = maxSoFar;
            
            currMin = min(arr[i], currMin + arr[i]);
            minSoFar = min(minSoFar, currMin);
            leftMin[i] = minSoFar;
        }
        
        // Reset variables for right-to-left pass
        currMax = 0, currMin = 0;
        maxSoFar = INT_MIN, minSoFar = INT_MAX;
        
        // Pass 2: Build rightMax and rightMin
        for (int i = n - 1; i >= 0; i--) {
            currMax = max(arr[i], currMax + arr[i]);
            maxSoFar = max(maxSoFar, currMax);
            rightMax[i] = maxSoFar;
            
            currMin = min(arr[i], currMin + arr[i]);
            minSoFar = min(minSoFar, currMin);
            rightMin[i] = minSoFar;
        }
        
        // Pass 3: Evaluate max absolute diff across all valid splits
        int maxDiff = 0;
        for (int i = 0; i < n - 1; i++) {
            int diff1 = abs(leftMax[i] - rightMin[i + 1]);
            int diff2 = abs(leftMin[i] - rightMax[i + 1]);
            maxDiff = max({maxDiff, diff1, diff2});
        }
        
        return maxDiff;
    }
};

/*
* Dry Run
* Input: arr = [2, -1, -2, 1, -4, 2, 8]
* 
* leftMax:  [2, 2, 2, 2, 2, 2, 10]
* leftMin:  [2, -1, -3, -3, -6, -6, -6]
* rightMax: [10, 10, 10, 10, 10, 10, 8]
* rightMin: [-6, -6, -6, -4, -4, 2, 8]
* 
* Iteration i = 4 (value -4):
* diff1 = abs(leftMax[4] - rightMin[5]) = abs(2 - 2) = 0
* diff2 = abs(leftMin[4] - rightMax[5]) = abs(-6 - 10) = 16
* maxDiff updates to 16
* 
* Output: 16
*/

```

---

## 🧠 Key Insights

* **Decoupling the Problem:** Finding the maximum difference between any two sets of numbers essentially requires finding the absolute difference of their extremes. Thus, we want `max_subarray_sum - min_subarray_sum` separated by some index `i`.
* **Prefix and Suffix States:** Precomputing answers for the left and right sides transforms a potential quadratic nested loop into three linear passes.
* **Kadane's Adaptation:** Kadane's algorithm works flawlessly for finding contiguous subarray minimums just as well as it does for maximums; simply swap `max()` operations for `min()`.

---

## 🔍 Further Exploration

* Look into related Google Dynamic Programming interview questions.
* Try extending this approach to circular arrays.
* Relevant GfG Problem: *Maximum Subarray Sum* or *Maximum Sum Circular Subarray*.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Max Absolute Diff of Two Subarrays](https://www.geeksforgeeks.org/problems/max-absolute-difference4114/1)
* **Algorithm Concept:** [Kadane's Algorithm](https://en.wikipedia.org/wiki/Maximum_subarray_problem)

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)