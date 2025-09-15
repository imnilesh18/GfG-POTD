# 📚 String Stack

![GFG](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-46.69%25-orange?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/string-stack--165812/1).

---

## Problem Statement

You are given two strings `pat` and `tar` consisting of lowercase English characters. You can construct a new string `s` by performing any one of the following operations for each character in `pat`:

1.  **Append** the character `pat[i]` to the string `s`.
2.  **Delete** the **last** character of `s` (if `s` is empty do nothing).

After performing operations on every character of `pat` exactly once, your goal is to determine if it is possible to make the string `s` equal to string `tar`.

---

## Examples

**Example 1:**

```
Input: pat = "geuaek", tar = "geek"
Output: true
Explanation:
Append the first three characters of pat to s, resulting in s = "geu".
Delete the last character for 'a', leaving s = "ge".
Then, append the last two characters 'e' and 'k' from pat to s,
resulting in s = "geek", which matches tar.
```

<details>
<summary>📖 <strong>Example 1 Breakdown</strong></summary>

Let's trace the operations required to form "geek" from "geuaek":

1.  **pat[0] = 'g'**: Append 'g'. `s = "g"`
2.  **pat[1] = 'e'**: Append 'e'. `s = "ge"`
3.  **pat[2] = 'u'**: Append 'u'. `s = "geu"`
4.  **pat[3] = 'a'**: Delete last char. `s = "ge"`
    - (Note: The operation for 'u' (append) and 'a' (pop) effectively cancel each other out. This is the key insight.)
5.  **pat[4] = 'e'**: Append 'e'. `s = "gee"`
6.  **pat[5] = 'k'**: Append 'k'. `s = "geek"`

The final string `s` matches `tar`. Thus, the output is **true**.

</details>

**Example 2:**

```
Input: pat = "agiffghd", tar = "gfg"
Output: true
Explanation:
Skip the first character 'a' in pat.
Append 'g' and 'i' to s, resulting in s = "gi".
Delete the last character for 'f', leaving s = "g".
Append 'f', 'g', and 'h' to s, resulting in s = "gfgh".
Finally, delete the last character for 'd', leaving s = "gfg", which matches tar.
```

**Example 3:**

```
Input: pat = "ufahs", tar = "aus"
Output: false
Explanation: It is impossible to construct the string tar from pat with the given operations.
```

---

## ⌛ Constraints

> 1 ≤ pat.size(), tar.size() ≤ 10^5

---

## Solution Approaches

This problem, while disguised as a stack problem, is actually a **subsequence matching problem with a strict parity constraint.**

The core realization is that every operation must be used exactly once. An "append" operation is either a **match** (if it matches the next character in `tar`) or **junk**. A "pop" operation (which can only happen on a non-empty stack) must cancel a previously appended junk character.

