# 📝 Check if a String is Subsequence of Other

<p align="left">
    <a href="https://www.geeksforgeeks.org/problems/given-two-strings-find-if-first-string-is-a-subsequence-of-second/1">
        <img alt="GeeksforGeeks" src="https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks">
    </a>
    <img alt="Difficulty" src="https://img.shields.io/badge/Difficulty-Easy-blue?style=for-the-badge">
    <img alt="Accuracy" src="https://img.shields.io/badge/Accuracy-51.68%25-yellow?style=for-the-badge">
    <img alt="Points" src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge">
    <img alt="License" src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge">
</p>

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/given-two-strings-find-if-first-string-is-a-subsequence-of-second/1).

---

## 🎯 Problem Statement

Given two strings **s1** and **s2**. You have to check that **s1** is a subsequence of **s2** or not.

**Note:** A subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

---

## 🧪 Examples

### Example 1:

```
Input:
s1 = "AXY", s2 = "YADXCP"
Output:
false
Explanation:
s1 is not a subsequence of s2 as 'Y' appears before 'A'.
```

### Example 2:

```
Input:
s1 = "gksrek", s2 = "geeksforgeeks"
Output:
true
Explanation:
If we combine the bold characters of "geeksforgeeks", it equals s1. So s1 is a subsequence of s2.
```

<details>
<summary>📖 Example Breakdown (s1 = "gksrek", s2 = "geeksforgeeks")</summary>

1.  **Initialize Pointers:**

    - `i` (for `s1`) starts at index 0 (`'g'`).
    - `j` (for `s2`) starts at index 0 (`'g'`).

2.  **Iteration 1:**

    - `s1[0]` ('g') == `s2[0]` ('g'). Match found!
    - Increment `i` to 1.
    - Increment `j` to 1.

3.  **Iteration 2 -> 4:**

    - `j` increments until `s2[4]` ('k') matches `s1[1]` ('k').
    - `s1[1]` ('k') == `s2[4]` ('k'). Match found!
    - Increment `i` to 2.
    - Increment `j` to 5.

4.  **Iteration 5 -> 7:**

    - `j` increments until `s2[7]` ('s') matches `s1[2]` ('s').
    - `s1[2]` ('s') == `s2[7]` ('s'). Match found!
    - Increment `i` to 3.
    - Increment `j` to 8.

5.  **Iteration 8:**

    - `j` increments to `s2[8]` ('r') which matches `s1[3]` ('r').
    - `s1[3]` ('r') == `s2[8]` ('r'). Match found!
    - Increment `i` to 4.
    - Increment `j` to 9.

6.  **Iteration 9 -> 10:**

    - `j` increments until `s2[10]` ('e') matches `s1[4]` ('e').
    - `s1[4]` ('e') == `s2[10]` ('e'). Match found!
    - Increment `i` to 5.
    - Increment `j` to 11.

7.  **Iteration 11 -> 12:**

    - `j` increments until `s2[12]` ('k') matches `s1[5]` ('k').
    - `s1[5]` ('k') == `s2[12]` ('k'). Match found!
    - Increment `i` to 6.
    - Increment `j` to 13.

8.  **Conclusion:**
    - The `while` loop terminates because `j` reaches the end of `s2`.
    - We check the final condition: `i == m`.
    - Here, `i` is 6 and `m` (length of `s1`) is 6. The condition `6 == 6` is true.
    - Therefore, `s1` is a subsequence of `s2`.

</details>

---

## ⛓️ Constraints

> `1 ≤ s1.size(), s2.size() ≤ 10^6`

---

## 💡 Solution Approaches

### Optimized Approach (Two Pointers)

The most efficient way to solve this problem is by using a two-pointer technique. We can iterate through both strings simultaneously to check for the ordered presence of characters from `s1` in `s2`.

#### C++ Solution

