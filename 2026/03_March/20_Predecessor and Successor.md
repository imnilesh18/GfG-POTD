# 🌳 Predecessor and Successor

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/predecessor-and-successor/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-47.36%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
  </a>
</p>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

You are given the `root` of a **Binary Search Tree (BST)** and an integer `key`. You need to find the inorder **predecessor** and **successor** of the given key. If either the predecessor or successor is not found, then set it to `NULL`.

**Note:** In an inorder traversal, the number just **smaller** than the target is the predecessor, and the number just **greater** than the target is the successor. 

---

## 💡 Examples

### Example 1
```text
Input: root = [50, 30, 70, 20, 40, 60, 80], key = 65
Output: [60, 70]
Explanation: In the given BST the inorder predecessor of 65 is 60 and the inorder successor of 65 is 70.
````

### Example 2

```text
Input: root = [8, 1, 9, N, 4, N, 10, 3], key = 8
Output: [4, 9]
Explanation: In the given BST the inorder predecessor of 8 is 4 and the inorder successor of 8 is 9.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>

Let's trace **Example 1**:

  - **Tree Structure:**
    ```text
              50
            /    \
          30      70
         /  \    /  \
        20  40  60   80
    ```
  - **Inorder Traversal:** `[20, 30, 40, 50, 60, 70, 80]`
  - **Target Key:** `65`
  - Looking at the sorted inorder traversal, the value just smaller than `65` is `60` (Predecessor).
  - The value just greater than `65` is `70` (Successor).
  - **Result:** `Predecessor = 60, Successor = 70`.

</details>

-----

## ⚠️ Constraints

>   - $1 \leq \text{no. of nodes} \leq 10^5$
>   - $0 \leq \text{node->data} \leq 10^6$
>   - $1 \leq \text{key} \leq 10^6$
>
> **Expected Complexities:**
>
>   - **Time Complexity:** $\mathcal{O}(\text{Height of the BST})$
>   - **Auxiliary Space:** $\mathcal{O}(1)$

-----

## 🛠️ Solution Approaches

### 1️⃣ Approach 1: Inorder Traversal Array (Brute Force)

**Intuition:** An inorder traversal of a Binary Search Tree (BST) yields elements in a sorted sequence. By storing the traversal inside an array or list, the problem reduces to a simple linear search array problem. We can iterate through the array to find the element just smaller than the key (predecessor) and the element just larger than the key (successor).

**Step-by-step approach:**

1.  Traverse the BST using Inorder Traversal (Left, Root, Right).
2.  Store the nodes in an array or a list.
3.  Iterate through the array:
      - If the current node's data is `< key`, update `pre` to this node.
      - If the current node's data is `> key`, update `suc` to this node and break (since the array is sorted, this is the immediate successor).
      - If the current node's data `== key`, check `i-1` for predecessor and `i+1` for successor (validating bounds), then break.

**Time Complexity:** $\mathcal{O}(N)$ - where $N$ is the number of nodes in the BST, because we visit all nodes during inorder traversal and then linearly scan the array.
**Space Complexity:** $\mathcal{O}(N)$ - to store the nodes in the auxiliary array.

#### C++ Code

```cpp
// Intuition: An inorder traversal of a BST gives a sorted array. We can use this array to easily find the predecessor and successor.
// Approach: Traverse the BST inorder, store nodes in a vector, and iterate through it to find the nearest smaller and greater values.
// Time Complexity: O(N) — Traversing the tree and scanning the array takes linear time.
// Space Complexity: O(N) — Extra space is required to store the inorder traversal.

class Solution {
public:
    // Helper function to perform inorder traversal and store nodes in a vector
    void inorder(Node* root, vector<Node*>& result) {
        if (!root) {
            return;
        }
        inorder(root->left, result);         // Traverse left subtree
        result.push_back(root);              // Visit current node
        inorder(root->right, result);        // Traverse right subtree
    }

    // Function to find predecessor and successor of given key
    vector<Node*> findPreSuc(Node* root, int key) {
        vector<Node*> result;                // Vector to store inorder traversal result
        inorder(root, result);               // Fill the vector with inorder traversal

        Node* pre = NULL;                    // Pointer to store predecessor
        Node* suc = NULL;                    // Pointer to store successor

        for (int i = 0; i < result.size(); i++) {
            if (result[i]->data < key) {
                pre = result[i];             // Keep updating predecessor until key is found
            } else if (result[i]->data > key) {
                suc = result[i];             // First greater element after key is the successor
                break;
            } else {
                if (i - 1 >= 0) {
                    pre = result[i - 1];     // Element before key is predecessor
                }
                if (i + 1 < result.size()) {
                    suc = result[i + 1];     // Element after key is successor
                }
                break;                       // Break after finding key
            }
        }
        return { pre, suc };                 // Return both predecessor and successor
    }
};
```

