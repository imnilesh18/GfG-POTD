# 🔄 Rotate Deque By K

| ⚠️ **Educational Use Only** |
| :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only.                                     |
| Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/rotate-deque-by-k/1). |

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-blue?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-75.79%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

</div>

---

## Problem Statement

You are given a deque `dq[]` (double-ended queue) containing non-negative integers, along with two positive integer `type` and `k`. The task is to rotate the deque circularly by `k` positions.

There are two types of rotation operations:

-   **Right Rotation (Clockwise):** If `type = 1`, rotate the deque to the right. This means moving the last element to the front, and repeating the process `k` times.
-   **Left Rotation (Anti-Clockwise):** If `type = 2`, rotate the deque to the left. This means moving the first element to the back, and repeating the process `k` times.

---

## Examples

### Example 1:

**Input:**
```
dq = [1, 2, 3, 4, 5, 6]
type = 1
k = 2
```
**Output:**
```
[5, 6, 1, 2, 3, 4]
```
**Explanation:**
The type is 1 and k is 2. So, we need to right rotate the deque by 2 times.
-   In the first right rotation, we get `[6, 1, 2, 3, 4, 5]`.
-   In the second right rotation, we get `[5, 6, 1, 2, 3, 4]`.

<details>
<summary>📖 Example Breakdown</summary>

1.  **Initial Deque:** `[1, 2, 3, 4, 5, 6]`
2.  **Operation:** Right rotate (`type = 1`) by `k = 2` positions.
3.  **Rotation 1:**
    -   Take the last element `6`.
    -   Move it to the front.
    -   Deque becomes: `[6, 1, 2, 3, 4, 5]`
4.  **Rotation 2:**
    -   Take the last element `5`.
    -   Move it to the front.
    -   Deque becomes: `[5, 6, 1, 2, 3, 4]`
5.  **Final Result:** `[5, 6, 1, 2, 3, 4]`

</details>

### Example 2:

**Input:**
```
dq = [10, 20, 30, 40, 50]
type = 2
k = 3
```
**Output:**
```
[40, 50, 10, 20, 30]
```
**Explanation:**
The type is 2 and k is 3. So, we need to left rotate the deque by 3 times.
-   In the first left rotation, we get `[20, 30, 40, 50, 10]`.
-   In the second left rotation, we get `[30, 40, 50, 10, 20]`.
-   In the third left rotation, we get `[40, 50, 10, 20, 30]`.

---

## Constraints

> `1 ≤ dq.size() ≤ 10^5`
> `1 ≤ k ≤ 10^5`
> `1 ≤ type ≤ 2`

---

## Solution Approaches

### Optimized Brute-Force Approach

The core idea is to simulate the rotation process. For a right rotation, we repeatedly take the last element and add it to the front. For a left rotation, we do the opposite. To make this efficient, we first reduce `k` by taking its modulo with the deque size, since rotating by the size of the deque results in the original deque.

