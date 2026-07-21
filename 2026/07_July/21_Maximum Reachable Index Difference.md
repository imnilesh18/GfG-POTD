# 🔠 Maximum Reachable Index Difference

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks Logo" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-48.14%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a string `s` containing lowercase English alphabets.

Start from any index containing the character `'a'` and perform jump operations. In each jump operation, move to any index on the right side whose character is the immediate next letter of the current character in the alphabet (i.e., `'a'` to `'b'`, `'b'` to `'c'`, `'c'` to `'d'`, and so on). 

Continue performing jumps until no further jump is possible. Find the **maximum possible difference** between the starting index and the ending index. If it is not possible to choose a starting index, return `-1`.

---

## 💡 Examples

**Example 1:**
```text
Input: s = "aaabcb"
Output: 5
Explanation: Start at index 0 ('a'), jump to index 5 ('b'). Difference = 5 - 0 = 5.
```

**Example 2:**
```text
Input: s = "xynjir"
Output: -1
Explanation: The string does not contain any character 'a'. So, the answer is -1.
```

**Example 3:**
```text
Input: s = "abcbzzd"
Output: 6
Explanation: Start from index 0 ('a'). Jump to index 1 ('b') because 'b' is the next alphabet character. Jump to index 2 ('c') because 'c' is the next character after 'b'. Jump to index 6 ('d') because 'd' is the next character after 'c'.
```

<details>
<summary>📖 <b>Example Breakdown (Example 3)</b></summary>

Let's break down `s = "abcbzzd"`:
*   **Index 0 (`a`)**: Start here. Valid starting point.
*   **Index 1 (`b`)**: Valid jump from index 0. Current difference: `1 - 0 = 1`.
*   **Index 2 (`c`)**: Valid jump from index 1. Current difference: `2 - 0 = 2`.
*   **Index 3 (`b`)**: We can also jump to this `b` from the `a` at index 0. Difference: `3 - 0 = 3`.
*   **Index 4 (`z`)**: Invalid. Cannot jump to `z` from anything we currently have.
*   **Index 5 (`z`)**: Invalid.
*   **Index 6 (`d`)**: Valid jump from the `c` at index 2 (which originally started from index 0). Current difference: `6 - 0 = 6`.

Maximum difference achieved is **6**.
</details>

---

## 🚫 Constraints

*   `1 <= s.size() <= 10^5`
*   `s` contains lowercase English alphabets.

---

## 🛠️ Solution Approaches

### Optimized Approach (Linear Scan with Reachability State)

```cpp
// Intuition: We need maximum (end_index - start_index) for a valid chain
// a -> b -> c -> ... while always moving right. For each character, we track:
// 1) earliest start index of 'a' that can reach this character
// 2) the latest position where this character is reachable in a valid chain
//
// Approach:
// 1. min_start[ch]: earliest 'a' start index for chains ending at letter ch.
// 2. last_pos[ch]: latest index where letter ch is reachable in a valid chain.
// 3. Scan string left to right:
//    - If char is 'a': it can always start a chain (difference 0).
//    - Else char is x: it is reachable only if previous letter (x-1) was reached
//      at some index < current index.
//    - If reachable, inherit earliest start from (x-1), update answer.
//
// Time Complexity: O(n), single pass.
// Space Complexity: O(1), fixed arrays of size 26.

class Solution {
  public:
    int maxIndexDifference(string &s) {
        vector<int> min_start(26, INT_MAX); // earliest 'a' start for each letter
        vector<int> last_pos(26, -1);       // latest reachable position for each letter
        int max_diff = -1;                  // if no 'a', stays -1
        
        for (int i = 0; i < (int)s.length(); i++) {
            int char_idx = s[i] - 'a';
            
            if (char_idx == 0) {
                // 'a' can start a chain
                min_start[0] = min(min_start[0], i);
                last_pos[0] = max(last_pos[0], i);
                max_diff = max(max_diff, 0); // start and end at same index
            } else {
                // Reach current char only if predecessor is reachable before i
                if (last_pos[char_idx - 1] != -1 && last_pos[char_idx - 1] < i) {
                    min_start[char_idx] = min(min_start[char_idx], min_start[char_idx - 1]);
                    last_pos[char_idx] = max(last_pos[char_idx], i);
                    max_diff = max(max_diff, i - min_start[char_idx]);
                }
            }
        }
        
        return max_diff;
    }
};

/*
*
* Dry Run
* Input: s = "dhoxjfrqfaa"
*
* Setup:
* min_start = [INT_MAX, INT_MAX, ..., INT_MAX]
* last_pos  = [-1, -1, ..., -1]
* max_diff = -1
*
* i = 0..8: characters are not 'a' and no valid predecessor chains to extend.
*
* i = 9, s[9] = 'a'
* min_start[0] = min(INT_MAX, 9) = 9
* last_pos[0]  = max(-1, 9) = 9
* max_diff = max(-1, 0) = 0
*
* i = 10, s[10] = 'a'
* min_start[0] = min(9, 10) = 9
* last_pos[0]  = max(9, 10) = 10
* max_diff = max(0, 0) = 0
*
* No 'b' exists to the right of any 'a', so no further jump.
* Final Output: 0
*
*/
```

---

## 🧠 Key Insights

* **Dependency on the Predecessor:** To reach character `x` at index `j`, we MUST have reached character `x-1` at some index `i < j`.
* **State Inheritance:** To maximize the index difference `end - start`, we don't just need *any* valid path; we need the path that originated from the *earliest possible* `'a'`. 
* **State Array Size:** Since we only have 26 lowercase letters, storing the earliest start point for each letter requires just `O(1)` space, making this tracking extremely efficient.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might also like practicing these related string and dynamic programming challenges on GeeksforGeeks:
* Longest Substring Without Repeating Characters
* Minimum Jumps to Reach the End
* Longest Increasing Subsequence

---

## 🔗 References

* **GeeksforGeeks Problem:** [Maximum Reachable Index Difference](https://www.geeksforgeeks.org/problems/maximum-reachable-index-difference/1)

---

## ✍️ Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

![Strings](https://img.shields.io/badge/Topic-Strings-blue?style=flat-square) ![Dynamic Programming](https://img.shields.io/badge/Topic-Dynamic%20Programming-lightgrey?style=flat-square) ![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-green?style=flat-square)