#### Java Code

```java
// Intuition: An inorder traversal of a BST gives a sorted array. We can use this array to easily find the predecessor and successor.
// Approach: Traverse the BST inorder, store nodes in an ArrayList, and iterate through it to find the nearest smaller and greater values.
// Time Complexity: O(N) — Traversing the tree and scanning the list takes linear time.
// Space Complexity: O(N) — Extra space is required to store the inorder traversal.

class Solution {
    // Helper method to perform inorder traversal and store nodes
    private void inorder(Node root, ArrayList<Node> result) {
        if (root == null) {
            return;
        }
        inorder(root.left, result);           // Traverse left subtree
        result.add(root);                     // Visit current node
        inorder(root.right, result);          // Traverse right subtree
    }

    public ArrayList<Node> findPreSuc(Node root, int key) {
        ArrayList<Node> result = new ArrayList<>(); // Stores inorder traversal result
        inorder(root, result);                      // Fill the list with inorder traversal

        Node pre = null;                            // Pointer to store predecessor
        Node suc = null;                            // Pointer to store successor

        for (int i = 0; i < result.size(); i++) {
            if (result.get(i).data < key) {
                pre = result.get(i);                // Keep updating predecessor until key is found
            } else if (result.get(i).data > key) {
                suc = result.get(i);                // First greater element after key is the successor
                break;
            } else {
                if (i - 1 >= 0) {
                    pre = result.get(i - 1);        // Element before key is predecessor
                }
                if (i + 1 < result.size()) {
                    suc = result.get(i + 1);        // Element after key is successor
                }
                break;                              // Break after finding key
            }
        }

        ArrayList<Node> ans = new ArrayList<>();
        ans.add(pre);                               // Add predecessor
        ans.add(suc);                               // Add successor
        return ans;                                 // Return result
    }
}
```

```text
/*
 * Dry Run
 *
 * 30
 * /    \
 * 20      40
 * /   \      \
 * 10     25     50
 * /  \    /
 * 5   15  23
 * \
 * 18
 *
 * Inorder traversal of BST:
 * [5, 10, 15, 18, 20, 23, 25, 30, 40, 50]
 *
 * Now we search for the key = 20 in the result list.
 *
 * Loop:
 * i = 0 → 5 < 20 → pre = 5
 * i = 1 → 10 < 20 → pre = 10
 * i = 2 → 15 < 20 → pre = 15
 * i = 3 → 18 < 20 → pre = 18
 * i = 4 → 20 == 20
 * → i-1 = 3 → pre = result[3] = 18
 * → i+1 = 5 → suc = result[5] = 23
 *
 * Result: Predecessor = 18, Successor = 23
 */
```

-----

### 2️⃣ Approach 2: Utilizing BST Properties (Optimized)

**Intuition:** A BST is structured such that all nodes in the left subtree are smaller, and all nodes in the right subtree are larger. Instead of an exhaustive $\mathcal{O}(N)$ search, we can mimic a Binary Search to find the predecessor and successor simultaneously, shrinking the search space drastically.

**Step-by-step approach:**

1.  Initialize `pre` and `suc` as `NULL` and start traversing from the `root`.
2.  While `curr` is not `NULL`:
      - If `curr->data < key`: The current node is strictly smaller, making it a potential predecessor. Update `pre = curr`, and move right (`curr = curr->right`) to find an even closer smaller value.
      - If `curr->data > key`: The current node is strictly larger, making it a potential successor. Update `suc = curr`, and move left (`curr = curr->left`) to find an even closer larger value.
      - If `curr->data == key`: We have found the key\!
          - The predecessor will be the maximum value in the left subtree (i.e., the rightmost node of `curr->left`).
          - The successor will be the minimum value in the right subtree (ie., the leftmost node of `curr->right`).
          - Break out of the loop.

**Time Complexity:** $\mathcal{O}(h)$ - where $h$ is the height of the BST. We only traverse top-down, eliminating halves of the tree at each step.
**Space Complexity:** $\mathcal{O}(1)$ - We only use a few auxiliary pointer variables.

#### C++ Code

