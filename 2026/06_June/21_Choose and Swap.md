# 🔀 Choose and Swap

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-22.67%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given a string `s` of lowercase English letters, you can swap all occurrences of any two distinct characters **at most once**. Return the **lexicographically smallest** string possible after performing this operation.

---

## 💡 Examples

### Example 1
```text
Input: s = "ccad"
Output: "aacd"
Explanation: In "ccad", we choose 'a' and 'c'. After doing the replacement operation once, we get "aacd". This is the lexicographically smallest string possible.
```

### Example 2
```text
Input: s = "abba"
Output: "abba"
Explanation: In "abba", we can get "baab" after doing the replacement operation once for 'a' and 'b', but that is not lexicographically smaller than "abba". So, the answer is "abba".
```

<details>
<summary><b>📖 Example Breakdown (ccad)</b></summary>

1. We have string `"ccad"`.
2. First character is `'c'`. We check if there is any smaller character (`'a'` or `'b'`) that appears later in the string.
3. `'a'` is smaller than `'c'`, and its first appearance is at index `2`, which is strictly after the first appearance of `'c'` (index `0`).
4. We swap all `'c'`s with `'a'`s and all `'a'`s with `'c'`s.
5. The string `"ccad"` transforms into `"aacd"`.
6. Since we are allowed at most one swap operation, we break and return `"aacd"`.
</details>

---

## ⚙️ Constraints

> - `1 ≤ |s| ≤ 10^5`
> - `s` consists of lowercase English letters only.

---

## 🚀 Solution Approaches

### Optimal Approach (Greedy with Hashing)

**Intuition:** To make the string lexicographically as small as possible, we should find the earliest character in the string that can be replaced by a strictly smaller character appearing later in the string.

```cpp
// Intuition: To get the lexicographically smallest string, we should replace the first possible character with a smaller character that appears later in the string.
// Approach:
// 1. Record the first occurrence index of every character present in the string.
// 2. Iterate through the string. For each character, check if there's any strictly smaller character (from 'a' up to current character - 1) whose first occurrence is after the current character's first occurrence.
// 3. The first time we find such a pair, we swap all occurrences of these two characters in the string and break, as we only need one swap operation to achieve the optimal result.
// Time Complexity: O(N) where N is the length of the string. We iterate the string a few times, and the inner loop runs at most 26 times.
// Space Complexity: O(1) as we only use a fixed size array of 26 integers to store indices.

class Solution {
  public:
    string chooseSwap(string &s) {
        int first_idx[26];
        
        // Initialize all indices to -1
        for (int i = 0; i < 26; i++) {
            first_idx[i] = -1;
        }
        
        // Store the first appearance of each character
        for (int i = 0; i < s.length(); i++) {
            if (first_idx[s[i] - 'a'] == -1) {
                first_idx[s[i] - 'a'] = i;
            }
        }
        
        // Traverse to find the first character that can be swapped
        for (int i = 0; i < s.length(); i++) {
            bool swapped = false;
            
            // Check all smaller characters
            for (int j = 0; j < s[i] - 'a'; j++) {
                // If a smaller character appears later, it's a valid swap
                if (first_idx[j] > first_idx[s[i] - 'a']) {
                    char char1 = s[i];
                    char char2 = j + 'a';
                    
                    // Swap all occurrences of char1 and char2
                    for (int k = 0; k < s.length(); k++) {
                        if (s[k] == char1) s[k] = char2;
                        else if (s[k] == char2) s[k] = char1;
                    }
                    swapped = true;
                    break; // Swap complete
                }
            }
            if (swapped) break; // Stop after at most one replacement operation
        }
        
        return s;
    }
};

/*
*
* Dry Run
* Input: s = "ccad"
* 1. first_idx array: 'a'=2, 'c'=0, 'd'=3 (others -1)
* 2. Loop i = 0, s[0] = 'c'.
* 3. Inner loop j from 0 to 1 ('a' to 'b').
* 4. j=0 ('a'). first_idx['a'] (2) > first_idx['c'] (0). True!
* 5. Swap 'c' and 'a' in the entire string.
* k=0: s[0]='c' -> 'a'
* k=1: s[1]='c' -> 'a'
* k=2: s[2]='a' -> 'c'
* k=3: s[3]='d' unchanged
* 6. String becomes "aacd".
* 7. swapped = true, break inner and outer loop.
* 8. Return "aacd".
*
*/
```

---

## 🧠 Key Insights

- **Greedy Strategy:** By iterating from the start of the string, we ensure the leftmost possible character is minimized. By checking candidate swap characters starting from `'a'` upwards, we guarantee maximum reduction in lexicographical order.
- **Constant Space Advantage:** Using a fixed-size array (`26` for the English alphabet) reduces lookup times to $O(1)$, which is highly efficient.

---

## 🔍 Further Exploration

- [Lexicographically Smallest String After Applying Operations](https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/)
- [Smallest String With Swaps](https://leetcode.com/problems/smallest-string-with-swaps/)

---

## 🔗 References

- **GeeksforGeeks Problem:** [Choose and Swap](https://www.geeksforgeeks.org/problems/choose-and-swap0531/1)

---

## 👨‍💻 Author

**Nilesh** 🔗 [GitHub - imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Greedy` `#Algorithms` `#String` `#GeeksforGeeks` `#C++`
