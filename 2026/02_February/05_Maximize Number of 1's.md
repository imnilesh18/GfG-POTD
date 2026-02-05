# 🟧 Maximize Number of 1's

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/maximize-number-of-1s0905/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/maximize-number-of-1s0905/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-39.46%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/maximize-number-of-1s0905/1)
[![Points](https://img.shields.io/badge/Points-4-brightgreen?style=for-the-badge)](https://www.geeksforgeeks.org/problems/maximize-number-of-1s0905/1)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

---

### ⚠️ Educational Use Only
> **This repository and its content are intended solely for educational purposes.** > **Solutions are provided for learning, practice, and reference only.** > **Problem statement and test cases are based on the GeeksforGeeks problem.**

---

## 🧐 Problem Statement

Given a binary array `arr[]` containing only **0s** and **1s** and an integer `k`, you are allowed to flip at most `k` **0s** to **1s**. Find the **maximum** number of consecutive **1's** that can be obtained in the array after performing the operation at most `k` times.

### 🛑 Constraints
- $1 \leq arr.size() \leq 10^5$
- $0 \leq k \leq arr.size()$
- $0 \leq arr[i] \leq 1$

---

## 📂 Examples

### Example 1
```bash
Input: arr[] = [1, 0, 1], k = 1
Output: 3
Explanation: By flipping the zero at index 1, we get the longest subarray from index 0 to 2 containing all 1’s.

```

### Example 2

```bash
Input: arr[] = [1, 0, 0, 1, 0, 1, 0, 1], k = 2
Output: 5
Explanation: By flipping the zeroes at indices 4 and 6, we get the longest subarray from index 3 to 7 containing all 1’s.

```

### Example 3

```bash
Input: arr[] = [1, 1], k = 2
Output: 2
Explanation: Since the array is already having the max consecutive 1's, hence we dont need to perform any operation. Hence the answer is 2.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's look at Example 2: `arr = [1, 0, 0, 1, 0, 1, 0, 1], k = 2`.
We want the longest subarray with at most `k=2` zeros.

1. **Window `[1]**`: 0 zeros. Valid. MaxLen = 1.
2. **Window `[1, 0]**`: 1 zero. Valid. MaxLen = 2.
3. **Window `[1, 0, 0]**`: 2 zeros. Valid. MaxLen = 3.
4. **Window `[1, 0, 0, 1]**`: 2 zeros. Valid. MaxLen = 4.
5. **Window `[1, 0, 0, 1, 0]**`: 3 zeros. **Invalid**.
* Shrink from left: remove `1`. Window: `[0, 0, 1, 0]`. 3 zeros. Still Invalid.
* Shrink from left: remove `0`. Window: `[0, 1, 0]`. 2 zeros. Valid.
* Current MaxLen calculation doesn't beat 4 yet (current length 3).


6. Eventually, the window covering indices 3 to 7 `[1, 0, 1, 0, 1]` contains exactly 2 zeros. Its length is 5.
7. This is the maximum possible length.

</details>

---

## 💡 Solution - Sliding Window (Two Pointers)

The core insight is to rephrase the problem: finding the longest sequence of 1s after flipping at most `k` 0s is mathematically identical to finding the **longest subarray that contains at most `k` zeros**.

If a subarray has `z` zeros and we assume they are all flipped, the length of consecutive 1s becomes the length of that subarray, provided `z <= k`.

### C++ Code

```cpp
// Intuition: The problem asks for the longest sequence of 1s after flipping at most k 0s. This is equivalent to finding the longest contiguous subarray that contains at most k zeros.
// Approach: We use a sliding window defined by pointers i (start) and j (end). We expand j to include elements. If the count of zeros in the window exceeds k, we increment i to shrink the window from the left until the zero count is valid (<= k). We track the maximum window length throughout.
// Time Complexity: O(N) - Each element is visited at most twice (once by the right pointer j and once by the left pointer i).
// Space Complexity: O(1) - We only use a few integer variables for state tracking.

class Solution {
  public:
    int maxOnes(vector<int>& arr, int k) {
        int n = arr.size();
        int i = 0; // Left pointer (start of window)
        int j = 0; // Right pointer (end of window)
        int zeroCount = 0;
        int maxLen = 0;

        while (j < n) {
            // 1. Expansion: Include current element arr[j] in the window
            if (arr[j] == 0) {
                zeroCount++; // Found a zero, increment count
            }

            // 2. Shrink the window from left if number of zeroes is greater than k
            // Keep shrinking until the window becomes valid again (zeros <= k)
            while (zeroCount > k) {
                if (arr[i] == 0) {
                    zeroCount--; // Removing a zero from the window
                }
                i++; // Move left pointer forward to shrink
            }

            // 3. Calculate result: update the maximum length of the valid window
            // The current window [i, j] has at most k zeros.
            // Length is j - i + 1.
            maxLen = max(maxLen, j - i + 1);

            // 4. Increment end pointer to expand the window
            j++;
        }

        return maxLen;
    }
};

/*
* Dry Run
* Input: arr = [1, 0, 0, 1], k = 1
*
* Iteration 1:
* j = 0, arr[0] = 1. zeroCount = 0.
* Condition (zeroCount > k) is false.
* maxLen = max(0, 0 - 0 + 1) = 1.
* j becomes 1.
*
* Iteration 2:
* j = 1, arr[1] = 0. zeroCount = 1.
* Condition (zeroCount > k) is false.
* maxLen = max(1, 1 - 0 + 1) = 2.
* j becomes 2.
*
* Iteration 3:
* j = 2, arr[2] = 0. zeroCount = 2.
* Condition (zeroCount 2 > k 1) is true. Enter inner loop.
* - i = 0, arr[0] = 1. zeroCount remains 2. i becomes 1.
* - i = 1, arr[1] = 0. zeroCount becomes 1. i becomes 2.
* Condition (zeroCount 1 > k 1) is false. Exit inner loop.
* Window is now [2, 2] (value: 0).
* maxLen = max(2, 2 - 2 + 1) = 2.
* j becomes 3.
*
* Iteration 4:
* j = 3, arr[3] = 1. zeroCount = 1.
* Condition (zeroCount > k) is false.
* maxLen = max(2, 3 - 2 + 1) = 2.
* j becomes 4.
*
* Loop ends (j < n is false).
* Return maxLen = 2.
*/

```

---

## 🗝️ Key Insights

1. **Problem Transformation:** Instead of actually modifying the array (flipping bits), we simply count zeros. This turns a "modification" problem into a standard "counting/subarray" problem.
2. **Sliding Window Property:** The condition "at most `k` zeros" is monotonic. If a window `[i, j]` is invalid (too many zeros), any super-window `[i, j+1]` is also invalid. This allows us to efficiently find the optimal `i` for every `j`.
3. **Efficiency:** This greedy, one-pass approach is optimal. We don't need nested loops to check every subarray.

---

## 🚀 Further Exploration

* **Weighted Flips:** What if flipping a zero costs a certain amount, and you have a total budget `W`? (This becomes a window sum problem).
* **Stream of Data:** How would you handle this if the array was an infinite stream of bits? (You might store indices of zeros in a deque).
* **Longest Subarray of 1's after deleting one element:** A similar problem often solved with prefix/suffix sums or sliding window.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/maximize-number-of-1s0905/1)
* [Sliding Window Technique Explained](https://www.geeksforgeeks.org/window-sliding-technique/)

---

## 🙋‍♂️ Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🔖 Tags

`#arrays` `#sliding-window` `#two-pointers` `#binary-search` `#cpp` `#geeksforgeeks` `#medium`

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

> **Note:** This repository is for educational purposes. Please respect the Code of Conduct and use these solutions for learning.
