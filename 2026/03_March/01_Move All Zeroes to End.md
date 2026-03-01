# 🟢 Move All Zeroes to End

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/move-all-zeroes-to-end-of-array0751/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty" />
    <img src="https://img.shields.io/badge/Accuracy-45.51%25-green?style=for-the-badge" alt="Accuracy" />
    <img src="https://img.shields.io/badge/Points-2-blue?style=for-the-badge" alt="Points" />
    <img src="https://img.shields.io/badge/License-MIT-orange?style=for-the-badge" alt="License" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

You are given an array `arr[]` of non-negative integers. You have to move all the zeros in the array to the right end while maintaining the relative order of the non-zero elements. 

The operation must be performed **in place**, meaning you should not use extra space for another array.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [1, 2, 0, 4, 3, 0, 5, 0]
Output: [1, 2, 4, 3, 5, 0, 0, 0]
Explanation: There are three 0s that are moved to the end.
```

### Example 2
```text
Input: arr[] = [10, 20, 30]
Output: [10, 20, 30]
Explanation: No change in array as there are no 0s.
```

### Example 3
```text
Input: arr[] = [0, 0]
Output: [0, 0]
Explanation: No change in array as there are all 0s.
```

<details>
<summary>📖 <b>Example Breakdown (Example 1)</b></summary>

1. **Initial state:** `[1, 2, 0, 4, 3, 0, 5, 0]`, `nonZeroIdx = 0`
2. **i = 0 (`1`):** Non-zero. Swap with `arr[nonZeroIdx]`. Array: `[1, 2, 0, 4, 3, 0, 5, 0]`. `nonZeroIdx = 1`
3. **i = 1 (`2`):** Non-zero. Swap with `arr[nonZeroIdx]`. Array: `[1, 2, 0, 4, 3, 0, 5, 0]`. `nonZeroIdx = 2`
4. **i = 2 (`0`):** Zero. Ignore. `nonZeroIdx = 2`
5. **i = 3 (`4`):** Non-zero. Swap with `arr[nonZeroIdx]`. Array: `[1, 2, 4, 0, 3, 0, 5, 0]`. `nonZeroIdx = 3`
6. **i = 4 (`3`):** Non-zero. Swap with `arr[nonZeroIdx]`. Array: `[1, 2, 4, 3, 0, 0, 5, 0]`. `nonZeroIdx = 4`
7. **i = 5 (`0`):** Zero. Ignore. `nonZeroIdx = 4`
8. **i = 6 (`5`):** Non-zero. Swap with `arr[nonZeroIdx]`. Array: `[1, 2, 4, 3, 5, 0, 0, 0]`. `nonZeroIdx = 5`
9. **i = 7 (`0`):** Zero. Ignore.

**Final Array:** `[1, 2, 4, 3, 5, 0, 0, 0]`

</details>

---

## ⚠️ Constraints

- `1 <= arr.size() <= 10^5`
- `0 <= arr[i] <= 10^5`

---

## 🛠️ Solution Approaches

### Optimized Approach: Two Pointers

This approach uses a two-pointer technique to modify the array in a single pass without any extra space.

```cpp
// Intuition: We can use a "two-pointer" technique where one pointer iterates through the array and another tracks the position where the next non-zero element should go.
// Approach: Maintain a pointer 'nonZeroIdx' starting at 0. Iterate through the array with a loop variable 'i'. Whenever arr[i] is non-zero, swap it with arr[nonZeroIdx] and increment 'nonZeroIdx'. This naturally pushes all non-zeros to the front and shifts zeros to the end.
// Time Complexity: O(N) because we traverse the array of size N exactly once.
// Space Complexity: O(1) as the swaps are performed in-place without using extra array space.

class Solution {
  public:
    void pushZerosToEnd(vector<int>& arr) {
        // Tracks target index for the next non-zero element
        int nonZeroIdx = 0; 
        
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] != 0) { 
                // Found a non-zero element, move it to the correct front position
                swap(arr[i], arr[nonZeroIdx]); 
                // Advance the target index for the next swap
                nonZeroIdx++; 
            }
        }
    }
};

/*
*
* Dry Run
*
* Input: arr = [1, 2, 0, 4]
* Variables: nonZeroIdx = 0, i = 0
* * Initialization:
* nonZeroIdx = 0
* * Iteration for i = 0:
* arr[0] is 1 (non-zero)
* Swap arr[0] and arr[nonZeroIdx] -> Swap(1, 1)
* Array remains [1, 2, 0, 4]
* nonZeroIdx becomes 1
* * Iteration for i = 1:
* arr[1] is 2 (non-zero)
* Swap arr[1] and arr[nonZeroIdx] -> Swap(2, 2)
* Array remains [1, 2, 0, 4]
* nonZeroIdx becomes 2
* * Iteration for i = 2:
* arr[2] is 0 (zero)
* Ignore and continue
* Array remains [1, 2, 0, 4]
* * Iteration for i = 3:
* arr[3] is 4 (non-zero)
* Swap arr[3] and arr[nonZeroIdx] -> Swap(4, 0)
* Array becomes [1, 2, 4, 0]
* nonZeroIdx becomes 3
* * Loop ends.
* Final output: [1, 2, 4, 0]
*
*/
```

---

## 🧠 Key Insights

* **In-place Sorting:** By using the fast-runner (`i`) and slow-runner (`nonZeroIdx`) two-pointer approach, we avoid the need for creating a secondary array.
* **Relative Order Preservation:** Since we process the array sequentially and only swap the current non-zero element into the next available safe spot, the original order of non-zero elements is perfectly retained.
* **Self-Swapping:** When no zeros have been encountered yet, the algorithm simply swaps the element with itself, which acts as a harmless no-op.

---

## 🔗 Further Exploration
If you enjoyed this problem, you might also like:
* **Remove Duplicates from Sorted Array** - Another fundamental two-pointer array manipulation problem.
* **Sort an Array of 0s, 1s, and 2s (Dutch National Flag Algorithm)** - Extends the multi-pointer strategy to partition elements.
* **Move Zeroes (LeetCode 283)** - The exact same problem variation found on LeetCode.

---

## 📚 References
* [GeeksforGeeks: Move All Zeroes to End](https://www.geeksforgeeks.org/problems/move-all-zeroes-to-end-of-array0751/1)
* C++ `std::swap` documentation.

---

## 🧑‍💻 Author
* [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
![Arrays](https://img.shields.io/badge/Arrays-black?style=for-the-badge&logo=codeforces&logoColor=white)
![Two Pointers](https://img.shields.io/badge/Two_Pointers-black?style=for-the-badge&logo=codeforces&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data_Structures-black?style=for-the-badge&logo=codeforces&logoColor=white)
![Algorithms](https://img.shields.io/badge/Algorithms-black?style=for-the-badge&logo=codeforces&logoColor=white)