# 🟢 Minimum Moves to Sort Permutation

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/morning-assembly3038/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-52.38%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` containing integers from `1` to `n` exactly once, sort the array in ascending order. 

In one operation, you can pick any element and move it either to the **beginning** or to the **end** of the array. 

Return the **minimum number of operations** required to sort the array.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [2, 1, 3]
Output: 1
Explanation: Move 1 to the beginning. The array becomes [1, 2, 3].

```

### Example 2

```text
Input: arr[] = [4, 3, 1, 2]
Output: 2
Explanation: 
1. Move 3 to the end to get [4, 1, 2, 3]. 
2. Then move 4 to the end to get [1, 2, 3, 4].

```

---

## ⚠️ Constraints

> * `1 ≤ arr.size() ≤ 10^5`
> * `1 ≤ arr[i] ≤ arr.size()`
> * All elements in `arr[]` are distinct.
> 
> 

---

## 🚀 Solution Approaches

### 1️⃣ Optimized Approach (Longest Consecutive Increasing Subsequence)

**Intuition:**
Since we can move elements to either the front or the back, the elements we do *not* need to move are those that already form a consecutive increasing subsequence (e.g., `1, 2, 3...`). The maximum number of elements we can leave untouched is exactly the length of the longest consecutive increasing subsequence. Thus, the minimum moves required will be the total number of elements minus this max length.

```cpp
// Intuition: Elements forming the longest consecutive increasing subsequence don't need to be moved. Minimum moves = total elements - length of this subsequence.
// Approach: Use a frequency/count array to track the length of the consecutive subsequence ending at each element. Then find the maximum length and subtract it from n.
// Time Complexity: O(n) as we iterate through the array to populate the count, and once through the count array to find the maximum.
// Space Complexity: O(n) for the count array of size n + 1.
class Solution {
  public:
    int minMoves(vector<int>& arr) {
        int n = arr.size(); // Total number of elements
        int count[n + 1] = {0}; // Track lengths of consecutive subsequences

        // Compute longest consecutive increasing subsequence.
        for (int x : arr) {
            if (count[x - 1] != 0) {
                count[x] = count[x - 1] + 1; // Extend the existing subsequence
            } else {
                count[x] = 1; // Start a new subsequence of length 1
            }
        }

        int longest = 0; // To store the max length found

        // Find maximum subsequence length.
        for (int i = 0; i <= n; ++i) {
            longest = max(longest, count[i]); // Update longest if count[i] is greater
        }

        return n - longest; // The rest of the elements must be moved
    }
};

/*
*
* Dry Run
* Input: arr[] = [4, 3, 1, 2]
* n = 4, count array initialized to {0, 0, 0, 0, 0}
* 
* Loop over elements:
* x = 4: count[3] is 0 -> count[4] = 1
* x = 3: count[2] is 0 -> count[3] = 1
* x = 1: count[0] is 0 -> count[1] = 1
* x = 2: count[1] is 1 -> count[2] = count[1] + 1 = 2
* 
* Loop to find max:
* Max value in count array is count[2], which is 2. (longest = 2)
* 
* Return n - longest: 4 - 2 = 2.
*
*/

```

---

## 🧠 Key Insights

* **Avoid Sorting:** Although the problem asks us to sort the array, we do not need to perform an actual sorting algorithm. We only need to compute the *minimum operations* mathematically.
* **Subsequence Tracking:** By checking `count[x - 1]`, we efficiently determine in $O(1)$ time if the current element `x` can extend an existing valid chain.

---

## 🔍 Further Exploration

If you enjoyed this problem, you might also like these:

* [Longest Increasing Subsequence](https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/)
* [Minimum Swaps to Sort](https://www.geeksforgeeks.org/minimum-number-swaps-required-sort-array/)

---

## 🔗 References

* **Original Problem:** [GeeksforGeeks: Minimum Moves to Sort Permutation](https://www.geeksforgeeks.org/problems/morning-assembly3038/1)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#Hash` `#Dynamic-Programming` `#Arrays` `#GeeksforGeeks`