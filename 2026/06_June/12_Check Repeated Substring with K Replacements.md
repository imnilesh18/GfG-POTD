<div align="center">

# 🔂 Check Repeated Substring with K Replacements

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/check-if-a-string-is-repetition-of-its-substring-of-k-length3302/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy: 53.15%](https://img.shields.io/badge/Accuracy-53.15%25-green?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

> **⚠️ Educational Use Only**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> The problem statement and test cases are based on the GeeksforGeeks problem.
</div>

---

## 📝 Problem Statement

Given a string `s` and an integer `k`, check if it is possible to convert `s` to a string that is a repetition of a substring with `k` characters. If not, return `false`. 

In order to convert, we can **replace exactly one substring of length `k`** with any `k` characters.

**Note:** In one operation, you can replace any substring of length `k` whose starting index `i` (0-based) satisfies `i % k == 0` with any sequence of `k` characters.

---

## 💡 Examples

### Example 1
```text
Input: s = "abcbedabcabc", k = 3
Output: true
Explanation: Replace "bed" with "abc" so that the whole string becomes a repetition of "abc".
```

### Example 2
```text
Input: s = "bdac", k = 2
Output: true
Explanation: The string can be divided into substrings of length k: ["bd", "ac"]. Since there are exactly two substrings and both are different, we can make them identical by replacing one substring with the other. Hence, the result is true.
```

### Example 3
```text
Input: s = "abcdabcd", k = 2
Output: false
Explanation: Since we are allowed to change only one instance, we cannot convert it properly.
```

<details>
<summary><b>📖 Example Breakdown (Example 1)</b></summary>

1. Given string `s = "abcbedabcabc"` and `k = 3`.
2. Total length `n = 12`. Is it divisible by `k`? Yes (`12 % 3 == 0`).
3. Break the string into chunks of length `k=3`:
   - `s[0:3] = "abc"`
   - `s[3:6] = "bed"`
   - `s[6:9] = "abc"`
   - `s[9:12] = "abc"`
4. Store chunk frequencies:
   - `"abc"` appears `3` times.
   - `"bed"` appears `1` time.
5. Since there are exactly `2` unique chunks, and one of them (`"bed"`) appears exactly `1` time, we can replace `"bed"` with `"abc"`.
6. Result: **True**.
</details>

---

## ⚠️ Constraints

> - `2 ≤ k ≤ s.size() ≤ 10^5`
> - `s` consists of lowercase English letters.
> - Expected Time Complexity: **O(n)**
> - Expected Auxiliary Space: **O(n)**

---

## 🛠️ Solution Approaches

### Optimal Approach (Using Hashing)

The problem asks us to determine if we can make a string a perfect repetition of a `k`-length substring by changing **at most one** `k`-length block. 

By partitioning the string into chunks of size `k`, we can map the frequency of each chunk.
- If the number of unique chunks is greater than `2`, it is impossible to fix with a single replacement.
- If there is only `1` unique chunk, it's already a perfect repetition.
- If there are exactly `2` unique chunks, one of them must appear exactly `1` time so it can be overwritten by the other.

```cpp
// Intuition: We can replace exactly one block of length k. For the string to become a repetition of a single length-k block, all other blocks must already be identical. Thus, we can have at most two unique blocks, and one of them must appear exactly once.
// Approach: 1. Check if string length is divisible by k. 2. Partition string into chunks of size k and store their frequencies in a hash map. 3. If there are more than 2 unique chunks, it's impossible. 4. If there is only 1 unique chunk, it's already a repeating string. 5. If there are exactly 2 unique chunks, one of them must have a frequency of 1 to be replaced by the other.
// Time Complexity: O(n) where n is the length of the string. We iterate over the string once and extract substrings.
// Space Complexity: O(n) to store the substrings and their frequencies in the unordered map.

class Solution {
  public:
    bool kSubstr(string &s, int k) {
        int n = s.length();
        
        // string length must be a multiple of k
        if (n % k != 0) {
            return false;
        }
        
        unordered_map<string, int> freq;
        
        // extract substrings of length k and map their frequencies
        for (int i = 0; i < n; i += k) {
            freq[s.substr(i, k)]++;
        }
        
        // more than 2 unique substrings can't be fixed with 1 replacement
        if (freq.size() > 2) {
            return false;
        }
        
        // already perfect repetition
        if (freq.size() == 1) {
            return true;
        }
        
        // exactly 2 unique substrings exist
        auto it = freq.begin();
        int count1 = it->second;
        it++;
        int count2 = it->second;
        
        // one of the substrings must appear exactly once to be replaced
        return (count1 == 1 || count2 == 1);
    }
};

/*
*
* Dry Run
*
* Input: s = "abcbedabcabc", k = 3
* n = 12, k = 3
* 12 % 3 is 0, valid length check passed
* 
* Loop iterations stepping by k=3:
* i = 0, substring is "abc", map adds "abc", freq["abc"] becomes 1
* i = 3, substring is "bed", map adds "bed", freq["bed"] becomes 1
* i = 6, substring is "abc", map updates "abc", freq["abc"] becomes 2
* i = 9, substring is "abc", map updates "abc", freq["abc"] becomes 3
* 
* Map state:
* "abc" mapped to 3
* "bed" mapped to 1
* 
* Condition checks:
* freq.size() is 2, greater than 2 check is false
* freq.size() is 2, equals 1 check is false
* Iterator extracts counts: count1 is 3, count2 is 1
* Final return evaluates if count1 is 1 or count2 is 1
* Since count2 is 1, return true
* 
* Output: true
*/
```

---

## 🧠 Key Insights
- **Pigeonhole Principle logic:** Since we can only make a single replacement operation, there can be a maximum of one anomalous chunk.
- **Divisibility Check:** An immediate short-circuit optimization; if the total string length isn't a multiple of `k`, the operation is structurally impossible.
- **String Parsing:** Efficiently pulling `k`-length blocks using the standard `.substr(i, k)` function reduces the problem to basic array/map frequency counting.

---

## 🔗 Further Exploration
- String Pattern Matching Algorithms (KMP, Rabin-Karp)
- Fixed Sliding Window Problems
- Problems on Hash Maps & Frequencies

---

## 📚 References
- **GeeksforGeeks Problem:** [Check Repeated Substring with K Replacements](https://www.geeksforgeeks.org/problems/check-if-a-string-is-repetition-of-its-substring-of-k-length3302/1)
- **Related Articles:** Convert String Repetition Substring K Length

---

## 👨‍💻 Author
**GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
![Strings](https://img.shields.io/badge/Strings-blue?style=flat-square) ![Map](https://img.shields.io/badge/Map-orange?style=flat-square) ![Data Structures](https://img.shields.io/badge/Data%20Structures-green?style=flat-square)