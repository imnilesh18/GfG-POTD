# 🟧 Two Pairs with Same Sum

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/satisfy-the-equation5847/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/satisfy-the-equation5847/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-50.31%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/satisfy-the-equation5847/1)
[![Points](https://img.shields.io/badge/Points-4-yellow?style=for-the-badge)](https://www.geeksforgeeks.org/problems/satisfy-the-equation5847/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:** This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Given an array `arr[]` of positive integers, find four indices `a`, `b`, `c`, and `d` such that:

$$\text{arr}[a] + \text{arr}[b] = \text{arr}[c] + \text{arr}[d]$$

where `a`, `b`, `c`, and `d` are **all distinct indices**.

* If multiple such quadruplets exist, return the one that is **lexicographically smallest** when the indices are considered in the order `a, b, c, d`.
* If no such quadruplet exists, return `{-1, -1, -1, -1}`.
* Ensure `a < b` and `c < d`, and the pair `(a, b)` is lexicographically smaller than the pair `(c, d)`.

---

## 🧪 Examples

### Example 1
```text
Input: arr[] = [3, 4, 7, 1, 2, 9, 8]
Output: [0, 2, 3, 5]
Explanation: arr[0] + arr[2] = 3 + 7 = 10, arr[3] + arr[5] = 1 + 9 = 10. 
This is the lexicographically smallest such quadruplet of indices.
```

### Example 2
```text
Input: arr[] = [1, 2, 3, 3]
Output: [-1, -1, -1, -1]
Explanation: No two distinct pairs of indices produce the same sum.
```

<details>
<summary>📖 <b>Example Breakdown (Example 1)</b></summary>

For `arr[] = [3, 4, 7, 1, 2, 9, 8]`, several disjoint pairs share the same sum:
1. **Sum = 5:** `(0, 4)` gives `3 + 2 = 5` and `(1, 3)` gives `4 + 1 = 5` $\rightarrow$ Quadruplet `[0, 4, 1, 3]`
2. **Sum = 10:** `(0, 2)` gives `3 + 7 = 10` and `(3, 5)` gives `1 + 9 = 10` $\rightarrow$ Quadruplet `[0, 2, 3, 5]`
3. **Sum = 11:** `(0, 6)` gives `3 + 8 = 11` and `(1, 2)` gives `4 + 7 = 11` $\rightarrow$ Quadruplet `[0, 6, 1, 2]`

Comparing the valid quadruplets lexicographically:
- `[0, 2, 3, 5] < [0, 4, 1, 3] < [0, 6, 1, 2]`

Hence, `[0, 2, 3, 5]` is the optimal answer.
</details>

---

## 🔒 Constraints

> * $4 \le \text{arr.size()} \le 10^3$
> * $1 \le \text{arr}[i] \le 10^7$
> * **Expected Time Complexity:** $\mathcal{O}(n^2)$
> * **Expected Auxiliary Space:** $\mathcal{O}(n^2)$

---

## 💡 Solution Approaches

### 🚀 Optimized Approach: Hashing Pair Sums

#### Intuition
A brute-force search over all 4-index combinations takes $\mathcal{O}(n^4)$ time, which exceeds time limits for $n \le 10^3$. Instead, we can generate all $\frac{n(n-1)}{2}$ pairs `(i, j)` with `i < j` in lexicographical order and store the **first** pair encountered for each sum in a hash map. Whenever the same sum appears again with four mutually distinct indices, we form a candidate quadruplet `{a, b, i, j}` and track the lexicographically smallest one.

#### C++ Implementation

```cpp
// Intuition: Two pairs with the same sum can be found in O(n^2) by hashing pair sums; iterating pairs in lexicographical order ensures the first pair stored for any sum is the smallest possible (a, b).
// Approach:
// 1. Create a hash map `firstPair` to store the first (lexicographically smallest) index pair {a, b} for each sum.
// 2. Iterate through all pairs (i, j) with i < j and compute `sum = arr[i] + arr[j]`.
// 3. If `sum` is unseen, record {i, j} in `firstPair`; otherwise, verify all four indices (a, b, i, j) are distinct.
// 4. Update `ans` whenever a valid quadruplet {a, b, i, j} is lexicographically smaller than the current best, and return `ans` (or {-1, -1, -1, -1} if none exists).
// Time Complexity: O(n^2) - We examine n*(n-1)/2 pairs, and each hash map operation and 4-element comparison runs in O(1) average time.
// Space Complexity: O(n^2) - In the worst case, all n*(n-1)/2 pairs produce unique sums stored in the hash map.

class Solution {
  public:
    vector<int> findPairs(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, pair<int, int>> firstPair; // Maps each sum to its earliest (smallest) index pair
        firstPair.reserve(n * n / 2); // Pre-allocate buckets to minimize hash collisions and rehashing

        vector<int> ans; // Stores the lexicographically smallest valid quadruplet

        // Generate all pairs (i, j) in increasing lexicographical order
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int sum = arr[i] + arr[j];

                auto it = firstPair.find(sum);
                if (it == firstPair.end()) {
                    // First time seeing this sum; store the smallest pair for it
                    firstPair[sum] = {i, j};
                } else {
                    auto [a, b] = it->second;
                    // Ensure all four indices are distinct so no array element is reused
                    if (a != i && a != j && b != i && b != j) {
                        vector<int> candidate = {a, b, i, j};
                        // Keep the lexicographically smallest quadruplet found so far
                        if (ans.empty() || candidate < ans) {
                            ans = candidate;
                        }
                    }
                }
            }
        }

        // Return {-1, -1, -1, -1} if no valid quadruplet exists
        return ans.empty() ? vector<int>{-1, -1, -1, -1} : ans;
    }
};

/*
Dry Run

Input: arr = [3, 4, 7, 1, 2, 9, 8]
n = 7, ans = []

i = 0, j = 1 -> sum = 3 + 4 = 7 -> stored firstPair[7] = {0, 1}
i = 0, j = 2 -> sum = 3 + 7 = 10 -> stored firstPair[10] = {0, 2}
i = 0, j = 3 -> sum = 3 + 1 = 4 -> stored firstPair[4] = {0, 3}
i = 0, j = 4 -> sum = 3 + 2 = 5 -> stored firstPair[5] = {0, 4}
i = 0, j = 5 -> sum = 3 + 9 = 12 -> stored firstPair[12] = {0, 5}
i = 0, j = 6 -> sum = 3 + 8 = 11 -> stored firstPair[11] = {0, 6}

i = 1, j = 2 -> sum = 4 + 7 = 11 -> found {0, 6}, distinct -> candidate = {0, 6, 1, 2} -> ans = {0, 6, 1, 2}
i = 1, j = 3 -> sum = 4 + 1 = 5 -> found {0, 4}, distinct -> candidate = {0, 4, 1, 3} -> ans = {0, 4, 1, 3}
i = 1, j = 4 -> sum = 4 + 2 = 6 -> stored firstPair[6] = {1, 4}
i = 1, j = 5 -> sum = 4 + 9 = 13 -> stored firstPair[13] = {1, 5}
i = 1, j = 6 -> sum = 4 + 8 = 12 -> found {0, 5}, distinct -> candidate = {0, 5, 1, 6} -> not smaller than ans

i = 2, j = 3 -> sum = 7 + 1 = 8 -> stored firstPair[8] = {2, 3}
i = 2, j = 4 -> sum = 7 + 2 = 9 -> stored firstPair[9] = {2, 4}
i = 2, j = 5 -> sum = 7 + 9 = 16 -> stored firstPair[16] = {2, 5}
i = 2, j = 6 -> sum = 7 + 8 = 15 -> stored firstPair[15] = {2, 6}

i = 3, j = 4 -> sum = 1 + 2 = 3 -> stored firstPair[3] = {3, 4}
i = 3, j = 5 -> sum = 1 + 9 = 10 -> found {0, 2}, distinct -> candidate = {0, 2, 3, 5} -> smaller than {0, 4, 1, 3} -> ans = {0, 2, 3, 5}
i = 3, j = 6 -> sum = 1 + 8 = 9 -> found {2, 4}, distinct -> candidate = {2, 4, 3, 6} -> not smaller than ans

i = 4, j = 5 -> sum = 2 + 9 = 11 -> found {0, 6}, distinct -> candidate = {0, 6, 4, 5} -> not smaller than ans
i = 4, j = 6 -> sum = 2 + 8 = 10 -> found {0, 2}, distinct -> candidate = {0, 2, 4, 6} -> not smaller than ans

i = 5, j = 6 -> sum = 9 + 8 = 17 -> stored firstPair[17] = {5, 6}

Output: [0, 2, 3, 5]
*/
```

---

## 🔑 Key Insights

1. **Lexicographical Ordering Guarantee:** Because `i` goes from `0` to `n - 1` and `j` goes from `i + 1` to `n - 1`, pairs are visited in strictly increasing lexicographical order. Storing only the *first* pair `(a, b)` for each sum ensures `(a, b)` is the smallest possible prefix for any quadruplet sharing that sum, and `(a, b) < (i, j)` always holds.
2. **Strict Distinctness Check:** Two pairs can have equal sums while sharing an index (e.g., `arr[0] + arr[2] == arr[0] + arr[4]` when `arr[2] == arr[4]`). Checking `a != i && a != j && b != i && b != j` guarantees four unique indices.
3. **Hash Map Pre-allocation:** Calling `firstPair.reserve(n * n / 2)` avoids dynamic rehashing overhead during insertion, keeping average lookup and insertion times fast.

---

## 🔍 Further Exploration

* [Four Elements (4Sum) - GeeksforGeeks](https://www.geeksforgeeks.org/problems/four-elements2452/1)
* [Find All Four Sum Numbers - GeeksforGeeks](https://www.geeksforgeeks.org/problems/find-all-four-sum-numbers1732/1)
* [Two Sum - Pair with Given Sum - GeeksforGeeks](https://www.geeksforgeeks.org/problems/key-pair5616/1)
* [Count Pairs with Given Sum - GeeksforGeeks](https://www.geeksforgeeks.org/problems/count-pairs-with-given-sum5022/1)

---

## 📚 References

* **Original Problem:** [Two Pairs with Same Sum | GeeksforGeeks](https://www.geeksforgeeks.org/problems/satisfy-the-equation5847/1)

---

## 👨‍💻 Author

* **Nilesh** — [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Hash](https://img.shields.io/badge/Topic-Hash-informational?style=flat-square)
![Sorting](https://img.shields.io/badge/Topic-Sorting-informational?style=flat-square)
![Map](https://img.shields.io/badge/Topic-Map-informational?style=flat-square)
![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B)
![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-298D46?style=flat-square&logo=geeksforgeeks)