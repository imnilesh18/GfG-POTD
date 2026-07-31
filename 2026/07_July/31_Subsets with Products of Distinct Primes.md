# 🔴 Subsets with Products of Distinct Primes

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-008A00?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/game-of-subsets/1)
[![Difficulty: Hard](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)]()
[![Accuracy: 66.87%](https://img.shields.io/badge/Accuracy-66.87%25-blue?style=for-the-badge)]()
[![Points: 8](https://img.shields.io/badge/Points-8-orange?style=for-the-badge)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](#-license)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an integer array `arr[]`, count the number of different subsets whose product can be represented as a product of **one or more distinct prime numbers**. Two subsets are considered different if the set of chosen array indices are not the same.

Return the count modulo **10⁹ + 7**.

---

## 🧪 Examples

### Example 1
```text
Input: arr[] = [1, 2, 3, 4]
Output: 6
Explanation: 
The subsets are:
- [2]       -> product = 2 = 2
- [3]       -> product = 3 = 3
- [1, 2]    -> product = 2 = 2
- [1, 3]    -> product = 3 = 3
- [2, 3]    -> product = 6 = 2 × 3
- [1, 2, 3] -> product = 6 = 2 × 3
All these products can be expressed as a product of one or more distinct prime numbers. Hence, the count is 6.
Note that [4] or any other subset with 4 are not chosen because products having 4 have repeated prime factors (2 x 2).
```

### Example 2
```text
Input: arr[] = [2, 2, 3]
Output: 5
Explanation: 
Since subsets formed using different indices are considered different, the chosen subsets are:
- [2] (using the first 2)
- [2] (using the second 2)
- [3]
- [2, 3] (using the first 2)
- [2, 3] (using the second 2)
Each subset has a product that can be expressed as a product of one or more distinct prime numbers.
Therefore, the answer is 5.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough of Example 1)</b></summary>

1. **Analyze Array Elements**: `[1, 2, 3, 4]`
2. **Filter Elements**:
   - `1`: Can be optionally attached to any valid subset without introducing new prime factors.
   - `2`: Prime factor `{2}` (Valid).
   - `3`: Prime factor `{3}` (Valid).
   - `4`: $2 \times 2$ contains duplicate prime factors (Invalid, ignore).
3. **Subsets from {2, 3}**:
   - `{2}` (Product: 2)
   - `{3}` (Product: 3)
   - `{2, 3}` (Product: 6 = $2 \times 3$)
   - Total non-empty subsets without 1s = **3**.
4. **Account for 1s**:
   - Count of `1` = 1.
   - Total choices for 1s = $2^1 = 2$.
5. **Final Subsets**: $3 \times 2 = 6$.
</details>

---

## ⛔ Constraints

> - `1 ≤ arr.size() ≤ 10⁵`
> - `1 ≤ arr[i] ≤ 30`

---

## 💡 Solution Approach

### Dynamic Programming with Bitmask

#### Intuition
Since `arr[i] ≤ 30`, the only prime numbers we need to consider are the **10 prime numbers** up to 30: **[2, 3, 5, 7, 11, 13, 17, 19, 23, 29]**.
Any number $x \le 30$ can be represented using a **10-bit bitmask**, where the $i$-th bit is set if the $i$-th prime divides $x$.

- Numbers containing squared prime factors (e.g., $4 = 2^2$, $9 = 3^2$, $12 = 2^2 \times 3$) can **never** be included in any valid subset.
- The number `1` has no prime factors and can be attached to any valid non-empty subset.
- We use 0/1 Knapsack style Dynamic Programming over the bitmask space ($2^{10} = 1024$ states) to calculate the count of valid subsets.

---

#### C++ Implementation

```cpp
// Intuition: The maximum value of arr[i] is 30, which has only 10 prime factors (2, 3, 5, 7, 11, 13, 17, 19, 23, 29). We can use a 10-bit mask to represent prime factors, filter non-square-free numbers, and use DP to find distinct prime product combinations.
// Approach: Count element frequencies, map square-free numbers to bitmasks, run 1D DP backwards over bitmask states, and scale the answer by 2^(frequency of 1).
// Time Complexity: O(N + 30 * 2^10) = O(N) where N is array length, since 30 * 1024 is constant (~30,000 operations).
// Space Complexity: O(2^10) = O(1) auxiliary space for DP table of size 1024.

class Solution {
  public:
    int countSubsets(vector<int> &arr) {
        long long MOD = 1e9 + 7;
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        vector<long long> freq(31, 0);

        // Count element frequencies
        for (int x : arr) {
            freq[x]++;
        }

        // Precompute bitmasks for square-free numbers
        vector<int> mask_of(31, 0);
        for (int i = 2; i <= 30; i++) {
            int temp = i;
            int mask = 0;
            bool is_square_free = true;

            for (int j = 0; j < 10; j++) {
                int count = 0;
                while (temp % primes[j] == 0) {
                    count++;
                    temp /= primes[j];
                }
                if (count > 1) { // Contains repeated prime factor
                    is_square_free = false;
                    break;
                }
                if (count == 1) {
                    mask |= (1 << j);
                }
            }
            mask_of[i] = is_square_free ? mask : -1;
        }

        // DP state: dp[mask] = count of subsets with prime factor state mask
        vector<long long> dp(1 << 10, 0);
        dp[0] = 1; // Base case: empty subset

        // DP transitions for elements from 2 to 30
        for (int i = 2; i <= 30; i++) {
            if (freq[i] == 0 || mask_of[i] == -1) continue;
            int x_mask = mask_of[i];
            long long count = freq[i];

            // Iterate backwards to prevent using frequency of same number multiple times
            for (int mask = (1 << 10) - 1; mask >= 0; mask--) {
                if ((mask & x_mask) == 0) { // Disjoint prime factors check
                    dp[mask | x_mask] = (dp[mask | x_mask] + dp[mask] * count) % MOD;
                }
            }
        }

        // Sum all valid non-empty subset counts
        long long total_subsets = 0;
        for (int mask = 1; mask < (1 << 10); mask++) {
            total_subsets = (total_subsets + dp[mask]) % MOD;
        }

        // Scale by 2^(freq[1]) for combinations involving 1s
        long long pow2 = 1;
        for (int i = 0; i < freq[1]; i++) {
            pow2 = (pow2 * 2) % MOD;
        }

        return (total_subsets * pow2) % MOD;
    }
};

/*
* Dry Run
*
* Input: arr = [1, 2, 3, 4]
* Frequencies: freq[1]=1, freq[2]=1, freq[3]=1, freq[4]=1
* Primes <= 30: [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
*
* Square-free Masks:
* Number 2: mask = 0000000001 (bit 0 for prime 2)
* Number 3: mask = 0000000010 (bit 1 for prime 3)
* Number 4: invalid (2^2), mask = -1
*
* DP Transitions:
* Initial: dp[0] = 1
* Process x = 2 (mask = 1, freq = 1):
*   dp[1] = dp[1] + dp[0] * 1 = 1
* Process x = 3 (mask = 2, freq = 1):
*   dp[2] = dp[2] + dp[0] * 1 = 1
*   dp[3] = dp[3] + dp[1] * 1 = 1
*
* Sum of non-empty DP states (dp[1] + dp[2] + dp[3]) = 3
* Multiply by choices of 1s: freq[1] = 1 -> pow2 = 2^1 = 2
* Total Subsets = 3 * 2 = 6
*
* Final Output: 6
*/
```

---

## 🔑 Key Insights

1. **State Space Reduction**: Although array length $N \le 10^5$, elements $arr[i] \le 30$. Frequency array compresses input size.
2. **Bitmasking Primes**: There are only 10 primes $\le 30$. Using bitwise operations (`mask & x_mask == 0`), we check distinct prime factor availability in $O(1)$ time.
3. **Filtering Non-Square-Free Numbers**: Numbers divisible by $p^2$ (such as 4, 8, 9, 12, 16, 18, 20, 24, 25, 27, 28) are automatically skipped.
4. **Multiplier for `1`s**: Adding `1` to any valid subset does not change its product's prime factor composition. If `1` occurs $k$ times, it multiplies total combinations by $2^k$.

---

## 🛠️ Further Exploration

- [Partition Equal Subset Sum](https://www.geeksforgeeks.org/problems/subset-sum-problem2014/1)
- [Subset Sum Problem](https://www.geeksforgeeks.org/problems/subset-sum-problem1611/1)
- [Count Subsets with Given Difference](https://www.geeksforgeeks.org/problems/target-sum-1626861722/1)

---

## 🔗 References

- **GeeksforGeeks Problem**: [Subsets with Products of Distinct Primes (Game of Subsets)](https://www.geeksforgeeks.org/problems/game-of-subsets/1)
- **Topic Tags**: `Dynamic Programming`, `Bit Magic`, `Mathematics`

---

## 👤 Author

Created with ❤️ by [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Dynamic Programming](https://img.shields.io/badge/Topic-Dynamic_Programming-blue?style=flat-square)
![Bit Magic](https://img.shields.io/badge/Topic-Bit_Magic-purple?style=flat-square)
![Math](https://img.shields.io/badge/Topic-Math-yellow?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-green?style=flat-square)