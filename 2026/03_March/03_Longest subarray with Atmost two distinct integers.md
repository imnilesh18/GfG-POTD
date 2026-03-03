# 🟧 Longest subarray with Atmost two distinct integers

<div align="center">
  
  [![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/fruit-into-baskets-1663137462/1)
  [![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
  [![Accuracy](https://img.shields.io/badge/Accuracy-47.98%25-green?style=for-the-badge)](#)
  [![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
  [![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` consisting of positive integers, your task is to find the length of the **longest** subarray that contains at most **two distinct** integers.

---

## 💡 Examples

<details>
<summary><b>📖 Example 1 Breakdown</b></summary>

```text
Input: arr[] = [2, 1, 2]
Output: 3
Explanation: 
The entire array [2, 1, 2] contains at most two distinct integers (2 and 1). 
Hence, the length of the longest subarray is 3.
```
</details>

<details>
<summary><b>📖 Example 2 Breakdown</b></summary>

```text
Input: arr[] = [3, 1, 2, 2, 2, 2]
Output: 5
Explanation: 
The longest subarray containing at most two distinct integers is [1, 2, 2, 2, 2], 
which has a length of 5.
```
</details>

---

## ⚙️ Constraints

> - `1 ≤ arr.size() ≤ 10^5`
> - `1 ≤ arr[i] ≤ 10^5`

---

## 🚀 Solution Approaches

### 1️⃣ Optimized Approach: Sliding Window

**Intuition:**
To solve this problem, we can use the 'Sliding Window' technique. Our goal is to expand our window to the right as long as the number of distinct elements inside it remains 2 or less. We use a hash map (`unordered_map`) to keep track of the frequencies of elements within the current window. As soon as the number of distinct elements exceeds 2, we start shrinking our window from the left until the count of distinct elements is back to 2 or less. 

```cpp
// Intuition: Use a sliding window and a hash map to track at most two distinct elements and their frequencies.
// Approach: Expand the window to the right using pointer j. If the map size exceeds 2, shrink the window from the left using pointer i until the map size is ≤ 2 again. Update the maximum length for each valid window.
// Time Complexity: O(n) — each element is added and removed at most once from the window.
// Space Complexity: O(1) — the hash map will store at most 3 distinct keys at any time.

class Solution {
public:
    int totalElements(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, int> mp;

        int i      = 0;          // left boundary of the window
        int j      = 0;          // right boundary of the window
        int result = 0;          // best window size seen so far

        while (j < n) {
            // include arr[j] into the window
            mp[arr[j]]++;

            // if more than two distinct numbers, shrink from the left
            while (mp.size() > 2) {
                mp[arr[i]]--;            // decrement frequency of arr[i]
                if (mp[arr[i]] == 0) {   // if frequency is zero, remove the key from map
                    mp.erase(arr[i]);
                }
                i++;                     // move the left boundary to the right
            }

            // window [i..j] is valid, update result
            result = max(result, j - i + 1);
            j++;                         // expand the window to the right
        }

        return result;
    }
};

/*
 *
 * Dry Run
 * arr = [1, 2, 1, 2, 3, 2, 2]
 * i = 0, j = 0, mp = {}, result = 0
 *
 * j=0: add 1
 * mp = {1:1}, size=1 ≤ 2 → result = max(0, 1) = 1
 *
 * j=1: add 2
 * mp = {1:1, 2:1}, size=2 ≤ 2 → result = max(1, 2) = 2
 *
 * j=2: add 1
 * mp = {1:2, 2:1}, size=2 ≤ 2 → result = max(2, 3) = 3
 *
 * j=3: add 2
 * mp = {1:2, 2:2}, size=2 ≤ 2 → result = max(3, 4) = 4
 *
 * j=4: add 3
 * mp = {1:2, 2:2, 3:1}, size=3 > 2 → start shrinking:
 * i=0: remove arr[0]=1 → mp={1:1, 2:2, 3:1}, size=3
 * i=1: remove arr[1]=2 → mp={1:1, 2:1, 3:1}, size=3
 * i=2: remove arr[2]=1 → mp={2:1, 3:1}, size=2, stop shrinking
 * new window i=3..4, length = 4 - 3 + 1 = 2 → result stays 4
 *
 * j=5: add 2
 * mp = {2:2, 3:1}, size=2 ≤ 2 → window 3..5 length = 3 → result = 4
 *
 * j=6: add 2
 * mp = {2:3, 3:1}, size=2 ≤ 2 → window 3..6 length = 4 → result = 4
 *
 * End loop → final result = 4
 *
 */
```

---

## 🧠 Key Insights

- **Sliding Window Technique:** This approach is highly efficient and perfectly suited for finding contiguous subarrays while satisfying a specific condition, allowing us to solve the problem in `O(N)` time complexity.
- **Hash Map Usage:** Tracking the numbers and their exact frequencies allows us to easily detect when our window violates the constraint (i.e., contains more than 2 distinct elements).
- **Continuous Optimization:** By checking the length of the window (`j - i + 1`) at every valid step, we can continuously update and safely capture the maximum length in the `result` variable.

---

## 🔍 Further Exploration

- [Substrings of length k with k-1 distinct elements (GeeksforGeeks)](https://www.geeksforgeeks.org/)
- [Longest K unique characters substring (GeeksforGeeks)](https://www.geeksforgeeks.org/)

---

## 📚 References

- **GeeksforGeeks Problem:** [Longest subarray with Atmost two distinct integers](https://www.geeksforgeeks.org/problems/fruit-into-baskets-1663137462/1)
- Detailed study of the Sliding Window Algorithm.

---

## 👨‍💻 Author

[![GitHub](https://img.shields.io/badge/GitHub-imnilesh18-181717?style=for-the-badge&logo=github)](https://github.com/imnilesh18)

---

## 🏷️ Tags

`two-pointer-algorithm` `Arrays` `Data Structures` `Algorithms` `sliding-window`
