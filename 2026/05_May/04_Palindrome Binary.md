# 🔁 Palindrome Binary

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/palindrome-numbers0942/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-49.1%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
[![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an integer `n`, determine whether its binary representation forms a **palindrome**. Return `true` if the binary representation of `n` is a palindrome; otherwise, return `false`.

**Note:** A binary representation is considered a palindrome if it reads the same forward and backward.

---

## 💡 Examples

**Example 1:**
```text
Input: n = 17
Output: true
Explanation: Binary representation of 17 is (10001)₂, which reads the same forward and backward, so it is a palindrome.
```

**Example 2:**
```text
Input: n = 16
Output: false
Explanation: Binary representation of 16 is (10000)₂, which is not a palindrome. 
```

<details>
<summary><b>📖 Example Breakdown (n = 17)</b></summary>

1. Binary of `17` is `10001`.
2. Reversing the string `10001` gives us `10001`.
3. Since the reversed binary string equals the original binary string, `17` is a binary palindrome.
</details>

---

## ⚙️ Constraints

> - `1 ≤ n ≤ 10^9`

**Expected Complexities:**
* **Time Complexity:** $O(\log n)$
* **Auxiliary Space:** $O(1)$

---

## 🚀 Solution Approach

### Bitwise Reversal Method
**Intuition:** 
Instead of converting the number into a string or an array of bits, we can directly construct the reversed binary representation of the given integer using bitwise operations. By extracting the least significant bit (LSB) and shifting it into a new integer, we build the exact reverse of the binary sequence. If this newly constructed integer equals the original, the binary representation is a palindrome.

### C++ Code Implementation
```cpp
// Intuition: A binary representation is a palindrome if reversing its bits yields the original number. We can build this reversed binary number bit by bit using bitwise operators.
// Approach: 
// 1. Store the original number in a temporary variable.
// 2. Extract the least significant bit (LSB) of the temporary variable.
// 3. Shift the reversed number left by 1 and append the extracted LSB.
// 4. Shift the temporary variable right by 1 to process the next bit.
// 5. Repeat until the temporary variable becomes 0, then compare the reversed number with the original.
// Time Complexity: O(log n) - We process each bit of the integer n, which takes logarithmic time relative to the value of n.
// Space Complexity: O(1) - Only a few integer variables are used, taking constant extra space.

class Solution {
public:
    bool isBinaryPalindrome(int x) {
        int rev = 0, temp = x;
    
        while (temp > 0) {
            // Append LSB of temp to rev
            rev = (rev << 1) | (temp & 1); 
            
            // Shift temp right to process the next bit
            temp >>= 1; 
        }
    
        // Check if the reversed binary equals the original
        return x == rev;
    }
};

/*
*
* Dry Run
* Input: x = 17 (Binary: 10001)
* Initial: rev = 0, temp = 17
*
* Iteration 1:
* LSB of temp = 17 & 1 = 1
* rev = (0 << 1) | 1 = 1
* temp = 17 >> 1 = 8
*
* Iteration 2:
* LSB of temp = 8 & 1 = 0
* rev = (1 << 1) | 0 = 2 (Binary: 10)
* temp = 8 >> 1 = 4
*
* Iteration 3:
* LSB of temp = 4 & 1 = 0
* rev = (2 << 1) | 0 = 4 (Binary: 100)
* temp = 4 >> 1 = 2
*
* Iteration 4:
* LSB of temp = 2 & 1 = 0
* rev = (4 << 1) | 0 = 8 (Binary: 1000)
* temp = 2 >> 1 = 1
*
* Iteration 5:
* LSB of temp = 1 & 1 = 1
* rev = (8 << 1) | 1 = 17 (Binary: 10001)
* temp = 1 >> 1 = 0
*
* Loop terminates since temp is 0.
* Return x == rev -> 17 == 17 -> true
*
*/
```

---

## 🧠 Key Insights

* **Bitwise Supremacy:** Using bitwise operators (`<<`, `>>`, `|`, `&`) is significantly faster and more memory-efficient than converting the integer into a binary string or array.
* **Overflow Safety:** Since `n` is up to `10^9`, its binary representation takes at most 30 bits. Reversing it fits safely within a standard 32-bit signed integer. 

---

## 🔍 Further Exploration

If you enjoyed this problem, you might want to try these related concepts:
* **Palindrome Number:** Determine if a number is a palindrome in Base 10.
* **Reverse Bits:** Reverse the bits of a given 32-bit unsigned integer.
* **Check if a number is a power of 2:** Another classic bit manipulation problem.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Palindrome Binary](https://www.geeksforgeeks.org/problems/palindrome-numbers0942/1)
* **Topics:** Mathematical, Algorithms, Bit Manipulation

---

## 👤 Author

**Nilesh**
* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#BitManipulation` `#Algorithms` `#Mathematical` `#GeeksforGeeks` `#Cpp` `#DataStructures`