# 📏 Longest Periodic Proper Prefix

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/longest-periodic-proper-prefix/1).

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GFG Badge"/>
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty Badge"/>
  <img src="https://img.shields.io/badge/Accuracy-44.36%25-orange?style=for-the-badge" alt="Accuracy Badge"/>
  <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points Badge"/>
  <img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License Badge"/>
</div>

---

## 📝 Problem Statement

Given a string `s`, find the length of the **longest periodic proper prefix** of `s`. If no such prefix exists, return `-1`.

A **periodic proper prefix** is a non-empty prefix of `s` (but not the whole string), such that repeating this prefix enough times produces a string that _starts_ with `s`.

---

## 🧪 Examples

### Example 1

```
Input: s = "aaaaaa"
Output: 5
Explanation:
The proper prefix "aaaaa" (length 5) is periodic.
Repeating it gives "aaaaa" + "aaaaa" = "aaaaaaaaaa...".
The original string "aaaaaa" is a prefix of this repeated string.
No longer proper prefix satisfies this condition.
```

### Example 2

```
Input: s = "abcab"
Output: 3
Explanation:
Repeating the proper prefix "abc" (length 3) forms "abcabc...", which contains "abcab" as a prefix.
```

<details>
<summary>📖 Example 2 Breakdown</summary>

Let's walk through `s = "abcab"`:

1.  **Identify Proper Prefixes:**

    - `a` (length 1)
    - `ab` (length 2)
    - `abc` (length 3)
    - `abca` (length 4)

2.  **Test Each Prefix for Periodicity:**

    - **Prefix "a"**: Repeating it gives `"aaaaa..."`. Is `"abcab"` a prefix of `"aaaaa..."`? No.
    - **Prefix "ab"**: Repeating it gives `"ababab..."`. Is `"abcab"` a prefix of `"ababab..."`? No.
    - **Prefix "abc"**: Repeating it gives `"abcabc..."`. Is `"abcab"` a prefix of `"abcabc..."`? Yes. This is a valid periodic proper prefix of length 3.
    - **Prefix "abca"**: Repeating it gives `"abcaabca..."`. Is `"abcab"` a prefix of `"abcaabca..."`? No.

3.  **Find the Longest:**
    - The only valid periodic proper prefix we found is `"abc"` with length `3`.
    - Therefore, the answer is `3`.

</details>

### Example 3

```
Input: s = "ababd"
Output: -1
Explanation:
No proper prefix satisfies the given condition. For example, repeating "ab" gives "ababab...", and "ababd" is not a prefix of it.
```

---

## ⛓️ Constraints

> `1 ≤ s.size() ≤ 10^5` > `s` consists of lowercase English alphabets

---

## 💡 Solution Approaches

### Optimized Approach: Z-Algorithm

The core idea is to use the **Z-Algorithm**, which efficiently computes a Z-array. The Z-array `z` for a string `s` of length `n` is an array where `z[i]` is the length of the longest substring starting from `s[i]` that is also a prefix of `s`.

A proper prefix of length `L` is periodic if the rest of the string `s[L:]` is a prefix of the original string `s`. This condition can be checked using the Z-array: `z[L] >= n - L`.

To find the _longest_ such prefix, we can check this condition by iterating `i` from `n-1` down to `1`. The first `i` that satisfies `z[i] == n - i` gives us the length of the longest periodic proper prefix. This is because `z[i] == n - i` implies that the suffix `s[i:]` (length `n-i`) is _exactly_ equal to the prefix `s[0:n-i]`. This structure guarantees that the prefix `s[0:i]` is periodic.

---

### C++ Solution

