# 🏹 Farthest Smaller Right

<div align="center">

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/farthest-smaller-right/1).

</div>

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/farthest-smaller-right/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-Problem-green?style=for-the-badge&logo=geeksforgeeks" alt="GeeksforGeeks Problem">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium">
  <img src="https://img.shields.io/badge/Accuracy-50.08%25-orange?style=for-the-badge" alt="Accuracy: 50.08%">
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4">
  <img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License: MIT">
</p>

---

## Problem Statement

You are given an array `arr[]`. For each element at index `i` (0-based indexing), find the **farthest index** `j` to the right (i.e., `j > i`) such that `arr[j] < arr[i]`. If no such index exists for a given position, return `-1` for that index. Return the resulting array of answers.

---

## Examples

**Example 1:**
```
Input: arr[] = [2, 5, 1, 3, 2]
Output: [2, 4, -1, 4, -1]
```
<details>
<summary>📖 Example Breakdown</summary>

* `arr[0] = 2`: The elements to the right are `[5, 1, 3, 2]`. The smaller elements are `1`. The index of `1` is `2`. So, the answer is `2`.
* `arr[1] = 5`: The elements to the right are `[1, 3, 2]`. Smaller elements are `1`, `3`, `2`. Their indices are `2`, `3`, `4`. The farthest index is `4`.
* `arr[2] = 1`: The elements to the right are `[3, 2]`. No smaller element exists. So, the answer is `-1`.
* `arr[3] = 3`: The elements to the right are `[2]`. The smaller element is `2` at index `4`.
* `arr[4] = 2`: No elements to the right. So, the answer is `-1`.
</details>

**Example 2:**
```
Input: arr[] = [2, 3, 5, 4, 1] 
Output: [4, 4, 4, 4, -1]
Explanation: arr[4] is the farthest smallest element to the right for arr[0], arr[1], arr[2] and arr[3].
```

---

## Constraints

<div align="center">

`1 ≤ arr.size() ≤ 10^6`
`1 ≤ arr[i] ≤ 10^6`

</div>

---

## Solution Approach

### Optimized Approach (Suffix Min + Binary Search)

The core idea is to efficiently find the farthest smaller element for each number. A brute-force check would be O(N²), which is too slow given the constraints.

We can optimize this by pre-calculating the minimum value for every suffix of the array. Let's call this the `suff` array, where `suff[i]` holds the minimum value from `arr[i]` to `arr[n-1]`. This `suff` array will be monotonically non-increasing.

Because the `suff` array is sorted in a non-increasing manner, we can use **Binary Search** on it. For each element `arr[i]`, we can binary search on the `suff` array from index `i+1` to `n-1` to find the rightmost (farthest) index `j` where `suff[j] < arr[i]`. This condition guarantees that there is at least one element at or after index `j` that is smaller than `arr[i]`, and by pushing our binary search to the right, we find the farthest such possibility.

This approach breaks the problem into two parts:
1.  **Preprocessing:** Build the suffix minimum array in O(N) time.
2.  **Searching:** For each of the N elements, perform a binary search O(log N) on the suffix array.

The total time complexity is O(N log N) with O(N) auxiliary space.

