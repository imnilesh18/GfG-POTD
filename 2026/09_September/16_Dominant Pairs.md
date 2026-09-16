# 🟩 Dominant Pairs

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-008A00?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-50.57%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an **even-sized** integer array `arr[]`, count the total number of **dominant pairs**.

A pair of indices `(i, j)` is defined as **dominant** if all of the following conditions are satisfied:
1. `0 ≤ i < arr.size() / 2` *(Index `i` belongs to the first half)*
2. `arr.size() / 2 ≤ j < arr.size()` *(Index `j` belongs to the second half)*
3. `arr[i] ≥ 5 × arr[j]` *(Dominance condition)*

Return the total count of such valid dominant pairs.

> **Note:** 0-based indexing is used.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [10, 2, 2, 1]
Output: 2
Explanation:
- First half: [10, 2] (indices 0 to 1)
- Second half: [2, 1] (indices 2 to 3)

Valid Dominant Pairs:
1. Pair {0, 2}: arr[0] = 10, arr[2] = 2 -> 10 >= 5 * 2 (10 >= 10) [Valid]
2. Pair {0, 3}: arr[0] = 10, arr[3] = 1 -> 10 >= 5 * 1 (10 >= 5)  [Valid]
```

### Example 2
```text
Input: arr[] = [10, 8, 2, 1, 1, 2]
Output: 5
Explanation:
- First half: [10, 8, 2] (indices 0 to 2)
- Second half: [1, 1, 2] (indices 3 to 5)

Valid Dominant Pairs:
1. Pair {0, 3}: arr[0] = 10, arr[3] = 1 -> 10 >= 5 * 1 (10 >= 5)  [Valid]
2. Pair {0, 4}: arr[0] = 10, arr[4] = 1 -> 10 >= 5 * 1 (10 >= 5)  [Valid]
3. Pair {0, 5}: arr[0] = 10, arr[5] = 2 -> 10 >= 5 * 2 (10 >= 10) [Valid]
4. Pair {1, 3}: arr[1] = 8,  arr[3] = 1 -> 8 >= 5 * 1  (8 >= 5)   [Valid]
5. Pair {1, 4}: arr[1] = 8,  arr[4] = 1 -> 8 >= 5 * 1  (8 >= 5)   [Valid]
```

<details>
<summary>📖 <b>Example Breakdown (Detailed Walkthrough)</b></summary>
<br>

Consider `arr[] = [10, 8, 2, 1, 1, 2]`:

- Array length `n = 6`, mid-point `n / 2 = 3`.
- Split into:
  - **Left Half:** `[10, 8, 2]`
  - **Right Half:** `[1, 1, 2]`
- After sorting both halves individually:
  - **Sorted Left Half:** `[2, 8, 10]`
  - **Sorted Right Half:** `[1, 1, 2]`
- For `arr[left] = 2`: No element in the right half satisfies `2 >= 5 * arr[right]`. Count added = 0.
- For `arr[left] = 8`: Right half elements `1` and `1` satisfy `8 >= 5 * 1`. Count added = 2.
- For `arr[left] = 10`: Right half elements `1`, `1`, and `2` satisfy `10 >= 5 * arr[right]`. Count added = 3.
- Total valid pairs = `0 + 2 + 3 = 5`.
</details>

---

## ⚙️ Constraints

> - $1 \le \text{arr.size()} \le 10^4$
> - $-10^4 \le \text{arr}[i] \le 10^4$
> - $\text{arr.size()}$ is guaranteed to be **even**.
> - Sum of $\text{arr.size()}$ across all test cases will not exceed $10^6$.

---

## 🚀 Solution Approach

### Two-Pointer Algorithm with Half-Sorting

**Intuition:**
Instead of checking all pairs in $O(n^2)$ time, we can sort the first half and second half of the array independently. Because relative ordering within each half does not affect pair validity between the halves, sorting enables a monotonic search. As the value in the sorted left half increases, the number of valid target elements in the sorted right half non-decreases, allowing an efficient $O(n \log n)$ two-pointer scan.

```cpp
// Intuition: Sorting both halves independently allows using a two-pointer approach, as increasing left-half elements monotonically expands the valid window in the sorted right half.
// Approach: Sort the first half [0, n/2) and second half [n/2, n) in non-decreasing order. Iterate through the left half with a pointer `left` and maintain a pointer `right` in the right half, incrementing `right` while arr[left] >= 5 * arr[right]. Accumulate the count of valid elements for each left index.
// Time Complexity: O(n log n) - O(n log n) to sort both halves of size n/2, and O(n) for the two-pointer traversal.
// Space Complexity: O(1) auxiliary space (excluding standard sorting stack frame space).

