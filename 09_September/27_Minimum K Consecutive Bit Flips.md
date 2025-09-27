#  Flipping Bits Minimum K Consecutive Bit Flips 🪙

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-70.62%25-brightgreen?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

---

> ⚠️ **Educational Use Only**: This repository and its content are intended solely for educational purposes. The solutions provided are for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/minimum-number-of-k-consecutive-bit-flips--171650/1).

---

## Problem Statement

You are given a binary array `arr[]` (containing only `0`'s and `1`'s) and an integer `k`. In one operation, you can select a contiguous subarray of length `k` and **flip all its bits** (i.e., change every `0` to `1` and every `1` to `0`).

Your task is to find the **minimum** number of such operations required to make the entire array consist of only `1`'s. If it is not possible, return `-1`.

---

## Examples

Here are a couple of examples to illustrate the problem:

<div align="center">
<img src="https://assets.leetcode.com/uploads/2021/02/25/kbits-ex1.png" alt="Example Illustration" width="600"/>
</div>

**Example 1:**
```
Input: arr = [1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1], k = 2
Output: 4
Explanation:
1. Select subarray [2, 3] and flip: [1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1]
2. Select subarray [4, 5] and flip: [1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1]
3. Select subarray [5, 6] and flip: [1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1]
4. Select subarray [6, 7] and flip: [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
```

<details>
<summary>📖 Example Breakdown</summary>

Let's walk through the first example: `arr = [1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1]`, `k = 2`.

- We iterate from left to right. The first `0` is at index `2`.
- We **must** flip the subarray of length `k=2` starting at index `2`. If we don't, this `0` will never be flipped to a `1` because our window only moves forward.
- **Flip 1 (indices 2-3):**
  - `arr` becomes `[1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1]`.
  - We have performed `1` flip.
- The next `0` is at index `4`.
- **Flip 2 (indices 4-5):**
  - `arr` becomes `[1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1]`.
  - Total flips: `2`.
- The next `0` is at index `5`.
- **Flip 3 (indices 5-6):**
  - `arr` becomes `[1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1]`.
  - Total flips: `3`.
- The next `0` is at index `6`.
- **Flip 4 (indices 6-7):**
  - `arr` becomes `[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]`.
  - Total flips: `4`.
- The array is now all `1`s. The minimum number of operations is `4`.

</details>

**Example 2:**
```
Input: arr = [0, 0, 1, 1, 1, 0, 0], k = 3
Output: -1
Explanation: It is not possible to convert all elements to 1's. After flipping from the first 0, we reach a state where the last few elements are 0, and we cannot start a flip that stays within bounds.
```

---

## Constraints

- `1 ≤ arr.size() ≤ 10^6`
- `1 ≤ k ≤ arr.size()`

---

## Solution Approaches

### Optimized Greedy Approach (Sliding Window)

The core idea is to use a greedy strategy. When we encounter a `0`, we must perform a flip operation starting at that index. Why? Because this is our only chance to turn this `0` into a `1`. Any future flip operation starting at a later index won't affect the current position.

To implement this efficiently without repeatedly flipping subarrays (which would be `O(N*K)`), we can use a clever trick. Instead of actually flipping the values, we can track the "effect" of past flips on the current element.

#### C++ Solution

