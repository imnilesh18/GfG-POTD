# 🟧 Successful Binary Searches Irrespective of Pivot

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/count-always-found/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-76.63%25-green?style=for-the-badge" alt="Accuracy: 76.63%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` of `n` distinct integers (not necessarily sorted), consider the following search for a target:

1. Maintain a range `[lo, hi]`, initially `[0, n-1]`.
2. At each step, pick any index `p` in `[lo, hi]` (not necessarily the middle) as pivot. If `arr[p] == target`, stop - found.
3. If `target < arr[p]`, set `hi = p - 1`; if `target > arr[p]`, set `lo = p + 1`. If `lo > hi`, stop - not found.

Count the number of indices `i` such that searching for `target = arr[i]` succeeds **no matter which pivot is chosen at every step** (i.e., for every possible sequence of pivot choices).

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [3, 7, 9, 8, 15]
Output: 3
Explanation: 3, 7, and 15 (indices 0, 1, 4) are always found. Every possible pivot comparison happens to steer the search toward them, no matter the order. 9 and 8 are not (e.g. if the first pivot picked is 8, searching for 9 gets pushed right and index 2 is lost forever).
```

### Example 2
```text
Input: arr[] = [9, 4, 1, 10, 22, 23, 20]
Output: 1
Explanation: Only 10 (index 3) is always found — every pivot, left or right, happens to steer toward it. Everything else can fail on some pivot order.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>
<br>

Let's break down `arr = [3, 7, 9, 8, 15]`:
- For an element to *always* be found, it must inherently act as a perfect partition point.
- **Rule:** It must be **strictly greater** than *all* elements to its left, AND **strictly smaller** than *all* elements to its right.
- `3`: Nothing on left (valid). Smaller than everything on right: `[7, 9, 8, 15]` (valid). -> **Found**
- `7`: Greater than left `[3]` (valid). Smaller than right `[9, 8, 15]` (valid). -> **Found**
- `9`: Greater than left `[3, 7]` (valid). Smaller than right `[8, 15]`? **False** (9 > 8). -> **Not Found**
- `8`: Greater than left `[3, 7, 9]`? **False** (8 < 9). -> **Not Found**
- `15`: Greater than left `[3, 7, 9, 8]` (valid). Nothing on right (valid). -> **Found**
- Total valid elements = **3**.

</details>

---

## ⚙️ Constraints

> - `1 ≤ arr.size() ≤ 10^5`
> - `1 ≤ arr[i] ≤ 10^6`
> - **Expected Time Complexity:** O(n)
> - **Expected Auxiliary Space:** O(n)

---

## 🚀 Solution Approaches

### Optimized Approach: Prefix Maximum & Suffix Minimum

**Intuition:** 
For a binary search algorithm to successfully find a target regardless of the pivot sequence, the target element must be naturally positioned in a "sorted-like" state relative to the rest of the array. Specifically, it must be strictly larger than everything that appears before it, and strictly smaller than everything that appears after it. 

Instead of checking the entire left and right sub-arrays for every single element (which would take $O(n^2)$ time), we can precompute the minimum values from the right side (Suffix Minimum) and keep a running track of the maximum value from the left side (Prefix Maximum). This brings the time complexity down to $O(n)$.

```cpp
// Intuition: For an element to be found regardless of pivot choices, it must be strictly greater than all elements on its left and strictly smaller than all elements on its right.
// Approach:
// 1. Precompute a suffix minimum array where suffMin[i] stores the minimum element from index i to n-1.
// 2. Iterate through the array while keeping track of the maximum element seen so far on the left (maxLeft).
// 3. For each element at index i, check if it is greater than maxLeft and smaller than suffMin[i+1].
// 4. Count the elements that satisfy both conditions and update maxLeft.
// Time Complexity: O(n) - We traverse the array twice: once to build the suffix minimums and once to count valid elements.
// Space Complexity: O(n) - We use an auxiliary array of size n to store the suffix minimums.
class Solution {
  public:
    int countAlwaysFound(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;
        if (n == 1) return 1;

        // Precompute the minimum element on the right (suffix minimums)
        vector<int> suffMin(n);
        suffMin[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffMin[i] = min(suffMin[i + 1], arr[i]);
        }

        int count = 0;
        int maxLeft = -1; // Given constraint arr[i] >= 1, -1 is safe to use.
        
        // Iterate through the array maintaining the maximum element seen so far
        for (int i = 0; i < n; ++i) {
            bool isGreater = (i == 0) || (arr[i] > maxLeft);
            bool isSmaller = (i == n - 1) || (arr[i] < suffMin[i + 1]);
            
            // If the element is strictly greater than all on its left 
            // and strictly smaller than all on its right
            if (isGreater && isSmaller) {
                count++;
            }
            
            // Update the maximum element found on the left
            if (arr[i] > maxLeft) {
                maxLeft = arr[i];
            }
        }

        return count;
    }
};

/*
*
* Dry Run
* Input: arr[] = [3, 7, 9, 8, 15]
* 
* 1. Compute suffMin:
*    suffMin[4] = 15
*    suffMin[3] = min(15, 8) = 8
*    suffMin[2] = min(8, 9) = 8
*    suffMin[1] = min(8, 7) = 7
*    suffMin[0] = min(7, 3) = 3
*    suffMin array becomes: [3, 7, 8, 8, 15]
* 
* 2. Iterate array (maxLeft initially -1):
*    - i=0 (arr[0]=3): isGreater=true(i=0), isSmaller=(3 < suffMin[1]=7)=true. count=1. maxLeft=3.
*    - i=1 (arr[1]=7): isGreater=(7 > maxLeft=3)=true, isSmaller=(7 < suffMin[2]=8)=true. count=2. maxLeft=7.
*    - i=2 (arr[2]=9): isGreater=(9 > maxLeft=7)=true, isSmaller=(9 < suffMin[3]=8)=false. count=2. maxLeft=9.
*    - i=3 (arr[3]=8): isGreater=(8 > maxLeft=9)=false, isSmaller=(8 < suffMin[4]=15)=true. count=2. maxLeft=9.
*    - i=4 (arr[4]=15): isGreater=(15 > maxLeft=9)=true, isSmaller=true(i=n-1). count=3. maxLeft=15.
* 
* 3. Final Result: count = 3
*
*/
```

---

## 🧠 Key Insights

- **Partition Logic:** This problem mirrors the logic of finding valid pivot elements in the QuickSort algorithm. An element is a valid pivot if it already sits in its correct final sorted position, dividing the array into strictly smaller and strictly larger halves.
- **Optimization Trick:** Instead of a nested loop checking every element, storing spatial data (`suffMin`) and carrying temporal data (`maxLeft`) reduces operations drastically from $O(n^2)$ to $O(n)$.

---

## 🔗 Further Exploration
- Compare this problem with finding "Peak Elements" or the "Next Greater Element" to understand different ways prefix and suffix trackers can be utilized in arrays.
- Explore how pivot selection directly affects the time complexity of QuickSort.

---

## 📚 References
- **GeeksforGeeks Problem:** [Count always found](https://www.geeksforgeeks.org/problems/count-always-found/1)

---

## 👨‍💻 Author
**Nilesh Kumar**
- GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`[binary-search]` `[arrays]` `[prefix-suffix]` `[constructive-algo]` `[geeksforgeeks]`