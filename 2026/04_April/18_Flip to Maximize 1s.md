# 🪙 Flip to Maximize 1s

<div align="center">
  
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-23.15%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` consisting of `0`'s and `1`'s. A **flip operation** involves changing all `0`'s to `1`'s and all `1`'s to `0`'s within a contiguous subarray. 

Formally, select a range `(l, r)` in the array `arr[]`, such that `(0 ≤ l ≤ r < n)` holds and flip the elements in this range.

Return the **maximum number of 1's** you can get in the array after doing **at most 1 flip operation**.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [1, 0, 0, 1, 0]
Output: 4
Explanation: By flipping the subarray from index 1 to 2, the array becomes [1, 1, 1, 1, 0]. This results in a total of 4 ones, which is the maximum possible after at most one flip.
````

### Example 2

```text
Input: arr[] = [1, 0, 0, 1, 0, 0, 1]
Output: 6
Explanation: By flipping the subarray from index 1 to 5, the array becomes [1, 1, 1, 0, 1, 1, 1]. This results in a total of 6 ones, which is the maximum possible after at most one flip.
```

\<details\>
\<summary\>📖 \<b\>Example Breakdown\</b\>\</summary\>

Consider the Array: `[0, 1, 0, 0, 1, 1, 0]`

1.  **Count Original 1's:** We start with `3` ones in the array.
2.  **Transform Array:** - `0` becomes `+1` (since flipping gives us a new 1)
      - `1` becomes `-1` (since flipping removes an existing 1)
      - Transformed Array: `[1, -1, 1, 1, -1, -1, 1]`
3.  **Apply Kadane’s Algorithm:** Find the maximum subarray sum of the transformed array.
      - Running sum peaks at `2`. This means we can gain a net of `2` extra ones by flipping the optimal subarray.
4.  **Final Result:** Original 1's (`3`) + Extra gained (`2`) = **5 maximum ones**.

\</details\>

-----

## 🧮 Constraints

>   - `1 ≤ n ≤ 10^6`
>   - `0 ≤ arr[i] ≤ 1`

-----

## 🚀 Solution Approach

### Modified Kadane's Algorithm

**Brief Summary/Intuition:**
The core idea is to transform the flip operation into a **Maximum Subarray Sum** problem. By changing `1`s to `-1`s and `0`s to `1`s, the sum of any subarray represents the exact *net gain* in the number of `1`s if we were to flip that specific subarray. Applying Kadane's algorithm quickly finds the maximum possible gain.

```cpp
// Intuition: By treating 0s as +1 (gain) and 1s as -1 (loss), we reframe the problem into finding the maximum contiguous subarray sum, which represents the maximum net gain of 1s achievable by a single flip.
// Approach: Count existing 1s while replacing 1s with -1 and 0s with 1. Then use Kadane's algorithm to find the max subarray sum (maximum gain). Add this gain to the initial count of 1s to get the answer.
// Time Complexity: O(n) where n is the length of the array, as we make linear passes through the elements.
// Space Complexity: O(1) because we modify the input array in-place and only use a few integer variables.

class Solution {
  public:
    // Helper function to apply Kadane's algorithm
    int maxSumSub(vector<int> &arr) {
        int n = arr.size();
        
        int sum = 0;
        int ans = 0;
        
        for (int i=0; i<n; i++) {
            sum += arr[i]; // Accumulate current value
            ans = max(ans, sum); // Update max gain found so far
            
            // If subarray sum becomes negative, skip the subarray 
            // by resetting running sum to 0
            if (sum < 0) sum = 0;
        }
        
        return ans;
    }
    
    // Main function to find the maximum number 
    // of 1's by flipping a subarray.
    int maxOnes(vector<int> &arr) {
        int n = arr.size();
        
        int oneCnt = 0;
        
        // Set 1's to -1 and 0's to 1 
        for (int i=0; i<n; i++) {
            if (arr[i] == 1) {
                arr[i] = -1; // Flipping 1 causes a loss
                oneCnt++;    // Keep track of original 1s
            }
            else arr[i] = 1; // Flipping 0 causes a gain
        }
        
        // Apply Kadane's algorithm to find 
        // the number of extra 1's gained
        int maxDiff = maxSumSub(arr);
        
        // Return total original 1's + max flipped ones
        return oneCnt + maxDiff;
    }
};

/*
*
* Dry Run
* Input: arr[] = [1, 0, 0, 1, 0]
*
* Initialization:
* oneCnt = 0
*
* Transformation loop:
* i=0: arr[0]=1 -> arr[0]=-1, oneCnt=1
* i=1: arr[1]=0 -> arr[1]=1, oneCnt=1
* i=2: arr[2]=0 -> arr[2]=1, oneCnt=1
* i=3: arr[3]=1 -> arr[3]=-1, oneCnt=2
* i=4: arr[4]=0 -> arr[4]=1, oneCnt=2
* Modified arr[] = [-1, 1, 1, -1, 1]
*
* Kadane's Algorithm (maxSumSub):
* sum = 0, ans = 0
* i=0: sum = -1, ans = max(0,-1) = 0, sum < 0 -> sum = 0
* i=1: sum = 1, ans = max(0,1) = 1
* i=2: sum = 2, ans = max(1,2) = 2
* i=3: sum = 1, ans = max(2,1) = 2
* i=4: sum = 2, ans = max(2,2) = 2
* * Result:
* maxDiff = 2
* Total Ones = oneCnt + maxDiff = 2 + 2 = 4
* Output: 4
*
*/
```

-----

## 🔑 Key Insights

  - **Mathematical Mapping:** Standard bit-flipping is hard to optimize directly. By mapping the impact of a flip (a `0` becomes `+1`, a `1` becomes `-1`), the problem elegantly collapses into the classic Maximum Subarray Sum problem.
  - **In-Place Modification:** Modifying the array in-place keeps auxiliary space usage at strictly `O(1)`.
  - **Handling All 1s:** If the array is exclusively `1`s, the transformed array is all `-1`s. Kadane's algorithm correctly yields a maximum sum of `0` (thanks to `ans = max(ans, sum)` and resetting negatives to `0`), resulting in the correct output (no net gain, total `1`s remain the same).

-----

## 🌍 Further Exploration

  - **Maximum Subarray (Kadane's Algorithm):** A fundamental DP concept used directly here.
  - **Maximum Product Subarray:** A related twist on finding contiguous subarray extremums.
  - **Minimum Flips to Make Binary String Alternating:** Another excellent string/array bit-manipulation challenge on GeeksforGeeks and LeetCode.

-----

## 🔗 References

  - **GeeksforGeeks Problem:** [Flip to Maximize 1s](https://www.geeksforgeeks.org/problems/flip-bits0240/1)
  - **Kadane's Algorithm Explanation:** [Wikipedia - Maximum Subarray Problem](https://en.wikipedia.org/wiki/Maximum_subarray_problem)

-----

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)