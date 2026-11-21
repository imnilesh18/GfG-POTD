# 🟢 Smallest Subarray Sum Greater Than x

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/smallest-subarray-with-sum-greater-than-x5651/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-37.07%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

> ⚠️ **Educational Use Only:**  
> This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the GeeksforGeeks problem[cite: 1].

---

## 📋 Problem Statement

Given an integer `x` and an array of integers, `arr[]`, find the length of the smallest contiguous subarray whose sum is **strictly greater** than `x`[cite: 1].  
If no such subarray exists, return `0`[cite: 1].

- **Platform:** GeeksforGeeks[cite: 1]
- **Difficulty:** Easy[cite: 1]
- **Accuracy:** 37.07%[cite: 1]
- **Submissions:** 178K+[cite: 1]
- **Points:** 2[cite: 1]
- **Average Time:** 20m[cite: 1]
- **Expected Time Complexity:** $O(n)$[cite: 1]
- **Expected Auxiliary Space:** $O(1)$[cite: 1]
- **Asked In:** Accolite, Amazon, Goldman Sachs, Google, Facebook[cite: 1]

---

## 🧪 Examples

### Example 1
```text
Input: x = 51, arr[] = [1, 4, 45, 6, 0, 19]
Output: 3
Explanation: The smallest subarray with a sum greater than 51 is [4, 45, 6], whose sum is 55 and length is 3.
```
*(Source: GeeksforGeeks Problem Statement[cite: 1])*

### Example 2
```text
Input: x = 100, arr[] = [1, 10, 5, 2, 7]
Output: 0
Explanation: No subarray has a sum greater than 100. Hence, the answer is 0.
```
*(Source: GeeksforGeeks Problem Statement[cite: 1])*

<details>
<summary><b>📖 Example Breakdown (Click to Expand)</b></summary>

Let's walk through **Example 1** where `x = 51` and `arr[] = [1, 4, 45, 6, 0, 19]`[cite: 1]:

1. **Initialize:** `i = 0`, `j = 0`, `sum = 0`, `mini = INT_MAX`
2. **Expand right (`j = 0`):** Add `arr[0] = 1` $\rightarrow$ `sum = 1` ($\le 51$)
3. **Expand right (`j = 1`):** Add `arr[1] = 4` $\rightarrow$ `sum = 5` ($\le 51$)
4. **Expand right (`j = 2`):** Add `arr[2] = 45` $\rightarrow$ `sum = 50` ($\le 51$)
5. **Expand right (`j = 3`):** Add `arr[3] = 6` $\rightarrow$ `sum = 56` ($> 51$, valid window `[1, 4, 45, 6]` of length `4`)
   - **Shrink left (`i = 0`):** `mini = min(INT_MAX, 4) = 4`. Subtract `arr[0] = 1` $\rightarrow$ `sum = 55`, `i = 1`
   - **Shrink left (`i = 1`):** `sum = 55 > 51` is still valid (`[4, 45, 6]`). `mini = min(4, 3) = 3`. Subtract `arr[1] = 4` $\rightarrow$ `sum = 51`, `i = 2`
   - **Stop shrinking:** `sum = 51` is no longer strictly greater than `51`.
6. **Expand right (`j = 4`):** Add `arr[4] = 0` $\rightarrow$ `sum = 51` ($\le 51$)
7. **Expand right (`j = 5`):** Add `arr[5] = 19` $\rightarrow$ `sum = 70` ($> 51$, valid window `[45, 6, 0, 19]` of length `4`)
   - **Shrink left (`i = 2`):** `mini = min(3, 4) = 3`. Subtract `arr[2] = 45` $\rightarrow$ `sum = 25`, `i = 3`
   - **Stop shrinking:** `sum = 25 <= 51`.
8. **Final Answer:** `mini = 3`[cite: 1].

</details>

---

## 🔒 Constraints

> - $1 \le x, \text{arr.size()} \le 10^5$[cite: 1]
> - $0 \le \text{arr}[i] \le 10^4$[cite: 1]

*Note: Since every element `arr[i]` is non-negative ($\ge 0$)[cite: 1], expanding the window to the right never decreases the running sum, and shrinking from the left never increases it. This monotonic property enables an optimal $O(n)$ sliding window solution.*

