# 🎯 Find the Closest Pair from Two Arrays

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/find-the-closest-pair-from-two-arrays4215/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-18.01%25-orange?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given two **sorted** arrays `arr1[]` and `arr2[]` of size `n` and `m` and a number `x`, find the pair whose sum is closest to `x` and the pair has an element from each array. In the case of multiple closest pairs, return any one of them.

**Note:** In the driver code, the absolute difference between the sum of the closest pair and `x` is printed.

---

## 💡 Examples

### Example 1
```text
Input: arr1[] = [1, 4, 5, 7], arr2[] = [10, 20, 30, 40], x = 32
Output: [1, 30]
Explanation: The closest pair whose sum is closest to 32 is [1, 30] = 31.
```

### Example 2
```text
Input: arr1[] = [1, 4, 5, 7], arr2[] = [10, 20, 30, 40], x = 50 
Output: [7, 40] 
Explanation: The closest pair whose sum is closest to 50 is [7, 40] = 47.
```

<details>
<summary>📖 <b>Example Breakdown (Example 1)</b></summary>
<br>

- We want to find a pair `(a, b)` where `a ∈ arr1` and `b ∈ arr2` such that `|a + b - x|` is minimized.
- Start pointers at `l = 0` (pointing to `1` in `arr1`) and `r = 3` (pointing to `40` in `arr2`).
- `Sum = 1 + 40 = 41`. Difference from 32 is 9. Best pair so far is `[1, 40]`. Since 41 > 32, we move `r` left.
- Now `l = 0`, `r = 2` (value `30`). `Sum = 1 + 30 = 31`. Difference from 32 is 1. Better! Update best pair to `[1, 30]`. Since 31 < 32, move `l` right.
- Continuing this logic, the minimum difference found is 1, corresponding to the pair `[1, 30]`.

</details>

---

## ⚠️ Constraints

- `1 ≤ arr1.size(), arr2.size() ≤ 10^5`
- `1 ≤ arr1[i], arr2[i] ≤ 10^9`
- `1 ≤ x ≤ 10^9`

**Expected Complexities:**
- **Time Complexity:** $\mathcal{O}(n + m)$
- **Auxiliary Space:** $\mathcal{O}(1)$

---

## 🚀 Solution Approach

### Two-Pointer Technique (Optimal)

```cpp
// Intuition: Since both arrays are already sorted, we can use a two-pointer technique to converge on the target sum x from opposite ends, avoiding the need to check every possible pair.
// Approach: Place one pointer at the start of arr1 (smallest elements) and another at the end of arr2 (largest elements). Calculate the sum of the elements at these pointers. If the sum is smaller than x, move the arr1 pointer forward to increase the sum. If it's larger, move the arr2 pointer backward to decrease it. Keep track of the pair with the minimum absolute difference from x throughout the process.
// Time Complexity: O(N + M), where N is the size of arr1 and M is the size of arr2. Each pointer only moves in one direction, so we traverse each array at most once.
// Space Complexity: O(1) auxiliary space, as we only use a few integer variables and a fixed-size vector to store the two result elements.

class Solution {
  public:
    vector<int> findClosestPair(vector<int> &arr1, vector<int> &arr2, int x) {
        int n = arr1.size();
        int m = arr2.size();
        
        int l = 0;                  // Start pointer for arr1
        int r = m - 1;              // End pointer for arr2
        
        int min_diff = INT_MAX;     // Track the smallest difference
        vector<int> res(2);         // Store the best pair
        
        while (l < n && r >= 0) {
            int sum = arr1[l] + arr2[r]; 
            int diff = abs(sum - x);     // Difference from target
            
            if (diff < min_diff) {       // Update if a closer pair is found
                min_diff = diff;
                res[0] = arr1[l];
                res[1] = arr2[r];
            }
            
            if (sum < x) {
                l++;                     // Need a larger sum, move right
            } else if (sum > x) {
                r--;                     // Need a smaller sum, move left
            } else {
                break;                   // Exact match found (diff == 0)
            }
        }
        
        return res;
    }
};

/*
*
* Dry Run
*
* Input: arr1 = [1, 4, 5, 7], arr2 = [10, 20, 30, 40], x = 32
* Initial state: l = 0, r = 3, min_diff = infinity
* * Iteration 1:
* arr1[0] = 1, arr2[3] = 40, sum = 41
* diff = abs(41 - 32) = 9
* 9 is less than infinity, update min_diff = 9, res = [1, 40]
* sum (41) > x (32), so decrement r to 2
* * Iteration 2:
* arr1[0] = 1, arr2[2] = 30, sum = 31
* diff = abs(31 - 32) = 1
* 1 is less than 9, update min_diff = 1, res = [1, 30]
* sum (31) < x (32), so increment l to 1
* * Iteration 3:
* arr1[1] = 4, arr2[2] = 30, sum = 34
* diff = abs(34 - 32) = 2
* 2 is not less than 1, min_diff remains 1
* sum (34) > x (32), so decrement r to 1
* * Iteration 4:
* arr1[1] = 4, arr2[1] = 20, sum = 24
* diff = abs(24 - 32) = 8
* 8 is not less than 1, min_diff remains 1
* sum (24) < x (32), so increment l to 2
* * Iteration 5:
* arr1[2] = 5, arr2[1] = 20, sum = 25
* diff = abs(25 - 32) = 7
* 7 is not less than 1, min_diff remains 1
* sum (25) < x (32), so increment l to 3
* * Iteration 6:
* arr1[3] = 7, arr2[1] = 20, sum = 27
* diff = abs(27 - 32) = 5
* 5 is not less than 1, min_diff remains 1
* sum (27) < x (32), so increment l to 4
* * Loop condition l < n (4 < 4) fails. Loop ends.
* Final result returned: [1, 30]
*/
```

---

## 🔑 Key Insights
- **Leveraging Pre-Sorting:** Because both arrays are already sorted, we do not need to use nested loops ($O(N \times M)$) to test all pairs.
- **Two-Pointer Convergence:** By starting at the minimum element of `arr1` and the maximum element of `arr2`, we can logically dictate the direction of pointer movements to approach `x`, ensuring an optimal $O(N + M)$ runtime.
- **Early Stopping:** If we hit an exact match (`sum == x`), we can break out of the loop immediately since `diff == 0` is the absolute minimum possible.

---

## 🔍 Further Exploration
- **Two Sum II - Input Array Is Sorted**: A similar problem that uses two pointers but operates on a single array.
- **3Sum / 4Sum**: Extends the two-pointer logic to more variables.
- **Find Pairs with Given Sum**: Similar concept but finding *exact* pairs rather than the *closest* pair.

---

## 🔗 References
- **GeeksforGeeks Problem Link:** [Find the closest pair from two arrays](https://www.geeksforgeeks.org/problems/find-the-closest-pair-from-two-arrays4215/1)

---

## 👨‍💻 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`Arrays` `Searching` `Data Structures` `Algorithms` `Two-Pointers` `GeeksforGeeks` 