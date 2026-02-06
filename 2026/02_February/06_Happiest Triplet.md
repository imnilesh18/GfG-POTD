# 😃 Happiest Triplet

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Medium-orange?logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/happiest-triplet2921/1)
![Accuracy](https://img.shields.io/badge/Accuracy-53.91%25-green)
![Points](https://img.shields.io/badge/Points-4-blue)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

You are given three arrays $a[]$, $b[]$, and $c[]$ of the same size. Find a triplet such that the difference between the **maximum** and **minimum** element in that triplet is minimized.

A triplet should be selected so that it contains exactly one number from each of the three given arrays. This triplet is called the **happiest triplet**.

**Output:** Print the triplet in **decreasing order**.

> **Note:** If there are multiple triplets with the same minimum difference, select the one with the **smallest sum** of its elements.

---

## 🔹 Constraints

* $1 \leq a.size(), b.size(), c.size() \leq 10^5$
* $1 \leq a[i], b[i], c[i] \leq 10^5$

---

## 🔍 Examples

### Example 1
```text
Input:  a[] = [5, 2, 8], b[] = [10, 7, 12], c[] = [9, 14, 6]
Output: [7, 6, 5]
Explanation: The triplet [5, 7, 6] has difference (7 - 5) = 2, which is the minimum of all possible triplets.

```

### Example 2

```text
Input:  a[] = [15, 12, 18, 9], b[] = [10, 17, 13, 8], c[] = [14, 16, 11, 5]
Output: [11, 10, 9]
Explanation: Multiple triplets have the same minimum difference. Among them, [11, 10, 9] has the smallest sum, so it is chosen.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's walk through **Example 1**:
`a = [5, 2, 8]`, `b = [10, 7, 12]`, `c = [9, 14, 6]`

1. **Sort Arrays:**
* `a`: `[2, 5, 8]`
* `b`: `[7, 10, 12]`
* `c`: `[6, 9, 14]`


2. **Pointers:** Start at `i=0, j=0, k=0`.
* Current values: `a[0]=2`, `b[0]=7`, `c[0]=6`.
* Min: 2, Max: 7, Diff: 5.
* Triplet: `[2, 7, 6]`.
* **Action:** Smallest is `a[i]`. Increment `i`.


3. **Next Step:** `i=1`.
* Current values: `a[1]=5`, `b[0]=7`, `c[0]=6`.
* Min: 5, Max: 7, Diff: 2.
* Diff (2) < Best Diff (5). New Best: `[5, 7, 6]`.
* **Action:** Smallest is `a[i]`. Increment `i`.


4. **Next Step:** `i=2`.
* Current values: `a[2]=8`, `b[0]=7`, `c[0]=6`.
* Min: 6, Max: 8, Diff: 2.
* Diff is same (2). Check Sum:  vs previous . Previous is better.
* **Action:** Smallest is `c[k]`. Increment `k`.



...Process continues. Final answer sorted descending: `[7, 6, 5]`.

</details>

---

## 💡 Solution Approaches

### 🚀 Optimized Approach (Sorting + Three Pointers)

The core idea is to treat the elements from the three arrays as a sliding window. By sorting the arrays, we can efficiently decide which element to change to potentially minimize the range . In every step, we increment the index of the array that holds the **minimum** value of the current triplet, hoping to find a larger value in that array that might reduce the gap with the current maximum.

```cpp
// Intuition: To minimize the difference (max - min), elements must be close to each other. By sorting, we can greedily advance the pointer of the smallest element to potentially find a larger value in that array, thereby shrinking the window between min and max.
// Approach: Sort all three arrays. Use three pointers initialized to the start. In each step, calculate min and max of current elements. Update the result if the current difference is smaller (or equal with smaller sum). Increment the pointer of the minimum element to try and reduce the gap.
// Time Complexity: O(N log N) due to sorting the three arrays (where N is the array size). The pointer traversal is O(N).
// Space Complexity: O(1) auxiliary space as we only use variables for pointers and tracking values.

class Solution {
  public:
    vector<int> smallestDiff(vector<int>& a, vector<int>& b, vector<int>& c) {
        // Sort arrays to apply two/three-pointer technique
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        sort(c.begin(), c.end());
        
        int n = a.size();
        int i = 0, j = 0, k = 0;
        
        // Track minimum difference and corresponding sum found so far
        int min_diff = INT_MAX;
        int min_sum = INT_MAX;
        vector<int> res(3);
        
        // Iterate until one array is exhausted
        while (i < n && j < n && k < n) {
            int v1 = a[i], v2 = b[j], v3 = c[k];
            
            // Find current minimum and maximum in the triplet
            int cur_min = min({v1, v2, v3});
            int cur_max = max({v1, v2, v3});
            int diff = cur_max - cur_min;
            int sum = v1 + v2 + v3;
            
            // Update result if strictly better diff or same diff with smaller sum
            if (diff < min_diff || (diff == min_diff && sum < min_sum)) {
                min_diff = diff;
                min_sum = sum;
                res = {v1, v2, v3};
            }
            
            // Greedily increment the pointer of the smallest element
            if (v1 == cur_min) i++;
            else if (v2 == cur_min) j++;
            else k++;
        }
        
        // Output requires triplet in decreasing order
        sort(res.begin(), res.end(), greater<int>());
        return res;
    }
};

/*
* Dry Run
* Input: a=[5,2,8], b=[10,7,12], c=[9,14,6]
* Sorted: a=[2,5,8], b=[7,10,12], c=[6,9,14]
*
* Iteration 1:
* Pointers: i=0(2), j=0(7), k=0(6)
* Triplet: (2, 7, 6) -> Min: 2, Max: 7, Diff: 5, Sum: 15
* Update Best: diff 5 < INT_MAX. Res=[2, 7, 6]
* Move: a[i] is min (2), increment i to 1
*
* Iteration 2:
* Pointers: i=1(5), j=0(7), k=0(6)
* Triplet: (5, 7, 6) -> Min: 5, Max: 7, Diff: 2, Sum: 18
* Update Best: diff 2 < 5. Res=[5, 7, 6]
* Move: a[i] is min (5), increment i to 2
*
* Iteration 3:
* Pointers: i=2(8), j=0(7), k=0(6)
* Triplet: (8, 7, 6) -> Min: 6, Max: 8, Diff: 2, Sum: 21
* Update Best: diff 2 == 2 but Sum 21 > 18. No change.
* Move: c[k] is min (6), increment k to 1
*
* Iteration 4:
* Pointers: i=2(8), j=0(7), k=1(9)
* Triplet: (8, 7, 9) -> Min: 7, Max: 9, Diff: 2, Sum: 24
* Update Best: diff 2 == 2 but Sum 24 > 18. No change.
* Move: b[j] is min (7), increment j to 1
* * ... Subsequent steps continue until a pointer goes out of bounds.
* Final Result: [5, 7, 6] sorted decreasing -> [7, 6, 5]
*/

```

---

## 🔑 Key Insights

1. **Sorting is Essential**: Sorting allows us to make a "greedy" choice. We know that increasing the minimum element is the only way to potentially decrease the difference .
2. **Three-Pointer Technique**: By maintaining one pointer for each array, we can traverse the sorted space efficiently in  time after sorting.
3. **Greedy Movement**: Always increment the pointer associated with the **minimum** value in the current triplet. This narrows the search space from the bottom up.
4. **Handling Ties**: The problem specifies that if differences are equal, we choose the one with the smallest sum. This is handled by a secondary condition in the update logic: `(diff == min_diff && sum < min_sum)`.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/happiest-triplet2921/1)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

> **Note:** This repository is for educational purposes only. Please respect the Code of Conduct and use these solutions responsibly.
