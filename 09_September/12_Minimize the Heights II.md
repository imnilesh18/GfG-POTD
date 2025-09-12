# 🗼 Minimize the Heights II

<div align="center">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GFG Badge"/>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge" alt="Difficulty Badge"/>
    <img src="https://img.shields.io/badge/Accuracy-15.06%25-red.svg?style=for-the-badge" alt="Accuracy Badge"/>
    <img src="https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge" alt="Points Badge"/>
    <img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License Badge"/>
</div>

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/minimize-the-heights3351/1).

---

## 📝 Problem Statement

Given an array `arr[]` denoting heights of `n` towers and a positive integer `k`.

For **each** tower, you must perform **exactly one** of the following operations **exactly once**.

1.  **Increase** the height of the tower by `k`.
2.  **Decrease** the height of the tower by `k`.

Find out the **minimum** possible difference between the height of the **shortest** and **tallest** towers after you have modified each tower.

**Note**: It is **compulsory** to increase or decrease the height by `k` for each tower. After the operation, the resultant array should **not** contain any **negative** integers.

---

## 🧪 Examples

### Example 1

```
Input:
k = 2, arr[] = [1, 5, 8, 10]
Output:
5
Explanation:
The array can be modified as [1+k, 5-k, 8-k, 10-k] = [3, 3, 6, 8]. The difference between the largest and the smallest is 8 - 3 = 5.
```

<details>
<summary>📖 Example Breakdown</summary>

Let's walk through the logic with `arr[] = [1, 5, 8, 10]` and `k = 2`.

1.  **Sort the Array**: First, we sort the array to handle the towers in a structured order of height.

    - `arr` becomes `[1, 5, 8, 10]`.

2.  **Initial Difference**: The initial maximum difference without any operations is `10 - 1 = 9`. This is our baseline answer to beat.

3.  **Core Idea**: To minimize the difference `(max_height - min_height)`, we should try to _increase_ the height of short towers and _decrease_ the height of tall towers.

4.  **Systematic Approach**:

    - Let's consider a "split point" in the sorted array. All towers to the left of the split point will have their height increased by `k`, and all towers to the right will have their height decreased by `k`.
    - The smallest tower's original height is `arr[0]`, and the tallest is `arr[n-1]`. No matter what, `arr[0]` must be increased (`arr[0] + k`), and `arr[n-1]` must be decreased (`arr[n-1] - k`) to minimize the range.
    - Let's iterate through the array and consider each tower `arr[i]` as the potential new tallest tower (after decreasing its height).

5.  **Iteration Walkthrough**:

    - **Initial State**: `res = arr[3] - arr[0] = 10 - 1 = 9`.
    - **Loop `i = 1`**:
      - The split is between `arr[0]` and `arr[1]`. We increase heights for indices `< 1` and decrease for indices `>= 1`.
      - Potential new minimum height: `min(arr[0] + k, arr[1] - k)` = `min(1 + 2, 5 - 2)` = `min(3, 3)` = `3`.
      - Potential new maximum height: `max(arr[0] + k, arr[3] - k)` = `max(1 + 2, 10 - 2)` = `max(3, 8)` = `8`.
      - New difference: `8 - 3 = 5`. Update `res = min(9, 5) = 5`.
    - **Loop `i = 2`**:
      - The split is between `arr[1]` and `arr[2]`. Increase for `< 2`, decrease for `>= 2`.
      - Potential new minimum: `min(arr[0] + k, arr[2] - k)` = `min(1 + 2, 8 - 2)` = `min(3, 6)` = `3`.
      - Potential new maximum: `max(arr[1] + k, arr[3] - k)` = `max(5 + 2, 10 - 2)` = `max(7, 8)` = `8`.
      - New difference: `8 - 3 = 5`. `res` remains `5`.
    - **Loop `i = 3`**:
      - The split is between `arr[2]` and `arr[3]`.
      - Potential new minimum: `min(arr[0] + k, arr[3] - k)` = `min(1 + 2, 10 - 2)` = `min(3, 8)` = `3`.
      - Potential new maximum: `max(arr[2] + k, arr[3] - k)` = `max(8 + 2, 10 - 2)` = `max(10, 8)` = `10`.
      - New difference: `10 - 3 = 7`. `res` remains `5`.

6.  **Final Result**: The minimum difference found is `5`.

</details>

### Example 2

```
Input:
k = 3, arr[] = [3, 9, 12, 16, 20]
Output:
11
Explanation:
The array can be modified as [3+k, 9+k, 12-k, 16-k, 20-k] = [6, 12, 9, 13, 17]. The difference between the largest and the smallest is 17 - 6 = 11.
```

---

## ⛓️ Constraints

- `1 ≤ k ≤ 10^7`
- `1 ≤ n ≤ 10^5`
- `1 ≤ arr[i] ≤ 10^7`

---

## 💡 Solution Approaches

### Optimized Approach

The core idea is to sort the array first. This allows us to systematically find the minimum possible difference. After sorting, for any tower, we either add `k` or subtract `k`. To minimize the range `(max - min)`, we should aim to increase smaller elements and decrease larger elements.

By iterating through the sorted array, we can find a "partition point". We assume all elements before this point are increased by `k` and all elements after are decreased by `k`. At each point, we calculate the potential new minimum and maximum heights and update our overall minimum difference.

#### C++ Solution

