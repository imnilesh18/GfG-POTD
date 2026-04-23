<div align="center">

# 🟢 Two Equal Sum Subarrays

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/split-an-array-into-two-equal-sum-subarrays/1)
[![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-54.45%25-blue?style=for-the-badge)](#)
[![Points: 2](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

> **⚠️ Educational Use Only**
> 
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform. 

---
</div>

## 📝 Problem Statement

Given an array of integers `arr[]`, return `true` if it is possible to split it into two subarrays (without reordering the elements) such that the sum of both subarrays are equal. If it is not possible, then return `false`.

### ⚡ Constraints

> - `1 ≤ arr.size() ≤ 10^5`
> - `1 ≤ arr[i] ≤ 10^6`

---

## 💡 Examples

**Example 1:**
```text
Input: arr[] = [1, 2, 3, 4, 5, 5]
Output: true
Explanation: We can divide the array into [1, 2, 3, 4] and [5, 5]. The sum of both the subarrays are 10.
```

**Example 2:**
```text
Input: arr[] = [4, 3, 2, 1]
Output: false
Explanation: We cannot divide the array into two subarrays with equal sum.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>

Let's dry run the array `[1, 2, 3, 4, 5, 5]`:
1. Find the total sum of all elements in the array: $1 + 2 + 3 + 4 + 5 + 5 = 20$.
2. Maintain a running left sum and calculate the right sum dynamically ($total - leftSum$).
3. **Step 1:** At `i=0`, element=1. `leftSum`=1, `rightSum`=19. (Not equal)
4. **Step 2:** At `i=1`, element=2. `leftSum`=3, `rightSum`=17. (Not equal)
5. **Step 3:** At `i=2`, element=3. `leftSum`=6, `rightSum`=14. (Not equal)
6. **Step 4:** At `i=3`, element=4. `leftSum`=10, `rightSum`=10. (**EQUAL!**)
7. We successfully found the split point. Return `true`.
</details>

---

## 🚀 Solution Approach

We can find the partition point in optimal $O(n)$ time by utilizing the **Prefix Sum** technique. 

```cpp
// Intuition: We need to find if there is a point where the prefix sum equals the suffix sum. Instead of calculating the suffix sum every time, we can precalculate the total sum. At any index, the right suffix sum is simply the total sum minus the current prefix sum (left sum).
// Approach: First, traverse the array to compute the `total` sum. Next, iterate through the array again, adding each element to a `leftSum` variable. In the same loop, determine the `rightSum` by subtracting `leftSum` from `total`. If they are equal, return true.
// Time Complexity: O(n), where n is the number of elements in the array. We iterate through the array twice (once for total sum, once for checking).
// Space Complexity: O(1), as we only use a few integer variables (`total`, `leftSum`, `rightSum`) regardless of the array size.

class Solution {
  public:
    bool canSplit(vector<int> &arr) {
        // Calculate total sum of the array
        int total = 0;
        for (int i = 0; i < arr.size(); i++)
            total += arr[i];
    
        int leftSum = 0;
        // Traverse to find a valid split point
        for (int i = 0; i < arr.size(); i++) {
            // Update running prefix sum
            leftSum += arr[i];
    
            // Right sum is the remaining elements' sum
            int rightSum = total - leftSum;
    
            // Check the condition for equal sum subarrays
            if (leftSum == rightSum)
                return true;
        }
    
        // Return false if no split point exists
        return false;
    }
};

/*
* Dry Run
*
* Input: arr[] = [1, 2, 3, 4, 5, 5]
*
* Total sum calculation:
* total = 1 + 2 + 3 + 4 + 5 + 5 = 20
*
* Iteration over elements:
* i = 0 | val = 1 | leftSum = 1  | rightSum = 20 - 1 = 19  -> 1 != 19
* i = 1 | val = 2 | leftSum = 3  | rightSum = 20 - 3 = 17  -> 3 != 17
* i = 2 | val = 3 | leftSum = 6  | rightSum = 20 - 6 = 14  -> 6 != 14
* i = 3 | val = 4 | leftSum = 10 | rightSum = 20 - 10 = 10 -> 10 == 10 (Matches!)
*
* Since leftSum matches rightSum at index 3, we successfully exit and return true.
*/
```

---

## 🧠 Key Insights

- **Avoiding Nested Loops:** A naive approach would check the sum of both halves for every index, taking $O(n^2)$ time. By calculating the total sum upfront, we reduce the secondary check to a single subtraction, completing the algorithm in linear $O(n)$ time.
- **Dynamic Check:** `rightSum` strictly mirrors the remaining sum without needing an explicit suffix array, which keeps the space complexity strictly bounded at $O(1)$.

---

## 🔗 Further Exploration

- [Equilibrium Point](https://www.geeksforgeeks.org/problems/equilibrium-point-1587115620/1) (A similar problem involving pivot indices).
- Subarray with 0 sum checks.

---

## 📚 References

- **Original Problem:** [GeeksforGeeks - Two Equal Sum Subarrays](https://www.geeksforgeeks.org/problems/split-an-array-into-two-equal-sum-subarrays/1)

---

## 👨‍💻 Author

Developed and maintained by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags

`#Prefix Sum` `#Sliding Window` `#Arrays` `#GeeksforGeeks` `#C++` `#Data Structures` 