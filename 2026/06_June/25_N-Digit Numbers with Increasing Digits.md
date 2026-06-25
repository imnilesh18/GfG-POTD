<div align="center">
  
# 📈 N-Digit Numbers with Increasing Digits

[![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/n-digit-numbers-with-digits-in-increasing-order5903/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)]()
[![Accuracy](https://img.shields.io/badge/Accuracy-49.66%25-green?style=for-the-badge)]()
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

---

### ⚠️ Educational Use Only
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

Given an integer `n`, return all the `n` digit numbers in increasing order, such that their digits are in **strictly increasing order** (from left to right).

---

## 💡 Examples

```text
Input: n = 1
Output: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
Explanation: Single digit numbers are considered to be strictly increasing order.
```

```text
Input: n = 2
Output: [12, 13, 14, 15, 16, 17, 18, 19, 23....79, 89]
Explanation: For n = 2, the correct sequence is 12, 13, 14, 15, 16, 17, 18, 19, 23 and so on up to 89.
```

```text
Input: n = 15
Output: []
Explanation: No such number exist (since we only have 9 non-zero digits, a strictly increasing number can't exceed length 9).
```

<details>
<summary><strong>📖 Example Breakdown (n = 2)</strong></summary>

1. **Step 1:** We start by placing digits `1` through `8` at the first position. (We can't start with `9` since no digit is greater than `9`).
2. **Step 2:** For each starting digit, we recursively append all possible larger digits.
   * Start with `1` ➔ Append `2` to `9` ➔ `[12, 13, ..., 19]`
   * Start with `2` ➔ Append `3` to `9` ➔ `[23, 24, ..., 29]`
   * ...
   * Start with `8` ➔ Append `9` ➔ `[89]`
3. **Result:** Concatenate all valid outcomes.

</details>

---

## ⚙️ Constraints

> - `1 ≤ n ≤ 10^5`

*(Note: While `n` can go up to `10^5`, any length `n > 9` will naturally yield an empty array because there are only 9 non-zero digits available to form a strictly increasing sequence).*

---

## 🚀 Solution Approaches

### 1. Generating Valid Numbers Directly (Optimized Recursion)

**Brief Intuition:** Instead of checking every number from $10^{n-1}$ to $10^n - 1$ (which would be catastrophically slow), we can construct valid numbers dynamically. We build numbers digit by digit using recursion. By ensuring that every newly chosen digit is strictly greater than the previously chosen digit, the strictly increasing property is automatically maintained. 

**Code Implementation (C++):**

```cpp
// Intuition: To generate n-digit numbers with strictly increasing digits, we can build them incrementally. We start with a valid first digit and recursively append greater digits until the number reaches length 'n'.
// Approach: If n == 1, 0 is a valid number, so handle it separately. For n > 1, iterate from 1 to 9 as the first digit. Use a recursive function to append strictly larger digits mathematically. Once the built number has length 'n', save it to the result array.
// Time Complexity: O(C(9, n)), where C is the combinations of 9 digits taken n at a time. The recursion only builds valid increasing combinations directly without exploring invalid branches.
// Space Complexity: O(n) for the recursive call stack depth, plus the space required to store the valid combinations in the resultant vector.

class Solution {
private:
    void solve(int length, int num, int last_digit, int n, vector<int>& result) {
        // Base case: check if we reached the required length
        if (length == n) {
            result.push_back(num);
            return;
        }
        
        // Try appending all valid digits greater than the last_digit
        for (int i = last_digit + 1; i <= 9; ++i) {
            solve(length + 1, num * 10 + i, i, n, result);
        }
    }
    
public:
    vector<int> increasingNumbers(int n) {
        vector<int> result;
        
        // Handle single digit edge case (includes 0)
        if (n == 1) {
            for (int i = 0; i <= 9; ++i) {
                result.push_back(i);
            }
            return result;
        }
        
        // For n > 1, start building the numbers from digits 1 to 9
        for (int i = 1; i <= 9; ++i) {
            solve(1, i, i, n, result);
        }
        
        return result;
    }
};

/*
*
* Dry Run
* Input: n = 2
* n is 2, not 1, so we skip the n=1 loop.
* First loop: Start building numbers from digits 1 to 9.
* * - Call solve(length=1, num=1, last_digit=1, n=2):
* length(1) != n(2). Loop 'i' from last_digit+1 (2) to 9:
* -> i=2: call solve(2, 1*10+2=12, 2, 2) -> length==n, add 12.
* -> i=3: call solve(2, 1*10+3=13, 3, 2) -> length==n, add 13.
* ...
* -> i=9: call solve(2, 1*10+9=19, 9, 2) -> length==n, add 19.
* * - Call solve(length=1, num=2, last_digit=2, n=2):
* length(1) != n(2). Loop 'i' from last_digit+1 (3) to 9:
* -> i=3: call solve(2, 2*10+3=23, 3, 2) -> length==n, add 23.
* ...
* * Process continues up to the digit 8:
* - Call solve(length=1, num=8, last_digit=8, n=2):
* -> i=9: call solve(2, 8*10+9=89, 9, 2) -> length==n, add 89.
* * Final result vector contains all sequences sequentially: [12, 13, ..., 89]
*
*/
```

---

## 🧠 Key Insights

- **Mathematical Generation:** Building numbers mathematically (`num * 10 + i`) is much faster and more memory-efficient than performing string manipulations.
- **Combination Constraints:** The maximum length of a strictly increasing number constructed from base-10 digits is 9 (e.g., `123456789`). If `n > 9`, the `for` loops inherently fail to execute, properly returning an empty array without causing index out-of-bounds or infinite recursion errors.
- **Edge Case Execution:** `n = 1` uniquely allows the digit `0`, which is correctly isolated in the primary function logic. 

---

## 🔍 Further Exploration

If you enjoyed exploring recursive number generation, consider these similar challenges to build your mastery:
- **Lexicographical Numbers:** Sorting numbers digit-by-digit recursively.
- **Valid Combinations & Permutations:** Implementing backtracking templates to find specific subsets.
- **Letter Combinations of a Phone Number:** Recursively decoding digit strings to character variations.

---

## 🔗 References

- **GeeksForGeeks Problem:** [N-Digit Numbers with Increasing Digits](https://www.geeksforgeeks.org/problems/n-digit-numbers-with-digits-in-increasing-order5903/1)
- **Concept Reference:** [Backtracking Algorithms](https://www.geeksforgeeks.org/backtracking-algorithms/)

---

## 👨‍💻 Author

**Nilesh** [![GitHub](https://img.shields.io/badge/GitHub-imnilesh18-181717?style=for-the-badge&logo=github)](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#DynamicProgramming` `#Recursion` `#Backtracking` `#Math` `#GeeksForGeeks` `#Algorithms`