# 🟢 Max Gap Between Two Same

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/maximum-number-of-characters-between-any-two-same-character4552/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-47.57%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

<br/>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a string `s` consisting of lowercase English letters, find the **maximum number of characters between any two identical characters**. If no character repeats, return `-1`.

### 💡 Expected Complexities
* **Time Complexity:** `O(|s|)`
* **Auxiliary Space:** `O(1)`

---

## 🎯 Examples

### Example 1
```text
Input: s = "socks"
Output: 3
Explanation: There are 3 characters ('o', 'c', 'k') between the two occurrences of 's'.
```

### Example 2
```text
Input: s = "for"
Output: -1
Explanation: No repeating character present.
```

<details>
<summary><b>📖 Example Breakdown (s = "socks")</b></summary>

1. **Initialization:**
   - `first_pos` array of size 26, all set to `-1`.
   - `max_gap = -1`.

2. **Iteration:**
   - `i = 0`, char = `'s'`: First occurrence. `first_pos['s' - 'a'] = 0`.
   - `i = 1`, char = `'o'`: First occurrence. `first_pos['o' - 'a'] = 1`.
   - `i = 2`, char = `'c'`: First occurrence. `first_pos['c' - 'a'] = 2`.
   - `i = 3`, char = `'k'`: First occurrence. `first_pos['k' - 'a'] = 3`.
   - `i = 4`, char = `'s'`: Seen before! Gap = `index - first_pos['s'] - 1` = `4 - 0 - 1 = 3`. Update `max_gap` = `max(-1, 3) = 3`.

3. **Result:**
   - Return `3`.

</details>

---

## 🛑 Constraints

> * `1 ≤ |s| ≤ 10^5`
> * `s` contains only lowercase English letters.

---

## 💻 Solution Approaches

### 🚀 Optimized Approach (First Occurrence Tracking)

We can solve this problem efficiently in a single pass. Instead of manually maintaining counts between elements, we can simply store the index of the **first occurrence** of every character in an array of size 26 (since there are only lowercase letters). When we encounter a character again, we can easily calculate the gap by subtracting its first seen index from its current index minus 1. 

```cpp
// Intuition: To find the maximum gap between identical characters, we only need to remember where we first saw each character. The gap is the difference between the current index and the first occurrence index minus one.
// Approach: Create a 26-size array initialized to -1 to store the first occurrence index of each character. Iterate through the string. If a character is seen for the first time, store its index. If seen again, calculate the gap and update the maximum gap found so far.
// Time Complexity: O(|s|) where |s| is the length of the string. We iterate through the string exactly once.
// Space Complexity: O(1) because we use a fixed-size array of 26 integers, regardless of the input string length.

class Solution {
  public:
    int maxCharGap(string &s) {
        // Array to store the first occurrence index of each character
        int first_pos[26];
        fill(first_pos, first_pos + 26, -1);
        
        // Track the maximum gap found
        int max_gap = -1;
        
        // Traverse the string
        for (int i = 0; i < s.length(); i++) {
            int char_idx = s[i] - 'a';
            
            // If character is encountered for the first time
            if (first_pos[char_idx] == -1) {
                first_pos[char_idx] = i;
            } 
            // If character has been seen before
            else {
                // Calculate gap and update max_gap
                max_gap = max(max_gap, i - first_pos[char_idx] - 1);
            }
        }
        
        return max_gap;
    }
};

/*
*
* Dry Run
*
* Input: s = "socks"
* State Setup: first_pos[26] = [-1, ... -1], max_gap = -1
* * i = 0, s[0] = 's': char_idx = 18. first_pos[18] is -1. Set first_pos[18] = 0.
* i = 1, s[1] = 'o': char_idx = 14. first_pos[14] is -1. Set first_pos[14] = 1.
* i = 2, s[2] = 'c': char_idx = 2.  first_pos[2] is -1.  Set first_pos[2] = 2.
* i = 3, s[3] = 'k': char_idx = 10. first_pos[10] is -1. Set first_pos[10] = 3.
* i = 4, s[4] = 's': char_idx = 18. first_pos[18] is 0 (!= -1). 
* Gap = i - first_pos[18] - 1 = 4 - 0 - 1 = 3.
* max_gap = max(-1, 3) = 3.
* * Loop ends. Return max_gap (3).
*
*/
```

---

## 🧠 Key Insights

* **Fixed Size Memory:** Utilizing the constraint that the string only contains lowercase letters allows us to use an `O(1)` memory array (`first_pos[26]`) instead of a more complex HashMap.
* **Greedy Gap Calculation:** We never need to update the `first_pos` of a character once it's set. The maximum gap for any character ending at index `i` will always be calculated from its *very first* occurrence.

---

## 🔍 Further Exploration

If you enjoyed this problem, you might also like these string manipulation and hashing challenges:
* [Longest Substring Without Repeating Characters](https://www.geeksforgeeks.org/problems/longest-distinct-characters-in-string5848/1)
* [First Non-Repeating Character in a Stream](https://www.geeksforgeeks.org/problems/first-non-repeating-character-in-a-stream1216/1)
* [Isomorphic Strings](https://www.geeksforgeeks.org/problems/isomorphic-strings-1587115620/1)

---

## 🔗 References

* **Original Problem:** [Max Gap Between Two Same on GeeksforGeeks](https://www.geeksforgeeks.org/problems/maximum-number-of-characters-between-any-two-same-character4552/1)
* **Company Tags:** Zoho

---

## 👤 Author

**Nilesh**
* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#String` `#Array` `#Hashing` `#GeeksforGeeks` `#Zoho`