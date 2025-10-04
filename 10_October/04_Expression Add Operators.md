# ➕ Expression Add Operators

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-29620A?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-61.49%25-brightgreen?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

</div>

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/expression-add-operators/1).

---

## Problem Statement

Given a string `s` that contains only digits (0-9) and an integer `target`, return **all possible** strings by inserting the binary operator `'+'`, `'-'`, and/or `'*'` between the digits of `s` such that the resultant expression evaluates to the `target` value.

**Note:**

- Operands in the returned expressions **should not contain leading zeros**. For example, `2 + 03` is not allowed whereas `20 + 3` is fine.
- It is allowed to not insert any of the operators.
- The driver code will print the final list of strings in lexicographically smallest order.

---

## Examples

Here are a few examples to illustrate the problem:

<details>
<summary><strong>Click to view test cases</strong></summary>

### Example 1

```
Input: s = "124", target = 9
Output: ["1+2*4"]
Explanation: The valid expression that evaluates to 9 is 1 + 2 * 4.
```

### Example 2

```
Input: s = "125", target = 7
Output: ["1*2+5", "12-5"]
Explanation: The two valid expressions that evaluate to 7 are 1 * 2 + 5 and 12 - 5.
```

### Example 3

```
Input: s = "12", target = 12
Output: ["12"]
Explanation: s itself matches the target. No other expressions are possible.
```

### Example 4

```
Input: s = "987612", target = 200
Output: []
Explanation: There are no expressions that can be created to evaluate to 200.
```

</details>

### 📖 Example Breakdown

<details>
<summary><strong>Walkthrough for `s = "125"`, `target = 7`</strong></summary>

Let's trace how we find the expression `"1*2+5"` using a backtracking approach.

1.  **Start at index 0 (`'1'`)**:

    - Take the number `1`. The current expression is `"1"`, evaluation is `1`, and the last operand is `1`.
    - Move to the next index (1).

2.  **At index 1 (`'2'`)**:

    - We have three choices for an operator before `'2'`: `+`, `-`, `*`.
    - **Try `+`**: Expression becomes `"1+2"`. Evaluation is `1 + 2 = 3`. Last operand is `2`. Recurse.
    - **Try `-`**: Expression becomes `"1-2"`. Evaluation is `1 - 2 = -1`. Last operand is `-2`. Recurse.
    - **Try `*`**: Expression becomes `"1*2"`.
      - To handle operator precedence, we update the evaluation like this: `current_eval - last_operand + (last_operand * current_number)`.
      - Evaluation: `1 - 1 + (1 * 2) = 2`. The new last operand is `1 * 2 = 2`.
      - Recurse with expression `"1*2"`, evaluation `2`, last operand `2`.

3.  **Continue from `"1*2"` (at index 2, `'5'`)**:

    - Take the number `5`. We have three operator choices.
    - **Try `+`**:
      - Expression: `"1*2+5"`.
      - Evaluation: `current_eval + current_number` -> `2 + 5 = 7`.
      - Last operand: `5`.
      - Recurse.

4.  **Base Case**:

    - We are at the end of the string (`index == s.length()`).
    - Check if the current evaluation (`7`) equals the `target` (`7`). **It does!**
    - Add the expression `"1*2+5"` to our list of results.

5.  **Backtrack**: The recursion unwinds, and the algorithm proceeds to explore other paths, such as `"1*2-5"`, `"1*2*5"`, and eventually finds `"12-5"` in a similar fashion.

</details>

---

## Constraints

<div align="center">

`1 ≤ s.size() ≤ 9`
`s consists of only digits (0-9).`
`-2^31 ≤ target ≤ 2^31-1`

</div>

---

## Solution Approaches

The problem can be solved using a **backtracking** (depth-first search) approach. We explore all possible ways to partition the string and place operators between the partitions.

### Optimized Approach (Backtracking)

The core idea is to build the expression string from left to right. At each step, we decide how long the next number is (e.g., '1', '12', or '124') and which operator to place before it.

A key challenge is handling the `*` operator, which has higher precedence than `+` and `-`. To solve this, we keep track of the `last` operand added. When we encounter a `*`, we can "undo" the previous operation on `last` and apply the multiplication.

- For `+` and `-`, the calculation is straightforward: `current_evaluation + new_number`.
- For `*`, the evaluation becomes: `(current_evaluation - last_operand) + (last_operand * new_number)`.

This ensures that multiplication is correctly applied to the term immediately preceding it.

### C++ Solution

