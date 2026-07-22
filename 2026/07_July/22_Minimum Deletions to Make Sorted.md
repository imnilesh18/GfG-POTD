# 🧹 Minimum Deletions to Make Sorted

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Accuracy-49.53%25-blue?style=for-the-badge" alt="Accuracy: 49.53%" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points: 2" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]`, find the **minimum number of elements to delete** so that the remaining elements form a strictly increasing sequence in the same order.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [5, 6, 1, 7, 4]
Output: 2
Explanation: Removing 1 and 4 leaves [5, 6, 7] which is strictly increasing.
```

### Example 2
```text
Input: arr[] = [1, 1, 1]
Output: 2
Explanation: Removing any 2 elements leaves [1] which is strictly increasing.
```

<details>
<summary><b>📖 Example Breakdown (Example 1)</b></summary>
<br>

To make the array `[5, 6, 1, 7, 4]` strictly increasing with the *minimum* number of deletions, we should preserve the **Longest Increasing Subsequence (LIS)**. 

1. The increasing subsequences include: `[5, 6, 7]`, `[1, 7]`, `[1, 4]`, etc.
2. The longest one is `[5, 6, 7]`, which has a length of **3**.
3. The total number of elements in the array is **5**.
4. Minimum elements to delete = `Total Length - Length of LIS` = `5 - 3` = **2**.
5. We delete `1` and `4`.

</details>

---

## ⚠️ Constraints

> - $1 \le n \le 10^5$
> - $1 \le arr[i] \le 10^5$

---

## 🚀 Solution Approaches

### Optimized Approach (Binary Search)

**Brief Summary:**
The core realization is that the minimum number of deletions is equivalent to the total number of elements minus the length of the Longest Increasing Subsequence (LIS). To adhere to the strict time complexity constraint of $O(n \log n)$, we use the binary search algorithm (`std::lower_bound` in C++) to construct the LIS dynamically.

```cpp
// Intuition: To minimize deletions for a sorted sequence, we must maximize the elements kept. This is exactly the Longest Increasing Subsequence (LIS). The answer is simply Total Elements - LIS Length.
// Approach: 
// 1. We find the length of the LIS using a binary search approach to meet the O(n log n) time complexity constraint.
// 2. Maintain a 'temp' array that dynamically tracks the smallest tail of all strictly increasing subsequences.
// 3. Iterate through 'arr'. If the current element is strictly greater than the last element in 'temp', append it.
// 4. Otherwise, use lower_bound (binary search) to find the first element in 'temp' that is >= the current element, and replace it.
// 5. The final length of 'temp' represents the LIS length. Return arr.size() - temp.size().
// Time Complexity: O(n log n) - We traverse the array of size n, and for each element, lower_bound takes O(log n) time.
// Space Complexity: O(n) - In the worst-case scenario (e.g., an already sorted array), the 'temp' array will store all n elements.

class Solution {
  public:
    int minDeletions(vector<int>& arr) {
        int n = arr.size();
        vector<int> temp;
        
        for (int i = 0; i < n; i++) {
            // If temp is empty or arr[i] is greater than the largest element in temp
            if (temp.empty() || arr[i] > temp.back()) {
                temp.push_back(arr[i]);
            } else {
                // Find the first element in temp that is >= arr[i]
                auto it = lower_bound(temp.begin(), temp.end(), arr[i]);
                // Replace to maintain the smallest possible sequence tails
                *it = arr[i];
            }
        }
        
        // Minimum deletions = total size - maximum sorted elements we can keep
        return n - temp.size();
    }
};

/*
*
* Dry Run
* Input: arr[] = [5, 6, 1, 7, 4]
* n = 5, temp = []
* i = 0, arr[0] = 5: temp is empty -> temp = [5]
* i = 1, arr[1] = 6: 6 > 5 -> temp = [5, 6]
* i = 2, arr[2] = 1: 1 < 6 -> lower_bound of 1 is at index 0. Replace 5 with 1 -> temp = [1, 6]
* i = 3, arr[3] = 7: 7 > 6 -> temp = [1, 6, 7]
* i = 4, arr[4] = 4: 4 < 7 -> lower_bound of 4 is at index 1. Replace 6 with 4 -> temp = [1, 4, 7]
* Loop ends. temp.size() = 3 (This is the length of the LIS)
* Result: n - temp.size() = 5 - 3 = 2
* Output: 2
*
*/
```

---

## 🧠 Key Insights

* **Rephrasing the Problem:** Framing "minimum deletions for a sorted sequence" into "Total Elements - Longest Increasing Subsequence" is the breakthrough step.
* **Greedy + Binary Search:** Standard DP for LIS takes $O(n^2)$, which fails for $n = 10^5$. Using the `temp` array (or tails array) with binary search ensures optimal replacements, keeping the active tails as small as possible and letting us extend the sequence more easily.
* **Strictly Increasing:** The use of `lower_bound` instead of `upper_bound` ensures we are looking for strictly increasing sequences (ignoring duplicate values from expanding the LIS size).

---

## 🔍 Further Exploration

* [Longest Increasing Subsequence (GeeksforGeeks)](https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/)
* [Maximum Sum Increasing Subsequence](https://www.geeksforgeeks.org/maximum-sum-increasing-subsequence-dp-14/)
* [Russian Doll Envelopes (LeetCode)](https://leetcode.com/problems/russian-doll-envelopes/)

---

## 🔗 References

* **Original Problem:** [Minimum Deletions to Make Sorted (GFG)](https://www.geeksforgeeks.org/problems/minimum-number-of-deletions-to-make-a-sorted-sequence3248/1)
* **C++ STL:** [`std::lower_bound` Documentation](https://en.cppreference.com/w/cpp/algorithm/lower_bound)

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`dynamic-programming` | `binary-search` | `longest-increasing-subsequence` | `array` | `geeksforgeeks`