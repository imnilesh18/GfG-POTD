# 🟧 Longest Subarray Sum Divisible by K

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/longest-subarray-with-sum-divisible-by-k1259/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-33.72%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-success?style=for-the-badge)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Given an array `arr[]` and a positive integer `k`, find the length of the **longest contiguous subarray** whose sum is divisible by `k`.

> **Note:** If there is no subarray with sum divisible by `k`, then return `0`.

- **Input Size:** Up to $10^5$ elements, containing positive, negative, and zero integers.
- **Goal:** Maximize the subarray length in $O(n)$ expected time and $O(\min(n, k))$ auxiliary space.

---

## 🧪 Examples

### Example 1
```text
Input:  arr[] = [2, 7, 6, 1, 4, 5], k = 3
Output: 4
Explanation: The subarray [7, 6, 1, 4] has sum = 18, which is divisible by 3.
```

### Example 2
```text
Input:  arr[] = [-2, 2, -5, 12, -11, -1, 7], k = 3
Output: 5
Explanation: The subarray [2, -5, 12, -11, -1] has sum = -3, which is divisible by 3.
```

### Example 3
```text
Input:  arr[] = [1, 2, -2], k = 2
Output: 2
Explanation: The subarray [2, -2] has sum = 0, which is divisible by 2.
```

<details>
<summary><b>📖 Example Breakdown (Example 1 Walkthrough)</b></summary>

For `arr[] = [2, 7, 6, 1, 4, 5]` and `k = 3`:

1. **Initialization:** Store `firstSeen[0] = -1` to handle subarrays starting at index `0`, with `prefixSum = 0` and `maxLen = 0`.
2. **Index `0` (`val = 2`):** `prefixSum = 2`, normalized remainder `rem = 2`. Not seen yet, so record `firstSeen[2] = 0`.
3. **Index `1` (`val = 7`):** `prefixSum = 9`, `rem = 0`. Remainder `0` was seen at index `-1`, giving length `1 - (-1) = 2` (`[2, 7]`). Update `maxLen = 2`.
4. **Index `2` (`val = 6`):** `prefixSum = 15`, `rem = 0`. Remainder `0` was first seen at `-1`, giving length `2 - (-1) = 3` (`[2, 7, 6]`). Update `maxLen = 3`.
5. **Index `3` (`val = 1`):** `prefixSum = 16`, `rem = 1`. Not seen yet, so record `firstSeen[1] = 3`.
6. **Index `4` (`val = 4`):** `prefixSum = 20`, `rem = 2`. Remainder `2` was first seen at index `0`, meaning the subarray from `0 + 1` to `4` (`[7, 6, 1, 4]`) has sum `20 - 2 = 18`, which is divisible by `3`. Length is `4 - 0 = 4`. Update `maxLen = 4`.
7. **Index `5` (`val = 5`):** `prefixSum = 25`, `rem = 1`. Remainder `1` was first seen at index `3`, giving length `5 - 3 = 2` (`[4, 5]`). `maxLen` stays `4`.

Final answer is **`4`**.
</details>

---

## 🔒 Constraints

> - $1 \le \text{arr.size()}, k \le 10^5$
> - $-10^5 \le \text{arr}[i] \le 10^5$
> - **Expected Time Complexity:** $O(n)$
> - **Expected Auxiliary Space:** $O(\min(n, k))$

---

## 💡 Solution Approaches

### 1️⃣ Brute-Force Overview
- **Intuition:** Generate all possible subarrays $(i, j)$ using two nested loops, compute their sums, and track the maximum length `j - i + 1` whenever `sum % k == 0`.
- **Complexity:** Takes $O(n^2)$ time and $O(1)$ space, which exceeds the time limit for $n \le 10^5$.

---

### 2️⃣ Optimized Approach: Prefix Sum + Modulo Hash Map

- **Intuition:** If two prefix sums at indices $i$ and $j$ ($i < j$) leave the same non-negative remainder when divided by $k$, their difference ($\text{prefixSum}[j] - \text{prefixSum}[i]$) is divisible by $k$, so the subarray `arr[i + 1 ... j]` has a sum divisible by $k$.
- **Approach:**
  1. Initialize a hash map `firstSeen` with `{0: -1}` to account for valid subarrays starting from index `0`.
  2. Traverse the array while maintaining a running `prefixSum` (`long long` to prevent integer overflow).
  3. Compute the normalized non-negative remainder `rem = ((prefixSum % k) + k) % k`.
  4. If `rem` already exists in `firstSeen`, update `maxLen = max(maxLen, i - firstSeen[rem])`. Otherwise, store `firstSeen[rem] = i`.