```cpp
// Intuition: The problem asks for a prefix P such that S is a prefix of P+P+P...
// This is equivalent to finding the largest proper prefix P = s[0...i-1] where the remaining part of the string s[i...n-1] is a prefix of P.
// The Z-algorithm helps identify substrings that are also prefixes of the main string.
//
// Approach:
// 1. Compute the Z-array for the input string 's'.
// 2. The Z-array element z[i] stores the length of the longest substring starting at index 'i' that matches the prefix of 's'.
// 3. We are looking for the largest 'i' (where i is the length of the prefix) such that the suffix s[i:] is a prefix of s.
// 4. This condition is perfectly captured by checking if z[i] == n - i. This means the substring from 'i' to the end matches the prefix of 's' of the same length.
// 5. We iterate from the end of the string (i = n - 1) down to 1 to find the largest such 'i'.
// 6. The first 'i' that satisfies the condition is our answer. If no such 'i' is found, it means no such prefix exists, so we return -1.
//
// Time Complexity: O(n), where n is the length of the string. The Z-algorithm runs in linear time.
// Space Complexity: O(n) to store the Z-array.

class Solution {
 public:
    // Function to compute the Z-array for a string.
    // z[i] = length of the longest substring starting at s[i] that is also a prefix of s.
    vector<int> zFunction(string &s) {
        int n = s.size();
        vector<int> z(n);

        // [l, r] defines the current "Z-box", a window that matches a prefix of s.
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            // If i is inside the current Z-box, we can initialize z[i] smartly.
            if (i <= r) {
                // z[i] is at least the minimum of the remaining length of the box and the pre-computed value.
                z[i] = min(r - i + 1, z[i - l]);
            }
            // Try to extend the match character by character.
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            // If the current match extends beyond the old Z-box, update the box boundaries.
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    int getLongestPrefix(string &s) {
        int n = s.size();
        if (n <= 1) return -1; // A proper prefix must exist.

        // Compute the Z-array for the string.
        vector<int> z = zFunction(s);

        // Traverse the Z-array from the end to find the longest proper prefix.
        // We look for a position 'i' where the suffix s[i:] is identical to the prefix s[0:n-i].
        for (int i = n - 1; i > 0; i--) {
            // The condition z[i] == n - i confirms that the suffix of length (n-i)
            // starting at index 'i' is exactly equal to the prefix of the same length.
            // This means the prefix of length 'i' is periodic.
            if (z[i] == n - i) {
                return i; // Found the longest one, so return its length.
            }
        }

        // If the loop completes, no such periodic proper prefix was found.
        return -1;
    }
};

/*
*
* Dry Run
*
* Input: s = "abcab"
* n = 5
*
* 1. Call zFunction("abcab"):
* - s = "abcab"
* - z-array calculation:
* - i=1: s[1]!='a' -> z[1]=0
* - i=2: s[2]!='a' -> z[2]=0
* - i=3: s[3]=='a', s[4]=='b'. Match "ab". -> z[3]=2
* - i=4: s[4]!='a' -> z[4]=0
* - Returns z = [0, 0, 0, 2, 0] (conceptually z[0]=n)
*
* 2. Call getLongestPrefix:
* - Loop from i = 4 down to 1.
* - i = 4: z[4] is 0. n-i is 1. (0 != 1). Continue.
* - i = 3: z[3] is 2. n-i is 2. (2 == 2). Condition met!
* - Return i, which is 3.
*
* Final Output: 3
*/
```

---

### Java Solution

