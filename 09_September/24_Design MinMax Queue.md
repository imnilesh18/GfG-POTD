# 🔱 Design MinMax Queue



| GFG | Difficulty | Accuracy | Points | License |
| :-: | :--------: | :------: | :----: | :-----: |
| <a href="https://www.geeksforgeeks.org/problems/design-minmax-queue/1"><img src="https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks" alt="GFG"></a> | <img src="https://img.shields.io/badge/Medium-yellow?style=for-the-badge" alt="Difficulty"> | <img src="https://img.shields.io/badge/82.66%25-brightgreen?style=for-the-badge" alt="Accuracy"> | <img src="https://img.shields.io/badge/4-blue?style=for-the-badge" alt="Points"> | <img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License"> |


> ⚠️ **Educational Use Only**: This repository and its content are intended solely for educational purposes. The solutions provided are for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeeks.org/problems/design-minmax-queue/1).

---

## Problem Statement

Design a **SpecialQueue** data structure that functions like a normal queue but with additional support for retrieving the **minimum** and **maximum** element efficiently.

The `SpecialQueue` must support the following operations:
- `enqueue(x)`: Insert an element `x` at the rear of the queue.
- `dequeue()`: Remove the element from the front of the queue.
- `getFront()`: Return the front element without removing it.
- `getMin()`: Return the minimum element in the queue in **O(1)** time.
- `getMax()`: Return the maximum element in the queue in **O(1)** time.

You will be given a sequence of queries `queries[][]`. The queries are represented in numeric form:
- `1 x`: Call `enqueue(x)`
- `2`: Call `dequeue()`
- `3`: Call `getFront()`
- `4`: Call `getMin()`
- `5`: Call `getMax()`

You only need to implement the five functions. It is guaranteed that all queries are valid.

---

## Examples

### Example 1:

```
Input: q = 6, queries[][] = [[1, 4], [1, 2], [3], [4], [2], [5]]
Output: [4, 2, 2]
Explanation:
1. enqueue(4): Queue: [4]
2. enqueue(2): Queue: [4, 2]
3. getFront(): Returns 4.
4. getMin(): Returns 2.
5. dequeue(): Removes 4. Queue: [2]
6. getMax(): Returns 2.
```

<details>
<summary>📖 Example Breakdown</summary>

Let's trace the state of our `SpecialQueue` and its helper deques (`min_dq`, `max_dq`) for the first example:

- **Initial State:** `q: []`, `min_dq: []`, `max_dq: []`

1.  **`enqueue(4)`:**
    - `q.push(4)` -> `q: [4]`
    - `min_dq` is empty, `min_dq.push_back(4)` -> `min_dq: [4]`
    - `max_dq` is empty, `max_dq.push_back(4)` -> `max_dq: [4]`

2.  **`enqueue(2)`:**
    - `q.push(2)` -> `q: [4, 2]`
    - `min_dq.back() (4) > 2`, so `min_dq.pop_back()` -> `min_dq: []`. Then `min_dq.push_back(2)` -> `min_dq: [2]`
    - `max_dq.back() (4) > 2`, no change. `max_dq.push_back(2)` -> `max_dq: [4, 2]`

3.  **`getFront()`:**
    - `q.front()` is **4**. Output: `[4]`

4.  **`getMin()`:**
    - `min_dq.front()` is **2**. Output: `[4, 2]`

5.  **`dequeue()`:**
    - `frontVal = q.front()` -> `frontVal = 4`
    - `frontVal (4) != min_dq.front() (2)`, no change to `min_dq`.
    - `frontVal (4) == max_dq.front() (4)`, so `max_dq.pop_front()` -> `max_dq: [2]`
    - `q.pop()` -> `q: [2]`

6.  **`getMax()`:**
    - `max_dq.front()` is **2**. Output: `[4, 2, 2]`

</details>

### Example 2:

```
Input: q = 4, queries[][] = [[1, 3], [4], [1, 5], [5]]
Output: [3, 5]
Explanation:
1. enqueue(3): Queue: [3]
2. getMin(): Returns 3.
3. enqueue(5): Queue: [3, 5]
4. getMax(): Returns 5.
```

---

## Constraints

<div align="center">

| Constraint | Value |
| :--- | :--- |
| `queries.size()` | `1 ≤ size ≤ 10^5` |
| `values in queue`| `0 ≤ value ≤ 10^9` |

</div>

---

## Solution Approach

The core idea is to use a primary `queue` to store the elements and two auxiliary `deque` (double-ended queues) to efficiently track the minimum and maximum elements.

- **`min_dq`**: This deque is maintained in a monotonically increasing order. The front of this deque will always be the smallest element currently in the queue.
- **`max_dq`**: This deque is maintained in a monotonically decreasing order. The front of this deque will always be the largest element currently in the queue.

This setup allows us to retrieve the min and max values in **O(1)** time.

### C++ Solution

