# 🧮 Longest Subsequence with Adjacent Diff as 1

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/longest-sub-sequence-such-that-difference-between-adjacents-is-one2558/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty Medium" />
  <img src="https://img.shields.io/badge/Accuracy-29.43%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-red?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License MIT" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem platform.

---

## 📝 Problem Statement

Given an array `arr[]` with `n` elements, find the **longest subsequence** such that the absolute difference between any two adjacent elements in the subsequence is exactly **one**.

### 💡 Constraints
> - `1 ≤ arr.size() ≤ 10^6`
> - `1 ≤ arr[i] ≤ 10^6`

---

## 🔍 Examples

### Example 1
```text
Input : arr[] = [10, 9, 4, 5, 4, 8, 6]
Output : 3
Explanation: The longest subsequences with difference 1 are [10, 9, 8], [4, 5, 4] and [4, 5, 6]. All have a length of 3.
```

### Example 2
```text
Input : arr[] = [1, 2, 3, 2, 3, 7, 2, 1]
Output : 7
Explanation: The longest subsequence with difference 1 is [1, 2, 3, 2, 3, 2, 1]. Length is 7.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>

Let's take **Example 1: `arr[] = [10, 9, 4, 5, 4, 8, 6]`**

We track the maximum subsequence length ending at each number using a map:
1. `10`: No `9` or `11` seen yet. Max length ending at `10` is **1**. (Current max = 1)
2. `9`: We've seen `10`. Length is `dp[10] + 1` = **2**. (Current max = 2)
3. `4`: No `3` or `5` seen yet. Max length ending at `4` is **1**. (Current max = 2)
4. `5`: We've seen `4`. Length is `dp[4] + 1` = **2**. (Current max = 2)
5. `4`: We've seen `5`. Length is `dp[5] + 1` = **3**. (Current max = 3)
6. `8`: We've seen `9`. Length is `dp[9] + 1` = **3**. (Current max = 3)
7. `6`: We've seen `5`. Length is `dp[5] + 1` = **3**. (Current max = 3)

The maximum sequence length achieved overall is **3**.
</details>

---

## 🚀 Solution Approaches

### Optimized Approach (Dynamic Programming with Hashing)

To find the longest subsequence with adjacent differences of `1`, we can use a Hash Map to store the longest subsequence length ending at any particular element. When we process a new element `arr[i]`, we only need to look back and see if `arr[i] - 1` or `arr[i] + 1` exists in our map. If they do, our current element can extend those subsequences.

```cpp
// Intuition: To form a valid subsequence, each element 'x' can only append to a previous subsequence ending in 'x - 1' or 'x + 1'. Using a hash map allows us to track the longest subsequence ending at any number in O(1) time.
// Approach: Iterate through the array while maintaining an unordered_map 'dp' where dp[val] stores the max length of a valid subsequence ending in 'val'. For each element arr[i], check map for arr[i]-1 and arr[i]+1, update dp[arr[i]] with 1 + max of those lengths, and update the global answer.
// Time Complexity: O(n) average case, as we traverse the array once and unordered_map lookups/insertions take O(1) average time.
// Space Complexity: O(n) auxiliary space for storing subsequence lengths of unique elements in the unordered_map.

class Solution {
  public:
      int longestSubseq(vector<int>& arr) {
    
        int n = arr.size();
    
        // Base case: if the array has only one element
        if (n == 1) {
            return 1;
        }
    
        // Map to store the length of the longest subsequence ending at a specific number
        unordered_map<int, int> dp;
        int ans = 1;
    
        // Loop through the array to fill the map with subsequence lengths
        for (int i = 0; i < n; ++i) {
    
            // Check if the current element can extend an adjacent subsequence
            if (dp.count(arr[i] + 1) > 0 || dp.count(arr[i] - 1) > 0) {
                // Update the length for current element based on adjacent numbers
                dp[arr[i]] = 1 + max(dp[arr[i] + 1], dp[arr[i] - 1]);
            } 
            else {
                // Start a new subsequence of length 1 if no adjacent numbers exist
                dp[arr[i]] = 1;  
            }
    
            // Update the overall result with the maximum subsequence length found so far
            ans = max(ans, dp[arr[i]]);
        }
    
        return ans;
    }
};

/*
*
* Dry Run
*
* Input: arr[] = [10, 9, 4, 5, 4, 8, 6]
* 
* i = 0, arr[0] = 10: dp[10] = 1, ans = 1
* i = 1, arr[1] = 9: dp[9] = max(dp[10]+1) = 2, ans = 2
* i = 2, arr[2] = 4: dp[4] = 1, ans = 2
* i = 3, arr[3] = 5: dp[5] = max(dp[4]+1) = 2, ans = 2
* i = 4, arr[4] = 4: dp[4] = max(dp[5]+1) = 3, ans = 3
* i = 5, arr[5] = 8: dp[8] = max(dp[9]+1) = 3, ans = 3
* i = 6, arr[6] = 6: dp[6] = max(dp[5]+1) = 3, ans = 3
* 
* Final Output: 3
*
*/
```

---

## 🧠 Key Insights
- **State Definition Optimization**: Instead of an $O(N^2)$ traditional LIS approach where we check all previous elements, checking only `value - 1` and `value + 1` brings the state transitions down to $O(1)$.
- **Hash Map Utility**: `unordered_map` operates as our DP table, effortlessly managing large numbers and scattered values up to $10^6$ while maintaining a space footprint bounded by $N$.

---

## 🔗 Further Exploration
- Longest Increasing Subsequence (LIS)
- Longest Consecutive Sequence
- Maximum Sum Increasing Subsequence

---

## 📚 References
- **Original Problem**: [GeeksforGeeks - Longest sub-sequence such that difference between adjacents is one](https://www.geeksforgeeks.org/problems/longest-sub-sequence-such-that-difference-between-adjacents-is-one2558/1)

---

## ✍️ Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`#Dynamic-Programming` `#Hash-Map` `#Arrays` `#GeeksforGeeks` `#Flipkart` 

---

> **Friendly Reminder:** Always attempt to solve the problem by yourself first before reviewing the provided code! Happy coding! 🚀