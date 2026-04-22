# 📊 Mean of range in array

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/mean-of-range-in-array2123/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-50.54%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an integer array `arr[]` and a 2D array `queries[][]`. Each query `queries[i] = [l, r]` represents a subarray ranging from index `l` to `r` (inclusive). For every query, compute the **mean (average)** of the elements in the specified range, and return the **floor value** of that mean.

Return an array where each element corresponds to the result of a query.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [1, 2, 3, 4, 5], queries[][] = [[0, 2], [1, 3], [0, 4]]
Output: [2, 3, 3]
Explanation: The array is [1, 2, 3, 4, 5].
Query 1: l = 0, r = 2 → subarray [1, 2, 3] → sum = 6 → mean = 6/3 = 2
Query 2: l = 1, r = 3 → subarray [2, 3, 4] → sum = 9 → mean = 9/3 = 3
Query 3: l = 0, r = 4 → subarray [1, 2, 3, 4, 5] → sum = 15 → mean = 15/5 = 3
Hence the answer is [2, 3, 3]
```

### Example 2
```text
Input: arr[] = [6, 7, 8, 10], queries[][] = [[0, 3], [1, 2]]
Output: [7, 7]
Explanation: The array is [6, 7, 8, 10].
Query 1: l = 0, r = 3 → subarray [6, 7, 8, 10] → sum = 31 → mean = 31/4 = 7 (floor value)
Query 2: l = 1, r = 2 → subarray [7, 8] → sum = 15 → mean = 15/2 = 7 (floor value)
Hence the answer is [7, 7]
```

<details>
<summary><b>📖 Example Breakdown (Example 1)</b></summary>
<br>

1. We have an array `arr = [1, 2, 3, 4, 5]`.
2. To avoid calculating the sum for each query iteratively, we build a **prefix sum** array:
   - `prefixSum` array tracks the cumulative sum up to index `i`.
   - `prefixSum` = `[0, 1, 3, 6, 10, 15]` (size `n + 1`)
3. For query `[1, 3]`:
   - Subarray is from index 1 to 3 (elements `2, 3, 4`).
   - Using prefix sum: `sum = prefixSum[3+1] - prefixSum[1] = 10 - 1 = 9`.
   - Number of elements = `3 - 1 + 1 = 3`.
   - Mean = `9 / 3 = 3`.
   
</details>

---

## 🔒 Constraints

> * `1 ≤ arr.size() ≤ 10^5`
> * `1 ≤ arr[i] ≤ 10^3`
> * `1 ≤ queries.size() ≤ 10^5`
> * `1 ≤ queries[i][0] ≤ queries[i][1] < arr.size()`

**Expected Complexities:**
* **Time Complexity:** $O(N + Q)$
* **Auxiliary Space:** $O(N)$

---

## ⚙️ Solution Approaches

### Optimized Approach (Prefix Sum)
Since the number of queries and array size can be up to $10^5$, calculating the sum iteratively for each query would lead to an $O(N \times Q)$ time limit exceeded (TLE) error. Instead, we precompute a **Prefix Sum** array. This allows us to fetch the sum of any subarray `[l, r]` in $O(1)$ constant time as `prefixSum[r + 1] - prefixSum[l]`.

```cpp
// Intuition: We need to repeatedly find the sum of elements within specific ranges (subarrays). Finding the sum for each query using a loop would be too slow. Using a Prefix Sum array allows us to answer range sum queries in O(1) time.
// Approach: Build a prefix sum array of size n+1 where prefixSum[i] stores the sum of elements up to index i-1. For each query [l, r], compute the subarray sum as prefixSum[r+1] - prefixSum[l], and calculate the floor mean by dividing this sum by the number of elements (r - l + 1).
// Time Complexity: O(n + q), where n is the size of the array (for building prefix sum) and q is the number of queries (each takes O(1) time).
// Space Complexity: O(n) to store the prefix sum array.

class Solution {
  public:
    vector<int> findMean(vector<int> &arr, vector<vector<int>> &queries) {
        int n = arr.size();
        int q = queries.size();
        vector<int> result;
        
        // Create a prefix sum array of size n + 1 initialized to 0
        vector<int> prefixSum(n + 1, 0);
    
        // Compute prefix sum where prefixSum[i] has sum of arr[0...i-1]
        for (int i = 1; i <= n; i++) {
            prefixSum[i] = prefixSum[i - 1] + arr[i - 1];
        }
    
        // Process each query
        for (int i = 0; i < q; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
    
            // Calculate the sum from l to r using prefix sum in O(1)
            int sum = prefixSum[r + 1] - prefixSum[l];
            int count = (r - l + 1); // Total elements in the range
    
            // Store the floor of the mean
            result.push_back(sum / count);
        }
    
        return result;
    }
};

/*
* Dry Run
* Input: arr = [1, 2, 3, 4, 5], queries = [[0, 2], [1, 3], [0, 4]]
* prefixSum array initialization: size 6, all 0s -> [0, 0, 0, 0, 0, 0]
* prefixSum computation:
* i=1: prefix[1] = 0 + 1 = 1
* i=2: prefix[2] = 1 + 2 = 3
* i=3: prefix[3] = 3 + 3 = 6
* i=4: prefix[4] = 6 + 4 = 10
* i=5: prefix[5] = 10 + 5 = 15
* prefixSum = [0, 1, 3, 6, 10, 15]
* Query 1: l=0, r=2
* sum = prefixSum[3] - prefixSum[0] = 6 - 0 = 6
* count = 2 - 0 + 1 = 3
* result = 6 / 3 = 2 -> result array: [2]
* Query 2: l=1, r=3
* sum = prefixSum[4] - prefixSum[1] = 10 - 1 = 9
* count = 3 - 1 + 1 = 3
* result = 9 / 3 = 3 -> result array: [2, 3]
* Query 3: l=0, r=4
* sum = prefixSum[5] - prefixSum[0] = 15 - 0 = 15
* count = 4 - 0 + 1 = 5
* result = 15 / 5 = 3 -> result array: [2, 3, 3]
* Return [2, 3, 3]
*/
```

---

## 🧠 Key Insights
1. **Range Sums to the Rescue:** Prefix sum arrays convert repetitive linear-time range addition queries into instant constant-time lookups. 
2. **Using 1-based Indexing:** By defining `prefixSum` with size `n + 1`, we bypass the need for an edge-case check when `l == 0`. It simplifies the lookup formula to universally be `prefixSum[r+1] - prefixSum[l]`.

---

## 🔎 Further Exploration
* **Subarray Sum Equals K** - Extend your knowledge of prefix sums to find specific targets in an array.
* **Range Sum Query (Immutable)** - Similar problem utilizing prefix sums for ranges.
* Try updating the array dynamically and fetching ranges using **Segment Trees** or **Fenwick Trees (BIT)**!

---

## 🔗 References
* [GeeksforGeeks Problem: Mean of range in array](https://www.geeksforgeeks.org/problems/mean-of-range-in-array2123/1)

---

## 👨‍💻 Author
Built and maintained by **[imnilesh18](https://github.com/imnilesh18)**.  
Feedback and contributions are always welcome!

**Tags:**
`#prefix-sum` `#Arrays` `#Data-Structures` `#Algorithms` `#GeeksforGeeks`
