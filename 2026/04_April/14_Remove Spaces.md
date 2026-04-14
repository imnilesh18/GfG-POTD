# 🟩 Remove Spaces

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/remove-spaces0128/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Basic-brightgreen?style=for-the-badge" alt="Difficulty: Basic" />
  <img src="https://img.shields.io/badge/Accuracy-49.21%25-blue?style=for-the-badge" alt="Accuracy: 49.21%" />
  <img src="https://img.shields.io/badge/Points-1-orange?style=for-the-badge" alt="Points: 1" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge" alt="License: MIT" />
  </a>
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/remove-spaces0128/1).

---

## 📝 Problem Statement

Given a string `s`, remove all the spaces from the string and return the modified string.

---

## 💡 Examples

**Example 1:**
```text
Input: s = "g eeks for ge eks"
Output: "geeksforgeeks"
Explanation: All space characters are removed from the given string while preserving the order of the remaining characters, resulting in the final string "geeksforgeeks".
```

**Example 2:**
```text
Input: s = "abc d "
Output: "abcd"
Explanation: All space characters are removed from the given string while preserving the order of the remaining characters, resulting in the final string "abcd".
```

<details>
<summary>📖 Example Breakdown (Walkthrough)</summary>

Let's do a quick walkthrough with `s = "a b c "`:
1. We iterate through the string character by character.
2. The first character is `'a'`, which is not a space. We keep it at the `0` index.
3. The second character is `' '` (space), so we skip it.
4. The third character is `'b'`. We move this character to the next available position (index `1`).
5. The fourth character is `' '` (space), so we skip it.
6. The fifth character is `'c'`. We move it to index `2`.
7. The last character is `' '` (space), skip it.
8. We trim the rest of the string starting from index `3`.
9. The final string is `"abc"`.
</details>

---

## 🚨 Constraints

- `1 ≤ |s| ≤ 10^5`

---

## 🛠️ Solution Approaches

### Using Built-in functions (Erase-Remove Idiom)

**Brief Intuition:**
Instead of dynamically concatenating characters into a new string (which takes $O(n)$ space), we can use two pointers logic encapsulated by the standard `std::remove` function. This algorithm shifts all non-space characters to the front, returning a pointer to the new logical end of the string. We then chop off the garbage characters at the end using `std::string::erase`.

```cpp
// Intuition: Modify the string in-place by pushing valid non-space characters to the front and discarding the rest.
// Approach: Use std::remove to shift non-space characters to the beginning. It returns an iterator pointing to the new end. Then, use string.erase to delete the leftover trailing characters.
// Time Complexity: O(n) where n is the length of the string, as std::remove processes every character exactly once.
// Space Complexity: O(1) because we are modifying the original string in-place without using extra allocated memory.
class Solution {
  public:
    string removeSpaces(string& s) {
        
        // move non-space characters to front
        auto new_end = remove(s.begin(), s.end(), ' ');
        
        // erase extra part
        s.erase(new_end, s.end());
        
        // return modified string
        return s;
    }
};

/*
*
* Dry Run
* * Input: s = "g e"
* Initial state: s = ['g', ' ', 'e']
* remove() sees 'g': keeps it at index 0.
* remove() sees ' ': skips it.
* remove() sees 'e': places it at index 1.
* remove() returns iterator pointing to index 2.
* Current internal state of s: ['g', 'e', 'e'] (garbage at the end)
* erase(new_end, s.end()) is called:
* It removes everything from index 2 to the end.
* Final string s = "ge"
* Return "ge"
*
*/
```

---

## 🧠 Key Insights

- **Erase-Remove Idiom:** The combination of `std::remove` and `std::string::erase` is a standard, highly optimized C++ idiom for deleting elements from sequential containers (like strings and vectors) in-place.
- **Space Optimization:** By overwriting indices in the pre-allocated string instead of generating a new one, we guarantee $O(1)$ auxiliary space overhead.

---

## 🚀 Further Exploration

- **Follow-up:** How would you implement the `remove` function manually using two explicit pointers (`read_ptr` and `write_ptr`)?
- Try solving similar GeeksforGeeks problems:
  - *Remove all duplicates from a given string*
  - *Reverse words in a given string*

---

## 🔗 References

- **GeeksforGeeks Problem:** [Remove Spaces](https://www.geeksforgeeks.org/problems/remove-spaces0128/1)
- **C++ Reference:** [Erase-Remove Idiom](https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom)

---

## 👨‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Strings` • `Data Structures` • `C++ STL` • `Two Pointers`