```java
// Intuition: The problem asks for a prefix P such that S is a prefix of P+P+P...
// This is equivalent to finding the largest proper prefix P = s.substring(0, i) where the remaining part of the string s.substring(i) is a prefix of P.
// The Z-algorithm helps identify substrings that are also prefixes of the main string.
//
// Approach:
// 1. Compute the Z-array for the input string 's'.
// 2. The Z-array element z[i] stores the length of the longest substring starting at index 'i' that matches the prefix of 's'.
// 3. We are looking for the largest 'i' (where i is the length of the prefix) such that the suffix s.substring(i) is a prefix of s.
// 4. This condition is perfectly captured by checking if z[i] == n - i. This means the substring from 'i' to the end matches the prefix of 's' of the same length.
// 5. We iterate from the end of the string (i = n - 1) down to 1 to find the largest such 'i'.
// 6. The first 'i' that satisfies the condition is our answer. If no such 'i' is found, it means no such prefix exists, so we return -1.
//
// Time Complexity: O(n), where n is the length of the string. The Z-algorithm runs in linear time.
// Space Complexity: O(n) to store the Z-array.

class Solution {
    // function to compute Z-array
    // z[i] = length of the longest substring starting at i
    // that matches the prefix of s
    public static int[] zFunction(String s) {
        int n = s.length();
        int[] z = new int[n];

        // [l, r] is the current segment that matches a prefix (the "Z-box")
        int l = 0, r = 0;
        for (int i = 1; i < n; ++i) {
            // If i is inside the Z-box, we can optimize the initial value of z[i].
            if (i <= r) {
                // Reuse previously computed values to get a head start.
                z[i] = Math.min(r - i + 1, z[i - l]);
            }
            // Naively extend the match from the current position.
            while (i + z[i] < n && s.charAt(z[i]) == s.charAt(i + z[i])) {
                z[i]++;
            }
            // If we found a match that extends beyond the current Z-box, update the box.
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    public static int getLongestPrefix(String s) {
        int n = s.length();
        if (n <= 1) return -1; // Proper prefix is not possible.

        // Compute the Z-array for the given string.
        int[] z = zFunction(s);

        // Traverse z-array from right to left to find the longest prefix.
        // We want to find the largest 'i' where the suffix s[i:] equals the prefix s[0:n-i].
        for (int i = n - 1 ; i > 0; i--) {
            // The condition z[i] == n - i checks if the suffix starting at 'i'
            // is identical to a prefix of s of the same length.
            // This means the prefix of length 'i' is periodic.
            if (z[i] == n - i) {
                return i; // Since we scan from the end, the first match is the longest.
            }
        }

        // If no such prefix is found after checking all possibilities.
        return -1;
    }
}

/*
*
* Dry Run
*
* Input: s = "abcab"
* n = 5
*
* 1. Call zFunction("abcab"):
* - s = "abcab"
* - z array calculation:
* - i=1: s.charAt(1)!='a' -> z[1]=0
* - i=2: s.charAt(2)!='a' -> z[2]=0
* - i=3: s.charAt(3)=='a', s.charAt(4)=='b'. Match "ab". -> z[3]=2
* - i=4: s.charAt(4)!='a' -> z[4]=0
* - Returns z = {0, 0, 0, 2, 0}
*
* 2. Call getLongestPrefix:
* - Loop from i = 4 down to 1.
* - i = 4: z[4] is 0. n-i is 1. (0 != 1). Continue.
* - i = 3: z[3] is 2. n-i is 2. (2 == 2). Condition met.
* - Return i, which is 3.
*
* Final Output: 3
*/
```

---

## 🎯 Key Insights

The Z-algorithm provides a powerful and linear-time solution for a problem that seems to require complex pattern matching. The key insight is translating the problem's definition of a "periodic proper prefix" into a concrete, checkable condition using the Z-array.

The condition `z[i] == n - i` is a clever way to verify periodicity. It confirms that the string `s` is composed of a prefix `P = s[0:i]` followed by a suffix that is identical to the beginning of `P`. This structure `s = P_start + P_start_prefix` is precisely what allows `P` to generate `s` when repeated.

---

## 🗺️ Further Exploration

- **[Z-algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/)**: A detailed article on how the Z-algorithm works.
- **[KMP Algorithm](https://www.geeksforGeeks.org/kmp-algorithm-for-pattern-searching/)**: Another famous linear-time pattern-searching algorithm that uses a precomputed LPS (Longest Proper Prefix which is also Suffix) array. It solves a different but related class of problems.
- **[Minimum Period of a String](https://www.geeksforgeeks.org/find-the-minimum-length-of-a-string-that-has-given-string-as-prefix/)**: A related problem that can also be solved using string algorithms.

---

## 📚 References

- **[Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/longest-periodic-proper-prefix/1)**

---

## 👨‍💻 Author

> **GitHub**: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<div align="left">
  <img src="https://img.shields.io/badge/Z Algorithm-20232A?style=for-the-badge" alt="Z-Algorithm Badge"/>
  <img src="https://img.shields.io/badge/String-EA4C89?style=for-the-badge" alt="String Badge"/>
  <img src="https://img.shields.io/badge/Pattern Searching-3498DB?style=for-the-badge" alt="Pattern Searching Badge"/>
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GFG Badge"/>
</div>

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**A Note on Educational Use:** This solution is intended for learning and reference. Please try to solve the problem on your own first to maximize the educational benefit.
