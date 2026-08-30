# 📈 Marks from Ranks

[![GeeksforGeeks](https://img.shields.io/badge/View_on_GFG-09B958?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/find-marks-from-ranks/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge)](#)
[![Accuracy: 52.15%](https://img.shields.io/badge/Accuracy-52.15%25-brightgreen?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](#)

<div align="center">
⚠️ <b>Educational Use Only</b><br>
This repository and its content are intended solely for educational purposes.<br>
Solutions are provided for learning, practice, and reference only.<br>
Problem statement and test cases are based on the GeeksforGeeks problem.
</div>

---

## 📝 Problem Statement

Consider an input where all marks obtained are divided into intervals of consecutive numbers represented as `l[]` and `r[]` where `l[i]` and `r[i]` represent the starting and ending marks (inclusive) of the `i-th` interval. 

* The intervals are sorted in increasing order and do not overlap.
* The rank of a mark is defined by its position among all valid marks in increasing order, with the smallest mark assigned rank 1, the next smallest rank 2, and so on.

Given an array `rank[]`, for each value in `rank[]`, find the corresponding mark and return it as an array.

---

## 💡 Examples

### Example 1
```text
Input: l[] = [1, 6, 14], r[] = [3, 9, 15], rank[] = [2, 5, 8]
Output: [2, 7, 14]
Explanation: The valid marks are 1, 2, 3, 6, 7, 8, 9, 14, 15. Their corresponding ranks are 1 to 9 as there are 9 distinct marks. Therefore, rank 2 corresponds to mark 2, rank 5 corresponds to mark 7, and rank 8 corresponds to mark 14.
```

<details>
<summary>📖 <b>Example Breakdown</b> (Click to expand)</summary>

1. **Given Intervals:** `[1, 3]`, `[6, 9]`, `[14, 15]`
2. **Generating Valid Marks:** 
   * `[1, 3]` -> `1, 2, 3`
   * `[6, 9]` -> `6, 7, 8, 9`
   * `[14, 15]` -> `14, 15`
3. **Combined Ordered List:** `[1, 2, 3, 6, 7, 8, 9, 14, 15]`
4. **Evaluating Ranks:** 
   * `rank 2` -> 2nd item in list -> `2`
   * `rank 5` -> 5th item in list -> `7`
   * `rank 8` -> 8th item in list -> `14`

</details>

### Example 2
```text
Input: l[] = [5, 10], r[] = [7, 12], rank[] = [1, 4, 6]
Output: [5, 10, 12]
Explanation: The valid marks are 5, 6, 7, 10, 11, 12. Their corresponding ranks are 1 to 6 in increasing order. Hence, rank 1 corresponds to mark 5, rank 4 corresponds to mark 10, and rank 6 corresponds to mark 12.
```

---

## ⚠️ Constraints

> - `1 ≤ l.size(), l[i], r.size(), r[i], rank.size(), rank[i] ≤ 10^5`
> - Expected Time Complexity: $O(n + q \log n)$
> - Expected Auxiliary Space: $O(n)$

---

## 🛠️ Solution Approach

### Brute-Force / Simulation Approach

This approach solves the problem by literally interpreting the intervals and generating the entire list of valid marks in sequence. Since the intervals are guaranteed to be sorted and non-overlapping, flattening them sequentially produces a perfectly sorted array of all valid marks. 

```cpp
// Intuition: The intervals are already sorted and non-overlapping. If we expand all these intervals and store every single number in a list, the index of each number in the list directly corresponds to its rank (0-indexed).
// Approach:
// 1. Create a dynamic array `marks` to hold every valid mark.
// 2. Iterate through each interval range from `l[i]` to `r[i]`.
// 3. Push every integer within the current interval into the `marks` array.
// 4. Create a `result` array to map the query ranks.
// 5. Iterate through the `rank` queries and retrieve the mark at `marks[rank[i] - 1]`.
// Time Complexity: O(M + Q), where M is the total count of valid marks across all intervals, and Q is the number of rank queries. Expanding intervals takes time proportional to their size.
// Space Complexity: O(M) auxiliary space to store every valid mark in the `marks` vector.

class Solution {
  public:
    vector<int> getMarks(vector<int> &l, vector<int> &r, vector<int> &rank) {
        vector<int> marks; // Array to hold all expanded marks
        int n = l.size();
        
        // Traverse through each given interval boundary
        for(int i = 0; i < n; i++) {
            // Expand interval and store each number
            for(int j = l[i]; j <= r[i]; j++) {
                marks.push_back(j);
            }
        }
        
        vector<int> result; // Array for final query answers

        // Process each rank query and fetch by index
        for (int i = 0; i < rank.size(); i++) {
            result.push_back(marks[rank[i] - 1]); // Adjust for 0-based indexing
        }

        return result;
    }
};

/*
* Dry Run
* 
* Input: l = [5, 10], r = [7, 12], rank = [1, 4, 6]
* 
* Expanding Intervals:
* Interval [5, 7] adds 5, 6, 7 to the marks array
* Interval [10, 12] adds 10, 11, 12 to the marks array
* Current marks array state: [5, 6, 7, 10, 11, 12]
* 
* Processing Queries:
* rank 1 maps to index 0, extracting 5, result becomes [5]
* rank 4 maps to index 3, extracting 10, result becomes [5, 10]
* rank 6 maps to index 5, extracting 12, result becomes [5, 10, 12]
* 
* Final Output: [5, 10, 12]
*/
```

---

## 🧠 Key Insights
- **Simplicity vs. Scalability:** The current implementation is highly intuitive because it perfectly simulates the problem definition. However, if the interval ranges were massively large (e.g., $10^9$), this approach would lead to a Memory Limit Exceeded (MLE) error.
- **Optimization Strategy:** To meet the optimal $O(n + q \log n)$ time complexity, one should precompute the **prefix sums** of the number of elements available up to each interval. For any given rank query, a **Binary Search** can quickly locate which interval contains the requested rank, completely bypassing the need to generate individual elements. 

---

## 🔍 Further Exploration
- How would you modify the solution to handle overlapping or unsorted intervals? (Hint: Merge Intervals first).
- Try rewriting the code using `std::lower_bound` on a prefix-count array to achieve the strict $O(n + q \log n)$ time complexity requirement!

---

## 🔗 References
- **Original Problem:** [GeeksforGeeks - Marks from Ranks](https://www.geeksforgeeks.org/problems/find-marks-from-ranks/1)

---

## 👤 Author
- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`Array` `Searching` `Binary Search` `Prefix Sum` `GeeksforGeeks`