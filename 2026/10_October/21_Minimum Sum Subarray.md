# 🟧 Minimum Sum Subarray

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-72.37%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-blue?style=for-the-badge" alt="License" />
</div>

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]`, find the minimum sum of a subarray containing atleast one element in the given array[cite: 1].

## 💡 Examples

<details>
<summary>📖 Example Breakdown (Click to Expand)</summary>

**Input:**
```text
arr[] = [3, -4, 2, -3, -1, 7, -5]

```

**Output:**

```text
-6

```

**Explanation:**
The subarray `[-4, 2, -3, -1]` has the minimum sum, which is `-6`.

**Additional Examples:**

**Input:** `arr[] = [4, -6, 3, -2, 5, -8, 2]`
**Output:** `-8`
**Explanation:** The subarray `[-8]` has the minimum sum, which is `-8`.

**Input:** `arr[] = [2, 6, 8, 1, 4]`
**Output:** `1`
**Explanation:** The subarray `[1]` has the minimum sum, which is `1`.
</details>
## ⚙️ Constraints

> * `1 ≤ arr.size() ≤ 10^5`
> 
> * `-10^4 ≤ arr[i] ≤ 10^4`

## 🛠️ Solution Approaches

### Optimized Approach (Kadane's Algorithm Adaptation)

We can adapt Kadane's algorithm to find the minimum sum contiguous subarray by tracking the minimum sum ending at the current position.

```cpp
// Intuition: We can adapt Kadane's algorithm to find the minimum sum contiguous subarray by tracking the minimum sum ending at the current position.
// Approach: 
// 1. Initialize min_sum and current_sum with the first element of the array.
// 2. Iterate through the array starting from the second element.
// 3. Update current_sum to the minimum of the current element or the sum of current_sum and the current element.
// 4. Update min_sum with the minimum of itself and current_sum.
// 5. Return min_sum.
// Time Complexity: O(n) where n is the size of the array, as we iterate through it once.
// Space Complexity: O(1) as we only use two variables for tracking sums.
class Solution {
  public:
    int minSubarraySum(vector<int> &arr) {
        // Initialize with the first element
        int min_sum = arr[0];
        int current_sum = arr[0];
        
        // Iterate through the rest of the array
        for (int i = 1; i < arr.size(); i++) {
            // The minimum sum ending at the current position is either 
            // the current element itself or the current element plus the previous minimum sum
            current_sum = min(arr[i], current_sum + arr[i]);
            
            // Update the overall minimum sum found so far
            min_sum = min(min_sum, current_sum);
        }
        
        return min_sum;
    }
};

/*
* Dry Run
* Input: arr[] = [3, -4, 2, -3]
* Initialization: min_sum = 3, current_sum = 3
* i = 1, arr[1] = -4: current_sum = min(-4, 3 + -4) = -4. min_sum = min(3, -4) = -4
* i = 2, arr[2] = 2: current_sum = min(2, -4 + 2) = -2. min_sum = min(-4, -2) = -4
* i = 3, arr[3] = -3: current_sum = min(-3, -2 + -3) = -5. min_sum = min(-4, -5) = -5
* Return: -5
*/

```

## 🧠 Key Insights

This solution efficiently adapts Kadane's algorithm (which typically finds the maximum contiguous subarray sum) by swapping the `max` function for the `min` function. This allows us to track the most negative running sum continuously in linear time with constant extra space.

## 🚀 Further Exploration

* Try the classic [Largest Sum Contiguous Subarray (Kadane's Algorithm)](https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/) problem to see the exact inverse logic.
* Explore variations like finding the subarray with a sum closest to zero.

## 🔗 References

* Problem Link: [Minimum Sum Subarray](https://www.geeksforgeeks.org/problems/smallest-sum-contiguous-subarray/1)

* For further reading, you can refer to the notes in `GfG.txt`.

## 👨‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

## 🏷️ Tags

* `Arrays`

* `Dynamic Programming`