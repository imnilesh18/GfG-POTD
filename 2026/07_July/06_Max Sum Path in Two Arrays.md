# 🔀 Max Sum Path in Two Arrays

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/max-sum-path-in-two-arrays/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-30.9%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
  </a>
</div>

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📜 Problem Statement

Given two sorted arrays of distinct integers in increasing order `a[]` and `b[]`, which may have some common elements, find the maximum sum of a path from the beginning of any array to the end of any array. You may switch from one array to the other only at common elements.

**Note:** When switching, count the common element only once.

---

## 💡 Examples

```text
Input: a[] = [2, 3, 7, 10, 12], b[] = [1, 5, 7, 8]
Output: 35
Explanation: The path will be (1 + 5 + 7 + 10 + 12) = 35, where 1 and 5 come from b[] and then 7 is common so we switch to a[] and add 10 and 12.
```

```text
Input: a[] = [1, 2, 3], b[] = [3, 4, 5]
Output: 15
Explanation: The path will be (1 + 2 + 3 + 4 + 5) = 15.
```

<details>
<summary>📖 <b>Example Breakdown</b></summary>

Let's break down the first example:
- `a[]` = `[2, 3, 7, 10, 12]`
- `b[]` = `[1, 5, 7, 8]`

We traverse both arrays simultaneously:
1. Start at `a[0]=2` and `b[0]=1`. Since `1 < 2`, add `1` to the sum of array `b` (`sum_b = 1`).
2. Move to `b[1]=5`. Since `2 < 5`, add `2` to the sum of array `a` (`sum_a = 2`).
3. Move to `a[1]=3`. Since `3 < 5`, add `3` to `sum_a` (`sum_a = 5`).
4. Move to `a[2]=7`. Now `b[1]=5 < 7`, so add `5` to `sum_b` (`sum_b = 6`).
5. Move to `b[2]=7`. Now `a[2] == b[2] == 7`. We hit a common element.
6. We take the maximum of `sum_a` and `sum_b` (`max(5, 6) = 6`), add the common element `7` (`6 + 7 = 13`), and reset both sums.
7. Continue from `a[3]=10` and `b[3]=8`. `8 < 10`, so `sum_b = 8`.
8. Array `b` is exhausted. Add the remaining elements of `a`: `sum_a = 10 + 12 = 22`.
9. The final answer is the accumulated sum (`13`) plus the maximum of the remaining sums (`max(22, 8) = 22`).
10. `13 + 22 = 35`.

</details>

---

## ⚙️ Constraints

- `1 ≤ a.size(), b.size() ≤ 10^4`
- `1 ≤ a[i], b[i] ≤ 10^5`

---

## 🛠️ Solution Approaches

### 🚀 Optimized Two-Pointer Approach

**Intuition:** Since the arrays are sorted, we can use a two-pointer approach to traverse them simultaneously, similar to the merge step in Merge Sort. We accumulate the sum of elements for both arrays separately. When we encounter a common element, it acts as a "bridge" where we can choose the path that yielded the maximum sum up to that point. We add that maximum sum and the common element to our final result, reset our accumulators, and continue the process.

