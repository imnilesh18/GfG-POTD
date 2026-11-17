# 🟩 Repeated Pattern Check

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/the-pattern-matcher/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](https://www.geeksforgeeks.org/problems/the-pattern-matcher/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-26.05%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/the-pattern-matcher/1)
[![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/the-pattern-matcher/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Given a string `s` made up of only two characters: `'x'` and `'y'`. Your task is to verify whether `s` is formed by concatenating one or more substrings that strictly follow the pattern $x^n y^n$ (where $n \ge 1$, meaning an equal number of consecutive `'y'` characters immediately follow an equal number of consecutive `'x'` characters).

Return `true` if the entire string satisfies this pattern; otherwise, return `false`.

---

## 🧪 Examples

### Example 1
```text
Input:  s = "xxyyxy"
Output: true
Explanation: The string can be split into "xxyy" + "xy". Both substrings contain an equal number of consecutive 'x' and 'y' characters.
```

### Example 2
```text
Input:  s = "xyx"
Output: false
Explanation: The last 'x' cannot form a valid substring because it is not followed by a matching 'y'.
```

<details>
<summary><b>📖 Example Breakdown</b></summary>
<br>

Let's walk through both sample inputs to see how contiguous blocks are evaluated:

1. **Input:** `s = "xxyyxy"`
   - **First Block:** Starts with two `'x'`s (`"xx"`), immediately followed by two `'y'`s (`"yy"`). Since $\text{count of 'x'} = \text{count of 'y'} = 2$, `"xxyy"` forms a valid $x^2 y^2$ pattern.
   - **Second Block:** Continues with one `'x'` (`"x"`), immediately followed by one `'y'` (`"y"`). Since $\text{count of 'x'} = \text{count of 'y'} = 1$, `"xy"` forms a valid $x^1 y^1$ pattern.
   - **Result:** All characters are consumed cleanly into valid blocks $\rightarrow$ `true`.

2. **Input:** `s = "xyx"`
   - **First Block:** Starts with one `'x'` (`"x"`) followed by one `'y'` (`"y"`), forming a valid `"xy"` block.
   - **Second Block:** Starts with one `'x'` (`"x"`), but reaches the end of the string with zero `'y'`s following it ($1 \ne 0$).
   - **Result:** Invalid trailing block $\rightarrow$ `false`.

</details>

---

## 🔒 Constraints

> - $1 \le \text{s.size()} \le 10^5$
> - `s` consists only of the characters `'x'` and `'y'`
> - **Expected Time Complexity:** $\mathcal{O}(\vert{}s\vert{})$
> - **Expected Auxiliary Space:** $\mathcal{O}(1)$

---

## 💡 Solution Approach

### Optimal Linear Scan (Block Counting)

#### Intuition
Because every valid substring must follow the strict form $x^n y^n$ ($n \ge 1$), the boundaries between concatenated substrings are uniquely determined. Whenever a sequence of `'y'`s transitions back into `'x'`, a new substring **must** begin. Therefore, we do not need backtracking, stacks, or extra substring allocations—we can greedily consume each contiguous group of `'x'`s followed by its contiguous group of `'y'`s in a single pass.

#### C++ Implementation

```cpp
// Intuition: Any valid string must consist of contiguous blocks where each block has consecutive 'x's immediately followed by an equal number of consecutive 'y's.
// Approach: Traverse the string using an index pointer. In each iteration, count consecutive 'x's, then count consecutive 'y's. If countX is 0 or countX != countY, return false. Repeat until the end of the string.
// Time Complexity: O(|s|), because each character in the string of length n is visited at most once.
// Space Complexity: O(1), as only a few integer variables are used regardless of input size.
class Solution {
  public:
    bool findPattern(string& s) {
        int n = s.size();
        int i = 0;

        while (i < n) {
            int countX = 0;
            // Count consecutive 'x' characters
            while (i < n && s[i] == 'x') {
                countX++;
                i++;
            }

            int countY = 0;
            // Count consecutive 'y' characters
            while (i < n && s[i] == 'y') {
                countY++;
                i++;
            }

            // Validate non-empty 'x' block and equal counts of 'x' and 'y'
            if (countX == 0 || countX != countY) {
                return false;
            }
        }

        return true;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "xxyyxy"
 * n = 6, i = 0
 *
 * Iteration 1:
 * i = 0 -> s[0] == 'x', countX = 1, i = 1
 * i = 1 -> s[1] == 'x', countX = 2, i = 2
 * i = 2 -> s[2] == 'y' (stop counting 'x')
 * i = 2 -> s[2] == 'y', countY = 1, i = 3
 * i = 3 -> s[3] == 'y', countY = 2, i = 4
 * i = 4 -> s[4] == 'x' (stop counting 'y')
 * Check: countX == 2, countY == 2 -> Valid block ("xxyy")
 *
 * Iteration 2:
 * i = 4 -> s[4] == 'x', countX = 1, i = 5
 * i = 5 -> s[5] == 'y' (stop counting 'x')
 * i = 5 -> s[5] == 'y', countY = 1, i = 6
 * i = 6 -> end of string
 * Check: countX == 1, countY == 1 -> Valid block ("xy")
 *
 * Loop terminates as i == n (6 == 6)
 * Output: true
 *
 */
```

---

## 🔑 Key Insights

- **Handling Leading `'y'` Characters:** Checking `countX == 0` immediately catches invalid strings or blocks that begin with `'y'` (e.g., `"yx"` or `"xxyyy"`).
- **Single-Pass Guarantee:** Even though there are nested `while` loops inside the outer loop, the pointer `i` only increments forward and never resets, guaranteeing strict $\mathcal{O}(|s|)$ linear time complexity.
- **Zero Extra Memory:** Counting frequencies on the fly avoids slicing or constructing intermediate substrings, keeping auxiliary space at $\mathcal{O}(1)$.

---

## 🚀 Further Exploration

If you enjoyed this problem, consider practicing these related string and pattern-matching challenges on GeeksforGeeks:

- [Count Binary Substrings](https://www.geeksforgeeks.org/problems/count-binary-substrings/1) — Count contiguous substrings with equal consecutive `0`s and `1`s.
- [Valid Parentheses / Parenthesis Checker](https://www.geeksforgeeks.org/problems/parenthesis-checker2744/1) — Generalize nested matching patterns using a stack.
- [Equal 0, 1 and 2](https://www.geeksforgeeks.org/problems/equal-0-1-and-23208/1) — Count substrings with equal frequencies of three distinct characters.

---

## 📚 References

- **Original Problem:** [Repeated Pattern Check — GeeksforGeeks](https://www.geeksforgeeks.org/problems/the-pattern-matcher/1)
- **Language Documentation:** [C++ `std::string` Reference](https://en.cppreference.com/w/cpp/string/basic_string)

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Strings](https://img.shields.io/badge/Strings-4A90E2?style=flat-square)
![Two Pointers](https://img.shields.io/badge/Two_Pointers-50E3C2?style=flat-square)
![Pattern Matching](https://img.shields.io/badge/Pattern_Matching-F5A623?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=flat-square)