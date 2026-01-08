# 🟧 Count Subarray with k odds

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D35?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-subarray-with-k-odds/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-FFC107?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-subarray-with-k-odds/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-51.12%25-28a745?style=for-the-badge)](https://www.geeksforgeeks.org/problems/count-subarray-with-k-odds/1)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/count-subarray-with-k-odds/1)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](LICENSE)

</div>

---

### ⚠️ Educational Use Only
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/problems/count-subarray-with-k-odds/1) problem.

---

## 🧐 Problem Statement

You are given an array `arr[]` of positive integers and an integer `k`. You have to **count** the number of subarrays that contain exactly `k` odd numbers.

### 🔹 Constraints
- $1 \le k \le arr.size() \le 10^5$
- $1 \le arr[i] \le 10^9$

---

## 📂 Examples

### Example 1
```bash
Input: arr[] = [2, 5, 6, 9], k = 2
Output: 2
Explanation: There are 2 subarrays with 2 odds: [2, 5, 6, 9] and [5, 6, 9].

```

### Example 2

```bash
Input: arr[] = [2, 2, 5, 6, 9, 2, 11], k = 2
Output: 8
Explanation: There are 8 subarrays with 2 odds:
[2, 2, 5, 6, 9], [2, 5, 6, 9], [5, 6, 9],
[2, 2, 5, 6, 9, 2], [2, 5, 6, 9, 2], [5, 6, 9, 2],
[6, 9, 2, 11], [9, 2, 11]

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's look at `arr[] = [2, 5, 6, 9]` with `k = 2`.

1. **At most 2 odds:**
* `[2]` (0 odds)
* `[2, 5]` (1 odd)
* `[2, 5, 6]` (1 odd)
* `[2, 5, 6, 9]` (2 odds)
* `[5]` (1 odd)
* `[5, 6]` (1 odd)
* `[5, 6, 9]` (2 odds)
* `[6]` (0 odds)
* `[6, 9]` (1 odd)
* `[9]` (1 odd)
* **Total:** 10 subarrays.


2. **At most 1 odd:**
* Excluding subarrays with 2 odds: `[2, 5, 6, 9]` and `[5, 6, 9]`.
* **Total:** 8 subarrays.


3. **Exactly 2 odds:**
*  subarrays.



</details>

---

## 💡 Solution Approach

### 🚀 Optimized Approach: Sliding Window (Two Pointers)

#### Intuition

Finding the number of subarrays with *exactly* `k` odd numbers directly using a single sliding window is tricky because the window needs to be flexible (it can expand or shrink while keeping the count `k`).

However, counting subarrays with **at most** `k` odd numbers is straightforward.
The logic follows the property:


#### Algorithm

1. Create a helper function `countAtMost(arr, k)`:
* Use two pointers, `i` and `j`, to represent the current window.
* Expand `j` and count odd numbers.
* If the count exceeds `k`, shrink the window from `i` until the count is valid.
* The number of valid subarrays ending at `j` is `j - i + 1`. Add this to the total.


2. The final answer is `countAtMost(arr, k) - countAtMost(arr, k - 1)`.

#### 💻 Code

```cpp
// Intuition: Calculating exactly k odds directly is complex. Using the property Exactly(k) = AtMost(k) - AtMost(k-1) simplifies this to a standard sliding window problem.
// Approach: Implement a helper to count subarrays with at most k odds using a sliding window. Subtract the result of k-1 from k.
// Time Complexity: O(N) since both pointers move across the array at most once per call.
// Space Complexity: O(1) as we only use a few integer variables.
class Solution {
  public:
    // Standard template to count subarrays with AT MOST k odd numbers
    int countAtMost(vector<int>& arr, int k) {
        if (k < 0) return 0;
        
        int i = 0, j = 0;
        int count = 0;
        int ans = 0;
        int n = arr.size();

        while (j < n) {
            // 1. Expand the window
            if (arr[j] % 2 != 0) {
                count++;
            }

            // 2. Shrink the window if invalid (too many odds)
            while (count > k) {
                if (arr[i] % 2 != 0) {
                    count--;
                }
                i++;
            }

            // 3. Calculate result 
            // All subarrays ending at j starting from i are valid (have <= k odds)
            ans += (j - i + 1);

            j++;
        }
        return ans;
    }

    int countSubarrays(vector<int>& arr, int k) {
        // Exactly K = (At most K) - (At most K-1)
        return countAtMost(arr, k) - countAtMost(arr, k - 1);
    }
};

/*
*
* Dry Run
* Input: arr = [2, 5, 6, 9], k = 2
*
* Call 1: countAtMost(arr, 2)
* j=0, val=2(even): win=[2], cnt=0 <= 2. ans += 1-0+1 = 1. (Total: 1)
* j=1, val=5(odd):  win=[2,5], cnt=1 <= 2. ans += 1-0+1 = 2. (Total: 3)
* j=2, val=6(even): win=[2,5,6], cnt=1 <= 2. ans += 2-0+1 = 3. (Total: 6)
* j=3, val=9(odd):  win=[2,5,6,9], cnt=2 <= 2. ans += 3-0+1 = 4. (Total: 10)
* Result AtMost(2) = 10.
*
* Call 2: countAtMost(arr, 1)
* j=0, val=2: win=[2], cnt=0. ans += 1. (Total: 1)
* j=1, val=5: win=[2,5], cnt=1. ans += 2. (Total: 3)
* j=2, val=6: win=[2,5,6], cnt=1. ans += 3. (Total: 6)
* j=3, val=9: cnt becomes 2. Loop while(cnt>1):
* i=0 (val 2), cnt=2. i becomes 1.
* i=1 (val 5), cnt=1. i becomes 2.
* Window now indices [2,3] (vals [6,9]), i=2, j=3. ans += 3-2+1 = 2. (Total: 8)
* Result AtMost(1) = 8.
*
* Final: 10 - 8 = 2.
*
*/

```

---

## 🗝️ Key Insights

* **Problem Transformation**: Converting "Exactly K" problems into "At most K" - "At most K-1" is a powerful technique for sliding window problems involving counts.
* **Sliding Window Efficiency**: The "At most K" approach allows the window to only expand and shrink monotonically, ensuring linear time complexity.
* **Handling Integers**: The logic applies strictly to the count of odd numbers, treating evens as "transparent" or 0-weight elements in terms of constraints.

---

## 🚀 Further Exploration

* [Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/)
* [Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/)
* [Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/)

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/count-subarray-with-k-odds/1)

---

## 📝 Author

Created by [imnilesh18](https://github.com/imnilesh18).

---

## 🏷️ Tags

---

## 📜 License

<div align="center">

</div>

> **Note**: This repository is for educational purposes. Please use these solutions to understand the concepts and improve your coding skills. Avoid direct copying for competitive programming.
