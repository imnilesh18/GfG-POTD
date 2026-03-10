# 📉 Subarrays with First Element Minimum

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/subarrays-with-first-element-minimum/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
    <img src="https://img.shields.io/badge/Accuracy-74.69%25-green?style=for-the-badge" alt="Accuracy" />
    <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

---

### ⚠️ Educational Use Only:
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

You are given an integer array `arr[]`. Your task is to **count** the number of subarrays where the first element is the **minimum element** of that subarray.

**Note:** A subarray is valid if its first element is not greater than any other element in that subarray.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [1, 2, 1]
Output: 5
Explanation:
All possible subarrays are:
[1], [1, 2], [1, 2, 1], [2], [2, 1], [1]

Valid subarrays are:
[1], [1, 2], [1, 2, 1], [2], [1] -> total 5
```

### Example 2
```text
Input: arr[] = [1, 3, 5, 2]
Output: 8
Explanation:
Valid subarrays are: 
[1], [1, 3], [1, 3, 5], [1, 3, 5, 2], [3], [3, 5], [5], [2] -> total 8
```

<details>
<summary>📖 <b>Example Breakdown (Input 1)</b></summary>

Let's break down `arr[] = [1, 2, 1]`:
- Starting at index `0` (val `1`): It is the minimum for subarrays `[1]`, `[1, 2]`, and `[1, 2, 1]`. Count = 3.
- Starting at index `1` (val `2`): It is the minimum for subarray `[2]`. If we take `[2, 1]`, `2` is not the minimum. Count = 1.
- Starting at index `2` (val `1`): It is the minimum for subarray `[1]`. Count = 1.
- **Total Valid Subarrays** = 3 + 1 + 1 = 5.

</details>

---

## ⚠️ Constraints

- $1 \le arr.size() \le 5 \times 10^4$
- $1 \le arr[i] \le 10^5$

---

## 🛠️ Solution Approaches

### Monotonic Stack (Optimized)

The most efficient way to solve this is to find the **Next Smaller Element** on the right for every index. If an element at index `i` is chosen as the start of a subarray, it will remain the minimum element of that subarray as long as we do not encounter an element strictly smaller than it. Thus, the valid subarray can extend up to index `j - 1`, where `j` is the index of the next strictly smaller element. The number of valid subarrays starting at `i` is exactly `(j - i)`.

```cpp
// Intuition: For an element at index i to be the minimum in a subarray starting at i, the subarray can only extend to the right up to (but not including) the next smaller element. Thus, finding the next smaller element on the right gives us the valid range for each starting index.
// Approach: Traverse from right to left. Maintain a monotonic stack of indices representing elements strictly smaller than the current elements. For each element, pop from stack until a smaller element is found. The valid subarrays starting at i are bounded by the top of the stack. Accumulate these counts.
// Time Complexity: O(n), where n is the size of the array. Each element is pushed and popped at most once.
// Space Complexity: O(n), in the worst case (e.g., strictly increasing array), the stack stores all n indices.

class Solution {
  public:
    int countSubarrays(vector<int>& arr){

        stack<int> st; // Stores indices to find the next smaller element
        int ans = 0;
        int n = arr.size();
    
        // Traverse the array from right to left
        for (int i = n - 1; i >= 0; i--) {
            // Pop elements that are greater than or equal to current element
            while (!st.empty() and arr[st.top()] >= arr[i])
                st.pop();
                
            // The index of next strictly smaller element
            // starting from i'th index. If none, bounded by n.
            int last = (st.empty() ? n : st.top());
    
            // Adding the number of subarrays which
            // can be formed in the valid range [i, last - 1]
            ans += (last - i);
            
            // Push current index to stack for future elements
            st.push(i);
        }
        return ans;
    }
};

/*
*
* Dry Run
*
* Input: arr = [1, 2, 1]
* n = 3, stack = empty, ans = 0
*
* Iteration 1 (i = 2): arr[2] = 1
* Stack is empty.
* last = n = 3
* ans = ans + (last - i) = 0 + (3 - 2) = 1
* Push index 2 to stack. Stack: [2]
*
* Iteration 2 (i = 1): arr[1] = 2
* arr[stack.top()] -> arr[2] = 1. Since 1 >= 2 is false, loop breaks.
* last = stack.top() = 2
* ans = ans + (last - i) = 1 + (2 - 1) = 2
* Push index 1 to stack. Stack: [2, 1]
*
* Iteration 3 (i = 0): arr[0] = 1
* arr[stack.top()] -> arr[1] = 2. 2 >= 1 is true, pop stack. Stack: [2]
* arr[stack.top()] -> arr[2] = 1. 1 >= 1 is true, pop stack. Stack: empty
* Stack is empty.
* last = n = 3
* ans = ans + (last - i) = 2 + (3 - 0) = 5
* Push index 0 to stack. Stack: [0]
*
* Final Answer: 5
*
*/
```

---

## 🧠 Key Insights

- The condition "first element is the minimum" implies that as long as subsequent elements are $\ge arr[i]$, the subarray remains valid.
- We utilize a **Monotonic Increasing Stack** to keep track of indices. Traversing backwards allows us to easily find the first index on the right that violates the condition (i.e., is strictly less than $arr[i]$).
- Once we identify the boundary index `last` where $arr[last] < arr[i]$, the number of valid subarrays beginning at index `i` is mathematically equivalent to `last - i`.

---

## 🚀 Further Exploration

- [Next Greater Element](https://www.geeksforgeeks.org/next-greater-element/)
- [Largest Rectangle in Histogram](https://www.geeksforgeeks.org/largest-rectangle-under-histogram/)
- [Sum of Subarray Minimums](https://www.geeksforgeeks.org/sum-of-subarray-minimums/)

---

## 🔗 References

- **GeeksforGeeks Problem:** [Subarrays with First Element Minimum](https://www.geeksforgeeks.org/problems/subarrays-with-first-element-minimum/1)

---

## 👨‍💻 Author

Created and maintained by [imnilesh18](https://github.com/imnilesh18).

---

## 🏷️ Tags

`Stack` `Arrays` `Data Structures` `GeeksforGeeks` `Monotonic Stack`