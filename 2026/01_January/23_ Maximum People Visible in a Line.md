# 🧍 Maximum People Visible in a Line

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D35?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Accuracy](https://img.shields.io/badge/Accuracy-50.11%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-brightgreen?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

### ⚠️ Educational Use Only
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 🧐 Problem Statement

You are given an array `arr[]`, where `arr[i]` represents the height of the `i-th` person standing in a line.

A person `i` can see another person `j` if:
1. `height[j] < height[i]`
2. There is no person `k` standing between them such that `height[k] ≥ height[i]`.

Each person can see in both directions (front and back).

Your task is to find the **maximum number of people** that any person can see (including themselves).

### 🔢 Constraints

- `1 ≤ arr.size() ≤ 10^4`
- `1 ≤ arr[i] ≤ 10^5`

---

## 🧪 Examples

### Example 1

```bash
Input: arr[] = [6, 2, 5, 4, 5, 1, 6]
Output: 6

```

<details>
<summary>📖 Example Breakdown</summary>

* **Person 1 (height 6):** Can see indices 1 (height 2), 2 (height 5), 3 (height 4), 4 (height 5), and 6 (height 6, essentially the next boundary). Actually, the condition stops seeing when someone `>=` is met. The person at index 6 is `6` (equal), so they block further view but are the limit.
* Strictly speaking based on the logic derived: The range of visibility extends to the nearest `>=` blockers.
* Left blocker: None (index -1).
* Right blocker: Index 6 (height 6).
* Visible range includes everyone between boundaries plus self.
* Total visible: indices 0, 1, 2, 3, 4, 5. Wait, the output says 6.
* Explanation says: "Person 1 can see 2, 3, 4, 5, 6 in addition to himself". That corresponds to indices 1, 2, 3, 4, 6.
* Logic used in solution: All elements strictly between the "Previous Greater or Equal" and "Next Greater or Equal" are strictly smaller. Thus, they satisfy the visibility condition.
* Result: 6.



</details>

### Example 2

```bash
Input: arr[] = [1, 3, 6, 4]
Output: 4

```

---

## 💡 Solution Approach

### 🚀 Stack-Based Approach (Monotonic Stack)

The problem asks for the number of contiguous smaller people a person can see. A person's vision is blocked by anyone taller or of equal height. This translates to finding the **Previous Greater or Equal Element** and the **Next Greater or Equal Element** for every index.

The range between these two blockers consists entirely of people strictly shorter than the current person `i`, meaning person `i` can see everyone in this range.

1. **Previous Greater Element (PGE):** Use a stack to find the index of the nearest element to the left that is `>= arr[i]`.
2. **Next Greater Element (NGE):** Use a stack to find the index of the nearest element to the right that is `>= arr[i]`.
3. **Calculate Visibility:** For each person `i`, the number of visible people is the count of elements in the range `(prev[i], next[i])` (exclusive of boundaries, but the math simplifies to inclusive count logic for the subarray).
* Visible Count = `(next[i] - 1) - (prev[i] + 1) + 1` which simplifies to `next[i] - prev[i] - 1`.



### 💻 C++ Implementation

```cpp
// Intuition: A person can see everyone strictly smaller than them contiguously until blocked by someone >= height. This defines a range bounded by Previous Greater Element and Next Greater Element.
// Approach: Use a Monotonic Stack to find the indices of the Previous Greater Element and Next Greater Element for all indices, then calculate the range size.
// Time Complexity: O(n) - We traverse the array a constant number of times (3 passes), and stack operations are O(1) amortized.
// Space Complexity: O(n) - We use extra space for the 'prev' and 'next' vectors and the stack.

class Solution {
  public:
    // Function to compute Previous Greater Element for each index
    vector<int> previousGreater(vector<int>& arr) {
        int n = arr.size();
        vector<int> prev(n, -1); // Initialize with -1 (left boundary imaginary index)
        stack<int> st;
      
        for (int i = 0; i < n; i++) {
            // Remove smaller elements, we only care about blockers (>= current)
            while (!st.empty() && arr[st.top()] < arr[i]) {
                st.pop();
            }
            // If stack is not empty, top is the nearest element >= arr[i]
            if (!st.empty()) prev[i] = st.top();
            st.push(i);
        }
        return prev;
    }
    
    // Function to compute Next Greater Element for each index
    vector<int> nextGreater(vector<int>& arr) {
        int n = arr.size();
        vector<int> next(n, n); // Initialize with n (right boundary imaginary index)
        stack<int> st;
      
        for (int i = n - 1; i >= 0; i--) {
            // Remove smaller elements to find the blocker on the right
            while (!st.empty() && arr[st.top()] < arr[i]) {
                st.pop();
            }
            // If stack not empty, top is the nearest element >= arr[i]
            if (!st.empty()) next[i] = st.top();
            st.push(i);
        }
        return next;
    }
    
    int maxPeople(vector<int>& arr) {
        int n = arr.size();
      
        // Compute Previous Greater and Next Greater indices
        vector<int> prev = previousGreater(arr);
        vector<int> next = nextGreater(arr);
      
        int maxCount = 0;
      
        for (int i = 0; i < n; i++) {
            // Left visible boundary: just after the previous greater element
            int leftBound = (prev[i] == -1 ? 0 : prev[i] + 1);
            // Right visible boundary: just before the next greater element
            int rightBound = (next[i] == n ? n - 1 : next[i] - 1);
      
            // Range size gives how many people visible including self
            // Formula: count = end - start + 1
            int count = rightBound - leftBound + 1;
      
            maxCount = max(maxCount, count);
        }
      
        return maxCount;
    }
};

/*
*
* Dry Run
* Input: arr[] = [1, 3, 6, 4]
*
* 1. Compute Previous Greater (indices):
* i=0 (1): stack empty -> prev[0] = -1. push(0).
* i=1 (3): 3 > 1 (pop 0). stack empty -> prev[1] = -1. push(1).
* i=2 (6): 6 > 3 (pop 1). stack empty -> prev[2] = -1. push(2).
* i=3 (4): 4 < 6 (no pop). top is 2 -> prev[3] = 2. push(3).
* prev = [-1, -1, -1, 2]
*
* 2. Compute Next Greater (indices):
* i=3 (4): stack empty -> next[3] = 4. push(3).
* i=2 (6): 6 > 4 (pop 3). stack empty -> next[2] = 4. push(2).
* i=1 (3): 3 < 6. top is 2 -> next[1] = 2. push(1).
* i=0 (1): 1 < 3. top is 1 -> next[0] = 1. push(0).
* next = [1, 2, 4, 4]
*
* 3. Calculate Counts:
* i=0 (1): L=0, R=0 -> Count = 1
* i=1 (3): L=0, R=1 -> Count = 2
* i=2 (6): L=0, R=3 -> Count = 4 (Max so far)
* i=3 (4): L=3, R=3 -> Count = 1
*
* Output: 4
*/

```

---

## 🔑 Key Insights

1. **Visibility Limits:** A person's vision is limited strictly by the first person strictly taller or of equal height.
2. **Monotonic Stack:** This is the standard pattern for finding the "Next Greater" or "Previous Greater" element. It allows us to find these boundaries in linear time  instead of quadratic .
3. **Range Calculation:** Once the boundaries (blockers) are identified, everyone strictly between the blockers is strictly smaller than the current person, meaning they are all visible.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/maximum-people-visible-in-a-line/1)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

---

## 📜 License

<div align="center">

This project is licensed under the MIT License.

</div>

> **Note:** This repository is for educational purposes only. Please respect the copyright of the problem source.