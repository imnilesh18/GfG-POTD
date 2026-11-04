# 🟧 XOR of All Subarray XORs

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-50.77%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an integer array `arr[]`, find the XOR of the XOR values of all possible non-empty subarrays of the array.

## 🚀 Examples

### Example 1
```text
Input: arr[] = [1, 2, 3] 
Output: 2
```
<details>
<summary><b>📖 Example Breakdown</b></summary>
<br>

All possible subarrays and their XOR values:
* `[1]` = 1
* `[1, 2]` = 3
* `[2, 3]` = 1
* `[1, 2, 3]` = 0
* `[2]` = 2
* `[3]` = 3

**Result:** `1 ^ 3 ^ 1 ^ 0 ^ 2 ^ 3 = 2`
</details>

### Example 2
```text
Input: arr[] = [1, 2]
Output: 0
```
<details>
<summary><b>📖 Example Breakdown</b></summary>
<br>

All possible subarrays and their XOR values:
* `[1]` = 1
* `[1, 2]` = 3
* `[2]` = 2

**Result:** `1 ^ 3 ^ 2 = 0`
</details>

---

## ⚠️ Constraints

> - `1 ≤ arr.size() ≤ 10^5`
> - `0 ≤ arr[i] ≤ 10^9`

---

## 💡 Solution Approaches

### Optimized Mathematical Approach (C++)

**Intuition:** 
By analyzing the frequency of each element in all possible subarrays, we observe a pattern. An element at index `i` (0-indexed) appears exactly `(i + 1) * (n - i)` times. If the total number of elements `n` is even, every element will appear an even number of times across all subarrays, resulting in a total XOR of 0. If `n` is odd, elements at even indices will appear an odd number of times, and elements at odd indices will appear an even number of times.

```cpp
// Intuition: Each element at index i appears (i + 1) * (n - i) times in all subarrays. Since XORing a number with itself an even number of times gives 0, we only care about elements that appear an odd number of times. If n is even, all elements appear an even number of times. If n is odd, only elements at even indices appear an odd number of times.
// Approach: First, check if the size of the array `n` is even; if so, return 0. If `n` is odd, iterate through the array taking steps of 2 (i.e., only even indices 0, 2, 4...) and compute the cumulative XOR of these elements.
// Time Complexity: O(n) - We iterate through at most half of the elements in the array.
// Space Complexity: O(1) - No auxiliary space is used; we only maintain a few integer variables.

class Solution {
  public:
    int subarrayXor(vector<int>& arr) {
        int n = arr.size();

        // If the array size is even, the frequency of every element in all 
        // possible subarrays will be even, resulting in an overall XOR of 0.
        if (n % 2 == 0) {
            return 0;
        }

        int res = 0;
        // If the array size is odd, only elements at even indices (0, 2, 4, ...)
        // will appear an odd number of times across all subarrays.
        for (int i = 0; i < n; i += 2) {
            res ^= arr[i];
        }

        return res;
    }
};

/*
*
* Dry Run
* Input: arr[] = [1, 2, 3], n = 3
* Condition check: n % 2 == 0 -> 3 % 2 != 0 (Array length is odd, continue)
* Initialize res = 0
* Iteration 1 (i = 0): res = 0 ^ arr[0] = 0 ^ 1 = 1
* Iteration 2 (i = 2): res = 1 ^ arr[2] = 1 ^ 3 = 2
* Loop terminates as i + 2 = 4 >= n
* Return res = 2
* Output: 2
*
*/
```

---

## 🧠 Key Insights

* **Frequency Counting Trick:** Instead of generating all subarrays (which would take `O(n^2)` or `O(n^3)` time), identifying how many times each element appears in the final equation reduces the problem to `O(n)`.
* **XOR Properties:** The most crucial property utilized here is `A ^ A = 0` (even frequency cancels out) and `A ^ 0 = A` (odd frequency leaves the element intact).

---

## 🔍 Further Exploration
- [XOR of all elements in an array](https://www.geeksforgeeks.org/find-xor-of-all-elements-in-an-array/)
- [Find the single element in an array where every other element appears twice](https://leetcode.com/problems/single-number/)
- Subarray mathematical combinatorial logic

---

## 🔗 References
* **GeeksforGeeks Problem:** [Game of XOR](https://www.geeksforgeeks.org/problems/game-of-xor1541/1)

---

## 👨‍💻 Author

**Nilesh Kumar**
* GitHub: [@imnilesh18](https://github.com/imnilesh18)
* LeetCode: [@imnilesh18](https://leetcode.com/u/imnilesh18/)

---

## 🏷️ Tags

`[Mathematics]` `[Bit Magic]` `[GeeksforGeeks]` `[Arrays]` `[C++]`