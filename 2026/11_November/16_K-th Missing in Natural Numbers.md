# 🟧 K-th Missing in Natural Numbers

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/k-th-missing-element-in-natural-numbers/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/k-th-missing-element-in-natural-numbers/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-74.76%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/k-th-missing-element-in-natural-numbers/1)
[![Points](https://img.shields.io/badge/Points-4-informational?style=for-the-badge)](https://www.geeksforgeeks.org/problems/k-th-missing-element-in-natural-numbers/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**  
> This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Given an array `arr[]` of distinct positive integers and a positive integer `k`[cite: 1]. Consider an infinite sequence of natural numbers starting from `1` (`1, 2, 3, 4, ...`)[cite: 1]. The task is to remove all elements present in `arr[]` from this sequence and find the **k-th smallest number** in the remaining sequence[cite: 1].

> 💡 **Note:** Your solution must run in **$O(1)$ auxiliary space**[cite: 1].

---

## 🧪 Examples

### Example 1
```text
Input: arr[] = [1, 9, 5, 2], k = 6
Output: 10
Explanation: After removing [1, 2, 5, 9] from the natural numbers, the remaining sequence is: 3, 4, 6, 7, 8, 10, 11, .... and so on. The 6th number in this sequence is 10, so the answer is 10.
```
[cite: 1]

### Example 2
```text
Input: arr[] = [1, 2, 3, 4], k = 1
Output: 5
Explanation: After removing [1, 2, 3, 4] from the natural numbers, the remaining sequence is: 5, 6, 7, .... and so on. The 1st number in the sequence is 5, so the answer is 5.
```
[cite: 1]

<details>
<summary><b>📖 Example Breakdown (Walkthrough of Example 1)</b></summary>

Let's trace `arr[] = [1, 9, 5, 2]` and `k = 6`[cite: 1]:

1. **Initial Assumption:** If no numbers were removed from the natural numbers `1, 2, 3, 4, 5, 6, ...`, the `6`-th smallest number would simply be `k = 6`.
2. **Sort the Removed Elements:** Sorting `arr[]` gives `[1, 2, 5, 9]`. Processing elements in ascending order ensures we account for smaller removals before larger ones.
3. **Shift `k` for Each Relevant Removal:**
   - **`num = 1`:** Since `1 <= 6`, removing `1` pushes the `6`-th remaining element one position to the right. So `k` becomes `6 + 1 = 7`.
   - **`num = 2`:** Since `2 <= 7`, removing `2` pushes our target one more step forward. So `k` becomes `7 + 1 = 8`.
   - **`num = 5`:** Since `5 <= 8`, removing `5` again shifts our target forward. So `k` becomes `8 + 1 = 9`.
   - **`num = 9`:** Since `9 <= 9`, removing `9` takes up the `9`-th spot itself, pushing our target to `9 + 1 = 10`.
4. **Final Result:** All elements in `arr[]` have been processed, leaving `k = 10` as the exact 6th missing natural number[cite: 1].

</details>

---

## 🔒 Constraints

> - $1 \le \text{arr.size()} \le 10^5$[cite: 1]
> - $1 \le \text{arr}[i], k \le 10^6$[cite: 1]
> - All elements of `arr` are distinct[cite: 1].

**Expected Complexities:**
- **Time Complexity:** $O(n \log n)$[cite: 1]
- **Auxiliary Space:** $O(1)$[cite: 1]

---

## 💡 Solution Approach

### Optimized Approach: In-Place Sorting & Target Shifting

#### 🧠 Intuition
In an untouched sequence of natural numbers `1, 2, 3, ...`, the `k`-th smallest number is simply `k`. Every time we remove a distinct number `num` that is less than or equal to our current candidate `k`, that slot is vacated, shifting the `k`-th available number up by `1` (`k++`). By sorting `arr[]` first, we process removals from smallest to largest and stop immediately once `num > k`, because numbers larger than `k` cannot displace the `k`-th smallest element.

#### 🛠️ C++ Implementation

```cpp
// Intuition: Start with k as the initial answer; every distinct removed element <= k shifts the k-th remaining number forward by 1.
// Approach: Sort the array in ascending order, iterate through each element, increment k while num <= k, and break early once num > k.
// Time Complexity: O(n log n) due to sorting the array of size n, followed by a linear O(n) scan.
// Space Complexity: O(1) auxiliary space since sorting is performed in-place without extra data structures.

class Solution {
  public:
    int findKthSmall(vector<int>& arr, int k) {
        // Sort the array to evaluate removed numbers in increasing order
        sort(arr.begin(), arr.end());
        
        for (int num : arr) {
            // If the removed number is <= current target k, shift k forward
            if (num <= k) {
                k++;
            } else {
                // Larger numbers lie beyond k and do not affect the k-th smallest
                break;
            }
        }
        
        // Return the final shifted k-th smallest missing natural number
        return k;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 9, 5, 2], k = 6
 *
 * After sorting: arr = [1, 2, 5, 9]
 *
 * Iteration 1: num = 1, since 1 <= 6 is true, k increments to 7
 * Iteration 2: num = 2, since 2 <= 7 is true, k increments to 8
 * Iteration 3: num = 5, since 5 <= 8 is true, k increments to 9
 * Iteration 4: num = 9, since 9 <= 9 is true, k increments to 10
 *
 * Loop terminates as all elements are processed.
 *
 * Output: 10
 *
 */
```

---

## 🔑 Key Insights

- **Why Sorting Is Essential:** If `arr[]` is unsorted (e.g., `[9, 1]`, `k = 1`), checking `9 <= 1` first would prematurely terminate the loop and miss `1`, which actually shifts `k` from `1` to `2`.
- **Distinctness Guarantee:** Because all elements in `arr[]` are guaranteed to be distinct, each `num <= k` removes a unique value from `[1, k]`, ensuring `k` never double-counts a removal.
- **Early Termination:** Once `num > k`, every subsequent element in the sorted array will also be strictly greater than `k`, allowing an immediate `break`.
- **Zero Extra Memory:** Unlike hash-set or boolean-lookup approaches that require $O(n)$ or $O(\max(\text{arr}))$ space, sorting in-place strictly honors the $O(1)$ auxiliary space constraint[cite: 1].

---

## 🚀 Further Exploration

- [Kth Missing Positive Number in a Sorted Array](https://www.geeksforgeeks.org/problems/kth-missing-positive-number-in-a-sorted-array/1) — Can you solve this in $O(\log n)$ time using Binary Search when the input array is already sorted?
- [Smallest Positive Missing](https://www.geeksforgeeks.org/problems/smallest-positive-missing-number-1587115621/1) — Find the first missing positive integer in $O(n)$ time and $O(1)$ space.
- [Missing Element of AP](https://www.geeksforgeeks.org/problems/missing-element-of-ap2228/1) — Practice finding missing values using mathematical progression properties.

---

## 📚 References

- **Original Problem:** [GeeksforGeeks — K-th Missing in Natural Numbers](https://www.geeksforgeeks.org/problems/k-th-missing-element-in-natural-numbers/1)[cite: 1]
- **C++ STL Documentation:** [`std::sort` — cppreference.com](https://en.cppreference.com/w/cpp/algorithm/sort)

---

## 👨‍💻 Author

- **Nilesh Kumar** — [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Arrays](https://img.shields.io/badge/Topic-Arrays-blue?style=flat-square)
![Sorting](https://img.shields.io/badge/Topic-Sorting-green?style=flat-square)
![Algorithms](https://img.shields.io/badge/Category-Algorithms-purple?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-298D46?style=flat-square)