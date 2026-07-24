# 🌳 Longest Consecutive Sequence in Binary Tree

<div align="center">
    
[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/longest-consecutive-sequence-in-binary-tree/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-30.58%25-blue?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-4-green?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](LICENSE)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given the root of a Binary Tree, find the length of the longest path consisting of connected nodes such that each next node has a value exactly **1 greater** than its parent.

* The path must move from **parent to child** only and follow increasing consecutive values.
* If no such path exists (i.e., no two nodes form a consecutive increasing sequence), return `-1`.

---

## 💡 Examples

### Example 1
```text
Input: root[] = [1, 2, 3]
       1
      / \
     2   3

Output: 2
Explanation: The longest consecutive sequence is 1 -> 2. So the answer for this test case is 2.
```

### Example 2
```text
Input: root[] = [10, 20, 30, 40, N, 60, 90]
       10
      /  \
    20    30
   /       \
  40        60
              \
               90

Output: -1
Explanation: For the above test case no sequence is possible where child == parent + 1. So output is -1.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>

Let's trace Example 1: `root[] = [1, 2, 3]`

1.  **Start at Root (1)**: 
    * Current Path Length = 1. Max Length = 1.
    * Check Left Child (2): Expected value is `1 + 1 = 2`.
    * Check Right Child (3): Expected value is `1 + 1 = 2`.
2.  **Move to Left Child (2)**:
    * Node value `2` equals the expected value `2`. 
    * Current Path Length becomes `1 + 1 = 2`. 
    * Update Max Length to `2`.
3.  **Move to Right Child (3)**:
    * Node value `3` does **not** equal expected value `2`.
    * Current Path Length resets to `1`.
4.  **Result**: 
    * Max Length found is `2`. Since it's greater than 1, we return `2`.

</details>

---

## ⚠️ Constraints

> * `1 <= no. of nodes in root <= 10^5`
> * `1 <= root.node->data <= 10^5`

---

## 🚀 Solution Approach

### Depth-First Search (DFS)

**Brief Intuition:**
To find consecutive paths moving from parent to child, we can traverse the tree using DFS. At each node, we check if its value is exactly `1` greater than its parent's value. If it is, we extend our current path length. If not, we reset the path length to 1. We keep a running maximum of these path lengths and return it at the end.

```cpp
// Intuition: We need to traverse the tree and track the length of consecutive increasing paths. DFS is a natural fit for exploring parent-to-child paths.
// Approach: Use a helper DFS function. Keep track of the expected next value (parent value + 1), current path length, and update a global/reference maximum length. If the current node matches the expected value, increment the path length. Otherwise, reset to 1. If max length > 1, return it, else return -1.
// Time Complexity: O(n) where n is the number of nodes, as we visit every node exactly once.
// Space Complexity: O(h) where h is the height of the tree, representing the call stack during DFS.

class Solution {
  public:
    int longestConsecutive(Node* root) {
        // Handle edge case of an empty tree
        if (!root) return -1;
        
        int maxLen = 0;
        
        // Start DFS from root with expected value as root->data
        dfs(root, root->data, 0, maxLen);
        
        // Return maxLen if a valid path exists, else return -1
        return maxLen > 1 ? maxLen : -1;
    }
    
  private:
    void dfs(Node* node, int target, int currLen, int& maxLen) {
        // Base case: Reached a leaf's child
        if (!node) return;
        
        // Extend path if consecutive, else reset path length to 1
        if (node->data == target) {
            currLen++;
        } else {
            currLen = 1;
        }
        
        // Update the global maximum length found so far
        maxLen = max(maxLen, currLen);
        
        // Recurse for left and right children with new target (node->data + 1)
        dfs(node->left, node->data + 1, currLen, maxLen);
        dfs(node->right, node->data + 1, currLen, maxLen);
    }
};

/*
*
* Dry Run
*
* Input: [1, 2, 3] (1 is root, 2 is left child, 3 is right child)
* maxLen = 0
* 
* dfs(Node(1), target=1, currLen=0, maxLen):
*   node->data (1) == target (1) -> currLen becomes 1
*   maxLen = max(0, 1) = 1
*   
*   dfs(Node(2), target=2, currLen=1, maxLen):
*     node->data (2) == target (2) -> currLen becomes 2
*     maxLen = max(1, 2) = 2
*     Both children of Node(2) are null, return.
*
*   dfs(Node(3), target=2, currLen=1, maxLen):
*     node->data (3) != target (2) -> currLen resets to 1
*     maxLen = max(2, 1) = 2
*     Both children of Node(3) are null, return.
*
* Final maxLen is 2. Since 2 > 1, we return 2. Output is 2.
*
*/
```

---

## 🔑 Key Insights

* **Pre-order Traversal Power:** We pass the "expected" state down to the children during the DFS. This allows us to make local decisions at each node without needing to re-traverse or backtrack complex paths.
* **Pass by Reference:** By passing `maxLen` by reference (`int& maxLen`), we ensure that the global maximum is updated seamlessly across all recursive calls without needing a class-level global variable.

---

## 🌍 Further Exploration

If you enjoyed this problem, check out these related tree concepts on GeeksforGeeks:
1. **Maximum Path Sum in a Binary Tree** - Exploring paths between any two nodes.
2. **Diameter of a Binary Tree** - Finding the longest path between any two leaf nodes.
3. **Longest Consecutive Sequence in an Array** - The 1D array variation of this problem.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Longest Consecutive Sequence in Binary Tree](https://www.geeksforgeeks.org/problems/longest-consecutive-sequence-in-binary-tree/1)
* **Data Structures:** Trees, Depth-First Search (DFS)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#DFS` `#BinaryTree` `#DataStructures` `#GeeksforGeeks` `#C++`