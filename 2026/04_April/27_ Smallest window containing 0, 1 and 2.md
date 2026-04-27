# 🟢 Smallest window containing 0, 1 and 2

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/smallest-window-containing-0-1-and-2--170637/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty">
  <img src="https://img.shields.io/badge/Accuracy-49.73%25-blue?style=for-the-badge" alt="Accuracy">
  <img src="https://img.shields.io/badge/Points-2-blue?style=for-the-badge" alt="Points">
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge" alt="License">
  </a>
</p>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a string `s` consisting only of the characters `'0'`, `'1'` and `'2'`, determine the length of the **smallest substring** that contains all three characters at least once.

If no such substring exists, return `-1`.

---

## ⚠️ Constraints

> - `1 ≤ s.size() ≤ 10^5`
> - `s` consists of characters `'0'`, `'1'`, and `'2'` only.

---

## 💡 Examples

### Example 1:
```text
Input: s = "10212"
Output: 3
Explanation: The substring "102" is the shortest substring that contains all three characters '0', '1', and '2', so the answer is 3.
```

### Example 2:
```text
Input: s = "12121"
Output: -1
Explanation: The character '0' is not present in the string, so no substring can contain all three characters '0', '1', and '2'. Hence, the answer is -1.
```

<details>
<summary>📖 Example Breakdown</summary>

**Detailed Walkthrough for Example 1 (`s = "10212"`):**
- Start expanding the window from left to right.
- `j=0` -> char `'1'`, window: `"1"` (Not valid)
- `j=1` -> char `'0'`, window: `"10"` (Not valid)
- `j=2` -> char `'2'`, window: `"102"` (Valid! All three characters present. Length = 3)
- Move `i` to shrink: `i=1`, window: `"02"` (Not valid)
- `j=3` -> char `'1'`, window: `"021"` (Valid! All three characters present. Length = 3)
- Move `i` to shrink: `i=2`, window: `"21"` (Not valid)
- `j=4` -> char `'2'`, window: `"212"` (Not valid)
- The minimum length recorded during the process is **3**.

</details>

---

## 🚀 Solution Approach

### Sliding Window (Two Pointers)

**Intuition:** A sliding window is ideal for finding the smallest contiguous substring satisfying a specific condition. By dynamically expanding and shrinking the window, we can maintain the character counts efficiently without redundant iterations.

**Approach:** 1. Initialize two pointers `i` and `j` at the start of the string.
2. Expand the window by moving `j` and updating the frequency of the current character in an array.
3. Whenever the window contains at least one of `'0'`, `'1'`, and `'2'`, update the minimum length.
4. Start shrinking the window from the left by moving `i` and reducing the frequency of the outgoing character until the condition (having all three characters) fails.
5. Repeat until the end of the string.

### 💻 C++ Code

```cpp
// Intuition: A sliding window is ideal for finding the smallest contiguous substring satisfying a condition. We use two pointers to dynamically adjust the window size while tracking the presence of '0', '1', and '2'.
// Approach: Initialize two pointers i and j. Expand the window by moving j and updating the character frequencies. Whenever the window contains at least one of '0', '1', and '2', update the minimum length and start shrinking the window from the left by moving i until the condition fails.
// Time Complexity: O(n) as both pointers i and j traverse the string linearly from left to right at most once.
// Space Complexity: O(1) since we only use a small fixed-size array of 3 elements to store character frequencies.

class Solution {
  public:
    int smallestSubstring(string s) {
        // Applying standard sliding window pattern
        int n = s.length();
        int i = 0;
        int j = 0;
        int minLen = 1e9; 
        
        // frequency array for characters '0', '1', and '2'
        int counts[3] = {0}; 

        while (j < n) {
            // expand the window by adding the current character
            counts[s[j] - '0']++;

            // shrink while the window has all three characters
            while (counts[0] > 0 && counts[1] > 0 && counts[2] > 0) {
                
                // calculate result for the current valid window
                if (j - i + 1 < minLen) {
                    minLen = j - i + 1;
                }

                // remove the left character to shrink the window
                counts[s[i] - '0']--;
                i++;
            }
            
            // move to the next character
            j++;
        }

        // return -1 if no valid window was found
        return minLen == 1e9 ? -1 : minLen;
    }
};

/*
*
* Dry Run
*
* Input s = "10212"
* * Initialize i = 0, j = 0, minLen = 1e9, counts = [0, 0, 0]
* * j = 0, s[j] = '1', counts becomes [0, 1, 0]
* Valid window condition is false
* * j = 1, s[j] = '0', counts becomes [1, 1, 0]
* Valid window condition is false
* * j = 2, s[j] = '2', counts becomes [1, 1, 1]
* Valid window condition is true
* Update minLen to 3
* Shrink window: remove s[i] which is '1', counts becomes [1, 0, 1], move i to 1
* Valid window condition is now false
* * j = 3, s[j] = '1', counts becomes [1, 1, 1]
* Valid window condition is true
* Update minLen to min(3, 3) which remains 3
* Shrink window: remove s[i] which is '0', counts becomes [0, 1, 1], move i to 2
* Valid window condition is now false
* * j = 4, s[j] = '2', counts becomes [0, 1, 2]
* Valid window condition is false
* * End of loop
* Final minLen is 3, return 3
*
*/
```

---

## 🧠 Key Insights

- **O(1) Space Constraint Avoided:** Because the character set is strictly limited to 3 characters (`'0'`, `'1'`, `'2'`), a small array of size 3 acts as our frequency map, keeping auxiliary space constant $O(1)$.
- **Dynamic Resizing:** Shrinking the window strictly checks against the minimum requirements, inherently isolating the shortest valid segment continuously. 

---

## 🔍 Further Exploration

- What if the string had $K$ distinct characters? The same approach would work by replacing the `counts[3]` array with a hash map or larger array, updating the logic to track $K$ distinct matched elements.
- Related GeeksforGeeks problems:
  - *Smallest window in a string containing all the characters of another string*
  - *Longest Substring Without Repeating Characters*

---

## 🔗 References

- **Original Problem:** [GeeksforGeeks - Smallest window containing 0, 1 and 2](https://www.geeksforgeeks.org/problems/smallest-window-containing-0-1-and-2--170637/1)
- **Concept:** Sliding Window Algorithm / Two Pointers

---

## ✍️ Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`sliding-window` `two-pointer-algorithm` `Strings` `Data Structures` `Algorithms` `Paytm`