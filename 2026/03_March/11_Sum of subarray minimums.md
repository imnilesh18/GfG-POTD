# 🟧 Sum of Subarray Minimums

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/sum-of-subarray-minimum/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty Medium" />
    <img src="https://img.shields.io/badge/Accuracy-46.92%25-green?style=for-the-badge" alt="Accuracy 46.92%" />
    <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points 4" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` of positive integers, find the **total sum** of the **minimum elements** of every possible subarrays.

**Note:** It is guaranteed that the total sum will fit within a 32-bit unsigned integer.

---

## 💡 Examples

**Example 1:**
```text
Input: arr[] = [10, 20]
Output: 40
Explanation: Subarrays are [10], [20], [10, 20]. Minimums are 10, 20, 10.
Sum of all these is 40.
```

**Example 2:**
```text
Input: arr[] = [1, 2, 3, 4]
Output: 20
Explanation: Subarrays are [1], [2], [3], [4], [1, 2], [1, 2, 3], [1, 2, 3, 4], [2, 3], [2, 3, 4], [3, 4]. Minimums are 1, 2, 3, 4, 1, 1, 1, 2, 2, 3.
Sum of all these is 20.
```

<details>
<summary>📖 Example Breakdown</summary>

**Detailed walkthrough for `arr = [3, 1, 2, 4]`:**

1. **Subarrays of length 1:** `[3], [1], [2], [4]` 
   * Minimums: `3, 1, 2, 4`
2. **Subarrays of length 2:** `[3, 1], [1, 2], [2, 4]`
   * Minimums: `1, 1, 2`
3. **Subarrays of length 3:** `[3, 1, 2], [1, 2, 4]`
   * Minimums: `1, 1`
4. **Subarrays of length 4:** `[3, 1, 2, 4]`
   * Minimums: `1`

**Total Sum:** `3 + 1 + 2 + 4 + 1 + 1 + 2 + 1 + 1 + 1 = 17`
</details>

---

## ⚙️ Constraints

> - $1 \le \text{arr.size()} \le 3 \times 10^4$
> - $1 \le \text{arr[i]} \le 10^3$

---

## 🧠 Solution Approaches

### 1️⃣ Brute Force Approach

**Brief Summary/Intuition:**
Generate all possible subarrays, keep track of the minimum element in each subarray, and keep accumulating these minimums to our total sum.

```cpp
// Intuition: Iterating through all possible subarrays and tracking the minimum element for each.
// Approach: Use two nested loops to represent the start and end of subarrays, maintaining a running minimum and accumulating it to the result.
// Time Complexity: O(n^2) - due to the nested loops going over start and end indices of all subarrays.
// Space Complexity: O(1) - uses only a few integer variables regardless of input size.

class Solution {
public:
    int sumSubMins(vector<int>& arr) {
        int n      = arr.size();      // total number of elements in the array
        int result = 0;               // accumulator for sum of subarray minimums

        // iterate over all possible starting points of subarrays
        for (int i = 0; i < n; i++) {
            int mini = arr[i];        // initialize minimum to the first element of the subarray
            
            // extend the subarray one element at a time
            for (int j = i; j < n; j++) {
                // update the minimum for the current subarray [i..j]
                mini = min(mini, arr[j]);

                // add the current minimum to the result
                result += mini;
            }
        }
        return result;                // return the total sum
    }
};

/*
 * Dry Run
 *
 * Input: arr[] = [3, 1, 2, 4]
 * Output: 17
 *
 * i = 0:
 * mini = arr[0] = 3
 * j = 0: mini = min(3, arr[0]=3) = 3, result += 3         => result = 3
 * j = 1: mini = min(3, arr[1]=1) = 1, result += 1         => result = 4
 * j = 2: mini = min(1, arr[2]=2) = 1, result += 1         => result = 5
 * j = 3: mini = min(1, arr[3]=4) = 1, result += 1         => result = 6
 *
 * i = 1:
 * mini = arr[1] = 1
 * j = 1: mini = min(1, arr[1]=1) = 1, result += 1         => result = 7
 * j = 2: mini = min(1, arr[2]=2) = 1, result += 1         => result = 8
 * j = 3: mini = min(1, arr[3]=4) = 1, result += 1         => result = 9
 *
 * i = 2:
 * mini = arr[2] = 2
 * j = 2: mini = min(2, arr[2]=2) = 2, result += 2         => result = 11
 * j = 3: mini = min(2, arr[3]=4) = 2, result += 2         => result = 13
 *
 * i = 3:
 * mini = arr[3] = 4
 * j = 3: mini = min(4, arr[3]=4) = 4, result += 4         => result = 17
 *
 * Final result = 17
 */
```

---

### 2️⃣ Optimized Approach: Contribution Technique using Monotonic Stack

**Brief Summary/Intuition:**
Instead of looking at each subarray, we figure out in how many subarrays each element `arr[i]` serves as the minimum. To do this, we find the **Next Smaller Element to the Left (NSL)** and the **Next Smaller Element to the Right (NSR)**. The total contribution of `arr[i]` will be `arr[i] * (number of sub-arrays where it is the minimum)`.

