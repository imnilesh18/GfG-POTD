# 🟧 Range Vowel Count Queries

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/range-vowel-count-queries-static/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/range-vowel-count-queries-static/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-79.97%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/range-vowel-count-queries-static/1)
[![Points](https://img.shields.io/badge/Points-4-brightgreen?style=for-the-badge)](https://www.geeksforgeeks.org/problems/range-vowel-count-queries-static/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:** This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Given a string `s` and a 2D array `queries[][]`, where each query consists of two integers `l` and `r`, find the number of vowels in the substring `s[l...r]` for each query. The substring includes both indices `l` and `r`.

Return an array containing the answers to all queries in the order they are given.

- **Expected Time Complexity:** $\mathcal{O}(n)$
- **Expected Auxiliary Space:** $\mathcal{O}(n)$

---

## 🧪 Examples

### Example 1
```text
Input: s = "geeksforgeeks", queries[][] = [[1, 3], [2, 4], [1, 9]]
Output: [2, 1, 4]
Explanation:
Query 1: "eek" has 2 vowels (e, e).
Query 2: "eks" has 1 vowel (e).
Query 3: "eeksforge" has 4 vowels (e, e, o, e).
```

### Example 2
```text
Input: s = "helloworld", queries[][] = [[0, 4], [5, 9], [0, 9]]
Output: [2, 1, 3]
Explanation:
Query 1: "hello" has 2 vowels (e, o).
Query 2: "world" has 1 vowel (o).
Query 3: "helloworld" has 3 vowels (e, o, o).
```

<details>
<summary><b>📖 Example Breakdown (Example 1 Walkthrough)</b></summary>

Let `s = "geeksforgeeks"` (length $n = 13$). First, we map each character to `1` if it is a vowel (`a, e, i, o, u`) and `0` otherwise, then compute a 1-indexed `prefix` sum array:

| Index (`i`) | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Character** | `g` | `e` | `e` | `k` | `s` | `f` | `o` | `r` | `g` | `e` | `e` | `k` | `s` |
| **Is Vowel?** | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 1 | 1 | 0 | 0 |
| **`prefix[i + 1]`** | 0 | 1 | 2 | 2 | 2 | 2 | 3 | 3 | 3 | 4 | 5 | 5 | 5 |

*(with `prefix[0] = 0`)*

Now each range query `[l, r]` is answered using `prefix[r + 1] - prefix[l]`:
- **Query `[1, 3]`** (`"eek"`): `prefix[4] - prefix[1] = 2 - 0 = 2`
- **Query `[2, 4]`** (`"eks"`): `prefix[5] - prefix[2] = 2 - 1 = 1`
- **Query `[1, 9]`** (`"eeksforge"`): `prefix[10] - prefix[1] = 4 - 0 = 4`

Final Result: `[2, 1, 4]`

</details>

---

## 🔒 Constraints

> - $1 \le \text{s.size()}, \text{queries.size()} \le 10^5$
> - `s` consists only of lowercase English alphabets
> - $\text{queries}[i].\text{size()} = 2$
> - $0 \le \text{queries}[i][0] \le \text{queries}[i][1] < \text{s.size()}$

---

## 💡 Solution Approaches

### 1️⃣ Brute Force Approach (Iterative Substring Scan)

For every query `[l, r]`, iterate directly through the substring from index `l` to `r` and increment a counter whenever a vowel is encountered. While simple and requiring no extra auxiliary space, repeatedly scanning overlapping ranges leads to Time Limit Exceeded (TLE) on large inputs ($n, q \le 10^5$).

```cpp
// Intuition: Count vowels directly by scanning from index l to r for every query.
// Approach: Loop through each query [l, r], iterate over s[l...r], increment a counter for each vowel, and store the count.
// Time Complexity: O(q * n), where q is the number of queries and n is the string length (each query can scan up to n characters).
// Space Complexity: O(1) auxiliary space (excluding the output array).

class Solution {
  public:
    vector<int> countVowels(string &s, vector<vector<int>> &queries) {
        vector<int> ans;
        ans.reserve(queries.size());

        // Helper lambda to check if a lowercase character is a vowel
        auto isVowel = [](char c) {
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };

        // Process each query independently
        for (const auto &q : queries) {
            int l = q[0];
            int r = q[1];
            int count = 0;

            // Scan substring s[l...r] to count vowels
            for (int i = l; i <= r; i++) {
                if (isVowel(s[i])) {
                    count++;
                }
            }

            ans.push_back(count);
        }

        return ans;
    }
};

/*
 * Dry Run
 *
 * Input: s = "helloworld", queries = [[0, 4], [5, 9], [0, 9]]
 *
 * Query 1: [0, 4] -> scans "hello" -> vowels at index 1 ('e'), 4 ('o') -> count = 2
 * Query 2: [5, 9] -> scans "world" -> vowel at index 6 ('o') -> count = 1
 * Query 3: [0, 9] -> scans "helloworld" -> vowels at 1, 4, 6 -> count = 3
 *
 * Output: [2, 1, 3]
 */
```

---

### 2️⃣ Optimized Approach (Prefix Sum Array)

Since the string `s` is static (no character updates occur between queries), we can precompute a 1-indexed `prefix` array where `prefix[i]` stores the total number of vowels in the prefix `s[0...i-1]`. Any range query `[l, r]` can then be answered in $\mathcal{O}(1)$ time via `prefix[r + 1] - prefix[l]`.

```cpp
// Intuition: Since the string is immutable, precomputing cumulative vowel counts allows answering any range query in O(1) time.
// Approach: Build a 1-indexed prefix sum array of vowel counts over s, then compute prefix[r + 1] - prefix[l] for each query [l, r].
// Time Complexity: O(n + q), where n is the length of s to build the prefix array and q is the number of queries answered in O(1) each.
// Space Complexity: O(n) auxiliary space to store the prefix sum array of size n + 1.

class Solution {
  public:
    vector<int> countVowels(string &s, vector<vector<int>> &queries) {
        int n = s.size();
        // prefix[i] stores total vowels in substring s[0 ... i-1]
        vector<int> prefix(n + 1, 0);

        // Helper lambda to check if a lowercase character is a vowel
        auto isVowel = [](char c) {
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };

        // Build the prefix sum array of vowel counts
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + (isVowel(s[i]) ? 1 : 0);
        }

        vector<int> ans;
        ans.reserve(queries.size());

        // Answer each [l, r] query in O(1) time
        for (const auto &q : queries) {
            int l = q[0];
            int r = q[1];
            ans.push_back(prefix[r + 1] - prefix[l]);
        }

        return ans;
    }
};

/*
 * Dry Run
 *
 * Input: s = "geeksforgeeks", queries = [[1, 3], [2, 4], [1, 9]]
 *
 * Step 1: Build prefix array (1-indexed vowel counts)
 * Index:   0  1  2  3  4  5  6  7  8  9 10 11 12
 * Char:    g  e  e  k  s  f  o  r  g  e  e  k  s
 * Vowel:   0  1  1  0  0  0  1  0  0  1  1  0  0
 * prefix: [0, 0, 1, 2, 2, 2, 2, 3, 3, 3, 4, 5, 5, 5]
 *
 * Step 2: Answer queries using prefix[r + 1] - prefix[l]
 * Query [1, 3] ("eek")       -> prefix[4] - prefix[1] = 2 - 0 = 2
 * Query [2, 4] ("eks")       -> prefix[5] - prefix[2] = 2 - 1 = 1
 * Query [1, 9] ("eeksforge") -> prefix[10] - prefix[1] = 4 - 0 = 4
 *
 * Output: [2, 1, 4]
 */
```

---

### 📊 Complexity Comparison

| Approach | Time Complexity | Auxiliary Space | Status |
| :--- | :---: | :---: | :---: |
| **Brute Force** | $\mathcal{O}(q \cdot n)$ | $\mathcal{O}(1)$ | ⚠️ TLE on large constraints |
| **Prefix Sum (Optimal)** | $\mathcal{O}(n + q)$ | $\mathcal{O}(n)$ | ✅ Optimal & Accepted |

---

## 🔑 Key Insights

- **Static Range Queries = Prefix Sums:** Whenever multiple range sum/count queries are performed on an unchanging array or string, converting elements into binary indicators (`1` for vowel, `0` for consonant) and building a prefix sum reduces per-query work from $\mathcal{O}(n)$ to $\mathcal{O}(1)$.
- **1-Based Padding Eliminates Edge Cases:** Initializing `prefix` with size `n + 1` (`prefix[0] = 0`) avoids conditional checks like `l == 0 ? prefix[r] : prefix[r] - prefix[l - 1]`, keeping the query formula uniform (`prefix[r + 1] - prefix[l]`).
- **Memory Pre-allocation:** Calling `ans.reserve(queries.size())` prevents dynamic vector reallocations while collecting query results.

---

## 🚀 Further Exploration

- **Related Problems:**
  - [Range Sum Query - Immutable](https://www.geeksforgeeks.org/problems/range-sum-queries2353/1) — Classic 1D prefix sum application.
  - [Equilibrium Point](https://www.geeksforgeeks.org/problems/equilibrium-point-1587115620/1) — Using prefix and suffix sums to find balanced indices.
  - [Subarray Sum Equals K](https://www.geeksforgeeks.org/problems/subarrays-with-sum-k/1) — Combining prefix sums with hash maps.
- **Follow-up Question:**
  - *What if the problem also allowed point update queries (changing `s[idx] = ch`)?* A static prefix sum would require $\mathcal{O}(n)$ per update; instead, a **Fenwick Tree (Binary Indexed Tree)** or **Segment Tree** would support both updates and vowel range queries in $\mathcal{O}(\log n)$ time.

---

## 📚 References

- **Original Problem:** [Range Vowel Count Queries — GeeksforGeeks](https://www.geeksforgeeks.org/problems/range-vowel-count-queries-static/1)
- **Concept Guide:** [Prefix Sum Array — Implementation and Applications (GeeksforGeeks)](https://www.geeksforgeeks.org/prefix-sum-array-implementation-applications-competitive-programming/)

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Prefix Sum](https://img.shields.io/badge/Topic-Prefix%20Sum-blue?style=flat-square)
![Strings](https://img.shields.io/badge/Topic-Strings-teal?style=flat-square)
![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)
![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-298D46?style=flat-square&logo=geeksforgeeks&logoColor=white)