```cpp
// Intuition: We can leverage the left-smaller and right-larger property of a BST to actively track potential predecessors and successors without needing an explicit array.
// Approach: Traverse downwards. Update pre when moving right, update suc when moving left. If found, extract max from left child for pre, and min from right child for suc.
// Time Complexity: O(h) — where h is the tree height, due to binary search-like traversal.
// Space Complexity: O(1) — No auxiliary data structures are used.

class Solution {
public:
    // Helper function to find the rightmost node in the left subtree
    Node* rightMost(Node* node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    // Helper function to find the leftmost node in the right subtree
    Node* leftMost(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    // Function to find predecessor and successor
    vector<Node*> findPreSuc(Node* root, int key) {
        Node* pre  = nullptr;     // To store predecessor
        Node* curr = root;        // Start from root
        Node* suc  = nullptr;     // To store successor

        while (curr) {
            if (curr->data < key) {
                pre  = curr;              // Current node could be predecessor
                curr = curr->right;       // Move to right to find closer value
            } else if (curr->data > key) {
                suc  = curr;              // Current node could be successor
                curr = curr->left;        // Move to left to find closer value
            } else {
                if (curr->left) {
                    pre = rightMost(curr->left); // Rightmost node in left subtree is predecessor
                }
                if (curr->right) {
                    suc = leftMost(curr->right); // Leftmost node in right subtree is successor
                }
                break;                           // Key found, no need to search further
            }
        }

        return { pre, suc };                // Return pair of predecessor and successor
    }
};
```

#### Java Code

```java
// Intuition: We can leverage the left-smaller and right-larger property of a BST to actively track potential predecessors and successors without needing an explicit array.
// Approach: Traverse downwards. Update pre when moving right, update suc when moving left. If found, extract max from left child for pre, and min from right child for suc.
// Time Complexity: O(h) — where h is the tree height, due to binary search-like traversal.
// Space Complexity: O(1) — No auxiliary data structures are used.

class Solution {
    // Helper to find rightmost node (max value) in a subtree
    private Node rightMost(Node node) {
        while (node.right != null) {
            node = node.right;
        }
        return node;
    }

    // Helper to find leftmost node (min value) in a subtree
    private Node leftMost(Node node) {
        while (node.left != null) {
            node = node.left;
        }
        return node;
    }

    // Function to find predecessor and successor
    public ArrayList<Node> findPreSuc(Node root, int key) {
        Node pre  = null;         // To store predecessor
        Node suc  = null;         // To store successor
        Node curr = root;         // Start traversal from root

        while (curr != null) {
            if (curr.data < key) {
                pre  = curr;      // Current node is a potential predecessor
                curr = curr.right;
            } else if (curr.data > key) {
                suc  = curr;      // Current node is a potential successor
                curr = curr.left;
            } else {
                if (curr.left != null) {
                    pre = rightMost(curr.left);  // Predecessor is rightmost of left subtree
                }
                if (curr.right != null) {
                    suc = leftMost(curr.right); // Successor is leftmost of right subtree
                }
                break;                          // Key found, break the loop
            }
        }

        ArrayList<Node> res = new ArrayList<>();
        res.add(pre);             // Add predecessor to result
        res.add(suc);             // Add successor to result
        return res;
    }
}
```

```text
/*
 * Dry Run
 *
 * 30
 * /    \
 * 20      40
 * /   \      \
 * 10     25     50
 * /  \    /
 * 5   15  23
 * \
 * 18
 *
 * Key = 20
 *
 * Start from root (30):
 * 30 > 20 → suc = 30, move left
 * 20 == 20 →
 * → curr.left exists → pre = rightMost(10)
 * → rightMost(10) = 15 → 15 has right → move to 18 → no right → pre = 18
 * → curr.right exists → suc = leftMost(25)
 * → leftMost(25) = 23 → no left → suc = 23
 *
 * Final Answer: Predecessor = 18, Successor = 23
 */
```

-----

## 🧠 Key Insights

  - **BST Traversal Properties:** An inorder traversal guarantees a perfectly sorted array for any valid BST. This makes finding relationships like nearest smaller (predecessor) and nearest greater (successor) straightforward.
  - **Space Optimization:** The optimized approach successfully strips away the $\mathcal{O}(N)$ space penalty by actively updating `pre` and `suc` variables sequentially during a binary-search-like traversal. When the key is actually found, searching solely its explicit left/right substructures ensures absolute correctness without tracking full history.

-----

## 🚀 Further Exploration

Want to solidify your Binary Search Tree skills? Check out these related problems:

  - [Check for BST](https://www.geeksforgeeks.org/problems/check-for-bst/1)
  - [Lowest Common Ancestor in a BST](https://www.geeksforgeeks.org/problems/lowest-common-ancestor-in-a-bst/1)
  - [Inorder Successor in BST](https://www.geeksforgeeks.org/problems/inorder-successor-in-bst/1)

-----

## 🔗 References

  - **GeeksforGeeks Problem:** [Predecessor and Successor](https://www.geeksforgeeks.org/problems/predecessor-and-successor/1)

-----

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

-----

## 🏷️ Tags

  - `binary-search-tree`
  - `tree`
  - `data-structures`
  - `geeksforgeeks`
