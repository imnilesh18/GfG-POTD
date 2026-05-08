# 🟥 Remove Invalid Parentheses

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Link-blue?logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/remove-invalid-parentheses/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-43.53%25-green)](#)
[![Points](https://img.shields.io/badge/Points-8-orange)](#)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](#)

<div align="center">
  ⚠️ <b>Educational Use Only:</b><br>
  This repository and its content are intended solely for educational purposes.<br>
  Solutions are provided for learning, practice, and reference only.<br>
  Problem statement and test cases are based on the GeeksforGeeks problem.
</div>

---

## 📝 Problem Statement

Given a string `s` consisting of lowercase letters and parentheses `'('` and `')'`. 
A string is considered **valid** if:
* Every opening parenthesis `'('` has a corresponding closing parenthesis `')'`.
* Parentheses are properly nested.

Remove the **minimum** number of invalid parentheses from `s` so that the resulting string becomes valid. Return **all the possible distinct valid strings** in **lexicographically sorted order**.

---

## 💡 Examples

```text
Input: s = "()())()"
Output: ["(())()", "()()()"]
Explanation: 
The string "()())()" has one extra ')', making it invalid. By removing one ')', we can make it valid in two ways:
Remove the 3rd index ')' -> "(())()"
Remove the 4th index ')' -> "()()()"
Both are valid and require the minimum removals.

```

```text
Input: s = "(a)())()"
Output: ["(a())()", "(a)()()"]
Explanation: 
We remove one ')' (minimum removals) to make it valid. Possible valid results:
Remove a ')' -> "(a())()"
Remove another ')' -> "(a)()()"

```

```text
Input: s = ")("
Output: [""]
Explanation: 
The string ")(" is invalid. Removing both parentheses (minimum removals) gives an empty string "", which is valid.

```

Let's break down `s = "()())()"`:

1. First, we identify the unbalanced parentheses. Traversing left to right, we find **0** extra `'('` and **1** extra `')'`.
2. We need to explore paths where we skip exactly **one** `')'`.
3. Valid skip at index 3: `s[0..2]` + `s[4..6]` = `"( ) ("` + `") ( )"` = `"( ) ( ) ( )"` -> `()()()`
4. Valid skip at index 4: `s[0..3]` + `s[5..6]` = `"( ) ( )"` + `" ( )"` = `"( ( ) ) ( )"` -> `(())()`
5. Both resulting strings are fully balanced and distinct. They are returned in sorted order: `["(())()", "()()()"]`.

---

## ⚙️ Constraints

> * 1 ≤ |s| ≤ 20
> * `s` consists of lowercase English letters and parentheses `'('` and `')'`
> 
> 

---

## 🚀 Solution Approach

### Backtracking with Pruning

**Brief Summary:**
To remove the *minimum* number of invalid parentheses, we must first figure out exactly how many opening and closing parentheses are mismatched. Once we have those counts, we can recursively build a new string character by character. At every parenthesis, we branch into two possibilities: either we remove it (if we still have removals left to do) or we keep it. Pruning duplicate branches and using a set ensures we only return distinct results.

```cpp
// Intuition: We must first count exactly how many left and right parentheses are unbalanced. Once known, we can explore every possible combination of string building by choosing to either keep or skip characters, using a backtracking strategy to ensure we only remove the minimum necessary.
// Approach: 1. Traverse the string to find the minimum number of '(' and ')' that need removal. 2. Use a backtracking function that maintains the current built string (`path`). 3. At each step, either skip the current character (if it's a parenthesis and we need to remove one) OR keep it (push, explore, pop). 4. Use a set to store distinct valid strings, then return them sorted lexicographically.
// Time Complexity: O(2^N) in the worst case, as every parenthesis presents two choices: keep or remove. N is the string length.
// Space Complexity: O(N) auxiliary space for the recursion depth and current path, plus O(K) where K is the number of valid results to store in the hash set.

class Solution {
    public:
    
    unordered_set<string> valid_strings; // To avoid duplicate valid strings

    void backtrack(int index, int left_count, int right_count, int left_rem, int right_rem, string& path, const string& s) {
        // Base case: Reached the end of the input string
        if (index == s.length()) {
            if (left_rem == 0 && right_rem == 0) {
                valid_strings.insert(path); // Save valid configuration
            }
            return;
        }

        char c = s[index];

        // 1. Choice: Remove the current parenthesis
        if (c == '(' && left_rem > 0) {
            backtrack(index + 1, left_count, right_count, left_rem - 1, right_rem, path, s); // Skip '('
        } else if (c == ')' && right_rem > 0) {
            backtrack(index + 1, left_count, right_count, left_rem, right_rem - 1, path, s); // Skip ')'
        }

        // 2. Choice: Keep the current character (Go -> Explore -> Backtrack)
        if (c != '(' && c != ')') {
            // Keep lowercase letters unconditionally
            path.push_back(c); // Go
            backtrack(index + 1, left_count, right_count, left_rem, right_rem, path, s); // Explore
            path.pop_back(); // Backtrack
        } else if (c == '(') {
            // Keep opening parenthesis unconditionally
            path.push_back(c); // Go
            backtrack(index + 1, left_count + 1, right_count, left_rem, right_rem, path, s); // Explore
            path.pop_back(); // Backtrack
        } else if (c == ')' && left_count > right_count) {
            // Keep closing parenthesis ONLY if it balances an existing opening one
            path.push_back(c); // Go
            backtrack(index + 1, left_count, right_count + 1, left_rem, right_rem, path, s); // Explore
            path.pop_back(); // Backtrack
        }
    }


    vector<string> validParenthesis(string &s) {
        int left_rem = 0, right_rem = 0;
        
        // Find minimum number of misplaced left and right parentheses
        for (char c : s) {
            if (c == '(') {
                left_rem++;
            } else if (c == ')') {
                if (left_rem > 0) {
                    left_rem--; // Matched a left parenthesis
                } else {
                    right_rem++; // Unmatched right parenthesis
                }
            }
        }

        string path = "";
        backtrack(0, 0, 0, left_rem, right_rem, path, s);

        // Convert set to vector and sort lexicographically
        vector<string> result(valid_strings.begin(), valid_strings.end());
        sort(result.begin(), result.end());
        return result;
    }
};

/*
*
* Dry Run
* Input: s = "(a)())()"
* 
* Initial counts check:
* s[0] = '(' -> left_rem = 1
* s[1] = 'a'
* s[2] = ')' -> left_rem = 0
* s[3] = '(' -> left_rem = 1
* s[4] = ')' -> left_rem = 0
* s[5] = ')' -> right_rem = 1
* s[6] = '(' -> left_rem = 1
* s[7] = ')' -> left_rem = 0
* We need to remove 0 '(' and 1 ')'
* 
* Backtrack starts: left_rem = 0, right_rem = 1, path = ""
* index = 0, c = '(': Keep it -> push '(', backtrack(1, left_count=1...)
* index = 1, c = 'a': Keep it -> push 'a', backtrack(2, left_count=1...)
* index = 2, c = ')': Keep it -> push ')', backtrack(3, left_count=1, right_count=1...)
* index = 3, c = '(': Keep it -> push '(', backtrack(4, left_count=2, right_count=1...)
* index = 4, c = ')':
*   Branch 1: Skip it -> path = "(a)(" (right_rem becomes 0), backtrack(5...)
*       ... leads to building "(a)()()"
*   Branch 2: Keep it -> path = "(a)()" (right_rem is still 1), backtrack(5...)
* index = 5, c = ')':
*   Branch 1: Skip it -> path = "(a)()" (right_rem becomes 0), backtrack(6...)
*       ... leads to building "(a())()"
*   Branch 2: Keep it -> invalid branch because left_count (2) is not > right_count (2). Pruned!
* 
* The set collects "(a)()()" and "(a())()".
* Converted to vector and lexicographically sorted -> ["(a())()", "(a)()()"].
*
*/

```

---

## 🔍 Key Insights

1. **Pre-Calculation is Powerful:** By identifying the exact number of excess `(` and `)` beforehand, we limit our recursion depth entirely to valid choices.
2. **Backtracking and State Reversal:** Because strings in C++ are passed by reference to save memory, we must cleanly undo (`pop_back()`) every choice we make after exploring it.
3. **Invalid Pruning Strategy:** We instantly kill recursive branches where `)` exceeds `(` in the constructed path (`left_count > right_count`). This drastically cuts down useless function calls.

---

## 📚 Further Exploration

If you enjoyed this problem, you might also like to practice these related topics:

* [Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) - Classic backtracking string builder.
* [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) - The foundational stack-based parenthetical matching problem.
* [Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/) - Expanding on the idea with Dynamic Programming / Stacks.

---

## 🔗 References

* **Original Problem:** [GeeksforGeeks - Remove Invalid Parentheses](https://www.geeksforgeeks.org/problems/remove-invalid-parentheses/1)

---

## ✍️ Author

* **Nilesh** - [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Backtracking` `#Strings` `#Recursion` `#DataStructures` `#Algorithms` `#GeeksforGeeks`