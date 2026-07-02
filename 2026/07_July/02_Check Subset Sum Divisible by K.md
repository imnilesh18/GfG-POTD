# 🟧 Check Subset Sum Divisible by K

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/subset-with-sum-divisible-by-m2546/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-22.41%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` of positive integers and a value `k`, return `true` if the sum of any non-empty subset of the given array is divisible by `k`. Otherwise, return `false`.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [3, 1, 7, 5], k = 6
Output: true
Explanation: If we take the subset {7, 5} then the sum will be 12 which is divisible by 6.
```

### Example 2
```text
Input: arr[] = [1, 2, 6], k = 5
Output: false
Explanation: All possible subsets of the given set are {1}, {2}, {6}, {1, 2}, {2, 6}, {1, 6} and {1, 2, 6}. There is no subset whose sum is divisible by 5.
```

<details>
<summary><b>📖 Example Breakdown (Example 1)</b></summary>
<br>

- Given array: `[3, 1, 7, 5]`
- Target divisor: `k = 6`
- Let's look at possible subsets:
  - `{3}` -> sum = 3 (not div by 6)
  - `{1, 5}` -> sum = 6 (divisible by 6!) -> **Return true**
  - `{7, 5}` -> sum = 12 (divisible by 6!) -> **Return true**
- Since we only need *any* non-empty subset to be divisible by `k`, finding `{7, 5}` or `{1, 5}` proves the result is `true`.

</details>

---

## 🔐 Constraints

> - `1 <= arr.size(), k <= 10^3`
> - `1 <= arr[i] <= 10^3`

---

## 🛠️ Solution Approach

### **Take / Not-Take (Pick / Non-Pick) with Memoization**

```cpp
// Intuition: We can determine if a subset sum is divisible by K by tracking the current sum modulo K. At each element, we have a choice: take the element or do not take it. By using memoization, we can avoid recalculating overlapping subproblems. Additionally, by the Pigeonhole Principle, if the array size is greater than or equal to K, a subset divisible by K is mathematically guaranteed to exist.
// Approach: 
// 1. Check if arr.size() >= k. If so, return true (Pigeonhole Principle).
// 2. Initialize a DP table with -1 to store the states based on the current index and current remainder.
// 3. Define a recursive function `solve(index, current_remainder)`.
// 4. In the function, calculate `newRem = (current_remainder + arr[index]) % k`. If `newRem == 0`, we found a valid subset, return true immediately.
// 5. Recursively explore two paths: 'Take' the current element (pass newRem) and 'Not Take' the current element (pass current_remainder).
// 6. Store the result of (take || notTake) in the DP table and return it.
// Time Complexity: O(N * K) where N is the size of the array and K is the divisor. Due to our Pigeonhole optimization, N is effectively capped at K, making it O(K^2) worst case.
// Space Complexity: O(N * K) for the DP memoization table and recursion stack space.

class Solution {
private:
    bool solve(int i, int rem, vector<int>& arr, int k, vector<vector<int>>& dp) {
        // Base case: if we reach the end of the array, no valid subset was found
        if (i == arr.size()) {
            return false; 
        }
        
        // Return pre-calculated result if it exists
        if (dp[i][rem] != -1) {
            return dp[i][rem];
        }

        // Simulating the "Take" decision
        int newRem = (rem + arr[i]) % k;
        
        // If taking this element results in a multiple of K, we are done
        if (newRem == 0) {
            return dp[i][rem] = 1; 
        }

        // Recursively check both possibilities: picking and not picking
        bool take = solve(i + 1, newRem, arr, k, dp);
        bool notTake = solve(i + 1, rem, arr, k, dp);

        // Store the outcome and return
        return dp[i][rem] = (take || notTake);
    }

public:
    bool divisibleByK(vector<int>& arr, int k) {
        // Pigeonhole Principle optimization
        // If size >= k, there will always be a subset divisible by k
        if (arr.size() >= k) {
            return true;
        }

        // DP table initialization: size N rows, K columns, filled with -1
        vector<vector<int>> dp(arr.size(), vector<int>(k, -1));
        
        // Start recursion from index 0 with a remainder of 0
        return solve(0, 0, arr, k, dp);
    }
};

/*
*
* Dry Run
*
* Input: arr = [3, 1, 7, 5], k = 6
* Pigeonhole check: size (4) >= k (6) is false, proceed to DP.
* * Initial call: solve(0, 0)
* arr[0] = 3. newRem = (0 + 3) % 6 = 3
* Branch 1 (Take): solve(1, 3)
* arr[1] = 1. newRem = (3 + 1) % 6 = 4
* Branch 1.1 (Take): solve(2, 4)
* arr[2] = 7. newRem = (4 + 7) % 6 = 5
* ...
* Branch 2 (Not Take): solve(1, 0)
* arr[1] = 1. newRem = (0 + 1) % 6 = 1
* Branch 2.2 (Not Take): solve(2, 0)
* arr[2] = 7. newRem = (0 + 7) % 6 = 1
* Branch 2.2.1 (Take): solve(3, 1)
* arr[3] = 5. newRem = (1 + 5) % 6 = 0
* newRem == 0 -> RETURN TRUE!
*
* Output propagates back up the recursion tree as true.
* */
```

---

## 🧠 Key Insights
- **Pigeonhole Principle Magic:** If you generate prefix sums modulo `k`, there are `k` possible remainders (`0` to `k-1`). If the array size is `N >= k`, there are at least `k` prefix sums. Thus, at least two prefix sums must share the same remainder (or one prefix sum is strictly `0` mod `k`). If two prefix sums have the same remainder, the subarray between them is perfectly divisible by `k`. Hence, `if (N >= k) return true;` is a massive optimization!
- **Dynamic Programming (Knapsack Variant):** Because we only care about the *remainder*, the state dynamically shrinks from tracking actual giant sums to just tracking numbers between `0` and `k-1`, drastically reducing the time complexity to exactly what is expected.

---

## 🚀 Further Exploration
- Try extending this logic to find the *length* of the largest/smallest subset divisible by `k`.
- Similar GeeksforGeeks Problems:
  - *Subset Sum Problem*
  - *Partition Equal Subset Sum*
  - *Longest Subarray with Sum Divisible by K*

---

## 🔗 References
- **GeeksforGeeks Problem:** [Check Subset sum divisible by k](https://www.geeksforgeeks.org/problems/subset-with-sum-divisible-by-m2546/1)
- **Concept:** Pigeonhole Principle in Competitive Programming, Dynamic Programming (Subset Sum Variations).

---

## 👨‍💻 Author
Created by **[imnilesh18](https://github.com/imnilesh18)**.  
Feedback, suggestions, and pull requests are always welcome!

---

## 🏷️ Tags
![Dynamic Programming](https://img.shields.io/badge/Dynamic_Programming-purple?style=for-the-badge)
![Algorithms](https://img.shields.io/badge/Algorithms-orange?style=for-the-badge)
![Arrays](https://img.shields.io/badge/Arrays-blue?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge)