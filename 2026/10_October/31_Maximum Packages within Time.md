# 📦 Maximum Packages within Time

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge) 
![Accuracy](https://img.shields.io/badge/Accuracy-42.66%25-blue?style=for-the-badge) 
![Points](https://img.shields.io/badge/Points-2-blue?style=for-the-badge) 
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

A delivery agent has to deliver packages at locations arranged in a line.  The number of packages at the `ith` location is given by `arr[i]`. 

The agent can start at any location and can only visit consecutive locations. 
Visiting each location takes **1 unit of time**. 

Given `arr[]` and `totalTime`, find the maximum number of packages the agent can deliver within `totalTime`. 

---

## 💡 Examples

<details>
<summary>📖 Example Breakdown</summary>

```text
Input: arr[] = [2, 1, 3, 5, 0, 1, 4], totalTime = 3
Output: 9
Explanation: The agent can visit three consecutive locations. Starting from the second location, it delivers arr[1] + arr[2] + arr[3] = 1 + 3 + 5 = 9 packages.
```
* *
</details>

```text
Input: arr[] = [1, 6, 2, 5, 3, 4], totalTime = 2
Output: 8
Explanation: The agent can visit two consecutive locations. Starting from the second location, it delivers arr[1] + arr[2] = 6 + 2 = 8 packages. Starting from the fourth location gives arr[3] + arr[4] = 5 + 3 = 8 packages. Hence, the maximum is 8 packages.
```
* *

---

## ⚠️ Constraints

> - `1 ≤ arr.size(), totalTime ≤ 10^5` 
> - `0 ≤ arr[i] ≤ 10^3` 

---

## 🚀 Solution Approaches

### 1️⃣ Optimized Approach (Fixed-Size Sliding Window)

**Brief Summary / Intuition:**
Because the agent can start anywhere and visits consecutive locations, we are essentially looking for the maximum sum of a contiguous subarray.  Since each step takes 1 unit of time, the maximum locations visited is capped by `totalTime`. Because package counts are non-negative, the best strategy is always to visit the maximum allowed locations, bounded by the array's size: `k = min(totalTime, n)`.  We can efficiently find this using a fixed-size sliding window algorithm.

```cpp
// Intuition: Since all packages are non-negative and visiting takes 1 unit of time per location, the agent should always visit exactly `min(totalTime, n)` consecutive locations to maximize the package count. A fixed-size sliding window efficiently finds the maximum sum of any contiguous subarray of this exact size.
// Approach: Calculate the effective window size `k`. Iterate through the array with two pointers (`i` and `j`) to maintain a sliding window. Add elements to `current_sum` as `j` expands. Once the window hits size `k`, update the `max_sum`, then shrink the window from the left (`i++`) while keeping it sliding forward.
// Time Complexity: O(n) - We traverse the array exactly once with the right pointer `j`. 
// Space Complexity: O(1) - Only a few integer variables are used for tracking sums and pointers, requiring constant extra space. 

class Solution {
  public:
    int maxPackages(vector<int>& arr, int totalTime) {
        int n = arr.size();
        int i = 0; // Left pointer of the window
        int j = 0; // Right pointer of the window

        int current_sum = 0;
        int max_sum = 0;

        // The maximum consecutive locations we can visit is bounded by the array size
        int k = min(totalTime, n); 

        while (j < n) {
            // 1. Calculations phase: add the current element to the window
            current_sum += arr[j];

            // 2. Expand phase: if the window size is not yet reached, just expand
            if (j - i + 1 < k) {
                j++;
            }
            // 3. Shrink & Result phase: when the window hits the exact required size
            else if (j - i + 1 == k) {
                // Calculate the result from the current valid window
                max_sum = max(max_sum, current_sum);

                // Remove the element going out of the window as we prepare to slide
                current_sum -= arr[i];

                // Slide the window forward
                i++;
                j++;
            }
        }

        return max_sum;
    }
};

/*
Dry Run
Input: arr = [2, 1, 3, 5, 0, 1, 4], totalTime = 3, k = 3
Init: i = 0, j = 0, current_sum = 0, max_sum = 0

Step 1: j=0, arr[0]=2, current_sum=2. Window size 1 < 3. j++.
Step 2: j=1, arr[1]=1, current_sum=3. Window size 2 < 3. j++.
Step 3: j=2, arr[2]=3, current_sum=6. Window size 3 == 3. max_sum=max(0,6)=6. current_sum-=arr[0](2)=4. i++, j++. (Window slides)
Step 4: j=3, arr[3]=5, current_sum=4+5=9. Window size 3 == 3. max_sum=max(6,9)=9. current_sum-=arr[1](1)=8. i++, j++.
Step 5: j=4, arr[4]=0, current_sum=8+0=8. Window size 3 == 3. max_sum=max(9,8)=9. current_sum-=arr[2](3)=5. i++, j++.
Step 6: j=5, arr[5]=1, current_sum=5+1=6. Window size 3 == 3. max_sum=max(9,6)=9. current_sum-=arr[3](5)=1. i++, j++.
Step 7: j=6, arr[6]=4, current_sum=1+4=5. Window size 3 == 3. max_sum=max(9,5)=9. current_sum-=arr[4](0)=5. i++, j++.

End of loop (j=7). Return max_sum = 9.
*/
```

---

## 🔑 Key Insights
- The condition `min(totalTime, n)` is crucial. Without it, providing a `totalTime` larger than the array size would break the logic. 
- Since there are no negative packages, there is no benefit to stopping early; always using a window of maximum permissible size guarantees the optimal solution.

---

## 🔍 Further Exploration
- GeeksforGeeks: *Maximum Sum Subarray of Size K*
- GeeksforGeeks: *Longest Subarray with Sum K*

---

## 🔗 References
- **Original Problem:** [Maximum Packages within Time](https://www.geeksforgeeks.org/problems/bird-and-maximum-fruit-gathering0509/1) 

---

## 👤 Author
- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
- `Arrays` 
- `Sliding-Window` 
- `Two-Pointer-Algorithm` 
- `Facebook` 
- `C++`