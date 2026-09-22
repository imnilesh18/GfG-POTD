# 🟧 Longest Matching in Dictionary with Removals

<div align="center">
  
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-43.54%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

</div>

<br/>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a lowercase string `s` and a dictionary `d[]` containing lowercase words, find the **longest word** in the dictionary that can be obtained by deleting some characters from `s` without changing the order of the remaining characters (i.e., it must be a valid subsequence).

**Note:** 
* If multiple words have the same maximum length, return the lexicographically smallest one. 
* If no valid word exists, return an empty string.

---

## 💡 Examples

### Example 1
```text
Input: d = ["ale", "apple", "monkey", "plea"], s = "abpcplea"
Output: "apple" 
Explanation: After deleting "b", "c", "a", string s becomes "apple", which is present in d.
```

### Example 2
```text
Input: d = ["a", "b", "c"], s = "abpcplea"
Output: "a"
Explanation: After deleting "b", "p", "c", "p", "l", "e", "a", string s becomes "a", which is present in d.
```

<details>
<summary><b>📖 Example Breakdown (Example 1)</b></summary>

Let's evaluate each word against `s = "abpcplea"`:

1. **"ale"** (Length 3): Can be formed by taking the `a` at index 0, `l` at index 5, and `e` at index 6. Valid!
2. **"apple"** (Length 5): Can be formed by taking `a` (0), `p` (2), `p` (4), `l` (5), `e` (6). Valid! It is longer than "ale", so our best candidate becomes "apple".
3. **"monkey"** (Length 6): The letter `m` is not present in `s`. Invalid!
4. **"plea"** (Length 4): Can be formed, but its length (4) is less than our current best candidate "apple" (5). Ignored.

**Final Answer:** `"apple"`
</details>

---

## ⚙️ Constraints

> - `1 ≤ |s| ≤ 5 * 10^5`
> - `1 ≤ n ≤ 10^4` *(where `n` is the number of words in the dictionary)*
> - `1 ≤ m ≤ 100` *(where `m` is the max length of a word in the dictionary)*
> - `s` and all words in the dictionary consist only of lowercase English letters.

---

## 🚀 Solution Approach

### Optimized Approach (Character Positioning & Binary Search)

A simple two-pointer approach for every word would take `O(|s|)` per word, leading to `O(n * |s|)` which is `10^4 * 5*10^5 = 5*10^9` operations—resulting in a Time Limit Exceeded (TLE). 

Instead, we can optimize this by precomputing the indices of every character in `s`. Then, for each character in a dictionary word, we can use **Binary Search (`upper_bound`)** to quickly find the next available index in `s`, drastically reducing the check time.

```cpp
// Intuition:
// To find the longest word in the dictionary that can be formed by deleting characters from string s, we check if each word is a valid subsequence of s. Pre-storing character positions in string s allows binary search to rapidly verify if characters appear in increasing order.

// Approach:
// 1. Store all occurrences of each character in string s in a list of indices `pos`.
// 2. Iterate through each word in the dictionary `d`.
// 3. Skip words that cannot beat the current best answer (shorter length, or equal length but lexicographically larger).
// 4. For candidate words, use std::upper_bound to binary search the next available index for each character in s.
// 5. Update the result with the longest and lexicographically smallest valid word found.

// Time Complexity:
// O(|s| + n * m * log|s|) - Preprocessing string s takes O(|s|) time. For each of the n words of length up to m, checking subsequence takes O(m * log|s|) binary searches.

// Space Complexity:
// O(|s|) - Auxiliary space required to store character index lists for string s.

class Solution {
  public:
    string findLongestWord(string &s, vector<string> &d) {
        // Store indices for each character in string s
        vector<vector<int>> pos(26);
        for (int i = 0; i < s.length(); i++) {
            pos[s[i] - 'a'].push_back(i);
        }

        string result = "";

        // Process each dictionary word
        for (const string &word : d) {
            // Skip word if it cannot improve current best result
            if (word.length() < result.length() || 
               (word.length() == result.length() && word >= result)) {
                continue;
            }

            // Verify if word is a subsequence of s via binary search
            int curr_pos = -1;
            bool is_subsequence = true;

            for (char ch : word) {
                const vector<int> &vec = pos[ch - 'a'];
                auto it = upper_bound(vec.begin(), vec.end(), curr_pos);

                // Character index not found after curr_pos
                if (it == vec.end()) {
                    is_subsequence = false;
                    break;
                }

                // Move current position to the found index
                curr_pos = *it;
            }

            // Update answer if word is valid
            if (is_subsequence) {
                result = word;
            }
        }

        return result;
    }
};

/*
*
* Dry Run
*
* Input: d = ["ale", "apple", "monkey", "plea"], s = "abpcplea"
* 
* Preprocessing s = "abpcplea":
* pos['a'] = [0, 7]
* pos['b'] = [1]
* pos['c'] = [3]
* pos['e'] = [6]
* pos['l'] = [5]
* pos['p'] = [2, 4]
* Initial result = ""
*
* Processing word = "ale":
* Length 3 > 0, proceed
* 'a': upper_bound in [0, 7] for > -1 gives index 0, curr_pos = 0
* 'l': upper_bound in [5] for > 0 gives index 5, curr_pos = 5
* 'e': upper_bound in [6] for > 5 gives index 6, curr_pos = 6
* Valid subsequence: update result = "ale"
*
* Processing word = "apple":
* Length 5 > 3, proceed
* 'a': upper_bound in [0, 7] for > -1 gives index 0, curr_pos = 0
* 'p': upper_bound in [2, 4] for > 0 gives index 2, curr_pos = 2
* 'p': upper_bound in [2, 4] for > 2 gives index 4, curr_pos = 4
* 'l': upper_bound in [5] for > 4 gives index 5, curr_pos = 5
* 'e': upper_bound in [6] for > 5 gives index 6, curr_pos = 6
* Valid subsequence: update result = "apple"
*
* Processing word = "monkey":
* Length 6 > 5, proceed
* 'm': upper_bound in [] for > -1 yields end (not found)
* Invalid subsequence
*
* Processing word = "plea":
* Length 4 < 5, skip check because result length (5) > word length (4)
*
* Final Output: "apple"
*
*/
```

---

## 🔍 Key Insights

* **Pre-optimization Trimming:** By verifying if `word.length() < result.length()` (or matching length but worse lexicographically), we avoid the costly `upper_bound` lookups entirely for words that could never improve our current best answer.
* **Smart Data Tracking:** Converting string `s` into a highly accessible map of strictly increasing character indices turns a linear scan `O(|s|)` into an ultra-fast binary search `O(log |s|)`!
* **Subsequence Nature:** The condition to form a valid string is strictly sequential. Hence, tracking `curr_pos` across the `upper_bound` operations ensures we only pick indices positioned *after* the previously matched character's index.

---

## 🔭 Further Exploration

* Look into related classic string matching problems, such as **Longest String Chain**.
* Practice on identical variants like **LeetCode 524: Longest Word in Dictionary through Deleting**.
* Try solving using the Two-Pointer approach just for comparison to see why it hits Time Limit Exceeded (TLE) against massive constraints!

---

## 🌐 References

* **Original Problem:** [GeeksforGeeks - Find largest word in dictionary](https://www.geeksforgeeks.org/problems/find-largest-word-in-dictionary2430/1)
* **C++ STL Reference:** [std::upper_bound](https://en.cppreference.com/w/cpp/algorithm/upper_bound)

---

## 👤 Author

* **Created by:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Strings` `Binary Search` `Subsequence` `Two Pointers` `GeeksforGeeks`