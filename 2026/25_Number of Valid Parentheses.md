# 🟧 Number of Valid Parentheses

![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?logo=geeksforgeeks&logoColor=white)
![Accuracy](https://img.shields.io/badge/Accuracy-66.08%25-green)
![Points](https://img.shields.io/badge/Points-4-blue)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

> **⚠️ Educational Use Only**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/problems/valid-number-of-parenthesis/1) problem.

---

## 📝 Problem Statement

You are given a number `n`, your task is to find the number of **all** the valid parentheses expressions of that length using only `"("` and `")"` brackets.

An input string of parentheses is valid if:
1.  Open brackets must be closed in **correct** order.
2.  **Every** close bracket has a corresponding open bracket.

For example - `"()()"` or `"(())"` are valid while `")()("` or `"))(("` are invalid parentheses expressions.

### ℹ️ Constraints

* `1 ≤ n ≤ 20`

---

## 📊 Examples

```bash
Input: n = 2
Output: 1
Explanation: There is only one possibe valid expressions of length 2 i.e., "()".

```

```bash
Input: n = 4
Output: 2
Explanation: Possibe valid expressions of length 4 are "(())" and "()()".

```

```bash
Input: n = 6
Output: 5
Explanation: Possibe valid expressions of length 6 are "((()))", "(())()", "()(())", "()()()" and "(()())".

```

<details>
<summary><b>📖 Example Breakdown: n = 6</b></summary>

For a length of `n = 6`, we strictly need `3` pairs of parentheses (`k = 3`).
The number of valid combinations corresponds to the 3rd Catalan number ().

The 5 valid combinations are:

1. `((()))` - Nested completely
2. `(())()` - Nested pair followed by single pair
3. `()(())` - Single pair followed by nested pair
4. `()()()` - Three sequential pairs
5. `(()())` - Two pairs nested inside one

Mathematical calculation:



</details>

---

## 💡 Solution Approaches

### 1️⃣ Mathematical Approach (Catalan Numbers)

#### Intuition

The problem asks for the number of valid parentheses sequences of a specific length `n`. A fundamental property of valid parentheses is that for every closing bracket, there must be a preceding matching opening bracket, and the total count of open and close brackets must be equal. This structure maps directly to **Catalan Numbers**. Since valid parentheses must come in pairs, an odd `n` immediately implies 0 valid sequences. For an even `n`, we are looking for the -th Catalan number, where .

#### Approach

1. **Check Parity**: If `n` is odd, return `0` immediately.
2. **Identify Pairs**: Calculate `k = n / 2`.
3. **Compute Binomial Coefficient**: We need to calculate . We can do this iteratively to keep intermediate values manageable.
* Iterate `i` from `0` to `k-1`.
* Update result: `res = res * (2k - i) / (i + 1)`.


4. **Apply Catalan Formula**: The -th Catalan number is . Divide the computed binomial coefficient by `k + 1`.

#### Complexity

* **Time Complexity**:  - We iterate `n/2` times to calculate the binomial coefficient.
* **Space Complexity**:  - We utilize a constant amount of extra space for variables.

```cpp
// Intuition: The problem requires counting valid parentheses sequences of length n. This is a classic application of Catalan numbers. Since parentheses come in pairs, n must be even. The solution involves computing the (n/2)-th Catalan number.
// Approach: First, handle the edge case where n is odd (return 0). Let k = n/2. Calculate the combination 2kCk (2k choose k) iteratively to avoid large factorials. Finally, divide by (k+1) to get the Catalan number C_k = (1/(k+1)) * (2kCk).
// Time Complexity: O(n) - The loop runs k times, where k = n/2.
// Space Complexity: O(1) - Only a few variables are used for storage.

class Solution {
  public:
    int findWays(int n) {
        // A valid parentheses string must have an even length.
        // If n is odd, it's impossible to pair them all up.
        if (n % 2 != 0) {
            return 0;
        }

        // We need to find the k-th Catalan number, where k is the number of pairs.
        int k = n / 2;
        
        // Use long long to prevent potential overflow during multiplication,
        // though for n <= 20, standard int would strictly suffice (C_10 = 16796).
        long long res = 1;
        
        // Calculate nCr(2k, k) iteratively
        // Formula: res = res * (2k - i) / (i + 1)
        for (int i = 0; i < k; i++) {
            res = res * (2 * k - i); // Multiply by numerator term
            res = res / (i + 1);     // Divide by denominator term
        }
        
        // Apply the Catalan divisor: 1 / (k + 1)
        return res / (k + 1);
    }
};

/*
*
* Dry Run
* Input: n = 6
* * 1. Check Parity: 6 % 2 == 0. Continue.
* 2. Calculate k: k = 6 / 2 = 3.
* 3. Initialize res = 1.
* * 4. Loop i from 0 to 2:
* i = 0: 
* res = 1 * (6 - 0) = 6
* res = 6 / 1 = 6
* i = 1:
* res = 6 * (6 - 1) = 30
* res = 30 / 2 = 15
* i = 2:
* res = 15 * (6 - 2) = 60
* res = 60 / 3 = 20
* * 5. Final Calculation:
* return res / (k + 1) -> 20 / (3 + 1) -> 20 / 4 = 5
* * Output: 5
*
*/

```

---

## 🔑 Key Insights

* **Parity Check**: The most basic insight is that a valid parenthesis string effectively consists of pairs. Any odd length `n` is immediately invalid.
* **Combinatorics**: The number of valid parenthesis expressions of length `2k` is exactly the **-th Catalan Number**, denoted .
* **Formula**: The direct formula  is efficient. Calculating  can be done in  time without computing full factorials, preventing overflow for moderate inputs.

---

## 🚀 Further Exploration

* **Generate Parentheses**: Try printing all the valid combinations instead of just counting them (recursion/backtracking).
* **Longest Valid Parentheses**: Find the length of the longest valid substring.
* **Score of Parentheses**: Calculate score based on nesting depth.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/valid-number-of-parenthesis/1)
* [Catalan Numbers - Wikipedia](https://en.wikipedia.org/wiki/Catalan_number)

---

## 👤 Author

**Nilesh** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

> **Note**: This repository is for educational purposes. Please respect the Code of Conduct and use these solutions for learning.
