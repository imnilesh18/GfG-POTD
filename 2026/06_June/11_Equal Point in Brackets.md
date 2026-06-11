# ⚖️ Equal Point in Brackets

![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy: 40.8%](https://img.shields.io/badge/Accuracy-40.8%25-blue?style=for-the-badge)
![Points: 2](https://img.shields.io/badge/Points-2-blue?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org) problem.

---

## 📝 Problem Statement

Given a string `s` of opening and closing brackets `'('` and `')'` only, find an **equal point** in the string. 

An equal point is a position `k` (0-based) such that the number of opening brackets before position `k` is equal to the number of closing brackets from position `k` to the end of the string. If multiple such points exist, return the **first valid position**.

**Note:**
* The string can be split at any position from `0` to `n`, where `n` is the length of the string.
* If we split at `0`, it means there is an empty string on the left.
* If we split at `n`, it means there is an empty string on the right.

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/703123/Web/Other/blobid0_1781098795.webp" alt="Equal Point Example Illustration" />
</div>

---

## 💡 Examples

```text
Input: s = "(())))("
Output: 4
```

```text
Input: s = "))"
Output: 2
Explanation: After index 2, the string splits into "))" and an empty string. The number of opening brackets in the first part is 0 and the number of closing brackets in the second part is also 0.
```

<details>
<summary>📖 <b>Example Breakdown Walkthrough</b></summary>

**String:** `s = "(())))("`
Let's analyze possible split points `k`:
- `k = 0`: Left = `""` (0 open), Right = `"(())))("` (4 close). `0 != 4`
- `k = 1`: Left = `"("` (1 open), Right = `"()))))("` (4 close). `1 != 4`
- `k = 2`: Left = `"()"` (1 open), Right = `"))))("` (4 close). `1 != 4`
- `k = 3`: Left = `"())"` (1 open), Right = `")))("` (3 close). `1 != 3`
- `k = 4`: Left = `"(())"` (2 open), Right = `"))("` (2 close). `2 == 2` ✅

The condition is met at `k = 4`, so 4 is our equal point!
</details>

---

## ⚠️ Constraints

> - `1 ≤ s.size() ≤ 10^5`
> - **Expected Time Complexity:** `O(n)`
> - **Expected Auxiliary Space:** `O(1)`

---

## 🚀 Solution Approach

### The "Aha!" Moment (Mathematical Approach)

You might think you need to keep track of left and right balances dynamically, but let's break down the math for the split point `k`:

1. If we split the string at index `k`, the total number of characters *before* `k` is exactly `k`.
2. Those `k` characters consist of some opening brackets (`Open_left`) and some closing brackets (`Close_left`).
   * `Open_left + Close_left = k`
3. The problem requires the opening brackets on the left to equal the closing brackets on the right:
   * `Open_left = Close_right`
4. We know the total number of closing brackets in the entire string is the sum of the closing brackets on both sides:
   * `Total_close = Close_left + Close_right`
5. Now, substitute `Close_right` with `Open_left` (since they must be equal from step 3):
   * `Total_close = Close_left + Open_left`
6. Look back at step 2! Since `Close_left + Open_left = k`, that means `Total_close = k`.

**Conclusion:** The answer `k` is ALWAYS exactly equal to the total number of closing brackets `)` in the entire string!

### Optimized Code (C++)

```cpp
// Intuition: The equal point k corresponds exactly to the total number of closing brackets ')' in the entire string.
// Approach: Traverse the string exactly once to count all occurrences of ')'. Return this count as the answer.
// Time Complexity: O(N) where N is the length of the string, since we traverse the string exactly once.
// Space Complexity: O(1) as we are only using a single integer variable to keep track of the count.
class Solution {
  public:
    int findIndex(string s) {
        int close_count = 0;
        
        // Count the total number of closing brackets in the string
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == ')') {
                close_count++;
            }
        }
        
        // The index we are looking for is exactly the total count of ')'
        return close_count;
    }
};

/*
* Dry Run
* 
* Input: s = "(())))("
* 
* Variables:
* close_count = 0
* 
* Iteration i = 0: s[0] is '(' -> close_count remains 0
* Iteration i = 1: s[1] is '(' -> close_count remains 0
* Iteration i = 2: s[2] is ')' -> close_count becomes 1
* Iteration i = 3: s[3] is ')' -> close_count becomes 2
* Iteration i = 4: s[4] is ')' -> close_count becomes 3
* Iteration i = 5: s[5] is ')' -> close_count becomes 4
* Iteration i = 6: s[6] is '(' -> close_count remains 4
* 
* Loop terminates.
* Return close_count (4).
*/
```

---

## 🧠 Key Insights
- **Mathematical Simplification:** What initially looks like a prefix-suffix array problem or a two-pointer sliding window problem collapses into basic counting once the underlying algebraic relationship (`k = Open_left + Close_left` & `Total_close = Open_left + Close_left`) is realized.
- **Space Optimization:** No extra arrays are needed to track opening brackets from the left or closing brackets from the right.

---

## 🔍 Further Exploration
- Try to solve a variation where you must find an index balancing *three* types of characters.
- [Minimum Add to Make Parentheses Valid](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/)
- [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)

---

## 🔗 References
- **Original Problem:** [GeeksforGeeks - Equal Point in a String of Brackets](https://www.geeksforgeeks.org/problems/find-equal-point-in-string-of-brackets2542/1)

---

## 👨‍💻 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`#Arrays` `#Strings` `#Data-Structures` `#GeeksForGeeks` `#Amazon` `#Mathematical-Logic`