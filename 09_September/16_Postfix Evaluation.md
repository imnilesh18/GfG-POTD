# 🔢 Postfix Evaluation

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-63.04%25-orange.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/evaluation-of-postfix-expression1735/1).

---

## Problem Statement

You are given an array of strings `arr[]` that represents a valid arithmetic expression written in Reverse Polish Notation (Postfix Notation). Your task is to evaluate the expression and return an integer representing its value.

**Note:**

- A postfix expression is of the form `operand1 operand2 operator` (e.g., "a b +").
- The division operation between two integers always computes the **floor** value, i.e `floor(5 / 3) = 1` and `floor(-5 / 3) = -2`.
- It is guaranteed that the result of the expression and all intermediate calculations will fit in a 32-bit signed integer.

---

## Examples

**Example 1:**

```
Input: arr[] = ["2", "3", "1", "*", "+", "9", "-"]
Output: -4
Explanation: If the expression is converted into an infix expression,
it will be 2 + (3 * 1) – 9 = 5 – 9 = -4.
```

**Example 2:**

```
Input: arr[] = ["2", "3", "^", "1", "+"]
Output: 9
Explanation: If the expression is converted into an infix expression,
it will be 2 ^ 3 + 1 = 8 + 1 = 9.
```

<details>
<summary><b>📖 Example 1 Breakdown</b></summary>
<br>
We evaluate the expression using a Stack. We iterate through the array:

1.  **Token "2"**: Push 2.
    - Stack: `[2]`
2.  **Token "3"**: Push 3.
    - Stack: `[2, 3]`
3.  **Token "1"**: Push 1.
    - Stack: `[2, 3, 1]`
4.  **Token "\*"**: Operator. Pop two operands (1 and 3). Calculate `3 * 1 = 3`. Push the result.
    - Stack: `[2, 3]`
5.  **Token "+"**: Operator. Pop two operands (3 and 2). Calculate `2 + 3 = 5`. Push the result.
    - Stack: `[5]`
6.  **Token "9"**: Push 9.
    - Stack: `[5, 9]`
7.  **Token "-"**: Operator. Pop two operands (9 and 5). Calculate `5 - 9 = -4`. Push the result.
    - Stack: `[-4]`

The iteration finishes. The final element on the stack is **-4**.

</details>

---

## Constraints

<div align="center">

| Constraint   | Value                                                         |
| :----------- | :------------------------------------------------------------ |
| `arr.size()` | `3 ≤ N ≤ 10^3`                                                |
| `arr[i]`     | Operator (`+`, `-`, `*`, `/`, `^`) or Integer `[-10^4, 10^4]` |

</div>

---

## Solution Approach: Stack-Based Evaluation

The optimal and standard way to evaluate a postfix (Reverse Polish Notation) expression is by using a **Stack**.

The logic relies on the structure of postfix notation: operands always appear before the operator that applies to them.

1.  Initialize an empty stack designed to hold integers (operands).
2.  Iterate through every token in the input array `arr`.
3.  **If the token is an operand (a number):** Convert the string to an integer and push it onto the stack. (We must correctly identify negative numbers like "-4" as operands, distinct from the subtraction operator "-").
4.  **If the token is an operator:** This means we must have at least two operands waiting on the stack.
    - Pop the top element; this is the _second_ operand (`val1`).
    - Pop the next element; this is the _first_ operand (`val2`).
    - Perform the operation `result = val2 OP val1`.
    - Push the `result` back onto the stack.
5.  After iterating through all tokens, the stack will contain exactly one element, which is the final result of the expression.

This approach ensures that operations are performed in the correct order as defined by the postfix sequence. A special helper function `floorDiv` is required to handle GFG's specific requirement for floor division involving negative numbers.

### C++ Solution

