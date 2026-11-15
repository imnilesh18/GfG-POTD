# 🟢 Sum of All Digit Subsequences

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/sum-of-all-sub-sequences-of-a-number3437/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-52.22%25-blue?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**  
> This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the GeeksforGeeks problem. 

---

## 📋 Problem Statement

Given a string `s` which consists of digits, find the **sum of all digits across all non-empty subsequences** of `s`. 

> **Note:** Since the answer can be very large, return it modulo $10^9 + 7$. 

---

## 🧪 Examples

### Example 1
```text
Input: s = "123"
Output: 24
Explanation: The non-empty subsequences are: [1], [2], [3], [1, 2], [1, 3], [2, 3], [1, 2, 3]. 
The sum of all digits in these subsequences is: 
1 + 2 + 3 + (1 + 2) + (1 + 3) + (2 + 3) + (1 + 2 + 3) = 24.
```

### Example 2
```text
Input: s = "405"
Output: 36
Explanation: The non-empty subsequences are: [4], [0], [5], [4, 0], [4, 5], [0, 5], [4, 0, 5]. 
The sum of all digits in these subsequences is 36.
```

<details>
<summary><b>📖 Example Breakdown (Walkthrough for <code>s = "123"</code>)</b></summary>

1. **String Length ($n$):** `3` (digits are `'1'`, `'2'`, `'3'`). 
2. **Total Non-Empty Subsequences:** $2^3 - 1 = 7$ subsequences: `[1]`, `[2]`, `[3]`, `[1, 2]`, `[1, 3]`, `[2, 3]`, `[1, 2, 3]`. 
3. **Frequency of Each Digit:**
   - `'1'` appears in `[1]`, `[1, 2]`, `[1, 3]`, `[1, 2, 3]` $\rightarrow$ **4 times** ($2^{3-1} = 2^2 = 4$). 
   - `'2'` appears in `[2]`, `[1, 2]`, `[2, 3]`, `[1, 2, 3]` $\rightarrow$ **4 times** ($2^{3-1} = 2^2 = 4$). 
   - `'3'` appears in `[3]`, `[1, 3]`, `[2, 3]`, `[1, 2, 3]` $\rightarrow$ **4 times** ($2^{3-1} = 2^2 = 4$). 
4. **Total Sum Calculation:**
   $$\text{Total Sum} = (1 + 2 + 3) \times 2^{3-1} = 6 \times 4 = 24$$
 

</details>

---

## 🔒 Constraints

> - $1 \le \text{s.size()} \le 10^5$ 
> - `s` consists only of digits `(1 - 9)` 

**Expected Complexities:**
- **Time Complexity:** $\mathcal{O}(\vert{}s\vert{})$ 
- **Auxiliary Space:** $\mathcal{O}(1)$ 

---

## 💡 Solution Approaches

### 🚀 Optimized Approach: Combinatorics & Symmetry

#### Intuition
Generating all $2^n - 1$ non-empty subsequences explicitly takes $\mathcal{O}(n \cdot 2^n)$ time, which will time out for $n \le 10^5$.  Instead of building subsequences, we count how many times each individual digit contributes to the final sum. For a string of length $n$, every character has two choices when forming a subsequence (either included or excluded). Fixing a specific digit at index $i$ as *included*, the remaining $n - 1$ characters can be chosen in $2^{n - 1}$ ways. Therefore, every digit in `s` appears in **exactly $2^{n - 1}$** non-empty subsequences.

#### C++ Implementation

```cpp
// Intuition: Each digit in a string of length n appears in exactly 2^(n-1) non-empty subsequences. Thus, the total sum is (sum of all digits) * 2^(n-1) % MOD.
// Approach: Traverse the string once to accumulate the sum of digits while simultaneously computing 2^(n-1) modulo 10^9 + 7, then multiply both values under modulo.
// Time Complexity: O(|s|), where |s| is the length of the string, since we perform a single linear pass.
// Space Complexity: O(1), as only a few constant-size variables are used.

class Solution {
  public:
    int subsequenceSum(string &s) {
        const int MOD = 1e9 + 7; // Modulo constant to prevent integer overflow
        long long digitSum = 0;  // Stores total sum of individual digits
        long long powerOfTwo = 1; // Stores 2^(n - 1) % MOD
        int n = s.size();

        for (int i = 0; i < n; i++) {
            digitSum += (s[i] - '0'); // Convert char digit to int and add to sum
            if (i > 0) {
                powerOfTwo = (powerOfTwo * 2) % MOD; // Compute 2^(n - 1) iteratively
            }
        }

        // Multiply total digit sum by 2^(n - 1) under modulo
        return ((digitSum % MOD) * powerOfTwo) % MOD;
    }
};

/*
Dry Run

Input: s = "123"
n = 3, MOD = 1000000007
Initial state: digitSum = 0, powerOfTwo = 1

Iteration i = 0:
s[0] = '1' -> digitSum = 0 + 1 = 1
i > 0 is false -> powerOfTwo = 1

Iteration i = 1:
s[1] = '2' -> digitSum = 1 + 2 = 3
i > 0 is true -> powerOfTwo = (1 * 2) % MOD = 2

Iteration i = 2:
s[2] = '3' -> digitSum = 3 + 3 = 6
i > 0 is true -> powerOfTwo = (2 * 2) % MOD = 4

Final Calculation:
((6 % MOD) * 4) % MOD = 24

Output: 24
*/
```

---

## 🔑 Key Insights

- **Contribution Technique:** Rather than enumerating all $2^n - 1$ subsets, reversing the perspective to calculate each digit's individual contribution collapses exponential complexity into linear time $\mathcal{O}(\vert{}s\vert{})$. 
- **Power of Two Off-by-One:** Multiplying `powerOfTwo` only when `i > 0` naturally computes $2^{n - 1}$ without needing an extra loop or modular exponentiation function, and cleanly handles the base case $n = 1$ where $2^0 = 1$. 
- **Overflow Prevention:** Using `long long` for `digitSum` and `powerOfTwo` ensures intermediate products stay well within 64-bit integer limits before applying `% MOD`. 

---

## 🔍 Further Exploration

- **Sum of all substrings of a number (GFG):** Notice the key difference between *subsequences* (non-contiguous, order-preserving subsets) and *substrings* (contiguous segments where positional place value $10^k$ matters).
- **Power Set (GFG):** Practice generating all non-empty subsequences lexicographically using bit manipulation or recursion.
- **Subset Sums (GFG):** Extend subset contribution concepts to arrays of arbitrary integers.

---

## 📚 References

- **Original Problem:** [GeeksforGeeks - Sum of All Digit Subsequences](https://www.geeksforgeeks.org/problems/sum-of-all-sub-sequences-of-a-number3437/1) 
- **Concepts:** Combinatorics, Contribution Technique, Modular Arithmetic

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Strings](https://img.shields.io/badge/Strings-informational?style=flat-square) 
![Combinatorics](https://img.shields.io/badge/Combinatorics-informational?style=flat-square)
![Mathematics](https://img.shields.io/badge/Mathematics-informational?style=flat-square)
![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white) 
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=flat-square&logo=geeksforgeeks&logoColor=white) 