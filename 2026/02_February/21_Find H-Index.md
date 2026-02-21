# 🟧 Find H-Index

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/find-h-index--165609/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-53.4%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge" alt="License: MIT" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.

---

## 📝 Problem Statement

You are given an array `citations[]`, where each element `citations[i]` represents the number of citations received by the $i^{th}$ paper of a researcher. You have to calculate the researcher’s **H-index**.

The **H-index** is defined as the maximum value $H$, such that the researcher has published at least $H$ papers, and all those papers have citation value greater than or equal to $H$.

---

## 💡 Examples

### Example 1

```text
Input: citations[] = [3, 0, 5, 3, 0]
Output: 3
Explanation: There are at least 3 papers with citation counts of 3, 5, and 3, all having citations greater than or equal to 3.
```

### Example 2

```text
Input: citations[] = [5, 1, 2, 4, 1]
Output: 2
Explanation: There are 3 papers (with citation counts of 5, 2, and 4) that have 2 or more citations. However, the H-Index cannot be 3 because there aren't 3 papers with 3 or more citations.
```

### Example 3

```text
Input: citations[] = [0, 0]
Output: 0
Explanation: The H-index is 0 because there are no papers with at least 1 citation.
```

<details>
<summary>📖 <b>Example Breakdown (Example 2)</b></summary>

Given `citations[] = [5, 1, 2, 4, 1]`

1. **Sort the array:** `[1, 1, 2, 4, 5]` (Total papers $n = 5$)
2. **Binary Search Initialization:** `low = 0`, `high = 4`, `hIndex = 0`
3. **Iteration 1:**
   * `mid = (0 + 4) / 2 = 2`
   * Number of papers with $\ge$ `citations[mid]` citations is $h = 5 - 2 = 3$.
   * `citations[2] = 2`. Is $2 \ge 3$? **No**. So we need to look for papers with higher citations (move `low = mid + 1 = 3`).
4. **Iteration 2:**
   * `mid = (3 + 4) / 2 = 3`
   * Number of papers with $\ge$ `citations[mid]` citations is $h = 5 - 3 = 2$.
   * `citations[3] = 4`. Is $4 \ge 2$? **Yes**.
   * Valid! Update `hIndex = 2`. Try to find a larger validity range by moving `high = mid - 1 = 2`.
5. **End Condition:** `low (3) > high (2)`. Search terminates.
6. **Result:** `2`

</details>

---

## ⚠️ Constraints

> - $1 \le \text{citations.size()} \le 10^6$
> - $0 \le \text{citations}[i] \le 10$

---

## 🛠️ Solution Approach

### Optimized Binary Search Approach

```cpp
// Intuition: By sorting the array, we can definitively determine how many papers have at least X citations based on their index. Binary search allows us to find the maximum valid H-Index efficiently.
// Approach: 
// 1. Sort the citations array in ascending order.
// 2. Use binary search on the indices of the array. Let `mid` be the current index.
// 3. The number of papers with at least `citations[mid]` citations is `h = n - mid`.
// 4. If `citations[mid] >= h`, then `h` is a valid H-Index. We record it and search left (lower indices, larger `h`) to see if a strictly higher H-Index is possible.
// 5. Otherwise, the citation count is too low for the remaining number of papers, so search right (higher indices).
// Time Complexity: O(n log n) due to sorting, followed by O(log n) for binary search.
// Space Complexity: O(1) assuming in-place sorting and no auxiliary space used.

class Solution {
public:
    // Function to find H-Index using Binary Search
    int hIndex(vector<int>& citations){
        int n = citations.size();   // Get total number of papers

        // Sort the citations array in ascending order
        sort(citations.begin(), citations.end());

        // Initialize binary search boundaries
        int low = 0, high = n - 1, hIndex = 0;

        // Perform binary search
        while (low <= high) {
            // Calculate the middle index
            int mid = low + (high - low) / 2;

            // h is the potential H-Index, determined by the number of papers
            // that exist from index 'mid' to the end of the array
            int h = n - mid;

            // Check if citations[mid] satisfies the H-Index condition
            if (citations[mid] >= h) {
                // If valid, update the H-Index and search the left half 
                // for a potentially higher H-Index value
                hIndex = h;
                high   = mid - 1;   
            } else {
                // Otherwise, search the right half for a higher citation count
                low = mid + 1;
            }
        }

        return hIndex;   // Return the maximum H-Index found
    }
};

/*
*
* Dry Run
* Input: citations = [3, 0, 5, 3, 0]
* Sorted: [0, 0, 3, 3, 5], n = 5
*
* Step 1: low = 0, high = 4. 
* mid = 2, citations[2] = 3. 
* h = 5 - 2 = 3. 
* Is 3 >= 3? Yes. hIndex = 3, high = 1.
* Step 2: low = 0, high = 1.
* mid = 0, citations[0] = 0.
* h = 5 - 0 = 5.
* Is 0 >= 5? No. low = 1.
* Step 3: low = 1, high = 1.
* mid = 1, citations[1] = 0.
* h = 5 - 1 = 4.
* Is 0 >= 4? No. low = 2.
*
* Loop ends (low = 2 > high = 1).
* Output: 3
*
*/
```

---

## 🧠 Key Insights
- **Sorting is Key:** Once the array is sorted, the relationship between an index and the number of elements remaining becomes linear. For any index `i`, exactly `n - i` elements are greater than or equal to `citations[i]`.
- **Binary Search Optimization:** Instead of checking every possible index from `0` to `n-1` (which would take $O(N)$ after sorting), Binary Search finds the optimal intersection point in just $O(\log N)$ steps.

---

## 🔍 Further Exploration
- Compare this with LeetCode 274: **H-Index**.
- Try solving it in $O(N)$ time utilizing an auxiliary frequency array (Count Sort concept)!
- Look into **H-Index II** where the input array is *already* sorted.

---

## 🔗 References
- **GeeksforGeeks Problem:** [Find H-Index](https://www.geeksforgeeks.org/problems/find-h-index--165609/1)
- **Concept Reference:** [What is the h-index?](https://en.wikipedia.org/wiki/H-index)

---

## 👨‍💻 Author
[![GitHub](https://img.shields.io/badge/GitHub-imnilesh18-181717?style=for-the-badge&logo=github)](https://github.com/imnilesh18)
