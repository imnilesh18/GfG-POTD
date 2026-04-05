# 🎯 Target Sum

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/target-sum-1626326450/1"><img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks"></a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium">
    <img src="https://img.shields.io/badge/Accuracy-31.52%25-green?style=for-the-badge" alt="Accuracy: 31.52%">
    <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4">
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT">
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array of integers `arr[]` and an integer `target`. We need to build an expression out of `arr[]` by adding one of the symbols `+` or `-` before each integer in `arr[]` and then concatenate all the integers.

For example: if `arr[] = [2, 1]`, you can add a `+` before 2 and a `-` before 1 and concatenate them to build the expression `+2-1`.

Return the number of different expressions that can be built, which evaluates to `target`.

> **Note:** An expression is considered different from another if the placement of `+` and `-` operators differs, even if the resulting value is the same.

---

## 💡 Examples

```text
Input: arr[] = [1, 1, 1, 1, 1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
```

```text
Input: arr[] = [1, 2, 3], target = 2
Output: 1
Explanation: There is 1 way to assign symbols to make the sum of nums be target 2.
+1 - 2 + 3 = 2
```

<details>
<summary><b>📖 Example Breakdown</b></summary>

For `arr = [1, 2, 3]` and `target = 2`:
- We explore all branches.
- Branch 1: `+1`
  - `+1 + 2 = 3` -> `+3 + 3 = 6` (No)
  - `+1 + 2 = 3` -> `+3 - 3 = 0` (No)
  - `+1 - 2 = -1` -> `-1 + 3 = 2` (✅ **Yes!**)
  - `+1 - 2 = -1` -> `-1 - 3 = -4` (No)
- Branch 2: `-1`
  - `-1 + 2 = 1` -> `+1 + 3 = 4` (No)
  - `-1 + 2 = 1` -> `+1 - 3 = -2` (No)
  - `-1 - 2 = -3` -> `-3 + 3 = 0` (No)
  - `-1 - 2 = -3` -> `-3 - 3 = -6` (No)
- Only 1 valid way! Result is 1.

</details>

---

## ⚙️ Constraints

> - `1 ≤ arr.size() ≤ 50`
> - `1 ≤ arr[i] ≤ 20`
> - `0 ≤ sum(arr) ≤ 1000`
> - `-1000 ≤ target ≤ 1000`
> 
> **Expected Complexities**
> - **Time Complexity:** `O(n * sum(arr))`
> - **Auxiliary Space:** `O(sum(arr))`

---

## 🛠️ Solution Approaches

### [Naive Approach] Using Recursion
The idea is to explore all possible expressions by assigning either a `+` or `-` sign to each element of the array. At each step, the current index and the cumulative sum together define the state of the recursion. When all elements have been processed, the current sum is compared with the target.

```cpp
// Intuition: We can either add or subtract each element to reach the target sum. We try all combinations recursively.
// Approach: For each element at index i, make two recursive calls: one adding the element to the current sum, and one subtracting it. Base case is when we reach the end of the array; if sum matches target, return 1, else 0.
// Time Complexity: O(2^n), as we have two choices for each of the n elements.
// Space Complexity: O(n), for the recursive call stack depth.
class Solution {
  public:
    int findPossibleWays(vector<int>& arr, int i, int s, int& target) {
    
        // If target is reached and all elements are processed, return 1
        if (s == target && i == arr.size())
            return 1;
    
        // If all elements are processed and target is not reached, return 0
        if (i >= arr.size())
            return 0;
    
        // Return total count of two choices:
        // 1. Add current element
        // 2. Subtract current element
        return findPossibleWays(arr, i + 1, s + arr[i], target)
               + findPossibleWays(arr, i + 1, s - arr[i], target);
    }
    
    int totalWays(vector<int>& arr , int target){
        return findPossibleWays(arr , 0 , 0 , target);
    }
};

/*
*
* Dry Run
* arr = [1, 1], target = 0
* i=0, s=0
* add 1: i=1, s=1
* add 1: i=2, s=2 -> returns 0
* sub 1: i=2, s=0 -> returns 1
* sub 1: i=1, s=-1
* add 1: i=2, s=0 -> returns 1
* sub 1: i=2, s=-2 -> returns 0
* totalWays = 1 + 1 = 2
*
*/
```

