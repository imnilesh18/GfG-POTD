# 📰 Palindrome Sentence

| [![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/string-palindromic-ignoring-spaces4723/1) | [![Difficulty](https://img.shields.io/badge/Difficulty-Easy-green)](https://www.geeksforgeeks.org/problems/string-palindromic-ignoring-spaces4723/1) | [![Accuracy](https://img.shields.io/badge/Accuracy-50.04%25-yellow)](https://www.geeksforgeeks.org/problems/string-palindromic-ignoring-spaces4723/1) | [![Points](https://img.shields.io/badge/Points-2-blue)](https://www.geeksforgeeks.org/problems/string-palindromic-ignoring-spaces4723/1) | [![License](https://img.shields.io/badge/License-MIT-blueviolet)](https://opensource.org/licenses/MIT) |
| :---: | :---: | :---: | :---: | :---: |

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/string-palindromic-ignoring-spaces4723/1).

---

## 📝 Problem Statement

Given a single string `s`, the task is to check if it is a **palindrome sentence** or not.

A palindrome sentence is a sequence of characters, such as a word, phrase, or series of symbols that reads the **same** backward as forward after converting all **uppercase** letters to **lowercase** and **removing** all **non-alphanumeric** characters (including spaces and punctuation).

---

## 📖 Examples

### Example 1:
**Input:** `s = "Too hot to hoot"`
**Output:** `true`
**Explanation:** If we remove all non-alphanumeric characters and convert all uppercase letters to lowercase, string `s` will become `"toohottohoot"` which is a palindrome.

<details>
<summary>📖 Example Breakdown</summary>

1.  **Original String:** `s = "Too hot to hoot"`
2.  **Lowercase:** `too hot to hoot`
3.  **Remove Non-Alphanumeric:** `toohottohoot`
4.  **Check Palindrome:**
    -   Read forwards: `toohottohoot`
    -   Read backwards: `toohottohoot`
    -   They are the same.
5.  **Result:** `true`

</details>

### Example 2:
**Input:** `s = "Abc 012..## 10cbA"`
**Output:** `true`
**Explanation:** If we remove all non-alphanumeric characters and convert all uppercase letters to lowercase, string `s` will become `"abc01210cba"` which is a palindrome.

### Example 3:
**Input:** `s = "ABC $. def01ASDF"`
**Output:** `false`
**Explanation:** The processed string becomes `"abcdef01asdf"`, which is not a palindrome.

---

## ⚙️ Constraints

- `1 ≤ s.length() ≤ 10^6`

---

## 💡 Solution Approaches

### Optimized Approach: Two Pointers

The most efficient way to solve this problem is by using a **two-pointer** technique. We place one pointer at the beginning of the string and another at the end. We move the pointers toward the center, comparing characters while skipping any non-alphanumeric characters.

#### C++ Solution

```cpp
// Intuition: The core idea is to compare the sentence from both ends, moving inwards.
// By ignoring non-alphanumeric characters and case differences, we can check if the
// essential characters form a palindrome.

// Approach:
// 1. Initialize two pointers, `i` at the start (0) and `j` at the end (length - 1) of the string.
// 2. Loop as long as `i` is less than `j`.
// 3. If the character at `i` is not alphanumeric, increment `i`.
// 4. If the character at `j` is not alphanumeric, decrement `j`.
// 5. If both are alphanumeric, compare their lowercase versions.
// 6. If they are not equal, the string is not a palindrome, so return `false`.
// 7. If they are equal, move both pointers towards the center (`i++`, `j--`).
// 8. If the loop finishes, it means all characters matched, so return `true`.

// Time Complexity: O(n), where n is the length of the string, because we traverse the string at most once.
// Space Complexity: O(1), as we only use a constant amount of extra space for the pointers.

class Solution {
  public:
    bool isPalinSent(string &s) {
        int i = 0, j = s.length() - 1;

        // Loop until the two pointers cross.
        while (i < j) {
    
            // Skip non-alphanumeric characters from the left.
            if (!isalnum(s[i]))
                i++;
    
            // Skip non-alphanumeric characters from the right.
            else if (!isalnum(s[j]))
                j--;
    
            // Both characters are alphanumeric, compare them (case-insensitive).
            else if (tolower(s[i]) == tolower(s[j]))
                i++, j--; // Pointers move inwards if characters match.
    
            // If characters do not match, it's not a palindrome.
            else
                return false;
        }
    
        // If the loop completes, the sentence is a palindrome.
        return true;
    }
};

/*
*
* Dry Run
*
* Input: s = "Too hot to hoot"
*
* Initial state:
* i = 0, s[i] = 'T'
* j = 14, s[j] = 't'
*
* Iteration 1:
* isalnum('T') -> true
* isalnum('t') -> true
* tolower('T') == tolower('t') -> 't' == 't' -> true
* i becomes 1, j becomes 13
*
* Iteration 2:
* isalnum('o') -> true
* isalnum('o') -> true
* tolower('o') == tolower('o') -> true
* i becomes 2, j becomes 12
*
* ... (skipping spaces)
*
* Eventually, i will become >= j.
* The loop terminates.
* Return: true
*
*/
```

#### Java Solution

```java
// Intuition: Similar to the C++ approach, we use two pointers to scan the string
// from its edges, focusing only on letters and digits while ignoring case.

// Approach:
// 1. Set a left pointer `i` to 0 and a right pointer `j` to the end of the string.
// 2. Iterate while the left pointer `i` is less than the right pointer `j`.
// 3. Move `i` forward if `s.charAt(i)` is not a letter or digit.
// 4. Move `j` backward if `s.charAt(j)` is not a letter or digit.
// 5. If both characters are alphanumeric, compare them in lowercase.
// 6. If they don't match, return `false`.
// 7. If they match, advance `i` and `j` towards each other.
// 8. If the loop completes without mismatches, return `true`.

// Time Complexity: O(n), as each character is visited at most once by either pointer.
// Space Complexity: O(1), no extra space proportional to the input size is used.

class Solution {
    public boolean isPalinSent(String s) {
        int i = 0, j = s.length() - 1;

        // Compares characters until the pointers meet or cross.
        while (i < j) {

            // Skip non-alphanumeric characters from the left side.
            if (!Character.isLetterOrDigit(s.charAt(i)))
                i++;

            // Skip non-alphanumeric characters from the right side.
            else if (!Character.isLetterOrDigit(s.charAt(j)))
                j--;

            // If characters are alphanumeric, compare them.
            else if (Character.toLowerCase(s.charAt(i)) 
                     == Character.toLowerCase(s.charAt(j))) {
                i++; // Move pointers inward on match.
                j--;
            }
            
            // If characters are not equal, the sentence is not a palindrome.
            else
                return false;
        }

        // If the entire string is checked without mismatch, it's a palindrome.
        return true;
        
    }
}

/*
*
* Dry Run
*
* Input: s = "Abc 012..## 10cbA"
*
* Initial state:
* i = 0, s.charAt(i) = 'A'
* j = 17, s.charAt(j) = 'A'
*
* Iteration 1:
* Character.isLetterOrDigit('A') -> true
* Character.isLetterOrDigit('A') -> true
* Character.toLowerCase('A') == Character.toLowerCase('A') -> 'a' == 'a' -> true
* i becomes 1, j becomes 16
*
* ... (skipping spaces and punctuations)
*
* Iteration (i=3, j=13):
* s.charAt(i) = ' ' -> skip, i becomes 4
*
* Iteration (i=4, s.charAt(i) = '0'), (j=13, s.charAt(j) = '0'):
* They match, i becomes 5, j becomes 12
*
* ...
*
* Eventually, the loop condition i < j becomes false.
* Return: true
*
*/
```

---

## 🔑 Key Insights

- **Two-Pointers:** This is a classic technique for problems that involve checking for symmetry in an array or string. It's highly efficient because it reduces the number of comparisons needed.
- **In-place Filtering:** Instead of creating a new, cleaned string (which would use O(n) space), we filter out non-alphanumeric characters on the fly by just advancing the pointers. This keeps the space complexity at a constant O(1).
- **Case-Insensitive Comparison:** Converting characters to lowercase before comparing them is crucial to correctly handle palindromes like "A man, a plan, a canal: Panama".

---

## 🔗 References

- **Original Problem:** [GeeksforGeeks | Palindrome Sentence](https://www.geeksforgeeks.org/problems/string-palindromic-ignoring-spaces4723/1)
- **Article:** [Two Pointers Technique - GeeksforGeeks](https://www.geeksforgeeks.org/dsa/two-pointers-technique/)

---

## 🧑‍💻 Author

- **Connect with me:** [imnilesh18](https://github.com/imnilesh18)

---

## #️⃣ Tags

`string` `two-pointers` `palindrome` `easy` `geeksforgeeks`

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

> **Reminder:** The solutions are for educational purposes. Always try to solve problems on your own first!