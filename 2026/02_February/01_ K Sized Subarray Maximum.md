# 🟧 K Sized Subarray Maximum

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-K_Sized_Subarray_Maximum-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Accuracy](https://img.shields.io/badge/Accuracy-26.04%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

<div align="center">
  <h3>⚠️ Educational Use Only</h3>
  <p>This repository and its content are intended solely for educational purposes.</p>
  <p>Solutions are provided for learning, practice, and reference only.</p>
  <p>Problem statement and test cases are based on the <a href="https://www.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k3101/1">GeeksforGeeks problem</a>.</p>
</div>

---

## 🧐 Problem Statement

Given an array `arr[]` of positive integers and an integer `k`. You have to find the **maximum value** for each contiguous subarray of size `k`. Return an array of maximum values corresponding to each contiguous subarray.

### 📉 Constraints

- `1 ≤ arr.size() ≤ 10^6`
- `1 ≤ k ≤ arr.size()`
- `0 ≤ arr[i] ≤ 10^9`

---

## 📂 Examples

### Example 1

```bash
Input: arr[] = [1, 2, 3, 1, 4, 5, 2, 3, 6], k = 3
Output: [3, 3, 4, 5, 5, 5, 6]

```

<details>
<summary>📖 Example Breakdown</summary>

1. **Subarray 1**: `[1, 2, 3]` -> Max is **3**
2. **Subarray 2**: `[2, 3, 1]` -> Max is **3**
3. **Subarray 3**: `[3, 1, 4]` -> Max is **4**
4. **Subarray 4**: `[1, 4, 5]` -> Max is **5**
5. **Subarray 5**: `[4, 5, 2]` -> Max is **5**
6. **Subarray 6**: `[5, 2, 3]` -> Max is **5**
7. **Subarray 7**: `[2, 3, 6]` -> Max is **6**

**Result**: `[3, 3, 4, 5, 5, 5, 6]`

</details>

### Example 2

```bash
Input: arr[] = [5, 1, 3, 4, 2], k = 1
Output: [5, 1, 3, 4, 2]
Explanation: When k = 1, each element in the array is its own subarray, so the output is simply the same array.

```

---

## 💡 Solution Approaches

### 1️⃣ Optimized Approach: Monotonic Deque (Sliding Window)

#### Intuition

To find the maximum in a sliding window efficiently, we need a data structure that gives us the max in  and handles updates in  amortized time. A **Monotonic Decreasing Deque** is perfect for this. It stores indices such that the values corresponding to these indices are in decreasing order. The front of the deque always holds the index of the maximum element for the current window.

#### Approach

1. **Maintain Decreasing Order**: Before adding a new element's index, remove all indices from the back of the deque whose values are less than or equal to the current element. These removed elements can never be the maximum because the current element is larger and appears later (stays in the window longer).
2. **Add Current Index**: Push the current index `j` to the back.
3. **Handle Window Bounds**: Remove the front index if it has fallen out of the current window `[j - k + 1, j]`.
4. **Store Result**: Once the first window is formed (i.e., `j >= k - 1`), the element at `arr[dq.front()]` is the maximum for the current window.

```cpp
// Intuition: Use a Deque to maintain indices of useful elements in decreasing order. The front is always the max of the current window.
// Approach: Sliding Window with Monotonic Deque. Remove smaller elements from back, remove outdated index from front.
// Time Complexity: O(N) - Each element is pushed and popped from the deque at most once.
// Space Complexity: O(K) - The deque stores at most K indices.

class Solution {
  public:
    vector<int> maxOfSubarrays(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> result;
        deque<int> dq; // Stores INDICES
        
        for (int j = 0; j < n; j++) {
            
            // 1. Remove elements from back that are smaller than current element
            // (Current element is larger and appears later, so previous smaller ones are useless)
            while (!dq.empty() && arr[dq.back()] <= arr[j]) {
                dq.pop_back();
            }
            
            // 2. Add current element's index to the back
            dq.push_back(j);
            
            // 3. Remove the front if it's out of the current window
            // Window range is [j-k+1 ... j]. If index < start of window, remove it.
            if (dq.front() < j - k + 1) {
                dq.pop_front();
            }
            
            // 4. Store result (start adding once we hit the first full window of size k)
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
* Input: arr = [1, 2, 3, 1], k = 3
*
* j=0 (val=1): dq=[0]
* j=1 (val=2): 1 < 2 -> pop 0. push 1. dq=[1(2)]
* j=2 (val=3): 2 < 3 -> pop 1. push 2. dq=[2(3)]. Window [0..2]. Max is arr[dq.front()] -> arr[2]=3. Res=[3]
* j=3 (val=1): 1 <= 1 (false). push 3. dq=[2(3), 3(1)]. Front 2 is in window [1..3]. Max is arr[2]=3. Res=[3, 3]
*
* Final Output: [3, 3]
*/

```

---

## 🗝️ Key Insights

* **Monotonic Property**: By ensuring the deque is strictly decreasing by value, `dq.front()` is always the maximum.
* **Index Tracking**: Storing indices instead of values is crucial to correctly identify and remove elements that slide out of the window (`j - k + 1`).
* **Efficiency**: Even though there is a `while` loop, each element enters the deque once and leaves once, ensuring linear time complexity .

---

## 🚀 Further Exploration

* **Sliding Window Minimum**: Similar logic but maintain a monotonic increasing deque.
* **K-th Largest in Window**: Requires more complex structures like a multiset or two heaps.
* **Longest Subarray with Limit**: Finding the longest subarray where the absolute difference between any two elements is  limit.

---

## 🔗 References

* [Original Problem on GeeksforGeeks](https://www.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k3101/1)
* [GeeksforGeeks Sliding Window Technique](https://www.geeksforgeeks.org/window-sliding-technique/)

---

## 🙋 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

<div align="center">
<img src="https://www.google.com/search?q=https://img.shields.io/badge/License-MIT-yellow.svg" alt="MIT License">
<p>This project is licensed under the MIT License.</p>
<p>⚠️ <strong>Educational Use Only</strong>: Solutions are for learning and reference.</p>
</div>
