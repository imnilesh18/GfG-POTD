# 🔗 URLify a Given String

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/urlify-a-given-string--141625/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Basic-brightgreen?style=for-the-badge" alt="Difficulty">
  <img src="https://img.shields.io/badge/Accuracy-72.64%25-blue?style=for-the-badge" alt="Accuracy">
  <img src="https://img.shields.io/badge/Points-1-yellow?style=for-the-badge" alt="Points">
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License">
</p>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a string `s`, replace all the spaces in the string with `'%20'`.

## 💡 Examples

### Example 1
```text
Input: s = "i love programming"
Output: "i%20love%20programming"
Explanation: The 2 spaces are replaced by '%20'
```

### Example 2
```text
Input: s = "Mr Benedict Cumberbatch"
Output: "Mr%20Benedict%20Cumberbatch"
Explanation: The 2 spaces are replaced by '%20'
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>

Let's trace the input string `s = "a b"`:
1. Identify the number of spaces. Here, there is `1` space.
2. Each space requires 2 additional characters (`'%20'` replaces `' '`). New length = `original_length + (spaces * 2)`.
3. Start filling from the back of the resized string to avoid overwriting characters that haven't been processed yet.
4. `b` is placed at the very end.
5. The space is encountered, so `0`, `2`, and `%` are placed backwards.
6. `a` is placed at the front.
7. Final string: `"a%20b"`.

</details>

---

## ⚙️ Constraints

- `1 ≤ s.size() ≤ 10^4`
- **Expected Time Complexity:** `O(n)`
- **Expected Auxiliary Space:** `O(1)`

---

## 🧑‍💻 Solution Approach

Here is the optimized approach to solve the problem in-place using two pointers.

```cpp
// Intuition: We need to make room for the extra characters, so we count the spaces, expand the string, and fill it in from back to front.
// Approach: Count how many spaces exist. Resize the string to its new required length. Use two pointers starting from the back to shift characters and insert '%20' in place of spaces.
// Time Complexity: O(n) because we do a quick count of spaces, then one pass backwards.
// Space Complexity: O(1) because we are directly modifying the string 's' without creating a new one.

class Solution {
public:
    string URLify(string &s) {
        // mark the end of original string
        int i = s.length() - 1; 
        
        // find out how much extra space we need
        int spaces = count(s.begin(), s.end(), ' ');
        
        // expand the string to fit '%20'
        s.resize(s.length() + spaces * 2); 
        
        // mark the end of the newly expanded string
        int j = s.length() - 1; 
        
        // work backwards to shift and replace
        while (i >= 0) {
            if (s[i] == ' ') {
                s[j--] = '0';
                s[j--] = '2';
                s[j--] = '%';
            } else {
                s[j--] = s[i];
            }
            i--;
        }
        
        return s;
    }
};

/*
*
* Dry Run
*
* Input string is "a b"
* Original end pointer i is 2
* Count finds 1 space
* String resizes from length 3 to 5
* New end pointer j is 4
*
* Check i = 2
* s[2] is 'b'
* Place 'b' at s[4]
* Decrement j to 3
* Decrement i to 1
*
* Check i = 1
* s[1] is a space
* Place '0', '2', '%' at positions 3, 2, 1
* Decrement j to 0
* Decrement i to 0
*
* Check i = 0
* s[0] is 'a'
* Place 'a' at s[0]
* Decrement j to -1
* Decrement i to -1
*
* Loop ends because i is less than 0
* Return modified string "a%20b"
*
*/
```

---

## 🔑 Key Insights

- **Right-to-Left Traversal:** The most crucial trick here is traversing and modifying the string from right to left. Since we are expanding the string, moving left-to-right would cause us to overwrite characters before we have a chance to evaluate them.
- **In-Place Modification:** By dynamically resizing the C++ `std::string` and filling it backward, we easily satisfy the `O(1)` auxiliary space constraint constraint.

---

## 🚀 Further Exploration

If you enjoyed this string manipulation problem, consider exploring these related topics and problems:
- String matching and pattern recognition algorithms.
- Two-pointer techniques for in-place array/string modifications.
- **Related GFG Problem:** Reverse words in a given string.

---

## 🔗 References

- **GeeksforGeeks Problem:** [URLify a given string](https://www.geeksforgeeks.org/problems/urlify-a-given-string--141625/1)
- **C++ `std::string::resize` Documentation:** [cplusplus.com](https://en.cppreference.com/w/cpp/string/basic_string/resize)

---

## ✍️ Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#Strings` `#Data Structures` `#Two Pointers` `#GeeksForGeeks` `#In-Place Modification`