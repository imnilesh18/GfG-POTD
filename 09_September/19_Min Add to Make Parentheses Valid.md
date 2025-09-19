# 🪙 Min Add to Make Parentheses Valid

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforGeeks.org/problems/min-add-to-make-parentheses-valid/1).

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/min-add-to-make-parentheses-valid/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-72.9%25-brightgreen?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

---

## 🎯 Problem Statement

You are given a string `s` consisting only of the characters `'('` and `')'`. Your task is to determine the **minimum** number of parentheses (either `'('` or `')'`) that must be inserted at any positions to make the string `s` a **valid parentheses string**.

A parentheses string is considered **valid** if:

- Every opening parenthesis `'('` has a corresponding closing parenthesis `')'`.
- Every closing parenthesis `')'` has a corresponding opening parenthesis `'('`.
- Parentheses are properly nested.

---

## 🧪 Examples

### Example 1:

```
Input: s = "(()("
Output: 2
Explanation: There are two unmatched '(' at the end, so we need to add two ')' to make the string valid.
```

### Example 2:

```
Input: s = ")))"
Output: 3
Explanation: Three '(' need to be added at the start to make the string valid.
```

### Example 3:

```
Input: s = ")()()"
Output: 1
Explanation: The very first ')' is unmatched, so we need to add one '(' at the beginning.
```

<details>
<summary>📖 Example Breakdown (s = "(()(")</summary>
  
1.  **s[0] = '(':** We see an opening bracket. We now need one closing bracket. `close_needed` becomes 1.
2.  **s[1] = '(':** Another opening bracket. We now need two closing brackets. `close_needed` becomes 2.
3.  **s[2] = ')':** We see a closing bracket. It can match one of the previous open brackets. `close_needed` becomes 1.
4.  **s[3] = '(':** A final opening bracket. We now need two closing brackets again. `close_needed` becomes 2.
5.  **End of string:** We have `open_needed = 0` (we never encountered a `)` without a preceding `(`) and `close_needed = 2` (we have two `(` that were never closed).
6.  **Total additions:** `open_needed + close_needed` = 0 + 2 = 2. We need to add two `)` characters.
</details>

---

## ⚙️ Constraints

> `1 ≤ s.size() ≤ 10^5`  
> `s[i] ∈ { '(' , ')' }`

---

## 💡 Solution Approaches

### Optimized Approach (Greedy)

The core idea is to iterate through the string and keep track of two counts:

1.  `open_needed`: The number of opening parentheses `'('` we must add. This is for cases where we encounter a closing parenthesis `')'` without a preceding open one.
2.  `close_needed`: The number of closing parentheses `')'` we must add. This is for open parentheses `'('` that are never closed.

By the end of the iteration, the sum of these two counters gives the minimum number of additions required.

#### C++ Solution

```cpp
// Intuition: We can determine the minimum additions by tracking the balance of parentheses. Instead of using a stack, we can use two counters: one for open parentheses that need a match, and one for closing parentheses that appear too early.
// Approach:
// 1. Initialize `open_needed` and `close_needed` to 0.
// 2. Iterate through the string character by character.
// 3. If we see '(', increment `close_needed` (we need a ')' to match it later).
// 4. If we see ')', check `close_needed`.
//    - If `close_needed` > 0, we have a matching '(', so decrement `close_needed`.
//    - If `close_needed` == 0, this ')' is unmatched, so we must add a '('. Increment `open_needed`.
// 5. The total minimum additions will be the sum of `open_needed` and the remaining `close_needed`.
// Time Complexity: O(N), where N is the length of the string, because we perform a single pass.
// Space Complexity: O(1), as we only use a constant amount of extra space for the counters.
class Solution {
  public:
    int minParentheses(string& s) {
        int open_needed = 0;  // Counts additions for ')' without a preceding '('
        int close_needed = 0; // Counts unclosed '('

        for (char c : s) {
            if (c == '(') {
                // An open parenthesis requires a closing one.
                close_needed++;
            } else if (c == ')') {
                // A closing parenthesis is found.
                if (close_needed > 0) {
                    // It matches a previous open one.
                    close_needed--;
                } else {
                    // No preceding '(', so we must add a '('.
                    open_needed++;
                }
            }
        }

        // The result is the sum of both needs.
        return open_needed + close_needed;
    }
};
/*
*
* Dry Run
*
* Input: s = "(()("
*
* Initial state: open_needed = 0, close_needed = 0
*
* 1. c = '(': close_needed becomes 1.
* 2. c = '(': close_needed becomes 2.
* 3. c = ')': close_needed > 0, so close_needed becomes 1.
* 4. c = '(': close_needed becomes 2.
*
* Final state: open_needed = 0, close_needed = 2
* Return: open_needed + close_needed = 0 + 2 = 2.
*
*/
```

