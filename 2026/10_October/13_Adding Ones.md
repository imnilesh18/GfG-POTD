# 🟩 Adding Ones

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Easy-4caf50?style=for-the-badge" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Accuracy-48.06%25-blue?style=for-the-badge" alt="Accuracy: 48.06%" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points: 2" />
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge" alt="License: MIT" />
</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Consider an array `arr[]` of size `n`, initially containing all zeros[cite: 1]. You are also given an array `updates[]` of `k` positive integers[cite: 1].

For each value `j` in `updates[]`, add `1` to every element `arr[i]` whose index satisfies `i ≥ j`[cite: 1].

The indices in `updates[]` are 1-based[cite: 1].

Perform all the updates and modify `arr[]` accordingly[cite: 1].

---

## 💡 Examples

**Example 1:**
```text
Input: n = 3, updates[] = [1, 1, 2, 3]
Output: [2, 3, 4]
Explanation: 
Initially, arr[] = [0, 0, 0]. 
After the first update 1, the array becomes [1, 1, 1]. 
After the second update 1, it becomes [2, 2, 2]. 
The update 2 increments all elements from index 2 onward, giving [2, 3, 3]. 
Finally, the update 3 increments the element at index 3, resulting in [2, 3, 4].
```
**

**Example 2:**
```text
Input: n = 2, updates[] = [1, 1, 1]
Output: [3, 3] 
Explanation: 
Initially the array is [0, 0]. 
After the first 1, it becomes [1, 1]. 
After the second 1 it becomes [2, 2]. 
After the third 1, it becomes [3, 3].
```
**

<details>
<summary>📖 <b>Example Breakdown (Interactive)</b></summary>

Let's break down Example 1 step-by-step using an optimized boundary marking logic instead of looping ranges:
1. Start with `arr = [0, 0, 0]`.
2. For update `1` (index 0), mark it: `arr[0]++` -> `[1, 0, 0]`.
3. For update `1` (index 0), mark it: `arr[0]++` -> `[2, 0, 0]`.
4. For update `2` (index 1), mark it: `arr[1]++` -> `[2, 1, 0]`.
5. For update `3` (index 2), mark it: `arr[2]++` -> `[2, 1, 1]`.
6. Apply a running prefix sum from left to right:
   - `arr[1] = arr[1] + arr[0]` -> `1 + 2 = 3` -> `[2, 3, 1]`
   - `arr[2] = arr[2] + arr[1]` -> `1 + 3 = 4` -> `[2, 3, 4]`
7. Final answer: `[2, 3, 4]`.
</details>

---

## ⚠️ Constraints

> - `1 ≤ n, updates.size() ≤ 10^5`[cite: 1]
> - `1 ≤ updates[i] ≤ n`[cite: 1]

---

## 💻 Solution Approach

**Brief Summary / Intuition:**
A naive approach would update all elements from index `j` to `n` for every update, which leads to $O(N \times K)$ time complexity resulting in Time Limit Exceeded (TLE). A highly optimized alternative uses the **Difference Array / Prefix Sum** technique. By incrementing only the starting boundary of the update, we can propagate the increments to all subsequent elements in a single sequential sweep using a prefix sum. 

### C++ Code

```cpp
// Intuition: Instead of iterating through the array for every update, we mark the start of the addition boundary and use a prefix sum to propagate the values forward in O(N) time.
// Approach: Initialize a zero array. Iterate over updates, decrementing the 1-based target to 0-based, and incrementing that start index. Finally, do a single pass to accumulate the prefix sums.
// Time Complexity: O(n + k) where n is the array size and k is the number of updates. We traverse the updates once and the array once.
// Space Complexity: O(1) auxiliary space, as the modifications are done directly in the required output array of size n.

class Solution {
  public:
    vector<int> update(int n, vector<int>& updates) {
        vector<int> arr(n, 0);

        // Mark the starting points for the prefix sum
        // updates[i] is 1-based, so subtract 1 for 0-based indexing
        for (int j : updates) {
            arr[j - 1]++;
        }

        // Calculate the prefix sum to propagate the additions
        for (int i = 1; i < n; i++) {
            arr[i] += arr[i - 1];
        }

        return arr;
    }
};

/*
*
* Dry Run
* Input: n = 3, updates = [1, 1, 2, 3]
* Initial arr: [0, 0, 0]
* Process update 1 (index 0): arr[0] becomes 1
* Process update 1 (index 0): arr[0] becomes 2
* Process update 2 (index 1): arr[1] becomes 1
* Process update 3 (index 2): arr[2] becomes 1
* State before prefix sum: arr = [2, 1, 1]
* Prefix sum step i=1: arr[1] += arr[0] => 1 + 2 = 3. arr = [2, 3, 1]
* Prefix sum step i=2: arr[2] += arr[1] => 1 + 3 = 4. arr = [2, 3, 4]
* Final result: [2, 3, 4]
*
*/
```
**

---

## 🧠 Key Insights
- **Difference Array Technique:** Whenever you need to perform multiple range addition queries, marking the boundaries (`start_index` gets `+val`, `end_index + 1` gets `-val`) is optimal. Since the problem asks to add `1` from index `j` to the *very end* of the array, there is no need to add a `-1` boundary. The prefix sum naturally carries the addition to the end.

---

## 🔍 Further Exploration
- Range Addition problems.
- Difference Array Data Structure.
- Prefix Sum variations in 1D and 2D arrays.

---

## 🔗 References
- **Original Problem:** [Adding Ones on GeeksforGeeks](https://www.geeksforgeeks.org/problems/adding-ones3628/1)[cite: 1]

---

## ✍️ Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
![Array](https://img.shields.io/badge/Array-Topic-blue?style=flat-square)
![Prefix Sum](https://img.shields.io/badge/Prefix_Sum-Topic-blue?style=flat-square)
![Difference Array](https://img.shields.io/badge/Difference_Array-Topic-blue?style=flat-square) 
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Platform-green?style=flat-square)
