# 🟧 Maximum Without 3 Consecutive Set Bits 

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-58.04%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a non-negative integer `n`, you can only change a set bit (1) to an unset bit (0). Find the maximum possible value of `n` such that its binary representation does not contain three consecutive set bits (111) after performing zero or more allowed operations .

---

## 🚀 Examples

**Example 1**
```text
Input: n = 2
Output: 2
Explanation: The binary representation of 2 is 10, which does not contain three consecutive set bits. Therefore, no change is required .
```

**Example 2**
```text
Input: n = 7
Output: 6
Explanation: The binary representation of 7 is 111, which contains three consecutive set bits. Changing the rightmost set bit to 0 gives: 111 -> 110. Thus, the maximum possible value is 6 .
```

<details>
<summary>📖 <b>Example Breakdown (n = 7)</b></summary>

1. The binary representation of `7` is `111`.
2. We detect three consecutive set bits at positions 2, 1, and 0.
3. To maximize the remaining value, we must unset the *least significant bit* among the three (which is at position 0).
4. Unsetting the 0th bit turns `111` into `110`.
5. The decimal value of `110` is `6`. 
</details>

---

## ⚠️ Constraints

> - `0 ≤ n ≤ 10^9` 

---

## 💡 Solution Approach

### Greedy Bit Manipulation
To maximize the value of the number while avoiding any "111" sequence, we must keep the higher-order (most significant) bits intact as much as possible. Therefore, we check bits starting from the highest possible position (bit 30 for `10^9`) down to bit 2. Whenever we encounter three consecutive set bits (`i`, `i-1`, `i-2`), we greedily unset the lowest bit among them (`i-2`). This guarantees the sequence is broken with the absolute minimum loss in numerical value.

### C++ Source Code

```cpp
// Intuition: To maximize the number while preventing three consecutive set bits, we should traverse from the most significant bit downwards. When '111' is found, unsetting the least significant bit of the three minimizes the value reduction.
// Approach: Iterate from bit 30 down to 2. Check if bits at i, i-1, and i-2 are all 1. If they are, unset the bit at i-2 using bitwise AND with the bitwise NOT of (1 << (i - 2)).
// Time Complexity: O(1) - The loop always runs a constant 29 times (from 30 to 2) .
// Space Complexity: O(1) - Only a few integer variables are used .

class Solution {
  public:
    int maxValue(int n) {
        // Iterate from the highest possible bit (30 for 10^9) down to 2 
        for (int i = 30; i >= 2; --i) {
            // Check if 3 consecutive bits (i, i-1, i-2) are all set to 1 
            if ((n & (1 << i)) && (n & (1 << (i - 1))) && (n & (1 << (i - 2)))) {
                // Unset the lowest bit among the three to maximize the number 
                n &= ~(1 << (i - 2));
            }
        }
        return n;
    }
};

/*
*
* Dry Run
* Input: n = 7 (Binary: 0...0111)
* Loop i from 30 down to 3: 
*   Condition fails (bits are 0)
* i = 2:
*   n & (1 << 2) => True (bit 2 is 1)
*   n & (1 << 1) => True (bit 1 is 1)
*   n & (1 << 0) => True (bit 0 is 1)
*   Inside if block: n &= ~(1 << 0) => n = 7 & ~1 => 7 & 6 = 6 (Binary: 0...0110)
* Loop ends.
* Return: 6
*
*/
```

---

## 🔍 Key Insights
- **Greedy Choice Property:** By scanning left-to-right (MSB to LSB), we ensure that we only sacrifice the smallest possible component of the number (`2^(i-2)`) when breaking a streak of three 1s.
- **Bitwise Operations:** Using `(n & (1 << i))` efficiently checks if a bit is set. Using `n &= ~(1 << pos)` efficiently unsets a specific bit without altering others.

---

## 🌍 Further Exploration
- Bitwise operations (AND, OR, XOR, NOT, Left/Right Shift)
- Greedy algorithms on binary representations
- Finding the Most Significant Bit (MSB) of an integer

---

## 🔗 References
- **GeeksforGeeks Problem:** [Maximum Without 3 Consecutive Set Bits](https://www.geeksforgeeks.org/problems/geek-hates-too-many-1s--170647/1) 

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`[bit-magic]` `[greedy]` `[cpp]` `[geeksforgeeks]` 