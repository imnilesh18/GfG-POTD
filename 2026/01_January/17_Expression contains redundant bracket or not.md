# 🟧 Expression contains redundant bracket or not

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Expression_contains_redundant_bracket_or_not-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/expression-contains-redundant-bracket-or-not/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-FFB800?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/expression-contains-redundant-bracket-or-not/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-48.71%25-green?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/expression-contains-redundant-bracket-or-not/1)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/expression-contains-redundant-bracket-or-not/1)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

> [!IMPORTANT]
> **⚠️ Educational Use Only**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.

---

## 📝 Problem Statement

Given a string of balanced expression `s`, check if it contains a redundant parenthesis or not. A set of parenthesis are redundant if the same sub-expression is surrounded by unnecessary or multiple brackets.

**Note:** Expression may contain `+`, `-`, `*`, and `/` operators. Given expression is **valid** and there are **no white spaces** present.

---

## 🎯 Examples

### Example 1
```bash
Input: s = "((a+b))"
Output: true 
Explanation: ((a+b)) can reduced to (a+b). The outer brackets are redundant.

```

### Example 2

```bash
Input: s = "(a+(b)/c)"
Output: true
Explanation: (a+(b)/c) can reduced to (a+b/c) because b is surrounded by () which is redundant.

```

### Example 3

```bash
Input: s = "(a+b+(c+d))"
Output: false
Explanation: (a+b+(c+d)) doesn't have any redundant or multiple brackets.

```

<details>
<summary><b>📖 Example Breakdown: s = "((a+b))"</b></summary>

1. **Initialize Stack**: Empty.
2. **Process '(':** Push `(`. Stack: `['(']`
3. **Process '(':** Push `(`. Stack: `['(', '(']`
4. **Process 'a':** Push `a`. Stack: `['(', '(', 'a']`
5. **Process '+':** Push `+`. Stack: `['(', '(', 'a', '+']`
6. **Process 'b':** Push `b`. Stack: `['(', '(', 'a', '+', 'b']`
7. **Process ')':**
* Pop until `(`.
* Pop `b` (not operator).
* Pop `+` (Operator found! `hasOperator = true`).
* Pop `a` (not operator).
* Pop `(`.
* `hasOperator` is `true`. This pair `(a+b)` is **valid**.
* Stack: `['(']`


8. **Process ')':**
* Pop until `(`.
* Immediate pop is `(`. No operators found in between.
* `hasOperator` is `false`.
* **Return `true**`. Redundant!



</details>

---

## 🔒 Constraints

* `1 ≤ |s| ≤ 10^5`
* `s` contains `(`, `)`, `+`, `-`, `*`, `/`, and lowercase English letters.

---

## 💡 Solution Approach

The core idea is to identify parentheses that do not enclose any operation. A pair of parentheses is redundant if:

1. It encloses another pair of parentheses directly (e.g., `((...))`).
2. It encloses only a single operand (e.g., `(a)`).

We use a **Stack** to traverse the expression:

1. Push all characters (`(`, operands, operators) onto the stack until a closing parenthesis `)` is encountered.
2. When a `)` is found, pop elements from the stack until the matching `(` is found.
3. While popping, verify if an operator (`+`, `-`, `*`, `/`) exists.
4. If **no operator** is found between the pair `(...)`, the parentheses are redundant.

### C++ Solution

```cpp
// Intuition: Redundant brackets surround content without operators (like "(a)") or verify redundancy of outer brackets (like "((a+b))").
// Approach: Push chars to stack. On ')', pop until '('. If no operator (+, -, *, /) was popped, brackets are redundant.
// Time Complexity: O(N) where N is the length of string s (each char processed twice max).
// Space Complexity: O(N) for the stack in the worst case.

class Solution {
  public:
    bool checkRedundancy(string &s) {
        stack<char> st;

        for (char ch : s) {
            // If we encounter a closing bracket, we check the sub-expression
            if (ch == ')') {
                bool hasOperator = false;
                
                // Pop elements until we find the matching opening '('
                // Check if there is an operator inside this pair
                while (!st.empty() && st.top() != '(') {
                    char top = st.top();
                    st.pop();
                    
                    if (top == '+' || top == '-' || top == '*' || top == '/') {
                        hasOperator = true;
                    }
                }
                
                // Pop the opening '(' itself
                st.pop();
                
                // If no operator was found, the brackets are redundant
                if (!hasOperator) {
                    return true;
                }
            } 
            else {
                // Push '(', operands, and operators onto the stack
                st.push(ch);
            }
        }
        
        // If we finish the loop without returning true, no redundancy exists
        return false;
    }
};

/*
*
* Dry Run
* Input: s = "(a)"
*
* i=0, ch='(': Push '('. Stack: ['(']
* i=1, ch='a': Push 'a'. Stack: ['(', 'a']
* i=2, ch=')': 
* - Pop 'a', top='a'. Not operator. Stack: ['(']
* - Top is '(', stop loop.
* - Pop '('. Stack: []
* - hasOperator is false.
* - Return true. (Correct, (a) is redundant)
*
*/

```

---

## 🔑 Key Insights

* **Operator Check**: The defining characteristic of a useful parenthesis pair in arithmetic expressions is that it groups an operation (e.g., `a+b`). If it wraps just a value `(a)` or nothing `()`, it serves no arithmetic purpose.
* **Immediate Nesting**: `((...))` creates a scenario where the outer pair sees the inner result as a single operand (conceptually) without an operator in between, triggering the redundancy check correctly.

---

## 📚 References

* [GFG Problem Link](https://www.geeksforgeeks.org/problems/expression-contains-redundant-bracket-or-not/1)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
* `Stack`
* `Strings`

---

## 📜 License
> [!WARNING]
> This repository is strictly for educational purposes. Copying code for academic assignments or competitive programming contests without understanding may violate academic integrity policies.
