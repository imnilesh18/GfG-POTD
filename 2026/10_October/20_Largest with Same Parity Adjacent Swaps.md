# 🟧 Largest with Same Parity Adjacent Swaps

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/even-swap/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-57.01%25-green?style=for-the-badge" alt="Accuracy: 57.01%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]`, you are allowed to swap two adjacent elements, `arr[i]` and `arr[i + 1]` **only if their sum is even**. Find the **lexicographically largest array** that can be obtained by performing this operation any number of times, including zero times.

> **Note:** An array X is lexicographically larger than another array Y if, at the first position where they differ, X has the larger element.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [1, 3, 5]
Output: [5, 3, 1]
Explanation: We can swap any adjacent pair as all have even sum. All possible obtainable arrays are [1, 3, 5], [1, 5, 3], [3, 1, 5], [3, 5, 1], [5, 1, 3] and [5, 3, 1]. The array [5, 3, 1] is lexicographically largest.
```

### Example 2
```text
Input: arr[] = [1, 3, 4, 2]
Output: [3, 1, 4, 2]
Explanation: [1, 3, 4, 2], [1, 3, 2, 4], [3, 1, 2, 4] and [3, 1, 4, 2] are all possible, among which the last one is the lexicographically largest one.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>
<br>

Consider `arr[] = [1, 3, 4, 2]`:
1. Look at `[1, 3]`. Both are odd. Sum is `1 + 3 = 4` (even). They share the same parity. We can swap them to `[3, 1]`.
2. Look at `[4, 2]`. Both are even. Sum is `4 + 2 = 6` (even). They share the same parity. We can swap them to `[4, 2]`.
3. Notice that `1` (odd) and `4` (even) cannot be swapped because `1 + 4 = 5` (odd). The parity boundaries break the array into independent segments.
4. Segments are: `[1, 3]` and `[4, 2]`.
5. Sort each segment descending: `[3, 1]` and `[4, 2]`.
6. Final array: `[3, 1, 4, 2]`.

</details>

---

## ⚠️ Constraints

- `1 ≤ arr.size() ≤ 10^5`
- `0 ≤ arr[i] ≤ 10^5`
- Array may contain duplicate elements.

---

## 🚀 Solution Approaches

### Optimized Approach (In-place Sorting by Parity Group)

**Intuition:** 
Two elements can only result in an even sum if they share the exact same parity (both are even, or both are odd). Because we can repeatedly swap any adjacent elements with the same parity, any contiguous subarray consisting entirely of odd numbers (or entirely of even numbers) can be freely rearranged into any permutation. To make the array lexicographically largest, we just need to identify these contiguous single-parity blocks and sort each block in descending order.

```cpp
// Intuition: Adjacent elements can only yield an even sum if they have the same parity (both even or both odd). Thus, any contiguous block of the same parity can be rearranged freely. To maximize lexicographical order, we sort these blocks descending.
// Approach: Iterate through the array to find contiguous segments of elements with the same parity. Once a segment is identified, sort it in descending order, then move to the next segment.
// Time Complexity: O(n log n) since in the worst case (all elements having the same parity), we sort the entire array once.
// Space Complexity: O(1) auxiliary space as sorting is done in-place (excluding recursive stack space of the sorting algorithm).
class Solution {
public:
    vector<int> lexicographicallyLargest(vector<int> &arr) {
        int n = arr.size();
        int i = 0; // Pointer to track the start of a parity segment
        
        while (i < n) {
            int j = i; // Pointer to find the end of the current parity segment
            
            // Expand segment while adjacent elements share the same parity
            while (j + 1 < n && (arr[j] % 2) == (arr[j + 1] % 2)) {
                j++;
            }
            
            // Sort the identified contiguous segment in descending order
            sort(arr.begin() + i, arr.begin() + j + 1, greater<int>());
            
            // Move pointer to the start of the next segment
            i = j + 1;
        }
        
        return arr;
    }
};

/*
*
* Dry Run
* Input: arr = [1, 3, 4, 2]
* n = 4, i = 0, j = 0
* Loop 1: arr[0] is 1, arr[1] is 3. Same parity (odd). j becomes 1.
*         arr[1] is 3, arr[2] is 4. Different parity. Inner loop breaks.
*         Sort segment arr[0..1] -> [1, 3] becomes [3, 1].
*         Array is now [3, 1, 4, 2]. i moves to 2.
* Loop 2: i = 2, j = 2. arr[2] is 4, arr[3] is 2. Same parity (even). j becomes 3.
*         Sort segment arr[2..3] -> [4, 2] remains [4, 2].
*         Array is now [3, 1, 4, 2]. i moves to 4.
* Loop ends (i = 4 is not < n).
* Output: [3, 1, 4, 2]
*
*/
```

---

## 🧠 Key Insights
- **Parity Isolation:** An even number and an odd number can never be swapped. This acts as an invisible "wall" between segments of different parities.
- **Independent Sorting:** Because we can swap adjacent elements indefinitely within a parity boundary, it perfectly simulates the Bubble Sort mechanism. Therefore, we can completely sort the sub-segment.

---

## 🔗 References
- **Problem Link:** [GeeksforGeeks - Even Swap](https://www.geeksforgeeks.org/problems/even-swap/1)
- **Related Topics:** Arrays, Sorting, Two-Pointer technique.

---

## 👨‍💻 Author

**Nilesh Kumar**
- GitHub: [@imnilesh18](https://github.com/imnilesh18)
- Platform Profile: [LeetGeek / GeeksforGeeks](https://github.com/imnilesh18)

---

## 🏷️ Tags
`#array` `#sorting` `#two-pointers` `#geeksforgeeks` `#c++`