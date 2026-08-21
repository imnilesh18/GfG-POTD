# 🔄 Transform String

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/transform-string5648/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-29.76%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-red?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given two strings `s1` and `s2`. Find the minimum number of steps required to transform string `s1` into string `s2`. 

The only allowed operation for the transformation is selecting a character from string `s1` and inserting it in the **beginning** of string `s1`. 

If transformation is not possible, return `-1`.

---

## 💡 Examples

### Example 1
```text
Input: s1 = "abd", s2 = "bad"
Output: 1
Explanation: The conversion can take place in 1 operation: Pick 'b' and place it at the front.
```

### Example 2
```text
Input: s1 = "GeeksForGeeks", s2 = "ForGeeksGeeks"
Output: 3
Explanation: The conversion can take place in 3 operations: 
1. Pick 'r' and place it at the front: s1 = "rGeeksFoGeeks"
2. Pick 'o' and place it at the front: s1 = "orGeeksFGeeks"
3. Pick 'F' and place it at the front: s1 = "ForGeeksGeeks"
```

<details>
<summary><b>📖 Example Breakdown (Walkthrough)</b></summary>

Let's break down Example 1: `s1 = "abd"`, `s2 = "bad"`
1. **Validation**: Both strings have the same characters (`a`, `b`, `d`) and the same length (3). Transformation is possible.
2. **Reverse Traversal**: We look at the strings from right to left.
   - Compare `s1[2]` ('d') and `s2[2]` ('d'). They match. We don't need to move 'd'.
   - Compare `s1[1]` ('b') and `s2[1]` ('a'). Mismatch!
   - Since 'b' doesn't match the required 'a' at this position, 'b' must be moved to the front eventually. We record **1 operation**.
   - We skip 'b' in `s1` and compare the next character `s1[0]` ('a') with `s2[1]` ('a'). They match.
3. **Result**: Only 1 operation was required to align the strings perfectly.
</details>

---

## ⚠️ Constraints

> - `1 <= s1.length(), s2.length() <= 10^4`
> - Both strings consist of uppercase and lowercase English letters.

---

## 💻 Solution Approach

```cpp
// Intuition: To transform s1 to s2 by only moving characters to the front, both strings must be anagrams. Furthermore, any characters in s1 that already match the sequence of s2 from the end do not need to be moved. We only need to count and move the mismatched characters.
// Approach: 
// 1. Check if lengths are equal and both strings have the same character frequencies.
// 2. Use two pointers, i and j, starting from the end of s1 and s2 respectively.
// 3. Traverse backwards: If s1[i] == s2[j], both match, so move both pointers.
// 4. If they don't match, s1[i] must be moved to the front. Increment operation count and move only pointer i.
// Time Complexity: O(N) where N is the length of the string. We traverse the strings a constant number of times.
// Space Complexity: O(1) auxiliary space, as the unordered_map stores at most 256 unique characters, which is constant.

class Solution {
  public:
    int transform(string &s1, string &s2) {

        // Base case: Different lengths cannot be transformed
        if (s1.length() != s2.length()) {
            return -1;
        }

        // Store character frequencies to verify if strings are anagrams
        unordered_map<char, int> m;
        int n = s1.length();
        
        // Count frequencies of characters in s1
        for (int i = 0; i < n; i++) {
            if (m.count(s1[i])) 
                m[s1[i]]++;
            else
                m[s1[i]] = 1;
        }

        // Subtract frequencies based on s2
        for (int i = 0; i < n; i++) {
            if (m.count(s2[i]))
                m[s2[i]]--;
        }

        // If any frequency is non-zero, strings are not anagrams
        for (auto it : m) {
            if (it.second != 0) 
                return -1;
        }

        // Two-pointer greedy approach from right to left
        int i = n - 1, j = n - 1;
        int res = 0;
        
        while (i >= 0 && j >= 0) {
            
            // Mismatch means s1[i] needs to be moved to the front
            while (i >= 0 && s1[i] != s2[j]) {
                res++; // Increment required operations
                i--;   // Move s1 pointer left to find a match for s2[j]
            }

            // Match found or i is exhausted, move both pointers
            i--;
            j--;
        }

        return res;
    }
};

/*
*
* Dry Run
* s1 = "abd", s2 = "bad"
* n = 3. Lengths are equal.
* Frequency map check passes (both have 1 'a', 1 'b', 1 'd'). All counts become 0.
* Two pointers start at the end: i = 2, j = 2, res = 0
* 
* Iteration 1:
* s1[2] ('d') == s2[2] ('d'). Match.
* Decrement both pointers: i = 1, j = 1
*
* Iteration 2:
* s1[1] ('b') != s2[1] ('a'). Mismatch.
* Increment res to 1. Decrement i to 0.
* Now check s1[0] ('a') == s2[1] ('a'). Match found. Break inner loop.
* Decrement both pointers: i = -1, j = 0
*
* Outer loop terminates because i >= 0 is false.
* Return res = 1.
*
*/
```

---

## 🔑 Key Insights

1. **Anagram Pre-requisite:** If the two strings do not contain the exact same characters in the exact same frequencies, it is impossible to transform one into the other. A simple hash map check confirms this in **O(N)** time.
2. **Suffix Matching Logic:** Because the only allowed operation is pushing a character to the *front*, any characters that are already properly aligned at the *back* of both strings should be left completely alone.
3. **Greedy Backward Traversal:** By iterating with two pointers from the end of the strings to the beginning, we can greedily find which characters in `s1` naturally fall into place with `s2`. Any character in `s1` that disrupts this flow is forced to be moved to the front.

---

## 🌍 Further Exploration

Looking to strengthen your string manipulation and greedy algorithm skills? Check out these related problems:
*   [Minimum number of bracket reversals needed to make an expression balanced](https://www.geeksforgeeks.org/problems/count-the-reversals/1)
*   [Anagram](https://www.geeksforgeeks.org/problems/anagram-1587115620/1)
*   [Check if string is rotated by two places](https://www.geeksforgeeks.org/problems/check-if-string-is-rotated-by-two-places-1587115620/1)

---

## 🔗 References

- **Original Problem:** [GeeksforGeeks - Transform String](https://www.geeksforgeeks.org/problems/transform-string5648/1)

---

## 🧑‍💻 Author

**Nilesh**
*   GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Hash` `Strings` `Map` `Two-Pointers` `Directi` `GeeksforGeeks`