```cpp
// Intuition: To check if s1 is a subsequence of s2, we can iterate through s2 while looking for the characters of s1 in their correct order.
// Approach: Use two pointers, i for s1 and j for s2. Traverse both strings from the beginning. If a character in s1 matches a character in s2, we move to the next character in s1. We always move to the next character in s2. If we reach the end of s1, it means all its characters were found in s2 in the correct order.
// Time Complexity: O(n), where n is the length of s2, as we traverse s2 at most once.
// Space Complexity: O(1), as we only use a constant amount of extra space for the pointers.
class Solution {
  public:
    bool isSubSeq(string& s1, string& s2) {
        int m = s1.length(), n = s2.length();

        // For s1 to be a subsequence, its length must be
        // smaller than or equal to s2's length.
        if (m > n) return false;

        int i = 0, j = 0; // i for s1, j for s2
        while (i < m && j < n) {
            // If characters match, move to the next char in s1
            if (s1[i] == s2[j])
                i++;
            // Always move to the next char in s2
            j++;
        }

        // If i has reached the end of s1, all characters were found in order
        return i == m;

    }
};
/*
*
* Dry Run
*
* s1 = "gksrek", m = 6
* s2 = "geeksforgeeks", n = 13
*
* Initial: i = 0, j = 0
*
* j=0, s2[0]='g', s1[0]='g' -> Match! i becomes 1.
* j=1, s2[1]='e', s1[1]='k' -> No match.
* j=2, s2[2]='e', s1[1]='k' -> No match.
* j=3, s2[3]='k', s1[1]='k' -> No match. Wait, mistake in manual trace, s2[3] is 'k', s1[1] is 'k'.
* Let's restart dry run carefully.
*
* s1 = "gksrek", s2 = "geeksforgeeks"
* i = 0, j = 0
*
* while (i < 6 && j < 13):
* j=0, s2[0]=='g', s1[0]=='g'. Match. i becomes 1. j becomes 1.
* j=1, s2[1]=='e', s1[1]=='k'. No match. j becomes 2.
* j=2, s2[2]=='e', s1[1]=='k'. No match. j becomes 3.
* j=3, s2[3]=='k', s1[1]=='k'. No match. s2[3] is 'k', s1[1] is 'k'. Match. i becomes 2. j becomes 4.
* j=4, s2[4]=='s', s1[2]=='s'. Match. i becomes 3. j becomes 5.
* j=5, s2[5]=='f', s1[3]=='r'. No match. j becomes 6.
* j=6, s2[6]=='o', s1[3]=='r'. No match. j becomes 7.
* j=7, s2[7]=='r', s1[3]=='r'. Match. i becomes 4. j becomes 8.
* j=8, s2[8]=='g', s1[4]=='e'. No match. j becomes 9.
* j=9, s2[9]=='e', s1[4]=='e'. Match. i becomes 5. j becomes 10.
* j=10, s2[10]=='e', s1[5]=='k'. No match. j becomes 11.
* j=11, s2[11]=='k', s1[5]=='k'. Match. i becomes 6. j becomes 12.
*
* Loop terminates because i is now 6 (i < m is false).
* Return i == m -> 6 == 6 -> true.
*
*/
```

#### Java Solution

```java
// Intuition: To check if s1 is a subsequence of s2, we can iterate through s2 while looking for the characters of s1 in their correct order.
// Approach: Use two pointers, i for s1 and j for s2. Traverse both strings from the beginning. If a character in s1 matches a character in s2, we move to the next character in s1. We always move to the next character in s2. If we reach the end of s1, it means all its characters were found in s2 in the correct order.
// Time Complexity: O(n), where n is the length of s2, as we traverse s2 at most once.
// Space Complexity: O(1), as we only use a constant amount of extra space for the pointers.
class Solution {
    public boolean isSubSeq(String s1, String s2) {
        int m = s1.length(), n = s2.length();

        // For s1 to be a subsequence, its length must be
        // smaller than or equal to s2's length.
        if (m > n) return false;

        int i = 0, j = 0; // i for s1, j for s2
        while (i < m && j < n) {
            // If characters match, move to the next char in s1
            if (s1.charAt(i) == s2.charAt(j))
                i++;
            // Always move to the next char in s2
            j++;
        }

        // If i has reached the end of s1, all characters were found in order
        return i == m;

    }
}
/*
*
* Dry Run
*
* s1 = "AXY", m = 3
* s2 = "YADXCP", n = 6
*
* Initial: i = 0, j = 0
*
* while (i < 3 && j < 6):
* j=0, s2[0]=='Y', s1[0]=='A'. No match. j becomes 1.
* j=1, s2[1]=='A', s1[0]=='A'. Match. i becomes 1. j becomes 2.
* j=2, s2[2]=='D', s1[1]=='X'. No match. j becomes 3.
* j=3, s2[3]=='X', s1[1]=='X'. Match. i becomes 2. j becomes 4.
* j=4, s2[4]=='C', s1[2]=='Y'. No match. j becomes 5.
* j=5, s2[5]=='P', s1[2]=='Y'. No match. j becomes 6.
*
* Loop terminates because j is now 6 (j < n is false).
* Return i == m -> 2 == 3 -> false.
*
*/
```

---

## 🔑 Key Insights

- The **two-pointer approach** is highly effective for sequence-related problems where order matters.
- By only advancing the pointer for the subsequence (`s1`) on a character match, we inherently preserve the required order of characters.
- The algorithm stops as soon as either string is fully traversed, making it efficient as it avoids unnecessary comparisons.

---

## 🚀 Further Exploration

- **Find the Longest Common Subsequence (LCS):** A more complex version where you need to find the longest subsequence common to two strings. This typically requires dynamic programming.
- **Number of Matching Subsequences:** Given a string `S` and an array of words, find how many words are a subsequence of `S`.

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/given-two-strings-find-if-first-string-is-a-subsequence-of-second/1)
- [Two Pointers Technique](https://www.geeksforgeeks.org/two-pointers-technique/)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<p align="left">
    <img alt="Tags" src="https://img.shields.io/badge/Tags-String-blue?style=for-the-badge">
    <img alt="Tags" src="https://img.shields.io/badge/Tags-Two Pointers-lightgrey?style=for-the-badge">
    <img alt="Tags" src="https://img.shields.io/badge/Tags-Subsequence-yellow?style=for-the-badge">
    <img alt="Tags" src="https://img.shields.io/badge/Tags-GeeksforGeeks-green?style=for-the-badge">
</p>

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**A gentle reminder: This content is for educational purposes only. It's important to understand the concepts and not just copy-paste the solutions.**
