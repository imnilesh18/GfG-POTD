# 🪟 Count Distinct Elements in Every Window

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-2980b9?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-distinct-elements-in-every-window/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-distinct-elements-in-every-window/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-41.83%25-green?style=for-the-badge)](https://www.geeksforgeeks.org/problems/count-distinct-elements-in-every-window/1)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/count-distinct-elements-in-every-window/1)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://github.com/imnilesh18/gfg-potd/blob/master/LICENSE)

</div>

<div align="center">
  <h3>⚠️ Educational Use Only</h3>
  <p>This repository and its content are intended solely for educational purposes.</p>
  <p>Solutions are provided for learning, practice, and reference only.</p>
  <p>Problem statement and test cases are based on the <a href="https://www.geeksforgeeks.org/problems/count-distinct-elements-in-every-window/1">GeeksforGeeks problem</a>.</p>
</div>

---

## 📝 Problem Statement

Given an integer array `arr[]` and a number `k`. Find the count of distinct elements in every window of size `k` in the array.

## 📊 Examples

### Example 1

```bash
Input: arr[] = [1, 2, 1, 3, 4, 2, 3], k = 4
Output: [3, 4, 4, 3]
Explanation:
Window 1: [1, 2, 1, 3] -> Distinct {1, 2, 3} -> Count: 3
Window 2: [2, 1, 3, 4] -> Distinct {2, 1, 3, 4} -> Count: 4
Window 3: [1, 3, 4, 2] -> Distinct {1, 3, 4, 2} -> Count: 4
Window 4: [3, 4, 2, 3] -> Distinct {3, 4, 2} -> Count: 3

```

### Example 2

```bash
Input: arr[] = [4, 1, 1], k = 2
Output: [2, 1]
Explanation:
Window 1: [4, 1] -> Distinct {4, 1} -> Count: 2
Window 2: [1, 1] -> Distinct {1} -> Count: 1

```

### Example 3

```bash
Input: arr[] = [1, 1, 1, 1, 1], k = 3
Output: [1, 1, 1]
Explanation:
Every window of size 3 contains only the element 1.
Count of distinct elements in each window is 1.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's walk through `arr = [1, 2, 1, 3, 4]`, `k = 3`.

1. **Index 0-2 (First Window)**: `[1, 2, 1]`
* Map: `{1:2, 2:1}`
* Distinct count: `2`
* Result: `[2]`


2. **Index 1-3 (Slide Right)**: Remove `arr[0]=1`, Add `arr[3]=3`
* Current window: `[2, 1, 3]`
* Map: `{1:1, 2:1, 3:1}` (Count of 1 decreased)
* Distinct count: `3`
* Result: `[2, 3]`


3. **Index 2-4 (Slide Right)**: Remove `arr[1]=2`, Add `arr[4]=4`
* Current window: `[1, 3, 4]`
* Map: `{1:1, 2:0 (removed), 3:1, 4:1}`
* Distinct count: `3`
* Result: `[2, 3, 3]`



</details>

---

## 🛑 Constraints

1 ≤ k ≤ arr.size() ≤ 10^5
1 ≤ arr[i] ≤ 10^5

---

## 💡 Solution Approaches

### Optimized Approach: Sliding Window with Hash Map

We can solve this problem efficiently using the **Sliding Window** technique combined with a **Hash Map** (or Frequency Array). The Hash Map stores the frequency of elements in the current window. As the window slides to the right:

1. **Add** the new element entering the window.
2. **Remove** the old element leaving the window.
3. The size of the Hash Map gives the count of distinct elements.

#### 💻 Code (C++)

```cpp
// Intuition: Use a sliding window to maintain element frequencies. Map size gives distinct count.
// Approach: Add current element to map. If window exceeds k, remove leftmost element (and key if count 0). Record map size when window equals k.
// Time Complexity: O(N) - Each element is added and removed from the map at most once.
// Space Complexity: O(K) - The map stores at most K distinct elements.

class Solution {
  public:
    vector<int> countDistinct(vector<int> &arr, int k) {
        int n = arr.size();
        vector<int> result;
        unordered_map<int, int> freqMap;
        
        int i = 0; // Left pointer
        int j = 0; // Right pointer (window expansion)
        
        while (j < n) {
            // 1. Expand the window
            freqMap[arr[j]]++;
            
            // 2. Shrink the window if it exceeds size k
            if (j - i + 1 > k) {
                freqMap[arr[i]]--;
                if (freqMap[arr[i]] == 0) {
                    freqMap.erase(arr[i]);
                }
                i++; // Slide the left boundary
            }
            
            // 3. Calculate the result
            // Once the window reaches size k, start recording results
            if (j - i + 1 == k) {
                result.push_back(freqMap.size());
            }
            
            j++; // Move to next element
        }
        
        return result;
    }
};

/*
*
* Dry Run
* Input: arr = [1, 2, 1, 3], k = 3
*
* Iteration 1 (j=0):
* arr[0] = 1 -> freqMap: {1:1}
* Window size < k, continue
*
* Iteration 2 (j=1):
* arr[1] = 2 -> freqMap: {1:1, 2:1}
* Window size < k, continue
*
* Iteration 3 (j=2):
* arr[2] = 1 -> freqMap: {1:2, 2:1}
* Window size == k (3) -> result.push(2) -> result: [2]
*
* Iteration 4 (j=3):
* arr[3] = 3 -> freqMap: {1:2, 2:1, 3:1}
* Window size (4) > k:
* remove arr[i=0]=1 -> freqMap: {1:1, 2:1, 3:1}
* i increments to 1
* Window size == k -> result.push(3) -> result: [2, 3]
*
* Final Output: [2, 3]
*
*/

```

---

## 🗝️ Key Insights

* **Fixed Window Size**: Since the window size `k` is constant, we don't need nested loops. A single pass (`O(N)`) suffices.
* **Frequency Map**: A simple `Set` is not enough because duplicate elements might exist within a window. We need to track counts to know exactly when an element is completely removed from the current window.
* **Map Size**: `freqMap.size()` provides the answer in `O(1)` time (effectively) or `O(K)` depending on implementation details, but for this constraint `O(N)` overall is optimal.

---

## 🚀 Further Exploration

* **Longest Substring Without Repeating Characters**: Use a variable size sliding window.
* **Subarrays with K Different Integers**: A harder variation involving counting subarrays.
* **First Negative Integer in Every Window of Size K**: Another standard sliding window problem.

---

## 📚 References

* **[GFG Problem Link](https://www.geeksforgeeks.org/problems/count-distinct-elements-in-every-window/1)**
* **[Sliding Window Pattern](https://www.geeksforgeeks.org/window-sliding-technique/)**

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`sliding-window` `hash-map` `array` `two-pointers` `geeksforgeeks` `cpp`

---

## 📜 License

<div align="center">

</div>

**⚠️ Educational Use Only**

This repository is intended for educational purposes only. Please use the solution for learning and practice.
