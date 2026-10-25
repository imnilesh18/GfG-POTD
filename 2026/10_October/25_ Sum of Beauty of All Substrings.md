# 🌟 Sum of Beauty of All Substrings

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Accuracy-57.41%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-blue?style=for-the-badge" alt="Points" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a string `s`, return the sum of the beauty of all substrings of `s`. The **beauty** of a substring is defined as the difference between the maximum and minimum frequencies of the characters present in that substring.

## 💡 Examples

```text
Input: s = "aaac"
Output: 3
Explanation: The substrings with non-zero beauty are "aaac" and "aac". 
- For "aaac", frequencies: a = 3, c = 1. Beauty = 3 − 1 = 2. 
- For "aac", frequencies: a = 2, c = 1. Beauty = 2 − 1 = 1. 
The remaining substrings have a beauty of 0. Total sum = 2 + 1 = 3.

```

```text
Input: s = "aabc"
Output: 2
Explanation: The substrings with non-zero beauty are "aab" and "aabc". 
- For "aab", frequencies: a = 2, b = 1. Beauty = 2 − 1 = 1. 
- For "aabc", frequencies: a = 2, b = 1, c = 1. Beauty = 2 − 1 = 1. 
Total sum = 1 + 1 = 2.

```

1. We start generating all substrings starting at index 0 (`a`):
* "a": frequencies `{'a':1}`, max=1, min=1 → beauty = 0
* "aa": frequencies `{'a':2}`, max=2, min=2 → beauty = 0
* "aab": frequencies `{'a':2, 'b':1}`, max=2, min=1 → beauty = 1
* "aabc": frequencies `{'a':2, 'b':1, 'c':1}`, max=2, min=1 → beauty = 1


2. Then start from index 1 (`a`):
* "a", "ab", "abc" all have max == min, so beauty = 0.


3. Substrings from index 2 and 3 ("b", "bc", "c") also have beauty = 0.
4. Total sum = 1 + 1 = 2.

---

## ⚙️ Constraints

* `1 ≤ s.size() ≤ 500`
* `s` consists only of lowercase English alphabets.

---

## 🛠️ Solution Approaches

### Optimized Approach (Nested Iteration with Running Frequency)

Instead of recalculating frequencies from scratch for every possible substring (which would be $O(N^3)$), we can iterate using an outer loop for the starting character and an inner loop to expand the substring character by character. We keep a running frequency array of size 26, updating it in $O(1)$ time for every new character added, and checking the min/max frequencies in just 26 steps.

```cpp
// Intuition: To find the sum of beauties of all substrings, we can systematically explore every possible substring while keeping a running count of character frequencies to avoid redundant calculations.
// Approach: Iterate over the string using an outer loop for the start index and an inner loop for the end index. Maintain a frequency array of size 26. Update the frequency for each new character included, find the max and min non-zero frequencies, and add their difference to the total beauty sum.
// Time Complexity: O(N^2) where N is the length of the string, as we evaluate N^2 substrings and perform a constant O(26) operation for each.
// Space Complexity: O(1) auxiliary space since the frequency array always holds exactly 26 elements regardless of input size.

class Solution {
  public:
    int beautySum(string &s) {
        int totalBeauty = 0;
        int n = s.length();

        // Iterate through all possible starting points of substrings
        for (int i = 0; i < n; ++i) {
            // Frequency array for lowercase English letters
            vector<int> freq(26, 0);

            // Expand the substring starting from index i
            for (int j = i; j < n; ++j) {
                // Update frequency of newly added character
                freq[s[j] - 'a']++;

                int maxF = 0;
                int minF = INT_MAX;

                // Find the max and min non-zero frequencies in constant time (26 ops)
                for (int k = 0; k < 26; ++k) {
                    if (freq[k] > 0) {
                        maxF = max(maxF, freq[k]);
                        minF = min(minF, freq[k]);
                    }
                }

                // Add the beauty of the current substring to the total
                totalBeauty += (maxF - minF);
            }
        }

        return totalBeauty;
    }
};

/*
*
* Dry Run
* Input: s = "aabc"
* i=0 ('a'):
*   j=0 ("a"): freq[a]=1. maxF=1, minF=1. Beauty = 0. totalBeauty = 0
*   j=1 ("aa"): freq[a]=2. maxF=2, minF=2. Beauty = 0. totalBeauty = 0
*   j=2 ("aab"): freq[a]=2, b=1. maxF=2, minF=1. Beauty = 1. totalBeauty = 1
*   j=3 ("aabc"): freq[a]=2, b=1, c=1. maxF=2, minF=1. Beauty = 1. totalBeauty = 2
* i=1 ('a'):
*   j=1 ("a"): Beauty = 0. totalBeauty = 2
*   j=2 ("ab"): freq[a]=1, b=1. Beauty = 0. totalBeauty = 2
*   j=3 ("abc"): freq[a]=1, b=1, c=1. Beauty = 0. totalBeauty = 2
* i=2 ('b') & i=3 ('c'):
*   Substrings "b", "bc", "c" all have maxF == minF, Beauty = 0. 
* Final totalBeauty = 2
*
*/

```

---

## 🔍 Key Insights

* **Avoiding $O(N^3)$ Processing**: By keeping the frequency array persistent inside the outer loop and just incrementing it within the inner loop, we avoid scanning the entire substring over and over.
* **Fixed Overhead**: Since the string only contains lowercase english letters, finding the `maxF` and `minF` takes exactly 26 operations, which evaluates to $O(1)$ constant time overhead.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might also like these string manipulation and sliding window challenges:

* Longest Substring Without Repeating Characters
* Minimum Window Substring
* Find All Anagrams in a String

---

## 🔗 References

* **GeeksforGeeks Problem**: [Sum of Beauty of All Substrings](https://www.geeksforgeeks.org/problems/sum-of-beauty-of-all-substrings-1662962118/1)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

## 🏷️ Tags

`#strings` `#substrings` `#geeksforgeeks` `#cpp` `#algorithm`