```cpp
// Intuition: The challenge is to get the min/max elements from a queue in O(1) time. A standard queue doesn't support this efficiently. We can use auxiliary data structures, specifically deques, to keep track of potential minimum and maximum values.
// Approach:
// 1. Use a standard `std::queue` as the main storage for queue elements.
// 2. Use two `std::deque`s: `min_dq` to track minimums and `max_dq` to track maximums.
// 3. For `enqueue(x)`:
//    - Push `x` to the main queue.
//    - For `min_dq`: Remove all elements from the back that are greater than `x`. Then push `x`. This maintains a monotonically increasing deque, so the minimum is always at the front.
//    - For `max_dq`: Remove all elements from the back that are less than `x`. Then push `x`. This maintains a monotonically decreasing deque, so the maximum is always at the front.
// 4. For `dequeue()`:
//    - Get the front element from the main queue.
//    - If this element is also at the front of `min_dq` or `max_dq`, pop it from them as well, since it's being removed from the main queue.
//    - Pop from the main queue.
// 5. `getMin()` and `getMax()` simply return the front elements of `min_dq` and `max_dq` respectively.
// Time Complexity: O(1) for all operations (amortized). Each element is pushed and popped from the deques at most once.
// Space Complexity: O(N) in the worst case, where N is the number of elements in the queue, as the deques could potentially store all elements.

class SpecialQueue {
    // Main queue to store elements
    queue<int> q;
    // Deque to get the minimum element in O(1)
    deque<int> min_dq;
    // Deque to get the maximum element in O(1)
    deque<int> max_dq;

public:
    /**
     * @brief Inserts an element at the rear of the queue and updates min/max deques.
     * @param x The integer element to be inserted.
     */
    void enqueue(int x) {
        // Push the element to the main queue
        q.push(x);

        // Maintain the min_dq to have elements in increasing order.
        // Remove elements from the back of min_dq that are larger than the new element.
        while (!min_dq.empty() && min_dq.back() > x) {
            min_dq.pop_back();
        }
        min_dq.push_back(x);

        // Maintain the max_dq to have elements in decreasing order.
        // Remove elements from the back of max_dq that are smaller than the new element.
        while (!max_dq.empty() && max_dq.back() < x) {
            max_dq.pop_back();
        }
        max_dq.push_back(x);
    }

    /**
     * @brief Removes the element from the front of the queue and updates min/max deques if needed.
     */
    void dequeue() {
        int frontVal = q.front();

        // If the front element is the current minimum, it's no longer in the queue.
        if (frontVal == min_dq.front()) {
            min_dq.pop_front();
        }

        // If the front element is the current maximum, it's no longer in the queue.
        if (frontVal == max_dq.front()) {
            max_dq.pop_front();
        }

        // Remove the element from the main queue
        q.pop();
    }

    /**
     * @brief Returns the front element of the queue.
     * @return The front element.
     */
    int getFront() {
        return q.front();
    }

    /**
     * @brief Returns the minimum element in the queue.
     * @return The minimum element.
     */
    int getMin() {
        // The front of min_dq is always the smallest element.
        return min_dq.front();
    }

    /**
     * @brief Returns the maximum element in the queue.
     * @return The maximum element.
     */
    int getMax() {
        // The front of max_dq is always the largest element.
        return max_dq.front();
    }
};

/*
*
* Dry Run
* Input: queries[][] = [[1, 4], [1, 2], [4], [5], [2], [5]]
*
* 1. enqueue(4):
* q: [4]
* min_dq: [4]
* max_dq: [4]
*
* 2. enqueue(2):
* q: [4, 2]
* min_dq: (4 > 2, pop 4), push 2 -> [2]
* max_dq: push 2 -> [4, 2]
*
* 3. getMin():
* returns min_dq.front() -> 2
*
* 4. getMax():
* returns max_dq.front() -> 4
*
* 5. dequeue():
* frontVal = 4
* min_dq.front() is 2 (not 4)
* max_dq.front() is 4, pop 4 -> [2]
* q.pop() -> q: [2]
*
* 6. getMax():
* returns max_dq.front() -> 2
*
*/
```

---

## Key Insights

The solution's efficiency comes from the clever use of deques to maintain sorted-like structures.
- By removing useless elements from the back during `enqueue`, we ensure that the front of `min_dq` is always the current minimum and the front of `max_dq` is the current maximum among all elements still present in the main queue.
- This avoids the need to iterate through the entire queue to find the min/max, which would be an O(N) operation. The amortized time complexity for enqueue and dequeue remains O(1).

---

## Further Exploration

- **Sliding Window Maximum:** This problem uses a similar deque-based technique to find the maximum in every sliding window of size `k`.
- **Min Stack:** A classic problem where you need to design a stack that supports `getMin()` in O(1) time. The same principle of an auxiliary data structure applies.
- **Design a data structure that supports insert, delete, search, and `getRandom` in O(1) time.**

---

## References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/design-minmax-queue/1)
- [Monotonic Queue Explained](https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/)

---

## Author

<div align="center">
    Connect with me on GitHub!
</div>
<p align="center">
    <a href="https://github.com/imnilesh18" target="_blank">
        <img src="https://img.shields.io/badge/imnilesh18-blue?style=for-the-badge&logo=github" alt="GitHub">
    </a>
</p>

---

## Tags

<div align="center">
    <img src="https://img.shields.io/badge/Queue-blueviolet?style=for-the-badge" alt="Queue">
    <img src="https://img.shields.io/badge/Deque-orange?style=for-the-badge" alt="Deque">
    <img src="https://img.shields.io/badge/Data%20Structure-green?style=for-the-badge" alt="Data Structure">
    <img src="https://img.shields.io/badge/Design-yellow?style=for-the-badge" alt="Design">
</div>

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**Note on Educational Use:** This content is for educational purposes only. If you are a student, it is recommended to first attempt the problem on your own before referring to this solution.