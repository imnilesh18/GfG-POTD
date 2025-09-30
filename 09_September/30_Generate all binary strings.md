# 💻 Generate all binary strings

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-63.9%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

---

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/generate-all-binary-strings/1).

---

## 📖 Problem Statement

Given an integer **n**, you need to generate all the **binary strings** of `n` characters representing bits.

**Note**: Return the strings in **ascending order**.

---

### 📝 Examples

**Example 1:**

```
Input: n = 2
Output: [00, 01, 10, 11]
Explanation: As each position can be either 0 or 1, the total possible combinations are 4.
```

**Example 2:**

```
Input: n = 3
Output: [000, 001, 010, 011, 100, 101, 110, 111]
Explanation: As each position can be either 0 or 1, the total possible combinations are 8.
```

<details>
<summary><strong>📖 Example Breakdown (n=2)</strong></summary>

Let's walk through generating binary strings of length 2.

1. We start with an empty string `""`.
2. We need to decide the first character. It can be '0' or '1'.
   - **Path 1:** Choose '0'. The string is now `"0"`.
   - **Path 2:** Choose '1'. The string is now `"1"`.
3. Now we decide the second character for each path.
   - For `"0"`:
     - **Path 1.1:** Choose '0'. The string is now `"00"`. Length is 2, so we stop and record it.
     - **Path 1.2:** Choose '1'. The string is now `"01"`. Length is 2, so we stop and record it.
   - For `"1"`:
     - **Path 2.1:** Choose '0'. The string is now `"10"`. Length is 2, so we stop and record it.
     - **Path 2.2:** Choose '1'. The string is now `"11"`. Length is 2, so we stop and record it.
4. We have explored all paths and found all combinations: `00`, `01`, `10`, `11`. The recursive approach naturally generates them in ascending order.
</details>

---

### ⛓️ Constraints

- `1 ≤ n ≤ 20`

---

## 💡 Solution Approaches

The problem of generating all binary strings of length `n` can be modeled as a decision tree. At each level `i` (from 0 to `n-1`), we decide whether the character at that position is a '0' or a '1'. This leads to a natural recursive solution.

### Optimized Approach (Recursion / Backtracking)

We use a helper function that builds the string recursively. For each position in the string, we make two recursive calls: one where we append a '0' and another where we append a '1'. The recursion stops when the string reaches the desired length `n`.

#### C++ Code

```cpp
// Intuition: The problem asks for all possible binary strings of a given length 'n'.
// This can be visualized as a binary tree of depth 'n', where at each level, we branch
// into two possibilities: appending a '0' or a '1'.
//
// Approach: We use a recursive helper function `solve`.
// 1. Start with an empty string.
// 2. The recursive function takes the target length `n`, the current string `current`, and a result vector.
// 3. Base Case: If `current.length() == n`, we have a complete binary string, so add it to the result vector and return.
// 4. Recursive Step: Make two recursive calls from the current state:
//    a. `solve(n, current + '0', result)`: Explore the path by appending '0'.
//    b. `solve(n, current + '1', result)`: Explore the path by appending '1'.
// 5. The initial call will be `solve(n, "", result)`. The nature of this depth-first exploration (exploring '0' branches before '1' branches) ensures the results are generated in ascending order.
//
// Time Complexity: O(2^n * n). There are 2^n binary strings of length n. For each string, creating and storing it can take O(n) time due to string concatenations and copying.
// Space Complexity: O(n). This is the maximum depth of the recursion stack. The space to store the 2^n results is not counted towards auxiliary space complexity.

class Solution {
  public:
    // Helper function to recursively generate the strings.
    void solve(int n, string current, vector<string>& result) {
        // Base case: If the current string has the desired length, add it to the results.
        if (current.length() == n) {
            result.push_back(current); // A valid binary string is found.
            return;
        }

        // Recursive step: Append '0' and explore this path.
        solve(n, current + '0', result);

        // Recursive step: Append '1' and explore this path.
        solve(n, current + '1', result);
    }

    vector<string> binstr(int n) {
        vector<string> result; // To store all generated binary strings.
        // Start the recursion with an empty string.
        solve(n, "", result);
        return result;
    }
};

/*
*
* Dry Run (n = 2)
*
* 1. binstr(2) is called.
* 2. solve(2, "", result) is called.
* - current.length() (0) != 2
* - Calls solve(2, "0", result)
* - current.length() (1) != 2
* - Calls solve(2, "00", result)
* - current.length() (2) == 2. Add "00" to result. result = ["00"]. Return.
* - Calls solve(2, "01", result)
* - current.length() (2) == 2. Add "01" to result. result = ["00", "01"]. Return.
* - Returns from solve(2, "0", result).
* - Calls solve(2, "1", result)
* - current.length() (1) != 2
* - Calls solve(2, "10", result)
* - current.length() (2) == 2. Add "10" to result. result = ["00", "01", "10"]. Return.
* - Calls solve(2, "11", result)
* - current.length() (2) == 2. Add "11" to result. result = ["00", "01", "10", "11"]. Return.
* - Returns from solve(2, "1", result).
* 3. binstr(2) returns ["00", "01", "10", "11"].
*
*/
```

---

## 🔑 Key Insights

- The problem is about generating all permutations with repetition, where the elements are `{0, 1}`.
- **Recursion** provides a clean and intuitive way to explore every possible combination. The state at each recursive call is the string built so far.
- **Backtracking** is implicitly used. After exploring a path (e.g., adding '0' and all subsequent characters), we return to the previous state to explore the other path (e.g., adding '1'). In the Java example, this is done explicitly with `deleteCharAt`. In the C++ example, it's implicit because new string objects are passed in each call.

---

## 🚀 Further Exploration

- **[Generate Parentheses](https://www.geeksforgeeks.org/problems/generate-all-possible-parentheses/1)**: A similar recursive problem where you generate all combinations of well-formed parentheses.
- **[Permutations of a given string](https://www.geeksforgeeks.org/problems/permutations-of-a-given-string-1587115620/1)**: Generate all unique orderings of characters in a string.
- **Combinations**: Generate all unique subsets of a certain size from a given set of numbers.

---

## 📚 References

- **Original Problem:** [GeeksforGeeks | Generate all binary strings](https://www.geeksforgeeks.org/problems/generate-all-binary-strings/1)
- **Recursion and Backtracking:** [GeeksforGeeks Article](https://www.geeksforgeeks.org/introduction-to-backtracking-data-structure-and-algorithm-tutorials/)

---

## 🧑‍💻 Author

- **Contributed by:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Recursion](https://img.shields.io/badge/Recursion-4A148C?style=for-the-badge)
![Backtracking](https://img.shields.io/badge/Backtracking-8E24AA?style=for-the-badge)
![Strings](https://img.shields.io/badge/Strings-7B1FA2?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge)

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**A gentle reminder:** The solutions in this repository are for educational purposes. They are meant to help you understand different problem-solving techniques. Always try to solve problems on your own first!
