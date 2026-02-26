# 🟢 Isomorphic Strings

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-34.21%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-blue?style=for-the-badge)

⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two strings `s1` and `s2` consisting of only lowercase English letters and of **equal length**, check if these two strings are **isomorphic** to each other.

If the characters in `s1` can be changed to get `s2`, then two strings, `s1` and `s2` are isomorphic. A character must be completely swapped out for another character while maintaining the order of the characters. A character may map to itself, but no two characters may map to the same character.

## 💡 Examples

<details>
<summary>📖 Example Breakdown 1</summary>

```text
Input: s1 = "aab", s2 = "xxy"
Output: true
Explanation: 
Each character in s1 can be consistently mapped to a unique character in s2 (a → x, b → y).
```
</details>

```text
Input: s1 = "aab", s2 = "xyz"
Output: false
Explanation: Same character 'a' in s1 maps to two different characters 'x' and 'y' in s2.
```

```text
Input: s1 = "abc", s2 = "xxz"
Output: false
Explanation: Two different characters 'a' and 'b' in s1 maps with same character 'x' in s2.
```

## 🚨 Constraints

- `1 <= s1.size() = s2.size() <= 10^5`

---

## 🛠️ Solution Approaches

### 1️⃣ Optimized Hash Map Approach

**Intuition:** Two strings are isomorphic if the characters at the exact same positions in both strings have the exact same "first occurrence" indices. By storing the index of the first time we see a character, we can compare the historical positions of the current characters.

```cpp
// Intuition: Two strings are isomorphic if their characters map uniquely and consistently. We can track the first occurrence index of each character to verify this mapping.
// Approach: Iterate through both strings simultaneously. Store the first occurrence index of each character in two separate hash maps. For every position, compare the stored indices; if they differ, the mapping is inconsistent.
// Time Complexity: O(n), where n is the length of the strings, as we iterate through them once and hash map operations take O(1) on average.
// Space Complexity: O(1), since the maps will store at most 26 lowercase English characters.
class Solution {
  public:
    bool areIsomorphic(string &s1, string &s2) {

        unordered_map<char, int> m1, m2; // Maps to store first occurrence indices
    
        for (int i = 0; i < s1.length(); ++i) {
    
            // If character not seen before, store its
            // first occurrence index
            if (m1.find(s1[i]) == m1.end()) {
                m1[s1[i]] = i;
            }
            
            // Do the same for the second string
            if (m2.find(s2[i]) == m2.end()) {
                m2[s2[i]] = i;
            }
    
            // Check if the first occurrence indices match
            if (m1[s1[i]] != m2[s2[i]]) {
                return false; // Mismatch implies not isomorphic
            }
        }
        
        return true; // All characters mapped consistently
    }
};

/*
*
* Dry Run
* Input: s1 = "aab", s2 = "xxy"
* * i = 0: s1[0]='a', s2[0]='x'
* m1 does not have 'a', so m1['a'] = 0
* m2 does not have 'x', so m2['x'] = 0
* m1['a'] (0) == m2['x'] (0), continue.
*
* i = 1: s1[1]='a', s2[1]='x'
* m1 has 'a', map unchanged.
* m2 has 'x', map unchanged.
* m1['a'] (0) == m2['x'] (0), continue.
*
* i = 2: s1[2]='b', s2[2]='y'
* m1 does not have 'b', so m1['b'] = 2
* m2 does not have 'y', so m2['y'] = 2
* m1['b'] (2) == m2['y'] (2), continue.
* * Loop finishes. Return true.
*
*/
```

---

## 🧠 Key Insights

- **Index Tracking Technique:** Instead of maintaining a complex two-way mapping (`char -> char`), tracking the *first occurrence index* ensures that both characters share the exact same structural pattern without edge case collisions.
- **O(1) Space Bound:** Because the problem is restricted to lowercase English letters, the `unordered_map` will hold a maximum of 26 keys, making the auxiliary space strictly constant `O(1)`.

## 🔗 Further Exploration

- [Check if two strings are k-anagrams](https://www.geeksforgeeks.org/check-if-two-strings-are-k-anagrams-or-not/)
- [Anagram Palindrome](https://www.geeksforgeeks.org/check-if-characters-of-a-given-string-can-be-rearranged-to-form-a-palindrome/)
- Try solving this without using `unordered_map`, but instead using standard arrays of size `256` for character mapping!

## 📚 References

- **Original Problem:** [GeeksforGeeks - Isomorphic Strings](https://www.geeksforgeeks.org/problems/isomorphic-strings-1587115620/1)

## ✍️ Author

GitHub: [imnilesh18](https://github.com/imnilesh18)

## 🏷️ Tags

`Strings` `Data Structures` `Hash` `Google`