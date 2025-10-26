# 🔗 Minimum Cost of ropes

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-green?style=flat&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/minimum-cost-of-ropes-1587115620/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=flat)
![Accuracy](https://img.shields.io/badge/Accuracy-42.73%25-orange?style=flat)
![Points](https://img.shields.io/badge/Points-4-blue?style=flat)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/minimum-cost-of-ropes-1587115620/1).

---

## 📝 Problem Statement

Given an array `arr[]` of **rope lengths**, connect all ropes into a **single rope** with the **minimum total cost**. The cost to connect two ropes is the **sum of their lengths**.

---

## 🧪 Examples

**Example 1:**

```cpp
Input: arr[] = [4, 3, 2, 6]
Output: 29
```

<details>
<summary>📖 Example Breakdown</summary>

1.  **Initial Ropes:** `[4, 3, 2, 6]`
2.  Connect the two smallest ropes: `2` and `3`.
    - Cost: `2 + 3 = 5`
    - Remaining Ropes: `[4, 5, 6]` (The new rope has length 5)
    - Total Cost So Far: `5`
3.  Connect the next two smallest ropes: `4` and `5`.
    - Cost: `4 + 5 = 9`
    - Remaining Ropes: `[9, 6]` (The new rope has length 9)
    - Total Cost So Far: `5 + 9 = 14`
4.  Connect the final two ropes: `9` and `6`.
    - Cost: `9 + 6 = 15`
    - Remaining Ropes: `[15]` (A single rope)
    - Total Cost So Far: `14 + 15 = 29`
5.  **Final Minimum Cost:** `29`

Any other order, such as connecting 4 and 6 first (`cost=10`, remaining `[10, 3, 2]`), then 3 and 2 (`cost=5`, remaining `[10, 5]`), then 10 and 5 (`cost=15`), results in a higher total cost of `10 + 5 + 15 = 30`. The greedy approach guarantees the minimum.

</details>

**Example 2:**

```cpp
Input: arr[] = [4, 2, 7, 6, 9]
Output: 62
Explanation:
1. Connect 2 and 4: Cost = 6. Ropes = [6, 7, 6, 9]. Total Cost = 6.
2. Connect 6 and 6: Cost = 12. Ropes = [12, 7, 9]. Total Cost = 6 + 12 = 18.
3. Connect 7 and 9: Cost = 16. Ropes = [12, 16]. Total Cost = 18 + 16 = 34.
4. Connect 12 and 16: Cost = 28. Ropes = [28]. Total Cost = 34 + 28 = 62.
```

**Example 3:**

```cpp
Input: arr[] = [10]
Output: 0
Explanation: Since there is only one rope, no connections are needed, so the cost is 0.
```

---

## ⛓️ Constraints

- `1 ≤ arr.size() ≤ 10^5`
- `1 ≤ arr[i] ≤ 10^4`

---

## 💡 Solution Approaches

### Optimized Approach (Greedy with Min-Heap)

**Intuition:** To minimize the total cost, we should always connect the two ropes with the smallest lengths at each step. This ensures that smaller lengths contribute to the cumulative cost as few times as possible. This greedy strategy is similar to Huffman coding.

**Approach:**

1.  Use a min-heap (priority queue) to store the lengths of the ropes.
2.  Push all initial rope lengths into the min-heap.
3.  While the heap contains more than one element (more than one rope):
    - Extract the two smallest rope lengths (`first` and `second`) from the heap.
    - Calculate the cost of connecting them (`first + second`).
    - Add this cost to the total result (`res`).
    - Push the length of the newly formed rope (`first + second`) back into the heap.
4.  Once only one element remains in the heap (representing the final single rope), return the total accumulated cost `res`.

```cpp
// Intuition: Always connect the two smallest ropes first to minimize the total cost.
//            This greedy strategy ensures smaller lengths contribute to the cumulative cost fewer times.
// Approach: Use a min-heap (priority queue) to efficiently retrieve the two smallest rope lengths at each step.
//           Repeatedly extract the two minimums, calculate their sum (cost), add it to the total cost,
//           and insert the sum (new rope length) back into the heap until only one rope remains.
// Time Complexity: O(N log N) - Initial heap creation takes O(N). Then, N-1 iterations occur. Each iteration involves two extractions (O(log N) each) and one insertion (O(log N)). Total: O(N + (N-1)*log N) = O(N log N).
// Space Complexity: O(N) - In the worst case, the priority queue stores all N rope lengths.

class Solution {
  public:
    int minCost(vector<int> &arr) {
        // Handle edge case: If there are 0 or 1 ropes, no cost is incurred.
        if (arr.size() <= 1) {
            return 0;
        }

        // Create a min priority queue (min-heap) initialized with rope lengths from the input vector.
        // 'greater<int>' makes it a min-heap (smallest element at the top).
        priority_queue<int, vector<int>, greater<int>> pq(arr.begin(), arr.end());

        // Initialize total cost result to 0.
        int res = 0;

        // Loop continues as long as there is more than one rope in the priority queue.
        while (pq.size() > 1) {
            // Extract the shortest rope length from the priority queue.
            int first = pq.top();
            pq.pop(); // Remove the extracted element.

            // Extract the second shortest rope length.
            int second = pq.top();
            pq.pop(); // Remove the extracted element.

            // Calculate the cost of connecting the two shortest ropes.
            int current_cost = first + second;

            // Add the current connection cost to the total result.
            res += current_cost;

            // Insert the length of the newly formed rope (sum of the two connected) back into the priority queue.
            pq.push(current_cost);
        }

        // When the loop finishes, only one rope remains, and 'res' holds the total minimum cost.
        return res;
    }
    /*
    *
    * Dry Run: arr = [4, 3, 2, 6]
    *
    * 1. Initialize Heap: pq = [2, 3, 4, 6] (min-heap automatically arranges)
    * 2. Initialize res = 0
    *
    * 3. Iteration 1 (pq.size() = 4 > 1):
    * - Extract first = 2, pq = [3, 4, 6]
    * - Extract second = 3, pq = [4, 6]
    * - current_cost = 2 + 3 = 5
    * - res = 0 + 5 = 5
    * - Push 5 into pq. pq = [4, 5, 6]
    *
    * 4. Iteration 2 (pq.size() = 3 > 1):
    * - Extract first = 4, pq = [5, 6]
    * - Extract second = 5, pq = [6]
    * - current_cost = 4 + 5 = 9
    * - res = 5 + 9 = 14
    * - Push 9 into pq. pq = [6, 9]
    *
    * 5. Iteration 3 (pq.size() = 2 > 1):
    * - Extract first = 6, pq = [9]
    * - Extract second = 9, pq = []
    * - current_cost = 6 + 9 = 15
    * - res = 14 + 15 = 29
    * - Push 15 into pq. pq = [15]
    *
    * 6. Loop ends (pq.size() = 1)
    *
    * 7. Return res = 29
    *
    */
};
```

---

## ✨ Key Insights

The core idea is the **greedy approach**. By always combining the two shortest available ropes, we ensure that smaller lengths are part of fewer intermediate sums. A **min-heap (priority queue)** is the ideal data structure for efficiently retrieving the two minimum elements at each step in O(log N) time.

---

## 🚀 Further Exploration

- **Huffman Coding:** This problem shares the same core greedy strategy. Explore Huffman coding for data compression.
- **Connect N ropes:** (Similar GFG problem variations might exist).
- **Minimum cost to merge K sorted lists:** Another problem solvable with min-heaps.
- Consider the time complexity if the input array was already sorted. Would a different approach be faster? (Yes, potentially O(N) with two pointers or a deque if merging sorted lists, but the initial sort takes O(N log N)).

---

## 📚 References

- [GeeksforGeeks Problem Link](https://www.geeksforGeeks.org/problems/minimum-cost-of-ropes-1587115620/1)
- [GeeksforGeeks Article on Min-Heap](https://www.geeksforgeeks.org/min-heap-in-java/)
- [Huffman Coding Algorithm](https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/)

---

## 👨‍💻 Author

- Connect with me: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

**Reminder:** The code and explanation are for educational purposes. Always strive to understand the underlying concepts and algorithms.
