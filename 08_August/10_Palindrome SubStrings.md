# 🟧 Palindrome SubStrings

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-45.8%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

</div>

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/count-palindrome-sub-strings-of-a-string0652/1).

---

## 📝 Problem Statement

Given a string `s`, count all palindromic sub-strings present in the string. The length of the palindromic sub-string must be **greater than or equal to 2**.

**Note:** A substring is palindromic if it reads the same forwards and backwards.

---

## 🧪 Examples

### Example 1:

```
Input: s = "abaab"
Output: 3
Explanation: All palindromic substrings (of length > 1) are: "aba", "aa", "baab".
```

<details>
<summary>📖 Example Breakdown</summary>

Let's walk through the input `s = "abbaeae"` from the dry run:

- **Odd-length palindromes:**
  - Center at `e` (index 4): `aea` is a palindrome. `count = 1`.
  - Center at `a` (index 5): `eae` is a palindrome. `count = 2`.
- **Even-length palindromes:**
  - Center between `b` and `b` (indices 1, 2): `bb` is a palindrome. `count = 3`.
  - Expanding from `bb`: `abba` is also a palindrome. `count = 4`.

The final count of palindromic substrings with length >= 2 is **4**.

</details>

### Example 2:

```
Input: s = "aaa"
Output: 3
Explanation: All palindromic substrings (of length > 1) are: "aa", "aa", "aaa".
```

### Example 3:

```
Input: s = "abbaeae"
Output: 4
Explanation: All palindromic substrings (of length > 1) are: "bb", "abba", "aea", "eae".
```

---

## ⛓️ Constraints

> `2 ≤ s.size() ≤ 5 * 10^3`
> `s` contains only lowercase english characters.

---

## 💡 Solution Approaches

### Optimized Approach: Expand from Center

The most efficient approach for this problem is to use the "Expand from Center" technique. The fundamental idea is that every palindrome is symmetric around a central point. This center can be a single character (for odd-length palindromes like "aba") or the space between two adjacent characters (for even-length palindromes like "abba").

We iterate through all `2N-1` potential centers in the string. For each center, we expand outwards with two pointers, `left` and `right`, as long as the pointers are within the string bounds and the characters at those positions match. Each time they match, we've found a valid palindromic substring, so we increment our counter.

#### C++ Solution

```cpp
// Intuition: Every palindrome has a center. We can iterate through all possible centers and expand outwards to count all palindromes. A center can be a single character (for odd length) or a pair of adjacent characters (for even length).
// Approach: Expand around center for each index (for odd and even length palindromes).
// Time Complexity: O(n^2) - In the worst case, each of the 2n-1 centers expands across the entire string.
// Space Complexity: O(1) - Only a few extra variables are used for pointers and the counter.

class Solution {
  public:
    int countPS(string &s) {
        int n = s.size();
        int count = 0;

        // Count odd length palindromic substrings (using each character as center)
        for (int i = 0; i < n; i++) {
            int left = i - 1;
            int right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                count++;        // Found a palindrome (length >= 3)
                left--;         // Expand to the left
                right++;        // Expand to the right
            }
        }

        // Count even length palindromic substrings (using adjacent characters as center)
        for (int i = 0; i < n; i++) {
            int left = i;
            int right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                count++;        // Found a palindrome (length 2 or more)
                left--;         // Expand to the left
                right++;        // Expand to the right
            }
        }
        return count;
    }
};

/*
*
* Dry Run
*
* Input: s = "abbaeae"
* n = 7, count = 0
*
* Odd Length Check:
* i = 0 ('a'): center 'a' -> no expansion.
* i = 1 ('b'): center 'b' -> s[0]!=s[2].
* i = 2 ('b'): center 'b' -> s[1]!=s[3].
* i = 3 ('a'): center 'a' -> s[2]!=s[4].
* i = 4 ('e'): center 'e' -> s[3]==s[5] ('a'=='a'). count becomes 1. Palindrome: "aea". Expand: s[2]!=s[6].
* i = 5 ('a'): center 'a' -> s[4]==s[6] ('e'=='e'). count becomes 2. Palindrome: "eae". Expand: left=3, right=7 (out).
* i = 6 ('e'): center 'e' -> no expansion.
*
* Even Length Check:
* i = 0: s[0]!=s[1].
* i = 1: s[1]==s[2] ('b'=='b'). count becomes 3. Palindrome: "bb". Expand: s[0]==s[3] ('a'=='a'). count becomes 4. Palindrome: "abba". Expand: left=-1 (out).
* i = 2 to 5: No initial matches.
*
* Final Count: 4
*/
```