class Solution {
  public:
    int dominantPairs(vector<int> &arr) {
        int n = arr.size();

        // Sort the first half in ascending order
        sort(arr.begin(), arr.begin() + n / 2);

        // Sort the second half in ascending order
        sort(arr.begin() + n / 2, arr.end());

        int count = 0;
        int right = n / 2;

        // Iterate through the first half of the array
        for (int left = 0; left < n / 2; left++) {

            // Move right pointer while dominance condition holds
            while (right < n && arr[left] >= 5 * arr[right]) {
                right++;
            }

            // Count dominant pairs
            count += (right - n / 2);
        }

        return count;
    }
};

/*
* Dry Run
* 
* Input: arr = [10, 8, 2, 1, 1, 2]
* n = 6, n / 2 = 3
* 
* Step 1: Sort halves
* First half before: [10, 8, 2] -> sorted: [2, 8, 10]
* Second half before: [1, 1, 2] -> sorted: [1, 1, 2]
* Modified arr = [2, 8, 10, 1, 1, 2]
* 
* Step 2: Initialize count = 0, right = 3
* 
* Iteration left = 0 (arr[left] = 2):
* Check right = 3 (arr[3] = 1): 2 >= 5 * 1 (2 >= 5) is False. Loop terminates.
* Valid elements count added: (right - n/2) = (3 - 3) = 0
* Current count = 0
* 
* Iteration left = 1 (arr[left] = 8):
* Check right = 3 (arr[3] = 1): 8 >= 5 * 1 (8 >= 5) is True -> right = 4
* Check right = 4 (arr[4] = 1): 8 >= 5 * 1 (8 >= 5) is True -> right = 5
* Check right = 5 (arr[5] = 2): 8 >= 5 * 2 (8 >= 10) is False. Loop terminates.
* Valid elements count added: (right - n/2) = (5 - 3) = 2
* Current count = 0 + 2 = 2
* 
* Iteration left = 2 (arr[left] = 10):
* Check right = 5 (arr[5] = 2): 10 >= 5 * 2 (10 >= 10) is True -> right = 6
* Check right = 6: Out of bounds (right < n is False). Loop terminates.
* Valid elements count added: (right - n/2) = (6 - 3) = 3
* Current count = 2 + 3 = 5
* 
* Return Output: 5
*/
```

---

## 🔑 Key Insights

* **Independence of Halves:** The condition requires $i < n/2$ and $j \ge n/2$. Since indices $i$ and $j$ come from disjoint fixed halves, rearranging elements within the first half or within the second half does not alter which pairs $(i, j)$ cross the midpoint boundary.
* **Monotonic Two-Pointer Window:** Once both halves are sorted in ascending order, if $arr[left] \ge 5 \times arr[right]$, then any element larger than $arr[left]$ (further right in the left half) will also satisfy the condition for that same $arr[right]$. Thus, the `right` pointer never needs to reset backwards.

---

## 🔗 Further Exploration

- [Count Inversions in an Array](https://www.geeksforgeeks.org/problems/inversion-of-array-1587115620/1)
- [Reverse Pairs (LeetCode 493)](https://leetcode.com/problems/reverse-pairs/)
- [Two Sum - Pair with Given Sum](https://www.geeksforgeeks.org/problems/two-sum-pairs-with-given-sum/1)

---

## 📚 References

- **GeeksforGeeks Problem Link:** [Dominant Pairs](https://www.geeksforgeeks.org/problems/dominant-pairs/1)
- **C++ Standard Library:** `std::sort` documentation

---

## 👤 Author

Created and maintained by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags

![Two Pointer](https://img.shields.io/badge/Tag-Two--Pointer-blue?style=flat-square)
![Sorting](https://img.shields.io/badge/Tag-Sorting-orange?style=flat-square)
![Arrays](https://img.shields.io/badge/Tag-Arrays-purple?style=flat-square)
![C++](https://img.shields.io/badge/Tag-C%2B%2B-00599C?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/Tag-GeeksforGeeks-008A00?style=flat-square)