```cpp
// Intuition: The problem requires finding the maximum sum path across two sorted arrays, allowing switches only at common elements. We can greedily accumulate sums for both arrays until a common element is found. At the common element, we pick the maximum accumulated sum, add the common element, and reset the sums.
// Approach:
// 1. Initialize variables i, j, sum1, sum2, and result to 0.
// 2. Traverse both arrays simultaneously using two pointers i and j.
// 3. If a[i] < b[j], add a[i] to sum1 and increment i.
// 4. If a[i] > b[j], add b[j] to sum2 and increment j.
// 5. If a[i] == b[j], add max(sum1, sum2) + a[i] to result, reset sum1 and sum2 to 0, and increment both i and j.
// 6. After the loop, process any remaining elements in array 'a' and add them to sum1.
// 7. Process any remaining elements in array 'b' and add them to sum2.
// 8. Add the maximum of the remaining sum1 and sum2 to the result and return it.
// Time Complexity: O(n + m), where n and m are the sizes of the two arrays. We traverse both arrays exactly once.
// Space Complexity: O(1), as we only use a few integer variables for computation.

class Solution {
  public:
    int maxPathSum(vector<int> &a, vector<int> &b) {
        int i = 0, j = 0;
        int n = a.size(), m = b.size();
        
        // Variables to store segment sums and the final result
        int sum1 = 0, sum2 = 0, result = 0;
        
        // Traverse both arrays simultaneously
        while (i < n && j < m) {
            if (a[i] < b[j]) {
                sum1 += a[i++]; // Add to sum1 and move pointer i
            } else if (a[i] > b[j]) {
                sum2 += b[j++]; // Add to sum2 and move pointer j
            } else {
                // Common element found, add max of sum1 and sum2 plus the common element
                result += max(sum1, sum2) + a[i];
                
                // Reset sums for the next segment
                sum1 = 0;
                sum2 = 0;
                
                // Move both pointers
                i++;
                j++;
            }
        }
        
        // Process remaining elements of array a
        while (i < n) {
            sum1 += a[i++];
        }
        
        // Process remaining elements of array b
        while (j < m) {
            sum2 += b[j++];
        }
        
        // Add the maximum of the final segments to the result
        result += max(sum1, sum2);
        
        return result;
    }
};

/*
*
* Dry Run
* Input: a[] = [2, 3, 7, 10, 12], b[] = [1, 5, 7, 8]
* Initialize: i = 0, j = 0, sum1 = 0, sum2 = 0, result = 0
* * Iteration 1: a[0] (2) > b[0] (1) -> sum2 = 1, j = 1
* Iteration 2: a[0] (2) < b[1] (5) -> sum1 = 2, i = 1
* Iteration 3: a[1] (3) < b[1] (5) -> sum1 = 2 + 3 = 5, i = 2
* Iteration 4: a[2] (7) > b[1] (5) -> sum2 = 1 + 5 = 6, j = 2
* Iteration 5: a[2] (7) == b[2] (7) -> result += max(5, 6) + 7 = 13. Reset sum1 = 0, sum2 = 0, i = 3, j = 3
* Iteration 6: a[3] (10) > b[3] (8) -> sum2 = 8, j = 4
* * Loop ends as j >= m.
* Process remaining elements of a:
* a[3] (10) -> sum1 = 10, i = 4
* a[4] (12) -> sum1 = 10 + 12 = 22, i = 5
* * Process remaining elements of b: none.
* * Final step: result += max(sum1, sum2) = 13 + max(22, 8) = 13 + 22 = 35.
* Output: 35
*
*/
```

---

## 🧠 Key Insights
- **Greedy Choice at Intersections:** Because we only switch arrays at common elements, every common element acts as a checkpoint. At each checkpoint, we must greedily pick the maximum sum among the two paths to maximize our overall path sum.
- **Merge-Sort Inspired Traversal:** We exploit the fact that the arrays are already sorted. A simple two-pointer traversal ensures that we don't miss any common elements and that we process the elements in linearly increasing order.
- **Handling Tails:** The arrays may not end simultaneously or end on a common element. Collecting the remainder of both arrays after the main loop and selecting the maximum one final time captures the best finishing path.

---

## 🚀 Further Exploration
- Try a similar problem involving finding the intersection of two sorted arrays.
- Explore variations of the "Merge Two Sorted Arrays" pattern, like finding the median of two sorted arrays.
- Practice related DP/Greedy traversal techniques such as the "Trapping Rain Water" or "Container With Most Water" problems.

---

## 🔗 References
- **Original GeeksforGeeks Problem:** [Max Sum Path in Two Arrays](https://www.geeksforgeeks.org/problems/max-sum-path-in-two-arrays/1)

---

## 👤 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`#array` `#two-pointers` `#greedy` `#merge` `#geeksforgeeks` `#c++`