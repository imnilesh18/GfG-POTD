# 📏 Longest Prefix Suffix

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/longest-prefix-suffix2527/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-27.91%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

---

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the **GeeksforGeeks** problem.

---

### Problem Statement

Given a string `s` of lowercase English alphabets, find the length of the longest proper **prefix** which is also a **suffix**.

**Note:** A proper prefix or suffix is one that is not equal to the entire string. They can be overlapping.

---

### Examples

**Example 1:**
```
Input: s = "abab"
Output: 2
Explanation: The string "ab" is the longest prefix which is also a suffix.
```

**Example 2:**
```
Input: s = "aabcdaabc"
Output: 4
Explanation: The string "aabc" is the longest prefix and suffix.
```

<details>
<summary><b>📖 Example 3 Breakdown</b></summary>

```
Input: s = "aaaa"
Output: 3
```
- **Prefixes:** "a", "aa", "aaa"
- **Suffixes:** "a", "aa", "aaa"
- **Matching:**
  - "a" (length 1) is a match.
  - "aa" (length 2) is a match.
  - "aaa" (length 3) is a match.
- **Longest Match:** The longest proper prefix that is also a suffix is "aaa", with a length of **3**.

</details>

---

### Constraints

> `1 ≤ s.size() ≤ 10^6`
> `s` contains only lowercase English alphabets.

---

### Solution Approaches

#### Optimized Approach: Rolling Hash (Double Hashing)

The core idea is to efficiently check if a prefix of length `k` is identical to the suffix of length `k` without direct character-by-character comparison. We can achieve this using **Rolling Hash**.

We'll calculate the hash of prefixes from left-to-right and hashes of suffixes from right-to-left. If the hash values match, it's highly likely the substrings are identical. To minimize the chance of hash collisions (where different strings produce the same hash), we use a **double hashing** technique with two different prime bases and moduli.

---

#### C++ Solution

```cpp
// Intuition: To find the longest proper prefix that is also a suffix, we can compare hashes of prefixes and suffixes of increasing lengths.
//            Rolling hash allows efficient calculation of these hashes. Using two different hash functions (double hashing) minimizes collisions.
// Approach:
// 1. Initialize two pairs of base and modulus for double hashing (base1/mod1, base2/mod2).
// 2. Iterate from length 1 up to n-1. In each step `i`, we consider prefixes and suffixes of length `i+1`.
// 3. In the loop, calculate the hash of the prefix s[0...i] using powers of the base.
// 4. Simultaneously, calculate the hash of the suffix s[n-i-1...n-1]. Note that the suffix hash is built from right to left.
// 5. If the prefix hashes (hash1) match the suffix hashes (hash2) for both hash functions, it confirms a match.
// 6. We update our answer `ans` with the current length `i+1` whenever a match is found. The loop ensures we find the longest one.
// Time Complexity: O(N), where N is the length of the string. We perform a single pass through the string.
// Space Complexity: O(1), as we only use a constant amount of extra space for variables.

class Solution {
  public:
    int getLPSLength(string &s) {
    
        // Constants for double hashing to reduce collisions
        int base1 = 31, base2 = 37;
        int mod1 = 1e9 + 7, mod2 = 1e9 + 9;
    
        // Powers of the bases, starting with base^0 = 1
        long long p1 = 1, p2 = 1;
        int n = s.size();
    
        // hash1 for prefix, hash2 for suffix. {hash_val_1, hash_val_2}
        vector<long long> hash1(2, 0), hash2(2, 0);
        int ans = 0;
    
        // Iterate up to n-1 because we need a proper prefix/suffix
        for (int i = 0; i < n - 1; i++) {
    
            // Update prefix hashes (calculating hash from left to right)
            // hash = (hash + char * base^i) % mod
            hash1[0] = (hash1[0] + (s[i] - 'a' + 1) * p1) % mod1;
            hash1[1] = (hash1[1] + (s[i] - 'a' + 1) * p2) % mod2;
    
            // Update suffix hashes (calculating hash from right to left)
            // hash = (hash * base + char) % mod
            hash2[0] = (hash2[0] * base1 + (s[n - i - 1] - 'a' + 1)) % mod1;
            hash2[1] = (hash2[1] * base2 + (s[n - i - 1] - 'a' + 1)) % mod2;
    
            // Check if both hash pairs match
            if (hash1 == hash2) {
                ans = i + 1; // Update the answer with the current length
            }
    
            // Update powers for the next iteration
            p1 = (p1 * base1) % mod1;
            p2 = (p2 * base2) % mod2;
        }
    
        return ans;
    }
};

/*
*
* Dry Run
* s = "abab", n = 4
*
* i = 0: (length 1)
* prefix: "a", suffix: "b"
* hash1: [1, 1]
* hash2: [2, 2]
* hash1 != hash2
*
* i = 1: (length 2)
* prefix: "ab", suffix: "ab"
* hash1 (for "ab"): [ (1 + 2*31)%mod1, (1 + 2*37)%mod2 ] -> [63, 75]
* hash2 (for "ab"): [ (2*31 + 1)%mod1, (2*37 + 1)%mod2 ] -> [63, 75]
* hash1 == hash2. ans = 2.
*
* i = 2: (length 3)
* prefix: "aba", suffix: "bab"
* hash1: [...]
* hash2: [...]
* hash1 != hash2
*
* Loop ends. Return ans = 2.
*
*/
```

---

#### Java Solution