```cpp
// Intuition: The goal is to minimize the difference between the maximum and minimum tower heights.
// By sorting the array, we can make a greedy choice. To minimize the range, it's always
// optimal to increase the heights of smaller towers and decrease the heights of taller towers.
// The new minimum element must be either arr[0] + k or arr[i] - k for some i.
// The new maximum element must be either arr[n-1] - k or arr[i-1] + k for some i.

// Approach:
// 1. Sort the array `arr` in non-decreasing order.
// 2. Initialize the result `res` with the initial difference: `arr[n-1] - arr[0]`.
// 3. Iterate from the second element `i = 1` to the end of the array.
// 4. In each iteration, check if `arr[i] - k` is negative. If it is, we cannot decrease this tower's height, so we skip it.
// 5. Calculate the potential new minimum height (`minH`) as `min(arr[0] + k, arr[i] - k)`.
//    This considers the smallest tower increased vs. the current tower `i` decreased.
// 6. Calculate the potential new maximum height (`maxH`) as `max(arr[i-1] + k, arr[n-1] - k)`.
//    This considers the tower just before `i` increased vs. the largest tower decreased.
// 7. Update `res` with the minimum of its current value and `maxH - minH`.
// 8. After the loop, `res` will hold the minimum possible difference.

// Time Complexity: O(N log N), dominated by the sorting step.
// Space Complexity: O(1), as we modify the array in-place (or O(log N) depending on sort implementation).

class Solution {
 public:
  int getMinDiff(vector<int> &arr, int k) {
    int n = arr.size();  // Get the size of the array
    sort(arr.begin(), arr.end());  // Sort the array to handle elements in order

    // Initialize the result with the difference of the original max and min
    int res = arr[n - 1] - arr[0];

    // Iterate through the array to find the optimal partition point
    for (int i = 1; i < n; i++) {
      // We can't have negative heights, so if arr[i]-k is negative, this partition is invalid
      if (arr[i] - k < 0) {
        continue;
      }

      // Potential minimum height after modification
      // It's either the first element increased or the current element decreased
      int minH = min(arr[0] + k, arr[i] - k);

      // Potential maximum height after modification
      // It's either the last element decreased or the previous element increased
      int maxH = max(arr[i - 1] + k, arr[n - 1] - k);

      // Update the result with the minimum difference found so far
      res = min(res, maxH - minH);
    }

    return res;  // Return the final minimum difference
  }
};

/*
*
* Dry Run
*
* Input: k = 2, arr[] = [1, 5, 8, 10]
*
* 1. n = 4
* 2. sort(arr): arr remains [1, 5, 8, 10]
* 3. res = arr[3] - arr[0] = 10 - 1 = 9
*
* 4. Loop for i = 1 to 3:
* - i = 1:
* - arr[1] - k = 5 - 2 = 3 (>= 0, so continue)
* - minH = min(arr[0]+k, arr[1]-k) = min(1+2, 5-2) = min(3, 3) = 3
* - maxH = max(arr[0]+k, arr[3]-k) = max(1+2, 10-2) = max(3, 8) = 8
* - res = min(res, maxH - minH) = min(9, 8 - 3) = 5
*
* - i = 2:
* - arr[2] - k = 8 - 2 = 6 (>= 0, so continue)
* - minH = min(arr[0]+k, arr[2]-k) = min(1+2, 8-2) = min(3, 6) = 3
* - maxH = max(arr[1]+k, arr[3]-k) = max(5+2, 10-2) = max(7, 8) = 8
* - res = min(res, maxH - minH) = min(5, 8 - 3) = 5
*
* - i = 3:
* - arr[3] - k = 10 - 2 = 8 (>= 0, so continue)
* - minH = min(arr[0]+k, arr[3]-k) = min(1+2, 10-2) = min(3, 8) = 3
* - maxH = max(arr[2]+k, arr[3]-k) = max(8+2, 10-2) = max(10, 8) = 10
* - res = min(res, maxH - minH) = min(5, 10 - 3) = 5
*
* 5. End of loop. Return res = 5.
*/
```

---

## 🎯 Key Insights

- **Sorting is Key**: The problem becomes much simpler once the array is sorted. It allows us to reason that the smallest elements should be increased and the largest ones decreased to minimize the overall range.
- **Identifying Potential Boundaries**: After sorting, the potential minimum element in any valid modified array will always be either `arr[0] + k` or `arr[i] - k` for some `i`. Similarly, the potential maximum will be `arr[n-1] - k` or `arr[i-1] + k`. By iterating through all possible split points `i`, we can check all relevant boundary combinations and find the global minimum difference.

---

## 🚀 Further Exploration

- [Minimize the Heights I](https://www.geeksforgeeks.org/problems/minimize-the-heights-i/1)
- [Chocolate Distribution Problem](https://www.geeksforgeeks.org/problems/chocolate-distribution-problem/0)
- [Maximize sum after K negations](https://www.geeksforgeeks.org/problems/maximize-sum-after-k-negations/1)

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/minimize-the-heights3351/1)

---

## 🧑‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## #️⃣ Tags

<div>
    <img src="https://img.shields.io/badge/-Array-blue?style=for-the-badge" alt="Array Tag"/>
    <img src="https://img.shields.io/badge/-Greedy-green?style=for-the-badge" alt="Greedy Tag"/>
    <img src="https://img.shields.io/badge/-Sorting-orange?style=for-the-badge" alt="Sorting Tag"/>
    <img src="https://img.shields.io/badge/-GeeksforGeeks-298D46?style=for-the-badge" alt="GeeksforGeeks Tag"/>
</div>

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder**: This content is for educational purposes. It's recommended to attempt the problem first and use this as a reference for learning and improvement.
