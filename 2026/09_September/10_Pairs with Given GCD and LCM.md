# 🧮 Pairs with Given GCD and LCM

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-62.15%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="MIT License" />
</div>

<div align="center">
  <h3>⚠️ Educational Use Only</h3>
  <p><i>This repository and its content are intended solely for educational purposes.<br>
  Solutions are provided for learning, practice, and reference only.<br>
  Problem statement and test cases are based on the GeeksforGeeks problem.</i></p>
</div>

---

## 📝 Problem Statement

Given two integers `x` and `y` representing the GCD and LCM of two unknown positive integers `a` and `b`, count the number of valid pairs `(a, b)` satisfying these conditions[cite: 1]. Note that `(a, b)` and `(b, a)` are counted as distinct pairs when `a ≠ b`[cite: 1].

---

## 🚦 Constraints

- `1 ≤ x, y ≤ 10^4`[cite: 1]
- **Expected Time Complexity:** `O(sqrt(n)log(n))`[cite: 1]
- **Expected Auxiliary Space:** `O(1)`[cite: 1]

---

## 💡 Examples

```text
Input: x = 2, y = 12
Output: 4
Explanation: The valid pairs are (2, 12), (4, 6), (6, 4), and (12, 2), since each pair has GCD = 2 and LCM = 12.
```

```text
Input: x = 6, y = 4
Output: 0
Explanation: LCM must always be a multiple of GCD. Since y is not divisible by x, no valid pair exists.
```

<details>
<summary>📖 <b>Example Breakdown (x = 2, y = 12)</b></summary>

1. We know that the LCM (`y`) must be perfectly divisible by the GCD (`x`). Here, `12 % 2 == 0`, which is true.
2. We find the product of their non-common factors by taking `n = y / x`, which gives `12 / 2 = 6`.
3. We need to find factors `i` and `j` of `6` where `i * j = 6` and `GCD(i, j) == 1` (they must be coprime).
4. Checking factors up to `sqrt(6)`:
   - **i = 1**: `j = 6 / 1 = 6`. Check `GCD(1, 6) == 1`. Valid. Multiplying by `x` gives pair `(2, 12)`. Since `1 ≠ 6`, `(12, 2)` is also counted. (+2 pairs)
   - **i = 2**: `j = 6 / 2 = 3`. Check `GCD(2, 3) == 1`. Valid. Multiplying by `x` gives pair `(4, 6)`. Since `2 ≠ 3`, `(6, 4)` is also counted. (+2 pairs)
5. Total valid pairs = **4**.

</details>

---

## ⚙️ Solution Approaches

### Mathematical Factorization Approach
**(Translated and adapted into English from the mathematical intuition)**

The core idea relies on the relationship between two numbers, their GCD, and their LCM. The LCM of two numbers is always a multiple of their GCD. If we divide the LCM by the GCD (let's call this `n`), the problem reduces to finding pairs of factors of `n` that are **coprime** (their GCD is 1). By iterating through all possible factor pairs `(i, j)` of `n` up to `sqrt(n)`, we can quickly verify if they are coprime. For every valid coprime pair where `i != j`, we discover two distinct valid combinations `(x*i, x*j)` and `(x*j, x*i)`, so we increment our result by 2.

```cpp
// Intuition: Since LCM is always a multiple of GCD, dividing LCM by GCD gives the product of their non-common coprime factors. By finding all coprime factor pairs of this product, we can construct all valid pairs.
// Approach: 
// 1. Check if y (LCM) is divisible by x (GCD). If not, no such pairs can exist.
// 2. Let n = y / x. If n == 1, there is only one valid pair: (x, x).
// 3. Iterate from i = 1 up to sqrt(n) to find factor pairs (i, j = n/i).
// 4. For each factor pair, verify if multiplying them back by x yields the correct GCD (meaning i and j are coprime).
// 5. If valid and i != j, add 2 to the result because (a,b) and (b,a) count as distinct pairs.
// Time Complexity: O(sqrt(y/x) * log(y/x)) - We iterate up to sqrt(n). The GCD calculation inside the loop takes logarithmic time.
// Space Complexity: O(1) - Only a few integer variables are used for counting and math operations.

class Solution {
  public:
    int pairCount(int x, int y) {
        int n = 0, res = 0;

        // lcm must be divisible by gcd, else no pair exists
        if (y % x == 0)
            n = y / x;

        // if n is 1, the only pair is (x, x)
        if (n == 1)
            res = 1;

        // find coprime factor pairs (i, n/i) of n
        for (int i = 1; i <= sqrt(n); i++) {
            if (n % i == 0) {
                int j = n / i;

                // both (x*i, x*j) and (x*j, x*i) are valid
                // only if i and j are coprime (gcd = 1)
                if (i != j && __gcd(x * i, x * j) == x)
                    res += 2;
            }
        }

        return res;
    }
};

/*
* Dry Run
* Input: x = 2, y = 12
* Step 1: y % x -> 12 % 2 == 0. n = 12 / 2 = 6.
* Step 2: n is not 1, res remains 0.
* Step 3: Loop i from 1 to sqrt(6) (which is 2):
*         i = 1: 6 % 1 == 0. j = 6. 
*                i != j (1 != 6) and __gcd(2*1, 2*6) -> __gcd(2, 12) == 2 (x).
*                res += 2 -> res is now 2.
*         i = 2: 6 % 2 == 0. j = 3. 
*                i != j (2 != 3) and __gcd(2*2, 2*3) -> __gcd(4, 6) == 2 (x).
*                res += 2 -> res is now 4.
* Step 4: Loop ends. Return res = 4.
* Output: 4
*/
```

---

## 🔑 Key Insights

- **Number Theory Rule:** For any two numbers `a` and `b`, `LCM(a,b) * GCD(a,b) = a * b`. 
- **Coprime Multipliers:** The problem is drastically simplified by isolating the non-common factors. By proving that the non-common factors `i` and `j` are coprime, we guarantee that scaling them up by the original GCD `x` will maintain `x` as the exact Greatest Common Divisor of the new pair.
- **Square Root Optimization:** We only need to check factors up to `sqrt(n)` instead of `n`, heavily optimizing the time complexity.

---

## 🔍 Further Exploration

- What happens if we need to find pairs of three numbers given their GCD and LCM?
- Explore **Prime Factorization** strategies for cases where `x` and `y` constraints are up to `10^9`.
- **Related Problem:** Find the minimum sum of a pair with a given GCD and LCM.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Pairs with Given GCD and LCM](https://www.geeksforgeeks.org/problems/possible-pairs1550/1)[cite: 1]
- **Concepts:** Euclidean Algorithm for GCD, Mathematical Properties of LCM.

---

## ✍️ Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

- `mathematics`
- `number-theory`
- `factorization`
- `geeksforgeeks`
- `cpp`