# 🔴 Substrings with more 1's than 0's

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/count-the-substring--170645/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-57.87%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License" />
</div>

<br>

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a binary string `s` consisting only of `0`s and `1`s. Calculate the number of substrings that have **more** `1`s than `0`s.

---

## 🚀 Examples

**Example 1:**
```text
Input: s = "011"
Output: 4
Explanation: There are 4 substrings which have more 1s than 0s: "011", "1", "11", and "1".

```

**Example 2:**

```text
Input: s = "0000"
Output: 0
Explanation: There is no substring with more 1s than 0s.

```

All possible substrings:

* "0" (0s: 1, 1s: 0) ❌
* "01" (0s: 1, 1s: 1) ❌
* "011" (0s: 1, 1s: 2) ✅
* "1" (0s: 0, 1s: 1) ✅
* "11" (0s: 0, 1s: 2) ✅
* "1" (0s: 0, 1s: 1) ✅

Total valid substrings = 4.

---

## ⚠️ Constraints

* $1 \le |s| \le 6 \times 10^4$

---

## 💡 Solution Approach

### Optimized Approach (Prefix Balance & Frequency Array)

**Intuition:**
We need to find substrings where the count of `1`s is strictly greater than the count of `0`s. By treating `1` as `+1` and `0` as `-1`, a valid substring will have a sum greater than `0`. Instead of checking every substring in $O(N^2)$, we can maintain a running prefix sum (balance). We calculate how many substrings starting at index `i` are *invalid* (balance $\le 0$), and subtract this from the total possible substrings starting at `i`. As we shift the starting index, we mathematically adjust our "base zero" and our invalid count in $O(1)$ time.

```cpp
// Intuition: Treat '1' as +1 and '0' as -1. A valid substring has a sum > 0. We can count invalid substrings starting from each index and subtract them from total possible substrings. Shifting the start index updates the balance and invalid count in O(1).
// Approach: 
// 1. Maintain a prefix balance where '1' adds 1 and '0' subtracts 1. Offset the array by `n` to avoid negative indices.
// 2. Do a first pass to find the initial number of invalid prefixes (balance <= zero) and populate the frequency map.
// 3. Iterate through the string, treating each index as a starting point. Valid substrings = total starting at `i` minus invalid ones.
// 4. Update the `zero` offset and the `minus` (invalid count) based on whether the outgoing character was '1' or '0'.
// Time Complexity: O(N) where N is the length of the string, as we do two linear passes.
// Space Complexity: O(N) to store the prefix frequency array of size 2*N + 1.

class Solution {
  public:
    int countSubstring(string s) {
        int n = s.size(); 
        int ans = 0;
    
        // "zero" acts as the base index to avoid negative arrays
        int zero = n;
        
        // Tracks count of invalid prefix states (0s >= 1s)
        int minus = 0;
    
        // Frequency array for prefix balances
        vector<int> mp(2 * n + 1, 0);
        int cur = zero;
    
        // Step 1: Build prefix balance frequencies
        for (auto i : s) {
            if (i == '0') cur--; // '0' is -1
            else cur++;          // '1' is +1
    
            // If current balance <= base, substring is invalid
            if (cur <= zero) {
                minus++;
            }
            mp[cur]++;
        }
    
        // Step 2: Count valid substrings by shifting the start window
        for (int i = 0; i < n; i++) { 
            // Valid substrings = total from i - invalid substrings
            ans += (n - i - minus);
    
            // Case 1: Outgoing character is '1'
            if (s[i] == '1') {
                mp[zero + 1]--; // Remove old prefix balance
                zero++;         // Shift base balance up
                minus += mp[zero]; // Update invalid count
            }
            // Case 2: Outgoing character is '0'
            else {
                mp[zero - 1]--; // Remove old prefix balance
                zero--;         // Shift base balance down
                minus--;        // Current invalid state removed
                minus -= mp[zero + 1]; // These are now valid, remove from invalid count
            }
        }
    
        return ans;
    }
};

/*
*
* Dry Run
* Input: s = "011"
* Initialization: n = 3, zero = 3, minus = 0, mp size = 7, cur = 3
*
* Pass 1 (Building balances):
* char '0': cur = 2. cur <= zero (2 <= 3). minus = 1. mp[2] = 1
* char '1': cur = 3. cur <= zero (3 <= 3). minus = 2. mp[3] = 1
* char '1': cur = 4. cur > zero (4 > 3). mp[4] = 1
*
* Pass 2 (Calculating ans):
* i = 0 ('0'):
* ans += (3 - 0 - 2) => ans = 1
* Update for '0': mp[2]-- => 0, zero-- => 2, minus-- => 1, minus -= mp[3] (1) => minus = 0
*
* i = 1 ('1'):
* ans += (3 - 1 - 0) => ans = 3
* Update for '1': mp[3]-- => 0, zero++ => 3, minus += mp[3] (0) => minus = 0
*
* i = 2 ('1'):
* ans += (3 - 2 - 0) => ans = 4
* Update for '1': mp[4]-- => 0, zero++ => 4, minus += mp[4] (0) => minus = 0
*
* Output: 4
*
*/

```

---

## 🔍 Key Insights

* **Mathematical Substitution:** By converting the string into a sequence of `+1`s and `-1`s, the problem turns into finding subarrays with a positive sum.
* **Reverse Counting:** Counting total possible subarrays and subtracting the *invalid* ones is much easier to maintain dynamically.
* **Base Shifting ($O(1)$ updates):** As we shrink the window from the left (incrementing `i`), we simulate the subtraction of `s[i]` from all subsequent prefix sums by simply shifting our `zero` reference axis. This avoids an $O(N)$ recalculation.

---

## 🔗 Further Exploration

* [Count subarrays with equal number of 1s and 0s](https://www.geeksforgeeks.org/count-subarrays-equal-number-1s-0s/)
* [Longest subarray with more 1s than 0s](https://www.google.com/search?q=https://www.geeksforgeeks.org/longest-subarray-with-more-ones-than-zeros/)

---

## 📚 References

* **Original Problem:** [Substrings with more 1's than 0's on GeeksforGeeks](https://www.geeksforgeeks.org/problems/count-the-substring--170645/1)

---

## 👨‍💻 Author

**Nilesh**

* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#strings` `#dynamic-programming` `#data-structures` `#algorithms` `#prefix-sum` `#geeksforgeeks`
