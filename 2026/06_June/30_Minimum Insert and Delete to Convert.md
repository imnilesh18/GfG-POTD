# 🎯 Minimum Insertions to Make Two Arrays Equal

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white) ![Difficulty: Hard](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge) ![Accuracy: 27.85%](https://img.shields.io/badge/Accuracy-27.85%25-blue?style=for-the-badge) ![Points: 8](https://img.shields.io/badge/Points-8-blue?style=for-the-badge) ![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. 
Solutions are provided for learning, practice, and reference only. 
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two arrays `a[]` and `b[]` of size `n` and `m` respectively, find the **minimum number of insertions and deletions** on the array `a[]`, required to make both the arrays identical.

**Note**: Array `b[]` is sorted and all its elements are distinct. Operations can be performed at any index, not necessarily at the end.

---

## 💡 Examples

```text
Input: a[] = [1, 2, 5, 3, 1], b[] = [1, 3, 5]
Output: 4
```

<details>
<summary>📖 Example Breakdown</summary>

1. **Delete `2`** from `a`: `a[] = [1, 5, 3, 1]`
2. **Insert `3`** after `1`: `a[] = [1, 3, 5, 3, 1]`
3. **Delete the last two elements** (`3`, `1`): `a[] = [1, 3, 5]`

Both arrays are now identical. 
Total operations = 1 deletion + 1 insertion + 2 deletions = **4 operations**.
</details>

```text
Input: a[] = [1, 4], b[] = [1, 4]
Output: 0
Explanation: Both the Arrays are already identical.
```

---

## ⚙️ Constraints

> * `1 ≤ n, m ≤ 10^5`
> * `1 ≤ a[i], b[i] ≤ 10^5`

**Expected Complexities:**
* **Time Complexity:** O(N log N)
* **Auxiliary Space:** O(N)

---

## 🧠 Solution Approaches

### Optimized Approach (Using LIS)
**Intuition:** 
Since array `b[]` is sorted and has entirely distinct elements, finding the Longest Common Subsequence (LCS) between `a[]` and `b[]` mathematically reduces to finding the Longest Increasing Subsequence (LIS) of elements in `a[]` that also exist in `b[]`. Any element not in this LIS must be deleted from `a[]`, and any missing element from `b[]` must be inserted. 

```cpp
// Intuition: Since array 'b' is sorted and has distinct elements, finding the Longest Common Subsequence (LCS) between 'a' and 'b' is equivalent to finding the Longest Increasing Subsequence (LIS) of elements in 'a' that are also present in 'b'.
// Approach:
// 1. Iterate through array 'a' and filter elements that exist in 'b' using binary search.
// 2. Compute the length of the LIS for these filtered elements to find the longest matching sequence.
// 3. The minimum operations required will be (a.size() - LIS) deletions + (b.size() - LIS) insertions.
// Time Complexity: O(n log n + n log m) where n is size of 'a' and m is size of 'b'. Binary search takes O(log m) and lower_bound takes O(log n).
// Space Complexity: O(n) to store the LIS sequence dynamically in the worst case.

class Solution {
  public:
    int minInsAndDel(vector<int> &a, vector<int> &b) {
        vector<int> lis;
        
        // Iterate over elements of 'a'
        for (int x : a) {
            // Check if 'x' exists in 'b'
            if (binary_search(b.begin(), b.end(), x)) {
                
                // Find the first element in lis >= x
                auto it = lower_bound(lis.begin(), lis.end(), x);
                
                // If x is greater than all elements, append it
                if (it == lis.end()) {
                    lis.push_back(x);
                } 
                // Otherwise, replace to maintain the smallest possible tail
                else {
                    *it = x;
                }
            }
        }
        
        int n = a.size();
        int m = b.size();
        
        // Operations = (n - LIS) deletions + (m - LIS) insertions
        return n + m - 2 * lis.size();
    }
};

/*
*
* Dry Run
* Input: a = [1, 2, 5, 3, 1], b = [1, 3, 5]
* n = 5, m = 3
* 
* Processing 'a':
* x = 1: exists in b -> lis = [1]
* x = 2: does not exist in b -> ignored
* x = 5: exists in b -> lis = [1, 5]
* x = 3: exists in b -> replaces 5 -> lis = [1, 3]
* x = 1: exists in b -> replaces 1 -> lis = [1, 3]
* 
* Final LIS size = 2
* Result = 5 + 3 - (2 * 2) = 8 - 4 = 4
*
*/
```

---

## 🔑 Key Insights

* **Transforming LCS to LIS:** The traditional LCS approach takes O(N * M) time, which will result in a Time Limit Exceeded (TLE) error for constraints up to `10^5`. Because `b[]` is sorted with distinct elements, any common subsequence is strictly increasing. This allows us to map the problem entirely to finding the LIS in O(N log N) time.
* **`std::binary_search` & `std::lower_bound`:** Using `binary_search` allows us to filter out useless elements in `O(log M)` time. `lower_bound` efficiently builds the LIS array by tracking the smallest possible tail elements in `O(log N)` time.

---

## 🔍 Further Exploration

* Longest Common Subsequence (LCS)
* Longest Increasing Subsequence (LIS)
* Minimum number of deletions and insertions to transform one string into another

---

## 🔗 References

* **GeeksforGeeks Problem:** [Minimum Insertions to Make Two Arrays Equal](https://www.geeksforgeeks.org/problems/minimum-insertions-to-make-two-arrays-equal/1)
* **C++ Algorithm Library:** [`std::lower_bound`](https://en.cppreference.com/w/cpp/algorithm/lower_bound)

---

## 👨‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Arrays` `Hash` `Dynamic Programming` `Data Structures` `Algorithms` `Binary Search` `GeeksforGeeks`