# 🟥 Geek's Destination with Special Jump

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/geek-and-her-destination--145724/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-70.54%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-orange?style=for-the-badge)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

> ⚠️ **Educational Use Only:** This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Geek starts at position `0` on the positive X-axis and needs to reach or pass position `d` on the positive X-axis.

Geek normally follows a repeating movement pattern:
1. Move **forward** by `a` units, taking `a` seconds.
2. Move **backward** by `b` units, taking `b` seconds.

Geek also has a **special jump** that moves him exactly `j` units forward in `1` second. He can use it at any time, even in the middle of a forward or backward movement, and the journey ends immediately after the jump.

Given five integers `a`, `b`, `d`, `l`, and `r`:
- For every integer `j` in the range `[l, r]`, find the **minimum time** required for Geek to reach or pass position `d`.
- He may either use the special jump or reach the destination using normal movement alone, whichever takes less time.
- Return the **sum of the minimum times** for all jump lengths from `l` to `r` modulo $10^9 + 7$.

> **Note:** Each jump length `j` is considered independently.

---

## 🧪 Examples

### Example 1
```text
Input: a = 2, b = 1, d = 5, l = 3, r = 4
Output: 5
Explanation:
For j = 3: Geek moves 2 units forward (2s), then takes a jump of 3 units (1s) to reach position 5. Minimum time = 3 seconds.
For j = 4: Geek moves 1 unit forward (1s), then takes a jump of 4 units (1s) to reach position 5. Minimum time = 2 seconds.
Total sum for range [3, 4] = 3 + 2 = 5.
```

### Example 2
```text
Input: a = 4, b = 2, d = 8, l = 2, r = 4
Output: 26
Explanation:
For j = 2: Geek moves 4 units forward (4s), 2 units backward (2s), 4 units forward (4s) to reach 6, then jumps 2 units (1s) to reach 8. Minimum time = 11 seconds.
For j = 3: Geek moves 4 units forward (4s), 2 units backward (2s), 3 units forward (3s) to reach 5, then jumps 3 units (1s) to reach 8. Minimum time = 10 seconds.
For j = 4: Geek moves 4 units forward (4s) to reach 4, then jumps 4 units (1s) to reach 8. Minimum time = 5 seconds.
Total sum for range [2, 4] = 11 + 10 + 5 = 26.
```

<details>
<summary><b>📖 Example Breakdown (Example 2 Walkthrough)</b></summary>

Given `a = 4, b = 2, d = 8, l = 2, r = 4`:
- **Cycle Mechanics:**
  - Each full cycle moves Geek forward by `a = 4` units (in `4s`) and backward by `b = 2` units (in `2s`), resulting in a net gain of `a - b = 2` units every `a + b = 6` seconds.
  - **Cycle 0:** Starts at `0` (at `0s`), peaks at `4` (at `4s`), retreats to `2` (at `6s`).
  - **Cycle 1:** Starts at `2` (at `6s`), peaks at `6` (at `10s`), retreats to `4` (at `12s`).
- **Required Pre-Jump Position (`m = d - j`):**
  - For `j = 2`: Need `m = 8 - 2 = 6`. Reached at peak of Cycle 1 at `t = 10s`. Adding `1s` jump gives `11s`.
  - For `j = 3`: Need `m = 8 - 3 = 5`. Reached during Cycle 1 (`2 + 3 = 5`) at `t = 6 + 3 = 9s`. Adding `1s` jump gives `10s`.
  - For `j = 4`: Need `m = 8 - 4 = 4`. Reached at peak of Cycle 0 at `t = 4s`. Adding `1s` jump gives `5s`.
- **Total Sum:** `11 + 10 + 5 = 26`.

</details>

---

## 🔒 Constraints & Complexity Expectations

```text
• 1 ≤ a ≤ 10
• 0 < b < a
• a < d ≤ 10^8
• 0 < l ≤ r < d

Expected Time Complexity: O(1)
Expected Auxiliary Space: O(1)
```

---

## 💡 Solution Approaches

### 1. Brute-Force / Direct Cycle Math per Jump (TLE on Large Ranges)

#### Intuition
To reach or pass `d` using a jump of length `j`, Geek must reach at least position `m = d - j` before jumping (since `j ≥ 1`, jumping from `d - 1` takes the exact same time as walking 1 final unit without a jump, so using the jump is always optimal). Additionally, Geek should never jump during a backward phase because every position in a backward phase was already visited earlier in that same cycle's forward phase.

#### Approach
1. Iterate over every jump length `j` from `l` to `r`.
2. Compute the target pre-jump position `m = d - j`.
3. Determine the earliest cycle `k` whose forward peak `k * (a - b) + a` is at least `m`:
   - If `m <= a`, then `k = 0`.
   - Otherwise, `k = ceil((m - a) / (a - b)) = (m - a - 1) / (a - b) + 1`.