#### C++ Solution
```cpp
// Intuition: The problem requires rotating a deque by k positions. A right rotation moves the last element to the front, and a left rotation moves the front element to the back. This can be achieved by performing the single-element move operation k times.
// Approach: First, we optimize the number of rotations by taking k modulo the size of the deque (k = k % dq.size()), as rotating by size returns the deque to its original state. Then, based on the rotation 'type', we loop 'k' times. For a right rotation (type 1), we move the last element to the front. For a left rotation (type 2), we move the first element to the back.
// Time Complexity: O(k % dq.size()). The complexity is determined by the number of rotations. Each rotation involves constant time deque operations (push, pop). After taking the modulo, k is at most dq.size() - 1.
// Space Complexity: O(1). The rotations are performed in-place on the deque, using only a single temporary variable to hold the element being moved.
class Solution {
  public:
    void rotateDeque(deque<int>& dq, int type, int k) {
        int n = dq.size();
        // If the deque is empty or has only one element, no rotation is needed.
        if (n <= 1) {
            return;
        }
        
        // Optimize k to avoid full rotations that result in the same deque state.
        k = k % n;

        // If k is 0, no rotation is necessary.
        if (k == 0) {
            return;
        }

        if (type == 1) { // Right rotation (Clockwise)
            // Perform k right rotations.
            for (int i = 0; i < k; i++) {
                // Get the last element.
                int last_element = dq.back();
                // Remove the last element.
                dq.pop_back();
                // Add the removed element to the front.
                dq.push_front(last_element);
            }
        } else { // Left rotation (Anti-Clockwise)
            // Perform k left rotations.
            for (int i = 0; i < k; i++) {
                // Get the first element.
                int first_element = dq.front();
                // Remove the first element.
                dq.pop_front();
                // Add the removed element to the back.
                dq.push_back(first_element);
            }
        }
    }
};

/*
*
* Dry Run
*
* Example 1: Right Rotation
* Input: dq = [1, 2, 3, 4, 5, 6], type = 1, k = 2
*
* 1. Initial values: n = 6, type = 1, k = 2.
* 2. Optimize k: k = 2 % 6 = 2.
* 3. Rotation type is 1 (Right). Loop 2 times.
*
* Iteration 1:
* - last_element = dq.back() -> 6
* - dq.pop_back() -> dq is now [1, 2, 3, 4, 5]
* - dq.push_front(6) -> dq is now [6, 1, 2, 3, 4, 5]
*
* Iteration 2:
* - last_element = dq.back() -> 5
* - dq.pop_back() -> dq is now [6, 1, 2, 3, 4]
* - dq.push_front(5) -> dq is now [5, 6, 1, 2, 3, 4]
*
* Final Output: [5, 6, 1, 2, 3, 4]
*
*
* Example 2: Left Rotation
* Input: dq = [10, 20, 30, 40, 50], type = 2, k = 3
*
* 1. Initial values: n = 5, type = 2, k = 3.
* 2. Optimize k: k = 3 % 5 = 3.
* 3. Rotation type is 2 (Left). Loop 3 times.
*
* Iteration 1:
* - first_element = dq.front() -> 10
* - dq.pop_front() -> dq is now [20, 30, 40, 50]
* - dq.push_back(10) -> dq is now [20, 30, 40, 50, 10]
*
* Iteration 2:
* - first_element = dq.front() -> 20
* - dq.pop_front() -> dq is now [30, 40, 50, 10]
* - dq.push_back(20) -> dq is now [30, 40, 50, 10, 20]
*
* Iteration 3:
* - first_element = dq.front() -> 30
* - dq.pop_front() -> dq is now [40, 50, 10, 20]
* - dq.push_back(30) -> dq is now [40, 50, 10, 20, 30]
*
* Final Output: [40, 50, 10, 20, 30]
*
*/
```

---

## Key Insights

-   The most crucial optimization is using the modulo operator (`k = k % dq.size()`). This prevents redundant rotations and keeps the number of operations minimal, especially when `k` is very large.
-   A **deque** is the perfect data structure for this problem because it provides efficient `O(1)` time complexity for adding/removing elements from both the front and the back.

---

## Further Exploration

-   [Rotate Array](https://www.geeksforgeeks.org/problems/rotate-array-by-n-elements-1587115621/1)
-   [Implement Deque](https://www.geeksforgeeks.org/problems/implement-deque-1587115620/1)
-   [Circular tour](https://www.geeksforgeeks.org/problems/circular-tour-1587115620/1)

---

## References

-   [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/rotate-deque-by-k/1)
-   [C++ Deque Documentation](https://en.cppreference.com/w/cpp/container/deque)

---

## Author

-   [imnilesh18](https://github.com/imnilesh18)

---

## Tags

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data%20Structures-3C873A?style=for-the-badge)
![Deque](https://img.shields.io/badge/Deque-orange?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**Reminder:** The content in this repository is for educational purposes only.