#### Java Solution

```java
// Intuition: Every palindrome is symmetric. We can treat each character and each pair of adjacent characters as a potential center and expand outwards to find all palindromes.
// Approach: Expand around center for each index (for odd and even length palindromes).
// Time Complexity: O(n^2) - We check 2n-1 potential centers, and each expansion can take O(n) time.
// Space Complexity: O(1) - We only use a constant amount of extra space for variables.

class Solution {
    public int countPS(String s) {
        int n = s.length();
        int count = 0;

        // Count odd length palindromic substrings (center is a single character)
        for (int i = 0; i < n; i++) {
            int left = i - 1;
            int right = i + 1;
            while (left >= 0 && right < n && s.charAt(left) == s.charAt(right)) {
                count++;        // Found a palindrome of length >= 3
                left--;         // Expand outwards
                right++;
            }
        }

        // Count even length palindromic substrings (center is between two characters)
        for (int i = 0; i < n; i++) {
            int left = i;
            int right = i + 1;
            while (left >= 0 && right < n && s.charAt(left) == s.charAt(right)) {
                count++;        // Found a palindrome of length >= 2
                left--;         // Expand outwards
                right++;
            }
        }
        return count;
    }
}

/*
*
* Dry Run
*
* Input: s = "abbaeae"
* n = 7, count = 0
*
* Odd Length Check:
* i = 0 ('a'): center 'a' -> no expansion.
* i = 1 ('b'): center 'b' -> s.charAt(0)!=s.charAt(2).
* i = 2 ('b'): center 'b' -> s.charAt(1)!=s.charAt(3).
* i = 3 ('a'): center 'a' -> s.charAt(2)!=s.charAt(4).
* i = 4 ('e'): center 'e' -> s.charAt(3)==s.charAt(5) ('a'=='a'). count is 1. ("aea"). Expand: s.charAt(2)!=s.charAt(6). Stop.
* i = 5 ('a'): center 'a' -> s.charAt(4)==s.charAt(6) ('e'=='e'). count is 2. ("eae"). Expand: left=3, right=7 (out). Stop.
* i = 6 ('e'): center 'e' -> no expansion.
*
* Even Length Check:
* i = 0: s.charAt(0)!=s.charAt(1).
* i = 1: s.charAt(1)==s.charAt(2) ('b'=='b'). count is 3. ("bb"). Expand: s.charAt(0)==s.charAt(3) ('a'=='a'). count is 4. ("abba"). Expand: left=-1 (out). Stop.
* i = 2 to 5: No initial matches.
*
* Final Count: 4
*/
```

---

## 🎯 Key Insights

- **Time vs. Space Trade-off**: While dynamic programming can also solve this in O(N^2) time, it requires O(N^2) space to store the palindrome table. The "Expand from Center" method provides the same time complexity but with a superior O(1) space complexity, making it the preferred solution.
- **Handling All Centers**: The key to correctness is ensuring all `2N-1` potential centers are checked. A separate loop for odd-length (N centers at `i`) and even-length (N-1 centers between `i` and `i+1`) guarantees complete coverage.

---

## 🚀 Further Exploration

- [Palindromic Partitioning](https://www.geeksforgeeks.org/problems/palindromic-patitioning4845/1): Find the minimum cuts needed to partition a string into palindromic substrings.

---

## 📚 References

- **Original Problem:** [GeeksforGeeks - Count Palindrome Sub-strings of a string](https://www.geeksforgeeks.org/problems/count-palindrome-sub-strings-of-a-string0652/1)

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## #️⃣ Tags

`string` `palindrome` `two-pointers` `expand-around-center` `geeksforgeeks` `hard-problem`

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**A Note on Educational Use:** This solution is intended for learning and reference. Please try to solve the problem on your own first to maximize the educational benefit.
