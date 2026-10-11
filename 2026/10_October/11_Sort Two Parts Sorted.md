# 🧩 Sort Two Parts Sorted

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Accuracy-50.0%25-blue?style=for-the-badge" alt="Accuracy: 50.0%" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points: 2" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an integer array `arr[]` where the two parts around a break point are individually sorted, merge them into a single sorted array. The break point can be anywhere in the array, including at the beginning or end.

---

## 💡 Examples

```text
Input: arr[] = [2, 3, 8, -1, 7, 10]
Output: [-1, 2, 3, 7, 8, 10]
Explanation: [2, 3, 8] and [-1, 7, 10] are sorted in the original array. The overall sorted version is [-1 2 3 7 8 10].
```

```text
Input: arr[] = [-4, 6, 9, -1, 3]
Output: [-4, -1, 3, 6, 9]
Explanation: [-4, 6, 9] and [-1, 3] are sorted in the original array. The overall sorted version is [-4 -1 3 6 9].
```

```text
Input: arr[] = [10, 20, 30]
Output: [10, 20, 30]
Explanation: One part is empty and the other part is whole array which is already sorted.
```

<details>
<summary>📖 Example Breakdown (Walkthrough)</summary>

**Given Array:** `[2, 3, 8, -1, 7, 10]`

1. **Identify the break point:** Iterate through the array to find where the sorted order drops. 
   - Element `8` is greater than `-1`, so the drop happens at index `2`.
   - The first sorted half is `[2, 3, 8]` (indices `0` to `2`).
   - The second sorted half is `[-1, 7, 10]` (indices `3` to `5`).
2. **Merge using two pointers:**
   - Pointer 1 (`p1`) starts at index `0`.
   - Pointer 2 (`p2`) starts at index `3`.
   - Compare `arr[p1]` and `arr[p2]`, place the smaller one in a temporary array, and move the corresponding pointer.
   - Sequence of placement: `-1`, `2`, `3`, `7`, `8`, `10`.
3. **Copy back:** Overwrite the original array with the temporary array.
</details>

---

## ⚠️ Constraints

> - $1 \le arr.size() \le 10^6$
> - $-10^5 \le arr[i] \le 10^5$

---

## 🚀 Solution Approaches

### Optimized Approach: Two-Pointer Merge

**Brief Summary:**
Since the array is comprised of two contiguous sorted subarrays, we can locate the exact point where the first subarray ends. Once we have the bounds for both halves, we can merge them in linear time into a temporary array using the classic two-pointer merge algorithm (similar to the merge step in Merge Sort) and then copy the sorted result back.

```cpp
// Intuition: The array consists of two individually sorted segments. By finding the break point where the sorting order drops, we can treat this as merging two sorted arrays into one, which is efficiently done using two pointers.
// Approach: First, traverse the array to find the index `break_idx` where an element is strictly greater than the next one. If no such index exists, it's already sorted. Otherwise, initialize two pointers for the start of both halves. Compare elements at both pointers, copying the smaller one into a temporary array. Finally, append any remaining elements and copy the temporary array back to the original array.
// Time Complexity: O(n) where n is the size of the array. Finding the break point takes O(n) time, and merging the two halves takes exactly O(n) time.
// Space Complexity: O(n) because a temporary array of size n is required to store the merged elements before updating the original array.

class Solution {
  public:
    void mergeTwoParts(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return;

        // Step 1: Find the break point where order drops
        int break_idx = -1;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                break_idx = i;
                break;
            }
        }

        // If no break point exists, the array is already sorted
        if (break_idx == -1) return;

        // Step 2: Merge the two sorted halves
        vector<int> temp(n);
        int p1 = 0;                   // Pointer for the first half
        int p2 = break_idx + 1;       // Pointer for the second half
        int k = 0;                    // Pointer for the temporary array

        // Compare and place smaller elements in temp
        while (p1 <= break_idx && p2 < n) {
            if (arr[p1] <= arr[p2]) {
                temp[k++] = arr[p1++];
            } else {
                temp[k++] = arr[p2++];
            }
        }

        // Copy any remaining elements from the first half
        while (p1 <= break_idx) {
            temp[k++] = arr[p1++];
        }

        // Copy any remaining elements from the second half
        while (p2 < n) {
            temp[k++] = arr[p2++];
        }

        // Step 3: Copy the merged result back to the original array
        arr = temp;
    }
};

/*
*
* Dry Run
*
Input: arr = [2, 3, 8, -1, 7, 10]
n = 6

Step 1: Find break point
arr[2] (8) > arr[3] (-1) -> break_idx = 2

Step 2: Merge
temp array size 6 created
p1 = 0, p2 = 3, k = 0

Comparisons:
arr[0] (2) > arr[3] (-1) => temp[0] = -1, p2 = 4, k = 1
arr[0] (2) <= arr[4] (7) => temp[1] = 2, p1 = 1, k = 2
arr[1] (3) <= arr[4] (7) => temp[2] = 3, p1 = 2, k = 3
arr[2] (8) > arr[4] (7) => temp[3] = 7, p2 = 5, k = 4
arr[2] (8) <= arr[5] (10) => temp[4] = 8, p1 = 3, k = 5

First half pointer (p1) exceeds break_idx.
Remaining elements from second half:
temp[5] = arr[5] (10), p2 = 6, k = 6

Step 3: Copy back
arr becomes [-1, 2, 3, 7, 8, 10]
*/
```

---

## 🧠 Key Insights

- Standard sorting algorithms take $O(N \log N)$ time, but because the two partitions are already sorted internally, taking advantage of the structural property reduces the time complexity to $O(N)$.
- The core logic is practically identical to the final `merge()` subroutine of the classic Merge Sort algorithm.

---

## 🔍 Further Exploration

- **Merge Sort:** Understanding the divide-and-conquer strategy will solidify how this merge step fits into a larger algorithm.
- **Merge Two Sorted Arrays:** A similar problem that deals with merging two completely separate sorted arrays rather than halves of the same array.
- **Search in a Rotated Sorted Array:** Another excellent problem testing how to navigate arrays that have a break point.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Sort Two Parts Sorted](https://www.geeksforgeeks.org/problems/sort-the-half-sorted2157/1)

---

## 👨‍💻 Author

**Nilesh Kumar**
- GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`two-pointer-algorithm` `Sorting` `Merge Sort` `Arrays` `geeksforgeeks` `cpp`