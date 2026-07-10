# 🧮 Ways to Express as Sum of Consecutives

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-of-sum-of-consecutives3741/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy: 24.63%](https://img.shields.io/badge/Accuracy-24.63%25-green?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statements and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given a number `n`, find the number of ways to represent this number as a sum of 2 or more consecutive natural numbers.

## 💡 Examples

```text
Input: n = 10
Output: 1
Explanation: There is only one way, 10 = 1 + 2 + 3 + 4.
```

```text
Input: n = 15
Output: 3
Explanation: There are 3 ways:
1. 15 = 1 + 2 + 3 + 4 + 5
2. 15 = 4 + 5 + 6
3. 15 = 7 + 8
```

<details>
<summary><b>📖 Example Breakdown</b></summary>
Let's analyze the number `15`:

We are looking for sequences of `k` consecutive integers starting from some integer `a` that sum to `15`. 
- For `k = 2`: `a + (a+1) = 15` ➔ `2a + 1 = 15` ➔ `a = 7`. (Sequence: **7, 8**)
- For `k = 3`: `a + (a+1) + (a+2) = 15` ➔ `3a + 3 = 15` ➔ `a = 4`. (Sequence: **4, 5, 6**)
- For `k = 4`: `a + (a+1) + (a+2) + (a+3) = 15` ➔ `4a + 6 = 15` ➔ `4a = 9` (No integer solution)
- For `k = 5`: `a + ... + (a+4) = 15` ➔ `5a + 10 = 15` ➔ `a = 1`. (Sequence: **1, 2, 3, 4, 5**)

Total valid consecutive sequences = 3.
</details>

---

## ⚙️ Constraints

> - `1 ≤ n ≤ 10^8`
> - Expected Time Complexity: `O(√N)`
> - Expected Auxiliary Space: `O(1)`

---

## 🚀 Solution Approach

### Mathematical Optimization

**Summary:** Instead of nested loops checking all possible sums, we can use algebra. The sum of `k` consecutive natural numbers starting from `a` is represented as:
`Sum = a + (a+1) + (a+2) + ... + (a+k-1)`
`Sum = k * a + k * (k - 1) / 2`
Since `Sum = n`, we can rewrite this as: `n - [k * (k - 1) / 2] = k * a`.
For a valid sequence to exist, `a` must be an integer $\ge 1$. Hence, the term `n - [k * (k - 1) / 2]` must be strictly greater than `0` and perfectly divisible by `k`.

```cpp
// Intuition: We can represent the sum of 'k' consecutive natural numbers starting from 'a' as: n = k*a + k*(k-1)/2. Rearranging gives n - k*(k-1)/2 = k*a. Since 'a' must be a natural number (a >= 1), the term (n - k*(k-1)/2) must be strictly greater than 0 and perfectly divisible by 'k'.
// Approach: Iterate over possible values of 'k' starting from 2. For each 'k', calculate the numerator (n - k*(k-1)/2). If the numerator is greater than 0 and divisible by 'k', it means a valid starting number 'a' exists, so we increment our count. The loop runs as long as k*(k-1)/2 < n.
// Time Complexity: O(√N) because the loop continues as long as k*(k-1)/2 < n, which restricts 'k' to approximately the square root of 2N.
// Space Complexity: O(1) as we are only using a few variables for counting and loop iterations.

class Solution {
  public:
    int getCount(int n) {
        int count = 0;
        
        // Iterate through number of consecutive terms (k >= 2)
        for (long long k = 2; k * (k - 1) / 2 < n; k++) {
            // Calculate the remaining sum required to be divided equally
            long long numerator = n - (k * (k - 1)) / 2;
            
            // Check if a valid positive starting integer 'a' exists
            if (numerator % k == 0) {
                count++;
            }
        }
        
        return count;
    }
};

/*
* Dry Run
* Input: n = 15
* * Initial: count = 0
* * Iteration 1: k = 2
* - Check: 2*(1)/2 = 1 < 15
* - numerator = 15 - 1 = 14
* - 14 % 2 == 0 (Valid) -> count = 1
* * Iteration 2: k = 3
* - Check: 3*(2)/2 = 3 < 15
* - numerator = 15 - 3 = 12
* - 12 % 3 == 0 (Valid) -> count = 2
* * Iteration 3: k = 4
* - Check: 4*(3)/2 = 6 < 15
* - numerator = 15 - 6 = 9
* - 9 % 4 != 0 (Invalid)
* * Iteration 4: k = 5
* - Check: 5*(4)/2 = 10 < 15
* - numerator = 15 - 10 = 5
* - 5 % 5 == 0 (Valid) -> count = 3
* * Iteration 5: k = 6
* - Check: 6*(5)/2 = 15 < 15 (False) -> Loop Breaks
* * Output: count = 3
*/
```

---

## 🧠 Key Insights

- **Avoiding TLE:** A brute-force two-pointer or sliding window approach might take `O(N)` which will give a Time Limit Exceeded (TLE) for `n = 10^8`. Using the mathematical approach cuts down the bounds to strictly `O(√N)`.
- **Arithmetic Progression Formula:** Using the formula for the sum of an Arithmetic Progression is the secret ingredient here to efficiently deduct the variable starting point `a` from equations. 

---

## 🔍 Further Exploration

- **Similar Problems:**
  - **Consecutive Numbers Sum** (LeetCode 829)
  - **Count numbers having 0 as a digit** (GFG)
- **Concepts to master:** Mathematical deductions in series, limits, and loop bounds optimization.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Ways to Express as Sum of Consecutives](https://www.geeksforgeeks.org/problems/count-of-sum-of-consecutives3741/1)
- **Mathematics Reference:** Arithmetic Progressions and Series Sum.

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#Mathematical` `#Algorithms` `#GeeksforGeeks` `#InterviewPrep` `#Optimization`