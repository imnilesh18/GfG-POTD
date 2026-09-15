# 🟩 Visit Leaves with Budget

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Leaf%20Under%20Budget-008a00?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/leaf-under-budget/1)
[![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](https://www.geeksforgeeks.org/problems/leaf-under-budget/1)
[![Accuracy: 50.05%](https://img.shields.io/badge/Accuracy-50.05%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/leaf-under-budget/1)
[![Points: 2](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/leaf-under-budget/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](LICENSE)

> ⚠️ **Educational Use Only:**  
> This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a binary tree and an integer $k$, where you start from the root at level 1. The cost of visiting a leaf node is equal to the level of that leaf node. You can visit any number of leaf nodes, but the total cost of visiting them must not exceed $k$.

Return the **maximum number of leaf nodes** that can be visited within the given budget $k$.

---

## 💡 Examples

### Example 1
```text
Input: root[] = [10, 8, 2, 3, N, 3, 6, N, N, N, 4], k = 8
Output: 2
Explanation:
Cost For visiting Leaf Node 3: 3
Cost For visiting Leaf Node 4: 4
Cost For visiting Leaf Node 6: 3
To maximize the number of visited leaves, choose the two cheapest leaves: Cost = 3 + 3 = 6 ≤ 8. 
Thus, the maximum number of leaf nodes that can be visited is 2.
```

### Example 2
```text
Input: root[] = [1, 2, 3, 4, 5, 6, 7], k = 5
Output: 1
Explanation: 
The leaf nodes are 4, 5, 6 and 7, and all are at level 3. Therefore, visiting each leaf costs 3. 
With a budget of 5, we can visit only one leaf because: 3 ≤ 5, but 3 + 3 > 5. 
Thus, the maximum number of leaf nodes that can be visited is 1.
```

### Example 3
```text
Input: root[] = [1], k = 1
Output: 1
Explanation: 
The root node is also a leaf node and is at level 1. Therefore, its visiting cost is 1. 
Thus, the maximum number of leaf nodes that can be visited is 1.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough of Example 1)</b></summary>

<br>

**Tree Level Structure:**
- **Level 1:** Root node `10`
- **Level 2:** Left child `8`, Right child `2`
- **Level 3:** Node `3` (Leaf), Node `3` (Leaf), Node `6`
- **Level 4:** Node `4` (Leaf)

**Leaf Costs:**
- Leaf `3` at level 3 $\rightarrow$ Cost = `3`
- Leaf `3` at level 3 $\rightarrow$ Cost = `3`
- Leaf `4` at level 4 $\rightarrow$ Cost = `4`

**Greedy Execution with Budget $k = 8$:**
- Sort costs: `[3, 3, 4]`
- Pick 1st leaf (cost 3): Remaining budget $8 - 3 = 5$, Count = `1`
- Pick 2nd leaf (cost 3): Remaining budget $5 - 3 = 2$, Count = `2`
- Try 3rd leaf (cost 4): $2 < 4$ (Cannot afford)

**Result:** Maximum leaf nodes visited = **2**
</details>

---

## 🔒 Constraints

- $1 \le \text{size of binary tree} \le 10^5$
- $1 \le k \le 10^4$

---

## 🛠️ Solution Approach

### Depth-First Search (DFS) + Greedy Selection

#### Intuition
To maximize the total count of leaf nodes visited under budget $k$, we should prioritize visiting the leaves located at shallower levels (cheapest costs) first. This optimal substructure invites a **Greedy Approach**.

#### Approach
1. **Traverse Tree:** Perform a DFS traversal starting from the root at level 1.
2. **Collect Leaf Costs:** Whenever a leaf node (node with no left or right child) is reached, record its current level (cost) in a vector.
3. **Sort Costs:** Sort the vector of leaf levels in ascending order so that cheapest leaves come first.
4. **Greedy Iteration:** Iterate through the sorted leaf levels, subtracting each cost from $k$ and incrementing the count until $k$ is insufficient.

```cpp
// Intuition: To maximize visited leaves within budget k, greedily pick leaves with smallest levels (lowest costs) first.
// Approach: Collect levels of all leaves via DFS, sort them ascendingly, and subtract costs from budget k greedily.
// Time Complexity: O(N + L log L) where N is total nodes and L is leaf count due to DFS traversal and sorting.
// Space Complexity: O(N) for recursion stack depth and storing leaf levels in a vector.

/* Binary Tree Node Structure
class Node {
  public:
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};
*/

class Solution {
  private:
    // Helper function to perform DFS and collect leaf levels
    void collectLeafLevels(Node* root, int level, vector<int>& leafLevels) {
        if (!root) return;

        // If leaf node, record its level (cost)
        if (!root->left && !root->right) {
            leafLevels.push_back(level);
            return;
        }

        // Recursively traverse left and right subtrees with level incremented
        collectLeafLevels(root->left, level + 1, leafLevels);
        collectLeafLevels(root->right, level + 1, leafLevels);
    }

  public:
    int getCount(Node *root, int k) {
        vector<int> leafLevels;
        
        // Step 1: Collect levels of all leaf nodes starting at level 1
        collectLeafLevels(root, 1, leafLevels);

        // Sort leaves by cost (level) ascending
        sort(leafLevels.begin(), leafLevels.end());

        int count = 0;
        // Step 2: Greedily pick leaves with minimum cost
        for (int cost : leafLevels) {
            if (k >= cost) {
                k -= cost;
                count++;
            } else {
                break;
            }
        }

        return count;
    }
};

/*
* Dry Run
*
* Input Tree Structure:
*        10 (Level 1)
*       /  \
*      8    2 (Level 2)
*     /    / \
*    3    3   6 (Level 3)
*              \
*               4 (Level 4)
* Budget k = 8
*
* DFS Traversal collects leaf levels:
* Leaf node 3 at left subtree has level 3
* Leaf node 3 at right subtree has level 3
* Leaf node 4 at right subtree has level 4
* Recorded leafLevels array is [3, 3, 4]
*
* Sorting leafLevels array:
* Array remains [3, 3, 4]
*
* Greedy Subtraction Loop:
* Cost 3: budget k becomes 8 - 3 = 5, total count becomes 1
* Cost 3: budget k becomes 5 - 3 = 2, total count becomes 2
* Cost 4: budget k = 2 is less than cost 4, loop terminates
*
* Returned maximum count is 2
*/
```

---

## 🔑 Key Insights

- **Greedy Choice Property:** Picking the leaf with the smallest cost leaves maximum budget for remaining leaves, ensuring optimal solution.
- **Alternative BFS Approach:** Performing a Breadth-First Search (Level Order Traversal) visits leaves inherently in non-decreasing order of their levels. This allows picking leaves directly until budget runs out without requiring an explicit sorting step.

---

## 🔍 Further Exploration

- [Sum of Leaf Nodes at Min Level](https://www.geeksforgeeks.org/problems/sum-of-leaf-nodes-at-min-level/1)
- [Count Leaves in Binary Tree](https://www.geeksforgeeks.org/problems/count-leaves-in-binary-tree/1)
- [Root to Leaf Paths Sum](https://www.geeksforgeeks.org/problems/root-to-leaf-paths-sum/1)

---

## 📚 References

- **GeeksforGeeks Problem:** [Leaf Under Budget](https://www.geeksforgeeks.org/problems/leaf-under-budget/1)
- **Data Structures:** Binary Tree, Depth-First Search, Greedy Algorithm

---

## 👤 Author

Crafted with ❤️ by **[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

[![Tag: tree](https://img.shields.io/badge/Tag-tree-blue?style=flat-square)](https://github.com/imnilesh18)
[![Tag: binary-tree](https://img.shields.io/badge/Tag-binary--tree-green?style=flat-square)](https://github.com/imnilesh18)
[![Tag: dfs](https://img.shields.io/badge/Tag-dfs-orange?style=flat-square)](https://github.com/imnilesh18)
[![Tag: greedy](https://img.shields.io/badge/Tag-greedy-purple?style=flat-square)](https://github.com/imnilesh18)
[![Tag: geeksforgeeks](https://img.shields.io/badge/Tag-geeksforgeeks-red?style=flat-square)](https://github.com/imnilesh18)

---

> ⚠️ **Educational Purpose Reminder:**  
> This code and accompanying documentation are created for learning, practice, and personal skill development only.