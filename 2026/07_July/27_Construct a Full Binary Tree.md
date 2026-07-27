# 🌳 Construct a Full Binary Tree

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty Medium" />
  <img src="https://img.shields.io/badge/Accuracy-74.63%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="MIT License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two arrays `pre[]` and `preMirror[]` of size `n` containing unique elements, where `pre[]` represents the preorder traversal of a full binary tree and `preMirror[]` represents the preorder traversal of its mirror tree, construct the original full binary tree using these traversals.

**Note:** A general binary tree cannot be uniquely constructed using these two traversals. However, a full binary tree can be constructed uniquely from the given traversals without any ambiguity.

---

## 📖 Examples

**Example 1:**
```text
Input: pre[] = [0, 1, 2], preMirror[] = [0, 2, 1]
Output: [0, 1, 2]
Explanation: The tree will look like:
       0
     /   \
    1     2
```

**Example 2:**
```text
Input: pre[] = [1, 2, 4, 5, 3, 6, 7], preMirror[] = [1, 3, 7, 6, 2, 5, 4]
Output: [1, 2, 4, 5, 3, 6, 7]
Explanation: The tree will look like:
         1
       /   \
      2     3
     / \   / \
    4   5 6   7
```

<details>
<summary>📖 <b>Example Breakdown</b> (Click to Expand)</summary>

Let's break down **Example 1**: `pre = [0, 1, 2]`, `preMirror = [0, 2, 1]`

1. **Root Identification:** The first element of `pre` is `0`. So, the root is `0`.
2. **Left Child:** In a full binary tree preorder, the node immediately following the root is the left child. So, `1` is the left child of `0`.
3. **Partitioning:** We find `1` in `preMirror`. It is at index `2`. 
    * In `preMirror`, the format is `(Root, Right-Subtree, Left-Subtree)`.
    * Since `1` is at index `2`, the left subtree elements are all elements from index `2` to the end of `preMirror`.
    * The right subtree elements are between index `1` and index `1` (which is just `2`).
4. **Recursion:** We recursively build the left subtree with `[1]` and the right subtree with `[2]`, attaching them to `0`.
</details>

---

## 🛑 Constraints

* `1 <= pre.size() <= 10^5`
* `0 <= pre[i] <= 10^9`
* `1 <= preMirror.size() <= 10^5`
* `0 <= preMirror[i] <= 10^9`

---

## 🧠 Solution Approach

```cpp
// Intuition:
// A full binary tree (where every node has 0 or 2 children) can be uniquely constructed
// using its preorder and mirror preorder traversals. The preorder traversal visits nodes
// in (Root, Left, Right) order, while the mirror preorder visits (Root, Right, Left).
// By picking the first element of preorder as the root, the very next element is guaranteed
// to be the root of the left subtree. We can find this left child's position in the mirror
// preorder to determine the exact boundaries of the left and right subtrees.
//
// Approach:
// 1. Map all elements of preMirror to their indices using an unordered_map for O(1) lookups.
// 2. Use a recursive function with a global (or class-level) index for the `pre` array.
// 3. For the current recursive call, create a node with `pre[preIndex]` and increment the index.
// 4. If the current subarray in preMirror has only one element (l == r), return the leaf node.
// 5. Otherwise, the next element in `pre` (i.e., `pre[preIndex]`) is the left child.
// 6. Find the index of this left child in `preMirror` using the map. Let this index be `mid`.
// 7. The left subtree corresponds to the range `[mid, r]` in preMirror.
// 8. The right subtree corresponds to the range `[l + 1, mid - 1]` in preMirror.
// 9. Recursively build the left and right subtrees and attach them to the current node.
//
// Time Complexity: O(n) - We visit each node exactly once. Map lookups take O(1) time on average.
// Space Complexity: O(n) - The unordered_map takes O(n) space, and the recursion stack takes O(n) space in the worst case (skewed tree).

/* Structure of Binary Tree Node
class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};*/

class Solution {
    int preIndex = 0;
    unordered_map<int, int> mirrorPos;

    Node* solve(vector<int>& pre, vector<int>& preMirror, int l, int r) {
        // Base case: if index is out of bounds or invalid range
        if (preIndex >= pre.size() || l > r) {
            return nullptr;
        }

        // Create current root and move to the next element in preorder
        Node* root = new Node(pre[preIndex++]);

        // If it's a leaf node, return the node immediately
        if (l == r) {
            return root;
        }

        // The next element in preorder is the root of the left subtree
        int leftNodeVal = pre[preIndex];
        int mid = mirrorPos[leftNodeVal];

        // Recursively construct left and right subtrees based on boundaries in preMirror
        root->left = solve(pre, preMirror, mid, r);
        root->right = solve(pre, preMirror, l + 1, mid - 1);

        return root;
    }

  public:
    Node* constructBinaryTree(vector<int>& pre, vector<int>& preMirror) {
        // Map values to their indices in preMirror for quick lookup
        for (int i = 0; i < preMirror.size(); i++) {
            mirrorPos[preMirror[i]] = i;
        }
        
        // Start the recursive construction with full boundaries
        return solve(pre, preMirror, 0, preMirror.size() - 1);
    }
};

/*
Dry Run
Input: pre = [0, 1, 2], preMirror = [0, 2, 1]

Map 'mirrorPos': {0:0, 2:1, 1:2}
Initial call: solve(pre, preMirror, l=0, r=2), preIndex = 0

Step 1: preIndex = 0, val = 0. root = Node(0). preIndex becomes 1. l(0) != r(2).
Left child value = pre[1] = 1.
mid = mirrorPos[1] = 2.
root->left = solve(l=2, r=2). root->right = solve(l=1, r=1).

Step 2: solve(l=2, r=2), preIndex = 1
val = 1. root = Node(1). preIndex becomes 2. l(2) == r(2).
Returns Node(1) to root->left.

Step 3: solve(l=1, r=1), preIndex = 2
val = 2. root = Node(2). preIndex becomes 3. l(1) == r(1).
Returns Node(2) to root->right.

Result: Tree constructed with 0 at root, 1 as left child, 2 as right child.
*/
```

---

## 💡 Key Insights

* **Preorder properties:** In any standard preorder traversal `(Root, Left, Right)`, the element directly following the root is the start of the left subtree.
* **Mirror properties:** In a mirror preorder traversal `(Root, Right, Left)`, the left subtree appears at the very end of the array sequence for that specific subtree block. 
* **Hash Mapping:** By mapping the `preMirror` array into an `unordered_map`, we reduce the time taken to search for the left child's index from O(n) to O(1), optimizing the total time complexity down from O(n²) to O(n).

---

## 🔭 Further Exploration

* **Construct Tree from Inorder and Preorder:** A foundational problem that explores similar recursive array partitioning techniques.
* **Construct Tree from Inorder and Postorder:** Another classic that reinforces how to identify roots and subtree boundaries.
* **Check if a Binary Tree is Full:** Practice verifying the structural properties of full binary trees.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Construct a Full Binary Tree](https://www.geeksforgeeks.org/problems/construct-a-full-binary-tree--170648/1)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

* `Tree`
* `Binary Tree`
* `Traversal`
* `Data Structures`
* `Recursion`