# 🔢 Pairs with Less Than K Diff

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/pairs-with-difference-less-than-k1348/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-38.07%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

<br>

<div align="center">
  <b>⚠️ Educational Use Only:</b><br>
  <i>This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.</i>
</div>

---

## 📝 Problem Statement

Given an array `arr[]` of positive integers and an integer `k`, find the total number of pairs of elements that have an absolute difference strictly less than `k`[cite: 1].

> **Note:** Pair `(i, j)` is considered the same as `(j, i)`[cite: 1].

---

## 💡 Examples

```text
Input: arr[] = [1, 10, 4, 2], k = 3
Output: 2
Explanation: We have an array arr[] = [1, 10, 4, 2] and k = 3. We can make only two pairs with a difference of less than 3: (1, 2) and (4, 2). So, the answer is 2.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>

1. Array: `[1, 10, 4, 2]`, `k = 3`
2. Sorted Array: `[1, 2, 4, 10]`
3. Differences evaluating from left to right in a sliding window:
   - Elements `(1, 2)`: $|1 - 2| = 1$ (< 3) 🟢 Valid
   - Elements `(2, 4)`: $|2 - 4| = 2$ (< 3) 🟢 Valid
   - All other pair combinations either exceed or equal $k=3$. 
4. Total valid pairs found: $2$.
</details>

```text
Input: arr[] = [2, 3, 4], k = 5
Output: 3
Explanation: For the given array arr[] = [2, 3, 4] and k = 5, there are 3 valid pairs where the absolute difference between the pair's elements is less than 5. These pairs are (2, 3), (2, 4), and (3, 4). Hence, the output is 3.
```

---

## 🛑 Constraints

- $1 \le \text{arr.size()} \le 10^5$[cite: 1]
- $0 \le k \le 10^5$[cite: 1]
- $1 \le arr[i] \le 10^5$[cite: 1]

---

## 🚀 Solution Approaches

### 1️⃣ Brute-Force Approach (Time Limit Exceeded)
The most straightforward method is to iterate through all possible pairs $(i, j)$ and check if their absolute difference is strictly less than $k$.

```cpp
// Intuition: Check every possible pair combination in the array to see if the condition holds.
// Approach: 
// 1. Use two nested loops to generate all unique pairs (i, j) where j > i.
// 2. Check if the absolute difference |arr[j] - arr[i]| is less than k.
// 3. Increment the result counter if the condition evaluates to true.
// Time Complexity: O(n^2) - Iterates through all possible pairs in nested loops.
// Space Complexity: O(1) - No auxiliary data structures are used.

class Solution {
  public:
    int countPairs(vector<int> &arr, int k) {
        int res = 0;
        int n = arr.size();
    
        // Iterate through every possible pair
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
    
                // If the absolute difference is strictly less than k, count it
                if (abs(arr[j] - arr[i]) < k) {
                    res++;
                }
            }
        }
        return res;
    }
};

/*
*
* Dry Run
* Input: arr[] = [1, 10, 4, 2], k = 3
* i=0(1): j=1(10)->diff 9. j=2(4)->diff 3. j=3(2)->diff 1 (res=1)
* i=1(10): j=2(4)->diff 6. j=3(2)->diff 8.
* i=2(4): j=3(2)->diff 2 (res=2)
* Output: 2
*
*/
```

### 2️⃣ Optimized Approach: Sorting + Sliding Window
By sorting the array, we group closest elements together, eliminating the need for an $O(n^2)$ search. We can dynamically manage a sliding window that expands and shrinks to count valid pairs in linear time after sorting.

```cpp
// Intuition: Sorting ensures that elements are logically ordered, meaning differences naturally increase as indices move further apart. A sliding window can then be used to rapidly count valid pairs by measuring the window's span.
// Approach: 
// 1. Sort the array in non-decreasing order.
// 2. Initialize two pointers `i` (start) and `j` (end) to track a valid sliding window.
// 3. Expand the window by iterating `j`. 
// 4. Shrink the window from the left (increment `i`) if the difference `arr[j] - arr[i]` equals or exceeds `k`.
// 5. The total valid pairs forming a difference less than `k` ending at `j` is simply `j - i`. Add this to the total.
// Time Complexity: O(n log n) - The dominant operation is sorting. The sliding window traversal takes O(n).
// Space Complexity: O(1) - Constant auxiliary space (excluding C++ sort overhead).

class Solution {
  public:
    int countPairs(vector<int> &arr, int k) {
        int n = arr.size();

        // Sort the array in non-decreasing order
        sort(arr.begin(), arr.end());

        int total = 0;
        int i = 0;
        int j = 0;

        // Iterate with right pointer j expanding the window
        while (j < n) {
            // Shrink window from the left if the difference exceeds or equals k
            while (i < j && arr[j] - arr[i] >= k) {
                i++;
            }
            
            // Calculate result: all items in the window with j form a valid pair
            total += (j - i);
            
            j++;
        }

        return total;
    }
};

/*
*
* Dry Run
* Input: arr[] = [1, 10, 4, 2], k = 3
* Sorted arr[] = [1, 2, 4, 10]
* 
* Initialization: total = 0, i = 0, j = 0
* 
* j = 0: arr[0] = 1. arr[0] - arr[0] (0) < 3.
*        total += (0 - 0) => 0
* 
* j = 1: arr[1] = 2. arr[1] - arr[0] (1) < 3.
*        total += (1 - 0) => 1
* 
* j = 2: arr[2] = 4. arr[2] - arr[0] (3) >= 3.
*        Shrink: i = 1. arr[2] - arr[1] (2) < 3.
*        total += (2 - 1) => 1 + 1 = 2
* 
* j = 3: arr[3] = 10. arr[3] - arr[1] (8) >= 3.
*        Shrink: i = 2, then i = 3. arr[3] - arr[3] (0) < 3.
*        total += (3 - 3) => 2 + 0 = 2
* 
* Output: 2
*
*/
```

---

## 🧠 Key Insights

- **Sorting eliminates exhaustive checking:** When numbers are ordered, as soon as a pairing exceeds the limit $k$, all subsequent numbers paired with the same base will also exceed it.
- **Math Trick with Indices:** In a sorted, sliding sequence `[i ... j]`, if the extreme ends satisfy the difference threshold, then every element in between paired with $j$ will also satisfy it. Therefore, `j - i` immediately yields the valid pair count for that iteration.

---

## 🔍 Further Exploration

- **Related Topics/Problems:** 
  - Subarray with given sum
  - Count pairs with given sum
  - Two Pointers technique
- **Follow-up Question:** How would the logic change if the constraint required finding an absolute difference *equal* to $k$? *(Hint: You could utilize a Hash Map/Set for an $O(n)$ time complexity).*

---

## 🔗 References

- **GeeksforGeeks Problem Link:** [Pairs with Less Than K Diff](https://www.geeksforgeeks.org/problems/pairs-with-difference-less-than-k1348/1)[cite: 1]

---

## 🧑‍💻 Author

Made with ❤️ by [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<div align="left">
  <img src="https://img.shields.io/badge/Language-C++-00599C?style=flat-square&logo=c%2B%2B" alt="C++" />
  <img src="https://img.shields.io/badge/Algorithm-Two_Pointers-4CAF50?style=flat-square" alt="Two Pointers" />
  <img src="https://img.shields.io/badge/Algorithm-Sliding_Window-FF9800?style=flat-square" alt="Sliding Window" />
  <img src="https://img.shields.io/badge/Data_Structure-Array-673AB7?style=flat-square" alt="Array" />
</div>