---

## 💡 Solution Approaches

### 1. Brute-Force Approach (Nested Loops)

#### Intuition
Check every possible contiguous subarray starting at index `i` and ending at index `j`. Maintain a running sum for each starting point, and the moment the sum exceeds `x`, record the subarray length `j - i + 1` and break early since extending further will only produce longer subarrays.

#### C++ Implementation
```cpp
// Intuition: Check all possible subarrays and track the minimum length whose sum exceeds x.
// Approach: Fix a starting index i, accumulate elements using an inner loop j, update the minimum length once sum > x, and break early.
// Time Complexity: O(n^2) in the worst case because two nested loops inspect all subarray pairs.
// Space Complexity: O(1) as only constant extra variables are used.

class Solution {
  public:
    int smallestSubWithSum(vector<int>& arr, int x) {
        int n = arr.size();
        int mini = INT_MAX; // Stores the minimum valid subarray length

        // Try every index as the start of the subarray
        for (int i = 0; i < n; i++) {
            int sum = 0;
            // Expand subarray to the right
            for (int j = i; j < n; j++) {
                sum += arr[j];
                // Record length and stop expanding once sum exceeds x
                if (sum > x) {
                    mini = min(mini, j - i + 1);
                    break;
                }
            }
        }

        // Return 0 if no subarray had a sum greater than x
        return (mini == INT_MAX) ? 0 : mini;
    }
};

/*
*
* Dry Run
* Input: x = 51, arr[] = [1, 4, 45, 6, 0, 19]
*
* i = 0: j = 0 -> sum = 1; j = 1 -> sum = 5; j = 2 -> sum = 50; j = 3 -> sum = 56 (> 51) -> mini = 4, break
* i = 1: j = 1 -> sum = 4; j = 2 -> sum = 49; j = 3 -> sum = 55 (> 51) -> mini = min(4, 3) = 3, break
* i = 2: j = 2 -> sum = 45; j = 3 -> sum = 51; j = 4 -> sum = 51; j = 5 -> sum = 70 (> 51) -> mini = min(3, 4) = 3, break
* i = 3: j = 3 -> sum = 6; j = 4 -> sum = 6; j = 5 -> sum = 25 (<= 51)
* i = 4: j = 4 -> sum = 0; j = 5 -> sum = 19 (<= 51)
* i = 5: j = 5 -> sum = 19 (<= 51)
*
* Result: mini = 3
*
*/
```

---

### 2. Optimized Approach (Two-Pointer Sliding Window)

#### Intuition
Because all elements in `arr[]` are non-negative[cite: 1], we can maintain a dynamic window `[i, j]` using two pointers. We expand the window by moving `j` forward until `sum > x`, and then greedily shrink the window from the left by advancing `i` while `sum > x` remains true to minimize the subarray length.

#### C++ Implementation
```cpp
// Intuition: Use a variable-size sliding window since non-negative elements guarantee monotonic sum changes as pointers move.
// Approach: Expand the window right with pointer j to accumulate sum; whenever sum > x, update minimum length and shrink from left with pointer i until sum <= x.
// Time Complexity: O(n) because both pointers i and j traverse the array at most once (at most 2n operations).
// Space Complexity: O(1) since only a few integer variables are maintained in auxiliary memory.

class Solution {
  public:
    int smallestSubWithSum(vector<int>& arr, int x) {
        int n = arr.size(); // Total number of elements
        int i = 0, j = 0;   // Left and right pointers of the sliding window
        int sum = 0;        // Running sum of current window [i, j]
        int mini = INT_MAX; // Tracks smallest valid subarray length
        
        while (j < n) {
            // 1. Expand window: add current element to calculation
            sum += arr[j];
            
            // 2. Check condition: if sum strictly exceeds x, shrink from left
            if (sum > x) {
                while (sum > x) {
                    mini = min(mini, j - i + 1); // Record current valid window size
                    sum -= arr[i];               // Remove leftmost element from sum
                    i++;                         // Contract window from the left
                }
            }
            
            // 3. Move right pointer forward
            j++;
        }
        
        // Return 0 if no valid subarray was found
        return (mini == INT_MAX) ? 0 : mini;
    }
};

/*
*
* Dry Run
* Input: x = 51, arr[] = [1, 4, 45, 6, 0, 19]
*
* Initial: n = 6, i = 0, j = 0, sum = 0, mini = INT_MAX
* j = 0: sum = 1 (<= 51) -> j becomes 1
* j = 1: sum = 5 (<= 51) -> j becomes 2
* j = 2: sum = 50 (<= 51) -> j becomes 3
* j = 3: sum = 56 (> 51) -> enters shrink loop:
*        mini = min(INT_MAX, 3 - 0 + 1) = 4, sum = 56 - 1 = 55, i = 1
*        mini = min(4, 3 - 1 + 1) = 3, sum = 55 - 4 = 51, i = 2
*        sum = 51 (not > 51, exit shrink loop) -> j becomes 4
* j = 4: sum = 51 + 0 = 51 (<= 51) -> j becomes 5
* j = 5: sum = 51 + 19 = 70 (> 51) -> enters shrink loop:
*        mini = min(3, 5 - 2 + 1) = 3, sum = 70 - 45 = 25, i = 3
*        sum = 25 (not > 51, exit shrink loop) -> j becomes 6
* Loop terminates as j == n.
*
* Output: 3
*
*/
```

