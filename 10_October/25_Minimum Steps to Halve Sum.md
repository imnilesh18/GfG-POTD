# 📉 Minimum Steps to Halve Sum

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-green?style=flat&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/minimum-steps-to-halve-sum/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=flat)
![Accuracy](https://img.shields.io/badge/Accuracy-57.08%25-blue?style=flat)
![Points](https://img.shields.io/badge/Points-4-orange?style=flat)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

---

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/minimum-steps-to-halve-sum/1).

---

## 📝 Problem Statement

Given an array `arr[]` of positive integers, find the **minimum** number of operations required to make the sum of its elements less than or equal to **half** of the original sum.

In one operation, you may replace any element with **half** of its value (using **floating-point** precision).

---

## 🧪 Examples

**Example 1:**

```plaintext
Input: arr[] = [8, 6, 2]
Output: 3
Explanation:
Initial sum = (8 + 6 + 2) = 16, Target half = 8
Operation 1: Halve 8 → arr becomes [4, 6, 2], Current sum = 12 (12 > 8)
Operation 2: Halve 6 → arr becomes [4, 3, 2], Current sum = 9 (9 > 8)
Operation 3: Halve 4 → arr becomes [2, 3, 2], Current sum = 7 (7 <= 8)
Minimum operations = 3.
```

<details>
<summary>📖 Example 1 Breakdown</summary>

1.  **Initial State:** `arr = [8, 6, 2]`, `sum = 16`, `target = 16 / 2 = 8`, `ops = 0`.
2.  **Goal:** Reduce `sum` to be `<= 8`.
3.  **Strategy:** Always halve the largest element to reduce the sum most effectively.
4.  **Step 1:**
    - Largest element is 8.
    - Halve it: `8 / 2 = 4`.
    - New array state (conceptually): `[4, 6, 2]`.
    - New sum: `sum = 16 - (8 / 2) = 16 - 4 = 12`.
    - Increment operations: `ops = 1`.
    - Check: `12 > 8`. Continue.
5.  **Step 2:**
    - Largest element is now 6.
    - Halve it: `6 / 2 = 3`.
    - New array state (conceptually): `[4, 3, 2]`.
    - New sum: `sum = 12 - (6 / 2) = 12 - 3 = 9`.
    - Increment operations: `ops = 2`.
    - Check: `9 > 8`. Continue.
6.  **Step 3:**
    - Largest element is now 4.
    - Halve it: `4 / 2 = 2`.
    - New array state (conceptually): `[2, 3, 2]`.
    - New sum: `sum = 9 - (4 / 2) = 9 - 2 = 7`.
    - Increment operations: `ops = 3`.
    - Check: `7 <= 8`. Stop.
7.  **Result:** Minimum operations required is 3.

</details>

**Example 2:**

```plaintext
Input: arr[] = [9, 1, 2]
Output: 2
Explanation:
Initial sum = 12, Target half = 6
Operation 1: Halve 9 → arr becomes [4.5, 1, 2], Current sum = 7.5 (7.5 > 6)
Operation 2: Halve 4.5 → arr becomes [2.25, 1, 2], Current sum = 5.25 (5.25 <= 6)
Minimum operations = 2.
```

---

## 🚦 Constraints

```plaintext
1 ≤ arr.size() ≤ 10^5
0 ≤ arr[i] ≤ 10^4
```

---

## 💡 Solution Approaches

### Optimized Approach (Max-Heap / Priority Queue)

**Intuition:**
To reduce the sum to its half in the minimum number of steps, we should greedily reduce the largest element in the array at each step. Halving the largest element provides the maximum possible reduction in the sum per operation. A max-heap (priority queue) is the ideal data structure to efficiently find and update the largest element.

**Code (C++):**

```cpp

class Solution {
  public:
    // Intuition: Greedily halve the largest element to reduce sum fastest. Use max-heap for efficiency.
    // Approach:
    // 1. Calculate initial sum and target (sum / 2).
    // 2. Push all elements onto a max-heap (priority_queue).
    // 3. While current sum > target:
    //    a. Pop the largest element (top of heap).
    //    b. Calculate its half.
    //    c. Subtract the *reduction amount* (half) from the sum.
    //    d. Push the halved element back onto the heap.
    //    e. Increment operation count.
    // 4. Return operation count.
    // Time Complexity: O(N log N + K log N), where N = arr.size() and K = number of operations.
    //                  O(N log N) to build the heap.
    //                  O(K log N) for K heap pop/push operations.
    // Space Complexity: O(N) to store elements in the priority queue.
    int minOperations(vector<int>& arr) {

        // Calculate the total initial sum of the array elements.
        double sum = 0;
        // Iterate through each element and add it to the sum.
        // Using double for sum to handle potential floating-point results from halving.
        for (int x : arr) sum += x;

        // Determine the target sum (half of the original sum).
        double target = sum / 2;

        // Use a max-heap (priority_queue in C++) to store elements.
        // It keeps the largest element at the top. Store as doubles for precision.
        priority_queue<double> pq;
        // Push all initial integer elements into the double priority queue.
        for (int x : arr) pq.push(static_cast<double>(x));

        // Initialize the count of operations.
        int ops = 0;

        // Loop continues as long as the current sum exceeds the target sum.
        while (sum > target) {
            // Get the largest element from the heap.
            double x = pq.top();
            // Remove the largest element from the heap.
            pq.pop();

            // Calculate half of the largest element.
            double h = x / 2;

            // Reduce the total sum by the amount removed (which is half of the original element).
            sum -= h;

            // Push the halved element back into the heap.
            pq.push(h);

            // Increment the operation counter.
            ops++;
        }

        // Return the total number of operations performed.
        return ops;

        /*
        * Dry Run (Example 1: arr[] = [8, 6, 2])
        *
        * Initial sum = 8 + 6 + 2 = 16.0
        * Target sum = 16.0 / 2 = 8.0
        * Heap (pq): [8.0, 6.0, 2.0]
        * Current sum = 16.0, ops = 0
        *
        * Iteration 1 (sum = 16.0 > 8.0):
        * x = pq.top() = 8.0; pq.pop() -> Heap: [6.0, 2.0]
        * h = 8.0 / 2 = 4.0
        * sum = 16.0 - 4.0 = 12.0
        * pq.push(4.0) -> Heap: [6.0, 4.0, 2.0]
        * ops = 1
        *
        * Iteration 2 (sum = 12.0 > 8.0):
        * x = pq.top() = 6.0; pq.pop() -> Heap: [4.0, 2.0]
        * h = 6.0 / 2 = 3.0
        * sum = 12.0 - 3.0 = 9.0
        * pq.push(3.0) -> Heap: [4.0, 3.0, 2.0]
        * ops = 2
        *
        * Iteration 3 (sum = 9.0 > 8.0):
        * x = pq.top() = 4.0; pq.pop() -> Heap: [3.0, 2.0]
        * h = 4.0 / 2 = 2.0
        * sum = 9.0 - 2.0 = 7.0
        * pq.push(2.0) -> Heap: [3.0, 2.0, 2.0]
        * ops = 3
        *
        * Loop condition (sum = 7.0 > 8.0) is false. Stop.
        * Return ops = 3.
        */
    }
};
```

---

## 🔑 Key Insights

The core idea is a **greedy approach**. To reach the target sum (half of the original) in the minimum number of operations, we must maximize the reduction in sum achieved by each operation. Since halving a number `x` reduces the sum by `x/2`, the largest reduction comes from halving the currently largest element in the array.

Using a **max-heap** (priority queue) allows us to efficiently:

1.  Find the largest element (`O(1)` time).
2.  Remove the largest element (`O(log N)` time).
3.  Insert the halved element back (`O(log N)` time).

This ensures that we always apply the operation to the element that gives the biggest immediate benefit, leading to the minimum total operations.

---

## 🚀 Further Exploration

- **K-th Largest Element in an Array:** Using heaps to find order statistics.
- **Minimum Cost of ropes:** Another greedy problem often solved efficiently with heaps (min-heap in this case).
- **Find Median from Data Stream:** Using two heaps (min and max) to maintain balance and find the median efficiently.
- **Maximize sum after K negations:** A greedy problem involving choosing which numbers to negate.

Consider how the time complexity would change if you didn't use a heap (e.g., sorting the array repeatedly or scanning for the max element in each step).

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/minimum-steps-to-halve-sum/1)
- [Priority Queue (Max Heap) in C++ STL](https://en.cppreference.com/w/cpp/container/priority_queue)
- [Greedy Algorithms](https://www.geeksforgeeks.org/greedy-algorithms/)

---

## 👨‍💻 Author

- Created by [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`greedy` `priority-queue` `max-heap` `array` `geeksforgeeks` `medium`

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

**Reminder:** The solutions and explanations provided are for educational purposes only. It's encouraged to understand the concepts rather than just copying the code. Always try to solve problems independently first.