This means all junk characters must come in pairs: one "append" (junk) and one "pop" (which must also be assigned to a junk character's turn).

This creates two critical parity constraints:

1.  **Internal Gaps:** The number of junk characters _between_ any two consecutive matches (say `pat[i]` matching `tar[j]` and `pat[k]` matching `tar[j+1]`) must be **EVEN**. The count is `k - i - 1`. For this gap to be even, `k` and `i` must have **DIFFERENT** parities.
2.  **Final Gap:** The number of junk characters _after_ the final match (say `pat[k_last]` matching `tar[M-1]`) until the end of `pat` (`pat[N-1]`) must also be **EVEN**. The count is `N - 1 - k_last`. For this gap to be even, `N-1` and `k_last` must have the **SAME** parity.

Therefore, we must find `tar` as a subsequence in `pat` such that the indices of the matches **strictly alternate parity** (e.g., EVEN, ODD, EVEN...) AND the final match's parity matches the parity of `N-1`.

### Optimized Approach (Parity DP & Precomputation)

We track two independent paths simultaneously:

1.  The subsequence path that is currently required to end on an **EVEN** index.
2.  The subsequence path that is currently required to end on an **ODD** index.

We precompute two tables (`next_even` and `next_odd`) in O(N) time. `next_even[i][c]` stores the first _even_ index `>= i` where `pat` has character `c`.

When looking for `tar[j]`:

- To find its match for the EVEN-ending path, we look for `next_even` _after_ the last ODD match (`last_o + 1`).
- To find its match for the ODD-ending path, we look for `next_odd` _after_ the last EVEN match (`last_e + 1`).

If, after matching all of `tar`, the `last_e` path is valid AND `(N-1)` is also EVEN, we return true. OR, if the `last_o` path is valid AND `(N-1)` is also ODD, we return true.

<details>
<summary><h3>C++ Solution (Optimized Parity DP)</h3></summary>

```cpp
// Intuition: The problem requires processing each character of 'pat' as either an "append" or a "pop". Any "append" of a junk character (one not matching the 'tar' sequence) must later be cancelled by a "pop" operation, which must also come from a junk character's turn. This implies all junk characters must be able to be paired up.
// Approach:
// 1. This creates a parity constraint. We must find 'tar' as a subsequence within 'pat'.
// 2. Any junk characters *between* two consecutive matches (say pat[i] for tar[j] and pat[k] for tar[j+1]) must be paired. The number of such chars is (k - i - 1). This count must be EVEN. This means k and i must have DIFFERENT parities.
// 3. Junk chars *before* the first match (pat[i_0] for tar[0]) don't matter; their operations can all be "pop" on an empty stack.
// 4. Junk chars *after* the final match (pat[i_last] for tar[M-1]) must also be paired. The count is (N - 1 - i_last). This must be EVEN. This means (N-1) and i_last must have the SAME parity.
// 5. So, we need to find a subsequence matching 'tar' where pat-indices alternate in parity (odd, even, odd, ...) OR (even, odd, even, ...).
// 6. We precompute two 2D arrays: `next_even[i][char]` (first EVEN index >= i with that char) and `next_odd[i][char]` (first ODD index >= i). This takes O(N).
// 7. We then iterate through 'tar' (j=0 to M-1) tracking two states:
//    - `last_even_idx`: The minimum pat-index that matches tar[0...j] ending on an EVEN index.
//    - `last_odd_idx`: The minimum pat-index that matches tar[0...j] ending on an ODD index.
// 8. To find the next match for tar[j] at an EVEN index, it must follow a previous ODD match: `next_even[last_odd_idx + 1]...`.
// 9. To find the next match for tar[j] at an ODD index, it must follow a previous EVEN match: `next_odd[last_even_idx + 1]...`.
// 10. After matching all of 'tar', we check the final condition:
//     - If we found a path ending at `last_even_idx`, we check if its parity matches (N-1)'s parity. (i.e., (N-1)%2 == 0).
//     - If we found a path ending at `last_odd_idx`, we check if its parity matches (N-1)'s parity. (i.e., (N-1)%2 == 1).
//     - If either is true, we return true.
// Time Complexity: O(N + M), where N=pat.size(), M=tar.size(). O(N) to build the 26*N next-char tables, and O(M) to iterate through 'tar' with O(1) table lookups.
// Space Complexity: O(N), for the 26*N (which is O(N)) lookup tables.

class Solution {
  public:
    bool stringStack(string &pat, string &tar) {
        int n = pat.size();
        int m = tar.size();

        // Use 'n' as a marker for "not found" (infinity or max index + 1)
        // next_even[i][c] = first EVEN index k >= i where pat[k] == char(c+'a')
        vector<vector<int>> next_even(n + 1, vector<int>(26, n));
        // next_odd[i][c]  = first ODD  index k >= i where pat[k] == char(c+'a')
        vector<vector<int>> next_odd(n + 1, vector<int>(26, n));

        // Build the next occurrence tables by iterating backward
        // This is a common precomputation technique.
        for (int i = n - 1; i >= 0; i--) {
            for (int c = 0; c < 26; c++) {
                // Copy values from the next position (i+1).
                // This ensures we inherit the next closest occurrence if the char isn't at index i.
                next_even[i][c] = next_even[i + 1][c];
                next_odd[i][c] = next_odd[i + 1][c];
            }

            int char_code = pat[i] - 'a'; // Get the 0-25 code for the character

            if (i % 2 == 0) { // If current index 'i' is Even
                next_even[i][char_code] = i; // This is the closest EVEN occurrence starting from i
            } else { // If current index 'i' is Odd
                next_odd[i][char_code] = i; // This is the closest ODD occurrence starting from i
            }
        }

        // DP state trackers:
        // last_e = min pat-index required to match tar[0...j-1], ending on an EVEN pat-index
        // last_o = min pat-index required to match tar[0...j-1], ending on an ODD  pat-index
        int last_e = -1; // Initialize to -1 (representing "before index 0")
        int last_o = -1;

        // Iterate through each character 'j' of the target string 'tar'
        for (int j = 0; j < m; j++) {
            int c = tar[j] - 'a'; // Get char code for the current target character

            int new_e = n; // Temp var: new best even-ending match index (init to "not found")
            int new_o = n; // Temp var: new best odd-ending match index (init to "not found")

            if (j == 0) {
                // For the first character (tar[0]), we can start at ANY index in 'pat'.
                // Any preceding junk ops are "pop on empty stack", which costs nothing.
                new_e = next_even[0][c]; // Find the very first EVEN occurrence of this char
                new_o = next_odd[0][c];  // Find the very first ODD occurrence of this char
            } else {
                // We MUST maintain parity alternation.

                // To match tar[j] at a NEW EVEN index (new_e):
                // We must have matched tar[j-1] at an ODD index (last_o).
                // We search pat *after* last_o (i.e., starting from last_o + 1).
                if (last_o != n) { // Check if the previous ODD path was valid (not "n")
                    new_e = next_even[last_o + 1][c];
                }

                // To match tar[j] at a NEW ODD index (new_o):
                // We must have matched tar[j-1] at an EVEN index (last_e).
                // We search pat *after* last_e (i.e., starting from last_e + 1).
                if (last_e != n) { // Check if the previous EVEN path was valid
                    new_o = next_odd[last_e + 1][c];
                }
            }

            // Update the states for the next iteration (j+1)
            last_e = new_e;
            last_o = new_o;

            // If both paths (ending-even, ending-odd) become impossible (value 'n'),
            // we cannot match tar[j], so we must fail early.
            if (last_e == n && last_o == n) {
                return false;
            }
        }

        // --- Final Check (After matching all of tar, j == m) ---

        // We must also satisfy the final gap constraint.
        // The remaining operations (from the last match index to the end of pat)
        // must represent an EVEN number of junk characters.
        // Count = (N-1) - last_match_index. This count must be EVEN.
        // This is mathematically equivalent to (N-1) and last_match_index having the SAME parity.

        // Case 1: We found a valid path ending at last_e (which has EVEN parity).
        if (last_e != n) {
            // We need (N-1) to ALSO have EVEN parity for the gap to be even.
            if ((n - 1) % 2 == 0) {
                return true;
            }
        }

        // Case 2: We found a valid path ending at last_o (which has ODD parity).
        if (last_o != n) {
            // We need (N-1) to ALSO have ODD parity for the gap to be even.
            if ((n - 1) % 2 == 1) {
                return true;
            }
        }

        // If neither valid path satisfies the end-gap constraint.
        return false;
    }
};

/*
*
* Dry Run
*
* Input: pat = "geuaek" (N=6), tar = "geek" (M=4)
*
* 1. Build next_even/next_odd tables (simplified relevant parts):
* next_even[0]['g'] = 0
* next_odd[1]['e']  = 1
* next_even[2]['e'] = 4
* next_odd[5]['k']  = 5
* (Other entries exist, e.g., next_odd[0]['g'] = n (6))
*
* 2. Main Loop:
* last_e = -1, last_o = -1
*
* j = 0, tar[0] = 'g':
* (j==0):
* new_e = next_even[0]['g'] = 0
* new_o = next_odd[0]['g']  = 6 (Not Found)
* Update: last_e = 0, last_o = 6
*
* j = 1, tar[1] = 'e':
* (j > 0):
* new_e = next_even[last_o + 1]['e'] = next_even[7]['e'] = 6 (Invalid path)
* new_o = next_odd[last_e + 1]['e']  = next_odd[1]['e']  = 1
* Update: last_e = 6, last_o = 1
* (Path found so far: g (idx 0), e (idx 1). This is Even -> Odd)
*
* j = 2, tar[2] = 'e':
* (j > 0):
* new_e = next_even[last_o + 1]['e'] = next_even[2]['e'] = 4
* new_o = next_odd[last_e + 1]['e']  = next_odd[7]['e']  = 6 (Invalid path)
* Update: last_e = 4, last_o = 6
* (Path found so far: g(0), e(1), e(4). This is Even -> Odd -> Even)
*
* j = 3, tar[3] = 'k':
* (j > 0):
* new_e = next_even[last_o + 1]['k'] = next_even[7]['k'] = 6 (Invalid path)
* new_o = next_odd[last_e + 1]['k']  = next_odd[5]['k']  = 5
* Update: last_e = 6, last_o = 5
* (Path found so far: g(0), e(1), e(4), k(5). This is Even -> Odd -> Even -> Odd)
*
* 3. End of Loop. Final Checks:
* N = 6. (N-1) = 5. Parity of (N-1) is ODD (1).
*
* Check Path 1 (even end):
* last_e = 6 (Invalid path). Skip check.
*
* Check Path 2 (odd end):
* last_o = 5 (Valid path).
* Check last_o parity: 5 % 2 == 1 (ODD).
* Check (N-1) parity: 5 % 2 == 1 (ODD).
* Parities match. (Gap is 5-5 = 0, which is even).
*
* 4. Return: true
*/
```

</details>

---

## 🔑 Key Insights

The problem is a dynamic programming optimization of a subsequence problem. The crucial insight is that the "append/pop" operations are a red herring; the real constraint is that any non-matching "junk" characters (both the appends and the pops that remove them) must be paired up, forcing an **even gap** between consecutive matches.

This transforms the problem into: "Can we find `tar` as a subsequence of `pat` such that the indices of the matching characters strictly alternate parity (EVEN, ODD, EVEN...) AND the parity of the final match index equals the parity of the final index of `pat` (N-1)?"

By precomputing the next available ODD and EVEN index for every character, we can check both required alternating-parity paths (the one starting EVEN and the one starting ODD) in a single O(M) pass over `tar`.

---

## 🚀 Further Exploration

- **Related Problem:** [Longest Common Subsequence (LCS)](https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/)
- **Related Problem:** [Edit Distance](https://www.geeksforgeeks.org/edit-distance-dp-5/)
- **Follow-up Question:** How would the solution change if the "pop" operation could remove _any_ character from `s`, not just the last one?
- **Follow-up Question:** How would the solution change if "pop" operations were free, meaning they didn't consume one of the `pat[i]` character turns?

---

## 📚 References

- [Original GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/string-stack--165812/1)

---

## 🏷️ Tags

![Dynamic Programming](https://img.shields.io/badge/Dynamic%20Programming-blue?style=for-the-badge)
![String](https://img.shields.io/badge/String-gray?style=for-the-badge)
![Parity](https://img.shields.io/badge/Parity-purple?style=for-the-badge)
![Precomputation](https://img.shields.io/badge/Precomputation-orange?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 📜 License

This project is licensed under the MIT License - see the LICENSE file for details.

This repository and its solutions are provided for **educational purposes only**. They are intended for learning, practice, and reference. Please respect the academic integrity policies of any institution or platform you are part of.