```cpp
// Intuition: Use a stack to evaluate the postfix (Reverse Polish Notation) expression. Operands are pushed onto the stack. When an operator is encountered, pop the last two operands, perform the operation, and push the result back.
// Approach:
// 1. Iterate through each token (string) in the input array `arr`.
// 2. Check if the token is an operand (a number). A token is a number if its first character is a digit OR if its length is > 1 and the first char is '-' (to handle negative numbers).
// 3. If it's an operand, convert it to an integer (stoi) and push it onto the stack `st`.
// 4. If it's an operator (+, -, *, /, ^):
// 5. Pop the top two elements: val1 (the second operand) and val2 (the first operand).
// 6. Perform the operation (val2 OP val1) based on the token.
// 7. For division, use the custom `floorDiv` helper to match GFG's negative floor division requirement.
// 8. For power, use pow(val2, val1).
// 9. Push the result of the operation back onto the stack.
// 10. After the loop finishes, the stack will contain exactly one element, which is the final result. Return st.top().
// Time Complexity: O(N), where N is the number of tokens in the array. We iterate through the array once.
// Space Complexity: O(N), in the worst case (e.g., all operands followed by operators), the stack may store up to (N/2 + 1) operands.

class Solution {
  public:
    // Helper function for GFG-specific floor division (handles negative results correctly)
    int floorDiv(int a, int b) {
        // Check for a negative result (a and b have different signs) AND a non-zero remainder
        if (a * b < 0 && a % b != 0)
            return (a / b) - 1; // Adjust standard C++ truncation toward the negative (floor)
        return a / b; // Otherwise, standard C++ division (truncates toward zero) is fine
    }

    // Function to evaluate a valid postfix expression.
    int evaluatePostfix(vector<string>& arr) {
        stack<int> st; // Stack to store operands

        // Iterate over each token in the expression array
        for (string token : arr) {

            // If it's an operand (number), push it onto the stack
            // This check correctly identifies:
            // 1. Positive numbers (e.g., "2", "15") using isdigit()
            // 2. Negative numbers (e.g., "-4", "-100") by checking size > 1 and first char == '-'
            if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
                st.push(stoi(token)); // Convert the string operand to an int and push
            }

            // Otherwise, the token must be an operator
            else {
                // An operator requires two operands. Pop them.
                int val1 = st.top(); st.pop(); // This is the *second* operand (e.g., 'b' in 'a b +')
                int val2 = st.top(); st.pop(); // This is the *first* operand (e.g., 'a' in 'a b +')

                // Perform the operation (val2 OP val1) based on the operator token
                if (token == "+") st.push(val2 + val1);
                else if (token == "-") st.push(val2 - val1);
                else if (token == "*") st.push(val2 * val1);
                else if (token == "/") st.push(floorDiv(val2, val1)); // Use custom floor division
                else if (token == "^") st.push((int)pow(val2, val1)); // Handle power operation
            }
        }

        // After processing all tokens, the final result is the only element left on the stack
        return st.top();
    }
};


/*
*
* Dry Run (Example 1)
* arr[] = ["2", "3", "1", "*", "+", "9", "-"]
* * Stack: []
* * Token: "2". Is operand. Push(2).
* Stack: [2]
* Token: "3". Is operand. Push(3).
* Stack: [2, 3]
* Token: "1". Is operand. Push(1).
* Stack: [2, 3, 1]
* Token: "*". Is operator.
* val1 = Pop() = 1
* val2 = Pop() = 3
* calc = val2 * val1 = 3 * 1 = 3. Push(3).
* Stack: [2, 3]
* Token: "+". Is operator.
* val1 = Pop() = 3
* val2 = Pop() = 2
* calc = val2 + val1 = 2 + 3 = 5. Push(5).
* Stack: [5]
* Token: "9". Is operand. Push(9).
* Stack: [5, 9]
* Token: "-". Is operator.
* val1 = Pop() = 9
* val2 = Pop() = 5
* calc = val2 - val1 = 5 - 9 = -4. Push(-4).
* Stack: [-4]
* * Loop finishes. Return st.top() -> -4.
*
*/
```

---

## Key Insights

The solution hinges on the **LIFO (Last-In, First-Out)** property of the Stack. Postfix notation guarantees that by the time an operator is encountered, the operands it needs (its immediate predecessors in the logic) are the two most recent items added to the stack.

The crucial detail is the order of operations: when evaluating `val2 OP val1`, `val1` is the item popped _first_ (the second operand in the expression) and `val2` is the item popped _second_ (the first operand in the expression).

## Further Exploration

- **Infix to Postfix Conversion:** Write an algorithm (like the Shunting-yard algorithm) to convert a standard infix expression (e.g., `(a + b) * c`) into a postfix expression (e.g., `a b + c *`).
- **Prefix Evaluation:** Modify this algorithm to evaluate a Prefix (Polish) expression (e.g., `* + a b c`). (Hint: Iterate the array in reverse order).

---

## References

- [Original GeeksforGeeks (GFG) Problem Link](https://www.geeksforgeeks.org/problems/evaluation-of-postfix-expression1735/1)

## Author

- [imnilesh18](https://github.com/imnilesh18)

## Tags

![Stack](https://img.shields.io/badge/Stack-blue?style=for-the-badge)
![Data Structures](https://img.shields.io/badge/Data_Structures-grey?style=for-the-badge)
![Postfix](https://img.shields.io/badge/Postfix-orange?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge)

---

## 📜 License

This project is licensed under the MIT License - see the LICENSE file for details.

This repository and its solutions are provided for **educational purposes only**. They are intended for learning, practice, and reference. Please respect the academic integrity policies of any institution or platform you are part of.
