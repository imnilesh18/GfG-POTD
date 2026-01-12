# 🟧 K Sized Subarray Maximum

<div align="center">

[![Status](https://img.shields.io/badge/Status-Active-success.svg)]()
[![Platform](https://img.shields.io/badge/GeeksforGeeks-Medium-orange.svg)](https://www.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k3101/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-26.04%25-blue.svg)]()
[![Points](https://img.shields.io/badge/Points-4-yellow.svg)]()
[![License](https://img.shields.io/badge/License-MIT-green.svg)]()

</div>

---

### ⚠️ Educational Use Only
> **This repository and its content are intended solely for educational purposes.** > Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

Given an array `arr[]` of positive integers and an integer `k`. You have to find the **maximum value** for each contiguous subarray of size `k`. Return an array of maximum values corresponding to each contiguous subarray.

### 📊 Examples

#### Example 1
```text
Input: arr[] = [1, 2, 3, 1, 4, 5, 2, 3, 6], k = 3
Output: [3, 3, 4, 5, 5, 5, 6]
Explanation: 
1st contiguous subarray [1, 2, 3], max = 3
2nd contiguous subarray [2, 3, 1], max = 3
3rd contiguous subarray [3, 1, 4], max = 4
4th contiguous subarray [1, 4, 5], max = 5
5th contiguous subarray [4, 5, 2], max = 5
6th contiguous subarray [5, 2, 3], max = 5
7th contiguous subarray [2, 3, 6], max = 6

```

#### Example 2

```text
Input: arr[] = [5, 1, 3, 4, 2], k = 1
Output: [5, 1, 3, 4, 2]
Explanation: When k = 1, each element in the array is its own subarray, so the output is simply the same array.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's walk through Example 1: `arr = [1, 2, 3, 1, 4, 5, 2, 3, 6]`, `k = 3`.

1. **Window [1, 2, 3]**: Max is `3`.
2. **Window [2, 3, 1]**: Max is `3`.
3. **Window [3, 1, 4]**: Max is `4`.
4. **Window [1, 4, 5]**: Max is `5`.
5. **Window [4, 5, 2]**: Max is `5`.
6. **Window [5, 2, 3]**: Max is `5`.
7. **Window [2, 3, 6]**: Max is `6`.

Result: `[3, 3, 4, 5, 5, 5, 6]`

</details>

---

## 🛑 Constraints

$1 \leq arr.size() \leq 10^6$

$1 \leq k \leq arr.size()$

$0 \leq arr[i] \leq 10^9$



---

## 💡 Solution Approaches

### 🚀 Optimized Approach: Sliding Window with Deque

A brute-force approach would iterate through every window and find the max in , leading to an overall  complexity. This is inefficient for large .

We can optimize this to  using a **Deque (Doubly Ended Queue)**. The deque will store **indices** of array elements. The key invariant is to maintain the deque in **decreasing order** of values. The front of the deque will always have the index of the maximum element for the current window.

#### C++ Solution

```cpp
// Intuition: Use a Deque to maintain indices of elements in decreasing order. The front of the Deque always stores the index of the maximum element for the current window.
// Approach: Iterate through the array. 1) Remove elements from back of Deque smaller than current (maintain decreasing order). 2) Add current index. 3) Remove front if out of window. 4) Add max (front) to result.
// Time Complexity: O(N) - Each element is added and removed from the deque at most once.
// Space Complexity: O(K) - The deque stores at most K elements in the worst case (e.g., sorted decreasing array).

class Solution {
  public:
    vector<int> maxOfSubarrays(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> result;
        deque<int> dq; // Stores INDICES

        for (int j = 0; j < n; j++) {
            
            // 1. Remove elements from back that are smaller than current element
            // (Because the current element is larger and will last longer)
            while (!dq.empty() && arr[dq.back()] <= arr[j]) {
                dq.pop_back();
            }
            
            // 2. Add current element's index
            dq.push_back(j);
            
            // 3. Remove the front if it's out of the current window
            // The window is [j-k+1 ... j]. If front < j-k+1, it's gone.
            if (dq.front() < j - k + 1) {
                dq.pop_front();
            }
            
            // 4. Store result (start adding once we hit the first window size k)
            if (j >= k - 1) {
                result.push_back(arr[dq.front()]);
            }
        }
        
        return result;
    }
};

/*
*
* Dry Run
* Input: arr = [1, 3, -1, -3, 5], k = 3
*
* j = 0 (val 1):
* dq is empty. push(0). dq=[0]
*
* j = 1 (val 3):
* arr[0]=1 <= 3. pop(0). dq is empty.
* push(1). dq=[1]
*
* j = 2 (val -1):
* arr[1]=3 > -1. No pop back.
* push(2). dq=[1, 2]
* Window [0..2]. front(1) is inside.
* j >= 2. Result push arr[dq.front()] -> arr[1] = 3. Res=[3]
*
* j = 3 (val -3):
* arr[2]=-1 > -3. No pop back.
* push(3). dq=[1, 2, 3]
* Window [1..3]. front(1) is inside.
* j >= 2. Result push arr[1] = 3. Res=[3, 3]
*
* j = 4 (val 5):
* arr[3]=-3 <= 5. pop(3).
* arr[2]=-1 <= 5. pop(2).
* arr[1]=3 <= 5. pop(1).
* push(4). dq=[4]
* Window [2..4]. front(4) is inside.
* j >= 2. Result push arr[4] = 5. Res=[3, 3, 5]
*
* Output: [3, 3, 5]
*/

```

---

## 🔑 Key Insights

1. **Monotonic Queue**: By keeping the deque strictly decreasing, the largest element is always available in  at `dq.front()`.
2. **Useless Elements**: If `arr[x] <= arr[y]` and `x < y`, then `arr[x]` will never be the maximum of a window that includes `arr[y]` because `arr[y]` is larger and stays in the window longer. Thus, we can safely discard `arr[x]`.
3. **Indices vs Values**: Storing indices is crucial to determine when an element falls out of the sliding window (index logic `dq.front() < j - k + 1`).

---

## 🎯 Further Exploration

* **LeetCode 239**: [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) (Identical problem).
* **First negative integer**: Find the first negative integer in every window of size k.
* **Longest Subarray**: Longest subarray with max element less than K.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k3101/1)

---

## 🧑‍💻 Author

Created by [imnilesh18](https://github.com/imnilesh18)

---

<div align="center">

</div>

**Educational Purpose Only**: This repository serves as a collection of solutions to educational problems.
