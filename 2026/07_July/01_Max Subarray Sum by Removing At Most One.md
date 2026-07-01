# 🧮 Max Subarray Sum by Removing At Most One

![GeeksForGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-32.53%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-brightgreen?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

<div align="center">
  
⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. 
Solutions are provided for learning, practice, and reference only. 
Problem statement and test cases are based on the GeeksforGeeks problem.
  
</div>

---

## 📝 Problem Statement

Given an array `arr[]`, find the maximum sum of a non-empty subarray. You are allowed to skip **at most one** element in the subarray.

> **Note:** After skipping the element, the subarray must still be non-empty.

---

## 💡 Examples

### Example 1

```text
Input: arr[] = [1, 2, 3, -4, 5]
Output: 11
Explanation: We can get the maximum sum subarray by skipping -4 (1 + 2 + 3 + 5 = 11).
```

### Example 2

```text
Input: arr[] = [-2, -3, 4, -1, -2, 1, 5, -3]
Output: 9
Explanation: We can get maximum sum subarray by skipping -2. The sequence [4, -1, 1, 5] sums to 9, which is the maximum achievable sum.
```

<details>
<summary><b>📖 Example Breakdown (Walkthrough)</b></summary>
<br>

Let's trace **Example 1**: `arr[] = [1, 2, 3, -4, 5]`

*   If we take the entire array: `1 + 2 + 3 + (-4) + 5 = 7`
*   If we drop `-4`: `1 + 2 + 3 + 5 = 11`
*   Since `11 > 7`, removing the negative value `-4` maximizes our subarray sum, satisfying the condition of skipping *at most* one element.

</details>

---

## ⚠️ Constraints

> * `1 ≤ arr.size() ≤ 10^6`
> * `-10^3 ≤ arr[i] ≤ 10^3`
> * **Expected Time Complexity:** `O(n)`
> * **Expected Auxiliary Space:** `O(1)`

---

## 🛠️ Solution Approaches

### Optimized Approach (Modified Kadane's Algorithm)

**Brief Intuition:**
This problem is a natural extension of Kadane’s algorithm. To decide whether to skip an element, we can maintain two concurrent states at any index `i`: 
1. The maximum subarray sum ending at `i` with **zero** skips.
2. The maximum subarray sum ending at `i` with **exactly one** skip (or carrying over a past skip).

```cpp
// Intuition: 
// To find the maximum subarray sum with at most one deletion, we can modify Kadane's Algorithm. 
// At any element, we have two states to track: the max sum without skipping any elements, 
// and the max sum having skipped exactly one element (or zero, which is covered).
//
// Approach: 
// 1. Initialize two variables: `no_skip` (max sum ending here with 0 deletions) 
//    and `skip` (max sum ending here with at most 1 deletion), both starting as arr[0].
// 2. Iterate through the array starting from index 1.
// 3. For the current element, update `skip` to be the maximum of (skip + arr[i]) 
//    which means we don't delete arr[i], or (previous no_skip) which means we delete arr[i].
// 4. Update `no_skip` using standard Kadane's (no_skip + arr[i] or just arr[i]).
// 5. Keep track of the overall maximum achievable sum.
// 
// Time Complexity: O(n) - We traverse the array exactly once, making it a linear time solution.
// Space Complexity: O(1) - We only use a few integer variables, so the auxiliary space is constant.

class Solution {
  public:
    int maxSumSubarray(vector<int>& arr) {
        // Base case: if the array is empty
        if (arr.empty()) return 0;

        // Initialize variables with the first element
        int no_skip = arr[0];
        int skip = arr[0];
        int max_sum = arr[0];

        // Traverse the array from the second element
        for (int i = 1; i < arr.size(); i++) {
            // Update skip: either keep a previously skipped subarray or skip the current element
            skip = max(skip + arr[i], no_skip);
            
            // Update no_skip: standard Kadane's algorithm step
            no_skip = max(no_skip + arr[i], arr[i]);
            
            // Update the overall maximum sum
            max_sum = max({max_sum, no_skip, skip});
        }

        return max_sum;
    }
};

/*
 *
 * Dry Run
 * 
 * Input: arr = [1, 2, 3, -4, 5]
 * 
 * Initial State:
 * no_skip = 1, skip = 1, max_sum = 1
 * 
 * i = 1 (arr[1] = 2)
 * - skip = max(1 + 2, 1) = 3
 * - no_skip = max(1 + 2, 2) = 3
 * - max_sum = max(1, 3, 3) = 3
 * 
 * i = 2 (arr[2] = 3)
 * - skip = max(3 + 3, 3) = 6
 * - no_skip = max(3 + 3, 3) = 6
 * - max_sum = max(3, 6, 6) = 6
 * 
 * i = 3 (arr[3] = -4)
 * - skip = max(6 + (-4), 6) = max(2, 6) = 6
 * - no_skip = max(6 + (-4), -4) = max(2, -4) = 2
 * - max_sum = max(6, 2, 6) = 6
 * 
 * i = 4 (arr[4] = 5)
 * - skip = max(6 + 5, 2) = max(11, 2) = 11
 * - no_skip = max(2 + 5, 5) = max(7, 5) = 7
 * - max_sum = max(6, 7, 11) = 11
 * 
 * Output: 11
 *
 */
```

---

## 🧠 Key Insights
* **State Transition:** The "magic" happens in `skip = max(skip + arr[i], no_skip)`. It elegantly handles both cases: inheriting a skipped element from the past (`skip + arr[i]`) versus choosing to skip the *current* element right now (`no_skip` from the previous step without adding `arr[i]`).
* **Space Optimization:** Instead of creating auxiliary arrays to store prefix and suffix subarray sums (`O(n)` space), computing states iteratively on-the-fly reduces the space complexity to strictly `O(1)`.

---

## 🔍 Further Exploration
If you enjoyed this problem, you might also want to practice:
* **Kadane's Algorithm** (Standard Maximum Subarray)
* **Maximum Product Subarray**
* **Maximum Subarray Sum with One Deletion (LeetCode equivalent)**

---

## 🔗 References
* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/max-sum-subarray-by-removing-at-most-one-element/1)

---

## ✍️ Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
* `Arrays`
* `Dynamic Programming`
* `Data Structures`
* `Algorithms`
* `GeeksForGeeks`