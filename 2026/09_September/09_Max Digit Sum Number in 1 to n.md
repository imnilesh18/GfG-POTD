# 🟩 Max Digit Sum Number in 1 to n

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Practice-29b6f6?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/biggest-integer-having-maximum-digit-sum1704/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-49.35%25-blue?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](#license)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.

---

## 📝 Problem Statement

Given a positive integer `n`, find a number in the range from `1` to `n` such that its digit sum is maximum. If there are multiple such numbers with the same maximum digit sum, return the largest among them.

---

## 📥 Examples

### Example 1
```text
Input: n = 48
Output: 48
Explanation: The numbers with maximum digit sum in range [1, 48] are 48 and 39 (both have digit sum = 12). Since 48 > 39, the answer is 48.
```

### Example 2
```text
Input: n = 90
Output: 89
Explanation: 89 gives the largest digit sum (8 + 9 = 17) in the range from 1 to 90. Hence, the answer is 89.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough for n = 90)</b></summary>

<br>

* **Initial candidate:** `90` $\rightarrow$ Digit sum = $9 + 0 = 9$
* **Option 1 (Modify index 0):** Decrement digit `'9'` to `'8'` and fill trailing positions with `'9'`:
  * Candidate: `89`
  * Digit sum: $8 + 9 = 17$
* **Option 2 (Modify index 1):** Digit is `'0'`, skipping reduction.
* **Comparison:** Maximum digit sum achieved is `17` with number `89`.

</details>

---

## ⛓️ Constraints

> - $1 \le n \le 10^9$
> - **Expected Time Complexity:** $\mathcal{O}(m)$ where $m$ is the number of digits in $n$.
> - **Expected Auxiliary Space:** $\mathcal{O}(m)$ where $m$ is the number of digits in $n$.

---

## 💡 Solution Approach

### Greedy Digit Manipulation Strategy

To find a number $\le n$ with the maximum digit sum, checking every number from $1$ to $n$ sequentially will cause a **Time Limit Exceeded (TLE)** error because $n$ can be up to $10^9$.

Instead, we observe that optimal candidates are formed either by:
1. The number $n$ itself.
2. Decrementing a non-zero digit at position $i$ by `1` and changing all digits to its right to `'9'`.

By trying this modification for every digit position $i$, we generate all potential maximum digit-sum candidates in $\mathcal{O}(m^2)$ time (where $m \le 10$ is the digit length), then pick the best candidate.

#### C++ Solution

```cpp
// Intuition: To maximize digit sum <= n, we evaluate n itself and numbers formed by decrementing digit s[i] and replacing trailing digits with '9'.
// Approach: Convert n to string, initialize bestNum = n with its digit sum, iterate through digits, decrement non-zero s[i], fill right digits with '9', compare digit sums, and keep the largest value on ties.
// Time Complexity: O(m^2) where m is the number of digits in n (m <= 10 for n <= 10^9).
// Space Complexity: O(m) to store the string representation of digits.

class Solution {
  private:
    // Helper function to calculate sum of digits of a given number
    int getDigitSum(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10; // Extract last digit
            num /= 10;      // Remove last digit
        }
        return sum;
    }

  public:
    int findMax(int n) {
        string s = to_string(n); // Convert number to string for digit access
        int bestNum = n;
        int maxSum = getDigitSum(n); // Base candidate is n itself

        // Try reducing each digit and setting the rest to '9'
        for (int i = 0; i < s.length(); i++) {
            if (s[i] > '0') {
                string temp = s;
                temp[i]--; // Reduce current digit by 1

                // Set all digits to the right to '9'
                for (int j = i + 1; j < temp.length(); j++) {
                    temp[j] = '9';
                }

                int val = stoi(temp);            // Convert back to integer
                int currentSum = getDigitSum(val); // Calculate new digit sum

                // Update bestNum if a higher sum is found, or if equal sum but larger value
                if (currentSum > maxSum) {
                    maxSum = currentSum;
                    bestNum = val;
                } else if (currentSum == maxSum) {
                    bestNum = max(bestNum, val);
                }
            }
        }

        return bestNum;
    }
};

/*
*
* Dry Run
*
* Input: n = 48
* 
* Initial State:
* s = "48", bestNum = 48, maxSum = getDigitSum(48) = 12
* 
* Iteration 0 (i = 0, s[0] = '4'):
* - Decrement s[0] -> '3'
* - Set trailing digits to '9' -> temp = "39"
* - val = 39, currentSum = getDigitSum(39) = 12
* - currentSum (12) == maxSum (12) -> bestNum = max(48, 39) = 48
* 
* Iteration 1 (i = 1, s[1] = '8'):
* - Decrement s[1] -> '7'
* - No trailing digits to right -> temp = "47"
* - val = 47, currentSum = getDigitSum(47) = 11
* - currentSum (11) < maxSum (12) -> No update
* 
* Final Result: 48
*
*/
```

---

## 🔑 Key Insights

* **Greedy Choice Property:** Filling trailing digits with `'9'` maximizes the digit sum for any fixed prefix choice.
* **Small Search Space:** A number $n \le 10^9$ has at most $10$ digits, making candidate evaluation effectively $\mathcal{O}(1)$ operations.
* **Tie-Breaking Rule:** When two numbers produce the same digit sum, taking `max(bestNum, val)` guarantees returning the largest integer.

---

## 🚀 Further Exploration

* [Count numbers with maximum digit sum in range](https://www.geeksforgeeks.org/problems/biggest-integer-having-maximum-digit-sum1704/1)
* [Digit DP Techniques for Range Sum Problems](https://www.geeksforgeeks.org/digit-dp-introduction/)

---

## 📚 References

* **GeeksforGeeks Problem Page:** [Max Digit Sum Number in 1 to n](https://www.geeksforgeeks.org/problems/biggest-integer-having-maximum-digit-sum1704/1)

---

## 👤 Author

Developed & Maintained by [imnilesh18](https://github.com/imnilesh18).

---

## 🏷️ Tags

`mathematics` `numbers` `greedy` `cpp` `geeksforgeeks` `digit-manipulation`