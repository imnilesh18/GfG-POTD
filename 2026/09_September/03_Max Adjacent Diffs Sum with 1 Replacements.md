# 🧮 Max Adjacent Diffs Sum with 1 Replacements

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/modify-array-to-maximize-sum-of-adjacent-differences1729/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-55.0%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="MIT License" />
</div>

<br>

<div align="center">
  <b>⚠️ Educational Use Only:</b><br>
  This repository and its content are intended solely for educational purposes.<br>
  Solutions are provided for learning, practice, and reference only.<br>
  Problem statement and test cases are based on the GeeksforGeeks problem.
</div>

---

## 📝 Problem Statement

Given an integer array `arr[]`, you are allowed to replace any elements with `1`. Find the maximum sum of absolute differences between consecutive elements after any number of modifications.

## 💡 Examples

```text
Input: arr[] = [3, 2, 1, 4, 5]
Output: 8
Explanation: Modify the array as arr[] = [3, 1, 1, 4, 1]. 
Sum = |1-3| + |1-1| + |4-1| + |1-4| = 8, the maximum possible.
```

```text
Input: arr[] = [1, 5]
Output: 4
Explanation: No modification needed. Sum = |5-1| = 4.
```

<details>
<summary>📖 <b>Example Breakdown (arr[] = [3, 2, 1, 4, 5])</b></summary>

1. **Index 0:** Keep as `3`.
2. **Index 1:** Change `2` to `1`. Difference with previous: `|1 - 3| = 2`. Sum = `2`.
3. **Index 2:** Keep as `1`. Difference with previous: `|1 - 1| = 0`. Sum = `2 + 0 = 2`.
4. **Index 3:** Keep as `4`. Difference with previous: `|4 - 1| = 3`. Sum = `2 + 3 = 5`.
5. **Index 4:** Change `5` to `1`. Difference with previous: `|1 - 4| = 3`. Sum = `5 + 3 = 8`.
Total maximum sum achieved is **8**.
</details>

## ⚠️ Constraints

> - `1 ≤ arr.size() ≤ 10^5`

---

## 🛠️ Solution Approaches

### 1. Dynamic Programming (Optimized Approach)

```cpp
// Intuition: At each step, we have two choices for an element: either keep it as is or change it to 1. Since the choice at the current step only depends on the previous step's state, we can use Dynamic Programming to track the maximum sum for both choices up to the current index.
// Approach: Create a 2D DP array where dp[i][0] is the max sum if the i-th element becomes 1, and dp[i][1] is the max sum if it remains arr[i]. Iterate through the array, updating the DP states based on the absolute differences between the current and next elements under both conditions.
// Time Complexity: O(n) because we iterate through the array of size n exactly once.
// Space Complexity: O(n) for the 2D DP array storing the states for each index.

class Solution {
  public:
    int maxDiffSum(vector<int> &arr) {
        int n = arr.size();

        // dp[i][0] stores the maximum sum when the i-th element is changed to 1
        // dp[i][1] stores the maximum sum when the i-th element remains unchanged
        vector<vector<int>> dp(n, vector<int>(2, 0));

        // Fill the DP table
        for (int i = 0; i < n - 1; i++) {

            // Case 1: Current element (i+1) is changed to 1
            // Compare previous element changed to 1 vs previous element unchanged
            dp[i + 1][0] = max(dp[i][0], dp[i][1] + abs(1 - arr[i]));

            // Case 2: Current element (i+1) remains as arr[i + 1]
            // Compare previous element changed to 1 vs previous element unchanged
            dp[i + 1][1] = max(dp[i][0] + abs(arr[i + 1] - 1), dp[i][1] + abs(arr[i + 1] - arr[i]));
        }

        // Return the maximum possible difference sum
        return max(dp[n - 1][0], dp[n - 1][1]);
    }
};

/*
* Dry Run
* Input: arr[] = [1, 5]
* n = 2
* dp table initialized to 2x2 with 0s.
* i = 0:
*   dp[1][0] = max(dp[0][0], dp[0][1] + abs(1 - arr[0]))
*            = max(0, 0 + abs(1 - 1)) = 0
*   dp[1][1] = max(dp[0][0] + abs(arr[1] - 1), dp[0][1] + abs(arr[1] - arr[0]))
*            = max(0 + abs(5 - 1), 0 + abs(5 - 1)) = 4
* Loop ends.
* Return max(dp[1][0], dp[1][1]) = max(0, 4) = 4.
* Output: 4
*/
```

## 🧠 Key Insights
- **State Definition:** By clearly defining `dp[i][0]` and `dp[i][1]`, we perfectly capture the two possible states for any element at index `i`.
- **Greedy Falls Short:** A greedy approach won't work because changing an element to `1` might yield a larger difference now, but ruin the potential for an even larger difference with the next element. DP looks at the global optimum.
- **Space Optimization Potential:** Since `dp[i+1]` only relies on `dp[i]`, we could easily optimize the space complexity to `O(1)` by just maintaining two variables for the previous states. 

## 🔍 Further Exploration
- How would you optimize the current `O(n)` space complexity to `O(1)`?
- **Related Patterns:** This is heavily related to the "State Machine DP" pattern, similar to problems like *House Robber* or *Best Time to Buy and Sell Stock*.

## 🔗 References
- **Original Problem:** [Max Adjacent Diffs Sum with 1 Replacements on GeeksforGeeks](https://www.geeksforgeeks.org/problems/modify-array-to-maximize-sum-of-adjacent-differences1729/1)

## 👨‍💻 Author
Created and maintained by [imnilesh18](https://github.com/imnilesh18).

## 🏷️ Tags
`Dynamic Programming` `Arrays` `GeeksforGeeks` `C++`