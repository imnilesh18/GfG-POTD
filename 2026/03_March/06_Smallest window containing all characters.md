<div align="center">
  
# 🪟 Smallest window containing all characters
  
[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/smallest-window-in-a-string-containing-all-the-characters-of-another-string-1587115621/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-30.19%25-green?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-orange?style=for-the-badge)](#)
  
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two strings `s` and `p`. Find the smallest substring in `s` consisting of all the characters (including duplicates) of the string `p`. Return an empty string `""` in case no such substring is present. 

If there are multiple such substrings of the same length found, return the one with the **least starting index**.

### 🚧 Constraints
- `1 ≤ s.length(), p.length() ≤ 10^6`
- `s` and `p` consist of lowercase English letters.

---

## 💡 Examples

### Example 1
```text
Input: s = "timetopractice", p = "toc"
Output: "toprac"
Explanation: "toprac" is the smallest substring in which "toc" can be found.
```

### Example 2
```text
Input: s = "zoomlazapzo", p = "oza"
Output: "apzo"
Explanation: "apzo" is the smallest substring in which "oza" can be found.
```

### Example 3
```text
Input: s = "zoom", p = "zooe"
Output: ""
Explanation: No substring is present containing all characters of p.
```

<details>
<summary>📖 Example Breakdown (Example 1)</summary>

**Input:** `s = "timetopractice"`, `p = "toc"`
- We need the characters `t`, `o`, and `c` at least once in our window.
- As we traverse `s` from left to right, we find our first valid window at index 0 to 10: `"timetoprac"`. Length is 11.
- We then shrink this window from the left to remove unneeded characters.
- By dropping the initial `"time"`, we get a new valid window from index 4 to 10: `"toprac"`. Length is 6.
- We continue traversing, but no smaller window containing `t`, `o`, `c` is found.
- The smallest valid window is `"toprac"`.
</details>

---

## ⚙️ Solution Approach

```cpp
// Intuition: We need to find the smallest substring in 's' that contains all characters of 'p'. A sliding window approach is perfect for this. We expand the window to the right until all characters are found, then shrink it from the left to minimize the window size while ensuring it still contains all characters of 'p'.
// Approach:
// 1. Create a frequency map `mp` for string `p` to know exactly how many of each character we need. Count unique required characters in `required`.
// 2. Maintain a `window` map for the current window in `s` and a `formed` counter to track how many unique characters have met their required frequency.
// 3. Expand the window by moving `j` to the right, adding `s[j]` to `window`. If `s[j]`'s frequency matches the required, increment `formed`.
// 4. Once `formed == required` (window is valid), record the minimum length and starting index. Then shrink the window from the left by moving `i` and updating frequencies to find smaller valid windows.
// 5. Finally, extract the substring using the best starting index and length.
// Time Complexity: O(n) where n is the length of 's'. The variables i and j only move forward, visiting each character at most twice.
// Space Complexity: O(1) auxiliary space, as the frequency arrays 'mp' and 'window' have a fixed size of 256, which is a constant.

class Solution {
  public:
    string minWindow(string &s, string &p) {
        int n = s.size();
        int m = p.size();
        
        // Edge case: if p is longer than s, it's impossible
        if (m > n || m == 0) return "";
        
        // Frequency array to store the required counts of characters in p
        vector<int> mp(256, 0);
        int required = 0; // Number of unique characters we need to match
        
        for (char c : p) {
            if (mp[c] == 0) required++;
            mp[c]++;
        }
        
        int i = 0;
        int j = 0;
        
        // Frequency array for the current window
        vector<int> window(256, 0);
        int formed = 0; // Number of unique characters currently meeting the requirement
        
        int minLen = INT_MAX;
        int start_idx = -1; // To extract the substring later
        
        while (j < n) {
            // 1. Add current character to window
            char c = s[j];
            window[c]++;
            
            // 2. If this character's frequency matches the required frequency, increment formed
            if (mp[c] > 0 && window[c] == mp[c]) {
                formed++;
            }
            
            // 3. Shrink the window while it is VALID (contains all characters of p)
            while (formed == required) {
                // Update the minimum window length and starting index
                if (j - i + 1 < minLen) {
                    minLen = j - i + 1;
                    start_idx = i;
                }
                
                // Remove the left-most character from the window
                char leftChar = s[i];
                window[leftChar]--;
                
                // If removing it breaks the requirement, decrement formed
                if (mp[leftChar] > 0 && window[leftChar] < mp[leftChar]) {
                    formed--;
                }
                
                i++; // Contract window
            }
            
            j++; // Expand window
        }
        
        // 4. Return the result
        return minLen == INT_MAX ? "" : s.substr(start_idx, minLen);
    }
};

/*
Dry Run
s = "timetopractice", p = "toc"
mp: t=1, o=1, c=1 (required = 3)

j=0: s[0]='t', window: t=1. formed=1
j=1..4: s="time", window: t=2,i=1,m=1,e=1. formed=1
j=5: s[5]='t', window: t=2...
j=6: s[6]='o', window: o=1. formed=2
j=7..10: s="timetoprac", window: ..., c=1. formed=3 (Valid Window!)

Shrink phase (formed == required):
len = 10-0+1=11, start=0. Remove s[0]='t'. window: t=1 (mp[t]=1), still formed=3
i=1. len = 10-1+1=10, start=1. Remove s[1]='i', formed=3
i=2. len = 9, start=2. Remove 'm', formed=3
i=3. len = 8, start=3. Remove 'e', formed=3
i=4. len = 7, start=4. Remove 't', window: t=0, formed=2 (Breaks loop)

Expand phase continues...
Finds "toprac" -> len=6, start=4.
Result = "toprac"
*/
```

---

## 🧠 Key Insights
- **Sliding Window Technique:** Instead of checking every possible substring (which would be computationally impossible at `O(n^2)` or `O(n^3)`), the sliding window dynamically expands and shrinks the search region, completing the task in linear `O(n)` time.
- **Frequency Arrays:** Given the constraints dictate only English characters, utilizing simple fixed-size arrays `vector<int> mp(256, 0)` is considerably faster than using hash maps (`std::unordered_map`). 
- **Formed Counter:** Keeping track of `formed` unique characters completely matching the `required` unique characters from `p` prevents having to iterate through 256 array spaces to validate the window condition on every loop.

---

## 🔍 Further Exploration
- Check out other sliding window patterns: [Longest Substring Without Repeating Characters](https://www.geeksforgeeks.org/length-of-the-longest-substring-without-repeating-characters/)
- Practice frequency hashing on: [Find All Anagrams in a String](https://www.geeksforgeeks.org/find-all-anagrams-in-a-string/)

---

## 🔗 References
- **Original Problem:** [Smallest window containing all characters (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/smallest-window-in-a-string-containing-all-the-characters-of-another-string-1587115621/1)
- **Sliding Window Algorithm:** [GeeksforGeeks Article](https://www.geeksforgeeks.org/window-sliding-technique/)

---

## ✍️ Author
**[imnilesh18](https://github.com/imnilesh18)**

### 🏷️ Tags
`sliding-window` `hash` `strings` `dynamic-programming` `binary-search` `geeksforgeeks` `c++`