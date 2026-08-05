# 🧮 Subarrays with Sum in Range

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks">
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty"> 
  <img src="https://img.shields.io/badge/Accuracy-48.76%25-green?style=for-the-badge" alt="Accuracy"> 
  <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points"> 
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License">
</div>

⚠️ Educational Use Only:
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement
Given an integer array `arr[]` and two integers `l` and `r`, find the number of subarrays whose sum lies in the range `[l, r]` (inclusive). 

> A subarray is a contiguous sequence of elements within the array. 

---

## 💡 Examples

### Example 1
```text
Input: l = 3, r = 8, arr[] = [1, 4, 6]
Output: 3
```
<details>
<summary>📖 Example Breakdown</summary>
The subarrays are <code>[1, 4]</code>, <code>[4]</code>, and <code>[6]</code>.  Therefore, the answer for this test case is <code>3</code>. 
</details>

### Example 2
```text
Input: l = 4, r = 13, arr[] = [2, 3, 5, 8]
Output: 6
```
<details>
<summary>📖 Example Breakdown</summary>
The subarrays are <code>[2, 3]</code>, <code>[2, 3, 5]</code>, <code>[3, 5]</code>, <code>[5]</code>, <code>[5, 8]</code>, and <code>[8]</code>.  Therefore, the answer for this test case is <code>6</code>. 
</details>

---

## ⚠️ Constraints
> - `1 ≤ arr.size() ≤ 10^5` 
> - `1 ≤ arr[i] ≤ 10^4` 
> - `1 ≤ l ≤ r ≤ 10^9` 

---

## 🚀 Solution Approaches

### 1️⃣ Optimized Sliding Window
**Summary / Intuition:**
Since all array elements are positive integers, the prefix sums increase monotonically. This allows us to use the sliding window technique to count valid sums efficiently. Instead of directly finding sums exactly in the range `[l, r]`, we can find the number of subarrays with a sum less than or equal to `r` and subtract the number of subarrays with a sum less than or equal to `l - 1`. 

```cpp
// Intuition: The problem asks for subarrays with sums in range [l, r]. Since array elements are positive, prefix sums increase monotonically. This allows us to use the sliding window technique. We can find the result by calculating (Subarrays with sum <= r) - (Subarrays with sum <= l - 1).
// Approach: Create a helper function using two pointers (left and right) to count subarrays with sum <= target. We add elements to a running sum. If the sum exceeds the target, we increment the left pointer to shrink the window until the sum is valid again. For each valid window, we add (right - left + 1) to the total count.
// Time Complexity: O(n) because each element is visited at most twice (by right and left pointers) in the sliding window. 
// Space Complexity: O(1) as we only use primitive variables to keep track of the sums and pointers. 
class Solution {
  private:
    long long countSumLessOrEqualTo(vector<int>& arr, int target) {
        long long count = 0;
        long long currentSum = 0;
        int left = 0;
        
        for (int right = 0; right < arr.size(); right++) {
            currentSum += arr[right]; // Expand the window to the right
            
            while (currentSum > target && left <= right) {
                currentSum -= arr[left]; // Shrink the window if sum is too large
                left++;
            }
            
            count += (right - left + 1); // Add all valid subarrays ending at 'right'
        }
        
        return count;
    }

  public:
    long long countSubarray(vector<int>& arr, int l, int r) {
        // Result = (Count with sum <= r) - (Count with sum <= l - 1)
        return countSumLessOrEqualTo(arr, r) - countSumLessOrEqualTo(arr, l - 1);
    }
};

/*
*
* Dry Run
*
Input: arr = [1, 4, 6], l = 3, r = 8

Target R = 8:
right=0, arr[0]=1, sum=1. sum <= 8. count += (0-0+1) -> 1
right=1, arr[1]=4, sum=5. sum <= 8. count += (1-0+1) -> 3
right=2, arr[2]=6, sum=11. sum > 8. Shrink: sum=10 (left=1). Shrink: sum=6 (left=2). count += (2-2+1) -> 4
Total subarrays <= 8 is 4.

Target L-1 = 2:
right=0, arr[0]=1, sum=1. sum <= 2. count += (0-0+1) -> 1
right=1, arr[1]=4, sum=5. sum > 2. Shrink: sum=4 (left=1). Shrink: sum=0 (left=2). count += (1-2+1) -> 1
right=2, arr[2]=6, sum=6. sum > 2. Shrink: sum=0 (left=3). count += (2-3+1) -> 1
Total subarrays <= 2 is 1.

Final Result: 4 - 1 = 3.
*/
```

---

## 🧠 Key Insights
- **Monotonicity**: The problem explicitly bounds `arr[i] ≥ 1`.  Without negative numbers or zeroes, the sum of a contiguous subarray strictly grows as it expands. This guarantees the sliding window approach is mathematically sound.
- **Difference Array Logic**: Calculating the range `[l, r]` using `Count(r) - Count(l - 1)` significantly simplifies window tracking and logic, circumventing the need for complex simultaneous pointers.

---

## 🔍 Further Exploration
- Subarray Sum Equals K
- Longest Subarray with Sum K
- Sliding Window Maximum

---

## 🔗 References
- **GeeksforGeeks Problem:** [Count the number of subarrays](https://www.geeksforgeeks.org/problems/count-the-number-of-subarrays/1) 

---

## 👤 Author
[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
- `sliding-window` 
- `Arrays` 
- `Two-Pointers`
- `geeksforgeeks`