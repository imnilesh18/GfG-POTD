# 🔀 Maximum Weight Transformation of String

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/maximum-weight-transformation-of-a-given-string3551/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-60.72%25-green?style=for-the-badge" alt="Accuracy: 60.72%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a string `s` consisting only of the characters `'A'` and `'B'`, you can toggle any character. A toggle changes `'A'` to `'B'` or `'B'` to `'A'`.

The weight of a string is calculated using the following rules:
* An alternating adjacent pair (`"AB"` or `"BA"`) contributes **4** to the weight.
* Each character can belong to at most **one** pair, so the pairs must not overlap.
* Every character that does not belong to any pair contributes **1** to the weight.
* Each toggle performed decreases the total weight by **1**.

Therefore, `Weight = (Weight of alternating adjacent pairs) + (Weight of characters that do not belong to any pair) - (Number of Toggles)`

You can toggle characters to make adjacent characters different and form pairs. Find the **maximum possible weight** obtainable from the string by choosing pairs and toggling characters optimally.

---

## 💡 Examples

### Example 1

```text
Input: s = "AA"
Output: 3
Explanation: The possible transformed strings are "AA", "AB", "BA", and "BB". 
The strings "AB" and "BA" each contain one alternating adjacent pair, contributing 4 to the weight. 
One toggle is required to obtain either string from "AA", reducing the weight by 1. 
Therefore, the maximum weight is 4 - 1 = 3.

```

### Example 2

```text
Input: s = "ABB"
Output: 5
Explanation: Possible transformations are "ABB", "ABA", "AAB", "AAA", "BBB", "BBA", "BAB" and "BAA". 
The original string "ABB" contains the alternating adjacent pair "AB", contributing 4 to the weight, while the remaining character 'B' contributes 1. 
No toggles are required. Therefore, the maximum weight is 4 + 1 = 5.

```

1. **Index 0 ('A'):** Cannot pair, weight is `1`.
2. **Index 1 ('B'):** Pair with 'A' to form "AB". Weight becomes `4`. (No toggles needed).
3. **Index 2 ('B'):** Cannot pair with Index 1 since it is already paired. Leave as individual character. Weight becomes `4 + 1 = 5`.
Result: 5.

---

## 🔒 Constraints

> * `1 ≤ s.size() ≤ 10^5`
> * `s` consists only of the characters `A` and `B`
> 
> 

---

## 🛠️ Solution Approaches

### Dynamic Programming (Space Optimized)

**Intuition:**
At any given character in the string, we have two distinct choices: either treat it as an individual character (adding 1 to the weight of the prefix) or pair it with the previous character. If we pair it, the weight depends on whether the characters are already different (adding 4) or the same (requiring a toggle, adding 4 - 1 = 3). Since the current decision only depends on the results of the previous step and the step before that, we can use dynamic programming and optimize the space to $O(1)$.

```cpp
// Intuition: Decide at each step whether to pair the current character with the previous one or leave it unpaired, optimizing for maximum weight.
// Approach: Iterate through the string from index 2 to n. Calculate the score if the current character is NOT paired (previous state + 1). Then calculate the score if it IS paired with the preceding character (if different: state[i-2] + 4; if same: state[i-2] + 3). Update our running maximums.
// Time Complexity: O(n), where n is the length of the string, as we process each character exactly once.
// Space Complexity: O(1), as we only maintain a constant number of variables (prev1, prev2, curr) instead of an entire DP array.

class Solution {
public:
    int getMaxWeight(string &s) {
        int n = s.length();
        
        // Base cases
        if (n == 0) return 0;
        if (n == 1) return 1;
        
        // prev2 tracks the maximum weight for the prefix of length i-2
        int prev2 = 0; 
        
        // prev1 tracks the maximum weight for the prefix of length i-1
        int prev1 = 1; 
        
        int curr = 0;
        
        for (int i = 2; i <= n; ++i) {
            // Choice 1: Do not pair the current character
            int not_paired = prev1 + 1;
            
            // Choice 2: Pair the current character with the previous one
            int paired;
            if (s[i-1] != s[i-2]) {
                paired = prev2 + 4; // Naturally alternating ("AB" or "BA"), no toggles needed
            } else {
                paired = prev2 + 3; // Same characters ("AA" or "BB"), needs 1 toggle (4 - 1 = 3)
            }
            
            // Take the maximum of both choices
            curr = max(not_paired, paired);
            
            // Update pointers for the next iteration
            prev2 = prev1;
            prev1 = curr;
        }
        
        return curr;
    }
};

/*
*
* Dry Run
* Input: s = "ABB"
* n = 3
* Initial state: prev2 = 0, prev1 = 1
*
* Iteration 1 (i = 2):
* s[1] ('B') != s[0] ('A')
* not_paired = prev1 + 1 = 1 + 1 = 2
* paired = prev2 + 4 = 0 + 4 = 4
* curr = max(2, 4) = 4
* Update: prev2 = 1, prev1 = 4
*
* Iteration 2 (i = 3):
* s[2] ('B') == s[1] ('B')
* not_paired = prev1 + 1 = 4 + 1 = 5
* paired = prev2 + 3 = 1 + 3 = 4
* curr = max(5, 4) = 5
* Update: prev2 = 4, prev1 = 5
*
* Return curr = 5
*
*/

```

---

## 🧠 Key Insights

* **Overlapping Subproblems:** The maximum weight at index `i` inherently relies on the maximum weights calculated at indices `i-1` and `i-2`, making this a classic DP structure.
* **Space Optimization Tricks:** Since we only ever need to look back two steps (`prev1` and `prev2`) to compute the current maximum weight, we do not need an array of size $N$. This reduces the auxiliary space complexity from the expected $O(N)$ down to $O(1)$.

---

## 🔭 Further Exploration

* Practice similar Dynamic Programming state-machine problems like **House Robber** or **Decode Ways**.
* Explore string manipulation and greedy algorithm counterparts on GeeksforGeeks.

---

## 🔗 References

* [Maximum Weight Transformation of a Given String on GeeksforGeeks](https://www.geeksforgeeks.org/problems/maximum-weight-transformation-of-a-given-string3551/1)

---

## ✍️ Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`dynamic-programming` `strings` `space-optimization` `geeksforgeeks` `c++`