# 🟧 Sum of subarray ranges

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/sum-of-subarray-ranges/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/sum-of-subarray-ranges/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-50.82%25-green?style=for-the-badge)](https://www.geeksforgeeks.org/problems/sum-of-subarray-ranges/1)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/sum-of-subarray-ranges/1)
![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

</div>

---

### ⚠️ Educational Use Only
> **This repository and its content are intended solely for educational purposes.** > **Solutions are provided for learning, practice, and reference only.** > **Problem statement and test cases are based on the GeeksforGeeks problem.**

---

## 🧐 Problem Statement

Given an integer array `arr[]`, the **range** of a subarray is defined as the difference between the **largest** and **smallest** elements within that subarray. Your task is to return the **sum** of the ranges of all possible subarrays in the array.

> **Note:** It is guaranteed that the result will fit within a 32-bit integer.

---

## 📊 Constraints

* $1 \le arr.size() \le 10^6$
* $10^{-9} \le arr[i] \le 10^9$

---

## 📝 Examples

### Example 1

```text
Input: arr[] = [1, 2, 3]
Output: 4

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

The 6 subarrays of `arr` are:

1. `[1]`: range = 1 - 1 = 0
2. `[2]`: range = 2 - 2 = 0
3. `[3]`: range = 3 - 3 = 0
4. `[1, 2]`: range = 2 - 1 = 1
5. `[2, 3]`: range = 3 - 2 = 1
6. `[1, 2, 3]`: range = 3 - 1 = 2

**Total Sum** = 0 + 0 + 0 + 1 + 1 + 2 = **4**

</details>

### Example 2

```text
Input: arr[] = [-32, 0, -2, 72]
Output: 318
Explanation: 
[-32] range: 0
[-32, 0] range: 32
... (summing all ranges)
Total Sum: 318

```

---

## 💡 Solution Approach

### 🚀 Optimized Approach (Monotonic Stack)

#### Intuition

The problem asks for  for all subarrays.
By linearity of expectation (or simple summation properties), this equals:
$$ \sum \text{Max}(Subarray) - \sum \text{Min}(Subarray) $$
Instead of generating all subarrays (), we can count how many times each element `arr[i]` serves as the **maximum** or **minimum** in a subarray.
Using a **Monotonic Stack**, we find the indices of the Previous Greater Element (PGE), Next Greater Element (NGE), Previous Smaller Element (PSE), and Next Smaller Element (NSE) for every `arr[i]`. The number of subarrays where `arr[i]` is the extremum is derived from the distance to these boundaries.

#### Implementation

```cpp
// Intuition: The sum of ranges is sum(all maxes) - sum(all mins). We calculate the contribution of each element as a maximum and as a minimum separately using Monotonic Stacks.
// Approach: 
// 1. Find indices of Previous Greater and Next Greater elements for every index to calculate sum of maximums.
// 2. Find indices of Previous Smaller and Next Smaller elements for every index to calculate sum of minimums.
// 3. Contribution = (i - prev_index) * (next_index - i) * arr[i].
// 4. Result is Sum(Max contributions) - Sum(Min contributions).
// Time Complexity: O(n) due to linear traversals and amortized O(1) stack operations.
// Space Complexity: O(n) for storing index arrays and stack.

class Solution {
  public:
    int subarrayRanges(vector<int>& arr) {
        int n = arr.size();
        long long totalSum = 0;
        stack<int> s;

        // --- Step 1: Add contribution of Maximums ---
        // Arrays to store indices of previous and next greater elements
        vector<int> prevGreater(n, -1);
        vector<int> nextGreater(n, n);

        // Find Previous Greater Element (strictly greater)
        for (int i = 0; i < n; i++) {
            // Pop elements smaller or equal to current to maintain monotonic decreasing stack
            while (!s.empty() && arr[s.top()] <= arr[i]) {
                s.pop();
            }
            if (!s.empty()) prevGreater[i] = s.top();
            s.push(i);
        }

        // Clear stack for next pass
        while (!s.empty()) s.pop();

        // Find Next Greater Element (greater or equal)
        for (int i = n - 1; i >= 0; i--) {
            // Pop elements strictly smaller to handle duplicates correctly (one side strict, one non-strict)
            while (!s.empty() && arr[s.top()] < arr[i]) {
                s.pop();
            }
            if (!s.empty()) nextGreater[i] = s.top();
            s.push(i);
        }

        // Calculate Sum of Maximums
        for (int i = 0; i < n; i++) {
            long long leftCount = i - prevGreater[i];
            long long rightCount = nextGreater[i] - i;
            // Add contribution: value * number of subarrays where arr[i] is max
            totalSum += (leftCount * rightCount * arr[i]);
        }

        // --- Step 2: Subtract contribution of Minimums ---
        while (!s.empty()) s.pop(); // Clear stack
        vector<int> prevSmaller(n, -1);
        vector<int> nextSmaller(n, n);

        // Find Previous Smaller Element (strictly smaller)
        for (int i = 0; i < n; i++) {
            // Pop elements larger or equal
            while (!s.empty() && arr[s.top()] >= arr[i]) {
                s.pop();
            }
            if (!s.empty()) prevSmaller[i] = s.top();
            s.push(i);
        }

        while (!s.empty()) s.pop(); // Clear stack

        // Find Next Smaller Element (smaller or equal)
        for (int i = n - 1; i >= 0; i--) {
            // Pop elements strictly larger
            while (!s.empty() && arr[s.top()] > arr[i]) {
                s.pop();
            }
            if (!s.empty()) nextSmaller[i] = s.top();
            s.push(i);
        }

        // Calculate Sum of Minimums and subtract from total
        for (int i = 0; i < n; i++) {
            long long leftCount = i - prevSmaller[i];
            long long rightCount = nextSmaller[i] - i;
            // Subtract contribution: value * number of subarrays where arr[i] is min
            totalSum -= (leftCount * rightCount * arr[i]);
        }

        return (int)totalSum;
    }
};

/*
*
* Dry Run
* Input: arr = [1, 2, 3]
* n = 3
*
* Part 1: Maximums
* i=0 (val=1): prevGreater=-1, nextGreater=1. Count = (0 - -1) * (1 - 0) = 1. Contribution = 1 * 1 = 1.
* i=1 (val=2): prevGreater=-1, nextGreater=2. Count = (1 - -1) * (2 - 1) = 2. Contribution = 2 * 2 = 4.
* i=2 (val=3): prevGreater=-1, nextGreater=3. Count = (2 - -1) * (3 - 2) = 3. Contribution = 3 * 3 = 9.
* Sum of Max = 1 + 4 + 9 = 14.
*
* Part 2: Minimums
* i=0 (val=1): prevSmaller=-1, nextSmaller=3. Count = (0 - -1) * (3 - 0) = 3. Contribution = 3 * 1 = 3.
* i=1 (val=2): prevSmaller=0, nextSmaller=3. Count = (1 - 0) * (3 - 1) = 2. Contribution = 2 * 2 = 4.
* i=2 (val=3): prevSmaller=1, nextSmaller=3. Count = (2 - 1) * (3 - 2) = 1. Contribution = 1 * 3 = 3.
* Sum of Min = 3 + 4 + 3 = 10.
*
* Total Sum = Sum of Max - Sum of Min = 14 - 10 = 4.
* Output: 4
*/

```

---

## 🔑 Key Insights

* **Decomposition:** The range problem can be split into finding the "sum of subarray maximums" and "sum of subarray minimums" separately.
* **Monotonic Stack:** This data structure efficiently finds the **Next Greater/Smaller Element** in  time.
* **Handling Duplicates:** To ensure each subarray is counted exactly once when duplicate elements exist, we use a strict comparison on one side (e.g., previous element) and a non-strict comparison on the other (e.g., next element).
* Example: For maximums, look for strictly greater on the left and greater-or-equal on the right.



---

## 🔍 Further Exploration

* **Sum of Subarray Minimums:** A subset of this problem.
* **Largest Rectangle in Histogram:** Uses similar Monotonic Stack logic.
* **Trapping Rain Water:** Another classic stack-based problem.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/sum-of-subarray-ranges/1)
* [Monotonic Stack Explanation](https://cp-algorithms.com/data_structures/stack_queue_modification.html)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🔖 Tags

---

<div align="center">

### 📜 License

This project is licensed under the **MIT License**.

<details>
<summary><b>Show License</b></summary>

```
MIT License

Copyright (c) 2024 imnilesh18

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

```

</details>

**⚠️ Educational Use Only**

</div>