### C++ Solution
```cpp
// Intuition: To find the farthest smaller element to the right for arr[i], we need an efficient way to query the minimums in the subarray arr[i+1...n-1].
// A suffix minimum array helps. suff[j] = min(arr[j...n-1]). This array is non-increasing, allowing binary search.
// Approach:
// 1. Pre-compute a suffix minimum array `suff`. `suff[i]` will store the minimum element from index `i` to `n-1`.
// 2. Iterate through the input array from `i = 0` to `n-1`.
// 3. For each `arr[i]`, perform a binary search on the `suff` array in the range `[i+1, n-1]`.
// 4. We want the farthest index `j` where `suff[j] < arr[i]`. So in binary search, if we find such a `mid`, we store it and try to find an even farther one by searching in the right half (`lo = mid + 1`).
// 5. If `suff[mid] >= arr[i]`, we search in the left half (`hi = mid - 1`).
// 6. The result of the binary search for each `i` is the answer for that index.
// Time Complexity: O(N log N), where N is the size of the array. O(N) for building the suffix min array and O(N*logN) for performing binary search for each element.
// Space Complexity: O(N) for storing the suffix minimum array `suff` and the answer array `ans`.
class Solution {
  public:
    vector<int> farMin(vector<int>& arr) {
        int n = arr.size();
        vector<int> ans(n, -1); // Initialize answer array with -1
    
        // build suffix min array
        vector<int> suff(n);
        suff[n - 1] = arr[n - 1]; // The last element is the min of the last suffix
        for (int i = n - 2; i >= 0; --i)
            suff[i] = min(arr[i], suff[i + 1]); // Each suffix min is the minimum of current element and the next suffix min
    
        // binary search on suffix for farthest smaller element
        for (int i = 0; i < n; ++i) {
            int lo = i + 1, hi = n - 1, res = -1; // Search range is to the right of i
    
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2; // Avoid potential overflow
                if (suff[mid] < arr[i]) {
                    res = mid;      // Found a potential answer, store it
                    lo = mid + 1;   // Try to find a farther index to the right
                } else {
                    hi = mid - 1;   // Suffix min is not smaller, search in the left half
                }
            }
    
            ans[i] = res; // Store the farthest index found
        }
    
        return ans;
    }
};

/*
*
* Dry Run
*
* Input: arr[] = [2, 5, 1, 3, 2]
*
* 1. Suffix Min Array Calculation:
* suff[4] = arr[4] = 2
* suff[3] = min(arr[3], suff[4]) = min(3, 2) = 2
* suff[2] = min(arr[2], suff[3]) = min(1, 2) = 1
* suff[1] = min(arr[1], suff[2]) = min(5, 1) = 1
* suff[0] = min(arr[0], suff[1]) = min(2, 1) = 1
* Final suff[] = [1, 1, 1, 2, 2]
*
* 2. Main Loop & Binary Search:
* - i = 0, arr[0] = 2:
* Binary search on suff[1...4] for a value < 2.
* Range [1,4]. lo=1, hi=4. mid=2. suff[2]=1 < 2. res=2, lo=3.
* Range [3,4]. lo=3, hi=4. mid=3. suff[3]=2 is not < 2. hi=2.
* Loop ends. res = 2. ans[0] = 2.
*
* - i = 1, arr[1] = 5:
* Binary search on suff[2...4] for a value < 5.
* Range [2,4]. lo=2, hi=4. mid=3. suff[3]=2 < 5. res=3, lo=4.
* Range [4,4]. lo=4, hi=4. mid=4. suff[4]=2 < 5. res=4, lo=5.
* Loop ends. res = 4. ans[1] = 4.
*
* - i = 2, arr[2] = 1:
* Binary search on suff[3...4] for a value < 1.
* suff[3]=2, suff[4]=2. No value is < 1. res remains -1. ans[2] = -1.
*
* - i = 3, arr[3] = 3:
* Binary search on suff[4...4] for a value < 3.
* Range [4,4]. lo=4, hi=4. mid=4. suff[4]=2 < 3. res=4, lo=5.
* Loop ends. res=4. ans[3] = 4.
*
* - i = 4, arr[4] = 2:
* Search range is empty (i+1 > n-1). Loop doesn't run. ans[4] = -1.
*
* Final Answer: [2, 4, -1, 4, -1]
*
*/
```

### Java Solution

