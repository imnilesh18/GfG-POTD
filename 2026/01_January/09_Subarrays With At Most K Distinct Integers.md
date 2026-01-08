# 🟧 Subarrays With At Most K Distinct Integers

<div align="center">

![Status](https://img.shields.io/badge/Status-Active-success?style=for-the-badge&logo=git&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-62.09%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-yellow?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-purple?style=for-the-badge)

</div>

---

### ⚠️ Educational Use Only
> **This repository and its content are intended solely for educational purposes.** > Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the **[GeeksforGeeks](https://www.geeksforgeeks.org/problems/subarrays-with-at-most-k-distinct-integers/1)** problem.

---

## 📝 Problem Statement

You are given an array `arr[]` of positive integers and an integer `k`. Your task is to find the number of **subarrays** in `arr[]` where the count of distinct integers is **at most** `k`.

> **Note:** A **subarray** is a contiguous part of an array.

---

## 🔍 Examples

### Example 1
```text
Input: arr[] = [1, 2, 2, 3], k = 2
Output: 9
Explanation: The subarrays with at most 2 distinct elements are:
[1], [2], [2], [3],
[1, 2], [2, 2], [2, 3],
[1, 2, 2], [2, 2, 3]

```

### Example 2

```text
Input: arr[] = [1, 1, 1], k = 1
Output: 6
Explanation: All subarrays have distinct count 1 (which is <= 1):
[1] (index 0), [1] (index 1), [1] (index 2),
[1, 1] (0-1), [1, 1] (1-2),
[1, 1, 1] (0-2)

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's take `arr = [1, 2, 1], k = 1`.

1. `j=0`, `arr[j]=1`: Distinct={1}. Valid. Subarrays ending at 0: `[1]`. Count += 1.
2. `j=1`, `arr[j]=2`: Distinct={1, 2}. Size > 1. Shrink window from left.
* Remove `arr[0]=1`. Distinct={2}. Valid. Subarrays ending at 1: `[2]`. Count += 1.


3. `j=2`, `arr[j]=1`: Distinct={2, 1}. Size > 1. Shrink window.
* Remove `arr[1]=2`. Distinct={1}. Valid. Subarrays ending at 2: `[1]`. Count += 1.
Total: 3.



</details>

---

## 🛑 Constraints

* `1 ≤ arr.size() ≤ 2 * 10^4`
* `1 ≤ k ≤ 2 * 10^4`
* `1 ≤ arr[i] ≤ 10^9`

---

## 💡 Solution Approach

### **Sliding Window Strategy**

The problem asks for the number of subarrays with **at most** `k` distinct integers. This property is monotonic: if a window `[i...j]` is valid, then any sub-window ending at `j` (like `[i+1...j]`, `[j...j]`) is also valid.

1. **Expand**: We use a pointer `j` to expand the window to the right, adding elements to a frequency map.
2. **Shrink**: If the number of distinct elements in the map exceeds `k`, we increment the left pointer `i`, removing elements from the map until the distinct count is `≤ k`.
3. **Count**: For every valid window `[i, j]`, the number of valid subarrays ending at `j` is exactly `j - i + 1`. This is because `arr[j]` can be paired with every starting position from `i` to `j` to form a valid subarray.

```cpp
// Intuition: Use a sliding window to maintain a range [i, j] containing at most k distinct elements. 
//            The number of valid subarrays ending at j is the length of this window (j - i + 1).
// Approach: 
//    1. Expand right pointer 'j' and track element frequencies in a map.
//    2. If map size > k, shrink left pointer 'i' until map size <= k.
//    3. Add current window size (j - i + 1) to the result.
// Time Complexity: O(N) - Each element is added and removed from the map at most once.
// Space Complexity: O(N) - In worst case, the map stores all distinct elements (or O(K) if strictly bounded).

class Solution {
  public:
    int countAtMostK(vector<int> &arr, int k) {
        int n = arr.size();
        unordered_map<int, int> mp; // Stores frequency of elements in current window
        
        int i = 0; // Left pointer
        int j = 0; // Right pointer
        
        int result = 0; // Total count of subarrays
        
        while(j < n) {
            
            // Add current element to window
            mp[arr[j]]++;
            
            // If window has more than k distinct elements, shrink from left
            while(mp.size() > k) {
                mp[arr[i]]--;
                if(mp[arr[i]] == 0) {
                    mp.erase(arr[i]); // Remove element completely if count becomes 0
                }
                i++; // Move left pointer forward
            }
            
            // All subarrays ending at j starting from i to j are valid
            // Number of such subarrays = length of window
            result += (j - i + 1);
            
            j++; // Move right pointer forward
        }
        return result;
    }
};

/*
*
* Dry Run: Input: arr[] = [1, 2, 2, 3], k = 2
*
* j=0, arr[0]=1: map={1:1}, size=1. Valid. res += (0-0+1) = 1.
* j=1, arr[1]=2: map={1:1, 2:1}, size=2. Valid. res += (1-0+1) = 1+2 = 3.
* j=2, arr[2]=2: map={1:1, 2:2}, size=2. Valid. res += (2-0+1) = 3+3 = 6.
* j=3, arr[3]=3: map={1:1, 2:2, 3:1}, size=3. Invalid (>2).
* - Shrink i=0: map[1] becomes 0 -> remove 1. map={2:2, 3:1}, size=2. i becomes 1. Valid.
* - res += (3-1+1) = 6+3 = 9.
*
* Final Result: 9
*/

```

---

## 🔑 Key Insights

* **"At Most K" Pattern**: Problems asking for "at most K" are often solvable directly with a single sliding window.
* **Window Math**: The logic `result += (j - i + 1)` is crucial. It efficiently counts valid subarrays ending at index `j` without nested loops.
* **Exact K**: If the problem asked for **exactly** `k` distinct integers, we could compute `countAtMostK(k) - countAtMostK(k-1)`.

---

## 🔗 Further Exploration

* **Subarrays with K Different Integers** (LeetCode 992) - Uses the exact K logic.
* **Longest Substring with At Most K Distinct Characters** - Same logic applied to strings.
* **Count Subarrays with Fixed Bounds** - More complex sliding window variations.

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

---

## 📜 License

This project is licensed under the **MIT License**.


> **Note**: This repository contains solution codes for educational purposes. All the problem statements and test cases are the property of the respective coding platform.
