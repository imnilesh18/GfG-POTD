# 🟧 Next element with greater frequency

<div align="center">

[![Status](https://img.shields.io/badge/Status-Active-success?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/next-element-with-greater-frequency--170637/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/next-element-with-greater-frequency--170637/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-60.4%25-blue?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/next-element-with-greater-frequency--170637/1)
[![Points](https://img.shields.io/badge/Points-4-green?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/next-element-with-greater-frequency--170637/1)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

---

### ⚠️ Educational Use Only

> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

Given an array `arr[]` of integers, for each element, find the **first element to its right** that has a **higher frequency** than the current element.
If no such element exists, return `-1` for that position.

---

## 🔍 Examples

### Example 1

```text
Input: arr[] = [2, 1, 1, 3, 2, 1]
Output: [1, -1, -1, 2, 1, -1]

```

<details>
<summary>📖 Example Breakdown</summary>

- **Frequencies:**
- `1`: 3 times
- `2`: 2 times
- `3`: 1 time

- **Traversal:**
- `arr[0] = 2` (freq 2): Next element to right with freq > 2 is `1` (freq 3). Result: `1`.
- `arr[1] = 1` (freq 3): No element to right has freq > 3. Result: `-1`.
- `arr[2] = 1` (freq 3): No element to right has freq > 3. Result: `-1`.
- `arr[3] = 3` (freq 1): Next element `2` has freq 2 > 1. Result: `2`.
- `arr[4] = 2` (freq 2): Next element `1` has freq 3 > 2. Result: `1`.
- `arr[5] = 1` (freq 3): End of array. Result: `-1`.

</details>

### Example 2

```text
Input: arr[] = [5, 1, 5, 6, 6]
Output: [-1, 5, -1, -1, -1]

```

---

## 🛑 Constraints

- `1 ≤ arr.size() ≤ 10^5`
- `1 ≤ arr[i] ≤ 10^5`

---

## 💡 Solution Approaches

### 1️⃣ Monotonic Stack (Frequency Based)

#### Intuition

This problem is a variation of the "Next Greater Element" pattern. Instead of comparing the values of the elements themselves, we compare their **frequencies**. We can pre-calculate frequencies using a hash map and then use a stack to maintain indices of elements for which we haven't found a "next greater frequency" element yet.

#### Approach

1. **Frequency Count**: Iterate through the array and count the frequency of each number using a hash map.
2. **Stack Traversal**: Use a stack to store indices of elements.
3. **Resolve Stack**: Iterate through the array again. For each element `arr[i]`:

- While the stack is not empty and the frequency of the current element `arr[i]` is greater than the frequency of the element at the index on top of the stack (`arr[st.top()]`), it means `arr[i]` is the "next greater frequency" element for `arr[st.top()]`.
- Pop the index from the stack and update the result array.

4. **Push Index**: Push the current index `i` onto the stack to find its next greater frequency element later.
5. **Remaining Elements**: Any indices left in the stack have no such element to their right, so they remain `-1` (default initialization).

#### Code

```cpp
// Intuition: Use a hash map to store frequencies and a monotonic stack to find the next element with a strictly greater frequency.
// Approach: First count frequencies. Then iterate through the array, maintaining a stack of indices. If current element's freq > top element's freq, pop stack and update result.
// Time Complexity: O(N) - We iterate through the array twice (once for freq map, once for logic), and each element is pushed/popped at most once.
// Space Complexity: O(N) - For the frequency map and the stack.

class Solution {
  public:
    vector<int> nextFreqGreater(vector<int>& arr) {
        int n = arr.size();
        vector<int> result(n, -1);
        unordered_map<int,int> freq;
        for (int x : arr) freq[x]++;

        stack<int> st;                                  // will hold indices

        // traverse from left to right
        for (int i = 0; i < n; i++) {
            // resolve any stack tops whose freq < current freq
            while (!st.empty() && freq[arr[i]] > freq[arr[st.top()]]) {
                result[st.top()] = arr[i];
                st.pop();
            }
            st.push(i);
        }
        return result;
    }
};

/*
*
* Dry Run
* Input: arr = [2, 1, 1, 3]
* Frequencies: {2:1, 1:2, 3:1}
* * i = 0, arr[0] = 2 (freq 1):
* Stack empty.
* Push 0. Stack: [0]
*
* i = 1, arr[1] = 1 (freq 2):
* Top is 0 (arr[0]=2, freq 1).
* freq[1] (2) > freq[2] (1) -> True.
* result[0] = 1. Pop 0.
* Push 1. Stack: [1]
*
* i = 2, arr[2] = 1 (freq 2):
* Top is 1 (arr[1]=1, freq 2).
* freq[1] (2) > freq[1] (2) -> False.
* Push 2. Stack: [1, 2]
*
* i = 3, arr[3] = 3 (freq 1):
* Top is 2 (arr[2]=1, freq 2).
* freq[3] (1) > freq[1] (2) -> False.
* Push 3. Stack: [1, 2, 3]
*
* End loop.
* Result: [1, -1, -1, -1]
*
*/

```

---

## 🔑 Key Insights

- **Separation of Concerns**: The problem effectively asks for NGE (Next Greater Element), but the metric for comparison is stored externally (in the `freq` map) rather than the element's direct value.
- **Monotonic Stack Property**: The stack maintains indices such that the frequencies of corresponding elements are non-increasing. When we encounter an element with a higher frequency, it violates this property for the stack top, triggering an update.
- **Handling Duplicates**: Since we store indices in the stack, duplicate values in the array are handled correctly based on their specific positions.

---

## 🚀 Further Exploration

- **Next Greater Element I/II**: The classic version comparing values.
- **Daily Temperatures**: Finds the number of days until a warmer temperature.
- **Stock Span Problem**: Finds consecutive days with lower price.

---

## 🔗 References

- [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/next-element-with-greater-frequency--170637/1)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
- `Hash`
- `Stack`
- `Data Structures`
---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

---

<div align="center">
<b>⚠️ Educational Purpose Only</b>
<i>This repository is strictly for learning and practice.</i>
</div>
