# 🟧 Longest Subarray with Majority Greater than K

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/longest-subarray-with-majority-greater-than-k/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge)](https://www.geeksforgeeks.org/problems/longest-subarray-with-majority-greater-than-k/1)
[![Accuracy: 52.63%](https://img.shields.io/badge/Accuracy-52.63%25-28A745?style=for-the-badge)](https://www.geeksforgeeks.org/problems/longest-subarray-with-majority-greater-than-k/1)
[![Points: 4](https://img.shields.io/badge/Points-4-007BFF?style=for-the-badge)](https://www.geeksforgeeks.org/problems/longest-subarray-with-majority-greater-than-k/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

Given an array `arr[]` and an integer `k`, the task is to find the length of the **longest** subarray in which the **count** of elements **greater than k** is **more** than the count of elements **less than or equal to k**.

---

## 💡 Examples

### Example 1

```text
Input: arr[] = [1, 2, 3, 4, 1], k = 2
Output: 3
Explanation: The subarray [2, 3, 4] or [3, 4, 1] satisfy the given condition, and there is no subarray of length 4 or 5 which will hold the given condition, so the answer is 3.
```

### Example 2

```text
Input: arr[] = [6, 5, 3, 4], k = 2
Output: 4
Explanation: In the subarray [6, 5, 3, 4], there are 4 elements > 2 and 0 elements <= 2, so it is the longest subarray.
```

<details>
<summary><b>📖 Example Breakdown (Example 1)</b></summary>

Let's break down `arr[] = [1, 2, 3, 4, 1]` with `k = 2`:
- We transform the array based on whether an element is `> k` `(+1)` or `<= k` `(-1)`.
- Transformed array: `[-1, -1, 1, 1, -1]`
- We want the longest subarray with a `sum > 0` (i.e., at least `1`).
- Subarray `[2, 3, 4]` transforms to `[-1, 1, 1]`, sum = `1 > 0`. Length = 3.
- Subarray `[3, 4, 1]` transforms to `[1, 1, -1]`, sum = `1 > 0`. Length = 3.
- No larger subarray exists with a positive sum. Output is `3`.
</details>

---

## ⚠️ Constraints

> - `1 ≤ arr.size() ≤ 10^6`
> - `1 ≤ arr[i] ≤ 10^6`
> - `0 ≤ k ≤ 10^6`

---

## 🛠️ Solution Approach

### Optimized Approach (Prefix Sum + Hashing)

```cpp
// Intuition: The problem can be simplified by converting the array into a binary representation.
// Elements > k become +1, and elements <= k become -1. The goal is then to find the
// longest subarray with a sum greater than 0.
//
// Approach:
// 1. Initialize a `sum = 0`, `max_len = 0`, and a hash map `mp` to store the first occurrence of each prefix sum.
// 2. Pre-populate the map with `mp[0] = -1` to handle cases where the valid subarray starts from index 0.
// 3. Iterate through the array from `i = 0` to `n-1`.
// 4. In each iteration, update the `sum` by adding `+1` if `arr[i] > k` and `-1` otherwise.
// 5. Check for two conditions to update `max_len`:
//    a. If `sum > 0`, it means the subarray from index `0` to `i` is a valid candidate. Update `max_len = i + 1`.
//    b. We need a subarray with a sum of at least 1. To find the longest such subarray ending at `i`,
//       we look for a previous prefix sum `sum - 1`. If `mp.count(sum - 1)` exists, it means we found
//       a subarray between `mp[sum - 1]` and `i` with a sum of exactly 1. Update `max_len` with `i - mp[sum - 1]`.
//       (We check for `sum-1` and not just any smaller sum because `sum-1` will give the longest possible length for the current `i`).
// 6. If the current `sum` is not already in the map, add it with its index `i`. This ensures we always store the
//    leftmost index for any sum, which is crucial for maximizing the subarray length.
//
// Time Complexity: O(N), where N is the size of the array. We iterate through the array once.
// Space Complexity: O(N), as the hash map can store up to N distinct prefix sums in the worst case.

class Solution {
public:
    int longestSubarray(vector<int> &arr, int k) {
        unordered_map<int, int> mp;
        int sum = 0;
        int max_len = 0;

        // A sum of 0 is found at index -1 (before the array starts)
        mp[0] = -1;

        for (int i = 0; i < arr.size(); ++i) {
            // Transform the element to +1 or -1 and update sum
            sum += (arr[i] > k) ? 1 : -1;

            // If the current prefix sum is positive, the subarray from index 0 is a candidate.
            // This handles cases where the longest subarray starts from the beginning.
            if (sum > 0) {
                max_len = max(max_len, i + 1);
            }

            // Find a subarray with a sum of at least 1 ending at i.
            // This is equivalent to finding a previous prefix sum of `sum - 1`.
            // mp[sum-1] gives the end of a prefix that we can remove to get a subarray sum of 1.
            if (mp.count(sum - 1)) {
                max_len = max(max_len, i - mp[sum - 1]);
            }

            // If the current sum hasn't been seen before, record its first occurrence.
            // This is key to finding the longest subarray. We only care about the leftmost
            // position of a prefix sum.
            if (mp.find(sum) == mp.end()) {
                mp[sum] = i;
            }
        }
        return max_len;
    }
};

/*
*
* Dry Run with arr[] = [1, 2, 3, 4, 1], k = 2
* Transformed array: [-1, -1, 1, 1, -1]
*
* i = 0: arr[0]=1 -> sum = -1. mp[-1] = 0.
* i = 1: arr[1]=2 -> sum = -2. mp[-2] = 1.
* i = 2: arr[2]=3 -> sum = -1. mp.count(-1-1 = -2) is true. max_len = max(0, 2 - mp[-2]) = max(0, 2 - 1) = 1.
* i = 3: arr[3]=4 -> sum = 0. sum > 0 is false. mp.count(0-1 = -1) is true. max_len = max(1, 3 - mp[-1]) = max(1, 3 - 0) = 3.
* i = 4: arr[4]=1 -> sum = -1. mp.count(-1-1 = -2) is true. max_len = max(3, 4 - mp[-2]) = max(3, 4 - 1) = 3.
*
* Final Result: 3
*
*/
```

---

## 🧠 Key Insights

1. **Array Transformation:** Changing the problem domain from "counting elements" to "finding a positive sum" by replacing target values with `+1` and `-1` makes this a classic prefix-sum map problem.
2. **Finding the Maximum Range:** Because we want the *longest* valid subarray, we only ever store the *first* occurrence of each prefix sum in the hash map. 
3. **Checking `sum - 1`:** If we have a negative sum `S` at index `i`, we need to chop off a prefix with sum `S - 1` to leave a subarray with sum `+1`. Finding `S - 1` specifically ensures we are chopping off the *least* negative prefix possible, yielding the longest possible valid string from that iteration.

---

## 🔍 Further Exploration

If you enjoyed this problem, you might also like these related GeeksforGeeks challenges:
- **Longest Subarray with Sum K**
- **Longest Subarray with Equal 0s and 1s**
- **Subarray with Given Sum**

---

## 📚 References

- **GeeksforGeeks Problem:** [Longest Subarray with Majority Greater than K](https://www.geeksforgeeks.org/problems/longest-subarray-with-majority-greater-than-k/1)
- **Concept:** Prefix Sum Array, Hash Maps

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#Array` `#Hash Map` `#Prefix Sum` `#GeeksforGeeks` `#C++` `#Data Structures` 
