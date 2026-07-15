# 📈 Longest Bitonic Subarray

<div align="center">

[![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/maximum-length-bitonic-subarray5730/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)]()
[![Accuracy](https://img.shields.io/badge/Accuracy-38.09%25-green?style=for-the-badge)]()
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)]()
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)]()

</div>

---

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given an array `arr[]` containing positive integers, return the maximum length of the **bitonic subarray**.

A subarray `arr[i...j]` is considered bitonic if its elements first **monotonically increase**, and then **monotonically decrease**. Formally, there exists an index `k` (where `i <= k <= j`) such that:
`arr[i] <= arr[i+1] <= ... <= arr[k]` 
`arr[k] >= arr[k+1] >= ... >= arr[j]`

---

## ⚙️ Constraints

> - `1 ≤ arr.size() ≤ 10^6`
> - `1 ≤ arr[i] ≤ 10^6`
> - **Expected Time Complexity:** `O(n)`
> - **Expected Auxiliary Space:** `O(1)`

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [12, 4, 78, 90, 45, 23]
Output: 5
Explanation: The longest bitonic subarray is [4, 78, 90, 45, 23], it starts increasing at 4, peaks at 90, and decreases to 23, giving length of 5.

```

### Example 2

```text
Input: arr[] = [10, 20, 30, 40]
Output: 4
Explanation: The array [10, 20, 30, 40] is striclty increasing with no decreasing part, so longest bitonic subarray is the entire array itself, giving a length of 4.

```

### Example 3

```text
Input: arr[] = [10, 10, 10, 10]
Output: 4

```

**Array:** `[12, 4, 78, 90, 45, 23]`

1. **Index 0 to 1:** `[12, 4]` (Decreasing only) → Length = 2
2. **Index 1 to 5:** `[4, 78, 90]` (Increasing), then `[90, 45, 23]` (Decreasing).
* Subarray: `[4, 78, 90, 45, 23]`
* Length: 5


3. **Maximum Length** found is **5**.

---

## 🧠 Approach & Intuition

**Intuition:**
A bitonic sequence naturally has two phases: an increasing mountain climb followed by a decreasing descent down the mountain. Since we want to find the longest subarray, we can greedily expand a "window" or range. Starting from an index `i`, we can move a pointer `j` forward as long as elements are increasing, and then move it forward again as long as they are decreasing.

**Step-by-Step Approach:**

1. Maintain two pointers: `i` for the start of the current bitonic sequence, and `j` to scan the sequence.
2. For any starting point `i`, first increment `j` as long as `arr[j] <= arr[j + 1]` (Increasing Phase).
3. Then, increment `j` as long as `arr[j] >= arr[j + 1]` (Decreasing Phase).
4. The length of this bitonic subarray is `j - i + 1`. We update our maximum length tracked so far.
5. **Crucial Edge Case (Flat Valleys):** If a sequence ends in a flat "valley" (e.g., `30, 20, 20`), the next sequence can actually start at the *first* `20`. To ensure we don't miss overlapping sequences, we backtrack `j` through any duplicate values to properly place the next `i`.
6. Advance `i` safely to avoid infinite loops on perfectly flat arrays.

---

## 💻 Implementation

```cpp
// Intuition: A bitonic subarray consists of a non-decreasing sequence followed by a non-increasing sequence. We can greedily expand a window to find these phases.
// Approach: Start at index `i`. Expand pointer `j` as long as elements increase. Then, expand `j` as long as they decrease. Update the max length. To handle flat valleys correctly, backtrack `j` through any duplicate elements to find the correct start for the next sequence.
// Time Complexity: O(n) where n is the length of the array. Each element is visited at most a few times.
// Space Complexity: O(1) as we only use a few integer variables for pointers and length tracking.

class Solution {
  public:
    int bitonic(vector<int> &arr) {
        int n = arr.size();
        if (n == 0) return 0; // Guard against empty arrays
        
        int maxLen = 1;
        int i = 0;
        
        // Loop to find all bitonic segments
        while (i < n - 1) {
            int j = i;
            
            // Phase 1: Expand monotonically increasing segment
            while (j < n - 1 && arr[j] <= arr[j + 1]) {
                j++;
            }
            
            // Phase 2: Expand monotonically decreasing segment
            while (j < n - 1 && arr[j] >= arr[j + 1]) {
                j++;
            }
            
            // Calculate length and update maximum
            maxLen = max(maxLen, j - i + 1);
            
            // Phase 3: Backtrack to the start of flat valleys 
            // Ensures we don't miss sequences sharing flat elements
            int next_i = j;
            while (next_i > i && arr[next_i] == arr[next_i - 1]) {
                next_i--;
            }
            
            // Safely advance `i`
            i = max(next_i, i + 1);
        }
        
        return maxLen;
    }
};

/*
*
* Dry Run
* Input: arr[] = [12, 4, 78, 90, 45, 23]
* * Setup: n = 6, maxLen = 1, i = 0
* * 1st Iteration (i = 0):
* j = 0.
* Inc Phase: arr[0] <= arr[1] (12 <= 4) is False. j stays 0.
* Dec Phase: arr[0] >= arr[1] (12 >= 4) is True. j becomes 1. arr[1] >= arr[2] (4 >= 78) is False.
* maxLen = max(1, 1 - 0 + 1) = 2. (Sequence: [12, 4])
* Backtrack: next_i = 1. arr[1] == arr[0] (4 == 12) is False.
* i = max(1, 0 + 1) = 1.
* * 2nd Iteration (i = 1):
* j = 1.
* Inc Phase: 4 <= 78 (True, j=2), 78 <= 90 (True, j=3), 90 <= 45 (False). j = 3.
* Dec Phase: 90 >= 45 (True, j=4), 45 >= 23 (True, j=5). j = 5.
* maxLen = max(2, 5 - 1 + 1) = 5. (Sequence: [4, 78, 90, 45, 23])
* Backtrack: next_i = 5. arr[5] == arr[4] (23 == 45) is False.
* i = max(5, 1 + 1) = 5.
* * Loop terminates because i (5) is not < n - 1 (5).
* * Final Result: 5
*
*/

```

---

## 🔍 Key Insights

1. **Greedy Expansion works:** A bitonic sub-array can be completely defined by checking simple adjacent relations. Because we just need sub-arrays (contiguous elements), checking the boundary elements one-by-one safely traces the entire profile of a bitonic sequence.
2. **Handling Flat Valleys:** The most prominent edge case arises with arrays like `[30, 20, 20, 30]`. `[30, 20, 20]` is a valid sequence, and `[20, 20, 30]` is another. The flat segment `20, 20` must be shared. Backtracking `j` across duplicate minimums smoothly handles this issue while keeping space complexity strictly at `O(1)`.

---

## 🔗 References

* **GeeksForGeeks Problem:** [Longest Bitonic Subarray](https://www.geeksforgeeks.org/problems/maximum-length-bitonic-subarray5730/1)
* **Related Concept:** [Bitonic Sequence Algorithm](https://en.wikipedia.org/wiki/Bitonic_sorter)

---

## 👨‍💻 Author

Built and maintained by [imnilesh18](https://github.com/imnilesh18).

---

## 🏷️ Tags

`#Arrays` `#TwoPointers` `#DynamicProgramming` `#Algorithms` `#GeeksForGeeks` `#InterviewPreparation`