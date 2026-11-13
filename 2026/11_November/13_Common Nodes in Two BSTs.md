# 🌳 Common Nodes in Two BSTs

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-51.7%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given the roots `r1` and `r2` of two Binary Search Trees (BST), find all nodes that are present in both trees (i.e., the intersection nodes of the two BSTs).[cite: 1]

Return the common node values in **sorted order**.[cite: 1]

---

## 💡 Examples

### Example 1

```text
Input: 
r1 = [5, 1, 10, 0, 4, 7, N, N, N, N, N, N, 9] 
r2 = [10, 7, 20, 4, 9, N, N]  

Output: [4, 7, 9, 10]
Explanation: The values present in both BSTs are 4, 7, 9, and 10. Hence, the answer is [4, 7, 9, 10].[cite: 1]
```

<details>
<summary>📖 <b>Example 1 Breakdown</b></summary>

1. **Tree 1 (r1):** Contains nodes `{0, 1, 4, 5, 7, 9, 10}`.
2. **Tree 2 (r2):** Contains nodes `{4, 7, 9, 10, 20}`.
3. **Intersection:** Comparing both sets, the common elements are `4, 7, 9, 10`.
4. **Result:** Because we need them in sorted order, an in-order traversal strategy naturally produces the required output `[4, 7, 9, 10]`.

</details>

### Example 2

```text
Input: 
r1 = [10, 2, 11, 1, 3, N, N]
r2 = [2, 1, 3]

Output: [1, 2, 3]
Explanation: The values 1, 2, and 3 are present in both BSTs. Hence, the answer is [1, 2, 3].[cite: 1]
```

---

## ⚠️ Constraints

> - `1 ≤ size of binary trees ≤ 10^5`[cite: 1]
> - `0 ≤ Node.data ≤ 10^9`[cite: 1]

---

## 🚀 Solution Approaches

### Optimized Approach: Simultaneous In-Order Traversal

**Intuition:** 
Since an in-order traversal of a Binary Search Tree processes the nodes in ascending sorted order, we can traverse both BSTs simultaneously. This essentially transforms the problem into a "merge two sorted arrays" operation, but done on-the-fly to save space. By utilizing two stacks to simulate the recursive traversal, we can control the pace of exploration for both trees and compare their elements one by one.

```cpp
// Intuition: We can find common elements in sorted order by performing a simultaneous iterative in-order traversal on both BSTs.
// Approach: 
// 1. Use two stacks to simulate in-order traversal for both trees.
// 2. Traverse to the leftmost nodes of both BSTs, pushing nodes onto their respective stacks.
// 3. Compare the top nodes of both stacks (the current smallest unvisited elements).
// 4. If values are equal, add to the result, pop both, and move to their right subtrees.
// 5. If the first tree's node is smaller, pop it and move to its right subtree.
// 6. If the second tree's node is smaller, pop it and move to its right subtree.
// Time Complexity: O(n1 + n2) where n1 and n2 are the number of nodes in r1 and r2 respectively. We visit each node at most once[cite: 1].
// Space Complexity: O(h1 + h2) where h1 and h2 are the heights of r1 and r2 respectively, representing the maximum elements stored in the stacks at any time[cite: 1].

class Solution {
  public:
    vector<int> findCommon(Node* r1, Node* r2) {
        vector<int> result;
        stack<Node*> s1, s2; // Stacks to manage iterative traversal
        Node* curr1 = r1;
        Node* curr2 = r2;

        while (curr1 != nullptr || curr2 != nullptr || !s1.empty() || !s2.empty()) {
            // Traverse to the leftmost node of the first BST
            while (curr1 != nullptr) {
                s1.push(curr1);
                curr1 = curr1->left;
            }

            // Traverse to the leftmost node of the second BST
            while (curr2 != nullptr) {
                s2.push(curr2);
                curr2 = curr2->left;
            }

            // If either stack is empty, no more common elements can exist
            if (s1.empty() || s2.empty()) {
                break;
            }

            Node* top1 = s1.top();
            Node* top2 = s2.top();

            // If values match, add to result and move to right subtrees for both
            if (top1->data == top2->data) {
                result.push_back(top1->data);
                s1.pop();
                s2.pop();
                curr1 = top1->right;
                curr2 = top2->right;
            } 
            // If the value in BST 1 is smaller, move to its right subtree
            else if (top1->data < top2->data) {
                s1.pop();
                curr1 = top1->right;
            } 
            // If the value in BST 2 is smaller, move to its right subtree
            else {
                s2.pop();
                curr2 = top2->right;
            }
        }

        return result;
    }
};

/*
*
* Dry Run
* Input: r1 = [5, 1, 10], r2 = [10, 7, 20]
*
* Initialization:
* s1 = [], s2 = [], curr1 = Node(5), curr2 = Node(10)
*
* Step 1 (Push left paths):
* s1 = [5, 1], s2 = [10, 7]
* Compare tops: 1 < 7 -> Pop s1. curr1 moves to 1->right (null).
*
* Step 2 (Push left paths):
* s1 = [5], s2 = [10, 7]
* Compare tops: 5 < 7 -> Pop s1. curr1 moves to 5->right (10).
*
* Step 3 (Push left paths):
* s1 = [10], s2 = [10, 7]
* Compare tops: 10 > 7 -> Pop s2. curr2 moves to 7->right (null).
*
* Step 4 (Push left paths):
* s1 = [10], s2 = [10]
* Compare tops: 10 == 10 -> Match! Add 10 to result. 
* Pop both. curr1 = 10->right (null), curr2 = 10->right (null).
*
* Result: [10]
*
*/
```

---

## 🧠 Key Insights
- **Space Efficiency:** Storing the entire in-order traversal of both trees into arrays would cost `O(n1 + n2)` space. By using an iterative stack approach, we only store a single path from the root to a leaf at any given moment, limiting our space complexity to `O(h1 + h2)`.
- **Early Stopping:** If either stack becomes empty during the comparison phase, it means we have completely exhausted one of the trees. We can immediately break the loop, saving unnecessary operations.

---

## 🔍 Further Exploration
- Intersection of Two Linked Lists
- Merge Two Balanced Binary Search Trees
- Two Sum IV - Input is a BST

---

## 🔗 References
- **GeeksforGeeks Problem:** [Common Nodes in Two BSTs](https://www.geeksforgeeks.org/problems/print-common-nodes-in-bst/1)[cite: 1]

---

## 👨‍💻 Author
- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`#binary-search-tree` `#two-pointers` `#stack` `#cpp` `#geeksforgeeks`