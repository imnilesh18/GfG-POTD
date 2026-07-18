# ⛰️ Mountain Subarray Queries

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-46.22%25-green?style=for-the-badge" alt="Accuracy: 46.22%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` and a list of `queries`. For each query `[l, r]`, find whether the subarray `arr[l...r]` is a mountain array. 

A subarray is called a **mountain array** if there exists an index `k` ($l \le k \le r$) such that: 
`arr[l] <= arr[l + 1] <= ... <= arr[k] >= arr[k + 1] >= ... >= arr[r]`

*   Elements of a Mountain subarray are first **non-decreasing** and then **non-increasing**.
*   A subarray that is entirely non-decreasing or entirely non-increasing is also considered a mountain.

---

## 💡 Examples

**Example 1:**
```text
Input: arr[] = [2, 3, 2, 4, 4, 6, 3, 2], queries[][] = [[0, 2], [1, 3]]
Output: [true, false]
Explanation: 
For query [0, 2], the subarray is [2, 3, 2]. The elements first increase and then decrease, so it forms a mountain.
For query [1, 3], the subarray is [3, 2, 4]. The elements decrease and then increase, so it does not form a mountain.

```

**Example 2:**

```text
Input: arr[] = [2, 2, 2, 2], queries[][] = [[0, 2], [1, 3]]
Output: [true, true]
Explanation: All subarrays of the given array are mountain.

```

1. **Array Slice:** The subarray from index 0 to 2 is `[2, 3, 2]`.
2. **Left slope:** From index 0 to 1, values go from `2` to `3` (Non-decreasing: Valid).
3. **Right slope:** From index 1 to 2, values go from `3` to `2` (Non-increasing: Valid).
4. **Peak:** The peak `k` is at index 1 (value `3`). Since it strictly follows the pattern, the result for this query is `true`.

---

## ⚙️ Constraints

> * $1 \le arr.size(), queries.size() \le 10^5$
> * $1 \le arr[i] \le 10^6$
> * $0 \le l \le r < arr.size()$
> 
> 

---

## 🚀 Solution Approaches

### Optimized Approach (Prefix & Suffix Arrays)

**Intuition:**
A subarray forms a mountain if there is an intersection between its non-decreasing left slope and its non-increasing right slope. By precomputing the maximum reach of the "uphill" slope starting from the left and the "uphill" slope starting from the right (going backward), we can answer each query in constant time.

```cpp
// Intuition: A subarray is a mountain if there's a peak. We can reach the peak by moving right 
// while elements are non-decreasing, and from the end, moving left while elements are non-increasing.
// Approach: 
// 1. Precompute `right_up[i]`: the furthest index to the right we can go in a non-decreasing manner.
// 2. Precompute `left_up[i]`: the furthest index to the left we can go in a non-increasing manner.
// 3. For any query [l, r], if right_up[l] >= left_up[r], they share a valid peak, so it's a mountain.
// Time Complexity: O(n + q) where n is array size and q is query size.
// Space Complexity: O(n) for the two prefix/suffix arrays used for preprocessing.
class Solution {
  public:
    vector<bool> processQueries(vector<int> &arr, vector<vector<int>> &queries) {
        int n = arr.size();
        vector<int> right_up(n);
        vector<int> left_up(n);
        
        // Base cases for edges
        right_up[n - 1] = n - 1;
        left_up[0] = 0;
        
        // Precompute left_up: furthest left index we can reach while values are non-increasing
        for (int i = 1; i < n; i++) {
            if (arr[i] <= arr[i - 1]) {
                left_up[i] = left_up[i - 1];
            } else {
                left_up[i] = i;
            }
        }
        
        // Precompute right_up: furthest right index we can reach while values are non-decreasing
        for (int i = n - 2; i >= 0; i--) {
            if (arr[i] <= arr[i + 1]) {
                right_up[i] = right_up[i + 1];
            } else {
                right_up[i] = i;
            }
        }
        
        vector<bool> res;
        // Process each query in O(1) time
        for (auto& q : queries) {
            int l = q[0];
            int r = q[1];
            
            // If the non-decreasing slope from 'l' meets or exceeds the non-increasing slope from 'r'
            if (right_up[l] >= left_up[r]) {
                res.push_back(true);
            } else {
                res.push_back(false);
            }
        }
        
        return res;
    }
};

/*
 * Dry Run
 * arr = [2, 3, 2], queries = [[0, 2]]
 * n = 3
 * left_up calculation:
 * left_up[0] = 0
 * i=1: arr[1]=3, arr[0]=2 (3 > 2) -> left_up[1] = 1
 * i=2: arr[2]=2, arr[1]=3 (2 <= 3) -> left_up[2] = left_up[1] = 1
 * right_up calculation:
 * right_up[2] = 2
 * i=1: arr[1]=3, arr[2]=2 (3 > 2) -> right_up[1] = 1
 * i=0: arr[0]=2, arr[1]=3 (2 <= 3) -> right_up[0] = right_up[1] = 1
 * Query processing:
 * [0, 2] -> right_up[0] (1) >= left_up[2] (1). Condition true!
 * Output: [true]
 */

```

---

## 🔑 Key Insights

* **Precomputation is King:** When dealing with multiple range queries (especially up to $10^5$), repeatedly scanning the array yields an $O(n \times q)$ Time Limit Exceeded (TLE) error. Precomputing boundaries allows $O(1)$ query resolution.
* **Intersection Logic:** If the rightmost bound of the rising slope starting at `l` overlaps or touches the leftmost bound of the falling slope ending at `r`, a continuous mountain structure is guaranteed.

---

## 🔭 Further Exploration

* **Longest Mountain in Array:** A similar problem where you have to find the length of the longest subarray that is a mountain.
* **Find Peak Element:** Given an array, find a peak element using Binary Search in $O(\log n)$ time.

---

## 🔗 References

* **GFG Problem Link:** [Mountain Subarray Queries](https://www.geeksforgeeks.org/problems/mountain-subarray-problem/1)

---

## ✍️ Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Arrays` `Preprocessing` `Prefix-Suffix` `GeeksforGeeks` `Amazon`