#### Java Solution

```java
// Intuition: The problem can be solved by maintaining a balance count. We only need to add parentheses when the balance becomes negative (a ')' appears without a '(') or when there are leftover open parentheses at the end.
// Approach:
// 1. Initialize `open_needed` and `close_needed` to 0.
// 2. Loop through each character of the string.
// 3. If the character is '(', increment `close_needed`. This signifies an open bracket that needs a matching closing bracket.
// 4. If the character is ')':
//    - If `close_needed` is greater than 0, it means there's a pending open bracket to match with, so decrement `close_needed`.
//    - Otherwise, this ')' is invalid and needs a preceding '('. Increment `open_needed`.
// 5. Finally, return the sum of `open_needed` (for invalid ')') and `close_needed` (for unclosed '(').
// Time Complexity: O(N), as we iterate through the string once.
// Space Complexity: O(1), using only constant extra space.
class Solution {
    public int minParentheses(String s) {
        int open_needed = 0;  // Additions for early ')'
        int close_needed = 0; // Additions for unclosed '('

        for (char c : s.toCharArray()) {
            if (c == '(') {
                // This open paren needs a closing one.
                close_needed++;
            } else if (c == ')') {
                if (close_needed > 0) {
                    // Match found for a previous '('.
                    close_needed--;
                } else {
                    // This ')' has no preceding '('.
                    open_needed++;
                }
            }
        }
        // Total additions is the sum of both requirements.
        return open_needed + close_needed;
    }
}

/*
*
* Dry Run
*
* Input: s = ")))"
*
* Initial state: open_needed = 0, close_needed = 0
*
* 1. c = ')': close_needed is 0, so open_needed becomes 1.
* 2. c = ')': close_needed is 0, so open_needed becomes 2.
* 3. c = ')': close_needed is 0, so open_needed becomes 3.
*
* Final state: open_needed = 3, close_needed = 0
* Return: open_needed + close_needed = 3 + 0 = 3.
*
*/
```

---

## 🧠 Key Insights

The greedy approach of using two counters is highly efficient. It avoids the overhead of a stack data structure by abstracting the problem into a simple balance-checking mechanism. `close_needed` acts like a count of open parentheses waiting for a match, while `open_needed` directly counts the misplaced closing parentheses that require an immediate fix. This correctly captures both types of invalidity in a single pass.

---

## 🚀 Further Exploration

- [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
- [Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/)
- [Generate Parentheses](https://leetcode.com/problems/generate-parentheses/)

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/min-add-to-make-parentheses-valid/1)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![string](https://img.shields.io/badge/String-gray?style=for-the-badge)
![stack](https://img.shields.io/badge/Stack-gray?style=for-the-badge)
![greedy](https://img.shields.io/badge/Greedy-gray?style=for-the-badge)
![geeksforgeeks](https://img.shields.io/badge/GeeksforGeeks-gray?style=for-the-badge)

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

> **Note**: The solutions and explanations are for educational purposes and are based on the problem statement from GeeksforGeeks.