---

### [Better Approach-1] Top Down DP (Memoization)
This approach optimizes the recursive solution by storing results of overlapping subproblems. Since the cumulative sum can become negative, an offset equal to the total sum of all elements is used to map sums to valid non-negative indices in the DP table.

```cpp
// Intuition: Overlapping subproblems in recursion can be memoized. We use a total sum offset to map negative sums to valid indices.
// Approach: Initialize a 2D DP array of size n x (2*totalSum + 1) with -1. During recursion, check if the result for the current index and sum (shifted by totalSum) is already computed. Otherwise, compute, store, and return it.
// Time Complexity: O(n * sum(arr)), as there are n * (2*sum) unique states to compute.
// Space Complexity: O(n * sum(arr)) for the DP table + O(n) recursive stack space.
class Solution {
  public:
    int findPossibleWays(vector<int>& arr, vector<vector<int> >& dp, 
                     int i, int s, int &target, int &total_sum) {
    
        // If target is reached and all elements are processed, return 1
        if (s == target && i == arr.size())
            return 1;
    
        // If all elements are processed and target is not reached, return 0
        if (i >= arr.size())
            return 0;
    
        // Use total_sum as an offset to handle negative cumulative sums
        if (dp[i][s + total_sum] != -1)
            return dp[i][s + total_sum];
    
        // Compute and store total count of two cases:
        // 1. Add current element
        // 2. Subtract current element
        return dp[i][s + total_sum]
               = findPossibleWays(arr, dp, i + 1, s + arr[i],
                               target, total_sum)
                 + findPossibleWays(arr, dp, i + 1, s - arr[i],
                                 target, total_sum);
    }
    
    int totalWays(vector<int>& arr , int target){
        int N = arr.size();
        int totalSum = 0;
        
        // Calculate total sum for offset
        for(int i = 0; i < N; i++){
            totalSum += arr[i];
        }
        
        // Initialize DP table with -1
        vector<vector<int>> dp(N , vector<int>(2*totalSum + 1, -1));
        return findPossibleWays(arr , dp , 0 , 0 , target , totalSum);
    }
};

/*
*
* Dry Run
* arr = [1], target = 1, totalSum = 1
* dp initialized to size 1 x 3 with -1
* i=0, s=0
* add 1: i=1, s=1 -> base case returns 1
* sub 1: i=1, s=-1 -> base case returns 0
* dp[0][1] = 1 + 0 = 1
* return 1
*
*/
```

---

### [Better Approach-2] Bottom Up DP (Tabulation)
In this approach, a DP table is built iteratively. Here, `dp[i][j]` represents the number of ways to form a sum `j` using the first `i` elements of the array. The table is initialized to represent zero elements forming a sum of zero.

```cpp
// Intuition: We can build a DP table iteratively where dp[i][j] stores the number of ways to form sum j using the first i elements.
// Approach: Initialize a DP table. Set dp[0][totalSum] = 1. Iterate through elements and sums, updating the current sum's ways by taking ways from the previous step (adding and subtracting current element).
// Time Complexity: O(n * sum(arr)), as we iterate over n elements and 2*sum possible sums.
// Space Complexity: O(n * sum(arr)), for storing the 2D DP table.
class Solution {
  public:
    int totalWays(vector<int>& arr, int target) {
        int N = arr.size();
        int totalSum = 0;
        
        // Calculate the maximum possible sum
        for(int i = 0; i < N; i++){
            totalSum += arr[i];
        }
        
        // DP table initialized to 0
        vector<vector<int>> dp(N + 1, vector<int> (2*totalSum + 1 , 0));
        
        // Base case: 1 way to get 0 sum with 0 elements (offset by totalSum)
        dp[0][totalSum] = 1;
        
        // Iterate through all elements
        for(int i = 1 ; i <= N ; i++){
            // Iterate through all possible sums
            for(int j = 0; j <= 2*totalSum; j++){
                
                // Propagate forward by adding current element
                if(j + arr[i-1] <= 2*totalSum)
                dp[i][j + arr[i-1]] += dp[i - 1][j];
                
                // Propagate forward by subtracting current element
                if(j - arr[i-1] >= 0)
                dp[i][j - arr[i-1]] += dp[i - 1][j];
                
            }
        }
        // Return ways to reach target (offset by totalSum)
        return dp[N][target + totalSum];
    }
};

/*
*
* Dry Run
* arr = [1], target = 1, totalSum = 1
* dp size 2 x 3
* dp[0][1] = 1
* i = 1
* j = 1: 
* add 1: dp[1][2] += dp[0][1] (1)
* sub 1: dp[1][0] += dp[0][1] (1)
* return dp[1][1+1] -> dp[1][2] = 1
*
*/
```

