# 🟩 Min Flips for Alternate

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/min-number-of-flips3210/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-48.58%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Given a binary string `s`, you can flip any bit (change `'0'` to `'1'` or `'1'` to `'0'`) to make the string alternating. A string is called **alternating** if no two adjacent characters are the same.

Your task is to find the **minimum number of bit flips** required to make the string alternating.

---

## 💡 Examples

### Example 1
```text
Input: s = "001"
Output: 1
Explanation: Flip the bit at index 0 from 0 to 1 to obtain "101", which is an alternating binary string. Hence, the minimum number of flips required is 1.
```


### Example 2
```text
Input: s = "0001010111"
Output: 2
Explanation: Flip the bit at indices 1 and 8 to obtain "0101010101", which is an alternating binary string. Hence, the minimum number of flips required is 2.
```


<details>
<summary><b>📖 Example Breakdown (Walkthrough for Example 2)</b></summary>

For a binary string of length `n = 10` (`s = "0001010111"`), there are only **two** valid alternating target strings:
1. **Target Pattern A (Starts with `'0'`):** `"0101010101"`
2. **Target Pattern B (Starts with `'1'`):** `"1010101010"`

Let's compare `s` index-by-index against **Target Pattern A**:

| Index (`i`) | `0` | `1` | `2` | `3` | `4` | `5` | `6` | `7` | `8` | `9` |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Input `s[i]`** | `0` | `0` | `0` | `1` | `0` | `1` | `0` | `1` | `1` | `1` |
| **Pattern A (`"0101..."`)** | `0` | `1` | `0` | `1` | `0` | `1` | `0` | `1` | `0` | `1` |
| **Mismatch with A?** | No | **Yes** | No | No | No | No | No | No | **Yes** | No |

- **Flips needed for Pattern A (`flips0`):** `2` (at indices `1` and `8`)
- **Flips needed for Pattern B (`n - flips0`):** `10 - 2 = 8` (every index that matched Pattern A mismatches Pattern B)
- **Minimum Flips:** `min(2, 8) = 2`

</details>

---

## 🔒 Constraints

> - $1 \le \text{s.size()} \le 10^5$
> - `s` consists only of the characters `'0'` and `'1'`
> - **Expected Time Complexity:** $\mathcal{O}(n)$
> - **Expected Auxiliary Space:** $\mathcal{O}(1)$

---

## 🚀 Solution Approach

### Optimal Single-Pass Greedy Approach (Parity Pattern Matching)

#### Intuition & Summary
Any valid alternating binary string of length $n$ can take only two possible forms:
1. Starting with `'0'`: `"010101..."` (even indices are `'0'`, odd indices are `'1'`)
2. Starting with `'1'`: `"101010..."` (even indices are `'1'`, odd indices are `'0'`)

Because these two target strings are exact bitwise complements of each other at every position, any character in `s` that matches `"010101..."` will automatically mismatch `"101010..."`, and vice versa. Thus, if `flips0` is the number of flips needed to convert `s` into `"010101..."`, the flips needed to convert `s` into `"101010..."` is guaranteed to be `n - flips0`. This allows us to find the answer in a single pass with constant extra space.

#### C++ Implementation

```cpp
// Intuition: Any alternating binary string of length n must match either "010101..." or "101010...". Since both patterns are exact bitwise complements, mismatches with one pattern equal matches with the other.
// Approach: Traverse the string once, counting the flips (flips0) needed to match "010101..." using index parity, then return the minimum of flips0 and (n - flips0).
// Time Complexity: O(n), where n is the length of string s, as we iterate through the string once.
// Space Complexity: O(1), since only constant extra variables are used.

class Solution {
  public:
    int minFlips(string &s) {
        int n = s.size(); // Store length of the binary string
        int flips0 = 0; // Flips needed to form "010101..." pattern

        // Traverse each character and compare with expected bit of "010101..."
        for (int i = 0; i < n; i++) {
            // Even indices expect '0' and odd indices expect '1'
            char expected = (i % 2 == 0) ? '0' : '1';
            // Increment flip count if current bit mismatches target pattern
            if (s[i] != expected) {
                flips0++;
            }
        }

        // Flips needed to form "101010..." is simply (n - flips0) due to complementarity
        return min(flips0, n - flips0);
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "001"
 * n = 3, flips0 = 0
 *
 * i = 0: expected = '0', s[0] = '0' -> match, flips0 = 0
 * i = 1: expected = '1', s[1] = '0' -> mismatch, flips0 = 1
 * i = 2: expected = '0', s[2] = '1' -> mismatch, flips0 = 2
 *
 * Pattern "010" requires flips0 = 2 flips
 * Pattern "101" requires n - flips0 = 3 - 2 = 1 flip
 *
 * Result: min(2, 1) = 1
 *
 */
```

---

## 🔑 Key Insights

- **Finite Target Space:** Unlike general string transformation problems, an alternating binary string has strictly **two** possible target configurations regardless of how large $n$ becomes.
- **Complementarity Trick (`n - flips0`):** You do not need two separate loops or two counters. Counting mismatches for `"010101..."` immediately gives the mismatch count for `"101010..."` via `n - flips0`.
- **Zero Extra Memory:** Instead of building candidate strings of length $n$ (which would cost $\mathcal{O}(n)$ space), checking `(i % 2 == 0) ? '0' : '1'` computes the target character on the fly in $\mathcal{O}(1)$ space.

---

## 🔍 Further Exploration

- **Minimum Changes To Make Alternating Binary String** — Identical problem formulation to practice under time constraints.
- **Minimum Number of Swaps to Make the Binary String Alternating** — A variation where you must **swap** adjacent or arbitrary bits instead of flipping them.
- **Flip Bits** — Classic binary string/array problem applying Kadane's algorithm to maximize `'1'`s after a single subarray flip.
- **Minimum Number of K Consecutive Bit Flips** — A harder sliding-window / difference-array variation where flips affect subarrays of length $K$.

---

## 📚 References

- **Original Problem:** [GeeksforGeeks — Min Number of Flips](https://www.geeksforgeeks.org/problems/min-number-of-flips3210/1)
- **Concepts:** Greedy Algorithms, String Parity Matching, Binary String Manipulation

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Strings](https://img.shields.io/badge/Topic-Strings-informational?style=flat-square)
![Binary Representation](https://img.shields.io/badge/Topic-Binary%20Representation-informational?style=flat-square)
![Greedy](https://img.shields.io/badge/Algorithm-Greedy-blueviolet?style=flat-square)
![Goldman Sachs](https://img.shields.io/badge/Company-Goldman%20Sachs-success?style=flat-square)
![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B)