```cpp
// Intuition: If two prefix sums yield the same modulo k remainder, the subarray between them has a sum divisible by k.
// Approach: Track running prefixSum and store the earliest index of each normalized remainder in a hash map to maximize subarray length.
// Time Complexity: O(n), where n is the size of arr, since each element is processed once with O(1) average hash map lookups.
// Space Complexity: O(min(n, k)), as at most k distinct remainders (and at most n prefix entries) are stored in the hash map.
class Solution {
  public:
    int longestSubarrayDivK(vector<int>& arr, int k) {
        unordered_map<int, int> firstSeen;
        firstSeen[0] = -1; // Base case: remainder 0 at index -1 for subarrays starting from index 0

        long long prefixSum = 0; // Use 64-bit integer to avoid overflow for large sums
        int maxLen = 0;

        for (int i = 0; i < arr.size(); i++) {
            prefixSum += arr[i]; // Accumulate running prefix sum

            // Normalize remainder into [0, k - 1] to handle negative prefix sums
            int rem = ((prefixSum % k) + k) % k;

            if (firstSeen.find(rem) != firstSeen.end()) {
                maxLen = max(maxLen, i - firstSeen[rem]); // Update max length using earliest matching remainder
            } else {
                // Store only the first occurrence of rem to maximize subarray length
                firstSeen[rem] = i;
            }
        }

        return maxLen;
    }
};

/*
 * Dry Run
 *
 * Input: arr = [2, 7, 6, 1, 4, 5], k = 3
 * Initial: firstSeen = {0: -1}, prefixSum = 0, maxLen = 0
 *
 * i = 0, arr[0] = 2:
 *   prefixSum = 2, rem = ((2 % 3) + 3) % 3 = 2
 *   rem 2 not in firstSeen -> firstSeen[2] = 0
 *
 * i = 1, arr[1] = 7:
 *   prefixSum = 9, rem = ((9 % 3) + 3) % 3 = 0
 *   rem 0 found at index -1 -> maxLen = max(0, 1 - (-1)) = 2
 *
 * i = 2, arr[2] = 6:
 *   prefixSum = 15, rem = ((15 % 3) + 3) % 3 = 0
 *   rem 0 found at index -1 -> maxLen = max(2, 2 - (-1)) = 3
 *
 * i = 3, arr[3] = 1:
 *   prefixSum = 16, rem = ((16 % 3) + 3) % 3 = 1
 *   rem 1 not in firstSeen -> firstSeen[1] = 3
 *
 * i = 4, arr[4] = 4:
 *   prefixSum = 20, rem = ((20 % 3) + 3) % 3 = 2
 *   rem 2 found at index 0 -> maxLen = max(3, 4 - 0) = 4
 *
 * i = 5, arr[5] = 5:
 *   prefixSum = 25, rem = ((25 % 3) + 3) % 3 = 1
 *   rem 1 found at index 3 -> maxLen = max(4, 5 - 3) = 4
 *
 * Output: 4
 */
```

---

## 🔑 Key Insights

- **Handling Negative Numbers in C++:** In C++, the `%` operator can return negative values when `prefixSum < 0` (e.g., `-4 % 3 = -1`). Using `((prefixSum % k) + k) % k` shifts all remainders into `[0, k - 1]`, ensuring `-4` (remainder `2`) and `+2` (remainder `2`) map to the same equivalence class.
- **Greedy First-Occurrence Storage:** Never overwrite `firstSeen[rem]` once recorded. Keeping the earliest index guarantees the largest possible distance `i - firstSeen[rem]` for any future match.
- **Overflow Protection:** With up to $10^5$ elements of magnitude $10^5$, the cumulative sum can reach $\pm 10^{10}$, requiring `long long` for `prefixSum`.

---

## 🚀 Further Exploration

- [Subarray Sums Divisible by K](https://www.geeksforgeeks.org/problems/sub-array-sum-divisible-by-k2617/1) — Count the total number of subarrays whose sum is divisible by `k`.
- [Largest Subarray with 0 Sum](https://www.geeksforgeeks.org/problems/largest-subarray-with-0-sum/1) — Find the longest contiguous subarray with sum equal to `0`.
- [Longest Subarray with Sum K](https://www.geeksforgeeks.org/problems/longest-sub-array-with-sum-k0809/1) — Find the longest subarray whose sum equals a target `k` with positive and negative elements.
- [Zero Sum Subarrays](https://www.geeksforgeeks.org/problems/zero-sum-subarrays1825/1) — Count all subarrays having sum equal to `0`.

---

## 📚 References

- **Original Problem:** [GeeksforGeeks — Longest Subarray Sum Divisible by K](https://www.geeksforgeeks.org/problems/longest-subarray-with-sum-divisible-by-k1259/1)
- **Core Concepts:** Prefix Sums, Modular Arithmetic Equivalence, Hash Tables (`std::unordered_map`)

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)
- **GeeksforGeeks:** [imnilesh18](https://www.geeksforgeeks.org/profile/imnilesh18)

---

## 🏷️ Tags

**Topic Tags:**
![Prefix Sum](https://img.shields.io/badge/Prefix%20Sum-informational?style=flat-square)
![Arrays](https://img.shields.io/badge/Arrays-informational?style=flat-square)
![Hash](https://img.shields.io/badge/Hash-informational?style=flat-square)
![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)

**Company Tags:**
![Microsoft](https://img.shields.io/badge/Microsoft-5E5E5E?style=flat-square&logo=microsoft&logoColor=white)
![Snapdeal](https://img.shields.io/badge/Snapdeal-E40046?style=flat-square)