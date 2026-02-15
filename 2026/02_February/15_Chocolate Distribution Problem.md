# 🍫 Chocolate Distribution Problem

<div align="center">
  <img src="https://img.shields.io/badge/Difficulty-Easy-green?style=for-the-badge&logo=geeksforgeeks" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-49.91%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-yellow?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/Submission-270K%2B-orange?style=for-the-badge" alt="Submissions" />
</div>

<br />

> [!IMPORTANT]
> **⚠️ Educational Use Only**
> 
> This repository and its content are intended solely for **educational purposes**. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

Given an array `arr[]` of positive integers, where each value represents the number of chocolates in a packet. Each packet can have a variable number of chocolates. There are `m` students, the task is to distribute chocolate packets among `m` students such that:

1.  Each student gets **exactly** one packet.
2.  The difference between the **maximum** number of chocolates given to a student and the **minimum** number of chocolates given to a student is minimized.

Return that minimum possible difference.

### 🧱 Constraints

- `1 ≤ m <= arr.size ≤ 10^5`
- `1 ≤ arr[i] ≤ 10^9`

---

## 🔍 Examples

**Input:**
```text
arr = [3, 4, 1, 9, 56, 7, 9, 12], m = 5
```

**Output:**

```text
6
```

<details>
<summary><b>📖 Example Breakdown</b></summary>

1. **Sort the array:** `[1, 3, 4, 7, 9, 9, 12, 56]`
2. We need to pick `m = 5` packets.
3. **Window 1:** `[1, 3, 4, 7, 9]`. Difference = `9 - 1 = 8`.
4. **Window 2:** `[3, 4, 7, 9, 9]`. Difference = `9 - 3 = 6`.
5. **Window 3:** `[4, 7, 9, 9, 12]`. Difference = `12 - 4 = 8`.
6. **Window 4:** `[7, 9, 9, 12, 56]`. Difference = `56 - 7 = 49`.
7. **Minimum Difference:** `6`.

</details>

**Input:**

```text
arr = [7, 3, 2, 4, 9, 12, 56], m = 3
```

**Output:**

```text
2
```

**Explanation:** The minimum difference between maximum chocolates and minimum chocolates is `4 - 2 = 2` by choosing following m packets: `[3, 2, 4]`.

**Input:**

```text
arr = [3, 4, 1, 9, 56], m = 5
```

**Output:**

```text
55
```

**Explanation:** With 5 packets for 5 students, each student will receive one packet, so the difference is `56 - 1 = 55`.

---

## 💡 Solution Approach

### 🚀 Sorting + Sliding Window

The core idea is that to minimize the difference between the maximum and minimum values in a subset, the chosen values must be as close to each other as possible. In a sorted array, the values with the smallest difference for a specific range size `m` will always be contiguous.

**Steps:**

1. **Sort** the array in ascending order.
2. Initialize a sliding window of size `m`.
3. Traverse the array. For every window starting at index `i` and ending at `j = i + m - 1`:
* Calculate the difference: `arr[j] - arr[i]`.
* Update the minimum difference found so far.


4. Return the global minimum difference.

### 💻 C++ Solution

```cpp
// Intuition: To find the minimum difference between max and min in a subset of size m, the elements must be contiguous in a sorted array.
// Approach: Sort the array and use a sliding window of size 'm' to find the minimum difference between the last and first element of the window.
// Time Complexity: O(N log N) due to sorting. The sliding window traversal is O(N).
// Space Complexity: O(1) as we only use a few variables for tracking indices and the result (ignoring sort stack space).

class Solution {
  public:
    int findMinDiff(vector<int>& a, int m) {
        int n = a.size();
        
        // 1. Sort is mandatory for the logic to work
        sort(a.begin(), a.end());
        
        int i = 0; // Start of window
        int j = 0; // End of window
        int minDiff = INT_MAX;
        
        while(j < n) {
            
            // Check if we have hit the required window size of 'm'
            if (j - i + 1 == m) {
                
                // Update the result (max is a[j], min is a[i])
                minDiff = min(minDiff, a[j] - a[i]);
                
                // Shrink the window from the left to slide it forward
                i++;
            }
            
            // Expand the window to the right
            j++;
        }
        
        return minDiff;
    }
};

/*
*
* Dry Run
* Input: arr = [3, 4, 1, 9, 56, 7, 9, 12], m = 5
* n = 8
*
* 1. Sort array: [1, 3, 4, 7, 9, 9, 12, 56]
* 2. Initialize: i = 0, j = 0, minDiff = INT_MAX
*
* Iteration 1-4:
* j increases to 4. Window: [1, 3, 4, 7, 9] (Indices 0 to 4)
* Size is 5 (4 - 0 + 1 == 5).
* minDiff = min(INT_MAX, a[4] - a[0]) = min(MAX, 9 - 1) = 8.
* i becomes 1.
*
* Iteration 5:
* j = 5. Window: [3, 4, 7, 9, 9] (Indices 1 to 5)
* Size is 5.
* minDiff = min(8, a[5] - a[1]) = min(8, 9 - 3) = 6.
* i becomes 2.
*
* Iteration 6:
* j = 6. Window: [4, 7, 9, 9, 12] (Indices 2 to 6)
* Size is 5.
* minDiff = min(6, a[6] - a[2]) = min(6, 12 - 4) = 6.
* i becomes 3.
*
* Iteration 7:
* j = 7. Window: [7, 9, 9, 12, 56] (Indices 3 to 7)
* Size is 5.
* minDiff = min(6, a[7] - a[3]) = min(6, 56 - 7) = 6.
* i becomes 4.
*
* j becomes 8 (Loop ends).
* Return 6.
*
*/

```

---

## 🔑 Key Insights

* **Greedy Property:** In an unsorted array, the packets could be anywhere. By sorting, we ensure that for any chosen smallest packet `arr[i]`, the best possible set of `m` packets including it will be the contiguous segment `arr[i...i+m-1]`.
* **Window Logic:** The difference is simply `arr[end_of_window] - arr[start_of_window]`.
* **Edge Cases:** Since `m <= arr.size`, we don't need to handle cases where we can't form a packet. If `m=1`, the difference is always `0`.

---

## 🔗 References

* **[Problem Link on GeeksforGeeks](https://www.geeksforgeeks.org/problems/chocolate-distribution-problem3825/1)**
* **[Sorting Algorithms - Wikipedia](https://en.wikipedia.org/wiki/Sorting_algorithm)**

---

## Author

**[imnilesh18](https://github.com/imnilesh18)**