# 🌊 Kth Largest in a Stream

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/kth-largest-element-in-a-stream2220/1"><img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" /></a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
    <img src="https://img.shields.io/badge/Accuracy-31.59%25-green?style=for-the-badge" alt="Accuracy" />
    <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an input stream `arr[]` of `n` integers, find the **Kth largest element** (not Kth largest unique element) after the insertion of each element in the stream. 

If the Kth largest element doesn't exist (i.e., fewer than `K` elements have been inserted), the answer will be `-1` for that insertion.

Return a list of size `n`, where each element represents the Kth largest value after the corresponding insertion.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [1, 2, 3, 4, 5, 6], k = 4
Output: [-1, -1, -1, 1, 2, 3]
```

<details>
<summary><b>📖 Example Breakdown</b></summary>

*   After `1`, the stream is `[1]`. The 4th largest does not exist. Output is `-1`.
*   After `2`, the stream is `[1, 2]`. The 4th largest does not exist. Output is `-1`.
*   After `3`, the stream is `[1, 2, 3]`. The 4th largest does not exist. Output is `-1`.
*   After `4`, the stream is `[1, 2, 3, 4]`. The 4th largest is `1`.
*   After `5`, the stream is `[1, 2, 3, 4, 5]`. The 4th largest is `2`.
*   After `6`, the stream is `[1, 2, 3, 4, 5, 6]`. The 4th largest is `3`.
</details>

### Example 2
```text
Input: arr[] = [3, 2, 1, 3, 3], k = 2
Output: [-1, 2, 2, 3, 3]
Explanation: 
- After 3, the stream is [3]. The 2nd largest does not exist. Output is -1.
- After 2, the stream is [3, 2]. The 2nd largest is 2.
- After 1, the stream is [3, 2, 1]. The 2nd largest is 2.
- After 3, the stream is [3, 2, 1, 3]. The 2nd largest is 3.
- After 3, the stream is [3, 2, 1, 3, 3]. The 2nd largest is 3.
```

---

## ⚙️ Constraints

> - $1 \le k \le n \le 10^5$
> - $1 \le \text{arr}[i] \le 10^5$

**Expected Complexities:**
*   **Time Complexity:** $O(n \cdot \log k)$
*   **Auxiliary Space:** $O(n)$

---

## 🚀 Solution Approaches

### Optimized Approach (Using Min-Heap)
```cpp
// Intuition: We need to find the Kth largest element efficiently as a stream of numbers comes in. By keeping only the K largest elements seen so far, the smallest among these K elements will always be our Kth largest overall. A min-heap perfectly serves this purpose.
// Approach: We iterate through the stream and push each element into a min-heap. If the heap's size exceeds K, we pop the smallest element (the top) to maintain exactly K elements. If the heap currently has fewer than K elements, we append -1 to our result. Otherwise, the top of the heap is the Kth largest element, which we append to our result.
// Time Complexity: O(n * log(k)) because we process 'n' elements and each insertion or deletion in a min-heap of size 'k' takes log(k) time.
// Space Complexity: O(k) for the min-heap which stores at most 'k' elements at any given time, plus O(n) auxiliary space for the result array.

class Solution {
  public:
    vector<int> kthLargest(vector<int>& arr, int k) {
        // code here - enhanced: initialize a min-heap to track the top k elements
        priority_queue<int, vector<int>, greater<int>> minHeap;
        vector<int> res; // stores the final answers for each step

        for (int num : arr) {
            minHeap.push(num); // add current stream element to heap

            if (minHeap.size() > k) {
                minHeap.pop(); // remove the smallest element if we exceed k elements
            }

            if (minHeap.size() < k) {
                res.push_back(-1); // Kth largest doesn't exist yet
            } else {
                res.push_back(minHeap.top()); // the top of min-heap is the Kth largest
            }
        }
        
        return res;
    }
};

/*
Dry Run

Input: arr = [1, 2, 3, 4, 5, 6], k = 4
Initialize minHeap as empty, res as empty

Current num: 1
Push 1 to minHeap. Heap: [1]
Size is 1, less than k(4). Append -1. res: [-1]

Current num: 2
Push 2 to minHeap. Heap: [1, 2]
Size is 2, less than k(4). Append -1. res: [-1, -1]

Current num: 3
Push 3 to minHeap. Heap: [1, 2, 3]
Size is 3, less than k(4). Append -1. res: [-1, -1, -1]

Current num: 4
Push 4 to minHeap. Heap: [1, 2, 3, 4]
Size is 4, equals k(4). Top is 1. Append 1. res: [-1, -1, -1, 1]

Current num: 5
Push 5 to minHeap. Heap: [1, 2, 3, 4, 5]
Size exceeds k(4), pop minimum (1). Heap: [2, 3, 4, 5]
Size equals k(4). Top is 2. Append 2. res: [-1, -1, -1, 1, 2]

Current num: 6
Push 6 to minHeap. Heap: [2, 3, 4, 5, 6]
Size exceeds k(4), pop minimum (2). Heap: [3, 4, 5, 6]
Size equals k(4). Top is 3. Append 3. res: [-1, -1, -1, 1, 2, 3]

Final Result: [-1, -1, -1, 1, 2, 3] 
*/
```

---

## 🔑 Key Insights

*   **Why Min-Heap?** A Max-Heap would give us the absolute largest element quickly, but finding the K-th largest would require popping `K-1` elements every time. By using a **Min-Heap of size K**, we trap the top `K` largest elements seen so far. The minimum among these (the top of the heap) is effectively the K-th largest overall.
*   **Constant Size Maintenance:** Popping elements when the size exceeds `K` ensures the heap operations never exceed $O(\log k)$, making the algorithm highly scalable for continuous streams.

---

## 🔍 Further Exploration

*   [Kth Smallest Element](https://www.geeksforgeeks.org/kth-smallest-largest-element-in-unsorted-array/)
*   [Find Median in a Stream](https://www.geeksforgeeks.org/median-of-stream-of-integers-running-integers/)
*   [Sliding Window Maximum](https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/)

---

## 🔗 References

*   **GeeksforGeeks Problem:** [Kth Largest in a Stream](https://www.geeksforgeeks.org/problems/kth-largest-element-in-a-stream2220/1)

---

## 👤 Author

*   **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Heap` `#Data Structures` `#Priority Queue` `#Stream` `#C++`

<div align="left">
    <img src="https://img.shields.io/badge/Flipkart-FFC200?style=flat-square&logo=flipkart&logoColor=white" />
    <img src="https://img.shields.io/badge/Amazon-232F3E?style=flat-square&logo=amazon&logoColor=white" />
    <img src="https://img.shields.io/badge/Microsoft-00A4EF?style=flat-square&logo=microsoft&logoColor=white" />
    <img src="https://img.shields.io/badge/Cisco-1BA0D7?style=flat-square&logo=cisco&logoColor=white" />
    <img src="https://img.shields.io/badge/Adobe-FF0000?style=flat-square&logo=adobe&logoColor=white" />
    <img src="https://img.shields.io/badge/Walmart-0071CE?style=flat-square&logo=walmart&logoColor=white" />
</div>