4. Compute total time for this `j`: `2 * b * k + m + 1` and accumulate modulo $10^9 + 7$.

```cpp
// Intuition: Jumping is always at least as fast as normal walking, and jumping during backward steps is suboptimal. Thus, for each jump j, we only need the earliest forward phase reaching position m = d - j.
// Approach: Loop through all j in [l, r], compute m = d - j, calculate the minimum full cycles k needed before the final forward walk, and sum (2 * b * k + m + 1) modulo 1e9 + 7.
// Time Complexity: O(r - l + 1), which can take up to 10^8 iterations and exceed the time limit for large ranges.
// Space Complexity: O(1), using only constant scalar variables.

class Solution {
  public:
    int minTime(int a, int b, int d, int l, int r) {
        const long long MOD = 1000000007LL;
        long long totalTime = 0;
        long long netGain = a - b; // Net forward distance per complete cycle

        for (int j = l; j <= r; ++j) {
            long long m = d - j; // Position Geek must reach before jumping
            long long k = 0;     // Number of complete cycles before final walk

            if (m > a) {
                // Ceiling division of (m - a) by (a - b)
                k = (m - a + netGain - 1) / netGain;
            }

            // Time = k * (a + b) + (m - k * (a - b)) + 1 = 2 * b * k + m + 1
            long long timeForJ = (2LL * b * k + m + 1) % MOD;
            totalTime = (totalTime + timeForJ) % MOD;
        }

        return static_cast<int>(totalTime);
    }
};

/*
 * Dry Run
 * Input: a = 4, b = 2, d = 8, l = 2, r = 4
 * netGain = 4 - 2 = 2
 *
 * j = 2 -> m = 6 (> 4) -> k = (6 - 4 + 1) / 2 = 1 -> timeForJ = 2*2*1 + 6 + 1 = 11
 * j = 3 -> m = 5 (> 4) -> k = (5 - 4 + 1) / 2 = 1 -> timeForJ = 2*2*1 + 5 + 1 = 10
 * j = 4 -> m = 4 (<= 4) -> k = 0 -> timeForJ = 2*2*0 + 4 + 1 = 5
 *
 * totalTime = (11 + 10 + 5) % 1000000007 = 26
 */
```

---

### 2. Optimized Approach (Prefix Sum + Floor Division Arithmetic)

#### Intuition
As `j` ranges from `l` to `r`, the required pre-jump position `m = d - j` forms a contiguous range `[L, R]` where `L = d - r` and `R = d - l`. The total answer splits cleanly into two closed-form sums:
$$\sum_{m=L}^{R} (2b \cdot k(m) + m + 1) = \sum_{m=L}^{R} (m + 1) + 2b \sum_{m=L}^{R} k(m)$$
The first part is an arithmetic progression, while the second part is the range difference `F(R) - F(L - 1)` of a step-function prefix sum that can be evaluated in $O(1)$ using integer quotient and remainder grouping.

#### Approach
1. Map `j ∈ [l, r]` to `m ∈ [L, R]` with `L = d - r` and `R = d - l`.
2. Compute the linear sum $\sum_{m=L}^{R} (m + 1) = \frac{(R - L + 1)(L + R + 2)}{2} \pmod{10^9 + 7}$.
3. Define `prefixCycles(X)` to compute $\sum_{m=1}^{X} k(m)$ in $O(1)$:
   - For $X \le a$, $k(m) = 0$, so return `0`.
   - For $X > a$, let $M = X - a$ and $D = a - b$. As $u$ goes from $1$ to $M$, $k(a + u) = \lfloor (u - 1) / D \rfloor + 1$.
   - Grouping $M$ into $q = \lfloor M / D \rfloor$ full blocks of size $D$ (with values $1, 2, \dots, q$) and a partial block of size $rem = M \bmod D$ (with value $q + 1$) yields:
     $$F(X) = D \cdot \frac{q(q + 1)}{2} + (q + 1) \cdot rem$$
4. Combine `linearSum` and `2 * b * (prefixCycles(R) - prefixCycles(L - 1))` modulo $10^9 + 7$.

