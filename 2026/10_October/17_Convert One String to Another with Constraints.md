# 🟩 Convert One String to Another with Constraints

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white) ![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge) ![Accuracy](https://img.shields.io/badge/Accuracy-49.91%25-blue?style=for-the-badge) ![Points](https://img.shields.io/badge/Points-2-blue?style=for-the-badge) ![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two strings `s1` and `s2`, consisting only of the characters `'A'`, `'B'`, and `'#'`. Determine whether `s1` can be transformed into `s2` by performing the following operations on `s1`:

*   `'A'` can move only towards the **left**.
*   `'B'` can move only towards the **right**.
*   Neither `'A'` nor `'B'` can cross each other.
*   `'#'` represents an empty position through which `'A'` and `'B'` can move.

Moving the character at index `i` one step to the left means swapping it with the character at index `i - 1`, provided `i - 1 >= 0`. Similarly, moving it one step to the right means swapping it with the character at index `i + 1`, provided `i + 1 < s1.length()`.

Return `true` if `s1` can be transformed into `s2`; otherwise, return `false`.

---

## 💡 Examples

**Example 1:**
```text
Input: s1 = #A#B#B#, s2 = A###B#B
Output: true
Explanation: The character 'A' in s1 can move one position towards the left to reach its position in s2, as there are no 'B' characters blocking its movement. Similarly, each 'B' can move towards the right to reach its corresponding position in s2 without crossing any other 'A' or 'B'. Therefore, s1 can be transformed into s2, so the answer is true.
```

**Example 2:**
```text
Input: s1 = #A#B#, s2 = #B#A#
Output: false
Explanation: The character 'A' in s1 is at index 1, whereas the corresponding 'A' in s2 is at index 3. Since 'A' can move only towards the left, it cannot reach a position to the right of its current position. Therefore, s1 cannot be transformed into s2, and hence, the answer is false.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>
<br>
Let's analyze <b>Example 1</b>: <code>s1 = "#A#B#B#"</code>, <code>s2 = "A###B#B"</code>

1. Look for the first non-`#` character in both strings.
2. In `s1`, it's `'A'` at index `1`. In `s2`, it's `'A'` at index `0`. 
3. Because `'A'` moves left, it can legally travel from index `1` to `0`.
4. Look for the next non-`#` character. In `s1`, it's `'B'` at index `3`. In `s2`, it's `'B'` at index `4`.
5. Because `'B'` moves right, it can legally travel from index `3` to `4`.
6. Look for the final non-`#` character. In `s1`, it's `'B'` at index `5`. In `s2`, it's `'B'` at index `6`.
7. `'B'` can legally move right from `5` to `6`.
8. Since all characters match in relative order and obey their movement directions, the transformation is valid.
</details>

---

## ⚠️ Constraints

> - `1 ≤ s1.size(), s2.size() ≤ 10^5`
> - Both strings consist only of characters `'A'`, `'B'`, and `'#'`.

---

## 💻 Solution Approaches

### Optimized Two-Pointer Approach

**Brief Summary / Intuition:**
Because `'A'` and `'B'` cannot cross each other, the relative sequence of `'A'`s and `'B'`s must be exactly the same in both strings after ignoring all `'#'`s. If they match, we must then verify if they can actually reach their target indices: an `'A'` in `s1` must have an index $\geq$ its target index in `s2` (so it can move left), and a `'B'` in `s1` must have an index $\leq$ its target index in `s2` (so it can move right).

```cpp
// Intuition: The relative sequence of 'A' and 'B' must remain identical because they cannot cross each other. Also, 'A' can only travel left (current index >= target index) and 'B' can only travel right (current index <= target index).
// Approach:
// 1. Use two pointers, i for s1 and j for s2, traversing both strings simultaneously.
// 2. Ignore all '#' characters to find the next active character ('A' or 'B').
// 3. If both strings are exhausted simultaneously, return true. If one is exhausted before the other, return false (mismatched character counts).
// 4. Ensure the non-'#' characters match. If s1[i] != s2[j], they are out of order, return false.
// 5. Check directional constraints: return false if 'A' needs to move right (i < j) or 'B' needs to move left (i > j).
// 6. Increment pointers and repeat.
// Time Complexity: O(n + m), where n and m are lengths of s1 and s2. Each index is visited at most once.
// Space Complexity: O(1), no extra auxiliary space is used.

class Solution {
  public:
    bool isItPossible(string &s1, string &s2) {
        int n = s1.length();
        int m = s2.length();
        
        // If lengths differ, transformation is impossible
        if (n != m) return false;

        int i = 0, j = 0;
        
        while (i < n || j < m) {
            // Skip all '#' in s1 to find next character
            while (i < n && s1[i] == '#') i++;
            // Skip all '#' in s2 to find next character
            while (j < m && s2[j] == '#') j++;
            
            // If both strings are completely exhausted, valid transformation
            if (i == n && j == m) return true;
            // If only one string is exhausted, mismatched count of 'A' or 'B'
            if (i == n || j == m) return false;
            
            // The characters must match exactly to maintain relative order
            if (s1[i] != s2[j]) return false;
            
            // 'A' can only move left, so it must start at an index >= its target
            if (s1[i] == 'A' && i < j) return false;
            
            // 'B' can only move right, so it must start at an index <= its target
            if (s1[i] == 'B' && i > j) return false;
            
            // Move to the next elements
            i++;
            j++;
        }
        
        return true;
    }
};

/*
*
* Dry Run
*
* Input: s1 = "#A#B#B#", s2 = "A###B#B"
*
* Initialization: i = 0, j = 0, n = 7, m = 7
*
* Iteration 1:
* - Skip '#' in s1: i becomes 1 (s1[1] == 'A')
* - Skip '#' in s2: j remains 0 (s2[0] == 'A')
* - s1[i] == s2[j] ('A' == 'A')
* - Check 'A' movement: i(1) >= j(0) -> valid
* - i++, j++ (i=2, j=1)
*
* Iteration 2:
* - Skip '#' in s1: i becomes 3 (s1[3] == 'B')
* - Skip '#' in s2: j becomes 4 (s2[4] == 'B')
* - s1[i] == s2[j] ('B' == 'B')
* - Check 'B' movement: i(3) <= j(4) -> valid
* - i++, j++ (i=4, j=5)
*
* Iteration 3:
* - Skip '#' in s1: i becomes 5 (s1[5] == 'B')
* - Skip '#' in s2: j becomes 6 (s2[6] == 'B')
* - s1[i] == s2[j] ('B' == 'B')
* - Check 'B' movement: i(5) <= j(6) -> valid
* - i++, j++ (i=6, j=7)
*
* Iteration 4:
* - Skip '#' in s1: i becomes 7
* - Skip '#' in s2: j remains 7
* - Both i == n and j == m (7 == 7). Strings exhausted successfully.
* - Return true.
*
* Output: true
*/
```

---

## 🔍 Key Insights

* **Two-Pointer Technique:** Bypassing irrelevant characters (like the `#` spaces) allows us to compare the relative sequence of the meaningful data.
* **Invariant Properties:** The problem revolves around two strict invariants: 
  1. The sequence of non-empty characters must be identical.
  2. The position deltas must match the directional rules (`'A'` only decreases its index, `'B'` only increases it). Checking these two conditions is sufficient to prove if the transformation is possible.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might want to try these related concepts on GeeksforGeeks:
- **Two Pointer Algorithms** (Finding pairs, reversing strings with constraints)
- **Greedy Algorithms** (Making optimal local moves)
- **String Manipulation Problems**

---

## 🔗 References

* **GeeksforGeeks Problem:** [Convert One String to Another with Constraints](https://www.geeksforgeeks.org/problems/check-if-it-is-possible-to-convert-one-string-into-another-with-given-constraints4116/1)

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Strings` `constructive algo` `Greedy` `two-pointer-algorithm` `GeeksforGeeks`