```java
// Intuition: Use a rolling hash to efficiently compare prefixes and suffixes. To avoid collisions where
//            different strings might yield the same hash, a double-hashing technique is employed, ensuring robustness.
// Approach:
// 1. Set up two distinct pairs of bases and moduli (base1/mod1, base2/mod2).
// 2. Iterate from the first character to the second-to-last (from i=0 to n-2) to check all proper prefix/suffix lengths.
// 3. In each iteration `i`, update the hash for the prefix of length `i+1`.
// 4. Concurrently, update the hash for the suffix of length `i+1`, calculated from right-to-left.
// 5. Compare the two hash pairs. If both pairs (hash1[0]==hash2[0] and hash1[1]==hash2[1]) are equal, we've found a valid prefix-suffix match.
// 6. Store the length `i+1` of this match. The final value of `ans` will be the longest one found.
// Time Complexity: O(N) because the algorithm iterates through the string once.
// Space Complexity: O(1) since a fixed number of variables are used, regardless of string size.

class Solution {
    public static int getLPSLength(String s) {
        // Constants for the two hash functions
        int base1 = 31, base2 = 37;
        int mod1 = 1000000007, mod2 = 1000000009;

        // Powers of the bases, start at 1 (base^0)
        long p1 = 1, p2 = 1;
        int n = s.length();

        // hash1 for prefix, hash2 for suffix
        long[] hash1 = new long[]{0, 0};
        long[] hash2 = new long[]{0, 0};
        int ans = 0;

        // Loop through all possible proper prefix lengths
        for (int i = 0; i < n - 1; i++) {

            // Update prefix hashes: hash_new = (hash_old + char * power) % mod
            hash1[0] = (hash1[0] + (long)(s.charAt(i) - 'a' + 1) * p1) % mod1;
            hash1[1] = (hash1[1] + (long)(s.charAt(i) - 'a' + 1) * p2) % mod2;

            // Update suffix hashes: hash_new = (hash_old * base + char) % mod
            // We process the suffix character from right-to-left (n-i-1)
            hash2[0] = ((long)hash2[0] * base1 + (s.charAt(n - i - 1) - 'a' + 1)) % mod1;
            hash2[1] = ((long)hash2[1] * base2 + (s.charAt(n - i - 1) - 'a' + 1)) % mod2;
            
            // Check if both hash pairs match
            if (hash1[0] == hash2[0] && hash1[1] == hash2[1]) {
                ans = i + 1; // It's a match, update the longest length found so far
            }

            // Update powers for the next character position
            p1 = (p1 * base1) % mod1;
            p2 = (p2 * base2) % mod2;
        }

        return ans;
    }
}

/*
*
* Dry Run
* s = "aabcdaabc", n = 9
*
* i = 0: prefix "a", suffix "c" -> No match
* i = 1: prefix "aa", suffix "bc" -> No match
* i = 2: prefix "aab", suffix "abc" -> No match
* i = 3: prefix "aabc", suffix "aabc"
* - Prefix hash for "aabc" is calculated.
* - Suffix hash for "aabc" is calculated.
* - hash1 == hash2. Match found! ans is updated to 4.
* ...
* Loop continues. No longer match is found.
*  4
*
*/
```

---

### Key Insights
- **Why Rolling Hash?**: It avoids the O(N²) complexity of naive string comparisons by converting substrings into numerical values (hashes). Calculating the hash for the next substring can be done in O(1) time from the previous one.
- **Double Hashing**: A single hash function has a small but non-zero chance of collision (two different strings producing the same hash). Using two independent hash functions dramatically reduces this probability, making the solution robust enough for a wide range of test cases.
- **Alternative (KMP Algorithm)**: This problem is the classic use case for the preprocessing step of the Knuth-Morris-Pratt (KMP) string searching algorithm. The KMP algorithm builds an `lps` (longest proper prefix which is also suffix) array in O(N) time and O(N) space. The answer to this problem is simply the last value in the `lps` array, i.e., `lps[n-1]`. The hashing solution achieves a better space complexity of O(1).

---

### Further Exploration
- **GeeksforGeeks**: [KMP Algorithm](https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/)
- **GeeksforGeeks**: [Rabin-Karp Algorithm](https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/)
- **LeetCode**: [Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/) (A related problem that can use similar prefix/suffix matching techniques).

---

### References
- **Original Problem**: [Longest Prefix Suffix on GeeksforGeeks](https://www.geeksforgeeks.org/problems/longest-prefix-suffix2527/1)
- **Hashing Concepts**: [String Hashing](https://cp-algorithms.com/string/string-hashing.html)

---

### Author
- **GitHub**: [imnilesh18](https://github.com/imnilesh18)

---

### Tags
<div>
    <span style="display:inline-block; margin:2px;"><img src="https://img.shields.io/badge/String-blue?style=for-the-badge" alt="String"></span>
    <span style="display:inline-block; margin:2px;"><img src="https://img.shields.io/badge/Hashing-green?style=for-the-badge" alt="Hashing"></span>
    <span style="display:inline-block; margin:2px;"><img src="https://img.shields.io/badge/Rabin--Karp-orange?style=for-the-badge" alt="Rabin-Karp"></span>
    <span style="display:inline-block; margin:2px;"><img src="https://img.shields.io/badge/KMP-purple?style=for-the-badge" alt="KMP"></span>
    <span style="display:inline-block; margin:2px;"><img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks"></span>
</div>

---

### License
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

> **Note**: The solutions and explanations are provided for educational purposes only, to help in understanding data structures and algorithms.