# 🟧 Sort by Set Bit Count

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-29A155?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-green?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-36.7%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-yellow?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/sort-by-set-bit-count1153/1).



</div>

---

## 📝 Problem Statement
Given an array `arr[]` of integers, your task is to sort the array in descending order according to the count of set bits (1s) in the binary representation of the array elements.

**Note:** If two integers have the same number of set bits, their relative order from the original array must be preserved (i.e., use a **stable sort**).

---

## 📖 Examples

### Example 1
**Input:** `arr[] = [5, 2, 3, 9, 4, 6, 7, 15, 32]`  
**Output:** `[15, 7, 5, 3, 9, 6, 2, 4, 32]`  

<details>
<summary>📖 Example Breakdown</summary>

Binary representations:
- 15 (1111) -> 4 bits
- 7 (0111) -> 3 bits
- 5 (0101) -> 2 bits
- 3 (0011) -> 2 bits
- 9 (1001) -> 2 bits
- 6 (0110) -> 2 bits
- 2 (0010) -> 1 bit
- 4 (0100) -> 1 bit
- 32 (10000) -> 1 bit

Sorting these by count (descending) while keeping ties in original order results in: `[15, 7, 5, 3, 9, 6, 2, 4, 32]`.
</details>

---

## ⚠️ Constraints
- `1 ≤ arr.size() ≤ 10^5`
- `1 ≤ arr[i] ≤ 10^6`

---

## 🚀 Solution Approach

### Optimized Approach (Stable Sort)
- **Intuition:** We need to sort elements by their set bit count in descending order while preserving the original relative order for ties, which perfectly aligns with the use case of a stable sort.
- **Approach:** Use C++ `std::stable_sort` with a custom lambda comparator. The comparator uses `__builtin_popcount` to efficiently count the set bits of two numbers and places the one with more set bits first.
- **Time Complexity:** $O(n \log n)$ where $n$ is the number of elements in the array, standard for `std::stable_sort`.
- **Space Complexity:** $O(1)$ auxiliary space, ignoring the $O(n)$ memory sometimes allocated internally by `std::stable_sort` for merging.

```cpp
class Solution {
  public:
    vector<int> sortBySetBitCount(vector<int>& arr) {
        // Use stable_sort to maintain relative order of equal elements
        stable_sort(arr.begin(), arr.end(), [](int a, int b) {
            // Compare set bits using built-in popcount function
            return __builtin_popcount(a) > __builtin_popcount(b);
        });
        
        // Return the modified array
        return arr;
    }
};
```

---

### 🧪 Dry Run
```text
/*
* Dry Run
* Input: arr = [5, 2, 3, 9]
*
* Initial state: [5, 2, 3, 9]
*
* Calculate set bits:
* 5 (0101) -> 2 set bits
* 2 (0010) -> 1 set bit
* 3 (0011) -> 2 set bits
* 9 (1001) -> 2 set bits
*
* Sorting based on set bits (descending):
* Elements with 2 bits: 5, 3, 9
* Elements with 1 bit: 2
*
* Maintaining stable order for elements with 2 bits:
* 5 comes before 3, 3 comes before 9.
*
* Output: [5, 3, 9, 2]
*/
```

---

## 💡 Key Insights
- **`__builtin_popcount(n)`**: A highly optimized compiler intrinsic in GCC to count the number of set bits in an integer.
- **Stability**: `std::stable_sort` is crucial here because the problem explicitly requires maintaining the original relative order for elements with an equal number of set bits.

---

## 🔗 References
- [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/sort-by-set-bit-count1153/1)
- [C++ std::stable_sort Documentation](https://en.cppreference.com/w/cpp/algorithm/stable_sort)

---

## 👤 Author
Created by [imnilesh18](https://github.com/imnilesh18).

---

## 🏷️ Tags
`#dynamic-programming` `#sorting` `#bit-manipulation` `#geeksforgeeks`