```cpp
// Intuition: Substituting m = d - j converts the query range [l, r] into a contiguous range [L, R] of pre-jump positions. The cycle count k(m) grows as a periodic step function, allowing O(1) prefix summation via quotient-remainder grouping.
// Approach: Compute the arithmetic series sum for (m + 1) over [L, R], evaluate the prefix sum of cycle counts F(R) - F(L - 1) using block decomposition, and combine both terms modulo 1e9 + 7.
// Time Complexity: O(1), as all summations are reduced to closed-form arithmetic formulas.
// Space Complexity: O(1), requiring only constant auxiliary memory.

class Solution {
  private:
    // Computes sum of k(m) for all m in [1, X] in O(1) time
    long long prefixCycles(long long X, long long a, long long b) {
        if (X <= a) return 0; // No complete cycles needed when m <= a

        long long M = X - a;         // Number of positions exceeding initial forward reach 'a'
        long long D = a - b;         // Net forward progress per full cycle
        long long q = M / D;         // Count of complete step blocks of length D
        long long rem = M % D;       // Remaining elements in the final incomplete block

        // Sum of (1 + 2 + ... + q) * D + (q + 1) * rem
        long long fullBlocks = D * (q * (q + 1) / 2);
        long long partialBlock = (q + 1) * rem;

        return fullBlocks + partialBlock;
    }

  public:
    int minTime(int a, int b, int d, int l, int r) {
        const long long MOD = 1000000007LL;

        // Transform jump range [l, r] into pre-jump target range [L, R]
        long long L = static_cast<long long>(d) - r;
        long long R = static_cast<long long>(d) - l;
        long long count = R - L + 1;

        // Part 1: Arithmetic progression sum of (m + 1) from m = L to R
        long long linearSum = (count * (L + R + 2) / 2) % MOD;

        // Part 2: 2 * b * sum of k(m) from m = L to R
        long long cycleSum = (prefixCycles(R, a, b) - prefixCycles(L - 1, a, b)) % MOD;
        if (cycleSum < 0) cycleSum += MOD;

        long long ans = (linearSum + (2LL * b % MOD) * cycleSum % MOD) % MOD;
        return static_cast<int>(ans);
    }
};

/*
 * Dry Run
 * Input: a = 4, b = 2, d = 8, l = 2, r = 4
 *
 * 1. Range transformation:
 *    L = 8 - 4 = 4, R = 8 - 2 = 6, count = 6 - 4 + 1 = 3
 *
 * 2. Linear sum of (m + 1) for m in [4, 6]:
 *    linearSum = (3 * (4 + 6 + 2) / 2) % MOD = (3 * 12 / 2) = 18
 *
 * 3. Prefix cycles:
 *    - prefixCycles(6, 4, 2): M = 2, D = 2 -> q = 1, rem = 0
 *      fullBlocks = 2 * (1 * 2 / 2) = 2, partialBlock = 0 -> returns 2
 *    - prefixCycles(3, 4, 2): 3 <= 4 -> returns 0
 *    - cycleSum = 2 - 0 = 2
 *
 * 4. Final answer:
 *    ans = (18 + (2 * 2) * 2) % MOD = (18 + 8) = 26
 */
```

---

## 🔑 Key Insights

- **Normal Movement Is Never Strictly Better:** Since $j \ge 1$, jumping from position $d - 1$ takes the exact same time (`1s`) as taking the final normal step from $d - 1$ to $d$, and jumping from earlier positions is strictly faster.
- **No Backward-Phase Jumps:** Every position visited while walking backward in cycle $k$ was already visited earlier during cycle $k$'s forward walk, so optimal jumps occur exclusively during forward phases.
- **Cycle-Linear Decoupling:** Rewriting $k(a + b) + (m - k(a - b)) + 1$ as $2b \cdot k(m) + m + 1$ separates the linear progression in $m$ from the periodic step function $k(m)$, turning an $O(10^8)$ loop into pure $O(1)$ arithmetic.
- **Overflow Safety:** Because $d \le 10^8$ and $a \le 10$, intermediate products such as `count * (L + R + 2)` ($\le 2 \times 10^{16}$) and `D * q * (q + 1) / 2` ($\le 5 \times 10^{15}$) fit safely within a 64-bit signed `long long` before applying modulo $10^9 + 7$.

---

## 🚀 Further Exploration

- **Follow-up 1:** What if Geek can use the special jump up to $K$ times instead of once?
- **Follow-up 2:** What if $a$ and $b$ are up to $10^9$ and the jump length $j$ has a cooldown or energy cost proportional to $j$?
- **Related Problems on GeeksforGeeks:**
  - *Minimum steps to destination*
  - *Reach a given score / Jump Game variations*
  - *Sum of floor values $\sum_{i=1}^{N} \lfloor N / i \rfloor$*

---

## 📚 References

- **Original Problem:** [Geek's Destination with Special Jump — GeeksforGeeks](https://www.geeksforgeeks.org/problems/geek-and-her-destination--145724/1)
- **Concepts:** Arithmetic Progressions, Ceiling/Floor Division Identities, Modular Arithmetic

---

## 👨‍💻 Author

- **Nilesh Kumar** — [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Prefix Sum](https://img.shields.io/badge/Prefix_Sum-informational?style=flat-square)
![Number Theory](https://img.shields.io/badge/Number_Theory-informational?style=flat-square)
![Greedy](https://img.shields.io/badge/Greedy-informational?style=flat-square)
![Mathematics](https://img.shields.io/badge/Mathematics-informational?style=flat-square)
![Modular Arithmetic](https://img.shields.io/badge/Modular_Arithmetic-informational?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=flat-square&logo=geeksforgeeks&logoColor=white)