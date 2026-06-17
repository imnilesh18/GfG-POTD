# 🟧 Cut rope to maximise product

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/max-rope-cutting1312/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-40.16%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="MIT License" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a rope of length `n` meters, cut it into multiple smaller ropes such that the product of their lengths is maximized. At least one cut is mandatory.

---

## 💡 Examples

```text
Input: n = 2
Output: 1
Explanation: Since 1 cut is mandatory. Maximum obtainable product is 1 * 1 = 1.
```

```text
Input: n = 5
Output: 6
Explanation: Maximum obtainable product is 2 * 3 = 6.
```

<details>
<summary>📖 Example Breakdown (n = 10)</summary>

1. If we cut it into `2, 2, 2, 2, 2`, the product is `32`.
2. If we cut it into `3, 3, 3, 1`, the product is `27`.
3. If we cut it into `3, 3, 4`, the product is `36`.

The maximum possible product for `10` is `36`.
</details>

---

## 🛑 Constraints

- `2 ≤ n ≤ 58`

---

## 💻 Solution Approach

### Math/Greedy Optimization

**Intuition:** To maximize the product, we should break the integer into numbers as close to $e$ ($~2.718$) as possible. The nearest integer is $3$. Hence, we cut the rope into segments of length $3$ to maximize the product. The only exception is when the remaining length is $4$, which is better left as $4$ (since $2 \times 2 = 4$, whereas $3 \times 1 = 3$).

```cpp
// Intuition: To maximize the product, we should cut the rope into lengths of 3. Lengths of 2 are the next best, and lengths of 1 should be avoided since they do not increase the product.
// Approach: If n is 2 or 3, we must cut it once, yielding n-1. For n > 3, we repeatedly subtract 3 from the length and multiply the product by 3 as long as the remaining length is greater than 4. The final remaining length (2, 3, or 4) is multiplied to the product.
// Time Complexity: O(n) because we reduce n by 3 in each iteration of the while loop.
// Space Complexity: O(1) as we are only using a few integer variables.

class Solution {
  public:
    int maxProduct(int n) {
        // Base Cases
        // Rope of length 2 or 3 must be cut at least once
        if (n == 2 || n == 3) {
            return n - 1;
        }
    
        // Store final product
        int product = 1;
    
        // Keep cutting parts of length 3
        // while remaining length is greater than 4
        while (n > 4) {
            // Multiply current product by 3
            product *= 3;
    
            // Reduce rope length
            n -= 3;
        }
    
        // Multiply remaining rope length
        return product * n;
    }
};

/*
*
* Dry Run
*
* Input: n = 10
* Initial state: product = 1, n = 10
* * Iteration 1:
* n (10) > 4 is TRUE
* product = 1 * 3 = 3
* n = 10 - 3 = 7
* * Iteration 2:
* n (7) > 4 is TRUE
* product = 3 * 3 = 9
* n = 7 - 3 = 4
* * Iteration 3:
* n (4) > 4 is FALSE. Loop ends.
* * Return: product * n -> 9 * 4 = 36
* Output: 36
*
*/
```

---

## 🔑 Key Insights

1. **The Rule of 3s:** In mathematics, to maximize the product of components with a fixed sum, you want the pieces to be as close to `e` (~2.71) as possible. Thus, dividing into 3s gives the best product.
2. **Handling 4s:** A piece of length 4 shouldn't be broken into `3` and `1` because `3 * 1 = 3`, whereas keeping it as `4` (or `2 * 2`) yields a product of `4`.
3. **Base Cases:** For `n = 2` and `n = 3`, we are forced to make a cut, yielding products `1` and `2` respectively, which are strictly less than the length itself. This is why we treat them as base cases right away.

---

## 🚀 Further Exploration

- [Integer Break (LeetCode 343)](https://leetcode.com/problems/integer-break/) - This is exactly the same problem on LeetCode.
- [Coin Change (GFG / LeetCode)](https://leetcode.com/problems/coin-change/) - A standard DP problem that involves optimal partitioning.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Cut rope to maximise product](https://www.geeksforgeeks.org/problems/max-rope-cutting1312/1)

---

## 🧑‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#math` `#greedy` `#dynamic-programming` `#geeksforgeeks` `#c++`