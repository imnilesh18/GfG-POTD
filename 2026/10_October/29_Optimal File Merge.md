# 🗂️ Optimal File Merge

![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white) ![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge) ![Accuracy: 82.09%](https://img.shields.io/badge/Accuracy-82.09%25-green?style=for-the-badge) ![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge) ![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an integer array `files[]`, where `files[i]` represents the size of the i-th file, merge all the files into a single file with the minimum total computation cost[cite: 1]. 
The cost of merging two files of sizes `x` and `y` is `x + y`[cite: 1]. After merging, a new file of size `x + y` is created, which can be merged further with other files[cite: 1]. 
Return the minimum total cost required to merge all the files[cite: 1].

> **Note:** It is guaranteed that the minimum total computation cost fits within a 32-bit signed integer[cite: 1].

---

## 💡 Examples

```text
Input: files[] = [3, 2, 4]
Output: 14
```
<details>
<summary>📖 Example Breakdown</summary>
There are different ways to combine these files[cite: 1]. The optimal method is:
1. Merge the smallest files `2` and `3`. Cost = `5`. Remaining files: `[4, 5]`.
2. Merge `4` and `5`. Cost = `9`. Remaining files: `[9]`.
Total Cost = `5 + 9 = 14`.
</details>

```text
Input: files[] = [2, 3, 6, 5, 7, 4]
Output: 68
```

---

## ⚠️ Constraints

> - **$1 \le files.size() \le 10^5$**[cite: 1]
> - **$1 \le files[i] \le 10^3$**[cite: 1]

---

## 🚀 Solution Approaches

### Greedy Approach using Min-Heap
**Intuition:** To minimize the overall cost, we must ensure that the largest files are merged as few times as possible. By always picking the two smallest available files to merge, we follow a greedy strategy that keeps the cumulative merging cost to an absolute minimum. A priority queue (min-heap) perfectly handles dynamically retrieving the smallest elements.

```cpp
// Intuition: To minimize the total merge cost, we should always merge the two smallest available files first. A min-heap allows us to efficiently track and extract these minimum values dynamically.
// Approach:
// 1. Insert all file sizes into a min-heap (priority queue).
// 2. While there is more than one file in the heap, extract the two smallest files.
// 3. Calculate their merge cost (first + second) and add it to the total cost.
// 4. Push the newly merged file size back into the heap.
// 5. Repeat until only one file remains in the heap.
// Time Complexity: O(n log n). Building the heap takes O(n), and each of the n-1 merges takes O(log n) to extract and push elements.
// Space Complexity: O(n) to store all the file sizes in the priority queue.
class Solution {
  public:
    int minComputation(vector<int> &files) {
        // Build a min-heap containing all file sizes to quickly fetch the smallest files
        priority_queue<int, vector<int>, greater<int>> minHeap(files.begin(), files.end());
        
        int totalCost = 0;

        // Continuously merge the two smallest files until a single file remains
        while (minHeap.size() > 1) {
            int first = minHeap.top(); // Extract smallest
            minHeap.pop();
            int second = minHeap.top(); // Extract second smallest
            minHeap.pop();

            int mergeCost = first + second;
            totalCost += mergeCost; // Accumulate merge cost

            minHeap.push(mergeCost); // Insert merged file back into heap
        }

        return totalCost;
    }
};

/*
*
* Dry Run
* Input: files[] = [3, 2, 4]
* Initialize Min-Heap: [2, 3, 4]
* totalCost = 0
* 
* Iteration 1:
* Extract 2 and 3. Heap: [4]
* mergeCost = 2 + 3 = 5
* totalCost = 0 + 5 = 5
* Push 5 into Heap. Heap: [4, 5]
* 
* Iteration 2:
* Extract 4 and 5. Heap: []
* mergeCost = 4 + 5 = 9
* totalCost = 5 + 9 = 14
* Push 9 into Heap. Heap: [9]
* 
* Heap size is 1. Loop terminates.
* Return totalCost: 14
*/
```

---

## 🔑 Key Insights
- **Greedy Strategy:** By merging the smallest files first, we ensure their weights contribute the least possible amount to subsequent merges.
- **Min-Heap Efficiency:** A priority queue inherently keeps elements sorted, reducing the operation of finding the two minimums to $O(\log n)$, preventing the need for repeated linear scans or full array sorts.

---

## 🔍 Further Exploration
- Try solving the **Huffman Coding** problem, which uses the exact same underlying greedy concept to build prefix trees.
- How would the approach change if you were asked to *maximize* the computation cost instead?

---

## 🔗 References
- **Original GeeksforGeeks Problem:** [Optimal File Merge](https://www.geeksforgeeks.org/problems/optimal-file-merge/1)[cite: 1]

---

## 👨‍💻 Author
[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`#Heap` `#Greedy` `#Amazon` `#GeeksForGeeks` `#C++`