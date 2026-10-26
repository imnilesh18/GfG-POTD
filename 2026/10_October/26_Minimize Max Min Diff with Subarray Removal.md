<div align="center">

# 🧮 Minimize Max Min Diff with Subarray Removal

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/minimize-the-difference/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy: 54.13%](https://img.shields.io/badge/Accuracy-54.13%25-brightgreen?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

</div>

---

## 📝 Problem Statement

You are given an array `arr[]` of size `n`. You need to remove a continuous subarray of size `k`, such that the difference between the maximum and minimum values of the remaining array is minimized. Find the minimum value obtained after performing the operation of the removal of the subarray.

## 💡 Examples

### Example 1
```text
Input: arr = [1, 2, 3, 4, 5], k = 3
Output: 1
Explanation: We remove the first subarray of length 3 [1, 2, 3], the remaining array is [4, 5] and the difference of maximum and minimum element is 1 (i.e. 5 - 4 = 1).
```

### Example 2
```text
Input: arr = [2, 3, 1, 4, 6, 7], k = 3
Output: 2
```

<details>
<summary>📖 <b>Example Breakdown (Click to expand)</b></summary>

For `arr = [2, 3, 1, 4, 6, 7]` and `k = 3`:
- If we remove the subarray `[2,3,1]` then remaining array is `[4,6,7]` and the difference = `7 - 4 = 3`
- If we remove the subarray `[3,1,4]` then remaining array is `[2,6,7]` and the difference = `7 - 2 = 5`
- If we remove the subarray `[1,4,6]` then remaining array is `[2,3,7]` and the difference = `7 - 2 = 5`
- If we remove the subarray `[4,6,7]` then remaining array is `[2,3,1]` and the difference = `3 - 1 = 2`

So the answer is `min(3, 5, 5, 2) = 2`.
</details>

---

## 🚧 Constraints

> - `1 ≤ arr.size() ≤ 10^5`
> - `1 ≤ arr[i] ≤ 10^9`
> - `0 ≤ k < arr.size()`

---

## 🚀 Solution Approaches

### 1. Optimized Approach (Prefix & Suffix Precomputation)

```cpp
// Intuition: Removing a subarray of size k splits the remaining array into a prefix and a suffix. We can find the min and max of the remaining elements efficiently in O(1) time if we precompute the suffix minimums/maximums and keep track of prefix minimums/maximums on the fly.
// Approach:
// 1. Handle edge case when k is 0 by simply calculating the max - min of the entire array.
// 2. Precompute `suffMin` and `suffMax` arrays from right to left to store minimum and maximum values for all suffixes.
// 3. Initialize prefix min (`pMin`) and max (`pMax`), and iterate through all valid starting indices `i` of the subarray to remove.
// 4. For each window `[i, i+k-1]`, determine the min and max of the remaining elements by comparing prefix and suffix bounds.
// 5. Update the global minimum difference `ans`. Expand the prefix by including `arr[i]` for the next iteration.
// Time Complexity: O(n) because calculating the suffix arrays and the main traversal each take linear time.
// Space Complexity: O(n) auxiliary space is used by the `suffMin` and `suffMax` arrays.

class Solution {
public:
    int minDiff(int k, vector<int> &arr) {
        int n = arr.size();

        // Handle 0 removals edge case
        if (k == 0) {
            int mx = arr[0], mn = arr[0];
            for (int x : arr) {
                mx = max(mx, x);
                mn = min(mn, x);
            }
            return mx - mn;
        }

        // Precompute suffix minimums and suffix maximums
        vector<int> suffMin(n), suffMax(n);
        suffMin[n - 1] = arr[n - 1];
        suffMax[n - 1] = arr[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            suffMin[i] = min(suffMin[i + 1], arr[i]);
            suffMax[i] = max(suffMax[i + 1], arr[i]);
        }

        int pMin = 2e9; // Tracks prefix minimum
        int pMax = -2e9; // Tracks prefix maximum
        int ans = 2e9;   // Globally tracks the minimum difference

        // Iterate through all valid starting indices of the removed subarray
        for (int i = 0; i <= n - k; i++) {
            int curMin, curMax;

            if (i == 0) {
                // Subarray is at the start; only suffix remains
                curMin = suffMin[k];
                curMax = suffMax[k];
            } else if (i == n - k) {
                // Subarray is at the end; only prefix remains
                curMin = pMin;
                curMax = pMax;
            } else {
                // Subarray is in the middle; combine prefix and suffix bounds
                curMin = min(pMin, suffMin[i + k]);
                curMax = max(pMax, suffMax[i + k]);
            }

            // Update the minimum difference found so far
            ans = min(ans, curMax - curMin);

            // Add current element to the prefix for the next step
            pMin = min(pMin, arr[i]);
            pMax = max(pMax, arr[i]);
        }

        return ans;
    }
};

/*
Dry Run
Input: arr = [1, 2, 3, 4, 5], k = 3
n = 5
1. Precompute suffMin: [1, 2, 3, 4, 5], suffMax: [5, 5, 5, 5, 5]
2. Initial state: pMin = INF, pMax = -INF, ans = INF
3. Loop i = 0 (Remove [1, 2, 3], remaining suffix [4, 5]):
   curMin = suffMin[3] = 4, curMax = suffMax[3] = 5
   ans = min(INF, 5 - 4) = 1
   Update prefix: pMin = min(INF, 1) = 1, pMax = max(-INF, 1) = 1
4. Loop i = 1 (Remove [2, 3, 4], remaining prefix [1], suffix [5]):
   curMin = min(pMin=1, suffMin[4]=5) = 1, curMax = max(pMax=1, suffMax[4]=5) = 5
   ans = min(1, 5 - 1) = 1
   Update prefix: pMin = min(1, 2) = 1, pMax = max(1, 2) = 2
5. Loop i = 2 (Remove [3, 4, 5], remaining prefix [1, 2]):
   curMin = pMin = 1, curMax = pMax = 2
   ans = min(1, 2 - 1) = 1
   Loop ends.
Output: 1
*/
```

---

## 🧠 Key Insights
- **Sliding Subarray Concept**: Rather than physically removing elements and shifting arrays (which takes $O(n^2)$), we logically bypass the window of size `k`.
- **Space-Time Trade-off**: By utilizing $O(n)$ space for the suffix arrays, we drop the lookup time for the remaining boundary values to $O(1)$, lowering the overall time complexity from $O(n^2)$ to $O(n)$.

---

## 🔍 Further Exploration
- GeeksforGeeks: *Sliding Window Maximum*
- GeeksforGeeks: *Prefix Sum Arrays*

---

## 🔗 References
- **Original Problem**: [GeeksforGeeks - Minimize the Difference](https://www.geeksforgeeks.org/problems/minimize-the-difference/1)

---

## 👤 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
- <kbd>array</kbd>
- <kbd>prefix-sum</kbd>
- <kbd>sliding-window</kbd>
- <kbd>geeksforgeeks</kbd>