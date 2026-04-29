# 🔀 Min Swaps to Group 1s

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/minimum-swaps-required-to-group-all-1s-together2451/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-40.3%25-green?style=for-the-badge" alt="Accuracy: 40.3%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
  </a>
</p>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

You are given a binary array `arr[]` consisting only of `0`s and `1`s. Determine the **minimum** number of swaps required to group all the `1`s together in a contiguous subarray.

A **swap** operation allows you to choose any two indices `i` and `j` and exchange their values (i.e., `swap(arr[i], arr[j])`).

If the array contains no `1`s, return `-1`.

---

## 💡 Examples

**Example 1:**
```text
Input: arr[] = [1, 0, 1, 0, 1]
Output: 1
Explanation: Only 1 swap is required to group all 1's together. Swapping index 1 and 4 will give arr[] = [1, 1, 1, 0, 0].
```

**Example 2:**
```text
Input: arr[] = [1, 0, 1, 0, 1, 1] 
Output: 1
Explanation: Only 1 swap is required to group all 1's together. Swapping index 0 and 3 will give arr[] = [0, 0, 1, 1, 1, 1].
```

**Example 3:**
```text
Input: arr[] = [0, 0, 0]
Output: -1
Explanation: No 1s are present in the array, so return -1.
```

<details>
<summary>📖 <b>Example Breakdown (Example 1)</b></summary>

1. **Initial Array:** `[1, 0, 1, 0, 1]`
2. **Total `1`s:** There are exactly **3** ones in the array. This means our final contiguous block of ones must be of size `3`.
3. **Analyze Windows of Size 3:**
   - Window 1 (indices 0 to 2): `[1, 0, 1]` -> Contains two `1`s. Requires 1 swap (to replace the `0`).
   - Window 2 (indices 1 to 3): `[0, 1, 0]` -> Contains one `1`. Requires 2 swaps.
   - Window 3 (indices 2 to 4): `[1, 0, 1]` -> Contains two `1`s. Requires 1 swap.
4. **Minimum Swaps:** The maximum number of `1`s already present in any window of size 3 is **2**. Thus, `Total 1s - Max 1s in window` = `3 - 2 = 1 swap`.

</details>

---

## ⚠️ Constraints

- `1 ≤ arr.size() ≤ 10^6`
- `0 ≤ arr[i] ≤ 1`

**Expected Complexities:**
- **Time Complexity:** $O(n)$
- **Auxiliary Space:** $O(1)$

---

## 🚀 Solution Approach

### 🛠️ Optimized Sliding Window

**Summary/Intuition:**
Since we want to group all `1`s together, the final group will be a contiguous subarray of size `K`, where `K` is the total number of `1`s in the array. We can use a fixed-size sliding window of size `K` to find the subsegment with the maximum number of `1`s already present. The minimum swaps needed will simply be `K` minus the maximum `1`s found in any window.

```cpp
// Intuition: The final contiguous block of 1s will have a size equal to the total number of 1s in the array. We can use a fixed-size sliding window to find the subsegment with the maximum number of 1s already present. The minimum swaps needed will simply be the total number of 1s minus the maximum 1s found in any window.
// Approach: First, count the total 1s to determine the required window size. If 0, return -1. Then, use two pointers (i and j) to slide a window of this fixed size across the array. Track the number of 1s currently in the window. Shrink the left side if the window exceeds the required size, calculate the max 1s when the window size is correct, and expand the right side.
// Time Complexity: O(N) because we iterate through the array twice — once to count the total 1s, and once for the sliding window. Both operations take linear time.
// Space Complexity: O(1) as we are only using a few integer variables (pointers and counters) regardless of the input size.

class Solution {
  public:
    int minSwaps(vector<int>& arr) {
        int n = arr.size();
        int total_ones = 0;
        
        // Count total 1s to determine window size
        for (int num : arr) {
            total_ones += num;
        }
        
        // Handle base case where no 1s exist
        if (total_ones == 0) {
            return -1;
        }
        
        int i = 0, j = 0;
        int current_ones = 0;
        int max_ones = 0;
        
        while (j < n) {
            // Add current element to our window count
            current_ones += arr[j];
            
            // shrink: reduce window if it exceeds total_ones
            if (j - i + 1 > total_ones) {
                current_ones -= arr[i];
                i++;
            }
            
            // calculate results: update max when window size matches total_ones
            if (j - i + 1 == total_ones) {
                max_ones = max(max_ones, current_ones);
            }
            
            // expand: move right pointer forward
            j++;
        }
        
        // Total swaps is total 1s minus the most 1s already together
        return total_ones - max_ones;
    }
};

/*
*
* Dry Run
*
* Input: arr[] = [1, 0, 1, 0, 1]
* n = 5
* total_ones = 3 (window size)
* Return -1 condition is skipped since total_ones > 0
* * j=0: arr[0]=1 is added. current_ones=1. Window size is 1. Expand j to 1.
* j=1: arr[1]=0 is added. current_ones=1. Window size is 2. Expand j to 2.
* j=2: arr[2]=1 is added. current_ones=2. Window size is 3. Matches total_ones, max_ones=2. Expand j to 3.
* j=3: arr[3]=0 is added. current_ones=2. Window size is 4. Shrink: remove arr[0], current_ones=1, i=1. Matches total_ones, max_ones remains 2. Expand j to 4.
* j=4: arr[4]=1 is added. current_ones=2. Window size is 4. Shrink: remove arr[1], current_ones=2, i=2. Matches total_ones, max_ones becomes 2. Expand j to 5.
* * Loop terminates because j = 5.
* Minimum swaps = total_ones - max_ones = 3 - 2 = 1.
* Result: 1
*
*/
```

---

## 🧠 Key Insights

- **Window Size is Pre-determined:** The key to solving this in $O(N)$ is realizing that you don't need to manually test every possible grouping. The size of the group is strictly constrained by the number of `1`s.
- **Maximum 1s = Minimum Swaps:** Finding the window of size `K` with the *maximum* number of `1`s gives us the window that requires the *minimum* number of `0`s to be swapped out.

---

## 🔍 Further Exploration

- **Circular Array Variant:** Consider how the logic would change if the array were circular (i.e., the end of the array wraps around to the beginning). You can append the array to itself to handle circular sliding windows.
- **Minimum Swaps to Group Elements:** A similar problem approach can be used if we need to group elements of multiple types (like `0`s, `1`s, and `2`s).

---

## 🔗 References

- **GeeksforGeeks Problem:** [Min Swaps to Group 1s](https://www.geeksforgeeks.org/problems/minimum-swaps-required-to-group-all-1s-together2451/1)
- **Concept:** Sliding Window Technique

---

## 👤 Author

**Nilesh**
- GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#SlidingWindow` `#TwoPointers` `#Arrays` `#DataStructures` `#GeeksforGeeks` `#Adobe` `#C++` 