```java
// Intuition: The problem asks for the farthest index `j > i` with `arr[j] < arr[i]`. A naive O(N^2) approach would be too slow. We can optimize by preprocessing.
// A suffix minimum array `suff` where `suff[k]` is the minimum of `arr[k...n-1]` is useful. This `suff` array is non-increasing, which is perfect for binary search.
// Approach:
// 1. Create a suffix minimum array `suff`. This is done by iterating from right-to-left. `suff[i] = min(arr[i], suff[i+1])`.
// 2. Iterate through the array with index `i`.
// 3. For each `arr[i]`, we need to find the largest `j` in `[i+1, n-1]` such that `arr[j] < arr[i]`.
// 4. This is equivalent to finding the largest `j` such that `suff[j] < arr[i]`.
// 5. We can binary search for this `j` on the `suff` array. If `suff[mid] < arr[i]`, we have a potential answer, so we record `mid` and search for a farther one in the right half `[mid+1, hi]`.
// 6. Otherwise, we search in the left half `[lo, mid-1]`.
// Time Complexity: O(N log N) - O(N) to build the suffix array and O(log N) for each of the N elements.
// Space Complexity: O(N) - For the suffix array and the answer list.
class Solution {
    public ArrayList<Integer> farMin(int[] arr) {
        int n = arr.length;
        // Initialize the answer list with -1
        ArrayList<Integer> ans = new ArrayList<>(Collections.nCopies(n, -1));
        ArrayList<Integer> arrList = new ArrayList<>(n);
        for (int i : arr) arrList.add(i);

        // build suffix min array
        ArrayList<Integer> suff = new ArrayList<>(arrList);
        // The last element is the base case
        suff.set(n - 1, arrList.get(n - 1));
        for (int i = n - 2; i >= 0; --i)
            // Calculate suffix min from right to left
            suff.set(i, Math.min(arrList.get(i), suff.get(i + 1)));

        // binary search on suffix for farthest smaller element
        for (int i = 0; i < n; ++i) {
            int lo = i + 1, hi = n - 1, res = -1; // Search space is to the right of `i`

            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                // If the minimum in the suffix from `mid` is smaller than arr[i]
                if (suff.get(mid) < arrList.get(i)) {
                    res = mid;       // This is a potential answer
                    lo = mid + 1;    // Check if a farther index exists on the right
                } else {
                    hi = mid - 1;    // Otherwise, search on the left
                }
            }

            ans.set(i, res); // Set the farthest index found
        }

        return ans;
    }
}

/*
*
* Dry Run
*
* Input: arr[] = [2, 5, 1, 3, 2]
*
* 1. Suffix Min ArrayList Calculation:
* suff.get(4) = 2
* suff.set(3, min(arr[3], suff.get(4))) -> min(3, 2) = 2
* suff.set(2, min(arr[2], suff.get(3))) -> min(1, 2) = 1
* suff.set(1, min(arr[1], suff.get(2))) -> min(5, 1) = 1
* suff.set(0, min(arr[0], suff.get(1))) -> min(2, 1) = 1
* Final suff = [1, 1, 1, 2, 2]
*
* 2. Main Loop & Binary Search:
* - i = 0, arr[0] = 2:
* Binary search on suff[1...4]. Target: find index `j` where suff.get(j) < 2.
* lo=1, hi=4 -> mid=2. suff.get(2)=1 < 2. res=2, lo=3.
* lo=3, hi=4 -> mid=3. suff.get(3)=2 is not < 2. hi=2.
* Loop ends. res = 2. ans.set(0, 2).
*
* - i = 1, arr[1] = 5:
* Binary search on suff[2...4]. Target: find `j` where suff.get(j) < 5.
* lo=2, hi=4 -> mid=3. suff.get(3)=2 < 5. res=3, lo=4.
* lo=4, hi=4 -> mid=4. suff.get(4)=2 < 5. res=4, lo=5.
* Loop ends. res = 4. ans.set(1, 4).
*
* - i = 2, arr[2] = 1:
* Binary search on suff[3...4]. Target: find `j` where suff.get(j) < 1.
* No such j exists. res remains -1. ans.set(2, -1).
*
* - i = 3, arr[3] = 3:
* Binary search on suff[4...4]. Target: find `j` where suff.get(j) < 3.
* lo=4, hi=4 -> mid=4. suff.get(4)=2 < 3. res=4, lo=5.
* Loop ends. res = 4. ans.set(3, 4).
*
* - i = 4, arr[4] = 2:
* Search range is empty. ans.set(4, -1).
*
* Final Answer: [2, 4, -1, 4, -1]
*
*/
```
---

## Key Insights

The problem becomes much simpler once we change our perspective. Instead of asking "for `arr[i]`, what is the farthest smaller element?", we can ask "for `arr[i]`, what is the farthest point `j` where the *minimum* from `j` onwards is smaller than `arr[i]`?".

The **suffix minimum array** provides this information efficiently. Its non-increasing (sorted) nature is the key property that unlocks the O(log N) binary search, leading to an overall O(N log N) solution.

---

## Further Exploration

-   [Next Greater Element](https://www.geeksforgeeks.org/problems/next-larger-element-1587115620/1)
-   [Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) (Similar concept using a monotonic stack)

---

## References

-   **Original Problem:** [GeeksforGeeks - Farthest Smaller Right](https://www.geeksforgeeks.org/problems/farthest-smaller-right/1)
-   **Binary Search:** [GeeksforGeeks - Binary Search](https://www.geeksforgeeks.org/binary-search/)

---

## Author

<p align="left">
  <a href="https://github.com/imnilesh18" target="_blank">
    <img src="https://img.shields.io/badge/GitHub-imnilesh18-blue?style=for-the-badge&logo=github" alt="GitHub - imnilesh18">
  </a>
</p>

---

## Tags

<div>
  <img src="https://img.shields.io/badge/Array-282C34?style=for-the-badge" alt="Array">
  <img src="https://img.shields.io/badge/Binary Search-282C34?style=for-the-badge" alt="Binary Search">
  <img src="https://img.shields.io/badge/Suffix Array-282C34?style=for-the-badge" alt="Suffix Array">
  <img src="https://img.shields.io/badge/GeeksforGeeks-282C34?style=for-the-badge" alt="GeeksforGeeks">
</div>

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**Note:** This is an educational repository. The code is intended for learning and reference purposes. It is not recommended to use this code in production environments without further testing and modification.