---

### [Expected Approach] Space Optimization
This approach reduces space usage by observing that each DP row depends only on the previous row. Instead of maintaining a full 2D table, two 1D arrays are used to represent the previous and current states.

```cpp
// Intuition: Since the DP state for the current element only depends on the results of the previous element, we can optimize space by only keeping the previous row.
// Approach: Use two 1D arrays `prev` and `curr`. Initialize `prev` for base case 0 elements. For each element, update `curr` based on `prev` for both addition and subtraction. Assign `curr` to `prev` after processing each element.
// Time Complexity: O(n * sum(arr)), iterating through elements and all possible sums.
// Space Complexity: O(sum(arr)), as we only store two 1D arrays of size 2*sum + 1.
class Solution {
  public:
    int totalWays(vector<int>& arr, int target) {
        int N = arr.size();
        int totalSum = 0;
        for(int i = 0; i < N; i++){
            totalSum += arr[i];
        }
        
        // Only two 1D arrays curr and prev needed
        vector<int> prev(2*totalSum + 1 , 0);
        vector<int> curr;
        
        // Base case: 1 way to get sum 0 (offset by totalSum)
        prev[totalSum] = 1;
        
        for(int i = 1 ; i <= N ; i++){
            // Reset curr array for the new element
            curr.assign(2*totalSum + 1 , 0);
            for(int sum = 0; sum <= 2*totalSum; sum++){
                
                // Propagate forward by adding current element
                if(sum + arr[i - 1] <= 2*totalSum)
                curr[sum + arr[i - 1]] += prev[sum];
                
                // Propagate forward by subtracting current element
                if(sum - arr[i - 1] >= 0)
                curr[sum - arr[i - 1]] += prev[sum];
                
            }
            // Move current state to previous for next iteration
            prev = curr;
            
        }
        // Result is in prev at target index
        return prev[target + totalSum];
    }
};

/*
*
* Dry Run
* arr = [1], target = 1, totalSum = 1
* prev = [0, 1, 0]
* i = 1
* curr = [0, 0, 0]
* sum = 1:
* add 1: curr[2] += prev[1] (1)
* sub 1: curr[0] += prev[1] (1)
* curr = [1, 0, 1]
* prev = curr
* return prev[2] = 1
*
*/
```

---

## 🔍 Key Insights
- **Offsets for Negative Indices:** Since a cumulative sum can dip into negative bounds, introducing an offset (`totalSum`) makes sure all valid array indices lie between `0` and `2 * totalSum`.
- **Space Optimization Pattern:** When DP relies solely on `dp[i-1][...]` to compute `dp[i][...]`, rolling 1D arrays drastically slash the required memory.
- **Conversion to Subset Sum:** This problem can optionally be reframed as finding a subset that equals a derived target `(target + sum) / 2`. 

---

## 🔭 Further Exploration
If you enjoyed this problem, you might also like these:
- **Partition Equal Subset Sum**
- **Subset Sum Problem**
- **Perfect Sum Problem**

---

## 🔗 References
- **Original Problem**: [Target Sum - GeeksforGeeks](https://www.geeksforgeeks.org/problems/target-sum-1626326450/1)

---

## 👨‍💻 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`dynamic-programming` `recursion` `memoization` `array` `geeksforgeeks` 