# 🟧 Equalize All Prefix Sums

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-69.73%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.

---

## 📝 Problem Statement

Given a sorted array `arr[]`. For each `i` (0 ≤ i ≤ n-1), make all the elements of the array from index `0` to `i` equal, using the minimum number of operations. 

In one operation you can either increase or decrease the array element by 1. Return an array that contains the minimum number of operations for each `i`, to accomplish the above task.

**Note:**
- For each index `i`, consider the original array without applying modifications made for previous indices.
- Try to solve the problem using **O(1)** extra space (excluding the resultant array).

---

## 🚫 Constraints

- `1 ≤ arr.size() ≤ 10^5`
- `-10^4 ≤ arr[i] ≤ 10^4`
- Sum of `n` over all test cases does not exceed `10^6`.

---

## 💡 Examples

**Example 1:**
```text
Input: arr[] = [1, 6, 9, 12]
Output: [0, 5, 8, 14]
Explanation: 
For i = 0, prefix [1] already has all equal elements, so operations = 0.
For i = 1, make [1, 6] equal to 4, operations = |1 - 4| + |6 - 4| = 5.
For i = 2, make [1, 6, 9] equal to 6, operations = |1 - 6| + |6 - 6| + |9 - 6| = 8.
For i = 3, make [1, 6, 9, 12] equal to 8, operations = 7 + 2 + 1 + 4 = 14
```

**Example 2:**
```text
Input: arr[] = [1, 1, 1, 7, 7, 10, 19]
Output: [0, 0, 0, 6, 12, 21, 33]
Explanation:
For i = 0 to 2, prefixes already have equal elements (all 1s), so operations = 0.
For i = 3, make [1, 1, 1, 7] equal to 1, operations = 6.
For i = 4, make [1, 1, 1, 7, 7] equal to 1, operations = 12.
For i = 5, make [1, 1, 1, 7, 7, 10] equal to 5, operations = 21.
For i = 6, make [1, 1, 1, 7, 7, 10, 19] equal to 7, operations = 33.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>

Let's dry run the logic with `arr[] = [1, 6, 9, 12]`:
To minimize absolute differences, we must equalize all elements to the **median** of the subarray.

- **i = 0**, `subarray = [1]`, `median = 1`. 
  - Ops: `|1-1| = 0`. Total = `0`.
- **i = 1**, `subarray = [1, 6]`, `median = 1` (or 6, choosing the left middle index).
  - Ops: `|1-1| + |6-1| = 0 + 5 = 5`. Total = `5`.
- **i = 2**, `subarray = [1, 6, 9]`, `median = 6`.
  - Ops: `|1-6| + |6-6| + |9-6| = 5 + 0 + 3 = 8`. Total = `8`.
- **i = 3**, `subarray = [1, 6, 9, 12]`, `median = 6` (left middle index).
  - Ops: `|1-6| + |6-6| + |9-6| + |12-6| = 5 + 0 + 3 + 6 = 14`. Total = `14`.

**Result:** `[0, 5, 8, 14]`
</details>

---

## 🛠️ Solution Approaches

### Optimized Approach (Mathematical & Median-based)

To minimize operations, the optimal target value for a subarray is always its **median**. Since the array is already sorted, the median of subarray `arr[0...i]` is safely at index `m = i / 2`. 
By maintaining a running prefix sum and dynamically updating the sum of the elements lying to the left of the median, we can compute the cost in exactly **O(1)** extra space and **O(N)** time without utilizing a whole extra prefix sum array.

```cpp
// Intuition: The minimum absolute difference sum is obtained by making all elements equal to the median. Since the array is sorted, the median of subarray `[0..i]` is always at index `i/2`.
// Approach: Iterate through the array maintaining a running total sum (`current_sum`) and the sum of elements left of the median (`sum_left`). Use these to algebraically calculate the cost to make elements equal to the median in O(1) space.
// Time Complexity: O(N) because we are processing each element of the array exactly once in a single pass.
// Space Complexity: O(1) auxiliary space, as we only use a few variables for counting sums instead of full prefix arrays.

class Solution {
public:
    vector<int> optimalArray(vector<int> &arr) {
        int n = arr.size();
        vector<int> ans;
        
        long long current_sum = 0; // Tracks sum of all elements up to i
        long long sum_left = 0;    // Tracks sum of elements strictly to the left of the median
        
        for (int i = 0; i < n; i++) {
            current_sum += arr[i]; // Include current element in overall sum
            int m = i / 2;         // Median index
            
            // If i becomes even (and > 0), the median shifts, so we must add the newly skipped left element to sum_left
            if (i > 0 && i % 2 == 0) {
                sum_left += arr[m - 1]; 
            }
            
            // Cost for elements strictly less than the median
            long long left_cost = (long long)m * arr[m] - sum_left;
            
            // Sum of elements strictly right of the median
            long long sum_right = current_sum - sum_left - arr[m];
            
            // Cost for elements strictly greater than the median
            long long right_cost = sum_right - (long long)(i - m) * arr[m];
            
            // Total operations needed is the sum of both costs
            ans.push_back(left_cost + right_cost);
        }
        
        return ans;
    }
};

/*
*
* Dry Run
*
* Input: arr = [1, 6, 9]
* * Initial: current_sum = 0, sum_left = 0, ans = []
*
* i = 0: current_sum = 1, m = 0.
* sum_left = 0. 
* left_cost = 0 * 1 - 0 = 0.
* sum_right = 1 - 0 - 1 = 0. 
* right_cost = 0 - 0 * 1 = 0.
* ans -> [0]
*
* i = 1: current_sum = 7, m = 0.
* sum_left = 0. 
* left_cost = 0 * 1 - 0 = 0.
* sum_right = 7 - 0 - 1 = 6.
* right_cost = 6 - (1 - 0) * 1 = 5.
* ans -> [0, 5]
*
* i = 2: current_sum = 16, m = 1.
* i is even -> sum_left += arr[0] -> sum_left = 1.
* left_cost = 1 * 6 - 1 = 5.
* sum_right = 16 - 1 - 6 = 9.
* right_cost = 9 - (2 - 1) * 6 = 3.
* Total cost = 5 + 3 = 8.
* ans -> [0, 5, 8]
*
*/
```

---

## 🧠 Key Insights

1. **Optimal Point is the Median:** In any absolute difference minimization problem, the target scalar is the median of the distribution.
2. **Space Optimization trick:** Instead of using an extra `O(N)` prefix sums array, keeping track of a running sum (`current_sum`) and shifting the left window sum (`sum_left`) seamlessly avoids redundant space usage.
3. **Pointers Strategy:** The condition `if (i > 0 && i % 2 == 0)` ensures that `sum_left` seamlessly includes the exact numbers left behind whenever the median shifts right.

---

## 🔍 Further Exploration

- [Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/)
- [Minimum Operations to Make Array Equal](https://leetcode.com/problems/minimum-operations-to-make-array-equal/)
- Find optimal meeting point (Median properties in Grids/1D lines).

---

## 🔗 References

- **GeeksforGeeks Problem:** [Equalize All Prefix Sums](https://www.geeksforgeeks.org/problems/optimal-array--170647/1)

---

## 👤 Author

**Nilesh**
- GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Arrays` `Sorting` `Data Structures` `Algorithms` `Mathematics` `Prefix Sum` `GeeksforGeeks`