---

## 🔑 Key Insights

- **Why Sliding Window Works Here:** The constraint $0 \le \text{arr}[i] \le 10^4$ guarantees there are no negative numbers[cite: 1]. Adding an element at `j` never decreases `sum`, and removing an element at `i` never increases `sum`, ensuring we never miss an optimal subarray when advancing `i`.
- **Amortized Linear Time ($O(n)$):** Although a `while` loop is nested inside the main `while (j < n)` loop, `i` only increments and never resets. Across the entire execution, `i` increments at most `n` times and `j` increments `n` times, yielding strictly $O(n)$ time complexity[cite: 1].
- **Strict Inequality Check:** The condition checks `sum > x` (strictly greater)[cite: 1]. If `sum == x`, the window is not valid and must continue expanding.
- **Edge Case Safety:** Using `INT_MAX` as the initial value for `mini` cleanly distinguishes between a valid minimum length and the case where the entire array sum is $\le x$ (which returns `0`)[cite: 1].

---

## 🚀 Further Exploration

- **Follow-up Question:** *What if `arr[]` could contain negative integers?*  
  Standard two-pointer sliding window fails when negative numbers are present because shrinking the window might actually increase the sum. In that scenario, you would use **Prefix Sums + a Monotonic Deque** to solve it in $O(n)$ time.
- **Related GeeksforGeeks Problems:**
  - [Indexes of Subarray Sum](https://www.geeksforgeeks.org/problems/subarray-with-given-sum-1587115621/1)
  - [Longest Subarray with Sum K](https://www.geeksforgeeks.org/problems/longest-sub-array-with-sum-k0809/1)
  - [Smallest Distinct Window](https://www.geeksforgeeks.org/problems/smallest-distant-window3132/1)

---

## 📚 References

- **Original Problem:** [Smallest Subarray Sum Greater Than x — GeeksforGeeks](https://www.geeksforgeeks.org/problems/smallest-subarray-with-sum-greater-than-x5651/1)[cite: 1]
- **Algorithmic Pattern:** Variable-Size Sliding Window / Two Pointers[cite: 1]

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Arrays](https://img.shields.io/badge/Topic-Arrays-blue?style=flat-square)
![Sliding Window](https://img.shields.io/badge/Topic-Sliding%20Window-blue?style=flat-square)
![Two Pointers](https://img.shields.io/badge/Pattern-Two%20Pointers-informational?style=flat-square)
![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=cplusplus)
![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-298D46?style=flat-square&logo=geeksforgeeks)
![Accolite](https://img.shields.io/badge/Company-Accolite-lightgrey?style=flat-square)
![Amazon](https://img.shields.io/badge/Company-Amazon-lightgrey?style=flat-square)
![Goldman Sachs](https://img.shields.io/badge/Company-Goldman%20Sachs-lightgrey?style=flat-square)
![Google](https://img.shields.io/badge/Company-Google-lightgrey?style=flat-square)
![Facebook](https://img.shields.io/badge/Company-Facebook-lightgrey?style=flat-square)