```cpp
// Intuition: We can solve this problem using a backtracking approach. We'll recursively explore all possible ways to place operators (+, -, *) between the digits of the input string 's' to see if any combination evaluates to the target.

// Approach:
// 1. Define a recursive helper function `buildExpr` that takes the current index, expression string, evaluated value, and the last operand.
// 2. The base case for the recursion is when the index reaches the end of the string. If the evaluated value equals the target, we add the expression to our result list.
// 3. In the recursive step, we iterate from the current index to the end of the string to form a number.
// 4. We must handle numbers with leading zeros (e.g., "05"), which are invalid. We skip these.
// 5. For the first number in the expression, we simply start the recursion.
// 6. For subsequent numbers, we try all three operators:
//    - For '+': `eval + num`, last operand is `num`.
//    - For '-': `eval - num`, last operand is `-num`.
//    - For '*': `eval - last + last * num`. This is the tricky part. We subtract the `last` operand to undo the previous operation and then add the product `last * num` to respect operator precedence. The new last operand becomes `last * num`.
// 7. The main function initializes an empty result vector and calls the helper function to start the process from index 0.

// Time Complexity: O(N * 4^N), where N is the length of the string. For each digit, we have roughly 4 choices (continue the number, or add +, -, *). The factor of N comes from substring creation.
// Space Complexity: O(N) for the recursion stack depth and to store the expression string being built.

class Solution {
  public:
    void buildExpr(vector<string>& res, string expr, string digits,
                   long target, int idx, long eval, long last) {

        // Base case: if we have processed all digits
        if (idx == digits.length()) {
            // If the final evaluation equals the target, add the expression to results
            if (eval == target)
                res.push_back(expr);
            return;
        }

        // Iterate through all possible next numbers
        for (int i = idx; i < digits.length(); i++) {

            // Avoid numbers with leading zeros (unless it's just "0")
            if (i != idx && digits[idx] == '0') break;

            // Form the current number part
            string part = digits.substr(idx, i - idx + 1);
            long num = stoll(part);

            if (idx == 0) {
                // First number: just add it to the expression
                buildExpr(res, part, digits, target, i + 1, num, num);
            } else {
                // Not the first number, so try all operators
                // Try '+' operator
                buildExpr(res, expr + "+" + part, digits, target, i + 1, eval + num, num);
                // Try '-' operator
                buildExpr(res, expr + "-" + part, digits, target, i + 1, eval - num, -num);
                // Try '*' operator (handle precedence)
                buildExpr(res, expr + "*" + part, digits, target, i + 1,
                          eval - last + last * num, last * num);
            }
        }
    }

    // Function to return valid expressions
    vector<string> findExpr(string S, int target) {
        vector<string> res;
        // Start the recursive process
        buildExpr(res, "", S, target, 0, 0, 0);
        return res;
    }
};

/*
*
* Dry Run
* s = "124", target = 9
*
* 1. buildExpr(res, "", "124", 9, 0, 0, 0)
* - i = 0, part = "1", num = 1
* - call buildExpr(res, "1", "124", 9, 1, 1, 1)  (First number)
*
* 2. buildExpr(res, "1", "124", 9, 1, 1, 1)
* - i = 1, part = "2", num = 2
* - call buildExpr(res, "1+2", "124", 9, 2, 1+2=3, 2)  (+)
* - call buildExpr(res, "1-2", "124", 9, 2, 1-2=-1, -2) (-)
* - call buildExpr(res, "1*2", "124", 9, 2, 1-1+1*2=2, 1*2=2) (*)
* - i = 2, part = "24", num = 24
* - call buildExpr(res, "1+24", "124", 9, 3, 1+24=25, 24)
* - ... and so on for other operators
*
* 3. Let's trace "1+2" path: buildExpr(res, "1+2", "124", 9, 2, 3, 2)
* - i = 2, part = "4", num = 4
* - call buildExpr(res, "1+2+4", "124", 9, 3, 3+4=7, 4)
* - call buildExpr(res, "1+2-4", "124", 9, 3, 3-4=-1, -4)
* - call buildExpr(res, "1+2*4", "124", 9, 3, 3-2+2*4=9, 2*4=8)
*
* 4. Let's trace "1+2*4" path: buildExpr(res, "1+2*4", "124", 9, 3, 9, 8)
* - idx (3) == digits.length() (3) -> Base case
* - eval (9) == target (9) -> True
* - res.push_back("1+2*4")
*
* The recursion continues to explore all other paths, but only "1+2*4" will match the target.
*
*/

```

---

## Key Insights

- **Backtracking is Essential**: The problem requires exploring all combinations, making backtracking a natural fit.
- **Handling `*` Precedence**: The trick `eval - last + last * num` is the most critical part of the algorithm. It correctly adjusts the running total to account for the higher precedence of multiplication without needing a complex parsing structure.
- **Leading Zeros**: A simple check (`i != idx && digits[idx] == '0'`) is sufficient to prune branches with invalid numbers like `01`, `05`, etc.
- **Data Types**: The intermediate evaluation `eval` and `last` operand can exceed the standard `int` range, so using `long` is safer to prevent overflow.

---

## Further Exploration

If you enjoyed this problem, consider exploring these related challenges:

- [**Combination Sum**](https://www.geeksforgeeks.org/problems/combination-sum/1): Another classic backtracking problem.
- [**Generate Parentheses**](https://www.geeksforgeeks.org/problems/generate-all-possible-parentheses/1): Involves generating all valid combinations of parentheses.
- [**Basic Calculator**](https://leetcode.com/problems/basic-calculator/): A problem that requires parsing and evaluating more complex expressions.
- [**Word Search**](https://www.geeksforgeeks.org/problems/word-search/1): Backtracking on a 2D grid.

---

## References

- **Original Problem**: [GeeksforGeeks | Expression Add Operators](https://www.geeksforgeeks.org/problems/expression-add-operators/1)
- **Backtracking**: A general algorithmic technique for solving problems recursively by trying to build a solution incrementally.

---

## Author

- Connect with me on GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## Tags

![Backtracking](https://img.shields.io/badge/-Backtracking--blue?style=for-the-badge)
![Recursion](https://img.shields.io/badge/-Recursion--green?style=for-the-badge)
![String](https://img.shields.io/badge/-String--orange?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/-GeeksforGeeks--lightgrey?style=for-the-badge)

---

## License

This project is licensed under the MIT License.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Disclaimer**: The solutions provided are for educational purposes. They are intended to help users learn and practice problem-solving skills.
