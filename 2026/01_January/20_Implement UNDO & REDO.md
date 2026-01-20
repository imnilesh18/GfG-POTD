# 🟧 Implement UNDO & REDO

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Medium-orange?logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/implement-undo-redo/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange)](https://www.geeksforgeeks.org/problems/implement-undo-redo/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-77.29%25-green)](https://www.geeksforgeeks.org/problems/implement-undo-redo/1)
[![Points](https://img.shields.io/badge/Points-4-blue)](https://www.geeksforgeeks.org/problems/implement-undo-redo/1)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

</div>

---

### ⚠️ Educational Use Only
> **This repository and its content are intended solely for educational purposes.** > **Solutions are provided for learning, practice, and reference only.** > **Problem statement and test cases are based on the GeeksforGeeks problem.** ---

## 📝 Problem Statement

You are given a text document that is initially empty. You need to complete the following functions:

1.  `void append(char x)` - Append the character `x` to the end of the document.
2.  `void undo()` - Undo the most recent **APPEND** operation (remove the last appended character).
3.  `void redo()` - Reapply the most recent undone operation (restore the last character removed by **UNDO**).
4.  `string read()` - Return the current content of the document as a string.

There will be a sequence of `q` queries `arr[]` on the document. The queries are represented in numeric form:
- `1 x`: Call `append(x)`
- `2`: Call `undo()`
- `3`: Call `redo()`
- `4`: Call `read()`

The driver code will process the queries, call the corresponding functions, and finally print the outputs of all `READ()` operations.

**You only need to implement the above four functions.**

---

## 💡 Examples

### Example 1

```text
Input: arr[] = [[1 'A'], [1 'B'], [1 'C'], [2], [4], [3], [4]]
Output: ["AB", "ABC"]
Explanation: 
1st query: Append('A'), Document contains "A".
2nd query: Append('B'), Document contains "AB".
3rd query: Append('C'), Document contains "ABC".
4th query: UNDO(), Last character 'C' is removed, Document contains "AB".
5th query: READ(), returns "AB".
6th query: REDO(), Restore 'C', Document contains "ABC".
7th query: READ(), returns "ABC".
```

### Example 2

```text
Input: arr[] = [[1 'D'], [2], [4]]
Output: [""]
Explanation: 
1st query: Append('D'), Document contains "D".
2nd query: UNDO(), Last character 'D' is removed, Document becomes empty.
3rd query: READ(), returns empty string "".
```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's walk through Example 1 step-by-step:

1.  **Init**: `doc = ""`, `redo_stack = ""`
2.  **Append('A')**: `doc = "A"`, `redo_stack` is cleared.
3.  **Append('B')**: `doc = "AB"`, `redo_stack` is cleared.
4.  **Append('C')**: `doc = "ABC"`, `redo_stack` is cleared.
5.  **Undo()**: 
    - Current `doc` is "ABC".
    - Remove 'C' from `doc`. `doc` becomes "AB".
    - Store 'C' in `redo_stack`. `redo_stack` becomes "C".
6.  **Read()**: Output "AB".
7.  **Redo()**:
    - `redo_stack` has "C".
    - Take 'C' and append to `doc`. `doc` becomes "ABC".
    - Remove 'C' from `redo_stack`.
8.  **Read()**: Output "ABC".

</details>

---

## 🚧 Constraints

- $1 \le q \le 10^4$
- **Expected Time Complexity:** O(1) for each operation.
- **Expected Auxiliary Space:** O(N) where N is the total number of characters.

---

## 🛠️ Solution Approaches

### 🚀 Optimized Stack-Based Approach

We can simulate the Undo/Redo mechanism using two main data structures:
1.  **Document String (`doc`)**: Stores the current visible text. It effectively acts as a stack where `append` pushes to the back and `undo` pops from the back.
2.  **Redo Stack (`redo_stack`)**: Stores the characters that were recently removed by an `undo` operation.

When we `undo`, we pop from `doc` and push to `redo_stack`.
When we `redo`, we pop from `redo_stack` and push back to `doc`.
Crucially, any new `append` operation must **clear** the `redo_stack`, as a new edit invalidates the "future" history.

```cpp
// Intuition: Use a string to maintain the current document state and another string (acting as a stack) to store characters removed by UNDO operations, allowing efficient REDO.
// Approach: 'doc' stores the text. 'redo_stack' stores undone chars. Append clears redo history. Undo moves char from doc to redo_stack. Redo moves char from redo_stack to doc.
// Time Complexity: O(1) per operation (amortized for string push_back/pop_back). Read takes O(L) where L is current doc length to return the string.
// Space Complexity: O(N) to store the document and the redo stack history.

class Solution {
  private:
    string doc;
    string redo_stack; // Acts as a stack for redo operations

  public:
    void append(char x) {
        // Append x into document
        doc.push_back(x);
        
        // When we type a new character, the 'redo' history becomes invalid
        // because we have branched off into a new state.
        redo_stack.clear();
    }

    void undo() {
        // Undo last change: Move char from doc to redo_stack
        if (!doc.empty()) {
            redo_stack.push_back(doc.back()); // Save char for potential redo
            doc.pop_back();                   // Remove from current doc
        }
    }

    void redo() {
        // Redo changes: Move char from redo_stack back to doc
        if (!redo_stack.empty()) {
            doc.push_back(redo_stack.back()); // Restore char to doc
            redo_stack.pop_back();            // Remove from redo stack
        }
    }

    string read() {
        // Read the document
        return doc;
    }
};

/*
*
* Dry Run
* Input Operations: [Append('X'), Append('Y'), Undo(), Redo(), Append('Z')]
*
* 1. Append('X')
* doc: "X", redo_stack: ""
*
* 2. Append('Y')
* doc: "XY", redo_stack: ""
*
* 3. Undo()
* doc back is 'Y'. 
* Push 'Y' to redo_stack -> "Y"
* Pop 'Y' from doc -> "X"
*
* 4. Redo()
* redo_stack back is 'Y'.
* Push 'Y' to doc -> "XY"
* Pop 'Y' from redo_stack -> ""
*
* 5. Append('Z')
* Push 'Z' to doc -> "XYZ"
* Clear redo_stack -> ""
*
* Final State: doc = "XYZ"
*
*/
```

---

## 🔑 Key Insights

- **Two Stacks Principle**: The standard way to implement Undo/Redo is using two stacks (or in this case, the string itself acts as a stack of characters).
- **Clearing History**: The most important logic often missed is inside `append`. If you write new content, you cannot "redo" old actions anymore; the redo history branches off and must be cleared.
- **Efficiency**: Using `std::string` as a stack (`push_back`, `pop_back`, `back`) is efficient and clean in C++.

---

## 🔗 References

- [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/implement-undo-redo/1)

---

## 👤 Author

- **[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

![Stack](https://img.shields.io/badge/Stack-Data%20Structure-blue)
![String](https://img.shields.io/badge/String-Manipulation-orange)
![Design](https://img.shields.io/badge/Design-System-purple)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-green)

---

## 📜 License

<div align="center">

This project is licensed under the **MIT License**.

**⚠️ Note:** This repository is for educational purposes only.

</div>