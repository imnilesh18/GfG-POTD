<div align="center">
  
# 🔠 Longest Repeating Character Replacement

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/longest-repeating-character-replacement/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-50.04%25-green?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

<br>

⚠️ **Educational Use Only**
<br>
This repository and its content are intended solely for educational purposes.
<br>
Solutions are provided for learning, practice, and reference only.
<br>
Problem statement and test cases are based on the GeeksforGeeks problem.

</div>

---

## 📝 Problem Statement

Given a string `s` of length `n` consisting of uppercase English letters and an integer `k`, you are allowed to perform **at most** `k` operations. In each operation, you can change any character of the string to any other uppercase English letter.

Determine the length of the **longest substring** that can be transformed into a string with all identical characters after performing at most `k` such operations.

---

## 💡 Examples

### Example 1
```text
Input: s = "ABBA", k = 2 
Output: 4 
Explanation: The string "ABBA" can be fully converted into the same character using at most 2 changes. By replacing both 'A' with 'B', it becomes "BBBB". Hence, the maximum length is 4.
```

### Example 2
```text
Input: s = "ADBD", k = 1
Output: 3
Explanation: In the string "ADBD", we can make at most 1 change. By changing 'B' to 'D', the string becomes "ADDD", which contains a substring "DDD" of length 3.
```

<details>
<summary>📖 <b>Example Breakdown (s = "ADBD", k = 1)</b></summary>

1. **Initial State:** Start at index `0`. Window is `[A]`. Replacements needed = `1 - 1 = 0 <= 1`. Max Length = `1`.
2. **Expand:** Include `D` at index `1`. Window is `[A, D]`. Most frequent is `1`. Replacements needed = `2 - 1 = 1 <= 1`. Max Length = `2`.
3. **Expand:** Include `B` at index `2`. Window is `[A, D, B]`. Most frequent is `1`. Replacements needed = `3 - 1 = 2 > 1`. 
   - **Shrink:** Remove `A` from the left. Window becomes `[D, B]`.
4. **Expand:** Include `D` at index `3`. Window is `[D, B, D]`. Most frequent is `D` (2 times). Replacements needed = `3 - 2 = 1 <= 1`. Max Length = `3`.
5. **Result:** The maximum length found is `3`.

</details>

---

## ⚠️ Constraints

> - `1 ≤ n, k ≤ 10^5`
> - `s` consists of only uppercase English letters.
> - **Expected Time Complexity:** `O(n)`
> - **Expected Auxiliary Space:** `O(1)`

---

## 🚀 Solution

### 🔹 Sliding Window (Optimized Approach)

**Intuition:** The problem requires finding the longest valid substring where the number of character replacements needed is at most `k`. A window is valid if its total size minus the count of its most frequent character is `<= k`.

**Algorithm:**
1. Use two pointers (`i` and `j`) to represent a sliding window. 
2. Track character frequencies using an array of size 26. 
3. If the current window requires more than `k` changes (`(window size) - maxFreq > k`), shrink the window from the left by advancing `i`. 
4. Otherwise, update the maximum length and expand the window to the right by advancing `j`.

```cpp
// Intuition: The problem requires finding the longest valid substring where the number of character replacements needed is at most k. A window is valid if its total size minus the count of its most frequent character is <= k.
// Approach: Use two pointers (i and j) to represent a sliding window. Track character frequencies. If the current window requires more than k changes ((window size) - maxFreq > k), shrink from the left. Otherwise, update the max length and expand the window to the right.
// Time Complexity: O(N) where N is the length of the string, as both pointers i and j traverse the string at most once.
// Space Complexity: O(1) since we use a fixed-size array of 26 integers to store character frequencies.

class Solution {
  public:
    int longestSubstr(string& s, int k) {
        int n = s.length();
        vector<int> count(26, 0); // character frequency map
        int i = 0, j = 0;
        int maxFreq = 0, ans = 0;
        
        while (j < n) {
            // include current character
            count[s[j] - 'A']++;
            maxFreq = max(maxFreq, count[s[j] - 'A']);
            
            // shrink the window if invalid
            while ((j - i + 1) - maxFreq > k) {
                count[s[i] - 'A']--;
                i++;
            }
            
            // update maximum length result
            ans = max(ans, j - i + 1);
            
            // expand the window
            j++;
        }
        
        return ans;
    }
};

/*
*
* Dry Run
*
* Input: s = "ADBD", k = 1
* Variables: n = 4, count = [0]*26, i = 0, j = 0, maxFreq = 0, ans = 0
* * j = 0, s[j] = 'A'
* count['A'] = 1, maxFreq = 1
* window size = 1, changes = 1 - 1 = 0 (<= k)
* shrink condition false
* ans = max(0, 1) = 1
* expand j to 1
* * j = 1, s[j] = 'D'
* count['D'] = 1, maxFreq = 1
* window size = 2, changes = 2 - 1 = 1 (<= k)
* shrink condition false
* ans = max(1, 2) = 2
* expand j to 2
* * j = 2, s[j] = 'B'
* count['B'] = 1, maxFreq = 1
* window size = 3, changes = 3 - 1 = 2 (> k)
* shrink: count['A'] becomes 0, i becomes 1
* ans = max(2, 2) = 2
* expand j to 3
* * j = 3, s[j] = 'D'
* count['D'] = 2, maxFreq = max(1, 2) = 2
* window size = 3 (since i=1, j=3), changes = 3 - 2 = 1 (<= k)
* shrink condition false
* ans = max(2, 3) = 3
* expand j to 4
* * Loop ends (j = 4 is not < n)
* Return ans = 3
*/
```

---

## 🧠 Key Insights

- **Sliding Window Dynamics:** Instead of checking every possible substring, the sliding window dynamically adjusts itself to maintain the longest valid sequence.
- **Max Frequency Trick:** We don't strictly need to recalculate `maxFreq` when shrinking the window. Since we are only interested in finding a *longer* valid substring, a previous historical `maxFreq` will keep the window size constraint active until we encounter an even higher frequency.

---

## 🔍 Further Exploration

If you enjoyed this problem, you might also want to try:
- **Max Consecutive Ones III** (Similar sliding window concept)
- **Longest Substring Without Repeating Characters**
- **Sliding Window Maximum**

---

## 🔗 References

- **GeeksforGeeks Problem:** [Longest Repeating Character Replacement](https://www.geeksforgeeks.org/problems/longest-repeating-character-replacement/1)

---

## 👨‍💻 Author

Created and maintained by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags

`two-pointer-algorithm` `Strings` `Data Structures` `Algorithms` `Sliding Window` `GeeksforGeeks` 