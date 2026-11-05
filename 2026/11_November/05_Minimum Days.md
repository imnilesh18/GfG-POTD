<div align="center">

# 🗓️ Minimum Days

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy: 54.28%](https://img.shields.io/badge/Accuracy-54.28%25-blue?style=for-the-badge)
![Points: 4](https://img.shields.io/badge/Points-4-success?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

</div>

---

## 📝 Problem Statement

Given a string `s` of length `n` containing only lowercase English letters, and a permutation array `p[]` of length `n` containing integers from `0` to `n - 1`.

On the `(i + 1)`th day, the character at index `p[i]` in the string is replaced with `'?'`. For example:
- On day 1, replace `s[p[0]]` with `'?'`.
- On day 2, replace `s[p[1]]` with `'?'`.
- On day 3, replace `s[p[2]]` with `'?'`.
- And so on.

Find the **minimum number of days required** so that no two adjacent characters in `s` are equal, unless at least one of them is `'?'`.

Formally, for every index `i` (0 <= i < n - 1), the string must satisfy: If `s[i] != '?'` and `s[i+1] != '?'`, then `s[i] != s[i+1]`.

---

## 💡 Examples

```text
Input: s = "aabb", p = [2, 1, 3, 0]
Output: 2

```

* **Initial String:** `"aabb"` (pairs at index 0-1 and 2-3)
* **Day 1:** We replace `s[p[0]]` (index 2) with `'?'`. The string becomes `"aa?b"`. Index 0 and 1 still have equal adjacent characters `'a'`.
* **Day 2:** We replace `s[p[1]]` (index 1) with `'?'`. The string becomes `"a??b"`. Now no two adjacent non-'?' characters are equal.
* **Result:** It took 2 days.

```text
Input: s = "abca", p = [3, 0, 2, 1]
Output: 0
Explanation: The initial string "abca" already satisfies the condition without replacing any characters.

```

---

## ⚠️ Constraints

> * `1 ≤ s.size() ≤ 10^5`
> * `0 ≤ p[i] < s.size()`
> * `s` consists only of lowercase English alphabets
> * `p.size() == s.size()`
> 
> 

---

## 🚀 Solution Approaches

### Optimized Approach (Counting Violations)

Instead of checking the entire string every single day (which would be $O(N^2)$ time), we can pre-calculate the total number of adjacent duplicate pairs. When we replace a character with `'?'`, we only need to check its immediate left and right neighbors. If it breaks a previously matching pair, we decrement our violation counter. The moment the counter hits zero, we return the current day.

```cpp
// Intuition: We need to eliminate all adjacent identical characters in a string by replacing them with '?' one by one based on a given permutation. Instead of checking the whole string every time, we can count the total number of adjacent identical pairs initially and dynamically update this count as we replace characters.
// Approach: 
// 1. Traverse the string and count all pairs where s[i] == s[i+1].
// 2. If the initial count is 0, return 0 as no replacements are needed.
// 3. Iterate through the permutation array `p` to replace characters day by day.
// 4. For each replacement at index `idx`, check if it breaks a matching pair with its left (s[idx] == s[idx-1]) or right (s[idx] == s[idx+1]) neighbor. If so, decrement the pair count.
// 5. Change s[idx] to '?' and check if the pair count has reached 0. If it has, return the current day (i + 1).
// Time Complexity: O(n) where n is the length of the string, as we do a single initial pass and then process each replacement in constant O(1) time.
// Space Complexity: O(1) auxiliary space, since we modify the string in place and only use a few integer variables for counting.

class Solution {
  public:
    int getMinimumDays(string &s, vector<int> &p) {
        int n = s.length();
        int pairs = 0;
        
        // Count initial pairs of adjacent identical characters
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1]) {
                pairs++; // Found an adjacent identical pair
            }
        }
        
        // If there are no such pairs initially, return 0 days
        if (pairs == 0) return 0;
        
        // Simulate replacing characters with '?' day by day
        for (int i = 0; i < n; i++) {
            int idx = p[i]; // Get the index to replace on the current day
            
            // Check if replacing s[idx] breaks an identical pair on the left
            if (idx > 0 && s[idx] == s[idx - 1]) {
                pairs--; // Decrement pair count as the left bond is broken
            }
            // Check if replacing s[idx] breaks an identical pair on the right
            if (idx < n - 1 && s[idx] == s[idx + 1]) {
                pairs--; // Decrement pair count as the right bond is broken
            }
            
            // Replace the character
            s[idx] = '?'; // Mark the character as replaced
            
            // If all identical adjacent pairs are broken, return current day
            if (pairs == 0) {
                return i + 1; // 1-based day index
            }
        }
        
        return 0; // Fallback return (should not be reached if inputs are valid)
    }
};

/*
* Dry Run
* Input: s = "aabb", p = [2, 1, 3, 0]
* Initial String: "aabb", n = 4
* Initial Pairs: s[0]==s[1] ('a'=='a') -> pairs = 1. s[2]==s[3] ('b'=='b') -> pairs = 2. Total pairs = 2.
* 
* Day 1 (i = 0):
* idx = p[0] = 2 (character 'b')
* Check left: idx > 0, s[2] == s[1] ('b' == 'a') -> False
* Check right: idx < 3, s[2] == s[3] ('b' == 'b') -> True! pairs becomes 1.
* Replace: s[2] = '?', string is now "aa?b"
* pairs == 1 (Not 0 yet)
* 
* Day 2 (i = 1):
* idx = p[1] = 1 (character 'a')
* Check left: idx > 0, s[1] == s[0] ('a' == 'a') -> True! pairs becomes 0.
* Check right: idx < 3, s[1] == s[2] ('a' == '?') -> False
* Replace: s[1] = '?', string is now "a??b"
* pairs == 0 -> Return current day (i + 1) = 2.
* 
* Output: 2
*/

```

---

## 🔑 Key Insights

* **Dynamic State Tracking:** Instead of re-evaluating the entire string's validity after every single change, we simply maintain a "bad pairs" counter. A local change at index `i` only ever affects the validity of pairs `(i-1, i)` and `(i, i+1)`.
* **In-Place Modification:** The string `s` is passed by reference `&s`, allowing us to manipulate the characters directly without incurring additional space complexities.

---

## 🔍 Further Exploration

* Look into other string manipulation challenges involving permutations.
* Explore problems tagged under `Sliding Window` or `State Tracking` where global states are updated via local changes to maintain an $O(N)$ time complexity.

---

## 🔗 References

* **GeeksforGeeks Problem Link:** [Minimum Days](https://www.geeksforgeeks.org/problems/minimum-days--170646/1)

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

* `strings`
* `permutation`
* `geeksforgeeks`
* `c++`