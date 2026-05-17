# 🌻 Make the Array Beautiful

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/make-the-array-beautiful--170647/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty - Easy" />
  <img src="https://img.shields.io/badge/Accuracy-49.96%25-blue?style=for-the-badge" alt="Accuracy - 49.96%" />
  <img src="https://img.shields.io/badge/Points-2-blue?style=for-the-badge" alt="Points - 2" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge" alt="License: MIT" />
  </a>
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> The problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) platform.

---

## 📝 Problem Statement

Given an array of negative and non-negative integers, your task is to make the array **beautiful**. 

An array is considered beautiful if two adjacent integers, `arr[i]` and `arr[i+1]`, have the **same sign** (i.e., both are negative or both are positive/zero). You can perform the following operation any number of times until the array becomes beautiful:
* If two adjacent elements have different signs (one is negative and the other is positive), **remove them**.

Return the beautiful array after performing the above operations. Scan the array from **left to right** for removing adjacent elements to ensure consistency with test cases. An empty array is also considered a beautiful array.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [4, 2, -2, 1]
Output: [4, 1]
Explanation: At indices 1 and 2, the elements 2 and -2 have different signs, so they are removed. The final beautiful array is [4, 1].

```

### Example 2

```text
Input: arr[] = [2, -2, -1, 1]
Output: []
Explanation: 
1. At indices 0 and 1, the elements 2 and -2 have different signs, so they are removed. The array becomes [-1, 1].
2. Now, -1 and 1 also have different signs, so they are removed. The final array is empty.

```

Let's walk through another array: `[2, 1, -1, -2, 3]`

1. **Start** with an empty result stack: `[]`
2. **Read `2**`: Stack is empty. Push `2`. Stack: `[2]`
3. **Read `1**`: Top of stack is `2` (positive). `1` is positive. Signs match. Push `1`. Stack: `[2, 1]`
4. **Read `-1**`: Top of stack is `1` (positive). `-1` is negative. Signs differ! Pop the top. Stack: `[2]`
5. **Read `-2**`: Top of stack is `2` (positive). `-2` is negative. Signs differ! Pop the top. Stack: `[]`
6. **Read `3**`: Stack is empty. Push `3`. Stack: `[3]`

**Result**: `[3]`

---

## ⚠️ Constraints

> * $1 \le arr.size() \le 10^5$
> * $-10^5 \le arr[i] \le 10^5$
> 
> 

---

## 🚀 Solution Approaches

### 1. Optimized Approach (Stack / Vector Simulation)

**Summary / Intuition:**
Since adjacent elements of opposite signs cancel each other out sequentially (like a chain reaction), this perfectly mirrors a Last-In-First-Out (LIFO) pattern. Using a stack (or a dynamic array like a `vector` to easily return the final result) efficiently handles these cascading removals without having to re-evaluate the whole array.

#### C++ Code

```cpp
// Intuition: Adjacent elements of opposite signs cancel each other out, which perfectly matches a Last-In-First-Out (LIFO) pattern. A stack efficiently handles these cascading removals.
// Approach: Simulate a stack using a vector. Iterate through the array from left to right. If the stack is empty or the current element shares the same sign as the stack's top (treating >= 0 as positive), push the element. If they have opposite signs, pop the top element. Return the stack.
// Time Complexity: O(N) where N is the size of the array since we traverse the array once and vector push/pop operations take O(1) time.
// Space Complexity: O(N) in the worst case if all elements have the same sign and get pushed to our simulated stack.

class Solution {
  public:
    vector<int> makeBeautiful(vector<int> arr) {
        // vector used to simulate stack behavior and store final result
        vector<int> st;
        
        for (int num : arr) {
            // push immediately if stack is empty
            if (st.empty()) {
                st.push_back(num);
            } else {
                int top = st.back();
                
                // check for opposite signs (0 is treated as positive)
                if ((top >= 0 && num < 0) || (top < 0 && num >= 0)) {
                    st.pop_back(); // opposite signs destroy each other
                } else {
                    st.push_back(num); // signs match, push to stack
                }
            }
        }
        
        return st;
    }
};

/*
*
* Dry Run
*
* Input: arr = [2, 1, -1, -2, 3]
* Initialize st = []
* 
* Step 1 (Element 2): st is empty, Action: Push 2, st = [2]
* Step 2 (Element 1): Top is 2 (+), Current is 1 (+), Signs match, Action: Push 1, st = [2, 1]
* Step 3 (Element -1): Top is 1 (+), Current is -1 (-), Opposite signs, Action: Pop the top element (1), st = [2]
* Step 4 (Element -2): Top is 2 (+), Current is -2 (-), Opposite signs, Action: Pop the top element (2), st = []
* Step 5 (Element 3): st is empty, Action: Push 3, st = [3]
* 
* Final Output: The remaining elements in the stack form the beautiful array: [3]
*/

```

---

## 🧠 Key Insights

* **LIFO Structure:** The problem is a classic variation of the "Valid Parentheses" or "Asteroid Collision" string/array reduction problems. The most recently added element is the first one to be compared and potentially removed, making the Stack data structure the optimal choice.
* **Vector over `std::stack`:** By simulating the stack directly with a `vector<int>`, we avoid the $O(N)$ overhead of popping elements out of a standard stack to reverse and build the final array.
* **Zero Handling:** Zero must be treated as a positive integer per the problem description (i.e., `0` and `5` have the same sign, but `0` and `-2` do not). The logic `(top >= 0 && num < 0)` elegantly handles this.

---

## 🔍 Further Exploration

If you enjoyed this problem, you might want to try these related concepts:

* **Asteroid Collision** (Similar stack-based elimination logic)
* **Valid Parentheses** (Classic LIFO string manipulation)
* **Remove All Adjacent Duplicates In String**

---

## 🔗 References

* **Original Problem:** [GeeksforGeeks - Make the array beautiful](https://www.geeksforgeeks.org/problems/make-the-array-beautiful--170647/1)

---

## 👨‍💻 Author

**Nilesh**

GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Arrays` `Stack` `Data Structures` `GeeksforGeeks` `C++`