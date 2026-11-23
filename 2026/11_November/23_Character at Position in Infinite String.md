# 🟧 Character at Position in Infinite String

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/the-infinite-string1049/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/the-infinite-string1049/1)
[![Accuracy: 46.98%](https://img.shields.io/badge/Accuracy-46.98%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/the-infinite-string1049/1)
[![Points: 4](https://img.shields.io/badge/Points-4-purple?style=for-the-badge)](https://www.geeksforgeeks.org/problems/the-infinite-string1049/1)
[![Company: National Instruments](https://img.shields.io/badge/Company-National%20Instruments-teal?style=for-the-badge)](https://www.geeksforgeeks.org/problems/the-infinite-string1049/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

> ⚠️ **Educational Use Only:**  
> This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Given a string `s` and an integer `pos`, an infinite string is constructed by repeatedly applying the following operation. In the $i$-th step ($i = 1, 2, 3, \dots$), append $i$ consecutive `'$'` characters, followed by the reverse of the current string, to the current string.

Formally, if the current string is `s`, update it as:

```text
s = s + ('$' repeated i times) + reverse(s)
```

The initial string is the given `s`, and the process continues indefinitely.

Find and return the character at the **`pos`** (**1-based indexing**) in the resulting infinite string.

<div align="center">

```text
Step i String Structure (Length L_i = 2 * L_{i-1} + i):

+------------------------+-------------------+------------------------+
|       S_{i-1}          |   '$' * i times   |    reverse(S_{i-1})    |
+------------------------+-------------------+------------------------+
1                    prevLen               prevLen + i               L_i
   (p stays unchanged)       (return '$')      (p mirrors to L_i - p + 1)
```

</div>

---

## 🧪 Examples

### Example 1
```text
Input:  s = "12345", pos = 3
Output: 3
Explanation: In "12345...", the character at pos 3 (1-based) is '3'.
```

### Example 2
```text
Input:  s = "12345", pos = 10
Output: 2
Explanation: After step 1, the string begins with "12345$54321...". The 10th character is '2'.
```

### Example 3
```text
Input:  s = "abc", pos = 7
Output: a
Explanation: After step 1, the string begins with "abc$cba...". The 7th character is 'a'.
```

<details>
<summary><b>📖 Example Breakdown (Step-by-Step Walkthrough)</b></summary>
<br>

Let's trace **Example 2**: `s = "12345"`, `pos = 10`

1. **Initial State ($i = 0$):**
   - $S_0 = \text{"12345"}$, $\text{len} = 5$
   - Since $\text{len} (5) < \text{pos} (10)$, we expand to Step 1.

2. **Forward Expansion ($i = 1$):**
   - $S_1 = \text{"12345"} + \text{"\$"} + \text{"54321"} = \text{"12345\$54321"}$
   - $\text{len} = 2 \times 5 + 1 = 11$
   - Now $\text{len} (11) \ge \text{pos} (10)$, so we stop expanding at `step = 1`.

3. **Backward Folding (`step = 1` $\rightarrow$ `step = 0`):**
   - Length before step 1: $\text{prevLen} = \frac{11 - 1}{2} = 5$
   - Partition ranges for $S_1$:
     - First half ($S_0$): indices `1` to `5`
     - Middle `'$'` block: index `6` to `6`
     - Reversed second half ($\text{reverse}(S_0)$): indices `7` to `11`
   - Our target `p = 10` lies in the reversed second half (`7..11`).
   - Mirror `p` back to $S_0$:
     $$p = \text{len} - p + 1 = 11 - 10 + 1 = 2$$
   - Update `len = 5` and `step = 0`.

4. **Base String Lookup:**
   - Loop terminates (`step == 0`).
   - Return `s[p - 1] = s[2 - 1] = s[1] = '2'`.

</details>

---

## 🔒 Constraints & Expected Complexities

> **Constraints:**
> - $1 \le \text{s.size()} \le 10^5$
> - $1 \le \text{pos} \le 10^9$
> - `s` consists of English alphabets and digits

- **Expected Time Complexity:** $\mathcal{O}(\log(\text{pos}))$
- **Expected Auxiliary Space:** $\mathcal{O}(1)$

---

## 💡 Solution Approaches

### 1. Brute-Force Simulation (Conceptual Overview)
- **Intuition:** Repeatedly build the string using $S_i = S_{i-1} + \text{string}(i, \text{'\$'}) + \text{reverse}(S_{i-1})$ until its length reaches at least `pos`, then return `S[pos - 1]`.
- **Why It Fails:** Because `pos` can be as large as $10^9$, constructing the string explicitly requires $\mathcal{O}(\text{pos})$ time and $\mathcal{O}(\text{pos})$ memory, resulting in **Time Limit Exceeded (TLE)** and **Memory Limit Exceeded (MLE)**.

---

### 2. Mathematical Length Growth & Reverse Folding (Optimized)
- **Intuition:** Instead of constructing the string, notice that each step doubles the previous string length plus $i$ separator characters ($L_i = 2 \cdot L_{i-1} + i$). Because the length grows exponentially, we can find the minimum step covering `pos` in logarithmic iterations and fold `pos` backward using symmetry until it lands inside the original string `s`.
- **Approach:**
  1. Start with `len = s.size()` and `step = 0`. Increment `step` and update `len = 2 * len + step` until `len >= pos`.
  2. While `step > 0`, compute the previous string length `prevLen = (len - step) / 2`.
  3. Check which of the three segments `p` falls into:
     - **Left half (`p <= prevLen`):** `p` lies in $S_{\text{step}-1}$, so `p` stays unchanged.
     - **Middle block (`p <= prevLen + step`):** `p` lies in the `'$'` block, so immediately return `'$'`.
     - **Right half (`p > prevLen + step`):** `p` lies in $\text{reverse}(S_{\text{step}-1})$, so mirror it back using `p = len - p + 1`.
  4. Update `len = prevLen`, decrement `step`, and repeat until `step == 0`, then return `s[p - 1]`.

#### C++ Implementation

```cpp
// Intuition: The string length doubles at every step (len = 2 * len + step), so we can avoid building the string and fold 'pos' backward using mirror symmetry until it maps into the base string 's'.
// Approach: First, simulate only the length growth until len >= pos. Then, work backward step-by-step: keep 'p' if it is in the left half, return '$' if it is in the middle separator block, or mirror 'p' (len - p + 1) if it is in the reversed right half.
// Time Complexity: O(log(pos)) - String length grows exponentially (at least doubling each step), taking at most ~30 iterations for pos <= 10^9.
// Space Complexity: O(1) - Only a few scalar variables are used without allocating extra strings.

class Solution {
  public:
    char posInfinite(string &s, int pos) {
        long long n = s.size();
        long long p = pos;
        
        // Step 1: Grow string length until it covers position p
        long long len = n;
        long long step = 0;
        while (len < p) {
            step++;
            len = 2 * len + step; // Length after appending 'step' '$'s and reverse(S)
        }
        
        // Step 2: Fold position p backward step-by-step
        while (step > 0) {
            long long prevLen = (len - step) / 2; // Length of string before current step
            
            if (p <= prevLen) {
                // Lies in the first half (S_{step-1}): p remains unchanged
            } else if (p <= prevLen + step) {
                // Lies in the middle '$' block
                return '$';
            } else {
                // Lies in the reversed second half: mirror back to S_{step-1}
                p = len - p + 1;
            }
            
            len = prevLen; // Shrink length to previous state
            step--;
        }
        
        // Map 1-based position back to 0-based index in initial string s
        return s[p - 1];
    }
};

/*
*
* Dry Run
*
* Input: s = "12345", pos = 10
* Initial: n = 5, p = 10, len = 5, step = 0
*
* Step 1 (Forward length growth):
* len (5) < p (10) -> step = 1, len = 2 * 5 + 1 = 11
* Loop stops since len (11) >= p (10)
*
* Step 2 (Backward folding):
* Iteration 1 (step = 1, len = 11, p = 10):
* prevLen = (11 - 1) / 2 = 5
* p <= 5 is false, p <= 5 + 1 (6) is false
* Else branch (reversed half): p = 11 - 10 + 1 = 2
* len = 5, step = 0
*
* Loop ends (step == 0)
* Return s[p - 1] = s[2 - 1] = s[1] = '2'
*
* Output: '2'
*
*/
```

---

## 🔑 Key Insights

- **Exponential Growth:** Since $L_i = 2L_{i-1} + i > 2^i \cdot L_0$, even for the maximum constraint $\text{pos} = 10^9$ and $L_0 = 1$, `step` never exceeds $30$.
- **Mirror Symmetry Mapping:** In a string of total length $L_i$ whose suffix of length $L_{i-1}$ is the reverse of its prefix of length $L_{i-1}$, the $p$-th character from the start (for $p > L_{i-1} + i$) corresponds symmetrically to the $(L_i - p + 1)$-th character from the start.
- **Overflow Prevention:** Using `long long` for `len`, `p`, and `prevLen` prevents 32-bit signed integer overflow when `len` exceeds `pos` up to $2 \times 10^9$.

---

## 🚀 Further Exploration

- [Find Kth Bit in Nth Binary String (LeetCode 1545)](https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/) — Uses the exact same recursive length-doubling and reverse-mirroring pattern.
- [K-th Symbol in Grammar (LeetCode 779)](https://leetcode.com/problems/k-th-symbol-in-grammar/) — Another logarithmic recursive index reduction problem.
- [Decoded String at Index (LeetCode 880)](https://leetcode.com/problems/decoded-string-at-index/) — Finding the $K$-th character in an exponentially expanding string without materializing it.

---

## 📚 References

- **Original Problem:** [GeeksforGeeks - Character at Position in Infinite String](https://www.geeksforgeeks.org/problems/the-infinite-string1049/1)
- **Core Concepts:** Recursion, Divide & Conquer Symmetry, Logarithmic Search Reduction

---

## 👨‍💻 Author

- **GitHub:** [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Mathematics](https://img.shields.io/badge/Topic-Mathematics-blue?style=flat-square)
![Strings](https://img.shields.io/badge/Topic-Strings-green?style=flat-square)
![Recursion](https://img.shields.io/badge/Topic-Recursion-orange?style=flat-square)
![National Instruments](https://img.shields.io/badge/Company-National%20Instruments-purple?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-298D46?style=flat-square)