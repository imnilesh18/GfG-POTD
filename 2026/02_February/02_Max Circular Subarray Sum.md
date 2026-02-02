# ⭕ Max Circular Subarray Sum

![GfG](https://img.shields.io/badge/GfG-193K+-orange?logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red)
![Accuracy](https://img.shields.io/badge/Accuracy-29.37%25-blue)
![Points](https://img.shields.io/badge/Points-8-green)
![License](https://img.shields.io/badge/License-MIT-yellow)

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

You are given a circular array `arr[]` of integers, find the **maximum** possible sum of a non-empty subarray. In a circular array, the subarray can start at the end and wrap around to the beginning. Return the maximum non-empty subarray sum, considering both non-wrapping and wrapping cases.

---

## 💾 Examples

### Example 1

```bash
Input: arr[] = [8, -8, 9, -9, 10, -11, 12]
Output: 22
Explanation: Starting from the last element of the array, i.e, 12, and moving in a circular fashion, we have max subarray as 12, 8, -8, 9, -9, 10, which gives maximum sum as 22.

```

### Example 2

```bash
Input: arr[] = [10, -3, -4, 7, 6, 5, -4, -1]
Output: 23
Explanation: Maximum sum of the circular subarray is 23. The subarray is [7, 6, 5, -4, -1, 10].

```

### Example 3

```bash
Input: arr[] = [5, -2, 3, 4]
Output: 12
Explanation: The circular subarray [3, 4, 5] gives the maximum sum of 12.

```

<details>
<summary><b>📖 Example Breakdown: [5, -2, 3, 4]</b></summary>

1. **Standard Kadane's (Max Sum):**
* Subarrays like `[5]`, `[5, -2, 3]`, `[3, 4]`.
* Max continuous sum is `3 + 4 + 5 - 2` isn't contiguous in standard sense, but `3+4` is 7, `5` is 5. Wait, non-wrapping max is actually `5 + (-2) + 3 + 4 = 10`.
* Let's trace:
* `5`: sum=5, max=5
* `-2`: sum=3, max=5
* `3`: sum=6, max=6
* `4`: sum=10, max=10


* `normalSum` = 10.


2. **Inverted Kadane's (Min Sum):**
* We want to find the minimum segment to remove.
* `minSum` trace:
* `5`: sum=5, min=5
* `-2`: sum=3 (reset to -2), min=-2
* `3`: sum=1, min=-2
* `4`: sum=5, min=-2


* `minSum` = -2.


3. **Circular Calculation:**
* `totalSum` = 5 - 2 + 3 + 4 = 10.
* `circularSum` = `totalSum` - `minSum` = 10 - (-2) = 12.


4. **Result:**
* Max(10, 12) = **12**.



</details>

---

## ⚙️ Constraints

* `1 ≤ arr.size() ≤ 10^5`
* `-10^4 ≤ arr[i] ≤ 10^4`

---

## 💡 Solution Approach

### Optimized Approach: Kadane's Algorithm (Standard & Inverted)

The maximum circular subarray sum can be one of two cases:

1. **Non-wrapping:** The maximum subarray sum is entirely within the array (standard Kadane's).
2. **Wrapping:** The maximum subarray sum wraps around the ends. This implies that the elements *not* included in the subarray form a minimum sum subarray in the middle. Thus, `Max Circular Sum = Total Sum - Min Subarray Sum`.

We calculate both and take the maximum. A special edge case exists where all numbers are negative; here, `Total Sum == Min Subarray Sum`, so we simply return the standard max (which is the largest single element).

```cpp
// Intuition: The result is either the max subarray sum (standard Kadane's) or the total sum minus the min subarray sum (wrapping case).
// Approach: Compute total sum, max subarray sum (Kadane's), and min subarray sum (inverted Kadane's) in a single pass. Handle the all-negative edge case.
// Time Complexity: O(n) - Single pass through the array.
// Space Complexity: O(1) - Constant auxiliary space.

class Solution {
  public:
    int maxCircularSum(vector<int> &arr) {

        int totalSum = 0;
        int currMaxSum = 0, currMinSum = 0;
        int maxSum = arr[0], minSum = arr[0];
        
        for (int i = 0; i < arr.size(); i++) {
        
            // Kadane's to find maximum sum subarray
            currMaxSum = max(currMaxSum + arr[i], arr[i]);
            maxSum = max(maxSum, currMaxSum);
        
            // Kadane's to find minimum sum subarray
            currMinSum = min(currMinSum + arr[i], arr[i]);
            minSum = min(minSum, currMinSum);
        
            // Sum of all the elements of input array
            totalSum = totalSum + arr[i];
        }
        
        int normalSum = maxSum;
        int circularSum = totalSum - minSum;
        
        // If the minimum subarray is equal to total Sum
        // then we just need to return normalSum (handles all negative case)
        if (minSum == totalSum)
            return normalSum;
        
        return max(normalSum, circularSum);
    }
};

/*
*
* Dry Run
* Input: arr[] = [5, -3, 5]
*
* Initialization:
* totalSum = 0
* currMax = 0, currMin = 0
* maxSum = 5, minSum = 5
*
* Iteration 1 (i=0, val=5):
* currMax = max(0+5, 5) = 5 -> maxSum = max(5, 5) = 5
* currMin = min(0+5, 5) = 5 -> minSum = min(5, 5) = 5
* totalSum = 5
*
* Iteration 2 (i=1, val=-3):
* currMax = max(5-3, -3) = 2 -> maxSum = max(5, 2) = 5
* currMin = min(5-3, -3) = -3 -> minSum = min(5, -3) = -3
* totalSum = 5 - 3 = 2
*
* Iteration 3 (i=2, val=5):
* currMax = max(2+5, 5) = 7 -> maxSum = max(5, 7) = 7
* currMin = min(-3+5, 5) = 2 -> minSum = min(-3, 2) = -3
* totalSum = 2 + 5 = 7
*
* Results:
* normalSum = 7
* circularSum = totalSum - minSum = 7 - (-3) = 10
* minSum (-3) != totalSum (7)
* Return max(7, 10) = 10
*
* Output: 10 (Explanation: Subarray [5, 5] wrapping around)
*/

```

---

## 🔑 Key Insights

1. **Duality of Min/Max:** Finding the maximum circular sum is mathematically equivalent to finding the minimum subarray sum in the "middle" and subtracting it from the total.
2. **Single Pass Efficiency:** We don't need two separate loops or arrays. `currMax`, `currMin`, and `totalSum` can all be updated in the same iteration `O(N)`.
3. **The "All Negative" Trap:** If the array is `[-1, -2, -3]`, `totalSum` will be `-6` and `minSum` will also be `-6`. `totalSum - minSum` would be `0` (implying an empty subarray), but the problem usually requires a non-empty subarray. In this scenario, the answer should be the max single element (`-1`), which is captured by `maxSum` (`normalSum`).

---

## 🚀 Further Exploration

* **Kadane's Algorithm:** Understand the standard maximum subarray sum problem.
* **Maximum Sum Rectangle:** Apply similar logic to 2D matrices.
* **Maximum Product Subarray:** Handle negative numbers multiplying to positives.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/max-circular-subarray-sum-1587115620/1)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

---

## 📜 License

<div align="center">
<p>This project is licensed under the MIT License.</p>
<p>⚠️ <strong>Educational Use Only</strong>: Solutions are for learning and reference.</p>
</div>

