# 🔡 Substrings with K Distinct

<div align="center">

![GfG](https://img.shields.io/badge/GfG-Medium-orange)
![Accuracy](https://img.shields.io/badge/Accuracy-20.46%25-blue)
![Points](https://img.shields.io/badge/Points-4-green)
![License](https://img.shields.io/badge/License-MIT-blue)

</div>

<div align="center">
  <h3>⚠️ Educational Use Only</h3>
  <p>This repository and its content are intended solely for educational purposes.</p>
  <p>Solutions are provided for learning, practice, and reference only.</p>
  <p>Problem statement and test cases are based on the GeeksforGeeks problem.</p>
</div>

---

## 📝 Problem Statement

You are given a string `s` consisting of lowercase characters and an integer `k`. You have to count all possible **substrings** that have **exactly k distinct** characters.

---

## 📊 Examples

```bash
Input: s = "abc", k = 2
Output: 2
Explanation: Possible substrings are ["ab", "bc"]

```

```bash
Input: s = "aba", k = 2
Output: 3
Explanation: Possible substrings are ["ab", "ba", "aba"]

```

```bash
Input: s = "aa", k = 1
Output: 3
Explanation: Possible substrings are ["a", "a", "aa"]

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's take `s = "aba"`, `k = 2`.

1. **Substrings**:
* "a" (1 distinct: 'a')
* "ab" (2 distinct: 'a', 'b') ✅
* "aba" (2 distinct: 'a', 'b') ✅
* "b" (1 distinct: 'b')
* "ba" (2 distinct: 'b', 'a') ✅
* "a" (1 distinct: 'a')


2. **Valid Substrings**: "ab", "aba", "ba".
3. **Count**: 3.

</details>

---

## 🛑 Constraints

* `1 ≤ s.size() ≤ 10^6`
* `1 ≤ k ≤ 26`

---

## 💡 Solution Approaches

We will explore three approaches:

1. **Brute Force**: Generate all substrings and check.
2. **Sliding Window (HashMap)**: Calculate `AtMost(K) - AtMost(K-1)` using a Map.
3. **Sliding Window (Optimized Array)**: Same logic but using a fixed-size array for O(1) space overhead.

### Approach 1: Brute Force

#### 🧠 Intuition

The simplest way is to iterate through every possible substring starting at index `i` and ending at `j`. For each substring, maintain a frequency count of characters to determine the number of distinct characters. If it matches `k`, increment the count. If it exceeds `k`, we can stop expanding for that `i`.

#### 🪜 Approach

1. Iterate `i` from `0` to `n-1` (start of substring).
2. Iterate `j` from `i` to `n-1` (end of substring).
3. Maintain a `freq` array or set to count distinct characters in `s[i...j]`.
4. If distinct count `== k`, increment result.
5. If distinct count `> k`, break inner loop.

#### 🕒 Complexity

* **Time Complexity**:  (Outer loop `N`, inner loop `N`).
* **Space Complexity**:  (Frequency array of size 26).

#### 💻 Code

```cpp
// Intuition: Iterate all substrings, counting distinct chars. Break if > k.
// Approach: Nested loops. Outer loop for start index, inner for end index. Maintain frequency array.
// Time Complexity: O(N^2)
// Space Complexity: O(1) (Fixed size array)

class Solution {
public:
    int countSubstr(string& s, int k) {
        int n = s.length();
        int result = 0;

        for (int i = 0; i < n; i++) {
            vector<int> freq(26, 0);      // Frequency array
            int distinctCnt = 0;          // Distinct count in current window

            for (int j = i; j < n; j++) {
                if (freq[s[j] - 'a'] == 0) {
                    distinctCnt++;        // New character found
                }
                freq[s[j] - 'a']++; 

                if (distinctCnt == k) {
                    result++;             // Valid substring
                } else if (distinctCnt > k) {
                    break;                // Optimization: Stop if distinct > k
                }
            }
        }
        return result;
    }
};

/*
 * Dry Run: s = "abc", k = 2
 * i=0 ('a'): "a"(1), "ab"(2)✅, "abc"(3)❌ -> break
 * i=1 ('b'): "b"(1), "bc"(2)✅
 * i=2 ('c'): "c"(1)
 * Total = 2
 */

```

```java
// Intuition: Iterate all substrings, counting distinct chars. Break if > k.
// Approach: Nested loops. Outer loop for start index, inner for end index. Maintain frequency array.
// Time Complexity: O(N^2)
// Space Complexity: O(1) (Fixed size array)

class Solution {
    int countSubstr(String s, int k) {
        int n = s.length();
        int result = 0;

        for (int i = 0; i < n; i++) {
            int[] freq = new int[26];
            int distinctCnt = 0;

            for (int j = i; j < n; j++) {
                if (freq[s.charAt(j) - 'a'] == 0) {
                    distinctCnt++;
                }
                freq[s.charAt(j) - 'a']++;

                if (distinctCnt == k) {
                    result++;
                } else if (distinctCnt > k) {
                    break;
                }
            }
        }
        return result;
    }
}

```

---

### Approach 2: Sliding Window with HashMap

#### 🧠 Intuition

Calculating **exactly K** distinct characters directly using sliding window is tricky because the window doesn't monotonically expand/shrink based on a single condition.
However, calculating **at most K** distinct characters is standard.
**Key Idea**: `Exactly(K) = AtMost(K) - AtMost(K-1)`.

#### 🪜 Approach

1. Implement a helper function `countAtMostK(s, k)`.
2. Use a sliding window `[i, j]`.
3. Expand `j`, add `s[j]` to map.
4. If map size `> k`, shrink from `i` until map size `≤ k`.
5. All substrings ending at `j` with start index from `i` to `j` are valid (count is `j - i + 1`).
6. Return `countAtMostK(s, k) - countAtMostK(s, k-1)`.

#### 🕒 Complexity

* **Time Complexity**:  (Each character visited at most twice).
* **Space Complexity**:  (Map size limited to 26).

#### 💻 Code

```cpp
// Intuition: Exactly(K) = AtMost(K) - AtMost(K-1).
// Approach: Sliding window to find count of substrings with <= K distinct characters.
// Time Complexity: O(N)
// Space Complexity: O(1) (Map size max 26)

class Solution {
public:
    // Helper to count substrings with at most k distinct characters
    int countAtMostK(string& s, int k) {
        int n = s.length();
        unordered_map<char, int> mp;
        int i = 0, j = 0, result = 0;

        while (j < n) {
            mp[s[j]]++; // Expand window

            while (mp.size() > k) { // Shrink if condition violated
                mp[s[i]]--;
                if (mp[s[i]] == 0) {
                    mp.erase(s[i]);
                }
                i++;
            }
            result += j - i + 1; // Add valid substrings count
            j++;
        }
        return result;
    }

    int countSubstr(string& s, int k) {
        return countAtMostK(s, k) - countAtMostK(s, k - 1);
    }
};

/*
 * Dry Run: s = "abc", k=2
 * AtMost(2): "a", "ab", "b", "bc", "c" -> 5 substrings
 * AtMost(1): "a", "b", "c" -> 3 substrings
 * Result: 5 - 3 = 2 ("ab", "bc")
 */

```

```java
// Intuition: Exactly(K) = AtMost(K) - AtMost(K-1).
// Approach: Sliding window to find count of substrings with <= K distinct characters.
// Time Complexity: O(N)
// Space Complexity: O(1) (Map size max 26)

class Solution {
    int countAtMostK(String s, int k) {
        int n = s.length();
        Map<Character, Integer> map = new HashMap<>();
        int i = 0, j = 0, result = 0;

        while (j < n) {
            map.put(s.charAt(j), map.getOrDefault(s.charAt(j), 0) + 1);

            while (map.size() > k) {
                map.put(s.charAt(i), map.get(s.charAt(i)) - 1);
                if (map.get(s.charAt(i)) == 0) {
                    map.remove(s.charAt(i));
                }
                i++;
            }
            result += j - i + 1;
            j++;
        }
        return result;
    }

    int countSubstr(String s, int k) {
        return countAtMostK(s, k) - countAtMostK(s, k - 1);
    }
}

```

---

### Approach 3: Sliding Window with Array (Optimized)

#### 🧠 Intuition

Maps can have overhead. Since the input contains only lowercase English letters, we can replace the `HashMap` with a fixed integer array of size 26. This improves constant factors in time and space complexity.

#### 🪜 Approach

1. Same logic as Approach 2: `Exactly(K) = AtMost(K) - AtMost(K-1)`.
2. Use `int freq[26]` instead of `unordered_map`.
3. Maintain a variable `distinctCnt` to track non-zero entries in the frequency array.

#### 🕒 Complexity

* **Time Complexity**: .
* **Space Complexity**:  (Strictly 26 integers).

#### 💻 Code

```cpp
// Intuition: Optimize Approach 2 using an array instead of HashMap.
// Approach: Use int[26] to track frequencies and a counter variable for distinct characters.
// Time Complexity: O(N)
// Space Complexity: O(1)

class Solution {
public:
    int countAtMostK(string& s, int k) {
        int n = s.length();
        int mp[26] = { 0 };  // Frequency array
        int i = 0, j = 0;
        int result = 0;
        int distinctCnt = 0; // Track distinct characters manually

        while (j < n) {
            if (mp[s[j] - 'a'] == 0) {
                distinctCnt++; // New distinct char
            }
            mp[s[j] - 'a']++;

            while (distinctCnt > k) {
                mp[s[i] - 'a']--;
                if (mp[s[i] - 'a'] == 0) {
                    distinctCnt--; // Distinct char removed
                }
                i++;
            }
            result += j - i + 1;
            j++;
        }
        return result;
    }

    int countSubstr(string& s, int k) {
        return countAtMostK(s, k) - countAtMostK(s, k - 1);
    }
};

/*
 * Dry Run: s = "aba", k=2
 * AtMost(2): 
 * j=0(a): distinct=1, res+=1 (1)
 * j=1(b): distinct=2, res+=2 (3)
 * j=2(a): distinct=2, res+=3 (6) -> Count = 6 ("a", "ab", "aba", "b", "ba", "a")
 * AtMost(1):
 * j=0(a): distinct=1, res+=1 (1)
 * j=1(b): distinct=2 -> shrink -> i=1, distinct=1, res+=1 (2)
 * j=2(a): distinct=2 -> shrink -> i=2, distinct=1, res+=1 (3) -> Count = 3 ("a", "b", "a")
 * Result: 6 - 3 = 3 ("ab", "aba", "ba")
 */

```

```java
// Intuition: Optimize Approach 2 using an array instead of HashMap.
// Approach: Use int[26] to track frequencies and a counter variable for distinct characters.
// Time Complexity: O(N)
// Space Complexity: O(1)

class Solution {
    int countAtMostK(String s, int k) {
        int n = s.length();
        int[] freq = new int[26];
        int i = 0, j = 0, result = 0;
        int distinctCnt = 0;

        while (j < n) {
            if (freq[s.charAt(j) - 'a'] == 0) {
                distinctCnt++;
            }
            freq[s.charAt(j) - 'a']++;

            while (distinctCnt > k) {
                freq[s.charAt(i) - 'a']--;
                if (freq[s.charAt(i) - 'a'] == 0) {
                    distinctCnt--;
                }
                i++;
            }
            result += j - i + 1;
            j++;
        }
        return result;
    }

    int countSubstr(String s, int k) {
        return countAtMostK(s, k) - countAtMostK(s, k - 1);
    }
}

```

---

## 🗝️ Key Insights

1. **Fixed vs. Variable Window**: Counting exactly `k` is hard because the window validity is strict. Counting `at most k` is flexible (just shrink if `> k`).
2. **Mathematical Trick**: The number of substrings with exactly `k` distinct characters is the number of substrings with `at most k` minus the number of substrings with `at most k-1`.


3. **Array Optimization**: Since characters are 'a'-'z', a frequency array of size 26 is much faster than a Hash Map due to lower overhead and cache locality.

---

## 🚀 Further Exploration

* [Longest Substring with At Most K Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/)
* [Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/)
* [Count Substrings with All Distinct Characters](https://www.google.com/search?q=https://www.geeksforgeeks.org/count-substrings-with-all-distinct-characters/)

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/count-number-of-substrings4528/1)

---

## 👤 Author

* [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

**⚠️ Educational Use Only** This repository is strictly for educational purposes. All solutions are my own implementations intended for learning.
