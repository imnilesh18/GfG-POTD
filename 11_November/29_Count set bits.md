# 🟧 Count set bits

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D35?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-total-set-bits-1587115620/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-FF8000?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-total-set-bits-1587115620/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-35.77%25-0075FF?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-total-set-bits-1587115620/1)
[![Points](https://img.shields.io/badge/Points-4-28a745?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-total-set-bits-1587115620/1)
[![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge&logo=github)](https://github.com/imnilesh18/gfg-potd/blob/master/LICENSE)

</div>

<p align="center">
  <b>⚠️ Educational Use Only:</b> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.
</p>

---

## 2. Problem Statement

You are given a number `n`. Find the total count of set bits for all numbers from **1** to **n** (both inclusive).

### 4. Constraints

- `1 ≤ n ≤ 10^8`

---

## 3. Examples

### Example 1

```
Input: n = 4
Output: 5
```

### Example 2

```
Input: n = 17
Output: 35
```

<details>
<summary><b>📖 Example Breakdown: n = 4</b></summary>

For numbers from 1 to 4:
- **1** (001): 1 set bit
- **2** (010): 1 set bit
- **3** (011): 2 set bits
- **4** (100): 1 set bit

**Total**: 1 + 1 + 2 + 1 = **5**
</details>

---

## 5. Solution Approaches

### Optimized Recursive Approach

The problem asks for the sum of set bits from 1 to n. An $O(n)$ approach is too slow. We can solve this in $O(\log n)$ by decomposing $n$ based on the most significant bit position.
For any power of 2, say $2^x$, the numbers from 0 to $2^x - 1$ have exactly $x \times 2^{x-1}$ set bits.
We split the range into:
1.  **Full Pattern:** $[0, 2^x - 1]$
2.  **MSB Contribution:** $[2^x, n]$
3.  **Remaining Bits:** Recursively solve for $n - 2^x$

```cpp
// Intuition: Decompose the problem based on the Most Significant Bit (MSB). The bits up to the largest power of 2 follow a mathematical pattern (x * 2^(x-1)), and the remaining bits can be solved recursively.
// Approach:
// 1. Find the largest power of 2 (x) such that 2^x <= n.
// 2. Count bits in the "full" pattern range [0, 2^x - 1] using the formula x * 2^(x-1).
// 3. Add the MSB count for the range [2^x, n], which is (n - 2^x + 1).
// 4. Recursively calculate the bits for the remaining numbers (n - 2^x).
// Time Complexity: O(log n) - We reduce the number by its MSB in each step.
// Space Complexity: O(log n) - Due to recursion stack depth.

class Solution {
  public:
    int countSetBits(int n) {
        // Base case
        if (n == 0) return 0;

        // Find highest power of 2 less than or equal to n
        // Note: log2 returns double, casting to int gives the floor value
        int x = (int)log2(n);

        // Set bits in the full pattern 0 to (2^x - 1)
        // FIXED: Added check to prevent left shift by negative number
        int fullBits = (x == 0) ? 0 : x * (1 << (x - 1));

        // Contribution of the highest bit from 2^x to n
        int msbBits = n - (1 << x) + 1;

        // Recursively count remaining set bits after removing highest bit
        // The problem reduces to finding set bits for (n - 2^x)
        int remaining = n - (1 << x);
        int remainingBits = countSetBits(remaining);

        // Total set bits
        return fullBits + msbBits + remainingBits;
    }
};

/*
*
* Dry Run
* Input: n = 4
*
* 1. countSetBits(4):
* - x = log2(4) = 2. (2^2 = 4 <= 4)
* - fullBits (range 0 to 3): 2 * 2^(2-1) = 4.
* - msbBits (range 4 to 4): 4 - 4 + 1 = 1.
* - remaining: 4 - 4 = 0.
* - Call countSetBits(0).
*
* 2. countSetBits(0):
* - Base case reached. Returns 0.
*
* 3. Back to countSetBits(4):
* - remainingBits = 0.
* - Total = 4 (full) + 1 (msb) + 0 (remaining) = 5.
* - Returns 5.
*
* Output: 5
*/
```

---

## 6. Key Insights

* **Pattern Recognition:** The sequence of set bits from $0$ to $2^x-1$ follows the formula $x \times 2^{x-1}$.
* **Divide and Conquer:** By removing the Most Significant Bit chunk, the problem reduces to a smaller instance of itself (finding set bits for $n - 2^x$).
* **MSB Counting:** The MSB is set for every number from $2^x$ to $n$. This count is simply $(n - 2^x + 1)$.

---

## 7. Further Exploration

* **Number of 1 Bits:** [LeetCode 191](https://leetcode.com/problems/number-of-1-bits/)
* **Counting Bits:** [LeetCode 338](https://leetcode.com/problems/counting-bits/)
* **Reverse Bits:** [LeetCode 190](https://leetcode.com/problems/reverse-bits/)

---

## 8. References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/count-total-set-bits-1587115620/1)

---

## 9. Author

[imnilesh18](https://github.com/imnilesh18)

---

## 10. Tags

![Bit Manipulation](https://img.shields.io/badge/Tag-Bit_Manipulation-blue?style=flat-square)
![Recursion](https://img.shields.io/badge/Tag-Recursion-green?style=flat-square)
![Math](https://img.shields.io/badge/Tag-Math-purple?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/Tag-GeeksforGeeks-orange?style=flat-square)

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

> **Note**: This repository is for educational purposes. Please do not use this code for academic dishonesty or plagiarism.