```java
// Intuition: Calculate the total contribution of each element to the final answer. An element is the minimum in subarrays extending up to its Next Smaller to Left (NSL) and Next Smaller to Right (NSR).
// Approach: Precompute NSL and NSR arrays using a Monotonic Stack. Then for each element, calculate the number of subarrays where it's the minimum as `(i - NSL) * (NSR - i)`, and add `arr[i] * (leftCount) * (rightCount)` to the sum.
// Time Complexity: O(n) - each element is pushed and popped from the monotonic stack at most once.
// Space Complexity: O(n) - required for storing the NSL, NSR arrays, and the stack.

import java.util.*;

class Solution {
    public int[] getNSL(int[] arr, int n) {
        int[] result = new int[n];
        Deque<Integer> st = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            // pop until you find a smaller element or stack becomes empty
            // using >= prevents duplicate elements from being counted multiple times
            while (!st.isEmpty() && arr[st.peek()] >= arr[i]) {
                st.pop();
            }
            // if empty, no smaller to left; else top of stack is NSL
            result[i] = st.isEmpty() ? -1 : st.peek();
            st.push(i);
        }
        return result;
    }

    public int[] getNSR(int[] arr, int n) {
        int[] result = new int[n];
        Deque<Integer> st = new ArrayDeque<>();

        for (int i = n - 1; i >= 0; i--) {
            // pop until you find a strictly smaller element or stack becomes empty
            while (!st.isEmpty() && arr[st.peek()] > arr[i]) {
                st.pop();
            }
            // if empty, no smaller to right; else top of stack is NSR
            result[i] = st.isEmpty() ? n : st.peek();
            st.push(i);
        }
        return result;
    }

    public int sumSubMins(int[] arr) {
        int n = arr.length;
        int[] NSL = getNSL(arr, n);
        int[] NSR = getNSR(arr, n);

        int sum = 0;

        for (int i = 0; i < n; i++) {
            // distance to previous smaller on left
            int leftD = i - NSL[i];
            
            // distance to next smaller on right
            int rightD = NSR[i] - i;
            
            // each element contributes arr[i] * leftD * rightD
            sum += arr[i] * leftD * rightD;
        }
        return sum;
    }
}

/*
 * Dry Run
 *
 * Input: arr[] = [3, 1, 2, 4]
 * Output: 17
 *
 * Compute NSL:
 * i=0: stack empty ⇒ NSL[0]=-1, push 0
 * i=1: pop 0 (3>=1), stack empty ⇒ NSL[1]=-1, push 1
 * i=2: arr[stack.peek()]=1 < 2 ⇒ NSL[2]=1, push 2
 * i=3: arr[stack.peek()]=2 < 4 ⇒ NSL[3]=2, push 3
 * NSL = [-1, -1, 1, 2]
 *
 * Compute NSR:
 * i=3: stack empty ⇒ NSR[3]=4, push 3
 * i=2: pop 3 (4>2), stack empty ⇒ NSR[2]=4, push 2
 * i=1: pop 2 (2>1), stack empty ⇒ NSR[1]=4, push 1
 * i=0: arr[stack.peek()]=1 < 3 ⇒ NSR[0]=1, push 0
 * NSR = [1, 4, 4, 4]
 *
 * Contributions:
 * i=0: leftD=1, rightD=1 ⇒ 3 * 1 * 1 = 3  ⇒ sum=3
 * i=1: leftD=2, rightD=3 ⇒ 1 * 2 * 3 = 6  ⇒ sum=9
 * i=2: leftD=1, rightD=2 ⇒ 2 * 1 * 2 = 4  ⇒ sum=13
 * i=3: leftD=1, rightD=1 ⇒ 4 * 1 * 1 = 4  ⇒ sum=17
 *
 * Final result = 17
 */
```

---

## 🔑 Key Insights

1. **Contribution over Iteration:** Instead of generating subarrays and finding their minimums, calculating how many times an element acts as the minimum drastically drops the complexity.
2. **Monotonic Stack Magic:** Finding the next smaller/greater elements to the left/right typically takes $O(N^2)$ with brute force, but Monotonic Stack reduces this to $O(N)$.
3. **Handling Duplicates elegantly:** When dealing with duplicate values, using `>=` for calculating `NSL` and `>` for `NSR` ensures we do not over-count the subarrays containing the duplicate elements!

---

## 🔍 Further Exploration

- [Next Greater Element](https://www.geeksforgeeks.org/problems/next-larger-element-1587115620/1)
- [Largest Rectangle in Histogram](https://www.geeksforgeeks.org/problems/maximum-rectangular-area-in-a-histogram-1587115620/1)
- **Sum of Subarray Ranges** (LeetCode 2104)

---

## 📚 References

- [Original Problem on GeeksforGeeks](https://www.geeksforgeeks.org/problems/sum-of-subarray-minimum/1)
- [Monotonic Stack concepts](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

<p>
  <img src="https://img.shields.io/badge/Array-000000?style=for-the-badge&logo=matrix&logoColor=white" alt="Array" />
  <img src="https://img.shields.io/badge/Stack-FF4B4B?style=for-the-badge&logo=stackexchange&logoColor=white" alt="Stack" />
  <img src="https://img.shields.io/badge/Monotonic_Stack-4B0082?style=for-the-badge&logo=stack&logoColor=white" alt="Monotonic Stack" />
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
</p>