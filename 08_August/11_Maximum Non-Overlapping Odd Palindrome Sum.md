⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/maximum-non-overlapping-odd-palindrome-sum/1).

# 💹 Maximum Non-Overlapping Odd Palindrome Sum

![GFG](https://img.shields.io/badge/GeeksforGeeks-29620A?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-22.29%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

---

## 📝 Problem Statement

Given a string `s` consisting of lowercase English letters, find the maximum possible sum of the lengths of any two **non-empty** and **non-overlapping** palindromic substrings of **odd length**.

Formally, choose any two substrings `s[i...j]` and `s[k...l]` such that $1 \le i \le j < k \le l \le s.size()$, both substrings are palindromes of odd length, and they do not overlap. Return the maximum sum of their lengths.

**Note**: A palindrome is a string that reads the same forward and backward. A substring is a contiguous sequence of characters within the string.

---

## 🧪 Examples

### Example 1:

```
Input: s = "xyabacbcz"
Output: 6
```
**Explanation:** `"aba"` and `"cbc"` are non-overlapping odd-length palindromes. Their lengths are 3 and 3, which gives the sum as 6.

<details>
<summary>📖 Example Breakdown</summary>

Let's analyze the string `s = "xyabacbcz"`:
1.  **Identify Odd-Length Palindromes:**
    * `a` (at index 2)
    * `b` (at index 3)
    * `a` (at index 4)
    * `c` (at index 5)
    * `b` (at index 6)
    * `c` (at index 7)
    * `aba` (centered at index 3, from 2 to 4)
    * `bacab` (not a palindrome)
    * `cbc` (centered at index 6, from 5 to 7)

2.  **Find Non-Overlapping Pairs:**
    * We need to pick two palindromes `s[i...j]` and `s[k...l]` where `j < k`.
    * Pair `("aba", "cbc")`:
        * `"aba"` is `s[2...4]`.
        * `"cbc"` is `s[5...7]`.
        * They are non-overlapping (4 < 5).
        * Their lengths are 3 and 3.
        * Sum = $3 + 3 = 6$.

    * Pair `("a", "cbc")`:
        * `"a"` is `s[2...2]`.
        * `"cbc"` is `s[5...7]`.
        * Non-overlapping.
        * Sum = $1 + 3 = 4$.

3.  **Conclusion:** The maximum possible sum is 6, from the pair `"aba"` and `"cbc"`.

</details>

### Example 2:

```
Input: s = "gfgforgeeks"
Output: 4
```
**Explanation:** `"gfg"` and `"g"` are non-overlapping odd-length palindromes. Their lengths are 3 and 1 which gives the sum as 4.

---

## 📊 Constraints

> `2 ≤ s.size() ≤ 10^5`
> `s` consists of lowercase English letters.

---

## 💡 Solution Approaches

The core idea is to find the optimal split point in the string. For each possible split point `i`, we need to find the longest odd-length palindrome that ends at or before `i` and the longest one that starts at or after `i+1`. To do this efficiently, we can precompute these values.

We use two arrays:
1.  `leftMax[i]`: Stores the length of the longest odd-length palindrome ending at or before index `i`.
2.  `rightMax[i]`: Stores the length of the longest odd-length palindrome starting at or after index `i`.

To quickly check if a substring is a palindrome, we use **Rolling Hashing**. By comparing the hash of a substring with the hash of its corresponding part in the reversed string, we can verify if it's a palindrome in $O(1)$ time after an initial $O(N)$ setup.

### Optimized Approach using Rolling Hash & DP

This approach uses dynamic programming-style prefix and suffix maximum arrays combined with rolling hash and binary search for an efficient solution.

#### C++ Solution
```cpp
// Intuition: The problem asks for the maximum sum of lengths of two non-overlapping odd-length palindromes.
// This can be rephrased as finding a split point 'i' in the string such that the sum of the longest
// odd palindrome ending at or before 'i' and the longest odd palindrome starting at or after 'i+1' is maximized.
// We can precompute these maximum lengths from the left and right to solve this efficiently. Palindrome checks, which
// can be slow, are optimized using Rolling Hashing.

// Approach:
// 1. Create a RollingHash class to compute substring hashes in O(1).
// 2. Generate hashes for the original string (fHash) and its reverse (rHash). This helps verify palindromes in O(1).
// 3. Initialize two arrays, `leftMax[n]` and `rightMax[n]`.
//    - `leftMax[i]` will store the maximum length of an odd palindrome ending in the prefix s[0...i].
//    - `rightMax[i]` will store the maximum length of an odd palindrome starting in the suffix s[i...n-1].
// 4. Populate `leftMax`:
//    - For each character `s[i]` as a potential center, use binary search to find the longest odd palindrome centered at `i`.
//    - Store this palindrome's length at its ending index in a temporary array.
//    - Post-process the array to ensure `leftMax[i]` holds the true maximum for the prefix ending at `i`.
// 5. Populate `rightMax` similarly but for suffixes.
// 6. Iterate through all possible split points `i` from 0 to n-2 and find the maximum value of `leftMax[i] + rightMax[i+1]`.

// Time Complexity: O(N log N), where N is the length of the string.
// The dominant operation is finding the longest palindrome for each of the N centers using binary search, which takes O(log N).
// Hashing takes O(N), and the final pass takes O(N).

// Space Complexity: O(N)
// We use O(N) space for the rolling hash structures and the two DP arrays (`leftMax`, `rightMax`).

class Solution {
public:
  int maxSum(string &s) {
    const int BASE = 911;
    const int MOD = 1e9 + 7;

    // Helper class for Rolling Hash calculation
    class RollingHash {
    private:
      vector<int> hash;
      vector<int> power;
      const int BASE;
      const int MOD;

    public:
      RollingHash(const string &s, int base, int mod)
          : BASE(base), MOD(mod) {
        int n = s.size();
        hash.resize(n + 1);
        power.resize(n + 1);
        hash[0] = 0;
        power[0] = 1;

        // Precompute hashes and powers of the base
        for (int i = 0; i < n; ++i) {
          hash[i + 1] = ((long long)hash[i] * BASE + s[i]) % MOD;
          power[i + 1] = ((long long)power[i] * BASE) % MOD;
        }
      }

      // Get hash of substring s[l...r] in O(1)
      int getHash(int l, int r) const {
        int val = (hash[r + 1] - (long long)hash[l] * power[r - l + 1] % MOD +
                   MOD) %
                  MOD;
        return val;
      }
    };

    // Lambda to check for palindrome using forward and reverse hashes
    auto isPalindrome = [&](int l, int r, RollingHash &fHash,
                              RollingHash &rHash, int n) {
      int h1 = fHash.getHash(l, r); // Hash of s[l...r]
      int h2 = rHash.getHash(n - 1 - r, n - 1 - l); // Hash of reversed s[l...r]
      return h1 == h2;
    };

    int n = s.size();
    // Hash for the original string
    RollingHash fHash(s, BASE, MOD);

    string rev = s;
    reverse(rev.begin(), rev.end());
    // Hash for the reversed string
    RollingHash rHash(rev, BASE, MOD);

    vector<int> leftMax(n, 1), rightMax(n, 1);

    // Calculate `leftMax`: longest odd palindrome ending at or before each index
    for (int i = 0; i < n; ++i) {
      int l = 0, r = min(i, n - 1 - i);
      int best = 1;

      // Binary search for the largest radius `m` for a palindrome centered at `i`
      while (l <= r) {
        int m = (l + r) / 2;
        int start = i - m;
        int end = i + m;
        if (isPalindrome(start, end, fHash, rHash, n)) {
          best = 2 * m + 1; // Update best length found
          l = m + 1;        // Try for a larger radius
        } else {
          r = m - 1;        // Radius is too large
        }
      }

      // Store the palindrome length at its end index
      int endIdx = i + best / 2;
      if (endIdx < n)
        leftMax[endIdx] = max(leftMax[endIdx], best);
    }

    // Post-processing to fill `leftMax` correctly
    // A palindrome of length L ending at i+1 implies a palindrome of length L-2 can end at i
    for (int i = n - 2; i >= 0; i--)
      leftMax[i] = max(leftMax[i], leftMax[i + 1] - 2);
    // Ensure `leftMax[i]` stores the max length in the prefix s[0...i]
    for (int i = 1; i < n; i++)
      leftMax[i] = max(leftMax[i], leftMax[i - 1]);

    // Calculate `rightMax`: longest odd palindrome starting at or after each index
    for (int i = n - 1; i >= 0; --i) {
      int l = 0, r = min(i, n - 1 - i);
      int best = 1;

      // Binary search for the largest palindrome centered at `i`
      while (l <= r) {
        int m = (l + r) / 2;
        int start = i - m;
        int end = i + m;
        if (isPalindrome(start, end, fHash, rHash, n)) {
          best = 2 * m + 1;
          l = m + 1;
        } else {
          r = m - 1;
        }
      }

      // Store the palindrome length at its start index
      int startIdx = i - best / 2;
      if (startIdx >= 0)
        rightMax[startIdx] = max(rightMax[startIdx], best);
    }
    
    // Post-processing for `rightMax`
    for (int i = 1; i < n; i++)
      rightMax[i] = max(rightMax[i], rightMax[i - 1] - 2);
    // Ensure `rightMax[i]` stores the max length in the suffix s[i...n-1]
    for (int i = n - 2; i >= 0; i--)
      rightMax[i] = max(rightMax[i], rightMax[i + 1]);

    // Find the optimal split point
    int ans = 0;
    for (int i = 0; i + 1 < n; ++i) {
      ans = max(ans, leftMax[i] + rightMax[i + 1]);
    }

    return ans;
  }
};

/*
*
* Dry Run
* s = "xyabacbcz", n = 9
*
* 1. Hashing: fHash for "xyabacbcz" and rHash for "zcbacbayx" are created.
*
* 2. leftMax calculation:
* - Center i=3 ('a'): Longest palindrome is "aba" (length 3). It ends at index 4.
* leftMax array (initially all 1s) will have leftMax[4] updated to max(1, 3) = 3.
* - Center i=6 ('b'): Longest palindrome is "cbc" (length 3). It ends at index 7.
* leftMax[7] becomes max(1, 3) = 3.
* - After all centers: leftMax might look like [1, 1, 1, 1, 3, 1, 1, 3, 1] (simplified).
* - Post-processing 1 (from right): leftMax[i] = max(leftMax[i], leftMax[i+1]-2)
* ... leftMax[3] = max(leftMax[3], leftMax[4]-2) = max(1, 3-2) = 1.
* ... leftMax[6] = max(leftMax[6], leftMax[7]-2) = max(1, 3-2) = 1.
* - Post-processing 2 (from left): leftMax[i] = max(leftMax[i], leftMax[i-1])
* leftMax becomes [1, 1, 1, 1, 3, 3, 3, 3, 3].
*
* 3. rightMax calculation:
* - Center i=3 ('a'): "aba" starts at index 2. rightMax[2] becomes max(1, 3) = 3.
* - Center i=6 ('b'): "cbc" starts at index 5. rightMax[5] becomes max(1, 3) = 3.
* - After all centers: rightMax might look like [1, 1, 3, 1, 1, 3, 1, 1, 1].
* - Post-processing (similar logic but reversed):
* rightMax becomes [3, 3, 3, 3, 3, 3, 1, 1, 1].
*
* 4. Final Answer Calculation:
* - Iterate i from 0 to 7. Find max(leftMax[i] + rightMax[i+1]).
* - i=0: leftMax[0] + rightMax[1] = 1 + 3 = 4
* - i=1: leftMax[1] + rightMax[2] = 1 + 3 = 4
* - i=2: leftMax[2] + rightMax[3] = 1 + 3 = 4
* - i=3: leftMax[3] + rightMax[4] = 1 + 3 = 4
* - i=4: leftMax[4] + rightMax[5] = 3 + 3 = 6
* - i=5: leftMax[5] + rightMax[6] = 3 + 1 = 4
* - ...
* - The maximum value found is 6.
*
* Final result: 6
*/
```

#### Java Solution

```java
// Intuition: The problem asks for the maximum sum of lengths of two non-overlapping odd-length palindromes.
// This can be rephrased as finding a split point 'i' in the string such that the sum of the longest
// odd palindrome ending at or before 'i' and the longest odd palindrome starting at or after 'i+1' is maximized.
// We can precompute these maximum lengths from the left and right to solve this efficiently. Palindrome checks, which
// can be slow, are optimized using Rolling Hashing.

// Approach:
// 1. Create a RollingHash class to compute substring hashes in O(1).
// 2. Generate hashes for the original string (fHash) and its reverse (rHash). This helps verify palindromes in O(1).
// 3. Initialize two arrays, `leftMax[n]` and `rightMax[n]`.
//    - `leftMax[i]` will store the maximum length of an odd palindrome ending in the prefix s[0...i].
//    - `rightMax[i]` will store the maximum length of an odd palindrome starting in the suffix s[i...n-1].
// 4. Populate `leftMax`:
//    - For each character `s[i]` as a potential center, use binary search to find the longest odd palindrome centered at `i`.
//    - Store this palindrome's length at its ending index in the `leftMax` array.
//    - Post-process the array to ensure `leftMax[i]` holds the true maximum for the prefix ending at `i`.
// 5. Populate `rightMax` similarly but for suffixes.
// 6. Iterate through all possible split points `i` from 0 to n-2 and find the maximum value of `leftMax[i] + rightMax[i+1]`.

// Time Complexity: O(N log N), where N is the length of the string.
// The dominant operation is finding the longest palindrome for each of the N centers using binary search, which takes O(log N).
// Hashing takes O(N), and the final pass takes O(N).

// Space Complexity: O(N)
// We use O(N) space for the rolling hash structures and the two DP arrays (`leftMax`, `rightMax`).

import java.util.Arrays;

class Solution {
    private static final int BASE = 911;
    private static final int MOD = (int)1e9 + 7;

    // Helper class for Rolling Hash calculation
    private static class RollingHash {
        private long[] hash;
        private long[] power;
        private final int n;

        public RollingHash(String s) {
            n = s.length();
            hash = new long[n + 1];
            power = new long[n + 1];
            hash[0] = 0;
            power[0] = 1;

            // Precompute hashes and powers of the base
            for (int i = 0; i < n; ++i) {
                hash[i + 1] = (hash[i] * BASE + s.charAt(i)) % MOD;
                power[i + 1] = (power[i] * BASE) % MOD;
            }
        }

        // Get hash of substring s[l...r] in O(1)
        public long getHash(int l, int r) {
            long val = (hash[r + 1] - (hash[l] * power[r - l + 1]) % MOD + MOD) % MOD;
            return val;
        }
    }

    // Check for palindrome using forward and reverse hashes
    private boolean isPalindrome(int l, int r, RollingHash fHash, RollingHash rHash, int n) {
        long h1 = fHash.getHash(l, r); // Hash of s[l...r]
        long h2 = rHash.getHash(n - 1 - r, n - 1 - l); // Hash of reversed s[l...r]
        return h1 == h2;
    }

    public int maxSum(String s) {
        int n = s.length();
        // Hash for the original string
        RollingHash fHash = new RollingHash(s);

        String rev = new StringBuilder(s).reverse().toString();
        // Hash for the reversed string
        RollingHash rHash = new RollingHash(rev);

        int[] leftMax = new int[n];
        Arrays.fill(leftMax, 1);
        int[] rightMax = new int[n];
        Arrays.fill(rightMax, 1);

        // Calculate `leftMax`: longest odd palindrome ending at or before each index
        for (int i = 0; i < n; ++i) {
            int l = 0, r = Math.min(i, n - 1 - i);
            int best = 1;

            // Binary search for the largest radius `m` for a palindrome centered at `i`
            while (l <= r) {
                int m = (l + r) / 2;
                int start = i - m;
                int end = i + m;
                if (isPalindrome(start, end, fHash, rHash, n)) {
                    best = 2 * m + 1; // Update best length
                    l = m + 1;        // Try for a larger radius
                } else {
                    r = m - 1;        // Radius too large
                }
            }
            
            // Store the palindrome length at its end index
            int endIdx = i + best / 2;
            if (endIdx < n) {
                leftMax[endIdx] = Math.max(leftMax[endIdx], best);
            }
        }

        // Post-processing to fill `leftMax` correctly
        // A palindrome of length L ending at i+1 implies a palindrome of length L-2 can end at i
        for (int i = n - 2; i >= 0; i--) {
            leftMax[i] = Math.max(leftMax[i], leftMax[i + 1] - 2);
        }
        // Ensure `leftMax[i]` stores the max length in the prefix s[0...i]
        for (int i = 1; i < n; i++) {
            leftMax[i] = Math.max(leftMax[i], leftMax[i - 1]);
        }

        // Calculate `rightMax`: longest odd palindrome starting at or after each index
        for (int i = n - 1; i >= 0; --i) {
            int l = 0, r = Math.min(i, n - 1 - i);
            int best = 1;

            // Binary search for the largest palindrome centered at `i`
            while (l <= r) {
                int m = (l + r) / 2;
                int start = i - m;
                int end = i + m;
                if (isPalindrome(start, end, fHash, rHash, n)) {
                    best = 2 * m + 1;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }

            // Store the palindrome length at its start index
            int startIdx = i - best / 2;
            if (startIdx >= 0) {
                rightMax[startIdx] = Math.max(rightMax[startIdx], best);
            }
        }

        // Post-processing for `rightMax`
        for (int i = 1; i < n; i++) {
            rightMax[i] = Math.max(rightMax[i], rightMax[i - 1] - 2);
        }
        // Ensure `rightMax[i]` stores the max length in the suffix s[i...n-1]
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = Math.max(rightMax[i], rightMax[i + 1]);
        }
        
        // Find the optimal split point
        int ans = 0;
        for (int i = 0; i + 1 < n; ++i) {
            ans = Math.max(ans, leftMax[i] + rightMax[i + 1]);
        }

        return ans;
    }
}

/*
*
* Dry Run
* s = "xyabacbcz", n = 9
*
* 1. Hashing: fHash for "xyabacbcz" and rHash for "zcbacbayx" are created.
*
* 2. leftMax calculation:
* - Center i=3 ('a'): Longest palindrome is "aba" (length 3). It ends at index 4.
* leftMax array (initially all 1s) will have leftMax[4] updated to Math.max(1, 3) = 3.
* - Center i=6 ('b'): Longest palindrome is "cbc" (length 3). It ends at index 7.
* leftMax[7] becomes Math.max(1, 3) = 3.
* - After all centers: leftMax might look like [1, 1, 1, 1, 3, 1, 1, 3, 1] (simplified).
* - Post-processing 1 (from right): leftMax[i] = Math.max(leftMax[i], leftMax[i+1]-2)
* ... leftMax[3] = Math.max(leftMax[3], leftMax[4]-2) = Math.max(1, 3-2) = 1.
* ... leftMax[6] = Math.max(leftMax[6], leftMax[7]-2) = Math.max(1, 3-2) = 1.
* - Post-processing 2 (from left): leftMax[i] = Math.max(leftMax[i], leftMax[i-1])
* leftMax becomes [1, 1, 1, 1, 3, 3, 3, 3, 3].
*
* 3. rightMax calculation:
* - Center i=3 ('a'): "aba" starts at index 2. rightMax[2] becomes Math.max(1, 3) = 3.
* - Center i=6 ('b'): "cbc" starts at index 5. rightMax[5] becomes Math.max(1, 3) = 3.
* - After all centers: rightMax might look like [1, 1, 3, 1, 1, 3, 1, 1, 1].
* - Post-processing (similar logic but reversed):
* rightMax becomes [3, 3, 3, 3, 3, 3, 1, 1, 1].
*
* 4. Final Answer Calculation:
* - Iterate i from 0 to 7. Find Math.max(ans, leftMax[i] + rightMax[i+1]).
* - i=0: leftMax[0] + rightMax[1] = 1 + 3 = 4
* - i=1: leftMax[1] + rightMax[2] = 1 + 3 = 4
* - i=2: leftMax[2] + rightMax[3] = 1 + 3 = 4
* - i=3: leftMax[3] + rightMax[4] = 1 + 3 = 4
* - i=4: leftMax[4] + rightMax[5] = 3 + 3 = 6
* - i=5: leftMax[5] + rightMax[6] = 3 + 1 = 4
* - ...
* - The maximum value found is 6.
*
* Final result: 6
*/
```

---

## 🔑 Key Insights

-   **Rolling Hashing**: This technique is crucial for achieving an efficient solution. It allows for $O(1)$ time complexity for checking if a substring is a palindrome after an initial $O(N)$ preprocessing, avoiding a costly $O(N)$ character-by-character comparison for each check.
-   **Prefix/Suffix Maximums (DP)**: The use of `leftMax` and `rightMax` arrays is a classic dynamic programming pattern. By precomputing the best possible palindromic substring ending (or starting) at each position, we can solve the main problem (finding the best pair) by simply iterating through all possible split points.
-   **Binary Search on Palindrome Length**: For each center, instead of expanding one character at a time (which would be $O(N)$), we can use binary search on the possible palindrome radius. This reduces the search for the longest palindrome from a given center to $O(\log N)$.
-   **Post-processing Trick**: The steps `dp[i] = max(dp[i], dp[i+1]-2)` and `dp[i] = max(dp[i], dp[i-1])` are clever. The first pass propagates the existence of smaller palindromes nested within larger ones. For example, if "abacaba" (length 7) ends at index `i`, then "bacab" (length 5) also exists and can be considered ending at `i-1`. The second pass ensures that `dp[i]` contains the maximum value seen so far in the prefix/suffix, which is what we ultimately need.

---

## 🔗 References

-   [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/maximum-non-overlapping-odd-palindrome-sum/1)
-   [GeeksforGeeks article on Rolling Hash](https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/)

---

## 🧑‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Dynamic Programming](https://img.shields.io/badge/Dynamic_Programming-4a148c?style=for-the-badge)
![String](https://img.shields.io/badge/String-0d47a1?style=for-the-badge)
![Hashing](https://img.shields.io/badge/Hashing-00695c?style=for-the-badge)
![Binary Search](https://img.shields.io/badge/Binary_Search-880e4f?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-29620A?style=for-the-badge)

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**A gentle reminder that this repository is for educational purposes. It's a great resource for learning and understanding different approaches to problem-solving. Happy coding!**