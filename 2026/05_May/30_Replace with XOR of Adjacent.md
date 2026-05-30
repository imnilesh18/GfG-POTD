# 🟢 Replace with XOR of Adjacent

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/replace-with-xor-of-adjacent/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Accuracy-75.8%25-blue?style=for-the-badge" alt="Accuracy: 75.8%" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points: 2" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` of `n` integers, modify the array **in-place** such that each element is replaced with the **XOR** of its adjacent elements.

- For the **first element**, update `arr[0] = arr[0] ^ arr[1]`.
- For the **last element**, update `arr[n-1] = arr[n-2] ^ arr[n-1]`.
- For **all other elements**, update `arr[i] = arr[i-1] ^ arr[i+1]`.

*Note: Here, `a ^ b` represents the bitwise XOR operation between `a` and `b`.*

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [2, 1, 4, 7]
Output: [3, 6, 6, 3]
```
<details>
<summary>📖 Example Breakdown</summary>

- **At index 0**: `arr[0] ^ arr[1]` = `2 ^ 1` = **3**
- **At index 1**: Original `arr[0] ^ arr[2]` = `2 ^ 4` = **6**
- **At index 2**: Original `arr[1] ^ arr[3]` = `1 ^ 7` = **6**
- **At index 3**: Original `arr[2] ^ arr[3]` = `4 ^ 7` = **3**

Thus, the updated array becomes `[3, 6, 6, 3]`.
</details>

### Example 2
```text
Input: arr[] = [5, 9, 2, 6, 7]
Output: [12, 7, 15, 5, 1]
Explanation:
- arr[0] = 5 ^ 9 = 12
- arr[1] = 5 ^ 2 = 7
- arr[2] = 9 ^ 6 = 15
- arr[3] = 2 ^ 7 = 5
- arr[4] = 6 ^ 7 = 1
```

---

## 🛑 Constraints

- `2 ≤ n ≤ 10^5`
- `1 ≤ arr[i] ≤ 10^7`

---

## 💻 Solution Approach

### Optimized In-Place Approach

**Brief Intuition:**
When updating the array in-place, an element's original value is overwritten and lost. However, the *next* adjacent element strictly requires that original value for its XOR computation. By temporarily storing the previous original value in a single variable (`prev`), we can prevent the need for an entire $O(n)$ auxiliary array.

```cpp
// Intuition: When updating the array in-place, an element's original value is lost once modified, but the next adjacent element needs that original value for its XOR computation. By simply holding the previous original value in a temporary variable, we can avoid using an entire auxiliary array.
// Approach: Store the original first element in a variable 'prev' and update the first element. Iterate through the array from the second element to the second-to-last element. At each step, save the current element, update it using 'prev' XORed with the next element, and then update 'prev' to the saved current element. Finally, calculate the last element using 'prev' and its current value.
// Time Complexity: O(n) as we iterate through the array of size n exactly once.
// Space Complexity: O(1) because we only use a few extra variables for temporary tracking.

class Solution {
  public:
    void replaceElements(vector<int>& arr) {
        int n = arr.size();
        
        int prev = arr[0]; // Store original first element
        
        arr[0] = arr[0] ^ arr[1]; // Update first element
        
        for (int i = 1; i < n - 1; i++) {
            int curr = arr[i]; // Keep original current element
            arr[i] = prev ^ arr[i+1]; // Update current element using original adjacent values
            prev = curr; // Shift prev forward for the next iteration
        }
        
        arr[n-1] = prev ^ arr[n-1]; // Update last element
    }
};

/*
*
* Dry Run
*
* Input: arr = [2, 1, 4, 7]
* * n = 4
* Initial array: 2, 1, 4, 7
* * Initialization step:
* prev = arr[0] = 2
* arr[0] = arr[0] ^ arr[1] = 2 ^ 1 = 3
* Array state: 3, 1, 4, 7
* * Loop i = 1:
* curr = arr[1] = 1
* arr[1] = prev ^ arr[2] = 2 ^ 4 = 6
* prev = curr = 1
* Array state: 3, 6, 4, 7
* * Loop i = 2:
* curr = arr[2] = 4
* arr[2] = prev ^ arr[3] = 1 ^ 7 = 6
* prev = curr = 4
* Array state: 3, 6, 6, 7
* * Loop terminates as i must be less than 3
* * Final update step:
* arr[3] = prev ^ arr[3] = 4 ^ 7 = 3
* Array state: 3, 6, 6, 3
* * Output: [3, 6, 6, 3]
*
*/
```

---

## 🔑 Key Insights

- **State Retention:** Utilizing a single variable (`prev`) effectively caches the state of the "past" index, ensuring data integrity without extra space.
- **In-Place Modification:** The problem requires `O(1)` space complexity which is strictly honored by iterating forward and immediately overriding the used elements.
- **Edge Cases:** The boundary elements (`i=0` and `i=n-1`) inherently only have one adjacent element, which is cleanly handled outside the main logic loop.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might want to try these related concepts:
- **Bit Magic / XOR logic:** "Find the Missing Number", "Single Number"
- **In-Place Array Manipulations:** "Move Zeroes", "Rotate Array"

---

## 🔗 References

- **GeeksforGeeks Problem:** [Replace with XOR of Adjacent](https://www.geeksforgeeks.org/problems/replace-with-xor-of-adjacent/1)
- **Bitwise Operators:** [Understanding XOR](https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/)

---

## ✍️ Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#arrays` `#bit-manipulation` `#xor` `#in-place` `#geeksforgeeks` `#cpp`