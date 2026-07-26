# 🌳 Complete Binary Tree Traversal with Array Input

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/print-binary-tree-levels-in-sorted-order3241/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-46.62%25-green?style=for-the-badge" alt="Accuracy: 46.62%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
  </a>
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an integer array `arr[]` representing the nodes of a **Complete Binary Tree** in level order traversal, return the nodes at each level in sorted ascending order.

For every level of the binary tree, sort the values present at that level independently and return the resulting levels as a 2D array, where the $i$-th row contains the sorted values of the $i$-th level.

---

## 💡 Examples

### Example 1

```text
Input: arr[] = [7, 6, 5, 4, 3, 2, 1]
Output: [[7], [5, 6], [1, 2, 3, 4]]

```

The complete binary tree formed from the given level order traversal is:

```text
       7
     /   \
    6     5
   / \   / \
  4   3 2   1

```

The nodes at each level after sorting are:

* **Level 0:** `[7]`
* **Level 1:** `[6, 5]` ➔ sorted: `[5, 6]`
* **Level 2:** `[4, 3, 2, 1]` ➔ sorted: `[1, 2, 3, 4]`

### Example 2

```text
Input: arr[] = [7, 16, 1, 4, 13]
Output: [[7], [1, 16], [4, 13]]
Explanation: 
Level 0: [7]
Level 1: [16, 1] -> sorted: [1, 16]
Level 2: [4, 13] -> sorted: [4, 13]

```

---

## 🚧 Constraints

> * $1 \le \text{arr.size()} \le 10^4$
> * $1 \le \text{arr}[i] \le 10^9$
> 
> 

---

## 🚀 Solution Approaches

### 1️⃣ Optimized Approach (Grouping by Powers of 2)

**Intuition:**
Since the array represents a Complete Binary Tree in level-order, the number of nodes at each level $i$ (starting at level $0$) is exactly $2^i$, except potentially for the last level which might not be completely full. This allows us to simply iterate through the array, slicing it into chunks of sizes $1, 2, 4, 8 \dots$, sorting each chunk, and appending it to our result.

```cpp
// Intuition: The given array is a level-order traversal of a complete binary tree. The number of nodes at each level `i` is 2^i (except potentially the last level). We can group the array elements level by level, sort each group, and store them.
// Approach: 
// 1. Traverse the array while keeping track of the current level's size (starting at 1 and doubling each time).
// 2. For each level, extract the elements, sort them in ascending order, and push them to the result vector.
// Time Complexity: O(n log n) - We visit each element once and sort each level. In the worst case, sorting all levels takes O(n log n) time overall.
// Space Complexity: O(n) - We use additional space to store the output 2D vector and a temporary vector for each level.

class Solution {
  public:
    vector<vector<int>> levelSort(vector<int>& arr) {
        vector<vector<int>> result; // To store the final level-wise sorted nodes
        int n = arr.size();         // Total number of nodes
        int i = 0;                  // Pointer to traverse the array
        int levelSize = 1;          // Number of nodes in the current level

        while (i < n) {
            vector<int> currentLevel; // Temporary vector for the current level
            
            // Extract up to 'levelSize' elements for the current level
            for (int j = 0; j < levelSize && i < n; ++j) {
                currentLevel.push_back(arr[i]);
                i++; // Move to the next node
            }
            
            // Sort the extracted level independently
            sort(currentLevel.begin(), currentLevel.end());
            
            // Add the sorted level to our result
            result.push_back(currentLevel);
            
            // Double the level size for the next level of the complete binary tree
            levelSize *= 2; 
        }
        
        return result; // Return the 2D array of sorted levels
    }
};

/*
*
* Dry Run
* Input: arr[] = [7, 6, 5, 4, 3, 2, 1]
* 
* Initialization: n = 7, i = 0, levelSize = 1, result = []
* 
* Iteration 1:
* - currentLevel extracts 1 element: [7]. i becomes 1.
* - sort currentLevel: [7]
* - result = [[7]]
* - levelSize becomes 2
* 
* Iteration 2:
* - currentLevel extracts 2 elements: [6, 5]. i becomes 3.
* - sort currentLevel: [5, 6]
* - result = [[7], [5, 6]]
* - levelSize becomes 4
* 
* Iteration 3:
* - currentLevel extracts 4 elements: [4, 3, 2, 1]. i becomes 7.
* - sort currentLevel: [1, 2, 3, 4]
* - result = [[7], [5, 6], [1, 2, 3, 4]]
* - levelSize becomes 8
* 
* i is now 7, which is not < n. Loop terminates.
* Output: [[7], [5, 6], [1, 2, 3, 4]]
*
*/

```

---

## 🧠 Key Insights

* **Predictable Structure:** A complete binary tree's level boundaries in an array representation are strictly defined by powers of 2. You don't need a queue to reconstruct the tree; simple array slicing by calculating index ranges is highly efficient.
* **Sorting Costs:** The time complexity is dominated by sorting the lowest levels. Since the last level can contain roughly $n/2$ nodes, sorting it takes $O(n \log n)$ time.

---

## 🔍 Further Exploration

* GeeksforGeeks: **Binary Tree Level Order Traversal** (Classic queue-based approach for arbitrary trees)
* GeeksforGeeks: **Reverse Level Order Traversal**
* Understand how heaps are implemented using arrays via Complete Binary Tree properties.

---

## 🔗 References

* **Problem Link:** [Complete Binary Tree Traversal with Array Input on GeeksforGeeks](https://www.geeksforgeeks.org/problems/print-binary-tree-levels-in-sorted-order3241/1)
* **Topics:** `Sorting`, `Queue`, `Tree`, `Priority Queue`

---

## 👨‍💻 Author

* **[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#dynamic-programming` `#LIS` `#array` `#geeksforgeeks` `#cpp` `#tree` `#sorting`