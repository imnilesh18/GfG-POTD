# 🔠 Palindrome with Minimum Sum

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/palindrome-with-minimum-sum--170648/1) [![Difficulty](https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge)](#) [![Accuracy](https://img.shields.io/badge/Accuracy-60.42%25-brightgreen?style=for-the-badge)](#) [![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#) [![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](#)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. 
Solutions are provided for learning, practice, and reference only. 
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a string `s` consisting of lowercase English letters and the character `'?'`, you need to:
- Replace every `'?'` with a lowercase English letter such that the resulting string is a palindrome.
- If it is possible to form a palindrome, return the **minimum possible sum** of the absolute ASCII differences between every pair of adjacent characters in the resulting string.
- If it is not possible to form a palindrome, return `-1`.

---

## 🎯 Examples

```text
Input: s = "a???c??c????"
Output: 4
```

<details>
<summary><b>📖 Example Breakdown</b></summary>
<br>

**Explanation:** 
One optimal palindrome is `"abbbccccbbba"`. 
The sum of the absolute ASCII differences between adjacent characters is:
`|a-b| + |b-b| + |b-b| + |b-c| + |c-c| + |c-c| + |c-b| + |b-b| + |b-b| + |b-a|`
`= 1 + 0 + 0 + 1 + 0 + 0 + 0 + 1 + 0 + 0 + 1 = 4`, which is the minimum possible.
</details>

```text
Input: s = "a???c??c???c"
Output: -1
Explanation: It is not possible to replace the '?' characters to make the string a palindrome because the first ('a') and last ('c') characters are different and cannot be changed.
```

---

## ⚠️ Constraints

> - `1 ≤ s.size() ≤ 10^5`

---

## 💡 Solution Approaches

### Optimized Greedy Approach

**Intuition:**
To minimize the sum of ASCII differences in a palindrome, we should replace any `'?'` with the nearest known character. Doing this adds a cost of `0` between the `'?'` and the adjacent character. Therefore, the only unavoidable costs come from the differences between the *existing* known characters. We can simply calculate the cost for the first half of the palindrome and multiply it by 2.

```cpp
// Intuition: To minimize the sum of ASCII differences in a palindrome, replace '?' with the nearest known character, adding 0 cost. The only unavoidable costs come from differences between existing adjacent known characters in the formed palindrome.
// Approach: 
// 1. Mirror known characters to satisfy the palindrome property. If a mismatch is found between knowns, return -1.
// 2. Iterate through the first half of the string and calculate the sum of absolute differences between adjacent known characters.
// 3. Since the string is a palindrome, multiply the first half's sum by 2 to get the total minimum sum.
// Time Complexity: O(n) where n is the length of the string, as we traverse the string halves linearly.
// Space Complexity: O(1) because we are modifying the string in-place and using constant extra variables.

class Solution {
public:
    int minimumSum(string &s) {
        int n = s.size();
        
        // Step 1: Force palindrome constraints by mirroring known characters
        for (int i = 0; i < n / 2; ++i) {
            int j = n - 1 - i;
            // Both ends are known characters
            if (s[i] != '?' && s[j] != '?') {
                if (s[i] != s[j]) {
                    return -1; // Impossible to form a palindrome
                }
            } 
            // Copy known character to the '?' side
            else if (s[i] != '?') {
                s[j] = s[i];
            } else if (s[j] != '?') {
                s[i] = s[j];
            }
        }
        
        // Step 2: Compute the sum of adjacent differences in the first half
        // Length of the first half (including the middle character if odd)
        int m = (n + 1) / 2; 
        int total_sum = 0;
        char prev = 0; // Tracks the last seen known character
        
        for (int i = 0; i < m; ++i) {
            // Ignore '?' as they can be matched with 'prev' for 0 cost
            if (s[i] != '?') {
                if (prev != 0) {
                    total_sum += abs(s[i] - prev);
                }
                prev = s[i]; // Update the last seen known character
            }
        }
        
        // Step 3: Mirror the cost for the second half
        return total_sum * 2;
    }
};

/*
*
* Dry Run
* Input: s = "a???c??c????"
* 
* Step 1 (Mirroring):
* i = 0: s[0]='a', s[11]='?' -> s[11] becomes 'a'
* i = 1, 2, 3: both are '?' -> remain unchanged
* i = 4: s[4]='c', s[7]='c' -> match, unchanged
* i = 5: both are '?' -> remain unchanged
* String is now: "a???c??c???a"
* 
* Step 2 (First Half Cost):
* m = 6 (First half is "a???c?")
* i = 0: s[0] = 'a', prev = 'a'
* i = 1, 2, 3: s[i] = '?', skip
* i = 4: s[4] = 'c', total_sum += abs('c' - 'a') = 2, prev = 'c'
* i = 5: s[5] = '?', skip
* First half sum = 2
* 
* Step 3 (Total Cost):
* Return 2 * 2 = 4
*
*/
```

---

## 🔑 Key Insights

- **Greedy Choice Property:** We don't need to actually determine what letters the `'?'`s will become. By pretending they simply "merge" with the nearest known character, we realize they add exactly 0 to the overall absolute difference sum.
- **Symmetry:** Because the string is guaranteed to be a palindrome after Step 1, the right half is a perfect mirror of the left half. We only need to compute the cost of the first half and multiply by 2, neatly handling both even and odd length strings.

---

## 🚀 Further Exploration

- Try modifying the problem to find the minimum sum if the string doesn't *have* to be a palindrome.
- Practice related GeeksforGeeks string manipulation problems involving greedy character replacement.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Palindrome with minimum sum](https://www.geeksforgeeks.org/problems/palindrome-with-minimum-sum--170648/1)

---

## 👨‍💻 Author

* **Nilesh Kumar** - [imnilesh18](https://github.com/imnilesh18)

## 🏷️ Tags

`dynamic-programming` `strings` `two-pointers` `greedy` `geeksforgeeks`