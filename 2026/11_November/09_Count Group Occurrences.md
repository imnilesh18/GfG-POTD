# 🟢 Count Group Occurrences

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Accuracy-27.88%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License: MIT" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a string `s` and an integer `k`, count the number of distinct characters that appear in **exactly `k` groups** in the string.

A group is defined as one or more consecutive occurrences of the same character. For example, in the string `"aaabbcca"`, the groups are `"aaa"`, `"bb"`, `"cc"`, and `"a"`.

---

## 💡 Examples

```text
Input: s = "abc", k = 1
Output: 3
Explanation: The characters 'a', 'b' and 'c' each appear in exactly one group.
```

```text
Input: s = "aaaaa", k = 2
Output: 0
Explanation: The character 'a' appears in only one group, so no character appears in exactly two groups.
```

<details>
<summary>📖 <b>Example Breakdown (s = "geeksforgeeks", k = 2)</b></summary>

1. We traverse the string and identify character groups based on where characters change.
2. Groups identified: `"g"`, `"ee"`, `"k"`, `"s"`, `"f"`, `"o"`, `"r"`, `"g"`, `"ee"`, `"k"`, `"s"`.
3. Tracking group frequencies:
   - `g`: 2 groups
   - `e`: 2 groups
   - `k`: 2 groups
   - `s`: 2 groups
   - `f`: 1 group
   - `o`: 1 group
   - `r`: 1 group
4. Since we are looking for characters with exactly `k = 2` groups, the qualifying characters are `g`, `e`, `k`, and `s`.
5. **Output = 4**.
</details>

---

## ⚠️ Constraints

> - `1 ≤ s.size() ≤ 10^5`
> - `1 ≤ k ≤ 10^3`
> - `s` consists only of lowercase English alphabets.

---

## 💻 Solution Approach

```cpp
// Intuition: A new group of a character only begins when we encounter a character different from the previous one, or at the start of the string. By counting these start points, we track how many disjoint groups exist for each character.
// Approach:
// 1. Create a `groupCount` array of size 26 initialized to 0 to store group occurrences for each character.
// 2. Iterate through the string character by character.
// 3. For each character, if it is the first character or differs from the previous one, increment its count in `groupCount`.
// 4. After processing the string, iterate through the `groupCount` array.
// 5. Count how many characters have exactly `k` groups and return this count.
// Time Complexity: O(n) where n is the length of the string, as we iterate through it exactly once. The second loop is constant O(26).
// Space Complexity: O(1) auxiliary space, as we only use a fixed-size array of 26 elements.

class Solution {
  public:
    int getCount(string &s, int k) {
        // Array to keep track of group counts for each of the 26 letters
        int groupCount[26] = {0};
        int n = s.length();
        
        for (int i = 0; i < n; i++) {
            // A new group starts at the beginning of the string 
            // or when the current character is different from the previous one
            if (i == 0 || s[i] != s[i - 1]) {
                groupCount[s[i] - 'a']++;
            }
        }
        
        int ans = 0;
        // Check which characters appeared in exactly 'k' groups
        for (int i = 0; i < 26; i++) {
            if (groupCount[i] == k) {
                ans++;
            }
        }
        
        return ans;
    }
};

/*
*
* Dry Run
* Input: s = "geeksforgeeks", k = 2
*
* Step-by-step:
* 'g' (i=0) -> New group. groupCount['g'] = 1
* 'e' (i=1) -> New group. groupCount['e'] = 1
* 'e' (i=2) -> Same as prev. Ignored.
* 'k' (i=3) -> New group. groupCount['k'] = 1
* 's' (i=4) -> New group. groupCount['s'] = 1
* 'f' (i=5) -> New group. groupCount['f'] = 1
* 'o' (i=6) -> New group. groupCount['o'] = 1
* 'r' (i=7) -> New group. groupCount['r'] = 1
* 'g' (i=8) -> New group. groupCount['g'] = 2
* 'e' (i=9) -> New group. groupCount['e'] = 2
* 'e' (i=10) -> Same as prev. Ignored.
* 'k' (i=11) -> New group. groupCount['k'] = 2
* 's' (i=12) -> New group. groupCount['s'] = 2
*
* Final Array counts exactly 2: g(2), e(2), k(2), s(2)
* Output: 4
*
*/
```

---

## 🔍 Key Insights

- **Avoid Redundant Work:** You don't need to manually parse and extract substring chunks to find groups. Simply identifying the boundary where a character sequence breaks (using `s[i] != s[i - 1]`) is mathematically equivalent and highly optimized.
- **Fixed-Size Data Structures:** Since the problem strictly limits the string to lowercase English alphabets, we can confidently use a static array of size 26 instead of an overhead-heavy hash map. This guarantees an $O(1)$ space footprint.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might want to try these related concepts:
- **String Compression** algorithms.
- **Run-Length Encoding (RLE)** techniques.
- **Two-Pointer / Sliding Window** string manipulation challenges.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Count Group Occurrences](https://www.geeksforgeeks.org/problems/count-the-characters1821/1)
- **Topics Covered:** Strings, Counting Frequencies.

---

## 👨‍💻 Author

**Nilesh Kumar**
- GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Strings` `#Arrays` `#Counting` `#GeeksForGeeks` `#C++` `#Competitive-Programming`