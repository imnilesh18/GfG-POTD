<div align="center">

# 📈 Maximum Frequency with K Increments

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/maximum-frequency-1662528911/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-65.85%25-green?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

</div>

---

## 📝 Problem Statement

Given an integer array `arr[]`. In one operation, you can choose an index and increment its value by 1[cite: 1].

Find the maximum possible frequency of any element after performing at most `k` operations[cite: 1].

---

## 🎯 Examples

**Example 1:**
```text
Input: arr[] = [2, 2, 4], k = 4
Output: 3
```

<details>
<summary><b>📖 Example Breakdown</b></summary>

1. We have the array `[2, 2, 4]` and `k = 4` maximum increments available[cite: 1].
2. If we target the number `4`, we need to increment the first `2` two times, and the second `2` two times.
3. Total operations used = `2 + 2 = 4`, which is exactly equal to our `k`[cite: 1].
4. The array becomes `[4, 4, 4]`[cite: 1].
5. The maximum frequency of `4` is `3`[cite: 1].
</details>

**Example 2:**
```text
Input: arr[] = [7, 7, 7, 7], k = 5
Output: 4
Explanation: The frequency of 7 is already 4, so no operations are needed.
```

---

## 🛑 Constraints

* `1 ≤ arr.size() ≤ 10^5`[cite: 1]
* `1 ≤ arr[i] ≤ 10^6`[cite: 1]
* `0 ≤ k ≤ 10^5`[cite: 1]

---

## 💡 Solution Approaches

### Optimized Approach: Sorting + Sliding Window
*(Note: As the Hindi explanation was not provided, the intuition and approach below have been reverse-engineered into clear, concise English based on the provided optimal sliding-window logic.)*

#### 1. Intuition
To maximize the frequency of an element using the fewest increments, we should only increment numbers that are already close to our target value. Sorting the array helps us group these closer numbers together. By utilizing a sliding window, we can test each element as a potential "target maximum" and dynamically adjust the window size to see how many previous elements can be incremented to match it without exceeding `k` operations.

#### 2. Approach
* **Sort the array:** This ensures that elements in any contiguous subarray are as close to each other in value as possible.
* **Sliding Window:** We use two pointers, `i` (left) and `j` (right). The element at `arr[j]` is our current target value.
* **Calculate Cost:** The total cost to make all elements in our window `[i, j]` equal to the target `arr[j]` is calculated using the formula: `(Target Value * Window Size) - Sum of Window`.
* **Shrink if Necessary:** If this cost exceeds our allowed operations `k`, the window is invalid. We shrink it from the left by incrementing `i` and updating the window sum.
* **Track Maximum:** At each valid step, we update our maximum frequency with the current window size.

#### Code Implementation

```cpp
// Intuition: To maximize an element's frequency with limited increments, we should target numbers and increment smaller numbers that are closest to it. Sorting groups these numbers together, allowing us to use a sliding window to find the longest valid sequence.
// Approach: 
// 1. Sort the array in ascending order.
// 2. Use a sliding window [i, j] where arr[j] is the target maximum value.
// 3. The cost to make all elements in the window equal to arr[j] is calculated as: (target * window_size) - sum_of_window.
// 4. If this cost exceeds k, shrink the window from the left (i++) until the cost is valid.
// 5. Keep track of the maximum window size encountered.
// Time Complexity: O(n log n) because sorting the array dominates the time complexity, while the sliding window traverses the array in O(n) time.
// Space Complexity: O(1) as we are only using a few extra variables for pointers, sum, and max frequency.

class Solution {
  public:
    int maxFrequency(vector<int>& arr, int k) {
        // Step 1: Sort the array to ensure we process closest elements together
        sort(arr.begin(), arr.end());
        
        int i = 0; // Left pointer of the sliding window
        int j = 0; // Right pointer of the sliding window
        long long sum = 0; // Running sum of elements inside the current window
        int max_freq = 0; // Stores the maximum valid frequency found
        
        // Step 2: Standard Sliding Window Template
        while (j < arr.size()) {
            // Expand: Add current element to the window sum
            sum += arr[j];
            
            // Shrink: If total increments needed exceed k, shrink from the left
            // increments needed = (target_value * window_size) - window_sum
            while ((long long)arr[j] * (j - i + 1) - sum > k) {
                // Remove the leftmost element from the sum and advance the left pointer
                sum -= arr[i];
                i++;
            }
            
            // Calculate result: Update the maximum frequency found so far for valid windows
            max_freq = max(max_freq, j - i + 1);
            
            // Move right pointer to evaluate the next potential target
            j++;
        }
        
        return max_freq;
    }
};

/*
*
* Dry Run
* Input: arr = [2, 2, 4], k = 4
*
* Step 1: Sort array -> arr = [2, 2, 4]
* 
* Iteration 1 (j=0, target=2):
* sum = 2
* Cost = (2 * 1) - 2 = 0. Cost <= 4, so window is valid.
* max_freq = max(0, 1) = 1.
*
* Iteration 2 (j=1, target=2):
* sum = 2 + 2 = 4
* Cost = (2 * 2) - 4 = 0. Cost <= 4, so window is valid.
* max_freq = max(1, 2) = 2.
*
* Iteration 3 (j=2, target=4):
* sum = 4 + 4 = 8
* Cost = (4 * 3) - 8 = 4. Cost <= 4, so window is valid.
* max_freq = max(2, 3) = 3.
*
* Output: 3
*
*/
```

---

## 🔑 Key Insights

* **Sorting is mandatory:** You cannot arbitrarily increment numbers spread across the array efficiently without sorting. Sorting guarantees that for any target `X`, the numbers with the cheapest increment "cost" to reach `X` are directly adjacent to it.
* **Mathematical Window Cost:** Instead of individually calculating the difference for each element, the formula `(Target * Size) - Sum` gives the total increments required in `O(1)` time, drastically optimizing the sliding window.

---

## 🔎 Further Exploration

If you enjoyed this problem, you might want to practice these related sliding-window and frequency maximization problems:
* **Max Consecutive Ones III** (Sliding Window concept)
* **Longest Repeating Character Replacement**
* **Find All Anagrams in a String**

---

## 🔗 References

* **GeeksforGeeks Problem:** [Maximum Frequency with K Increments](https://www.geeksforgeeks.org/problems/maximum-frequency-1662528911/1)

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`sliding-window` `sorting` `two-pointers` `array` `geeksforgeeks`
