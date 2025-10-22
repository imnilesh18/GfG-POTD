# ⚙️ Nearly sorted

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-green?style=flat&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/nearly-sorted-1587115620/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=flat)
![Accuracy](https://img.shields.io/badge/Accuracy-75.25%25-brightgreen?style=flat)
![Points](https://img.shields.io/badge/Points-4-blue?style=flat)
![License](https://img.shields.io/badge/License-MIT-blue.svg?style=flat)

---

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/nearly-sorted-1587115620/1).

---

## 📝 Problem Statement

Given an array `arr[]`, where each element is at most **k positions away** from its correct position in the sorted order.
Your task is to **restore** the sorted order of `arr[]` by rearranging the elements **in place**.

**Note:** Don't use any built-in `sort()` method.

---

## 🧪 Examples

**Example 1:**

```plaintext
Input: arr[] = [2, 3, 1, 4], k = 2
Output: [1, 2, 3, 4]
Explanation:
All elements are at most k = 2 positions away from their correct positions.
Element 1 moves from index 2 to 0
Element 2 moves from index 0 to 1
Element 3 moves from index 1 to 2
Element 4 stays at index 3
```

<details>
<summary>📖 Example 1 Breakdown</summary>

- **Input:** `arr = [2, 3, 1, 4]`, `k = 2`
- The array size `n` is 4.
- The property "each element is at most k positions away" means the element that _should_ be at index `i` in the sorted array is currently located somewhere between index `max(0, i-k)` and `min(n-1, i+k)`.
- Consider index 0. The correct element (1) must be within indices `[0, 0+2] = [0, 2]`. The elements are `[2, 3, 1]`. The minimum is 1.
- Consider index 1. The correct element (2) must be within indices `[max(0, 1-2), min(3, 1+2)] = [0, 3]`. If we place elements sequentially, the element for index 0 (which is 1) is found among `arr[0...k] = [2, 3, 1]`. After placing 1 at `arr[0]`, we need the element for index 1. It must be among the next window of size `k+1`.
- Using a min-heap approach:
  1.  Push first `k=2` elements: `pq = {2, 3}`.
  2.  Process `arr[k]=arr[2]=1`: Push 1. `pq = {1, 2, 3}`. `arr[2-k]=arr[0] = pq.top() = 1`. Pop 1. `pq = {2, 3}`. `arr = [1, 3, 1, 4]`.
  3.  Process `arr[k+1]=arr[3]=4`: Push 4. `pq = {2, 3, 4}`. `arr[3-k]=arr[1] = pq.top() = 2`. Pop 2. `pq = {3, 4}`. `arr = [1, 2, 1, 4]`.
  4.  End of array. Place remaining heap elements:
      - `arr[4-k]=arr[2] = pq.top() = 3`. Pop 3. `pq = {4}`. `arr = [1, 2, 3, 4]`.
      - `arr[5-k]=arr[3] = pq.top() = 4`. Pop 4. `pq = {}`. `arr = [1, 2, 3, 4]`.
- **Final Output:** `[1, 2, 3, 4]`

</details>

**Example 2:**

```plaintext
Input: arr[]= [7, 9, 14], k = 1
Output: [7, 9, 14]
Explanation:
All elements are already stored in the sorted order.
```

---

## ⛓️ Constraints

```plaintext
1 ≤ arr.size() ≤ 10^6
0 ≤ k < arr.size()
1 ≤ arr[i] ≤ 10^6
```

---

## 💡 Solution Approaches

### Approach 1: Using Min-Heap

**Intuition:**
Since each element `arr[i]` is at most `k` positions away from its sorted position, the smallest element required for the sorted array must be within the first `k+1` elements. We can maintain a window of size `k+1` and always extract the minimum element from this window to place it in its correct sorted position. A min-heap is ideal for efficiently finding and extracting the minimum element from a dynamic window.

**Implementation:**
We use a min-priority queue (min-heap) to store `k+1` elements at a time.

1. Initialize the min-heap with the first `k` elements of the array.
2. Iterate through the rest of the array starting from index `k`.
3. In each iteration `i`:
   a. Push the current element `arr[i]` into the heap. Now the heap contains `k+1` potential candidates for the next smallest element.
   b. The smallest element in the heap (`pq.top()`) is the correct element for position `i-k`. Assign `arr[i-k] = pq.top()`.
   c. Pop the smallest element from the heap.
4. After the loop finishes, the heap might still contain some elements. Pop them one by one and place them in the remaining positions of the array.

```cpp

class Solution {
public:
    // Intuition: The element belonging at index `i` is within the window `[i, i+k]`.
    // Use a min-heap to keep track of the smallest element in a sliding window of size k+1.
    // Approach:
    // 1. Create a min-heap (priority_queue).
    // 2. Push the first 'k' elements into the heap.
    // 3. Iterate from index 'k' to 'n-1'.
    // 4. In each iteration 'i':
    //    a. Push arr[i] into the heap.
    //    b. The smallest element in the heap is the correct element for index 'i-k'. Place it: arr[i-k] = pq.top().
    //    c. Pop the smallest element from the heap.
    // 5. After the loop, place the remaining elements from the heap into the array.
    // Time Complexity: O(N log K) - Each element is pushed and popped once from the heap of size K.
    // Space Complexity: O(K) - The heap stores at most K+1 elements.
    void nearlySorted(std::vector<int> &arr, int k) {

        int n = arr.size(); // Get the size of the array

        // Create a min-heap using a priority queue.
        // `greater<int>` makes it a min-heap.
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

        // Push the first 'k' elements into the min-heap.
        // Note: Loop runs from i = 0 to k-1. If k=0, this loop doesn't run.
        for (int i = 0; i < k && i < n; i++) // Ensure i < n for edge cases like k >= n
            pq.push(arr[i]);

        int insert_idx = 0; // Index in arr where the next smallest element should be placed

        // Iterate through the array starting from index k.
        for (int i = k; i < n; i++) {
            // Push the current element into the heap.
            pq.push(arr[i]);

            // The top of the min-heap is the smallest element among the current window.
            // Place this smallest element at the correct sorted position (insert_idx).
            arr[insert_idx] = pq.top();
            pq.pop(); // Remove the smallest element.
            insert_idx++; // Move to the next position in the array.
        }

        // After iterating through the array, the heap might still contain elements.
        // These are the largest remaining elements. Place them in the remaining spots.
        while (!pq.empty()) {
            arr[insert_idx] = pq.top();
            pq.pop();
            insert_idx++;
        }
    }

    /*
    * Dry Run (Example 1: arr = [2, 3, 1, 4], k = 2)
    *
    * 1. n = 4
    * 2. Initialize pq:
    * - i = 0: push(arr[0]=2). pq = {2}
    * - i = 1: push(arr[1]=3). pq = {2, 3}
    * 3. Main loop (i from k=2 to n-1=3):
    * - i = 2 (element arr[2]=1):
    * - push(1). pq = {1, 2, 3} (size k+1 = 3)
    * - arr[insert_idx=0] = pq.top() = 1. arr = [1, 3, 1, 4]
    * - pop(). pq = {2, 3}
    * - insert_idx = 1
    * - i = 3 (element arr[3]=4):
    * - push(4). pq = {2, 3, 4} (size k+1 = 3)
    * - arr[insert_idx=1] = pq.top() = 2. arr = [1, 2, 1, 4]
    * - pop(). pq = {3, 4}
    * - insert_idx = 2
    * 4. End of main loop.
    * 5. Place remaining elements from pq:
    * - pq not empty. arr[insert_idx=2] = pq.top() = 3. arr = [1, 2, 3, 4]
    * - pop(). pq = {4}
    * - insert_idx = 3
    * - pq not empty. arr[insert_idx=3] = pq.top() = 4. arr = [1, 2, 3, 4]
    * - pop(). pq = {}
    * - insert_idx = 4
    * - pq empty. Stop.
    *
    * Final Output: arr = [1, 2, 3, 4]
    */
};
```

---

## ✨ Key Insights

- The crucial property is that the correct element for any position `i` is guaranteed to be within the window `[i, i+k]`.
- A min-heap allows us to maintain this sliding window efficiently and always extract the minimum (the next element needed for the sorted sequence) in `O(log K)` time.
- By placing the extracted minimum at the position `i-k` (or using a separate `insert_idx`), we effectively build the sorted array in place from left to right.

---

## 🚀 Further Exploration

- **K Largest Elements:** Find the k largest elements in an array. (Heap is useful here too).
- **Merge K Sorted Arrays:** Merge k sorted arrays into a single sorted array. (Min-heap can store the smallest element from each array).
- **Median in a stream of integers:** Find the median of numbers seen so far. (Two heaps: min-heap and max-heap).

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/nearly-sorted-1587115620/1)
- [GeeksforGeeks Article on K-Sorted Array](https://www.geeksforgeeks.org/nearly-sorted-algorithm/)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Heap](https://img.shields.io/badge/Data%20Structure-Heap-orange?style=flat-square)
![Priority Queue](https://img.shields.io/badge/Data%20Structure-Priority%20Queue-blue?style=flat-square)
![Sorting](https://img.shields.io/badge/Algorithm-Sorting-green?style=flat-square)
![Array](https://img.shields.io/badge/Data%20Structure-Array-lightgrey?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-green?style=flat-square&logo=geeksforgeeks)

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**Disclaimer:** This solution is provided for educational purposes only. It is intended to help users understand the problem and potential approaches. Always adhere to the platform's specific requirements and constraints when submitting solutions.

---
