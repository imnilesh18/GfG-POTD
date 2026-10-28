# 🟧 Nth Character in Concatenated Decimal String

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white) 
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-71.83%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. 
Solutions are provided for learning, practice, and reference only. 
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Consider a string `s` formed by concatenating the decimal representations of all positive integers in order:[cite: 1]
`s = "12345678910111213141516171819202122232425262728293031..."`[cite: 1]

Given an integer `n`, find the `n`th character (1-based indexing) in the string `s`.[cite: 1]

## 💡 Examples

```text
Input: n = 10
Output: '1'
Explanation: The 10th character in "1234567891011..." is '1'.
```
[cite: 1]

```text
Input: n = 11
Output: '0'
Explanation: The 11th character in "1234567891011..." is '0'.
```
[cite: 1]

<details>
<summary>📖 <b>Example Breakdown (n = 11)</b></summary>

1. **Count 1-digit numbers:** There are 9 single-digit numbers (1-9), which take up the first 9 characters of the string.
2. **Remaining characters:** To find the 11th character, we subtract 9, leaving us looking for the 2nd character in the 2-digit number sequence.
3. **Identify the number:** The 2-digit numbers start at 10. The 1st and 2nd characters of this sequence belong to the number `10`.
4. **Extract the digit:** The 2nd character in the 2-digit sequence is the second digit of `10`, which is `'0'`.

</details>

## ⚙️ Constraints

```text
1 ≤ n ≤ 10^9
```
[cite: 1]

---

## 🛠️ Solution Approach

### Optimized Mathematical Approach
Instead of building the massive string (which would cause a Memory Limit Exceeded error for $N = 10^9$), we mathematically jump through digit length groups (1-digit numbers, 2-digit numbers, etc.) to calculate exactly which number contains our target character, and then extract that specific character.

```cpp
// Intuition: Generating the full concatenated string up to N characters is impossible due to memory limits (N up to 10^9). Instead, we can mathematically determine which number contains the Nth digit by counting how many digits are contributed by 1-digit numbers, 2-digit numbers, etc.
// Approach: 
// 1. Loop through digit lengths (1, 2, 3...) and subtract the total number of digits they contribute from N until N is less than the digits contributed by the current length.
// 2. Calculate the exact number that contains our target digit using the remaining N.
// 3. Convert this exact number to a string and return the specific character at the correct index.
// Time Complexity: O(log10 n) - We skip through digit lengths which grow logarithmically relative to n.
// Space Complexity: O(1) - We only store a few variables and convert a single integer to a string (max 10 characters), taking constant space.
class Solution {
  public:
    char nthCharacter(int n) {
        long long len = 1;      // Current length of numbers being processed
        long long count = 9;    // Number of integers in the current length (9, 90, 900...)
        long long start = 1;    // Starting number of the current length (1, 10, 100...)
        long long N = n;        // Copy of target index

        // Step 1: Find the number of digits in the target number
        while (N > len * count) {
            N -= len * count;   // Subtract digits contributed by current length range
            len++;              // Move to the next digit length
            count *= 10;        // Multiply count by 10 for the next range
            start *= 10;        // Update starting number
        }

        // Step 2: Find the exact number containing the Nth digit
        // (N - 1) / len gives the offset from the 'start' number
        long long target_num = start + (N - 1) / len;

        // Step 3: Extract the digit at index (N - 1) % len
        string s = to_string(target_num);
        return s[(N - 1) % len]; // Return the exact character
    }
};

/*
*
* Dry Run
* Input: n = 11
* Initialization: len = 1, count = 9, start = 1, N = 11
* 
* Loop iteration 1:
* N (11) > len * count (1 * 9 = 9) -> True
* N = 11 - 9 = 2
* len = 2, count = 90, start = 10
* 
* Loop iteration 2:
* N (2) > len * count (2 * 90 = 180) -> False
* 
* Find exact number:
* target_num = 10 + (2 - 1) / 2 = 10 + 1 / 2 = 10 + 0 = 10
* 
* Extract character:
* string s = "10"
* index = (2 - 1) % 2 = 1 % 2 = 1
* s[1] is '0'
* Return '0'
*
*/
```

---

## 🧠 Key Insights
* **Group Counting:** By realizing that 1-9 contribute 9 digits, 10-99 contribute $90 \times 2 = 180$ digits, and 100-999 contribute $900 \times 3 = 2700$ digits, we can drastically reduce the search space from $O(N)$ to $O(\log_{10} N)$.
* **Offset Calculation:** The formula `(N - 1) / len` accurately finds how many numbers away from the `start` boundary our target number sits, and `(N - 1) % len` finds the exact digit inside that specific number.

## 🔎 Further Exploration
* Nth Digit (Similar problem on LeetCode)
* Champernowne's constant problems
* String parsing and modular arithmetic combinations

## 🔗 References
* **GeeksforGeeks Problem:** [Nth in Concatenated Decimal String](https://www.geeksforgeeks.org/problems/nth-character-in-concatenated-decimal-string0245/1)[cite: 1]
* **Topic Tags:** Mathematics[cite: 1]

---

## 👨‍💻 Author
**[imnilesh18](https://github.com/imnilesh18)**

## 🏷️ Tags
`- mathematics` `- string` `- geeksforgeeks` `- algorithms` `- modulo-arithmetic`