```cpp
// Intuition: A greedy approach works best. When we see a '0', we must flip the next 'k' bits to make the current bit '1'.
// This is our only chance to fix the current bit, as future flips won't affect it. We can track the number of active flips
// affecting the current element to determine its effective value without modifying the array multiple times.

// Approach: We iterate through the array, maintaining a count `current_active_flips`. This count represents how many
// past flip operations are currently "active" and affecting the current index `i`.
// 1. If we are at index `i`, any flip that started at `i-k` is now out of range. So we decrement `current_active_flips`
//    if a flip was initiated at `i-k`. We use the array itself to mark this, by adding 2 to `arr[i-k]`.
// 2. We check the effective value of `arr[i]`. If `(arr[i] + current_active_flips)` is even, it means the effective
//    value is 0 (since 0+even=even, 1+odd=even).
// 3. If the effective value is 0, we must perform a flip. We increment `total_flips` and `current_active_flips`.
//    To mark that a flip started here, we add 2 to `arr[i]`. This preserves the original parity (0->2, 1->3) while marking.
// 4. If a required flip would go out of bounds (i.e., `i + k > n`), it's impossible, so we return -1.

// Time Complexity: O(N), where N is the size of the array. We iterate through the array once.
// Space Complexity: O(1), as we modify the input array in place to store flip information, using no extra space.

class Solution {
  public:
    /**
     * @brief Finds the minimum number of k-bit flips to make the array all 1s.
     * This function uses a greedy approach with a sliding window optimization to achieve
     * linear time complexity and constant extra space.
     * @param arr The binary array of 0s and 1s, passed by reference.
     * @param k The length of the contiguous subarray to flip in one operation.
     * @return The minimum number of operations, or -1 if impossible.
     */
    int kBitFlips(vector<int>& arr, int k) {
        int n = arr.size();
        int total_flips = 0;

        // Tracks the net effect of flip operations on the current element.
        // An even value means no net flip; an odd value means a net flip.
        int current_active_flips = 0;

        for (int i = 0; i < n; ++i) {
            // A flip that started at index (i - k) is no longer active.
            // We use a marker (value > 1) to check if a flip was initiated there.
            if (i >= k && arr[i - k] > 1) {
                current_active_flips--; // Deactivate the flip that's now out of the window.
            }

            // Determine the effective value of the current bit.
            // (arr[i] + current_active_flips) % 2 == 0 means the effective bit is 0.
            // This works even if arr[i] is marked (e.g., 2 or 3), because adding 2
            // doesn't change the parity of the sum.
            if ((arr[i] + current_active_flips) % 2 == 0) {
                // If the effective value is 0, we must perform a flip starting at `i`.

                // Check if a flip starting at `i` would go out of bounds.
                if (i + k > n) {
                    return -1; // Impossible to make the array all 1s.
                }

                // Register the new flip.
                total_flips++;
                current_active_flips++;

                // Mark the start of this flip operation by adding 2.
                // This preserves the original bit's parity (0->2, 1->3) while marking.
                arr[i] += 2;
            }
        }

        return total_flips;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1], k = 2
 *
 * i = 0: arr[0]=1. (1+0)%2 != 0. No flip.
 * i = 1: arr[1]=1. (1+0)%2 != 0. No flip.
 * i = 2: arr[2]=0. (0+0)%2 == 0. Flip needed.
 * - i+k = 4 <= 11. Valid.
 * - total_flips = 1.
 * - current_active_flips = 1.
 * - arr[2] becomes 0+2=2.
 * - arr state (conceptually): [1, 1, 2, 0, 0, 1, 1, 0, 1, 1, 1]
 *
 * i = 3: i>=k (3>=2). arr[i-k]=arr[1]=1 <= 1. No change to current_active_flips.
 * arr[3]=0. (0+1)%2 != 0. No flip needed.
 *
 * i = 4: i>=k (4>=2). arr[i-k]=arr[2]=2 > 1. Deactivate flip.
 * - current_active_flips becomes 0.
 * - arr[4]=0. (0+0)%2 == 0. Flip needed.
 * - i+k = 6 <= 11. Valid.
 * - total_flips = 2.
 * - current_active_flips = 1.
 * - arr[4] becomes 0+2=2.
 * - arr state (conceptually): [1, 1, 2, 0, 2, 1, 1, 0, 1, 1, 1]
 *
 * i = 5: i>=k (5>=2). arr[i-k]=arr[3]=0 <= 1. No change.
 * arr[5]=1. (1+1)%2 == 0. Flip needed (effective value is 0).
 * - i+k = 7 <= 11. Valid.
 * - total_flips = 3.
 * - current_active_flips = 2.
 * - arr[5] becomes 1+2=3.
 *
 * i = 6: i>=k (6>=2). arr[i-k]=arr[4]=2 > 1. Deactivate flip.
 * - current_active_flips becomes 1.
 * - arr[6]=1. (1+1)%2 == 0. Flip needed (effective value is 0).
 * - i+k = 8 <= 11. Valid.
 * - total_flips = 4.
 * - current_active_flips = 2.
 * - arr[6] becomes 1+2=3.
 *
 * ... and so on. The final result will be 4.
 *
 */
```

---

## Key Insights

- **Greedy Choice**: The key insight is that the decision to flip at any index `i` is determined solely by the state of `arr[i]`. If it's a `0` (or its effective value is `0`), we *must* flip. This greedy choice doesn't negatively impact future decisions because it's the only opportunity to fix the current bit.
- **State Tracking with O(1) Space**: The brilliant part of the optimized solution is avoiding the use of an extra queue or array to track active flips. By modifying the input array `arr` (e.g., by adding 2), we can mark the start of a flip operation. This lets us know when to "deactivate" a flip's effect as our sliding window moves past it, achieving a constant space complexity.

---

## Further Exploration

- **[Sliding Window Maximum](https://www.geeksforgeeks.org/problems/sliding-window-maximum/1)**: A classic problem that uses a deque to find the maximum in every window of size `k`.
- **[Count Subarrays with Fixed Bounds](https://www.geeksforgeeks.org/problems/count-subarrays-with-fixed-bounds/1)**: Another sliding window problem that requires careful management of window boundaries.
- **[Longest Substring with At Most K Distinct Characters](https://www.geeksforgeeks.org/problems/longest-k-unique-characters-substring/0)**: A problem that involves expanding and shrinking a window to meet certain criteria.

---

## References

- **[Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/minimum-number-of-k-consecutive-bit-flips--171650/1)**
- **[Sliding Window Technique](https://www.geeksforgeeks.org/window-sliding-technique/)**

---

## Author

- **Connect with me on GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## Tags

`Array` `Greedy` `Sliding Window` `Bit Manipulation` `Hard` `GeeksforGeeks`

---

## License

This project is licensed under the MIT License - see the [LICENSE](https://opensource.org/licenses/MIT) file for details.

**A gentle reminder**: This solution is for educational purposes. Always try to solve problems on your own first!